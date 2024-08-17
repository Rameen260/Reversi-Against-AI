#include <stdio.h>
#include <stdbool.h>
#include <string.h>
void makeBoard(char board[][26], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            board[i][j] = 'U';
        }
    }
    board[(n - 1) / 2][(n - 1) / 2] = 'W';
    board[(n - 1) / 2][((n - 1) / 2) + 1] = 'B';
    board[(n / 2)][(n - 1) / 2] = 'B';
    board[(n / 2)][((n - 1) / 2) + 1] = 'W';
}
void printBoard(char board[][26], int n)
{
    printf("  ");
    for (int i = 0; i < n; i++)
        printf("%c", 97 + i);
    for (int i = 0; i < n; i++)
    {
        printf("\n%c ", 97 + i);
        for (int j = 0; j < n; j++)
        {
            printf("%c", board[i][j]);
        }
    }
    printf("\n");
}
bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol)
{
    int dRow = deltaRow, dCol = deltaCol;
    if (((row + dRow) >= n || (row + dRow) < 0) || ((col + dCol) >= n || (col + dCol) < 0)) // next slot out of bounds
    {
        return false;
    }
    else if ((board[row + dRow][col + dCol] != colour) && (board[row + dRow][col + dCol] != 'U') && (board[row][col] == 'U')) // next slot is valid
    {
        for (int z = 1; z <= n; z++)
        {
            dRow = deltaRow * z, dCol = deltaCol * z;
            if (((row + dRow) >= n || (row + dRow) < 0) || ((col + dCol) >= n || (col + dCol) < 0)) // Out of bounds
                return false;
            else if (board[row + dRow][col + dCol] == 'U') // Cant be Empty spot in between, all in between spots must be opposite colour
                return false;
            else if (board[row + dRow][col + dCol] == colour) // Valid Move
                return true;
        }
    }
    return false;
}
void fliptiles(char board[][26], int n, char playC, int row, int col)
{
    int direction[8][2] = {{1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}};
    for (int k = 0; k < 8; k++)
    {
        int dRow = direction[k][0], dCol = direction[k][1];
        if (checkLegalInDirection(board, n, row, col, playC, dRow, dCol)) // If chosen spot is valid
        {
            int multiplier = 1;
            while (board[(row) + dRow * multiplier][(col) + dCol * multiplier] != playC)
            {

                board[(row) + dRow * multiplier][(col) + dCol * multiplier] = playC;
                multiplier++;
            }
        }
    }
}
bool positionInBounds(int n, int row, int col)
{
    if ((row >= n || row < 0) || (col >= n || col < 0))
        return false;
    return true;
}
bool available(char board[][26], int n, int row, int col, char colour) // checks if a spot is an available spot
{
    int direction[8][2] = {{1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}};
    for (int k = 0; k < 8; k++)
    {
        if (checkLegalInDirection(board, n, row, col, colour, direction[k][0], direction[k][1]))
            return true;
    }
    return false;
}
bool availableChecker(char board[][26], int n, char colour)
{
    for (int i = 0; i < n; i++) // finds the best spot for the computer
    {
        for (int j = 0; j < n; j++)
        {
            if (available(board, n, i, j, colour))
                return true;
        }
    }
    return false;
}
char winnerDetect(char board[][26], int n, int playC, int compC)
{
    if ((availableChecker(board, n, 'W')) || (availableChecker(board, n, 'B')))
        return 'C';
    int numPlayer = 0, numComp = 0;
    for (int i = 0; i < n; i++) // finds the best spot for the computer
    {
        for (int j = 0; j < n; j++)
        {
            if (board[i][j] == playC)
                numPlayer++;
            else if (board[i][j] == compC)
                numComp++;
        }
    }
    if (numPlayer > numComp)
        return playC;
    else if (numPlayer < numComp)
        return compC;

    return 'D';
}
int computer(char board[][26], int n, char compC, int i, int j) // AKA SCORE
{
    int score = 0, direction[8][2] = {{1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}};
    for (int k = 0; k < 8; k++)
    {
        int dRow = direction[k][0], dCol = direction[k][1];
        if (checkLegalInDirection(board, n, i, j, compC, direction[k][0], direction[k][1]))
        {
            //  printf("\n%i %i %i %i\n", i, j, direction[k][0], direction[k][1]);
            int multiplier = 1;
            while (board[(i) + dRow * multiplier][(j) + dCol * multiplier] != compC)
            {
                multiplier++;
            }
            score += multiplier;
        }
    }
    return score;
}
void copyBoard(char board[][26], char boardCopy[][26], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            boardCopy[i][j] = board[i][j];
        }
    }
}
// int centeredScore(char board[][26], int n, char compC, int *row, int *col) // Meant for center pieces
// {
// }

int centeredScore(char board[][26], int n, char compC, int *row, int *col) // Meant for center pieces
{
    char boardCopy[26][26];
    int scoreboard[26][26];
    copyBoard(board, boardCopy, n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scoreboard[i][j] = 0;
        }
    }
    scoreboard[(n - 1) / 2][(n - 1) / 2] = 2;
    scoreboard[(n - 1) / 2][((n - 1) / 2) + 1] = 2;
    scoreboard[(n / 2)][(n - 1) / 2] = 2;
    scoreboard[(n / 2)][((n - 1) / 2) + 1] = 2;

    scoreboard[(n - 1) / 2][((n - 1) / 2) - 1] = 1;
    scoreboard[(n - 1) / 2][((n - 1) / 2) + 2] = 1;
    scoreboard[(n / 2)][((n - 1) / 2) - 1] = 1;
    scoreboard[(n / 2)][((n - 1) / 2) + 2] = 1;

    scoreboard[(n - 3) / 2][(n - 1) / 2] = 1;
    scoreboard[(n - 3) / 2][((n - 1) / 2) + 1] = 1;
    scoreboard[((n + 2) / 2)][(n - 1) / 2] = 1;
    scoreboard[((n + 2) / 2)][((n - 1) / 2) + 1] = 1;

    scoreboard[(n - 3) / 2][(n - 3) / 2] = 1;
    scoreboard[(n - 3) / 2][((n + 2) / 2)] = 1;
    scoreboard[((n + 2) / 2)][(n - 3) / 2] = 1;
    scoreboard[((n + 2) / 2)][((n + 2) / 2)] = 1;

    int score = 0, largestScore = 0, direction[8][2] = {{1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}};
    for (int ii = 2; ii < n - 2; ii++)
    {
        for (int jj = 2; jj < n - 2; jj++)
        {
            copyBoard(board, boardCopy, n);
            for (int k = 0; k < 8; k++)
            {
                if (checkLegalInDirection(board, n, ii, jj, compC, direction[k][0], direction[k][1]))
                {
                    k = 9;
                    fliptiles(boardCopy, n, compC, ii, jj);
                    for (int i = 0; i < n; i++)
                    {
                        for (int j = 0; j < n; j++)
                        {
                            if (board[i][j] - boardCopy[i][j] != 0)
                            {
                                if (scoreboard[i][j] != 0)
                                {
                                    score += scoreboard[i][j];
                                }
                            }
                        }
                    }
                    copyBoard(board, boardCopy, n);
                    if (score > largestScore)
                    {
                        largestScore = score;
                        *row = ii, *col = jj;
                    }
                    score = 0;
                }
            }
        }
    }
    return largestScore;
}
int highestScore(char board[][26], int n, char compC, int *row, int *col) // Returns highest score
{
    int score = 0, largestScore = 0, lowestscore = (n * n) + 1, fill = 0;
    int highi, highj, lowi, lowj;
    for (int i = 0; i < n; i++) // finds the best spot for the computer
    {
        for (int j = 0; j < n; j++)
        {
            score = computer(board, n, compC, i, j);
            if (score > largestScore)
            {
                largestScore = score;
                highi = i, highj = j;
            }
            if (score < lowestscore)
            {
                lowestscore = score;
                lowi = i, lowj = j;
            }
        }
    }

    for (int i = 0; i < n; i++) // finds the best spot for the computer
    {
        for (int j = 0; j < n; j++)
        {
            if (board[i][j] == 'W' || board[i][j] == 'B')
            {
                fill++;
            }
        }
    }
    if (fill > (n * n) / 2)
    {
        *row = highi, *col = highj;
        return 0;
    }
    else
    {
        *row = lowi, *col = lowj;
        return 0;
    }

    return largestScore;
}
int makeMove(char board[][26], int n, char turn, int *row, int *col)
{
    // 1-corners
    int check = 0;
    // corner
    if (check == 0)
    {
        if (available(board, n, 0, 0, turn))
        {
            *row = 0, *col = 0, check = 1;
        }
        else if (available(board, n, 0, n - 1, turn))
        {
            *row = 0, *col = n - 1, check = 1;
        }
        else if (available(board, n, n - 1, 0, turn))
        {
            *row = n - 1, *col = 0, check = 1;
        }
        else if (available(board, n, n - 1, n - 1, turn))
        {
            *row = n - 1, *col = n - 1, check = 1;
        }
    }
    if (check == 0) // around corner
    {
        if (board[0][0] == turn) // topL
        {

            if (available(board, n, 0, 1, turn))
                *row = 0, *col = 1, check = 1;
            else if (available(board, n, 1, 0, turn))
                *row = 1, *col = 0, check = 1;
        }
        if (board[n - 1][n - 1] == turn) // bottomR
        {
            if (available(board, n, n - 2, n - 1, turn))
                *row = n - 2, *col = n - 1, check = 1;
            else if (available(board, n, n - 1, n - 2, turn))
                *row = n - 1, *col = n - 2, check = 1;
        }
        if (board[0][n - 1] == turn) // topR
        {
            if (available(board, n, 0, n - 2, turn))
                *row = 0, *col = n - 2, check = 1;
            else if (available(board, n, 1, n - 1, turn))
                *row = 1, *col = n - 1, check = 1;
        }
        if (board[n - 1][0] == turn) // bottomL
        {
            if (available(board, n, n - 1, 1, turn))
                *row = n - 1, *col = 1, check = 1;
            else if (available(board, n, n - 2, 0, turn))
                *row = n - 2, *col = 0, check = 1;
        }
    }
    if (check == 0) // edge
    {
        int score = 0, largestScore = 0;
        for (int k = 2; k < n - 2; k++)
        {
            if (available(board, n, 0, k, turn))
            {
                score = computer(board, n, turn, 0, k);
                if (score > largestScore)
                {
                    largestScore = score;
                    *row = 0, *col = k, check = 1;
                }
            }
            if (available(board, n, k, 0, turn))
            {
                score = computer(board, n, turn, k, 0);
                if (score > largestScore)
                {
                    largestScore = score;
                    *row = k, *col = 0, check = 1;
                }
            }
            if (available(board, n, n - 1, k, turn))
            {
                score = computer(board, n, turn, n - 1, k);
                if (score > largestScore)
                {
                    largestScore = score;
                    *row = n - 1, *col = k, check = 1;
                }
            }
            if (available(board, n, turn, k, n - 1))
            {
                score = computer(board, n, turn, k, n - 1);
                if (score > largestScore)
                {
                    largestScore = score;
                    *row = k, *col = n - 1, check = 1;
                }
            }
        }
    }
    // if (check == 0) // center
    // {
    //     if (centeredScore(board, n, turn, row, col) != 0)
    //         check = 1;
    // }
    
    if (check == 0)
    {
        for (int i = 2; i < 6 && check == 0; i++)
        {
            if (available(board, n, 2, i, turn))
            {
                *row = 2,*col = i,check = 0;
            }
            else if (available(board, n, 5, i, turn))
            {
                *row = 5,*col = i,check = 0;
            }
            else if (available(board, n, i, 2, turn))
            {
                *row = i, *col = 2, check = 0;
            }
            else if (available(board, n, i, 5, turn))
            {
                *row = i,*col = 5,check = 0;
            }
        }
    }
    if (check == 0) // highest score
    {
        if (highestScore(board, n, turn, row, col) != 0)
            check = 1;
    }
    if (check == 0) // pick any spot
    {
        for (int i = 0; i < n; i++) // finds the best spot for the computer
        {
            for (int j = 0; j < n; j++)
            {
                if (available(board, n, i, j, turn))
                {
                    *row = i, *col = j;
                }
            }
        }
    }
    return 0;
}
int main(void)
{
    // Creating Base Board
    int row, col;
    int *rows = &row, *cols = &col;
    int n;
    char board[26][26], move[3], dRow, dCol, compcolour, playcolour;
    char winnerCheck = 'C'; // When this value is equal to 'C', the game will be continued, otherwise it will be either 'W', 'B', or 'D' for draw
    int direction[8][2] = {{1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}};
    int playfirst = 0;
    printf("Black(B) goes first.\nMake sure to pick an Even board dimension for fair play.\n\n");
    printf("Enter the board dimension: "); // creating board
    scanf("%i", &n);
    makeBoard(board, n);

    printf("Computer plays (B/W): ");
    scanf(" %c", &compcolour);
    printBoard(board, n);

    if (compcolour == 'W')
        playcolour = 'B';
    else
        playcolour = 'W';

    char playC = playcolour;
    char compC = compcolour;

    while (winnerCheck == 'C')
    {
        if (!availableChecker(board, n, playC))
        {
            printf("%c player has no valid move.\n", playC);
        }
        else if (compC == 'W' || playfirst == 1) // ensures that black goes first
        {
            printf("Enter move for colour %c (RowCol): ", playC);
            scanf("%s", move);

            if (available(board, n, move[0] - 97, move[1] - 97, playC)) // Out of Bounds/Already taken spot
            {
                for (int k = 0; k < 8; k++)
                {
                    dRow = direction[k][0], dCol = direction[k][1];
                    if (checkLegalInDirection(board, n, move[0] - 97, move[1] - 97, playC, dRow, dCol)) // If chosen spot is valid
                    {
                        int multiplier = 1;
                        while (board[(move[0] - 97) + dRow * multiplier][(move[1] - 97) + dCol * multiplier] != playC)
                        {

                            board[(move[0] - 97) + dRow * multiplier][(move[1] - 97) + dCol * multiplier] = playC;
                            multiplier++;
                        }
                    }
                }
                board[move[0] - 'a'][move[1] - 'a'] = playC;
                printBoard(board, n);
            }
            else
            {
                printf("Invalid move.\n");
                winnerCheck = compC;
            }
            if (winnerCheck == 'C')
            {
                winnerCheck = winnerDetect(board, n, playC, compC);
            }
        }
        playfirst = 1;
        //---------------------------------------------------------------------------------------
        if (winnerCheck == 'C')
        {
            makeMove(board, n, compC, rows, cols);
            fliptiles(board, n, compC, row, col);
            board[row][col] = compC;
            printf("Computer played this: %c%c\n", row + 97, col + 97);
            printBoard(board, n);
        }
        if (winnerCheck == 'C')
            winnerCheck = winnerDetect(board, n, playC, compC);
    }
    printf("%c player wins.", winnerCheck);
}