#include <stdio.h>
#include <stdlib.h>
#include <sglib.h>
#include "Move.h"

void FreeMoveThreeList(MoveThreeList *moveThreeList)
{
    MoveThreeList *currentItem = NULL;
    SGLIB_LIST_MAP_ON_ELEMENTS(struct MoveThreeList, moveThreeList, currentItem, next, {
        FreeMoveThreeList(currentItem->moveThree.chidren);
        free(currentItem);
    });
}