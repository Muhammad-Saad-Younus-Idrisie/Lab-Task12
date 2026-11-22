#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int containsDigit(char *str) {
    while (*str != '\0') {
        if (*str >= '0' && *str <= '9')
            return 1;
        str++;
    }
    return 0;
}

int main(void) {
    int n;

    printf("Enter the number of usernames: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number.\n");
        return 1;
    }

    char **users = (char **)malloc(n * sizeof(char *));
    if (users == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    char temp[256];
    for (int i = 0; i < n; i++) {
        printf("Enter username %d: ", i + 1);
        scanf("%255s", temp);
        users[i] = (char *)malloc(strlen(temp) + 1);
        if (users[i] == NULL) {
            printf("Memory allocation failed!\n");
            for (int j = 0; j < i; j++) free(users[j]);
            free(users);
            return 1;
        }
        strcpy(users[i], temp);
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        if (containsDigit(users[i])) {
            free(users[i]);
        } else {
            users[count++] = users[i];
        }
    }

    if (count > 0) {
        char **tmp = (char **)realloc(users, count * sizeof(char *));
        if (tmp != NULL) users = tmp;
    }

    printf("\nValid usernames (alphabetic only):\n");
    if (count == 0) {
        printf("None.\n");
    } else {
        for (int i = 0; i < count; i++)
            printf("%d. %s\n", i + 1, users[i]);
    }

    for (int i = 0; i < count; i++)
        free(users[i]);
    free(users);
    users = NULL;
    return 0;
}
