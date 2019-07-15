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

    typedef void (*GenerateThePossibleMovesForPieceFunction)(const char initialBoardStatus[8][8],
                                                              const int firstPosition[2],
                                                              MoveThreeList **moveThreeList);

    typedef bool (*CheckMoveFunction)(const char initialBoardStatus[8][8],
                                      const int firstPosition[2],
                                      const int finalPosition[2],
                                      GenerateThePossibleMovesForPieceFunction *generateThePossibleMovesForPieceFunction);

    //The function that finds all possible moves from current position for a checker
    bool findPossiblePieceJumps(const char board[8][8], const int startPosition[2], MoveList **list);

    //The function that builds Move Three List for current piece
    bool buildPieceJumpThreeList(const char board[8][8], const int startPosition[2], MoveThreeList **moveThreeList);

    //The function that generates all the possible moves that can be
    //played up to a specified number of moves.
    void generateThePossibleMovesThree(const char initialBoardStatus[8][8],
                                             const int playerColor,
                                             GenerateThePossibleMovesForPieceFunction *generateThePossibleMovesForPieceFunction,
                                             const int maximumDepthOfMuves);

    //The function that can determine if a move is valid
    bool checkMove(const char initialBoardStatus[8][8],
                   const int firstPosition[2],
                   const int finalPosition[2],
                   const GenerateThePossibleMovesForPieceFunction *generateThePossibleMovesForPieceFunction);

    //The function that can reset board state to inintial state
    void resetBoard(char board[8][8]);

    //The function  that generates the possible moves for a piece
    void generateThePossibleMovesForPiece(const char initialBoardStatus[8][8],
                                          const int firstPosition[2],
                                          MoveThreeList **moveThreeList);

#ifdef __cplusplus
}
#endif

#endif // INCLUDED_CHECKERS_GAME_H