
// The number of states in your table
#define NSTATES 14

// The starting state, at the beginning of each line
#define START 0

// The state to go to after a valid line
// All lines end with the newline character '\n'
#define ACCEPT 12

// The state to jump to as soon as a line is invalid
#define ERROR 13

#define LABEL 1

// Main content, accept a repetition of statements
#define BODY LABEL + 2 // 3

#define GO BODY + 2 // 4

#define DXY GO + 2 // 6

int table[NSTATES][256];

void fillTable()
{

    // Make all states lead to ERROR by default
    for (int i = 0; i < NSTATES; i++)
    {
        for (int c = 0; c < 256; c++)
        {
            table[i][c] = ERROR;
        }
    }

    { /* START */

        // Skip whitespace
        table[START][' '] = START;

        // If we reach a newline, and are not in the middle of a statement, accept
        table[START]['\n'] = ACCEPT;

        { /* START: LABEL */

            // Regex approx. `^(0-9)+: ((d(x|y)=-?(0-9)+)|go( go)*)+`
            for (char c = '0'; c <= '9'; c++)
            {
                table[START][c] = LABEL;
                table[LABEL][c] = LABEL;
            }
            table[LABEL][':'] = LABEL + 1;
            table[LABEL + 1][' '] = BODY;
        }

        { /* START: STATEMENTS */

            table[START]['g'] = GO;
            table[START]['d'] = DXY;
        }
    }

    { /* BODY */

        table[BODY]['g'] = GO;
        table[BODY]['d'] = DXY;

        { /* BODY: GO */

            // Accept the statement "go"
            table[GO]['o'] = GO + 1;
            table[GO + 1]['\n'] = ACCEPT;

            // Accept repeated "go"s with spaces e.g "go go go" but not "gogogo"
            table[GO + 1][' '] = BODY;
        }

        { /* BODY: DXY */
            // Accept "d(x|y)=<number>" with leading zeros (007)
            // Regex approximately d(x|y)=-?(0-9)+
            table[DXY]['x'] = DXY + 1;
            table[DXY]['y'] = DXY + 1;
            table[DXY + 1]['='] = DXY + 2;
            table[DXY + 2]['-'] = DXY + 3;
            for (char c = '0'; c <= '9'; c++)
            {
                table[DXY + 2][c] = DXY + 3;
                table[DXY + 3][c] = DXY + 3;
            }
            table[DXY + 3]['\n'] = ACCEPT;
            // Loop
            table[DXY + 3][' '] = BODY;
        }
    }
}
