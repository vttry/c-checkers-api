#if !defined(INCLUDED_CHECKERS_GAME_H)
#define INCLUDED_CHECKERS_GAME_H

#include <stdbool.h>

#include "Player.h"
#include "Checker.h"
#include "Move.h"

#ifdef __cplusplus
extern "C"
{
#endif

    //The function that finds all possible moves from current position for a checker
    void findPossiblePieceJumps(const char board[8][8], const int startPosition[2], MoveList **list);

    //The function that builds Move Three List for current piece
    void generateJumpThreeForPiece(const char board[8][8], MoveThree *parentMoveThree);

    //The function  that generates the move three for a piece
    void generateMoveThreeForPiece(const char initialBoardStatus[8][8],
                                   const int startPosition[2],
                                   MoveThree *parentMoveThree);

    //We try to find piece-empty Pattern for kings
    bool findPieceEmptyDiagonalPattern(const char board[8][8],
                                       const int offset[2],
                                       const int startPosition[2],
                                       int startPointOfPattern[2]);

    //The function that can reset board state to inintial state
    void resetBoard(char board[8][8]);

    //build three of possible simple moves for the piece without jumps
    void buildNotJumpThreeForNotKingPiece(const char board[8][8], MoveThree *parentMoveThree);

    //Function that copy board state to destination
    void copyBoard(char destinationBoard[8][8], const char originalBoard[8][8]);

#ifdef __cplusplus
}
#endif

#endif // INCLUDED_CHECKERS_GAME_H