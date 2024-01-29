#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h> // For INT_MAX

void generateUniqueRandomNumbers(int n, int start, int end) {
	char *resultString;

    if (end - start + 1 < n) {
        printf("Error: Not enough unique numbers in the given range to satisfy the request.\n");
        return;
    }

    srand(time(NULL));
    int numbers[n];
	resultString = malloc()
    resultString[0] = '\0';

    for (int i = 0; i < n; i++) {
        int unique = 0;
        int randNum;

        while (!unique) {
            unique = 1;
            randNum = start + rand() % (end - start + 1); // Generate a random number in the given range

            for (int j = 0; j < i; j++) {
                if (numbers[j] == randNum) {
                    unique = 0;
                    break;
                }
            }
        }

        numbers[i] = randNum;
        sprintf(numberStr, "%d ", randNum);
        strcat(resultString, numberStr);
    }

    // Remove the last space
    size_t len = strlen(resultString);
    if (len > 0) {
        resultString[len - 1] = '\0';
    }
}