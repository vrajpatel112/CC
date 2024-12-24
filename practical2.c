#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 100
#define MAX_SYMBOLS 100

typedef struct {
    int current_state;
    char input_symbol;
    int next_state;
} Transition;

typedef struct {
    int states[MAX_STATES];
    int num_states;
    char input_symbols[MAX_SYMBOLS];
    int num_symbols;
    int initial_state;
    int accepting_states[MAX_STATES];
    int num_accepting_states;
    Transition transitions[MAX_STATES * MAX_SYMBOLS];
    int num_transitions;
} FiniteAutomaton;

void initialize_fa(FiniteAutomaton *fa) {
    fa->num_states = 0;
    fa->num_symbols = 0;
    fa->initial_state = -1;
    fa->num_accepting_states = 0;
    fa->num_transitions = 0;
}

void add_transition(FiniteAutomaton *fa, int current_state, char input_symbol, int next_state) {
    fa->transitions[fa->num_transitions].current_state = current_state;
    fa->transitions[fa->num_transitions].input_symbol = input_symbol;
    fa->transitions[fa->num_transitions].next_state = next_state;
    fa->num_transitions++;
}

int find_next_state(FiniteAutomaton *fa, int current_state, char input_symbol) {
    for (int i = 0; i < fa->num_transitions; i++) {
        if (fa->transitions[i].current_state == current_state && fa->transitions[i].input_symbol == input_symbol) {
            return fa->transitions[i].next_state;
        }
    }
    return -1; // Invalid transition
}

int is_accepting_state(FiniteAutomaton *fa, int state) {
    for (int i = 0; i < fa->num_accepting_states; i++) {
        if (fa->accepting_states[i] == state) {
            return 1;
        }
    }
    return 0;
}

void validate_string(FiniteAutomaton *fa, char *input_string) {
    int current_state = fa->initial_state;

    for (int i = 0; i < strlen(input_string); i++) {
        char symbol = input_string[i];
        current_state = find_next_state(fa, current_state, symbol);
        if (current_state == -1) {
            printf("Invalid String\n");
            return;
        }
    }

    if (is_accepting_state(fa, current_state)) {
        printf("Valid String\n");
    } else {
        printf("Invalid String\n");
    }
}

void test_cases() {
    // Test case 1: String over 0 and 1 where every 0 is immediately followed by 11
    FiniteAutomaton fa1;
    initialize_fa(&fa1);
    fa1.num_symbols = 2;
    fa1.input_symbols[0] = '0';
    fa1.input_symbols[1] = '1';
    fa1.num_states = 4;
    fa1.initial_state = 1;
    fa1.num_accepting_states = 1;
    fa1.accepting_states[0] = 1;

    add_transition(&fa1, 1, '0', 2);
    add_transition(&fa1, 1, '1', 1);
    add_transition(&fa1, 2, '1', 3);
    add_transition(&fa1, 3, '1', 1);

    printf("Test case 1:\n");
    validate_string(&fa1, "011"); // Valid
    validate_string(&fa1, "0110"); // Invalid
    validate_string(&fa1, "11011"); // Valid

    // Test case 2: String over a, b, c that starts and ends with the same letter
    FiniteAutomaton fa2;
    initialize_fa(&fa2);
    fa2.num_symbols = 3;
    fa2.input_symbols[0] = 'a';
    fa2.input_symbols[1] = 'b';
    fa2.input_symbols[2] = 'c';
    fa2.num_states = 4;
    fa2.initial_state = 1;
    fa2.num_accepting_states = 3;
    fa2.accepting_states[0] = 2;
    fa2.accepting_states[1] = 3;
    fa2.accepting_states[2] = 4;

    add_transition(&fa2, 1, 'a', 2);
    add_transition(&fa2, 1, 'b', 3);
    add_transition(&fa2, 1, 'c', 4);
    add_transition(&fa2, 2, 'a', 2);
    add_transition(&fa2, 2, 'b', 2);
    add_transition(&fa2, 2, 'c', 2);
    add_transition(&fa2, 2, 'a', 2);
    add_transition(&fa2, 3, 'a', 3);
    add_transition(&fa2, 3, 'b', 3);
    add_transition(&fa2, 3, 'c', 3);
    add_transition(&fa2, 3, 'b', 3);
    add_transition(&fa2, 4, 'a', 4);
    add_transition(&fa2, 4, 'b', 4);
    add_transition(&fa2, 4, 'c', 4);
    add_transition(&fa2, 4, 'c', 4);

    printf("Test case 2:\n");
    validate_string(&fa2, "abca"); // Valid
    validate_string(&fa2, "abcb"); // Valid
    validate_string(&fa2, "abcc"); // Valid

    // Test case 3: String over lower-case alphabet and digits, starts with alphabet only
    FiniteAutomaton fa3;
    initialize_fa(&fa3);
    fa3.num_symbols = 36; // 26 letters + 10 digits
    for (int i = 0; i < 26; i++) {
        fa3.input_symbols[i] = 'a' + i;
    }
    for (int i = 0; i < 10; i++) {
        fa3.input_symbols[26 + i] = '0' + i;
    }
    fa3.num_states = 2;
    fa3.initial_state = 1;
    fa3.num_accepting_states = 1;
    fa3.accepting_states[0] = 1;

    for (int i = 0; i < 26; i++) {
        add_transition(&fa3, 1, fa3.input_symbols[i], 1);
    }
    for (int i = 0; i < 10; i++) {
        add_transition(&fa3, 1, fa3.input_symbols[26 + i], 1);
    }

    printf("Test case 3:\n");
    validate_string(&fa3, "a123"); // Valid
    validate_string(&fa3, "1abc"); // Invalid
    validate_string(&fa3, "z9x");  // Valid
}

int main() {
    test_cases();
    return 0;
}
