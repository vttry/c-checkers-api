#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <CheckersGame.h>

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

TEST_CASE("Check Move 1")
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
    {
        int firstPosition[2] = {0, 2};
        int secondPosition[2] = {1, 3};
        bool ret = checkMove(patternBoard, firstPosition, secondPosition, NULL, NULL);
        REQUIRE(ret);
    }
    {
        int firstPosition[2] = {0, 2};
        int secondPosition[2] = {0, 2};
        bool ret = checkMove(patternBoard, firstPosition, secondPosition, NULL, NULL);
        REQUIRE(!ret);
    }
}