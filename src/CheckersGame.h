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
    //Function that check if a coordinate is in the rigth range and on a black field
    bool checkCoordinate(const int position[2]);

    //check if checker is black
    bool isBlackPiece(const char checker);

    //return piece by position
    const char getPieceByPosition(const char board[8][8], const int position[2]);

    //The function that finds all possible moves from current position for a checker
    void findPossiblePieceJumps(const char board[8][8], const int startPosition[2], MoveList **list);

    //The function that builds Move Tree List for current piece
    void generateJumpTreeForPiece(const char board[8][8], MoveTree *parentMoveTree);

    //The function  that generates the move tree for a piece
    void generateMoveTreeForPiece(const char initialBoardStatus[8][8],
                                   const int startPosition[2],
                                   MoveTree *parentMoveTree);

    //We try to find piece-empty Pattern for kings
    bool findPieceEmptyDiagonalPattern(const char board[8][8],
                                       const int offset[2],
                                       const int startPosition[2],
                                       int startPointOfPattern[2]);

    //The function that can reset board state to inintial state
    void resetBoard(char board[8][8]);

    //build tree of possible simple moves for the piece without jumps
    void buildNotJumpTreeForNotKingPiece(const char board[8][8], MoveTree *parentMoveTree);

    //Function that copy board state to destination
    void copyBoard(char destinationBoard[8][8], const char originalBoard[8][8]);

#ifdef __cplusplus
}
#endif

#endif // INCLUDED_CHECKERS_GAME_H