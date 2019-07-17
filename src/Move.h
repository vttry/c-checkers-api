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

    typedef struct MoveTree
    {
        struct MoveTree *parent;
        Move Move;
        struct MoveTreeList *chidren;
    } MoveTree;

    typedef struct MoveTreeList
    {
        MoveTree moveTree;
        struct MoveTreeList *next;
    } MoveTreeList;

    void FreeMoveTreeList(MoveTreeList *moveTreeList);

#ifdef __cplusplus
}
#endif

#endif // INCLUDED_MOVE_H
