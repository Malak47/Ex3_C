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
    strncpy(string, "", strlen(string));
}

char GematriaSequences(char word[], char txt[]) {
    int sumOfWord = findMeTheValueOfTheString(word);
    int txtLen = strlen(txt);
    char result[txtLen];
    char saveString[txtLen];
    memset(result, 0, sizeof(result));
    memset(saveString, 0, sizeof(saveString));
    //cleanUpString(result);
    //cleanUpString(saveString);
    int count = 0;                     //012345678911234567892123456
    for (int i = 0; i < txtLen; i++) { //a-bc,dbca-zwxyzabzyxw0dcba~
        memset(saveString, 0, sizeof(saveString));
        for (int k = i; k < txtLen; k++) {
            if ('a' <= txt[k] && txt[k] <= 'z') {
                count += (int) (txt[k]) - 96;
                strncat(saveString, &txt[k], 1);

            } else if ('A' <= txt[k] && txt[k] <= 'Z') {
                count += (int) (txt[k]) - 64;
                strncat(saveString, &txt[k], 1);
            } else if (count != 0) {
                strncat(saveString, &txt[k], 1);
                continue;
            } else {
                i++;
                k = i - 1;
                memset(saveString, 0, sizeof(saveString));
            }
            if (count == sumOfWord) {
                int saveStringLen = strlen(saveString);
                for (int j = 0; j < saveStringLen; j++) {
                    strncat(result, &saveString[j], 1);
                }

                //cleanUpString(saveString);
                memset(saveString, 0, sizeof(saveString));
                count = 0;
                strncat(result, "~", 1);
                i++;
                k = i - 1;
            } else if (count > sumOfWord) {
                //cleanUpString(saveString);
                memset(saveString, 0, sizeof(saveString));
                count = 0;
                i++;
                k = i - 1;
            }
        }
    }
    return result;
}

int main() {
//    printf("%d\n", findMeTheValueOfTheChar('a'));
//    printf("%d", findMeTheValueOfTheString("aaaaaa a, - % 0 a"));
    char word[] = "abcd";
    char txt[] = "a-bc,dbca-zwxyzabzyxw0dcba~";

    printf("%s", GematriaSequences(word, txt));

    return 0;
}