#include "CheckerTurn.h"

void FreeMove(CheckerTurn *CheckerTurn)
{
    if (CheckerTurn->defietedEnemiesCount > 0)
        for (int i = 0; i < CheckerTurn->defietedEnemiesCount; i++)
        {
            free(CheckerTurn->defietedEnemyPositions[i]);
        }
    free(CheckerTurn);
}