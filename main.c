#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define TXT 1024
#define WORD 30

//------------------------------Q1--------------------------------------
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

char *GematriaSequences(char *word, char *txt) {
    int sumOfWord = findMeTheValueOfTheString(word);
    int txtLen = strlen(txt);
    char *result = calloc(1025, 1024);
    char saveString[txtLen];
    int MC = 0;
    memset(result, 0, sizeof(result));
    memset(saveString, 0, sizeof(saveString));
    //cleanUpString(result);
    //cleanUpString(saveString);
    int count = 0;                     //012345678911234567892123456
    for (int i = 0; i < txtLen; i++) { //a-bc,dbca-zwxyzabzyxw0dcba~
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

                //cleanUpString(saveString);
                memset(saveString, 0, sizeof(saveString));
                count = 0;
                strncat(result, "~", 1);
                MC++;
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

char *AtbashSequences(char *word, char *txt) {
    char reverse1[strlen(word)];
    char reverse2[strlen(word)];
    char *result = calloc(1025, 1024);

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
    outerloop:
    for (int i = 0; i < strlen(txt); i++) {
        if (txt[i] == '~') {
            i = strlen(txt) - 1;
            break;
        }
        if (txt[i] == reverse1[0]) {
            strncat(saveString, &txt[i], 1);
            int k = i;
            for (int j = 1; j < strlen(reverse1); j++) {
                k++;
                if(txt[k]=='~'){
                    break;
                }
                else if ((txt[k] == reverse1[j]) || (('a' > txt[k] || txt[k] > 'z') && ('A' > txt[k] || txt[k] > 'Z'))) {
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
            strncat(saveString, &txt[i], 1);            //xyz,   a0w xyzw
            int k = i;
            for (int j = 1; j < strlen(reverse2); j++) {
                k++;
                if(txt[k]=='~'){
                    break;
                }
                else if ((txt[k] == reverse2[j]) || (('a' > txt[k] || txt[k] > 'z') && ('A' > txt[k] || txt[k] > 'Z'))) {
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

int main() {
//    printf("%d\n", findMeTheValueOfTheChar('a'));
//    printf("%d", findMeTheValueOfTheString("aaaaaa a, - % 0 a"));
// "a-bc,dbca-zwxyzabzyxw0dcba~"
    char word[] = "abcd";
    char txt[] = "a-bc,dbca-zwxyzabzyxw0dcba~";

    char word1[] = "fish";
    char txt1[] = "One, two, three, four, five,\n"
                  "Once I caught a fish alive,\n"
                  "Six, seven, eight, nine, ten,\n"
                  "Then I let go again.~";

    char word2[] = "sea";
    char txt2[] = "A sailor went to sea, sea, sea\n"
                  "To see what he could see, see, see\n"
                  "But all that he could see, see, see\n"
                  "Was the bottom of the deep blue sea, sea, sea!~";

    char word3[] = "sheep";
    char txt3[] = "Baa, baa black sheep\n"
                  "Have you any wool\n"
                  "Yes sir, yes sir\n"
                  "Three bags full.\n"
                  "~\n"
                  "One for my master\n"
                  "And one for my dame\n"
                  "And one for the little boy\n"
                  "Who lives down the lane";

    char word4[] = "Head";
    char txt4[] = "Head, shoulders, knees and toes,\n"
                  "Knees and toes.\n"
                  "Head, shoulders, knees and toes,\n"
                  "Knees and toes.\n"
                  "And eyes, and ears, and mouth, and nose.\n"
                  "Head, shoulders, knees and toes,\n"
                  "Knees and toes.~";

    char word5[] = "abcd";
    char txt5[] = "skldjahd312-z0yxw      -\n"
                  "1=23 w1293 .. 21# xyzz wxy~z";

//------------------------------Q1--------------------------------------
//    char a[1025];
//    memset(a, 0, sizeof(a));
//    strcpy(a, GematriaSequences(word, txt));
//    printf("%s", a);
//------------------------------Q1--------------------------------------
    char a2[1025];
    memset(a2, 0, sizeof(a2));
    strcpy(a2, AtbashSequences(word5, txt5));
    printf("%s", a2);
    return 0;
}