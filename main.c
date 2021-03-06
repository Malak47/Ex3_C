#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define TXT 1024
#define WORD 30

//------------------------------Q1--------------------------------------
int findMeTheValueOfTheChar(char c) {
    int result;
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

char *GematriaSequences(char *word, char *txt) {
    int sumOfWord = findMeTheValueOfTheString(word);
    int txtLen;
    txtLen = strlen(txt);
    char *result = calloc(TXT + 1, TXT);
    char saveString[txtLen];
    int MC = 0;
    memset(result, 0, sizeof(result));
    memset(saveString, 0, sizeof(saveString));
    int count = 0;
    for (int i = 0; i < txtLen; i++) {
        memset(saveString, 0, sizeof(saveString));
        for (int k = i; k < txtLen; k++) {
            if (txt[k] == '~') {
                i = txtLen - 1;
                break;
            }
            if ('a' <= txt[k] && txt[k] <= 'z') {
                count += (int) (txt[k]) - 96;
                strncat(saveString, &txt[k], 1);

            } else if ('A' <= txt[k] && txt[k] <= 'Z') {
                count += (int) (txt[k]) - 64;
                strncat(saveString, &txt[k], 1);
            } else if (count != 0) { // ab i-> -    ab-
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
                    MC++;
                }
                memset(saveString, 0, sizeof(saveString));
                count = 0;
                strncat(result, "~", 1);
                MC++;
                i++;
                k = i - 1;
            } else if (count > sumOfWord) {

                memset(saveString, 0, sizeof(saveString));
                count = 0;
                i++;
                k = i - 1;
            }
        }
    }
    result[MC - 1] = '\0';
    return result;
}
//------------------------------Q1--------------------------------------

//------------------------------Q2--------------------------------------
char reverseChar(char ch) {
    char ans = ch;
    if ('a' <= ch && ch <= 'z' || 'A' <= ch && ch <= 'Z') {
        int temp = findMeTheValueOfTheChar(ch);
        temp = 26 - temp + 1;
        if ('A' <= ch && ch <= 'Z') {
            ans = ((char) temp + 64);
        } else {
            ans = ((char) temp + 96);
        }
    }
    return ans;
}


char *strrev(char *str) {
    char *ptr1, *ptr2;

    if (!str || !*str)
        return str;
    for (ptr1 = str, ptr2 = str + strlen(str) - 1; ptr2 > ptr1; ++ptr1, --ptr2) {
        *ptr1 ^= *ptr2;
        *ptr2 ^= *ptr1;
        *ptr1 ^= *ptr2;
    }
    return str;
}

char *AtbashSequences(char *word, char *txt) {
    char reverse1[strlen(word)];
    char reverse2[strlen(word)];
    char *result = calloc(TXT + 1, TXT);

    char saveString[strlen(txt)];
    int MC = 0;
    memset(reverse1, 0, sizeof(reverse1));
    memset(reverse2, 0, sizeof(reverse2));
    memset(result, 0, sizeof(result));
    memset(saveString, 0, sizeof(saveString));
    int i = 0;
    while (word[i] != '\0') {
        char saveHere = reverseChar(word[i]);
        strncat(reverse1, &saveHere, 1);
        strncat(reverse2, &saveHere, 1);
        i++;
    }
    strrev(reverse2);
    for (int i = 0; i < strlen(txt); i++) {
        if (txt[i] == '~') {
            break;
        }
        if (txt[i] == reverse1[0]) {
            strncat(saveString, &txt[i], 1);
            int k = i;
            for (int j = 1; j < strlen(reverse1); j++) {
                k++;
                if (txt[k] == '~') {
                    break;
                } else if ((txt[k] == reverse1[j]) ||
                           (('a' > txt[k] || txt[k] > 'z') && ('A' > txt[k] || txt[k] > 'Z'))) {
                    strncat(saveString, &txt[k], 1);
                    if (strlen(reverse1) - 1 == j) {
                        strncat(result, saveString, strlen(saveString));
                        MC += strlen(saveString);
                        memset(saveString, 0, sizeof(saveString));
                        strncat(result, "~", 1);
                        MC++;
                    }

                } else {
                    memset(saveString, 0, sizeof(saveString));
                    break;
                }
                if (('a' > txt[k] || txt[k] > 'z') && ('A' > txt[k] || txt[k] > 'Z')) {
                    j = j - 1;
                }
            }
        } else if (txt[i] == reverse2[0]) {
            strncat(saveString, &txt[i], 1);
            int k = i;
            for (int j = 1; j < strlen(reverse2); j++) {
                k++;
                if (txt[k] == '~') {
                    break;
                } else if ((txt[k] == reverse2[j]) ||
                           (('a' > txt[k] || txt[k] > 'z') && ('A' > txt[k] || txt[k] > 'Z'))) {
                    strncat(saveString, &txt[k], 1);
                    if (strlen(reverse2) - 1 == j) {
                        strncat(result, saveString, strlen(saveString));
                        MC += strlen(saveString);
                        memset(saveString, 0, sizeof(saveString));
                        strncat(result, "~", 1);
                        MC++;
                    }
                } else {
                    memset(saveString, 0, sizeof(saveString));
                    break;
                }
                if (('a' > txt[k] || txt[k] > 'z') && ('A' > txt[k] || txt[k] > 'Z')) {
                    j = j - 1;
                }
            }
        }
    }
    result[MC - 1] = '\0';
    return result;
}

//------------------------------Q2--------------------------------------

//------------------------------Q3--------------------------------------
char *AnagramSequences(char *word, char *txt) {
    int txtLen = strlen(txt);
    char *result = calloc(TXT + 1, TXT);
    char saveString[txtLen];
    int MC = 0;
    memset(result, 0, sizeof(result));
    memset(saveString, 0, sizeof(saveString));

    for (int i = 0; i < txtLen; i++) {
        if (txt[i] == '~') {
            break;
        }
        int j = 0;
        char wordCopy[strlen(word)];
        strcpy(wordCopy, word);
        int k = i;
        while (wordCopy[j] != '\0') {
            if (txt[k] == '~') {
                break;
            }
            if (txt[k] == wordCopy[j] || (txt[k] == ' ' && saveString[0] != 0)) {
                strncat(saveString, &txt[k], 1);
                if (txt[k] != ' ')
                    memmove(&wordCopy[j], &wordCopy[j + 1], strlen(wordCopy) - j);
                k++;
                j = 0;
            } else {
                j++;
            }
        }
        if (strlen(wordCopy) == 0) {
            strncat(result, saveString, strlen(saveString));
            strncat(result, "~", 1);
            MC += strlen(saveString) + 1;
        }
        memset(saveString, 0, sizeof(saveString));
    }
    result[MC - 1] = '\0';
    return result;
}

//------------------------------Q3--------------------------------------

int main() {

    char WORDinput[WORD];
    char copyWord[WORD];
    char TXTinput[TXT];
    char txt;
    gets(WORDinput);
    int j = 0;
    for (int i = 0; i < WORD; i++) {
        if (WORDinput[i] != ' ' && WORDinput[i] != '\t' && WORDinput[i] != '\n') {
            copyWord[j] = WORDinput[i];
            j++;
        } else {
            break;
        }
    }
    for (int i = 0; i < TXT; i++) {
        scanf("%c", &txt);
        if (txt != '~') {
            TXTinput[i] = txt;
        } else {
            TXTinput[i] = txt;
            break;
        }
    }
    printf("Gematria Sequences:");
    printf("%*c", 1, ' ');
    printf("%s\n", GematriaSequences(copyWord, TXTinput));
    printf("Atbash Sequences:");
    printf("%*c", 1, ' ');
    printf("%s\n", AtbashSequences(copyWord, TXTinput));
    printf("Anagram Sequences:");
    printf("%*c", 1, ' ');
    printf("%s", AnagramSequences(copyWord, TXTinput));

    return 0;
}