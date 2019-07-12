
#include "CheckersGame.h"
#include "Checker.h"

#include <sglib.h>


bool checkMove(const char initialBoardStatus[8][8],
               const int firstPosition[2],
               const int finalPosition[2],
               int *defietedEnemyPositions[2],
               int *defietedEnemiesCount)
{
    //check checkers
    
    return true;
}

void resetBoard(char board[8][8])
{

    //fill board with white fields
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            board[i][j * 2 + 1 - i % 2] = WHITE_FIELD;
        }
    }

    //fill board with white chekers
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            board[i][j * 2 + i % 2] = WHITE_CHECKER;
        }
    }

    //fill board with Black Fields
    for (int i = 3; i < 5; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            board[i][j * 2 + i % 2] = BLACK_EMPTY_FIELD;
        }
    }

    //fill board with black chekers
    for (int i = 5; i < 8; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            board[i][j * 2 + i % 2] = BLACK_CHECKER;
        }
    }
}