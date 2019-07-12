#if !defined(INCLUDED_GAME_THREE_H)
#define INCLUDED_GAME_THREE_H

#include "CheckerTurn.h"
typedef struct GameThree
{
    struct GameThree **children;
    struct GameThree *parent;
    CheckerTurn CheckerTurn;
    int childrenCount;
} GameThree;

void FreeGameThree(GameThree *gameThree);

#endif // INCLUDED_GAME_THREE_H