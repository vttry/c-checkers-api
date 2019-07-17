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
        //check if finalPosition has the same color as startPosition on intial board state
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

//calculate checkers count
static int calculateCheckersCount(const char board[8][8], const int playerColor)
{
    int currentCoordinate[2];
    int checkersCount = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            currentCoordinate[0] = i;
            currentCoordinate[1] = j * 2 + i % 2;
            char currentFigure = board[currentCoordinate[0]][currentCoordinate[1]];
            if (
                (playerColor == BLACK_PLAYER &&
                 (currentFigure == BLACK_CHECKER || currentFigure == BLACK_KING)) ||
                (playerColor == WHITE_PLAYER &&
                 (currentFigure == WHITE_CHECKER || currentFigure == WHITE_KING))

            )
            {
                checkersCount++;
            }
        }
    }
    return checkersCount;
}

//calculate kings count
static int calculateKingsCount(const char board[8][8], const int playerColor)
{
    int currentCoordinate[2];
    int kingsCount = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            currentCoordinate[0] = i;
            currentCoordinate[1] = j * 2 + i % 2;
            char currentFigure = board[currentCoordinate[0]][currentCoordinate[1]];
            if (
                (playerColor == BLACK_PLAYER &&
                 (currentFigure == BLACK_KING)) ||
                (playerColor == WHITE_PLAYER &&
                 (currentFigure == WHITE_KING)))
            {
                kingsCount++;
            }
        }
    }
    return kingsCount;
}

//build game three node, this function calls recursively
static void buildGameThreeNode(const int currentdepthOfMuves,
                               const int moveRemains,
                               const int playerColor,
                               const GenerateThePossibleMovesForPieceFunction generateThePossibleMovesForPieceFunction,
                               GameThree *parentGameThree)
{
    //check current depth
    if (currentdepthOfMuves == 0)
    {
        return;
    }

    int checkersCount = calculateCheckersCount(parentGameThree->board, playerColor);

    //check loose condition
    if (checkersCount == 0)
    {
        return;
    }

    int enemyColor = playerColor == WHITE_PLAYER ? BLACK_PLAYER : WHITE_PLAYER;
    int enemyCheckersCount = calculateCheckersCount(parentGameThree->board, enemyColor);

    //check loose condition with kings
    if (moveRemains == 0 && checkersCount == 3 && enemyCheckersCount == 1)
    {
        if (calculateKingsCount(parentGameThree->board, playerColor) == 3 ||
            calculateKingsCount(parentGameThree->board, enemyColor) == 1)
        {
            return;
        }
    }

    //iterate over all pieces and try to find possible moves
    //we have to create two lists - captureBoardList, and notCaptureBoardList
    //becase we can't move if we can capture
    char currentFigure;
    int currentCoordinate[2];
    BoardList *captureBoardList = NULL;
    BoardList *notCaptureBoardList = NULL;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            currentCoordinate[0] = i;
            currentCoordinate[1] = j * 2 + i % 2;
            currentFigure = parentGameThree->board[currentCoordinate[0]][currentCoordinate[1]];
            if (
                (playerColor == BLACK_PLAYER &&
                 (currentFigure == BLACK_CHECKER ||
                  currentFigure == BLACK_KING)) ||
                (playerColor == WHITE_PLAYER &&
                 (currentFigure == WHITE_CHECKER ||
                  currentFigure == WHITE_KING)))
            {
                //get possible moves for current piece
                BoardList *currentBoardList = generateThePossibleMovesForPieceFunction(parentGameThree->board, currentCoordinate);

                if (!currentBoardList)
                    continue;

                if (calculateCheckersCount(currentBoardList->board, enemyColor) < enemyCheckersCount)
                {
                    SGLIB_LIST_CONCAT(struct BoardList, captureBoardList, currentBoardList, next);
                }
                else
                {
                    SGLIB_LIST_CONCAT(struct BoardList, notCaptureBoardList, currentBoardList, next);
                }
            }
        }
    }

    BoardList *boardList = NULL;
    int secondepthOfMuves = currentdepthOfMuves - 1;
    int secondMoveRemains = moveRemains;

    if (captureBoardList)
    {
        //free not captured boardlist
        {
            BoardList *currentBoardList = NULL;
            SGLIB_LIST_MAP_ON_ELEMENTS(struct BoardList, notCaptureBoardList, currentBoardList, next, {
                free(currentBoardList);
            });
        }
        boardList = captureBoardList;
        secondMoveRemains = 15;
    }
    else
    {
        boardList = notCaptureBoardList;

        //check loose condition with kings
        if (checkersCount == 3 && enemyCheckersCount == 1)
        {
            if (calculateKingsCount(parentGameThree->board, playerColor) == 3 &&
                calculateKingsCount(parentGameThree->board, enemyColor) == 1)
            {
                secondMoveRemains--;
            }
        }
    }

    //iterate over board list and create nodes recursively
    BoardList *currentBoardList = NULL;
    SGLIB_LIST_MAP_ON_ELEMENTS(struct BoardList, boardList, currentBoardList, next, {
        GameThreeList *gameThreeList = (GameThreeList *)malloc(sizeof(GameThreeList));
        copyBoard(gameThreeList->gameThree.board, currentBoardList->board);
        gameThreeList->gameThree.children = NULL;
        gameThreeList->next = NULL;

        //free alloceted memory
        free(currentBoardList);
 
        //add new node to parent gameThree
        SGLIB_LIST_ADD(struct GameThreeList, parentGameThree->children, gameThreeList, next);

        //build game Three
        buildGameThreeNode(secondepthOfMuves,
                           secondMoveRemains,
                           enemyColor,
                           generateThePossibleMovesForPieceFunction,
                           &gameThreeList->gameThree);
    });
}

GameThree *generateGameThree(const char initialBoardStatus[8][8],
                             const int playerColor,
                             const GenerateThePossibleMovesForPieceFunction generateThePossibleMovesForPieceFunction,
                             const int maximumDepthOfMuves)
{
    //we allocate memory for first gameThreeNode
    GameThree *gameThree = (GameThree *)malloc(sizeof(GameThree));
    copyBoard(gameThree->board, initialBoardStatus);
    gameThree->children = NULL;

    // set move remains count for 3x1 king lose condition
    int moveRemains = 15;

    //build game Three
    buildGameThreeNode(maximumDepthOfMuves,
                       moveRemains,
                       playerColor,
                       generateThePossibleMovesForPieceFunction,
                       gameThree);

    if (gameThree->children)
    {
        return gameThree;
    }
    else
    {
        free(gameThree);
        return NULL;
    }
}