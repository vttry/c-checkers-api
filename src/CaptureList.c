#include "CaptureList.h"
#include <stdio.h>
#include <stdlib.h>
void FreeCaptureList(CaptureList *CaptureList)
{
    if (CaptureList->next)
    {
        FreeCaptureList(CaptureList->next);
    }
    free(CaptureList);
}


CaptureList *CreateCaptureList(const int position[2],
                               const CaptureList *previous)
{
    int size = sizeof(CaptureList);
    CaptureList *ct = malloc(sizeof(CaptureList));
    ct->position[0] = position[0];
    ct->position[1] = position[1];
    ct->previous = previous;
    return ct;
}