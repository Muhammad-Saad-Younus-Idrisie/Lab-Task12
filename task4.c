#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;

    printf("Enter the number of movie categories: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of categories.\n");
        return 1;
    }

    int *ratings = (int *)calloc(n, sizeof(int));
    if (ratings == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter rating count for category %d: ", i);
        scanf("%d", &ratings[i]);
    }

    int total = 0, highest = 0;
    for (int i = 0; i < n; i++) {
        total += ratings[i];
        if (ratings[i] > ratings[highest])
            highest = i;
    }
    printf("\nTotal ratings across all categories: %d\n", total);
    printf("Average ratings per category: %.2f\n", (float)total / n);
    printf("Category with highest rating count: %d (count = %d)\n", highest, ratings[highest]);

    int idx, newCount;
    printf("\nEnter category index to update (0 to %d): ", n - 1);
    scanf("%d", &idx);
    if (idx < 0 || idx >= n) {
        printf("Invalid category index.\n");
    } else {
        printf("Enter new rating count for category %d: ", idx);
        scanf("%d", &newCount);
        ratings[idx] = newCount;

        printf("\nUpdated rating counts:\n");
        total = 0;
        highest = 0;
        for (int i = 0; i < n; i++) {
            printf("Category %d: %d\n", i, ratings[i]);
            total += ratings[i];
            if (ratings[i] > ratings[highest])
                highest = i;
        }
        printf("Total ratings: %d\n", total);
        printf("Average ratings per category: %.2f\n", (float)total / n);
        printf("Category with highest rating count: %d\n", highest);
    }

    free(ratings);
    ratings = NULL;
    return 0;
}
