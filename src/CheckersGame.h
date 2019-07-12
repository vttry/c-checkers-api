#if !defined(INCLUDED_CHECKERS_GAME_H)
#define INCLUDED_CHECKERS_GAME_H

#include <stdbool.h>

#include "Player.h"
#include "GameThree.h"
#include "CheckerTurn.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef bool (*CheckMoveFunction)(const char initialBoardStatus[8][8],
                                      const int firstPosition[2],
                                      const int finalPosition[2]);

    typedef void *(*GenerateThePossibleMovesForPieceFunction)(const char initialBoardStatus[8][8],
                                                              const int *firstPosition,
                                                              const char pieceType,
                                                              const CheckMoveFunction *checkMoveFunction,
                                                              CheckerTurn **possibleMoves,
                                                              int *possibleMovesCount);

    //The function that generates all the possible moves that can be
    //played up to a specified number of moves.
    GameThree *generateThePossibleMovesThree(const char initialBoardStatus[8][8],
                                             const int playerColor,
                                             const CheckMoveFunction *checkMoveFunction,
                                             const GenerateThePossibleMovesForPieceFunction *generateThePossibleMovesForPieceFunction,
                                             const int maximumDepthOfMuves);

    //The function that can determine if a move is valid
    bool checkMove(const char initialBoardStatus[8][8],
                   const int firstPosition[2],
                   const int finalPosition[2],
                   int *defietedEnemyPositions[2],
                   int *defietedEnemiesCount);

    //The function that can reset board state to inintial state
    void resetBoard(char board[8][8]);

    //The function  that generates the possible moves for a piece
    void generateThePossibleMovesForPiece(const char initialBoardStatus[8][8],
                                          const int firstPosition[2],
                                          const char pieceType,
                                          const CheckMoveFunction *checkMoveFunction,
                                          CheckerTurn **possibleMoves,
                                          int *possibleMovesCount);

#ifdef __cplusplus
}
#endif

#endif // INCLUDED_CHECKERS_GAME_H