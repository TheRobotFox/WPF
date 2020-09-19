#include "Clipboard.h"
#include "Utils.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
//int main(){
	struct List* List = CreateList("Data\\raw", "Data\\fin");

	if (List==0) {
		//printf("Can't open File!");
		MessageBoxA(NULL, "Konnte Listen nicht Laden!", "GenderApp", MB_OK);
		return -1;
	}

	int size = 0;
	int copy_size=0;
	//MessageBoxA(NULL, "Gender App gestarted!", "GenderApp", MB_OK);
	while (1) {
		Sleep(100);
		if (GetAsyncKeyState(VK_RMENU) && GetKeyState('L') & 0x8000) {
			while (GetKeyState(VK_RMENU) & 0x8000);
			Sleep(50);
			char* Copy_clipboard = GetClipboard(&copy_size);
			Sleep(50);
			clearClipboard();
			GetText();
			Sleep(50);
			char* String = GetClipboard(&size);
			if ((size > 1) && String!=0) {
				char* new_String = Gender(String, &size, List);
				SetClipboard(new_String, size);
				Sleep(50);
				SetText();
				Sleep(20);
				free(new_String);
				free(String);
			}
			SetClipboard(Copy_clipboard, copy_size);
			free(Copy_clipboard);

		}
		if (GetAsyncKeyState(VK_RMENU) && GetKeyState('4') & 0x8000) {
			MessageBoxA(NULL, TEXT("Beende GenderApp!"), TEXT("GenderApp"), MB_OK | MB_SYSTEMMODAL);
			return 0;
		}

	}

	//printf("\n%s\n", new_String);
	return 0;
}