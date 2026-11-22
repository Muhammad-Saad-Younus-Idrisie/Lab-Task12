#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;

    printf("Enter the number of book categories: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of categories.\n");
        return 1;
    }

    int *stock = (int *)malloc(n * sizeof(int));
    if (stock == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter stock for category %d: ", i);
        scanf("%d", &stock[i]);
    }

    int total = 0, lowest = 0;
    for (int i = 0; i < n; i++) {
        total += stock[i];
        if (stock[i] < stock[lowest])
            lowest = i;
    }
    printf("\nTotal stock: %d\n", total);
    printf("Average stock per category: %.2f\n", (float)total / n);
    printf("Category with lowest stock: %d (stock = %d)\n", lowest, stock[lowest]);

    int idx, newStock;
    printf("\nEnter category index to update (0 to %d): ", n - 1);
    scanf("%d", &idx);
    if (idx < 0 || idx >= n) {
        printf("Invalid category index.\n");
    } else {
        printf("Enter new stock for category %d: ", idx);
        scanf("%d", &newStock);
        stock[idx] = newStock;

        printf("\nUpdated stock levels:\n");
        total = 0;
        lowest = 0;
        for (int i = 0; i < n; i++) {
            printf("Category %d: %d\n", i, stock[i]);
            total += stock[i];
            if (stock[i] < stock[lowest])
                lowest = i;
        }
        printf("Total stock: %d\n", total);
        printf("Average stock per category: %.2f\n", (float)total / n);
        printf("Category with lowest stock: %d\n", lowest);
    }

    free(stock);
    stock = NULL;
    return 0;
}
