#include "Clipboard.h"
#include <stdio.h>

void SetClipboard(const char* data, int size) {
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

int Strlen(char* String) {
	int i = 0;
	while (String[i])
		i++;
	return i;
}

char* GetClipboard(int* length) {
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