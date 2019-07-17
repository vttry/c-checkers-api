#include <stdio.h>
#include <stdlib.h>
#include <sglib.h>

#include "CheckersGame.h"
#include "CheckersGameAPI.h"

void resetBoardToInitialState(char board[8][8])
{
    resetBoard(board);
}

static void buildBoardList(const char currentBoard[8][8], BoardList **list, MoveThree *parentNode)
{
    //if we dont have children we just add currentBoard to list
    if (!parentNode->chidren)
    {
        BoardList *currentBoardList = (BoardList *)malloc(sizeof(BoardList));
        copyBoard(currentBoardList->board, currentBoard);
        currentBoardList->next = NULL;
        SGLIB_LIST_ADD(struct BoardList, *list, currentBoardList, next);
        return;
    }

    //we have to make changes on board using children nodes and recursively call current function
    MoveThreeList *curentNode = NULL;

    SGLIB_LIST_MAP_ON_ELEMENTS(struct MoveThreeList, parentNode->chidren, curentNode, next, {
        char newBoard[8][8];
        copyBoard(newBoard, currentBoard);
        newBoard[parentNode->Move.finalPosition[0]][parentNode->Move.finalPosition[1]] = BLACK_EMPTY_FIELD;
        newBoard[curentNode->moveThree.Move.finalPosition[0]][curentNode->moveThree.Move.finalPosition[1]] = curentNode->moveThree.Move.finalStatus;
        if (curentNode->moveThree.Move.isJump)
        {
            newBoard[curentNode->moveThree.Move.capturedPosition[0]][curentNode->moveThree.Move.capturedPosition[1]] = BLACK_EMPTY_FIELD;
        }
        buildBoardList(newBoard, list, &curentNode->moveThree);
    });
}

BoardList *generateThePossibleMovesForPiece(const char initialBoardStatus[8][8],
                                            const int startPosition[2])
{
    MoveThree *moveThree = (MoveThree *)malloc(sizeof(MoveThree));
    generateMoveThreeForPiece(initialBoardStatus, startPosition, moveThree);
    if (!moveThree->chidren)
    {
        free(moveThree);
        return NULL;
    }
    BoardList *boardList = NULL;

    //build moveThree
    buildBoardList(initialBoardStatus, &boardList, moveThree);

    //free allocated memory
    FreeMoveThreeList(moveThree->chidren);
    free(moveThree);
    return boardList;
}