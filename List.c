#include "List.h"

// Get beginning of each new line in the word list

unsigned int* ConvFile(FILE* f, short linecount) {
	fseek(f, 0, SEEK_END);
	int size = ftell(f);
	fseek(f, 0, SEEK_SET);
	int* lines = malloc(linecount * 4);
	memset(lines - 1, 0, linecount * 4);
	for (int i = 1; i < linecount; i++) {
		fgets(tmp, max_word_length, f);
		lines[i] = strlen(tmp) + lines[i - 1] + 1;
		memset(tmp, 0, max_word_length);
	}

	fseek(f, 0, SEEK_SET);
	return lines;
}

// Create LookUpTable from List

unsigned int* generatelookUptable(FILE* file, unsigned int* line_amount) {
	int* lookUpTable = malloc(lookUpTable_length * 4);
	int currentLetter = -1;
	char tablepos = 0;
	int line_count = 0;
	while (!feof(file)) {
		fgets(tmp, max_word_length, file);
		if (charindex(tmp[0]) > currentLetter && isLetter(tmp[0])) {
			currentLetter = charindex(tmp[0]);
			lookUpTable[tablepos] = line_count;
			tablepos++;
			//printf("%c, %d\n", tmp[0], line_count);
		}
		line_count++;
	}
	*line_amount = line_count - 1;
	lookUpTable[tablepos] = line_count-1;
	fseek(file, 0, SEEK_SET);
	return lookUpTable;
}

// read Word list into Wordlist Object

struct WordList* LoadWordList(const char* Path, int lines_amount) {
	struct WordList* List = malloc(sizeof(struct WordList));
	List->file = fopen(Path, "r");
	if (!List->file)
		return 0;
	List->lines_beginging = ConvFile(List->file, lines_amount);

	return List;
}

// Generate List Object 

struct List* CreateList(const char* Path_original, const char* Path_corrected) {

	struct List* List = malloc(sizeof(struct List));
	FILE* file = fopen(Path_original, "r");
	if (!file)
		return 0;
	int line_count;
	List->lookUpTable = generatelookUptable(file, &line_count);
	List->lines_amount = line_count;
	List->original = LoadWordList(Path_original, List->lines_amount);
	List->corrected = LoadWordList(Path_corrected, List->lines_amount);
	fclose(file);
	if (List->original == 0 || List->corrected == 0) {
		return 0;
	}
	return List;
}