#include <stdio.h>
#include <stdlib.h>
#include <sglib.h>
#include "CheckersGame.h"

//Function that check if a coordinate is in the rigth range and on a black field
bool checkCoordinate(const int position[2])
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
bool isBlackPiece(const char checker)
{
    return checker > '2';
};

//get checker status
static const char getFinalStatus(const char checker, int finalPosition[2])
{
    if (isBlackPiece(checker))
    {
        if (checker == BLACK_KING || finalPosition[0] == 0)
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
        if (checker == WHITE_KING || finalPosition[0] == 7)
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
const char getPieceByPosition(const char board[8][8], const int position[2])
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
void copyBoard(char destinationBoard[8][8], const char originalBoard[8][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            destinationBoard[i][j] = originalBoard[i][j];
        }
    }
}

//get offset
void getOffset(const int startPosition[2], const int endPosition[2], int offset[2])
{
    offset[0] = endPosition[0] > startPosition[0] ? 1 : -1;
    offset[1] = endPosition[1] > startPosition[1] ? 1 : -1;
}

//We try to find piece-empty Pattern for kings
bool findPieceEmptyDiagonalPattern(const char board[8][8],
                                   const int offset[2],
                                   const int startPosition[2],
                                   int startPointOfPattern[2])
{
    int currentPosition[2] = {
        startPosition[0] + offset[0] * 2,
        startPosition[1] + offset[1] * 2};

    int capturedPosition[2] = {
        startPosition[0] + offset[0],
        startPosition[1] + offset[1]};

    while (checkCoordinate(currentPosition))
    {
        if (getPieceByPosition(board, capturedPosition) == BLACK_EMPTY_FIELD)
        {
            capturedPosition[0] += offset[0];
            capturedPosition[1] += offset[1];
            currentPosition[0] += offset[0];
            currentPosition[1] += offset[1];

            continue;
        }

        //check if captured position is cell with figure which hasen't the same color and second position is empty black field
        if (
            getPieceByPosition(board, currentPosition) == BLACK_EMPTY_FIELD &&
            getPieceByPosition(board, capturedPosition) != BLACK_EMPTY_FIELD &&
            (isBlackPiece(getPieceByPosition(board, capturedPosition)) !=
             isBlackPiece(getPieceByPosition(board, startPosition))))
        {
            copyPosition(startPointOfPattern, capturedPosition);
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

//we try to find all possible jumps for current position for a checker
void findPossiblePieceJumps(const char board[8][8], const int startPosition[2], MoveList **list)
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
            currentMove->Move.finalStatus = getFinalStatus(getPieceByPosition(board, startPosition), finalPosition);
            currentMove->Move.isJump = true;
            SGLIB_LIST_ADD(MoveList, *list, currentMove, next);
        }
    }

    //left-top
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
            currentMove->Move.finalStatus = getFinalStatus(getPieceByPosition(board, startPosition), finalPosition);
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
            currentMove->Move.finalStatus = getFinalStatus(getPieceByPosition(board, startPosition), finalPosition);
            currentMove->Move.isJump = true;
            SGLIB_LIST_ADD(MoveList, *list, currentMove, next);
        }
    }

    //right-bottom
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
            currentMove->Move.finalStatus = getFinalStatus(getPieceByPosition(board, startPosition), finalPosition);
            currentMove->Move.isJump = true;
            SGLIB_LIST_ADD(MoveList, *list, currentMove, next);
        }
    }
}

// build the list of second possible king jumps
void findPossibleSecondKingJumps(const char board[8][8], const int startPosition[2], const int offset[2], MoveList **list)
{
    //iterate trought offset path
    int currentOffsetPosition[2];
    copyPosition(currentOffsetPosition, startPosition);
    //left diagonal offset
    int leftDiagonalOffset[2] = {offset[0] * -1,
                                 offset[1]};
    //right diagonal offset
    int rightDiagonalOffset[2] = {offset[0],
                                  offset[1] * -1};
    //check all diagonal sides
    while (true)
    {
        int startPointOfPattern[2];
        //find left diagonal pattern
        if (findPieceEmptyDiagonalPattern(board, leftDiagonalOffset, currentOffsetPosition, startPointOfPattern))
        {
            int finalPosition[2] = {startPointOfPattern[0] + leftDiagonalOffset[0], startPointOfPattern[1] + leftDiagonalOffset[1]};
            MoveList *currentMove = (MoveList *)malloc(sizeof(MoveList));
            copyPosition(currentMove->Move.capturedPosition, startPointOfPattern);
            copyPosition(currentMove->Move.finalPosition, finalPosition);
            currentMove->Move.finalStatus = getPieceByPosition(board, startPosition);
            currentMove->Move.isJump = true;
            SGLIB_LIST_ADD(MoveList, *list, currentMove, next);
        }

        //find right diagonal pattern
        if (findPieceEmptyDiagonalPattern(board, rightDiagonalOffset, currentOffsetPosition, startPointOfPattern))
        {
            int finalPosition[2] = {startPointOfPattern[0] + rightDiagonalOffset[0], startPointOfPattern[1] + rightDiagonalOffset[1]};
            MoveList *currentMove = (MoveList *)malloc(sizeof(MoveList));
            copyPosition(currentMove->Move.capturedPosition, startPointOfPattern);
            copyPosition(currentMove->Move.finalPosition, finalPosition);
            currentMove->Move.finalStatus = getPieceByPosition(board, startPosition);
            currentMove->Move.isJump = true;
            SGLIB_LIST_ADD(MoveList, *list, currentMove, next);
        }
        currentOffsetPosition[0] += offset[0];
        currentOffsetPosition[1] += offset[1];
        if (!(checkCoordinate(currentOffsetPosition) && getPieceByPosition(board, currentOffsetPosition) == BLACK_EMPTY_FIELD))
        {
            currentOffsetPosition[0] -= offset[0];
            currentOffsetPosition[1] -= offset[1];
            break;
        }
    }

    //check last field in offset direction
    int finalPosition[2] = {currentOffsetPosition[0] + offset[0], currentOffsetPosition[1] + offset[1]};

    if (checkCoordinate(finalPosition) &&
        getPieceByPosition(board, finalPosition) == BLACK_EMPTY_FIELD &&
        getPieceByPosition(board, currentOffsetPosition) != BLACK_EMPTY_FIELD &&
        isBlackPiece(getPieceByPosition(board, currentOffsetPosition)) != isBlackPiece(getPieceByPosition(board, startPosition)))
    {
        MoveList *currentMove = (MoveList *)malloc(sizeof(MoveList));
        copyPosition(currentMove->Move.capturedPosition, currentOffsetPosition);
        copyPosition(currentMove->Move.finalPosition, finalPosition);
        currentMove->Move.finalStatus = getPieceByPosition(board, startPosition);
        currentMove->Move.isJump = true;
        SGLIB_LIST_ADD(MoveList, *list, currentMove, next);
    }
}

// build the list of first possible king jumps
void findPossibleKingFirstJumps(const char board[8][8], const int startPosition[2], MoveList **list)
{
    {
        //first is right-top
        int offset[2] = {1, 1};
        int startPointOfPattern[2];
        if (findPieceEmptyDiagonalPattern(board, offset, startPosition, startPointOfPattern))
        {
            int finalPosition[2] = {startPointOfPattern[0] + offset[0], startPointOfPattern[1] + offset[1]};
            MoveList *currentMove = (MoveList *)malloc(sizeof(MoveList));
            copyPosition(currentMove->Move.capturedPosition, startPointOfPattern);
            copyPosition(currentMove->Move.finalPosition, finalPosition);
            currentMove->Move.finalStatus = getPieceByPosition(board, startPosition);
            currentMove->Move.isJump = true;
            SGLIB_LIST_ADD(MoveList, *list, currentMove, next);
        }
    }
    {
        //left-top
        int offset[2] = {1, -1};
        int startPointOfPattern[2];
        if (findPieceEmptyDiagonalPattern(board, offset, startPosition, startPointOfPattern))
        {
            int finalPosition[2] = {startPointOfPattern[0] + offset[0], startPointOfPattern[1] + offset[1]};
            MoveList *currentMove = (MoveList *)malloc(sizeof(MoveList));
            copyPosition(currentMove->Move.capturedPosition, startPointOfPattern);
            copyPosition(currentMove->Move.finalPosition, finalPosition);
            currentMove->Move.finalStatus = getPieceByPosition(board, startPosition);
            currentMove->Move.isJump = true;
            SGLIB_LIST_ADD(MoveList, *list, currentMove, next);
        }
    }
    {
        //left-bottom
        int offset[2] = {-1, -1};
        int startPointOfPattern[2];
        if (findPieceEmptyDiagonalPattern(board, offset, startPosition, startPointOfPattern))
        {
            int finalPosition[2] = {startPointOfPattern[0] + offset[0], startPointOfPattern[1] + offset[1]};
            MoveList *currentMove = (MoveList *)malloc(sizeof(MoveList));
            copyPosition(currentMove->Move.capturedPosition, startPointOfPattern);
            copyPosition(currentMove->Move.finalPosition, finalPosition);
            currentMove->Move.finalStatus = getPieceByPosition(board, startPosition);
            currentMove->Move.isJump = true;
            SGLIB_LIST_ADD(MoveList, *list, currentMove, next);
        }
    }
    {
        //right-bottom
        int offset[2] = {-1, 1};
        int startPointOfPattern[2];
        if (findPieceEmptyDiagonalPattern(board, offset, startPosition, startPointOfPattern))
        {
            int finalPosition[2] = {startPointOfPattern[0] + offset[0], startPointOfPattern[1] + offset[1]};
            MoveList *currentMove = (MoveList *)malloc(sizeof(MoveList));
            copyPosition(currentMove->Move.capturedPosition, startPointOfPattern);
            copyPosition(currentMove->Move.finalPosition, finalPosition);
            currentMove->Move.finalStatus = getPieceByPosition(board, startPosition);
            currentMove->Move.isJump = true;
            SGLIB_LIST_ADD(MoveList, *list, currentMove, next);
        }
    }
}

//build tree of possible jumps for the checker
void generateJumpTreeForPiece(const char board[8][8], MoveTree *parentMoveTree)
{
    int *startPosition = parentMoveTree->Move.finalPosition;
    //check if current piece is not king
    if (getPieceByPosition(board, startPosition) == BLACK_CHECKER ||
        getPieceByPosition(board, startPosition) == WHITE_CHECKER)
    {
        MoveList *currentMoveList = NULL;
        MoveList *currentMove = NULL;
        findPossiblePieceJumps(board, startPosition, &currentMoveList);

        //recursively call buildCheckerMoveTreeList for all finded Move
        SGLIB_LIST_MAP_ON_ELEMENTS(struct MoveList, currentMoveList, currentMove, next, {
            //alloc memory for new node and set current Move
            MoveTreeList *currentMoveTreeList = (MoveTreeList *)malloc(sizeof(MoveTreeList));
            copyPosition(currentMoveTreeList->moveTree.Move.capturedPosition, currentMove->Move.capturedPosition);
            copyPosition(currentMoveTreeList->moveTree.Move.finalPosition, currentMove->Move.finalPosition);
            currentMoveTreeList->moveTree.Move.finalStatus = currentMove->Move.finalStatus;
            currentMoveTreeList->moveTree.Move.isJump = true;
            currentMoveTreeList->moveTree.chidren = NULL;
            currentMoveTreeList->moveTree.parent = parentMoveTree;
            currentMoveTreeList->next = NULL;

            //free currentMove
            free(currentMove);

            //make copy of board
            char currentBoard[8][8];
            copyBoard(currentBoard, board);

            //make swap
            setPieceByTypeAndPosition(currentBoard, currentMoveTreeList->moveTree.Move.finalStatus, currentMoveTreeList->moveTree.Move.finalPosition);
            setPieceByTypeAndPosition(currentBoard, BLACK_EMPTY_FIELD, startPosition);
            setPieceByTypeAndPosition(currentBoard, BLACK_EMPTY_FIELD, currentMoveTreeList->moveTree.Move.capturedPosition);

            //call recursively to fill children nodes;
            generateJumpTreeForPiece(currentBoard, &currentMoveTreeList->moveTree);

            //add currentMoveTreeList to parent Move tree list
            SGLIB_LIST_ADD(MoveTreeList, parentMoveTree->chidren, currentMoveTreeList, next);
        });

    }    //check if current piece is not king
    else //for Kings
    {
        //the rule is next:
        //if it is first jump
        //we have to check all diagonals to make jump
        //if we can we recursively call this method for next jump

        //else we have to
        //find offset direction (direct path)
        //find last empty field using offset direction
        //then we should find figure-black diagonal pattern for each pieces in (direct path)
        //if we find this pattern we have to recursively call current method
        //until second field of (direct path) isn't empty
        //then we have to check if last field is figure and second is empty
        //if yes, we recursively call current method for last field
        //after all we should check if we have jump series we only add jump series to moveTreeList
        //if not we modify last node moveTreeList

        //check if it first Jump
        if (!parentMoveTree->parent)
        {

            MoveList *currentMoveList = NULL;
            MoveList *currentMove = NULL;
            findPossibleKingFirstJumps(board, startPosition, &currentMoveList);

            //recursively call buildCheckerMoveTreeList for all finded Move
            SGLIB_LIST_MAP_ON_ELEMENTS(struct MoveList, currentMoveList, currentMove, next, {
                //alloc memory for new node and set current Move
                MoveTreeList *currentMoveTreeList = (MoveTreeList *)malloc(sizeof(MoveTreeList));
                
                copyPosition(currentMoveTreeList->moveTree.Move.capturedPosition, currentMove->Move.capturedPosition);
                copyPosition(currentMoveTreeList->moveTree.Move.finalPosition, currentMove->Move.finalPosition);
                currentMoveTreeList->moveTree.Move.finalStatus = currentMove->Move.finalStatus;
                currentMoveTreeList->moveTree.parent = parentMoveTree;
                currentMoveTreeList->moveTree.Move.isJump = true;
                currentMoveTreeList->moveTree.chidren = NULL;
                currentMoveTreeList->next = NULL;

                //free currentMove
                free(currentMove);

                //make copy of board
                char currentBoard[8][8];
                copyBoard(currentBoard, board);

                //make swap
                setPieceByTypeAndPosition(currentBoard, currentMoveTreeList->moveTree.Move.finalStatus, currentMoveTreeList->moveTree.Move.finalPosition);
                setPieceByTypeAndPosition(currentBoard, BLACK_EMPTY_FIELD, startPosition);
                setPieceByTypeAndPosition(currentBoard, BLACK_EMPTY_FIELD, currentMoveTreeList->moveTree.Move.capturedPosition);

                //call recursively to fill children nodes;
                generateJumpTreeForPiece(currentBoard, &currentMoveTreeList->moveTree);

                //add currentMoveTreeList to parent Move tree list
                SGLIB_LIST_ADD(MoveTreeList, parentMoveTree->chidren, currentMoveTreeList, next);
            });
        } //check if it first Jump
        else
        {
            int offset[2];
            getOffset(parentMoveTree->parent->Move.finalPosition, parentMoveTree->Move.finalPosition, offset);
            //second jump
            MoveList *currentMoveList = NULL;
            MoveList *currentMove = NULL;
            findPossibleSecondKingJumps(board, startPosition, offset, &currentMoveList);

            //recursively call buildCheckerMoveTreeList for all finded Move
            SGLIB_LIST_MAP_ON_ELEMENTS(struct MoveList, currentMoveList, currentMove, next, {
                //alloc memory for new node and set current Move
                MoveTreeList *currentMoveTreeList = (MoveTreeList *)malloc(sizeof(MoveTreeList));
              
                copyPosition(currentMoveTreeList->moveTree.Move.capturedPosition, currentMove->Move.capturedPosition);
                copyPosition(currentMoveTreeList->moveTree.Move.finalPosition, currentMove->Move.finalPosition);
                currentMoveTreeList->moveTree.Move.finalStatus = currentMove->Move.finalStatus;
                currentMoveTreeList->moveTree.parent = parentMoveTree;
                currentMoveTreeList->moveTree.Move.isJump = true;
                currentMoveTreeList->moveTree.chidren = NULL;
                currentMoveTreeList->next = NULL;

                //free currentMove
                free(currentMove);

                //make copy of board
                char currentBoard[8][8];
                copyBoard(currentBoard, board);

                //make swap
                setPieceByTypeAndPosition(currentBoard, currentMoveTreeList->moveTree.Move.finalStatus, currentMoveTreeList->moveTree.Move.finalPosition);
                setPieceByTypeAndPosition(currentBoard, BLACK_EMPTY_FIELD, startPosition);
                setPieceByTypeAndPosition(currentBoard, BLACK_EMPTY_FIELD, currentMoveTreeList->moveTree.Move.capturedPosition);

                //call recursively to fill children nodes;
                generateJumpTreeForPiece(currentBoard, &currentMoveTreeList->moveTree);

                //add currentMoveTreeList to parent Move tree list
                SGLIB_LIST_ADD(MoveTreeList, parentMoveTree->chidren, currentMoveTreeList, next);
            });

            //if we don't have jumps build just move forvard possibilities
            if (!currentMoveList)
            {

                //iterate trought offset path
                int currentOffsetPosition[2];
                copyPosition(currentOffsetPosition, startPosition);
                currentOffsetPosition[0] += offset[0];
                currentOffsetPosition[1] += offset[1];
                while (checkCoordinate(currentOffsetPosition) && getPieceByPosition(board, currentOffsetPosition) == BLACK_EMPTY_FIELD)
                {
                    //alloc memory for new node and set current Move
                    MoveTreeList *currentMoveTreeList = (MoveTreeList *)malloc(sizeof(MoveTreeList));
                
                    copyPosition(currentMoveTreeList->moveTree.Move.finalPosition, currentOffsetPosition);
                    currentMoveTreeList->moveTree.Move.finalStatus = parentMoveTree->Move.finalStatus;
                    currentMoveTreeList->moveTree.Move.isJump = false;
                    currentMoveTreeList->moveTree.parent = parentMoveTree->parent;
                    currentMoveTreeList->moveTree.chidren = NULL;
                    currentMoveTreeList->next = NULL;

                    //free currentMove
                    free(currentMove);

                    //add currentMoveTreeList to Move tree list
                    SGLIB_LIST_ADD(MoveTreeList, parentMoveTree->parent->chidren, currentMoveTreeList, next);

                    //find offset
                    currentOffsetPosition[0] += offset[0];
                    currentOffsetPosition[1] += offset[1];
                }
            }
        }
    }
}

//build tree of possible simple moves for the piece without jumps
void buildNotJumpTreeForNotKingPiece(const char board[8][8], MoveTree *parentMoveTree)
{
    int *startPosition = parentMoveTree->Move.finalPosition;

    //first is right-top it is only for white piece
    {
        int finalPosition[2] = {startPosition[0] + 1,
                                startPosition[1] + 1};

        if (checkCoordinate(finalPosition) &&
            !isBlackPiece(getPieceByPosition(board, startPosition)) &&
            getPieceByPosition(board, finalPosition) == BLACK_EMPTY_FIELD)
        {
            MoveTreeList *currentMoveTreeList = (MoveTreeList *)malloc(sizeof(MoveTreeList));
            copyPosition(currentMoveTreeList->moveTree.Move.finalPosition, finalPosition);
            currentMoveTreeList->moveTree.Move.finalStatus = getFinalStatus(getPieceByPosition(board, startPosition), finalPosition);
            currentMoveTreeList->moveTree.Move.isJump = false;
            currentMoveTreeList->moveTree.chidren = NULL;
            currentMoveTreeList->next = NULL;
            SGLIB_LIST_ADD(MoveTreeList, parentMoveTree->chidren, currentMoveTreeList, next);
        }
    }

    //left-top it is only for white piece
    {
        int finalPosition[2] = {startPosition[0] + 1,
                                startPosition[1] - 1};

        if (checkCoordinate(finalPosition) &&
            !isBlackPiece(getPieceByPosition(board, startPosition)) &&
            getPieceByPosition(board, finalPosition) == BLACK_EMPTY_FIELD)
        {
            MoveTreeList *currentMoveTreeList = (MoveTreeList *)malloc(sizeof(MoveTreeList));
            copyPosition(currentMoveTreeList->moveTree.Move.finalPosition, finalPosition);
            currentMoveTreeList->moveTree.Move.finalStatus = getFinalStatus(getPieceByPosition(board, startPosition), finalPosition);
            currentMoveTreeList->moveTree.Move.isJump = false;
            currentMoveTreeList->moveTree.chidren = NULL;
            currentMoveTreeList->next = NULL;
            SGLIB_LIST_ADD(MoveTreeList, parentMoveTree->chidren, currentMoveTreeList, next);
        }
    }

    //left-bottom it is only for black piece
    {
        int finalPosition[2] = {startPosition[0] - 1,
                                startPosition[1] - 1};

        if (checkCoordinate(finalPosition) &&
            isBlackPiece(getPieceByPosition(board, startPosition)) &&
            getPieceByPosition(board, finalPosition) == BLACK_EMPTY_FIELD)
        {
            MoveTreeList *currentMoveTreeList = (MoveTreeList *)malloc(sizeof(MoveTreeList));
            copyPosition(currentMoveTreeList->moveTree.Move.finalPosition, finalPosition);
            currentMoveTreeList->moveTree.Move.finalStatus = getFinalStatus(getPieceByPosition(board, startPosition), finalPosition);
            currentMoveTreeList->moveTree.Move.isJump = false;
            currentMoveTreeList->moveTree.chidren = NULL;
            currentMoveTreeList->next = NULL;
            SGLIB_LIST_ADD(MoveTreeList, parentMoveTree->chidren, currentMoveTreeList, next);
        }
    }

    //right-bottom  it is only for black piece
    {
        int finalPosition[2] = {startPosition[0] - 1,
                                startPosition[1] + 1};

        if (checkCoordinate(finalPosition) &&
            isBlackPiece(getPieceByPosition(board, startPosition)) &&
            getPieceByPosition(board, finalPosition) == BLACK_EMPTY_FIELD)
        {
            MoveTreeList *currentMoveTreeList = (MoveTreeList *)malloc(sizeof(MoveTreeList));
            copyPosition(currentMoveTreeList->moveTree.Move.finalPosition, finalPosition);
            currentMoveTreeList->moveTree.Move.finalStatus = getFinalStatus(getPieceByPosition(board, startPosition), finalPosition);
            currentMoveTreeList->moveTree.Move.isJump = false;
            currentMoveTreeList->moveTree.chidren = NULL;
            currentMoveTreeList->next = NULL;
            SGLIB_LIST_ADD(MoveTreeList, parentMoveTree->chidren, currentMoveTreeList, next);
        }
    }
}

//build tree of possible simple moves for the Kings without jumps
void buildNotJumpTreeForKingPiece(const char board[8][8], MoveTree *parentMoveTree)
{
    int *startPosition = parentMoveTree->Move.finalPosition;

    //first is right-top it is only for white piece
    {
        int offset[2] = {1, 1};
        //iterate trought offset path
        int currentOffsetPosition[2];
        copyPosition(currentOffsetPosition, startPosition);
        currentOffsetPosition[0] += offset[0];
        currentOffsetPosition[1] += offset[1];
        while (checkCoordinate(currentOffsetPosition) && getPieceByPosition(board, currentOffsetPosition) == BLACK_EMPTY_FIELD)
        {
            //alloc memory for new node and set current Data
            MoveTreeList *currentMoveTreeList = (MoveTreeList *)malloc(sizeof(MoveTreeList));
            copyPosition(currentMoveTreeList->moveTree.Move.finalPosition, currentOffsetPosition);
            currentMoveTreeList->moveTree.Move.finalStatus = BLACK_KING;
            currentMoveTreeList->moveTree.Move.isJump = false;
            currentMoveTreeList->moveTree.chidren = NULL;
            currentMoveTreeList->next = NULL;

            //add currentMoveTreeList to Move tree list
            SGLIB_LIST_ADD(MoveTreeList, parentMoveTree->chidren, currentMoveTreeList, next);

            //find offset
            currentOffsetPosition[0] += offset[0];
            currentOffsetPosition[1] += offset[1];
        }
    }

    //left-top it is only for white piece
    {
        int offset[2] = {1, -1};
        //iterate trought offset path
        int currentOffsetPosition[2];
        copyPosition(currentOffsetPosition, startPosition);
        currentOffsetPosition[0] += offset[0];
        currentOffsetPosition[1] += offset[1];
        while (checkCoordinate(currentOffsetPosition) && getPieceByPosition(board, currentOffsetPosition) == BLACK_EMPTY_FIELD)
        {
            //alloc memory for new node and set current Data
            MoveTreeList *currentMoveTreeList = (MoveTreeList *)malloc(sizeof(MoveTreeList));
            copyPosition(currentMoveTreeList->moveTree.Move.finalPosition, currentOffsetPosition);
            currentMoveTreeList->moveTree.Move.finalStatus = BLACK_KING;
            currentMoveTreeList->moveTree.Move.isJump = false;
            currentMoveTreeList->moveTree.chidren = NULL;
            currentMoveTreeList->next = NULL;

            //add currentMoveTreeList to Move tree list
            SGLIB_LIST_ADD(MoveTreeList, parentMoveTree->chidren, currentMoveTreeList, next);

            //find offset
            currentOffsetPosition[0] += offset[0];
            currentOffsetPosition[1] += offset[1];
        }
    }

    //left-bottom it is only for black piece
    {
        int offset[2] = {-1, -1};
        //iterate trought offset path
        int currentOffsetPosition[2];
        copyPosition(currentOffsetPosition, startPosition);
        currentOffsetPosition[0] += offset[0];
        currentOffsetPosition[1] += offset[1];
        while (checkCoordinate(currentOffsetPosition) && getPieceByPosition(board, currentOffsetPosition) == BLACK_EMPTY_FIELD)
        {
            //alloc memory for new node and set current Data
            MoveTreeList *currentMoveTreeList = (MoveTreeList *)malloc(sizeof(MoveTreeList));
            copyPosition(currentMoveTreeList->moveTree.Move.finalPosition, currentOffsetPosition);
            currentMoveTreeList->moveTree.Move.finalStatus = BLACK_KING;
            currentMoveTreeList->moveTree.Move.isJump = false;
            currentMoveTreeList->moveTree.chidren = NULL;
            currentMoveTreeList->next = NULL;

            //add currentMoveTreeList to Move tree list
            SGLIB_LIST_ADD(MoveTreeList, parentMoveTree->chidren, currentMoveTreeList, next);

            //find offset
            currentOffsetPosition[0] += offset[0];
            currentOffsetPosition[1] += offset[1];
        }
    }
    //right-bottom  it is only for black piece
    {
        int offset[2] = {-1, 1};
        //iterate trought offset path
        int currentOffsetPosition[2];
        copyPosition(currentOffsetPosition, startPosition);
        currentOffsetPosition[0] += offset[0];
        currentOffsetPosition[1] += offset[1];
        while (checkCoordinate(currentOffsetPosition) && getPieceByPosition(board, currentOffsetPosition) == BLACK_EMPTY_FIELD)
        {
            //alloc memory for new node and set current Data
            MoveTreeList *currentMoveTreeList = (MoveTreeList *)malloc(sizeof(MoveTreeList));
            copyPosition(currentMoveTreeList->moveTree.Move.finalPosition, currentOffsetPosition);
            currentMoveTreeList->moveTree.Move.finalStatus = BLACK_KING;
            currentMoveTreeList->moveTree.Move.isJump = false;
            currentMoveTreeList->moveTree.chidren = NULL;
            currentMoveTreeList->next = NULL;

            //add currentMoveTreeList to Move tree list
            SGLIB_LIST_ADD(MoveTreeList, parentMoveTree->chidren, currentMoveTreeList, next);

            //find offset
            currentOffsetPosition[0] += offset[0];
            currentOffsetPosition[1] += offset[1];
        }
    }
}

void generateMoveTreeForPiece(const char initialBoardStatus[8][8],
                               const int startPosition[2],
                               MoveTree *parentMoveTree)
{
    //set first node of tree
    copyPosition(parentMoveTree->Move.finalPosition, startPosition);
    parentMoveTree->Move.finalStatus = getPieceByPosition(initialBoardStatus, startPosition);
    parentMoveTree->Move.isJump = false;
    parentMoveTree->parent = NULL;
    parentMoveTree->chidren = NULL;
    //first try to build jump tree list
    generateJumpTreeForPiece(initialBoardStatus, parentMoveTree);

    // second try to build move list if we don't have jumps
    if (!parentMoveTree->chidren)
    {
        //check if current piece is checker
        if (getPieceByPosition(initialBoardStatus, startPosition) == BLACK_CHECKER ||
            getPieceByPosition(initialBoardStatus, startPosition) == WHITE_CHECKER)
        {
            buildNotJumpTreeForNotKingPiece(initialBoardStatus, parentMoveTree);
        }
        else
        {
            //if current piece is king;
            buildNotJumpTreeForKingPiece(initialBoardStatus, parentMoveTree);
        }
    }
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