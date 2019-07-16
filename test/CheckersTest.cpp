#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <CheckersGame.h>
#include <sglib.h>

static bool compareBoards(const char board1[8][8], const char board2[8][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board1[i][j] != board2[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

TEST_CASE("Resetted board should be equal the pattern")
{
    char patternBoard[8][8] = {
        {'1', ' ', '1', ' ', '1', ' ', '1', ' '},
        {' ', '1', ' ', '1', ' ', '1', ' ', '1'},
        {'1', ' ', '1', ' ', '1', ' ', '1', ' '},
        {' ', '#', ' ', '#', ' ', '#', ' ', '#'},
        {'#', ' ', '#', ' ', '#', ' ', '#', ' '},
        {' ', '3', ' ', '3', ' ', '3', ' ', '3'},
        {'3', ' ', '3', ' ', '3', ' ', '3', ' '},
        {' ', '3', ' ', '3', ' ', '3', ' ', '3'}};
    char secondBoard[8][8];
    resetBoard(secondBoard);
    REQUIRE(compareBoards(secondBoard, patternBoard));
}

static bool compareCoordinates(int c1[2], int c2[2])
{
    return (c1[0] == c2[0] && c1[1] == c2[1]);
}

TEST_CASE("Check Moves")
{
    char board[8][8] = {
        {'1', ' ', '1', ' ', '1', ' ', '1', ' '},
        {' ', '1', ' ', '1', ' ', '1', ' ', '1'},
        {'1', ' ', '1', ' ', '1', ' ', '1', ' '},
        {' ', '#', ' ', '#', ' ', '#', ' ', '#'},
        {'#', ' ', '#', ' ', '1', ' ', '#', ' '},
        {' ', '3', ' ', '3', ' ', '3', ' ', '3'},
        {'3', ' ', '#', ' ', '#', ' ', '#', ' '},
        {' ', '3', ' ', '3', ' ', '3', ' ', '3'}};
    {
        int startPosition[2] = {5, 3};

        MoveList *list = NULL;
        findPossiblePieceJumps(board, startPosition, &list);
        int count = 0;
        MoveList *currentItem = NULL;
        SGLIB_LIST_MAP_ON_ELEMENTS(struct MoveList, list, currentItem, next, { count++; });

        REQUIRE(count == 1);

        int recuiredFinalPosition[2] = {3, 5};
        int requiredCapturedPosition[2] = {4, 4};
        REQUIRE(compareCoordinates(list->Move.capturedPosition, requiredCapturedPosition));
        REQUIRE(compareCoordinates(list->Move.finalPosition, recuiredFinalPosition));
        SGLIB_LIST_MAP_ON_ELEMENTS(struct MoveList, list, currentItem, next, { free(currentItem); });
    }

    {
        int startPosition[2] = {4, 4};

        MoveList *list = NULL;
        findPossiblePieceJumps(board, startPosition, &list);
        int count = 0;
        MoveList *currentItem = NULL;
        SGLIB_LIST_MAP_ON_ELEMENTS(struct MoveList, list, currentItem, next, { count++; });
        SGLIB_LIST_MAP_ON_ELEMENTS(struct MoveList, list, currentItem, next, { free(currentItem); });

        REQUIRE(count == 2);
    }

    {
        int startPosition[2] = {5, 1};

        MoveList *list = NULL;
        findPossiblePieceJumps(board, startPosition, &list);
        int count = 0;
        MoveList *currentItem = NULL;
        SGLIB_LIST_MAP_ON_ELEMENTS(struct MoveList, list, currentItem, next, { count++; });
        SGLIB_LIST_MAP_ON_ELEMENTS(struct MoveList, list, currentItem, next, { free(currentItem); });

        REQUIRE(count == 0);
    }
}

TEST_CASE("Check Jumps Treelist building")
{
    char board[8][8] = {
        {'1', ' ', '1', ' ', '1', ' ', '1', ' '},
        {' ', '1', ' ', '1', ' ', '1', ' ', '1'},
        {'1', ' ', '1', ' ', '1', ' ', '1', ' '},
        {' ', '#', ' ', '#', ' ', '#', ' ', '#'},
        {'#', ' ', '#', ' ', '1', ' ', '#', ' '},
        {' ', '3', ' ', '3', ' ', '3', ' ', '3'},
        {'3', ' ', '#', ' ', '#', ' ', '#', ' '},
        {' ', '3', ' ', '3', ' ', '3', ' ', '3'}};
    {
        int startPosition[2] = {4, 4};

        MoveThree jumpThree;
        jumpThree.chidren = NULL;
        jumpThree.parent = NULL;
        jumpThree.Move.finalPosition[0] = startPosition[0];
        jumpThree.Move.finalPosition[1] = startPosition[1];
        jumpThree.Move.isJump = false;

        generateJumpThreeForPiece(board, &jumpThree);
        int count = 0;
        MoveThreeList *currentItem = NULL;
        SGLIB_LIST_MAP_ON_ELEMENTS(struct MoveThreeList, jumpThree.chidren, currentItem, next, {
            count++;
            free(currentItem);
        });

        REQUIRE(count == 2);
    }

    {
        int startPosition[2] = {5, 3};

        MoveThree jumpThree;
        jumpThree.chidren = NULL;
        jumpThree.parent = NULL;
        jumpThree.Move.finalPosition[0] = startPosition[0];
        jumpThree.Move.finalPosition[1] = startPosition[1];
        generateJumpThreeForPiece(board, &jumpThree);
        int count = 0;
        MoveThreeList *currentItem = NULL;
        SGLIB_LIST_MAP_ON_ELEMENTS(struct MoveThreeList, jumpThree.chidren, currentItem, next, {
            count++;
            free(currentItem);
        });

        REQUIRE(count == 1);
    }
}

TEST_CASE("Check simple moves Treelist building")
{
    char board[8][8] = {
        {'1', ' ', '1', ' ', '1', ' ', '1', ' '},
        {' ', '1', ' ', '1', ' ', '1', ' ', '1'},
        {'1', ' ', '1', ' ', '1', ' ', '1', ' '},
        {' ', '#', ' ', '#', ' ', '#', ' ', '#'},
        {'#', ' ', '#', ' ', '1', ' ', '#', ' '},
        {' ', '3', ' ', '#', ' ', '#', ' ', '3'},
        {'3', ' ', '#', ' ', '#', ' ', '#', ' '},
        {' ', '3', ' ', '3', ' ', '3', ' ', '3'}};
    {
        int startPosition[2] = {0, 0};

        MoveThree jumpThree;
        jumpThree.chidren = NULL;
        jumpThree.parent = NULL;
        jumpThree.Move.finalPosition[0] = startPosition[0];
        jumpThree.Move.finalPosition[1] = startPosition[1];
        buildNotJumpThreeForNotKingPiece(board, &jumpThree);
        int count = 0;
        MoveThreeList *currentItem = NULL;
        SGLIB_LIST_MAP_ON_ELEMENTS(struct MoveThreeList, jumpThree.chidren, currentItem, next, {
            count++;
            free(currentItem);
        });

        REQUIRE(count == 0);
    }

    {
        int startPosition[2] = {2, 0};

        MoveThree jumpThree;
        jumpThree.chidren = NULL;
        jumpThree.parent = NULL;
        jumpThree.Move.finalPosition[0] = startPosition[0];
        jumpThree.Move.finalPosition[1] = startPosition[1];
        buildNotJumpThreeForNotKingPiece(board, &jumpThree);
        int count = 0;
        MoveThreeList *currentItem = NULL;
        SGLIB_LIST_MAP_ON_ELEMENTS(struct MoveThreeList, jumpThree.chidren, currentItem, next, {
            count++;
            free(currentItem);
        });

        REQUIRE(count == 1);
    }

    {
        int startPosition[2] = {4, 4};

        MoveThree jumpThree;
        jumpThree.chidren = NULL;
        jumpThree.parent = NULL;
        jumpThree.Move.finalPosition[0] = startPosition[0];
        jumpThree.Move.finalPosition[1] = startPosition[1];
        buildNotJumpThreeForNotKingPiece(board, &jumpThree);
        int count = 0;
        MoveThreeList *currentItem = NULL;
        SGLIB_LIST_MAP_ON_ELEMENTS(struct MoveThreeList, jumpThree.chidren, currentItem, next, {
            count++;
            free(currentItem);
        });

        REQUIRE(count == 2);
    }
}

TEST_CASE("Find piece-empty diagonal pattern")
{
    char board[8][8] = {
        //0    1    2    3    4    5    6    7
        {'1', ' ', '1', ' ', '1', ' ', '1', ' '},  //0
        {' ', '3', ' ', '1', ' ', '#', ' ', '1'},  //1
        {'#', ' ', '1', ' ', '3', ' ', '1', ' '},  //2
        {' ', '#', ' ', '#', ' ', '#', ' ', '#'},  //3
        {'#', ' ', '#', ' ', '1', ' ', '#', ' '},  //4
        {' ', '#', ' ', '#', ' ', '#', ' ', '3'},  //5
        {'2', ' ', '#', ' ', '2', ' ', '#', ' '},  //6
        {' ', '#', ' ', '3', ' ', '4', ' ', '3'}}; //7
    {
        int startPosition[2] = {6, 0};
        int offset[2] = {-1, 1};
        int startPointOfPattern[2];
        bool ret = findPieceEmptyDiagonalPattern(board,
                                                 offset,
                                                 startPosition,
                                                 startPointOfPattern);

        REQUIRE(ret);
        REQUIRE(startPointOfPattern[0] == 2);
        REQUIRE(startPointOfPattern[1] == 4);
    }

    {
        int startPosition[2] = {7, 5};
        int offset[2] = {-1, -1};
        int startPointOfPattern[2];
        bool ret = findPieceEmptyDiagonalPattern(board,
                                                 offset,
                                                 startPosition,
                                                 startPointOfPattern);

        REQUIRE(ret);
        REQUIRE(startPointOfPattern[0] == 6);
        REQUIRE(startPointOfPattern[1] == 4);
    }
}

TEST_CASE("Generate possible moves for Kings without jumps")
{
    char board[8][8] = {
        //0    1    2    3    4    5    6    7
        {'1', ' ', '1', ' ', '1', ' ', '1', ' '},  //0
        {' ', '3', ' ', '1', ' ', '1', ' ', '1'},  //1
        {'#', ' ', '1', ' ', '1', ' ', '1', ' '},  //2
        {' ', '#', ' ', '#', ' ', '#', ' ', '#'},  //3
        {'#', ' ', '#', ' ', '4', ' ', '#', ' '},  //4
        {' ', '#', ' ', '#', ' ', '#', ' ', '3'},  //5
        {'2', ' ', '#', ' ', '3', ' ', '#', ' '},  //6
        {' ', '#', ' ', '3', ' ', '4', ' ', '3'}}; //7
    {
        int startPosition[2] = {6, 0};

        MoveThree moveThree;
        generateMoveThreeForPiece(board, startPosition, &moveThree);
        int count = 0;
        MoveThreeList *currentItem = NULL;
        SGLIB_LIST_MAP_ON_ELEMENTS(struct MoveThreeList, moveThree.chidren, currentItem, next, {
            count++;
        });
        FreeMoveThreeList(currentItem);
        REQUIRE(count == 4);
    }

    {
        int startPosition[2] = {7, 5};

        MoveThree moveThree;
        generateMoveThreeForPiece(board, startPosition, &moveThree);
        int count = 0;
        MoveThreeList *currentItem = NULL;
        SGLIB_LIST_MAP_ON_ELEMENTS(struct MoveThreeList, moveThree.chidren, currentItem, next, {
            count++;
        });
        FreeMoveThreeList(currentItem);
        REQUIRE(count == 1);
    }

    {
        int startPosition[2] = {4, 4};

        MoveThree moveThree;
        generateMoveThreeForPiece(board, startPosition, &moveThree);
        int count = 0;
        MoveThreeList *currentItem = NULL;
        SGLIB_LIST_MAP_ON_ELEMENTS(struct MoveThreeList, moveThree.chidren, currentItem, next, {
            count++;
        });
        FreeMoveThreeList(currentItem);
        REQUIRE(count == 7);
    }
}

TEST_CASE("Generate possible moves with jumps")
{
    char board[8][8] = {
        //0    1    2    3    4    5    6    7
        {'1', ' ', '#', ' ', '1', ' ', '1', ' '},  //0
        {' ', '1', ' ', '#', ' ', '1', ' ', '1'},  //1
        {'3', ' ', '1', ' ', '1', ' ', '1', ' '},  //2
        {' ', '#', ' ', '#', ' ', '#', ' ', '#'},  //3
        {'#', ' ', '#', ' ', '4', ' ', '1', ' '},  //4
        {' ', '#', ' ', '1', ' ', '#', ' ', '3'},  //5
        {'2', ' ', '#', ' ', '4', ' ', '#', ' '},  //6
        {' ', '#', ' ', '3', ' ', '4', ' ', '3'}}; //7
    {
        int startPosition[2] = {2, 0};

        MoveThree moveThree;
        generateMoveThreeForPiece(board, startPosition, &moveThree);
        int count = 0;
        SGLIB_LIST_MAP_ON_ELEMENTS(struct MoveThreeList, moveThree.chidren, currentItem, next, {
            count++;
        });
        REQUIRE(count == 1);
        REQUIRE(moveThree.chidren);
        REQUIRE(moveThree.chidren->moveThree.chidren->moveThree.chidren == NULL);
        REQUIRE(moveThree.chidren->moveThree.chidren->moveThree.Move.finalPosition[0] == 3);
        REQUIRE(moveThree.chidren->moveThree.chidren->moveThree.Move.finalPosition[1] == 5);
        
    }

    {
        int startPosition[2] = {6, 4};

        MoveThree moveThree;
        generateMoveThreeForPiece(board, startPosition, &moveThree);
        int count = 0;
        MoveThreeList *currentItem = NULL;
        SGLIB_LIST_MAP_ON_ELEMENTS(struct MoveThreeList, moveThree.chidren, currentItem, next, {
            count++;
        });
        FreeMoveThreeList(currentItem);
        REQUIRE(count == 3);
    }
}