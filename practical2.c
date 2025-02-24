#include <stdio.h>
#include <string.h>

#define MAX_STATES 10
#define MAX_SYMBOLS 10

// Function prototypes
int findSymbolIndex(char symbols[], int num_symbols, char symbol);
int isAcceptingState(int state, int accept_states[], int num_accept_states);
int validateString(char *input, char symbols[], int num_symbols, int transition[][MAX_SYMBOLS], int start_state, int accept_states[], int num_accept_states);

int main() {
    int num_symbols, num_states, start_state, num_accept_states;
    int accept_states[MAX_STATES];
    int transition[MAX_STATES][MAX_SYMBOLS];
    char symbols[MAX_SYMBOLS];
    char input[100];

    // Input the number of symbols and the symbols themselves
    printf("Number of input symbols: ");
    scanf("%d", &num_symbols);

    printf("Input symbols: ");
    for (int i = 0; i < num_symbols; i++) {
        scanf(" %c", &symbols[i]);
    }

    // Input the number of states and the start state
    printf("Enter number of states: ");
    scanf("%d", &num_states);

    printf("Initial state: ");
    scanf("%d", &start_state);

    // Input the accepting states
    printf("Number of accepting states: ");
    scanf("%d", &num_accept_states);

    printf("Accepting states: ");
    for (int i = 0; i < num_accept_states; i++) {
        scanf("%d", &accept_states[i]);
    }

    // Initialize the transition table
    for (int i = 0; i < num_states; i++) {
        for (int j = 0; j < num_symbols; j++) {
            transition[i][j] = -1; // Default invalid transition
        }
    }

    // Fill the transition table
    printf("Transition table:\n");
    for (int i = 0; i < num_states; i++) {
        for (int j = 0; j < num_symbols; j++) {
            printf("State %d to %c -> ", i + 1, symbols[j]);
            scanf("%d", &transition[i][j]);
        }
    }

    // Input string to validate
    printf("Input string: ");
    scanf("%s", input);

    // Validate the string
    if (validateString(input, symbols, num_symbols, transition, start_state, accept_states, num_accept_states)) {
        printf("Valid string\n");
    } else {
        printf("Invalid string\n");
    }

    return 0;
}

// Function to find the index of a symbol in the symbols array
int findSymbolIndex(char symbols[], int num_symbols, char symbol) {
    for (int i = 0; i < num_symbols; i++) {
        if (symbols[i] == symbol) {
            return i;
        }
    }
    return -1; // Symbol not found
}

// Function to check if a state is an accepting state
int isAcceptingState(int state, int accept_states[], int num_accept_states) {
    for (int i = 0; i < num_accept_states; i++) {
        if (state == accept_states[i]) {
            return 1;
        }
    }
    return 0;
}

// Function to validate a string against the finite automaton
int validateString(char *input, char symbols[], int num_symbols, int transition[][MAX_SYMBOLS], int start_state, int accept_states[], int num_accept_states) {
    int current_state = start_state;

    for (int i = 0; i < strlen(input); i++) {
        int symbol_index = findSymbolIndex(symbols, num_symbols, input[i]);
        if (symbol_index == -1) {
            return 0; // Invalid symbol
        }
        current_state = transition[current_state - 1][symbol_index]; // Transition to the next state
        if (current_state == -1) {
            return 0; // Invalid transition
        }
    }

    return isAcceptingState(current_state, accept_states, num_accept_states);
}
