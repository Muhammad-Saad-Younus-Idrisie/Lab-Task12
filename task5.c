#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getCategory(char c) {
    if (c >= 'A' && c <= 'Z') return 1;
    if (c >= 'a' && c <= 'z') return 2;
    if (c >= '0' && c <= '9') return 3;
    return 4;
}

float similarity(const char *pattern, const char *attempt) {
    int lp = (int)strlen(pattern), la = (int)strlen(attempt);
    int maxLen = lp > la ? lp : la;
    int minLen = lp < la ? lp : la;
    if (maxLen == 0) return 100.0f;

    int match = 0;
    for (int i = 0; i < minLen; i++)
        if (getCategory(pattern[i]) == getCategory(attempt[i]))
            match++;
    return (float)match / maxLen * 100.0f;
}

int main(void) {
    int n;
    char temp[256];

    printf("Enter the number of participants: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number.\n");
        return 1;
    }

    char **passwords = (char **)malloc(n * sizeof(char *));
    float *scores = (float *)malloc(n * sizeof(float));
    if (passwords == NULL || scores == NULL) {
        printf("Memory allocation failed!\n");
        free(passwords);
        free(scores);
        return 1;
    }

    printf("Enter the password pattern (e.g. Aa#91!): ");
    scanf("%255s", temp);
    char *pattern = (char *)malloc(strlen(temp) + 1);
    if (pattern == NULL) {
        printf("Memory allocation failed!\n");
        free(passwords);
        free(scores);
        return 1;
    }
    strcpy(pattern, temp);

    int best = 0;
    for (int i = 0; i < n; i++) {
        printf("Enter password attempt of participant %d: ", i + 1);
        scanf("%255s", temp);
        passwords[i] = (char *)malloc(strlen(temp) + 1);
        if (passwords[i] == NULL) {
            printf("Memory allocation failed!\n");
            for (int j = 0; j < i; j++) free(passwords[j]);
            free(passwords);
            free(scores);
            free(pattern);
            return 1;
        }
        strcpy(passwords[i], temp);

        scores[i] = similarity(pattern, passwords[i]);
        if (scores[i] > scores[best])
            best = i;
    }

    printf("\nPattern: %s\n", pattern);
    printf("\n%-5s %-25s %s\n", "No.", "Password", "Similarity");
    for (int i = 0; i < n; i++)
        printf("%-5d %-25s %.2f%%\n", i + 1, passwords[i], scores[i]);

    printf("\nHighest similarity: participant %d, password \"%s\" (%.2f%%)\n",
           best + 1, passwords[best], scores[best]);

    for (int i = 0; i < n; i++) {
        free(passwords[i]);
        passwords[i] = NULL;
    }
    free(passwords);
    free(scores);
    free(pattern);
    passwords = NULL; scores = NULL; pattern = NULL;
    return 0;
}
