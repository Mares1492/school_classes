#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct MorseMapping {
    char character;  // the ASCII character
    char* code;      // the Morse code representation
};

struct MorseMapping MorseDictionary[] = {
        {'A', ".-"},
        {'B', "-..."},
        {'C', "-.-."},
        {'D', "-.."},
        {'E', "."},
        {'F', "..-."},
        {'G', "--."},
        {'H', "...."},
        {'I', ".."},
        {'J', ".---"},
        {'K', "-.-"},
        {'L', ".-.."},
        {'M', "--"},
        {'N', "-."},
        {'O', "---"},
        {'P', ".--."},
        {'Q', "--.-"},
        {'R', ".-."},
        {'S', "..."},
        {'T', "-"},
        {'U', "..-"},
        {'U', "..--"},
        {'V', "...-"},
        {'W', ".--"},
        {'X', "-..-"},
        {'Y', "-.--"},
        {'Z', "--.."},
        {'0', "-----"},
        {'1', ".----"},
        {'2', "..---"},
        {'3', "...--"},
        {'4', "....-"},
        {'5', "....."},
        {'6', "-...."},
        {'7', "--..."},
        {'8', "---.."},
        {'9', "----."},
        {' ', "/"},
        {'.', ".-.-.-"},
        {',', "--..--"},
        {'?', "..--.."},
        {'\'', ".----."},
        {'!', "-.-.--"},
        {'/', "-..-."},
        {'(', "-.--."},
        {')', "-.--.-"},
        {'&', ".-..."},
        {':', "---..."},
        {';', "-.-.-."},
        {'=', "-...-"},
        {'+', ".-.-."},
        {'-', "-....-"},
        {'_', "..--.-"},
        {'"', ".-..-."},
        {'$', "...-..-"},
        {'@', ".--.-."},
};


void GetTranslatedSymbol( const char* code) {
    for (int i = 0; i < sizeof(MorseDictionary) / sizeof(struct MorseMapping); i++) {
        if (strcmp(code, MorseDictionary[i].code) == 0) {
            printf("%c", MorseDictionary[i].character);
            return;
        }
    }
    printf("%s{not found}", code);
    // not found
}

int main(){
    FILE *fp;
    char symbol;
    char *code = calloc(10, sizeof(char));
    int head = 0;

    fp = fopen("D:\\C\\files_to_read\\morse1.txt", "r");

    if (fp == NULL) {
        printf("Error opening file\n");
        perror("Error");
        return 1;
    }

    while (fscanf(fp, "%c", &symbol) != EOF) {
        if (symbol == '\n') {
            printf("\n");
            continue;
        }
        if (symbol == '/') {
            GetTranslatedSymbol(code);
            code = calloc(10, sizeof(char));
            head = 0;
            continue;
        }
        code[head] = symbol;
        ++head;
    }
    free(code);
    fclose(fp);

    return 0;
}