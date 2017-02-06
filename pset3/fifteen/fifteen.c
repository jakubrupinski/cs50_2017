/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// board with sorted values (for win check)
int sorted_board[DIM_MAX][DIM_MAX];

// empty space location
int empty_column;
int empty_row;

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    // calculate number of tiles to fill, and leave one space blank (and start counting from num of tiles)
    int num_of_tiles = (d * d) - 1,
        sorted_tile = 1;
    
    // fill the tiles top left to bottom right
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            // tiles should be in reverse order and leave last space empty
            board[i][j] = num_of_tiles;
            num_of_tiles--;
            // insert sorted values into sorted_board
            sorted_board[i][j] = sorted_tile;
            sorted_tile++;
            // printf("%2i ", sorted_board[i][j]);
        }
        // printf("\n");
    }
    
    // if number of tiles is uneven - swap 1 and 2 to make puzzle solvable
    if (d % 2== 0)
    {
        board[d-1][d-2] = 2;
        board[d-1][d-3] = 1;
    }
    // initialize empty column and empty row to last place on board
    empty_column = d-1;
    empty_row = d-1;
    
    // make last tile zero on sorted board
    sorted_board[d-1][d-1] = 0;
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for (int i = 0; i < d; i++)
    {
        // print horizontal row
        for (int j = 0; j < d; j++)
        {
            // if current tile is empty (empty row and column) - draw underscore
            if (i == empty_column && j == empty_row)
            {
                printf(" _ ");
            }
            else
            {
                printf("%2i ", board[i][j]);
            }
        }
        // create a vertical newline
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // find index of tile and check if it borders with empty space
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            // if tile number found on board and it borders with empty space - swap it
            if (tile == board[i][j])
            {
                /** if tile column is column with emptyspace and borders with emptyspace row
                 * or if tile row is row with emptyspace and borders with emptyspace column
                 */
                if ( (i == empty_column && (j == empty_row - 1 || j == empty_row + 1)) || 
                        (j == empty_row && (i == empty_column - 1 || i == empty_column + 1)) )
                {
                    board[empty_column][empty_row] = tile;
                    board[i][j] = 0;
                    // update empty tile location
                    empty_column = i;
                    empty_row = j;
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    bool is_sorted = true;
    // check if current board is sorted by comparing it to sorted_board, if it is - win
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            // printf("b%2i s%2i", board[i][j], sorted_board[i][j]);
            // if current board tile is different than in sorted_board 
            if (board[i][j] != sorted_board[i][j])
            {
                is_sorted = false;
            }
        }
        printf("\n");
    }
    
    if (is_sorted)
    {
        return true;
    }
    else
    {
        return false;
    }
}
