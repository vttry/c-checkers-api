#include <stdio.h>
#include <stdlib.h>
#include <sglib.h>
#include "CheckersGame.h"

//Function that check if a coordinate is in the rigth range and on a black field
static bool checkCoordinate(const int position[2])
{
    //check if position in the right range
    if (position == NULL ||
        position[0] < 0 ||
        position[0] > 7 ||
        position[1] < 0 ||
        position[1] > 7)
        return false;

    //check if position is a black field
    return (position[0] % 2 == position[1] % 2);
}

//check if checker is black
static bool isBlackPiece(const char checker)
{
    return checker > '2';
};

//get checker status
static const char getFinalStatus(const char checker, int finalPosition[2])
{
    if (isBlackPiece(checker))
    {
        if (checker == BLACK_KING || finalPosition[0] == 7)
        {
            return BLACK_KING;
        }
        else
        {
            return BLACK_CHECKER;
        }
    }
    else
    {
        if (checker == WHITE_KING || finalPosition[0] == 0)
        {
            return WHITE_KING;
        }
        else
        {
            return WHITE_CHECKER;
        }
    }
};

//set piece by type and position
static void setPieceByTypeAndPosition(char board[8][8], char type, const int position[2])
{
    board[position[0]][position[1]] = type;
}

//return piece by position
static const char getPieceByPosition(const char board[8][8], const int position[2])
{
    return board[position[0]][position[1]];
}

//copy position
static void copyPosition(int destination[2], const int position[2])
{
    destination[0] = position[0];
    destination[1] = position[1];
}

//Function that copy board state to destination
static void copyBoard(char destinationBoard[8][8], const char originalBoard[8][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            destinationBoard[i][j] = originalBoard[i][j];
        }
    }
}

//we try to find all possible moves from current position for a checker
bool findPossiblePieceJumps(const char board[8][8], const int startPosition[2], MoveList **list)
{

    //first is right-top
    {
        int finalPosition[2] = {startPosition[0] + 2,
                                startPosition[1] + 2};
        int capturedPosition[2] = {startPosition[0] + 1,
                                   startPosition[1] + 1};

        if (checkCoordinate(finalPosition) &&
            getPieceByPosition(board, finalPosition) == BLACK_EMPTY_FIELD &&
            getPieceByPosition(board, capturedPosition) != BLACK_EMPTY_FIELD &&
            isBlackPiece(getPieceByPosition(board, capturedPosition)) != isBlackPiece(getPieceByPosition(board, startPosition)))
        {
            MoveList *currentMove = (MoveList *)malloc(sizeof(MoveList));
            copyPosition(currentMove->Move.capturedPosition, capturedPosition);
            copyPosition(currentMove->Move.finalPosition, finalPosition);
            currentMove->Move.finalStatus = getFinalStatus(getPieceByPosition(board, finalPosition), finalPosition);
            currentMove->Move.isJump = true;
            SGLIB_LIST_ADD(MoveList, *list, currentMove, next);
        }
    }

    //left-top
    {
        int finalPosition[2] = {startPosition[0] - 2,
                                startPosition[1] + 2};
        int capturedPosition[2] = {startPosition[0] - 1,
                                   startPosition[1] + 1};
        if (checkCoordinate(finalPosition) &&
            getPieceByPosition(board, finalPosition) == BLACK_EMPTY_FIELD &&
            getPieceByPosition(board, capturedPosition) != BLACK_EMPTY_FIELD &&
            isBlackPiece(getPieceByPosition(board, capturedPosition)) != isBlackPiece(getPieceByPosition(board, startPosition)))
        {
            MoveList *currentMove = (MoveList *)malloc(sizeof(MoveList));
            copyPosition(currentMove->Move.capturedPosition, capturedPosition);
            copyPosition(currentMove->Move.finalPosition, finalPosition);
            currentMove->Move.finalStatus = getFinalStatus(getPieceByPosition(board, finalPosition), finalPosition);
            currentMove->Move.isJump = true;
            SGLIB_LIST_ADD(MoveList, *list, currentMove, next);
        }
    }

    //left-bottom
    {
        int finalPosition[2] = {startPosition[0] - 2,
                                startPosition[1] - 2};
        int capturedPosition[2] = {startPosition[0] - 1,
                                   startPosition[1] - 1};
        if (checkCoordinate(finalPosition) &&
            getPieceByPosition(board, finalPosition) == BLACK_EMPTY_FIELD &&
            getPieceByPosition(board, capturedPosition) != BLACK_EMPTY_FIELD &&
            isBlackPiece(getPieceByPosition(board, capturedPosition)) != isBlackPiece(getPieceByPosition(board, startPosition)))
        {
            MoveList *currentMove = (MoveList *)malloc(sizeof(MoveList));
            copyPosition(currentMove->Move.capturedPosition, capturedPosition);
            copyPosition(currentMove->Move.finalPosition, finalPosition);
            currentMove->Move.finalStatus = getFinalStatus(getPieceByPosition(board, finalPosition), finalPosition);
            currentMove->Move.isJump = true;
            SGLIB_LIST_ADD(MoveList, *list, currentMove, next);
        }
    }

    //right-bottom
    {
        int finalPosition[2] = {startPosition[0] + 2,
                                startPosition[1] - 2};
        int capturedPosition[2] = {startPosition[0] + 1,
                                   startPosition[1] - 1};
        if (checkCoordinate(finalPosition) &&
            getPieceByPosition(board, finalPosition) == BLACK_EMPTY_FIELD &&
            getPieceByPosition(board, capturedPosition) != BLACK_EMPTY_FIELD &&
            isBlackPiece(getPieceByPosition(board, capturedPosition)) != isBlackPiece(getPieceByPosition(board, startPosition)))
        {
            MoveList *currentMove = (MoveList *)malloc(sizeof(MoveList));
            copyPosition(currentMove->Move.capturedPosition, capturedPosition);
            copyPosition(currentMove->Move.finalPosition, finalPosition);
            currentMove->Move.finalStatus = getFinalStatus(getPieceByPosition(board, finalPosition), finalPosition);
            currentMove->Move.isJump = true;
            SGLIB_LIST_ADD(MoveList, *list, currentMove, next);
        }
    }
}

//build three of possible moves for the checker
bool buildPieceJumpThreeList(const char board[8][8], const int startPosition[2], MoveThreeList **moveThreeList)
{
    MoveList *currentMoveList = NULL;
    MoveList *currentMove = NULL;
    findPossiblePieceJumps(board, startPosition, &currentMoveList);

    //recursively call buildCheckerMoveThreeList for all finded Move
    SGLIB_LIST_MAP_ON_ELEMENTS(struct MoveList, currentMoveList, currentMove, next, {
        //alloc memory for new node and set current Move
        MoveThreeList *currentMoveThreeList = (MoveThreeList *)malloc(sizeof(MoveThreeList));
        currentMoveThreeList->moveThree.Move = currentMove->Move;
        copyPosition(currentMoveThreeList->moveThree.Move.capturedPosition, currentMove->Move.capturedPosition);
        copyPosition(currentMoveThreeList->moveThree.Move.finalPosition, currentMove->Move.finalPosition);
        currentMoveThreeList->moveThree.Move.finalStatus = currentMove->Move.finalStatus;
        currentMoveThreeList->moveThree.Move.isJump = true;
        currentMoveThreeList->moveThree.chidren = NULL;
        currentMoveThreeList->next = NULL;

        //free currentMove
        free(currentMove);

        //make copy of board
        char currentBoard[8][8];
        copyBoard(currentBoard, board);

        //make swap
        setPieceByTypeAndPosition(currentBoard, getPieceByPosition(board, startPosition), currentMoveThreeList->moveThree.Move.finalPosition);
        setPieceByTypeAndPosition(currentBoard, BLACK_EMPTY_FIELD, startPosition);
        setPieceByTypeAndPosition(currentBoard, BLACK_EMPTY_FIELD, currentMoveThreeList->moveThree.Move.capturedPosition);

        //call recursively to fill children nodes;
        buildPieceJumpThreeList(currentBoard, currentMoveThreeList->moveThree.Move.finalPosition, &currentMoveThreeList->moveThree.chidren);

        //add currentMoveThreeList to Move three list
        SGLIB_LIST_ADD(MoveThreeList, *moveThreeList, currentMoveThreeList, next);
    });
}

void resetBoard(char board[8][8])
{

    //fill board with white fields
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            board[i][j * 2 + 1 - i % 2] = WHITE_FIELD;
        }
    }

    //fill board with white chekers
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            board[i][j * 2 + i % 2] = WHITE_CHECKER;
        }
    }

    //fill board with Black Fields
    for (int i = 3; i < 5; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            board[i][j * 2 + i % 2] = BLACK_EMPTY_FIELD;
        }
    }

    //fill board with black chekers
    for (int i = 5; i < 8; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            board[i][j * 2 + i % 2] = BLACK_CHECKER;
        }
    }
}