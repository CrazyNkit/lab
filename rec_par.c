#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_RULES 100
#define MAX_RULE_LENGTH 100
#define MAX_INPUT_LENGTH 100

// Define a structure to hold a grammar rule
typedef struct {
    char nonTerminal;
    char production[MAX_RULE_LENGTH];
} Rule;

// Function to check if a character is a non-terminal
bool isNonTerminal(char c) {
    return c >= 'A' && c <= 'Z';
}

// Recursive descent parsing function with backtracking
bool parse(char* input, int* index, Rule* rules, int numRules, char startSymbol) {
    printf("Parsing: %c\n", startSymbol);
    int initialIndex = *index;
    int i, j;
    for (i = 0; i < numRules; i++) {
        if (rules[i].nonTerminal == startSymbol) {
            printf("Applying rule: %s\n", rules[i].production);
            int len = strlen(rules[i].production);
            bool success = true;
            for (j = 0; j < len; j++) {
                if (isNonTerminal(rules[i].production[j])) {
                    if (!parse(input, index, rules, numRules, rules[i].production[j])) {
                        success = false;
                        break;
                    }
                } else {
                    if (input[*index] == rules[i].production[j]) {
                        (*index)++;
                    } else {
                        success = false;
                        break;
                    }
                }
            }
            // If we successfully parsed the entire production, return true
            if (success) {
                return true;
            } else {
                // Backtrack
                *index = initialIndex;
            }
        }
    }
    return false;
}

int main() {
    Rule rules[MAX_RULES];
    int numRules = 0;
    
    printf("Enter grammar rules (Enter 'exit' to stop):\n");
    char inputRule[MAX_RULE_LENGTH];
    while (numRules < MAX_RULES) {
        printf("Rule %d: ", numRules + 1);
        scanf("%s", inputRule);
        if (strcmp(inputRule, "exit") == 0)
            break;
        rules[numRules].nonTerminal = inputRule[0];
        strcpy(rules[numRules].production, inputRule + 3);
        numRules++;
    }

    char input[MAX_INPUT_LENGTH];
    printf("\nEnter the input string: ");
    scanf("%s", input);

    char startSymbol;
    printf("Enter the start symbol: ");
    scanf(" %c", &startSymbol);

    int index = 0;
    bool result = parse(input, &index, rules, numRules, startSymbol);

    if (result && index == strlen(input)) {
        printf("String is accepted by the grammar.\n");
    } else {
        printf("String is not accepted by the grammar.\n");
    }

    return 0;
}
