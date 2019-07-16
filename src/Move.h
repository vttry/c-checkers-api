#if !defined(INCLUDED_MOVE_H)
#define INCLUDED_MOVE_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct Move
    {
        bool isJump;
        int finalPosition[2];
        int capturedPosition[2];
        char finalStatus;
    } Move;

    typedef struct MoveList
    {
        Move Move;
        struct MoveList *next;
    } MoveList;

    typedef struct MoveThree
    {
        struct MoveThree *parent;
        Move Move;
        struct MoveThreeList *chidren;
    } MoveThree;

    typedef struct MoveThreeList
    {
        MoveThree moveThree;
        struct MoveThreeList *next;
    } MoveThreeList;

    void FreeMoveThreeList(MoveThreeList *moveThreeList);

#ifdef __cplusplus
}
#endif

#endif // INCLUDED_MOVE_H
