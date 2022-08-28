#include <windows.h>
#include <stdlib.h>

void set_clipboard(const char* data, int size);
char* get_clipboard(int* length);

void copy();
void paste();
void clearClipboard();
