#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define TXT 1024
#define WORD 30

int findMeTheValueOfTheChar(char c) {
    int result = 0;
    if ('a' <= c && c <= 'z') {
        result = (int) (c) - 96;
        return result;

    } else if ('A' <= c && c <= 'Z') {
        result = (int) (c) - 64;
        return result;
    } else {
        return -1;
    }
}

int findMeTheValueOfTheString(char str[]) {
    int result = 0;
    for (int i = 0; i < strlen(str); i++) {
        if ('a' <= str[i] && str[i] <= 'z') {
            result += (int) (str[i]) - 96;
        } else if ('A' <= str[i] && str[i] <= 'Z') {
            result += (int) (str[i]) - 64;
        } else {
            continue;
        }
    }
    return result;
}

void cleanUpString(char string[]) {
    int strLen = strlen(string);
    strncpy(string,"",strlen(string));
}

char GematriaSequences(char word[], char txt[]) {
    int sumOfWord = findMeTheValueOfTheString(word);
    int txtLen = strlen(txt);
    char result[txtLen];
    char saveString[txtLen];
    cleanUpString(result);
    cleanUpString(saveString);
    int count = 0;
    int savei = 0;
    for (int i = 0; i < txtLen; i++) {
        if ('a' <= txt[i] && txt[i] <= 'z') {
            count += (int) (txt[i]) - 96;
            strncat(saveString, &txt[i], 1);

        } else if ('A' <= txt[i] && txt[i] <= 'Z') {
            count += (int) (txt[i]) - 64;
            strncat(saveString, &txt[i], 1);
        } else {
            continue;
        }
        if (count == sumOfWord) {
            int saveStringLen = strlen(saveString);
            for (int j = 0; j < saveStringLen; j++) {
                strncat(result, &saveString[j], 1);
                if (&saveString[j] == 0) {
                    break;
                }
            }
            cleanUpString(saveString);
            count = 0;
            savei++;
            i = savei;
        } else if (count > sumOfWord) {
            cleanUpString(saveString);
            count = 0;
            savei++;
            i = savei;
        }
    }
    return result;
}

int main() {
//    printf("%d\n", findMeTheValueOfTheChar('a'));
//    printf("%d", findMeTheValueOfTheString("aaaaaa a, - % 0 a"));
    char word[] = "abcd";
    char txt[] = "a-bc,dbca-zwxyzabzyxw0dcba~";
    printf("%s%s", GematriaSequences(word, txt));
    return 0;
}
