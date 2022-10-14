#include <windows.h>
#include <stdlib.h>

void Clipboard_set(const char *data, int size);
int Clipboard_get(char **str);

void Clipboard_copy();
void Clipboard_paste();
void Clipboard_clear();
