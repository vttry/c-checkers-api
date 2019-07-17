#include <stdio.h>
#include <stdlib.h>
#include <sglib.h>
#include "Move.h"

void FreeMoveTreeList(MoveTreeList *moveTreeList)
{
    MoveTreeList *currentItem = NULL;
    SGLIB_LIST_MAP_ON_ELEMENTS(struct MoveTreeList, moveTreeList, currentItem, next, {
        FreeMoveTreeList(currentItem->moveTree.chidren);
        free(currentItem);
    });
}