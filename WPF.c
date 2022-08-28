#include "clipboard.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	int size;
	while (1) {
		Sleep(100);
		if (GetAsyncKeyState(VK_RMENU) && GetKeyState('P') & 0x8000) {
			while (GetKeyState(VK_RMENU) & 0x8000);
			Sleep(50);
			Copy();
			Sleep(50);
			char* string = get_clipboard(&size);
			if ((size > 1) && string!=0) {

				for(int i=0; i<size; i++)
				{
					if(string[i]=='\\')
						string[i]='/';
				}
				set_clipboard(string, size);
				Sleep(50);
				free(string);
			}

		}
		if (GetAsyncKeyState(VK_RMENU) && GetKeyState('4') & 0x8000) {
			MessageBoxA(NULL, TEXT("Stopping WPF!"), TEXT("GenderApp"), MB_OK | MB_SYSTEMMODAL);
			return 0;
		}

	}

	return 0;
}
