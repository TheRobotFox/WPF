#include "Include/Utils.h"

// turn Letter into it's upper form
char uppr(char Character) {
	if (Character > 90)
		Character -= 32;
	return Character;
}

// get pos of Letter in Alphabet
unsigned char charindex(char Letter) {
	Letter = uppr(Letter);
	return Letter - 65;
}

// check if Character is Valid Letter
char isLetter(unsigned char Letter) {
	Letter = charindex(Letter);
	if (Letter > 25)
		return 0;
	return 1;
}

// counts Words in a String
int countWords(const char* String, int size) {
	int count = 0;
	int pos = 0;
	while (pos < size - 1) {
		while (isLetter(String[pos]) && (pos < size - 1))
			pos++;
		count++;
		while (!isLetter(String[pos]) && (pos < size - 1))
			pos++;
	}
	return count + 1;
}

// read specific line of file

void ReadLine(char* buff, int lineNum, struct WordList* List) {
	fseek(List->file, List->lines_beginging[lineNum], SEEK_SET);
	fgets(buff, max_word_length, List->file);
}
// Compare Strings

char cmp(const char* StrA, const char* StrB, int size) {
	char A;
	char B;
	for (int i = 0; i < size; i++) {
		A = uppr(StrA[i]);
		B = uppr(StrB[i]);

		if (A != B)
			return 1;
	}
	if (isLetter(StrA[size]) != isLetter(StrB[size]))
		return 1;
	return 0;
}

void GetText() {
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
	free(ip);
}

void SetText() {
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
	free(ip);
}

unsigned int FindWord(const char* String, int length, struct Hit* Hit, struct List* List) {

	// Setup
	int lookuptable_pos = 0;
	int pos = 0;
	unsigned int Hit_index = 0;


	while (pos < length - 1) {

		// Goto First Letter
		while (!isLetter(String[pos]) && (pos < length - 1))
			pos++;
		if (pos < length - 1) {
			// get lookuptable_pos for Lookuptable
			lookuptable_pos = charindex(String[pos]);
			for (int check_pos = List->lookUpTable[lookuptable_pos]; check_pos < List->lookUpTable[lookuptable_pos + 1]; check_pos++) {
				ReadLine(tmp, check_pos, List->original);
				if (!cmp(String + pos, tmp, strlen(tmp) - 1)) {
					// Fill "Hit" structure with information
					Hit[Hit_index].length = strlen(tmp);
					Hit[Hit_index].pos = pos;
					Hit[Hit_index].line = check_pos;
					Hit_index++;
					pos += strlen(tmp) - 1;
				}
			}
			while (isLetter(String[pos]) && (pos < length - 1)) {
				pos++;
			}
		}
	}
	return Hit_index;
}


char* Gender(const char* String, int* length, struct List* List) {

	// Setup
	int words = countWords(String, *length);
	#ifdef DEBUG
	printf("words: %d\n", words);

	#endif // DEBUG


	struct Hit* Hit = malloc(words * sizeof(struct Hit));

	unsigned int Hits = FindWord(String, *length, Hit, List);


	for (unsigned int i = 0; i < Hits; i++) {

		ReadLine(tmp, Hit[i].line, List->corrected);

		* length += strlen(tmp) - Hit[i].length;
	}
	char* new_String = malloc((*length) + 1);

	unsigned int current_Hit = 0;
	int offset = 0;
	int pos;
	for (pos = 0; pos < *length - 1; pos++) {
		if (pos - offset == Hit[current_Hit].pos) {
			ReadLine(tmp, Hit[current_Hit].line, List->corrected);
			for (int i = 0; i < strlen(tmp) - 1; i++) {
				new_String[pos + i] = tmp[i];
			}

			pos += strlen(tmp) - 2;
			offset += strlen(tmp) - Hit[current_Hit].length;

			current_Hit++;
			continue;
		}
		new_String[pos] = String[pos - offset];
	}
	new_String[*length - 1] = 0;
	free(Hit);
	return new_String;

}


