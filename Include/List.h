#pragma once
#include "Utils.h"


struct Hit {
	int pos;
	unsigned int line;
	unsigned int length;
};

struct WordList {
	FILE* file;
	unsigned int* lines_beginging;
};

struct List {
	struct WordList* original;
	struct WordList* corrected;
	unsigned int lines_amount;
	unsigned int* lookUpTable;
};

unsigned int* ConvFile(FILE* f, short linecount);

unsigned int* generatelookUptable(FILE* file, unsigned int* line_amount);

struct WordList* LoadWordList(const char* Path, int lines_amount);

struct List* CreateList(const char* Path_original, const char* Path_corrected);