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
        newBoard[curentNode->moveThree.Move.finalPosition[0]][curentNode->moveThree.Move.finalPosition[1]] =
            curentNode->moveThree.Move.finalStatus;
        if (curentNode->moveThree.Move.isJump)
        {
            newBoard[curentNode->moveThree.Move.capturedPosition[0]][curentNode->moveThree.Move.capturedPosition[1]] =
                BLACK_EMPTY_FIELD;
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

bool checkMove(const char initialBoardStatus[8][8],
               const int startPosition[2],
               const int finalPosition[2],
               const GenerateThePossibleMovesForPieceFunction generateThePossibleMovesForPieceFunction)
{
    //we have to check that coordinates is valid,
    //start coordinate is a piece,
    //end coordinate don't have the same color,
    if (!checkCoordinate(startPosition) ||
        !checkCoordinate(finalPosition) ||
        getPieceByPosition(initialBoardStatus, startPosition) == BLACK_EMPTY_FIELD ||
        isBlackPiece(getPieceByPosition(initialBoardStatus, startPosition)) ==
            isBlackPiece(getPieceByPosition(initialBoardStatus, finalPosition)))
    {
        return false;
    }
    //second check we have to build possible moves
    //and if final position has the same color as start position then
    //we can say that move exists
    BoardList *boardList = generateThePossibleMovesForPieceFunction(initialBoardStatus, startPosition);
    if (!boardList)
    {
        return false;
    }

    BoardList *currentItem = NULL;
    bool isFound = false;
    SGLIB_LIST_MAP_ON_ELEMENTS(struct BoardList, boardList, currentItem, next, {
        //check if finalPosition has the same color as start
        if (!isFound &&
            getPieceByPosition(currentItem->board, finalPosition) != BLACK_EMPTY_FIELD &&
            isBlackPiece(getPieceByPosition(initialBoardStatus, startPosition)) ==
                isBlackPiece(getPieceByPosition(currentItem->board, finalPosition)))
        {
            isFound = true;
        }
        //free allocated memory
        free(currentItem);
    });
    return isFound;
}