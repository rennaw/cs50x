/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements the Game of Fifteen (generalized to d x d).
 *
 * Usage: ./fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [MIN,MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */

#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// board's minimal dimension
#define MIN 3

// board's maximal dimension
#define MAX 9

// board, whereby board[i][j] represents row i and column j
int board[MAX][MAX];

// board's dimension
int d;

// blank tile location, in two variables
int blank_row, blank_col;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
void slide(int tile, int tile_row, int tile_col);
bool move(int tile);
bool won(void);
void save(void);

int main(int argc, string argv[])
{
    // greet player
    greet();

    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < MIN || d > MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            MIN, MIN, MAX, MAX);
        return 2;
    }

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // saves the current state of the board (for testing)
        save();

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep for animation's sake
        usleep(500000);
    }

    // that's all folks
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
    printf("GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1,
 * (i.e., fills board with values but does not actually print them),
 * whereby board[i][j] represents row i and column j.
 */
void init(void)
{
    // num_tiles - count == d*d - 1, continues to 0 (blank)
    int count = 0;
    int num_tiles = d * d - 1;
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            board[i][j] = num_tiles - count;
            count++;
        }
    }
    // swaps values of last two tiles if num_tiles is odd
    if (d % 2 == 0)
    {
        board[d - 1][d - 2] = 2;
        board[d - 1][d - 3] = 1;
    }
    // remembers the blank tile at lower right hand corner
    blank_row = d - 1;
    blank_col = d - 1;
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // loop through board's rows and cols
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            // blank tile is an underscore
            if (board[i][j] == 0)
            {
                printf("   ");
            }
            else
            {
                printf("%2d ", board[i][j]);
            }
        }
        printf("\n");
    }
}
/**
 * "Slides" user's tile into the empty slot
 */
void slide(int tile, int tile_row, int tile_col)
{
    // no need for tmp for this, since blank is always 0
    board[blank_row][blank_col] = tile;
    board[tile_row][tile_col] = 0;

    // now to set the blank's now position variables
    blank_row = tile_row;
    blank_col = tile_col;
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false.
 */
bool move(int tile)
{
    // linear search for tile, record row & col position
    // if tile is not found, return false (with -1 as flag)
    int tile_row = -1;
    int tile_col = -1;
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == tile)
            {
                tile_row = i;
                tile_col = j;
            }
        }
    }
    if (tile_row == -1 || tile_col == -1)
    {
        return false;
    }

    /* The logic in this next part may be a bit dense, but
     * it works on the comparison of the four variables:
     * the row and col of the blank tile, and the row and
     * col of the user's tile.
     *
     * If one dimention is the same, and the other dimention
     * is off by one, then the tiles are adjacent. Otherwise,
     * they are not adjacent.
     */

    // checks if either the row or the col is the same
    if (tile_row == blank_row || tile_col == blank_col)
    {
        // this will evaluate to false if the tiles are in the same row
        if (tile_row == (blank_row - 1) || tile_row == (blank_row + 1))
        {
            // if tile is in the same col and one-off row from blank
            slide(tile, tile_row, tile_col);
            return true;
        }
            // this will evalute to false if the tiles are in the same col
        else if (tile_col == (blank_col - 1) || tile_col == (blank_col + 1))
        {
            // if tile is in the same row and one-off col from blank
            slide(tile, tile_row, tile_col);
            return true;
        }
    }
    // if the tile is not in the same row or the same col
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration),
 * else false.
 */
bool won(void)
{
    // checks first to see if blank tile is in the lower right corner
    // because this configuration is less probable
    if (board[d - 1][d - 1] != 0)
    {
        return false;
    }
    // check to see if the tiles are in ascending order
    // from 1 to the number of tiles, return false if not
    int count = 0;
    int num_tiles = d * d - 1;

    // loop through board with our old friends i and j
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            count++;
            // if there are still tiles left to count, AND
            // the current tile is NOT equal, then test fails
            if (count <= num_tiles && board[i][j] != count)
            {
                return false;
            }
        }
    }
    // if the board does not fail the test, then it is in winning configuration
    return true;
}

/**
 * Saves the current state of the board to disk (for testing).
 */
void save(void)
{
    // log
    const string log = "log.txt";

    // delete existing log, if any, before first save
    static bool saved = false;
    if (!saved)
    {
        unlink(log);
        saved = true;
    }

    // open log
    FILE* p = fopen(log, "a");
    if (p == NULL)
    {
        return;
    }

    // log board
    fprintf(p, "{");
    for (int i = 0; i < d; i++)
    {
        fprintf(p, "{");
        for (int j = 0; j < d; j++)
        {
            fprintf(p, "%i", board[i][j]);
            if (j < d - 1)
            {
                fprintf(p, ",");
            }
        }
        fprintf(p, "}");
        if (i < d - 1)
        {
            fprintf(p, ",");
        }
    }
    fprintf(p, "}\n");

    // close log
    fclose(p);
}
