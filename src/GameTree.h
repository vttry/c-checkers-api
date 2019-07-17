#if !defined(INCLUDED_GAMETHREE_H)
#define INCLUDED_GAMETHREE_H

typedef struct GameTree
{
    char board[8][8];
    struct GameTreeList * children;
} GameTree;

typedef struct GameTreeList
{
    GameTree gameTree;
    struct GameTreeList *next;
} GameTreeList;

#ifdef __cplusplus
extern "C"
{
#endif

    void FreeGameTree(GameTree *gameTree);

#ifdef __cplusplus
}
#endif

#endif // INCLUDED_GAMETHREE_H