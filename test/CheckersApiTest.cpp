#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <CheckersGameApi.h>
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
    resetBoardToInitialState(secondBoard);
    REQUIRE(compareBoards(secondBoard, patternBoard));
}

TEST_CASE("Build board list and check")
{
    char board[8][8] = {
        //0    1    2    3    4    5    6    7
        {'1', ' ', '1', ' ', '1', ' ', '1', ' '},  //0
        {' ', '1', ' ', '1', ' ', '1', ' ', '1'},  //1
        {'1', ' ', '1', ' ', '1', ' ', '1', ' '},  //2
        {' ', '#', ' ', '#', ' ', '#', ' ', '#'},  //3
        {'#', ' ', '#', ' ', '#', ' ', '#', ' '},  //4
        {' ', '3', ' ', '3', ' ', '3', ' ', '3'},  //5
        {'3', ' ', '3', ' ', '3', ' ', '3', ' '},  //6
        {' ', '3', ' ', '3', ' ', '3', ' ', '3'}}; //7

    char secondBoard[8][8] = {
        //0    1    2    3    4    5    6    7
        {'1', ' ', '1', ' ', '1', ' ', '1', ' '},  //0
        {' ', '1', ' ', '1', ' ', '1', ' ', '1'},  //1
        {'#', ' ', '1', ' ', '1', ' ', '1', ' '},  //2
        {' ', '1', ' ', '#', ' ', '#', ' ', '#'},  //3
        {'#', ' ', '#', ' ', '#', ' ', '#', ' '},  //4
        {' ', '3', ' ', '3', ' ', '3', ' ', '3'},  //5
        {'3', ' ', '3', ' ', '3', ' ', '3', ' '},  //6
        {' ', '3', ' ', '3', ' ', '3', ' ', '3'}}; //7

    int position[2] = {2, 0};
    BoardList *boardList = generateThePossibleMovesForPiece(board, position);

    REQUIRE(boardList);
    BoardList *currentItem = NULL;
    int count = 0;
    SGLIB_LIST_MAP_ON_ELEMENTS(struct BoardList, boardList, currentItem, next, {
        count++;
    });
    REQUIRE(count == 1);
    REQUIRE(compareBoards(boardList->board, secondBoard));
    SGLIB_LIST_MAP_ON_ELEMENTS(struct BoardList, boardList, currentItem, next, {
        free(currentItem);
    });
}

TEST_CASE("CheckMove")
{
    char board[8][8] = {
        //0    1    2    3    4    5    6    7
        {'1', ' ', '1', ' ', '1', ' ', '1', ' '},  //0
        {' ', '1', ' ', '1', ' ', '1', ' ', '1'},  //1
        {'1', ' ', '1', ' ', '1', ' ', '1', ' '},  //2
        {' ', '#', ' ', '#', ' ', '#', ' ', '#'},  //3
        {'#', ' ', '#', ' ', '1', ' ', '#', ' '},  //4
        {' ', '3', ' ', '3', ' ', '3', ' ', '3'},  //5
        {'3', ' ', '3', ' ', '3', ' ', '3', ' '},  //6
        {' ', '3', ' ', '3', ' ', '3', ' ', '3'}}; //7
    {
        int startPosition[2] = {5, 3};
        int finalPosition[2] = {3, 5};
        bool ret = checkMove(board, startPosition, finalPosition, generateThePossibleMovesForPiece);
        REQUIRE(ret == true);
    }
    {
        int startPosition[2] = {5, 3};
        int finalPosition[2] = {3, 1};
        bool ret = checkMove(board, startPosition, finalPosition, generateThePossibleMovesForPiece);
        REQUIRE(ret == false);
    }
}

TEST_CASE("Check Buid Game Three")
{
    {
        char board[8][8] = {
            //0    1    2    3    4    5    6    7
            {'1', ' ', '1', ' ', '1', ' ', '1', ' '},  //0
            {' ', '1', ' ', '1', ' ', '1', ' ', '1'},  //1
            {'1', ' ', '1', ' ', '1', ' ', '1', ' '},  //2
            {' ', '#', ' ', '#', ' ', '#', ' ', '#'},  //3
            {'#', ' ', '#', ' ', '#', ' ', '#', ' '},  //4
            {' ', '3', ' ', '3', ' ', '3', ' ', '3'},  //5
            {'3', ' ', '3', ' ', '3', ' ', '3', ' '},  //6
            {' ', '3', ' ', '3', ' ', '3', ' ', '3'}}; //7

        struct GameThree *gameThree = generateGameThree(board, WHITE_PLAYER, generateThePossibleMovesForPiece, 1);

        REQUIRE(gameThree);

        GameThreeList *currentGameThreeList = NULL;
        int count = 0;
        SGLIB_LIST_MAP_ON_ELEMENTS(struct GameThreeList, gameThree->children, currentGameThreeList, next, {
            count++;
        });

        REQUIRE(count == 7);
    }

    {
        char board[8][8] = {
            //0    1    2    3    4    5    6    7
            {'#', ' ', '#', ' ', '#', ' ', '#', ' '},  //0
            {' ', '1', ' ', '#', ' ', '#', ' ', '#'},  //1
            {'#', ' ', '#', ' ', '#', ' ', '#', ' '},  //2
            {' ', '#', ' ', '#', ' ', '#', ' ', '#'},  //3
            {'#', ' ', '#', ' ', '#', ' ', '#', ' '},  //4
            {' ', '3', ' ', '3', ' ', '3', ' ', '3'},  //5
            {'3', ' ', '3', ' ', '3', ' ', '3', ' '},  //6
            {' ', '3', ' ', '3', ' ', '3', ' ', '3'}}; //7

        struct GameThree *gameThree = generateGameThree(board, WHITE_PLAYER, generateThePossibleMovesForPiece, 2);

        REQUIRE(gameThree);

        GameThreeList *currentGameThreeList = NULL;
        int count = 0;
        SGLIB_LIST_MAP_ON_ELEMENTS(struct GameThreeList, gameThree->children, currentGameThreeList, next, {
            count++;
        });
        REQUIRE(count == 2);

        //next move must have 7 moves
        int nextCount = 0;
        SGLIB_LIST_MAP_ON_ELEMENTS(struct GameThreeList, gameThree->children->gameThree.children, currentGameThreeList, next, {
            nextCount++;
        });

        REQUIRE(nextCount == 7);
    }
}