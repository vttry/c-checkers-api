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