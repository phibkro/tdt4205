
// The number of states in your table
#define NSTATES 14

// The starting state, at the beginning of each line
#define START 0

// The state to go to after a valid line
// All lines end with the newline character '\n'
#define ACCEPT 12

// The state to jump to as soon as a line is invalid
#define ERROR 13

int table[NSTATES][256];

void fillTable() {

    // Make all states lead to ERROR by default
    for (int i = 0; i < NSTATES; i++) {
        for (int c = 0; c < 256; c++) {
            table[i][c] = ERROR;
        }
    }

    // Skip whitespace
    table[START][' '] = START;

    // If we reach a newline, and are not in the middle of a statement, accept
    table[START]['\n'] = ACCEPT;

    // Accept the statement "go"
    table[START]['g'] = 1;
    table[1]['o'] = 2;
    table[2]['\n'] = ACCEPT;

    // Accept repeated "go"s with spaces e.g "go go go" but not "gogogo"
    table[2][' '] = START;

    // Accept "d(x|y)=<number>" with leading zeros (007)
    // Regex approximately d(x|y)=-?(0-9)+
    table[START]['d'] = 3;
    table[3]['x'] = 4;
    table[3]['y'] = 4;
    table[4]['='] = 5;
    table[5]['-'] = 6;
    for (char c = '0'; c <= '9'; c++)
    {
        table[5][c] = 6;
        table[6][c] = 6;
    }
    table[6]['\n'] = ACCEPT;
    // Loop
    table[6][' '] = START;
    

}
