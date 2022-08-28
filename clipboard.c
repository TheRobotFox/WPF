#include "clipboard.h"
#include <stdio.h>

void copy() {
        INPUT ip[2];                                                      memset(ip, 0, sizeof(INPUT) * 2);
                                                                          ip[0].type = INPUT_KEYBOARD;
        ip[0].ki.wVk = VK_CONTROL;                                        ip[1].type = INPUT_KEYBOARD;
        ip[1].ki.wVk = 'C';                                               SendInput(2, ip, sizeof(INPUT));
        ip[0].ki.dwFlags = KEYEVENTF_KEYUP;
        ip[1].ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(2, ip, sizeof(INPUT));                                  free(ip);
}

void paste() {
        INPUT ip[2];
        memset(ip, 0, sizeof(INPUT) * 2);
        ip[0].type = INPUT_KEYBOARD;                                      ip[0].ki.wVk = VK_CONTROL;
        ip[1].type = INPUT_KEYBOARD;                                      ip[1].ki.wVk = 'V';                                               SendInput(2, ip, sizeof(INPUT));                                  ip[0].ki.dwFlags = KEYEVENTF_KEYUP;
        ip[1].ki.dwFlags = KEYEVENTF_KEYUP;                               SendInput(2, ip, sizeof(INPUT));
        free(ip);                                                 }

void set_clipboard(const char* data, int size) {
	HGLOBAL h = GlobalAlloc(GMEM_MOVEABLE, size);
	memcpy(GlobalLock(h), data, size);
	GlobalUnlock(h);
	OpenClipboard(NULL);
	EmptyClipboard();
	SetClipboardData(CF_TEXT, h);
	CloseClipboard();
}

void clearClipboard() {
	OpenClipboard(NULL);
	EmptyClipboard();
	CloseClipboard();
}

char* get_clipboard(int* length) {
	if (OpenClipboard(NULL)) {
		HANDLE h;
		h = GetClipboardData(CF_TEXT);
		if (h) {
			char* Text = GlobalLock(h);
			*length = strlen(Text)+1;
			if (*length > 1) {
				char* msg = malloc(*length);
				memcpy(msg, Text, *length);
				GlobalUnlock(h);
				CloseClipboard();
				return msg;
			}
			GlobalUnlock(h);
		}
		CloseClipboard();
	}
	return 0;
}
