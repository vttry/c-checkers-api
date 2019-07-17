#if !defined(INCLUDED_GAMETHREE_H)
#define INCLUDED_GAMETHREE_H

typedef struct GameThree
{
    char board[8][8];
    struct GameThreeList * children;
} GameThree;

typedef struct GameThreeList
{
    GameThree gameThree;
    struct GameThreeList *next;
} GameThreeList;


#endif // INCLUDED_GAMETHREE_H