#include <Windows.h>

BOOL SelfDestruct() {
	TCHAR szFile[MAX_PATH], szCmd[MAX_PATH];

	if ((GetModuleFileName(0, szFile, MAX_PATH) != 0) &&
		(GetShortPathName(szFile, szFile, MAX_PATH) != 0))
	{
		lstrcpy(szCmd, L"/c del ");
		lstrcat(szCmd, szFile);
		lstrcat(szCmd, L" >> NUL");

		if ((GetEnvironmentVariable(L"ComSpec", szFile, MAX_PATH) != 0) &&
			((INT)ShellExecute(0, 0, szFile, szCmd, 0, SW_HIDE) > 32))
			return TRUE;
	}

	return FALSE;
}
