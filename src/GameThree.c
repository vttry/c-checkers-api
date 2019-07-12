#include <stdlib.h>
#include "GameThree.h"
void FreeGameThree(GameThree *gameThree)
{
    if (gameThree->childrenCount > 0)
    {
        for (size_t i = 0; i < gameThree->childrenCount; i++)
        {
            FreeGameThree(&gameThree[i]);
            free(&gameThree[i]);
        }
    }
    free(gameThree);
}