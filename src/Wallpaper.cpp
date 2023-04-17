#include <Windows.h>
#include <wininet.h>
#include <Shlwapi.h>
#include <gdiplus.h>

#pragma comment(lib, "Wininet.lib")
#pragma comment(lib, "Urlmon.lib")
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "Gdiplus.lib")



TCHAR _TEMP_PATH_BMP[MAX_PATH], _TEMP_PATH_JPG[MAX_PATH];

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid) {
    using namespace Gdiplus;

    UINT  num = 0;
    UINT  size = 0;

    ImageCodecInfo* pImageCodecInfo = NULL;

    GetImageEncodersSize(&num, &size);
    if (size == 0)
        return -1;

    pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
    if (pImageCodecInfo == NULL)
        return -1;

    GetImageEncoders(num, size, pImageCodecInfo);

    for (UINT j = 0; j < num; ++j)
    {
        if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
        {
            *pClsid = pImageCodecInfo[j].Clsid;
            free(pImageCodecInfo);
            return j;
        }
    }

    free(pImageCodecInfo);
    return -1;
}

void ConvertWallpaper(const TCHAR* _TEMP_PATH_JPG, const TCHAR* _TEMP_PATH_BMP) {
	using namespace Gdiplus;

    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    Image* image = Image::FromFile(_TEMP_PATH_JPG);

    Bitmap* bitmap = new Bitmap(image->GetWidth(), image->GetHeight(), PixelFormat24bppRGB);

    Graphics* graphics = Graphics::FromImage(bitmap);
    graphics->DrawImage(image, 0, 0, image->GetWidth(), image->GetHeight());

    CLSID clsid;
    GetEncoderClsid(L"image/bmp", &clsid);

    Status result = bitmap->Save(_TEMP_PATH_BMP, &clsid, NULL);

    delete graphics;
    delete bitmap;
    delete image;

    GdiplusShutdown(gdiplusToken);

    DeleteFile(_TEMP_PATH_JPG);
}

void DownloadWallpaper(const TCHAR* _URL) {
	DeleteUrlCacheEntry(_URL);

	URLDownloadToFile(NULL, _URL, _TEMP_PATH_JPG, 0, NULL);
}

void InitializePaths(const TCHAR* _BMP_FILE_NAME, const TCHAR* _JPG_FILE_NAME) {
    GetTempPath(MAX_PATH, _TEMP_PATH_BMP);
    GetTempPath(MAX_PATH, _TEMP_PATH_JPG);

    lstrcat(_TEMP_PATH_BMP, L"\\");
    lstrcat(_TEMP_PATH_BMP, _BMP_FILE_NAME);

    lstrcat(_TEMP_PATH_JPG, L"\\");
    lstrcat(_TEMP_PATH_JPG, _JPG_FILE_NAME);
}

void CheckWallpaper(const TCHAR* _URL, const TCHAR* _BMP_FILE_NAME, const TCHAR* _JPG_FILE_NAME) {
    InitializePaths(_BMP_FILE_NAME, _JPG_FILE_NAME);

	if (!PathFileExists(_TEMP_PATH_BMP)) {
		DownloadWallpaper(_URL);
		ConvertWallpaper(_TEMP_PATH_JPG, _TEMP_PATH_BMP);
	}
}

void SetWallpaper() {
    SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, (void*)_TEMP_PATH_BMP, SPIF_UPDATEINIFILE);
}