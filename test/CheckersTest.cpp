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
        int firstPosition[2] = {5, 3};

        MoveList *list = NULL;
        findPossiblePieceJumps(board, firstPosition, &list);
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
        int firstPosition[2] = {4, 4};

        MoveList *list = NULL;
        findPossiblePieceJumps(board, firstPosition, &list);
        int count = 0;
        MoveList *currentItem = NULL;
        SGLIB_LIST_MAP_ON_ELEMENTS(struct MoveList, list, currentItem, next, { count++; });
        SGLIB_LIST_MAP_ON_ELEMENTS(struct MoveList, list, currentItem, next, { free(currentItem); });

        REQUIRE(count == 2);
    }

    {
        int firstPosition[2] = {5, 1};

        MoveList *list = NULL;
        findPossiblePieceJumps(board, firstPosition, &list);
        int count = 0;
        MoveList *currentItem = NULL;
        SGLIB_LIST_MAP_ON_ELEMENTS(struct MoveList, list, currentItem, next, { count++; });
        SGLIB_LIST_MAP_ON_ELEMENTS(struct MoveList, list, currentItem, next, { free(currentItem); });

        REQUIRE(count == 0);
    }
}

TEST_CASE("Check Moves Treelist building")
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
        int firstPosition[2] = {4, 4};

        MoveThreeList *threeList = NULL;
        buildPieceJumpThreeList(board, firstPosition, &threeList);
        int count = 0;
        MoveThreeList *currentItem = NULL;
        SGLIB_LIST_MAP_ON_ELEMENTS(struct MoveThreeList, threeList, currentItem, next, {
            count++;
            free(currentItem);
        });

        REQUIRE(count == 2);
    }

    {
        int firstPosition[2] = {5, 3};

        MoveThreeList *threeList = NULL;
        buildPieceJumpThreeList(board, firstPosition, &threeList);
        int count = 0;
        MoveThreeList *currentItem = NULL;
        SGLIB_LIST_MAP_ON_ELEMENTS(struct MoveThreeList, threeList, currentItem, next, {
            count++;
            free(currentItem);
        });

        REQUIRE(count == 1);
    }
}