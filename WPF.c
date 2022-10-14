#include <windows.h>
#include "clipboard.h"
#include <time.h>
#include <omp.h>
#include <stdio.h>

#define WAIT 100

//https://stackoverflow.com/questions/4191465/how-to-run-only-one-instance-of-application?noredirect=1&lq=1
BOOL CheckOneInstance()
{
    HANDLE m_hStartEvent = CreateEventW( NULL, TRUE, FALSE, L"EVENT_NAME_HERE" );
    if ( GetLastError() == ERROR_ALREADY_EXISTS ) {
        CloseHandle( m_hStartEvent ); 
        m_hStartEvent = NULL;
        // already exist
        // send message from here to existing copy of the application
        return FALSE;
    }
    // the only instance, start in a usual way
    return TRUE;
}
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
//int main(){/
	if(!CheckOneInstance()){
		MessageBoxA(0, TEXT("WPF arleady running!\nuse Ctrl+1 for help"), TEXT("WPF"), 0);
		return 0;
	}
	while (1) {
		Sleep(20); 
		if (GetAsyncKeyState(VK_CONTROL) && GetKeyState('C') & 0x8000) {

			for(int i=0; i<WAIT; i++)
			{
				if(!(GetKeyState('C') & 0x8000))
					goto stage1;
				Sleep(10);
			}
			continue;
			stage1:
			for(int i=0; i<WAIT; i++)
			{
				if(GetKeyState('C') & 0x8000)
					goto stage2;
				Sleep(10);
			}
			continue;
			stage2:
			char *str;
			int size = Clipboard_get(&str);
			//printf("Converting %d\n", size);
			if (size){

				for(int i=0; i<size; i++)
				{
					if(str[i]=='\\')
						str[i]='/';
				}
				Clipboard_set(str, size);
				free(str);
			}

		}
		if (GetAsyncKeyState(VK_CONTROL) && GetKeyState('1') & 0x8000) {
			MessageBoxA(NULL, TEXT("WPF is running!\nUse double Ctrl+C to copy paths.\nDo Ctrl+4 to exit"), TEXT("WPF"), MB_OK | MB_SERVICE_NOTIFICATION);
		}
		if (GetAsyncKeyState(VK_CONTROL) && GetKeyState('4') & 0x8000) {
			MessageBoxA(NULL, TEXT("Stopping WPF!"), TEXT("WPF"), MB_OK | MB_SERVICE_NOTIFICATION);
			return 0;
		}

	}

	return 0;
}