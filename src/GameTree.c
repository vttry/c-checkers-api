#include <stdio.h>
#include <stdlib.h>
#include <sglib.h>
#include "GameTree.h"

void FreeGameTree(GameTree *gameTree)
{
    if (!gameTree)
        return;
    GameTreeList *currentItem = NULL;
    SGLIB_LIST_MAP_ON_ELEMENTS(struct GameTreeList, gameTree->children, currentItem, next, {
        free(currentItem);
    });
}