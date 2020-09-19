#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "List.h"

#define max_word_length 4096
#define lookUpTable_length 27

char tmp[max_word_length];

char uppr(char Character);

unsigned char charindex(char Letter);

int countWords(const char* String, int size);

void ReadLine(char* buff, int lineNum, struct WordList* List);

char isLetter(unsigned char Letter);

char cmp(const char* StrA, const char* StrB, int size);

void GetText();

void SetText();

unsigned int FindWord(const char* String, int length, struct Hit* Hit, struct List* List);

char* Gender(const char* String, int* length, struct List* List);