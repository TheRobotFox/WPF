#include "clipboard.h"
#include <stdio.h>

void Clipboard_copy()
{
        INPUT ip[2];
	memset(ip, 0, sizeof(INPUT) * 2);
	ip[0].type = INPUT_KEYBOARD;
        ip[0].ki.wVk = VK_CONTROL;
	ip[1].type = INPUT_KEYBOARD;
        ip[1].ki.wVk = 'C';
	SendInput(2, ip, sizeof(INPUT));
        ip[0].ki.dwFlags = KEYEVENTF_KEYUP;
        ip[1].ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(2, ip, sizeof(INPUT));
}

void Clipboard_paste()
{
        INPUT ip[2];
        memset(ip, 0, sizeof(INPUT) * 2);
        ip[0].type = INPUT_KEYBOARD;
	ip[0].ki.wVk = VK_CONTROL;
        ip[1].type = INPUT_KEYBOARD;
	ip[1].ki.wVk = 'V';
	SendInput(2, ip, sizeof(INPUT));
	ip[0].ki.dwFlags = KEYEVENTF_KEYUP;
        ip[1].ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(2, ip, sizeof(INPUT));
}

void Clipboard_set(const char *data, int size)
{
	HGLOBAL h = GlobalAlloc(GMEM_MOVEABLE, size);
	memcpy(GlobalLock(h), data, size);
	GlobalUnlock(h);
	OpenClipboard(NULL);
	EmptyClipboard();
	SetClipboardData(CF_TEXT, h);
	CloseClipboard();
}

void Clipboard_clear()
{
	OpenClipboard(NULL);
	EmptyClipboard();
	CloseClipboard();
}

int Clipboard_get(char **str)
{
	if (OpenClipboard(NULL)) {
		HANDLE h;
		h = GetClipboardData(CF_TEXT);
		if (h) {
			char* clipboard_text = GlobalLock(h);
			int length = strlen(clipboard_text)+1;
			if (length > 1) {
				*str = malloc(length*sizeof(char));
				memcpy(*str, clipboard_text, length);
				GlobalUnlock(h);
				CloseClipboard();
				return length;
			}
			GlobalUnlock(h);
		}
		CloseClipboard();
	}
	return 0;
}
