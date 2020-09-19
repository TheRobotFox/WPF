#include <windows.h>
#include <stdlib.h>

void SetClipboard(const char* data, int size);
char* GetClipboard(int* length);
void clearClipboard();
int Strlen(char* String);