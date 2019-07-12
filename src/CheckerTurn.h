
#if !defined(INCLUDED_CHECKER_TURN_H)
#define INCLUDED_CHECKER_TURN_H

typedef struct CheckerTurn
{
    int checkerColor;
    int firstCheckerType;
    int secondCheckerType;
    int firsPosition[2];
    int secondPosition[2];
    int *defietedEnemyPositions[2];
    int defietedEnemiesCount;
} CheckerTurn;

void FreeMove(CheckerTurn *CheckerTurn);

#endif // INCLUDED_CHECKER_TURN_H