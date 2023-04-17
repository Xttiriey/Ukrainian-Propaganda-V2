#include <Windows.h>
#include <wininet.h>
#include <Shlwapi.h>

#pragma comment(lib, "Wininet.lib")
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "Winmm.lib")



TCHAR _TEMP_PATH_WAV[MAX_PATH];

void DownloadAnthem(const TCHAR* _URL) {
	DeleteUrlCacheEntry(_URL);

	URLDownloadToFile(NULL, _URL, _TEMP_PATH_WAV, 0, NULL);
}

void InitializePath(const TCHAR* _WAV_FILE_NAME) {
    GetTempPath(MAX_PATH, _TEMP_PATH_WAV);

    lstrcat(_TEMP_PATH_WAV, L"\\");
    lstrcat(_TEMP_PATH_WAV, _WAV_FILE_NAME);
}

void CheckAnthem(const TCHAR* _URL, const TCHAR* _WAV_FILE_NAME) {
    InitializePath(_WAV_FILE_NAME);

    if (!PathFileExists(_TEMP_PATH_WAV)) {
        DownloadAnthem(_URL);
    }
}

void PlayAnthem() {
    while (true)
    {
        PlaySound(_TEMP_PATH_WAV, NULL, SND_LOOP);
    }
}