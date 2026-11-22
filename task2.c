#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *readLine(void) {
    size_t cap = 16, len = 0;
    char *buf = (char *)malloc(cap);
    if (buf == NULL) return NULL;

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (len + 1 >= cap) {
            cap *= 2;
            char *tmp = (char *)realloc(buf, cap);
            if (tmp == NULL) { free(buf); return NULL; }
            buf = tmp;
        }
        buf[len++] = (char)ch;
    }
    buf[len] = '\0';

    char *exact = (char *)realloc(buf, len + 1);
    return exact ? exact : buf;
}

int main(void) {
    int n;

    printf("Enter the number of feedback entries: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number.\n");
        return 1;
    }
    while (getchar() != '\n');

    char **feedback = (char **)malloc(n * sizeof(char *));
    if (feedback == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter feedback %d: ", i + 1);
        feedback[i] = readLine();
        if (feedback[i] == NULL) {
            printf("Memory allocation failed!\n");
            for (int j = 0; j < i; j++) free(feedback[j]);
            free(feedback);
            return 1;
        }
    }

    int totalChars = 0, longestLen = 0;
    char *longest = feedback[0];

    for (char **p = feedback; p < feedback + n; p++) {
        int len = 0;
        for (char *c = *p; *c != '\0'; c++)
            len++;
        totalChars += len;
        if (len > longestLen) {
            longestLen = len;
            longest = *p;
        }
    }

    printf("\n--- All Feedback Entries ---\n");
    for (int i = 0; i < n; i++)
        printf("%d. %s\n", i + 1, feedback[i]);

    printf("\nTotal characters across all feedback: %d\n", totalChars);
    printf("Longest feedback (%d characters): %s\n", longestLen, longest);

    for (int i = 0; i < n; i++) {
        free(feedback[i]);
        feedback[i] = NULL;
    }
    free(feedback);
    feedback = NULL;
    return 0;
}
