#include <stdio.h>
#include <string.h>
#define MAX_RULES 10
#define MAX_LEN 100

char grammar[MAX_RULES][MAX_LEN];
int numRules;

void parseString(char *str, int start, int end) {
    if (start > end) {
        printf("Valid string!\n");
        return;
    }

    for (int i = 0; i < numRules; i++) {
        int len = strlen(grammar[i]);
        if (strncmp(str + start, grammar[i], len) == 0) {
            parseString(str, start + len, end);
            return;
        }
    }

    printf("Invalid string!\n");
}

int main() {
    printf("Enter the number of grammar rules: ");
    scanf("%d", &numRules);

    printf("Enter the grammar rules (one per line):\n");
    for (int i = 0; i < numRules; i++) {
        scanf("%s", grammar[i]);
    }

    char inputString[MAX_LEN];
    printf("Enter the input string: ");
    scanf("%s", inputString);

    parseString(inputString, 0, strlen(inputString) - 1);

    return 0;
}
