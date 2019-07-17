#if !defined(INCLUDED_CHECKERSGAMEAPI)
#define INCLUDED_CHECKERSGAMEAPI

#include "GameThree.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct BoardList
    {
        char board[8][8];
        struct BoardList *next;
    } BoardList;

    typedef BoardList *(*GenerateThePossibleMovesForPieceFunction)(const char initialBoardStatus[8][8],
                                                                   const int startPosition[2]);

    typedef bool (*CheckMoveFunction)(const char initialBoardStatus[8][8],
                                      const int startPosition[2],
                                      const int finalPosition[2],
                                      GenerateThePossibleMovesForPieceFunction *generateThePossibleMovesForPieceFunction);

    //The function that can determine if a move is valid
    bool checkMove(const char initialBoardStatus[8][8],
                   const int startPosition[2],
                   const int finalPosition[2],
                   const GenerateThePossibleMovesForPieceFunction generateThePossibleMovesForPieceFunction);

    //The function that  generates the possible moves for a piece
    BoardList *generateThePossibleMovesForPiece(const char initialBoardStatus[8][8],
                                                const int startPosition[2]);

    //The function that generates all the possible moves that can be
    //played up to a specified number of moves.
    GameThree *generateGameThree(const char initialBoardStatus[8][8],
                                 const int playerColor,
                                 GenerateThePossibleMovesForPieceFunction generateThePossibleMovesForPieceFunction,
                                 const int maximumDepthOfMuves);

    //The function that reset board to initial state
    void resetBoardToInitialState(char board[8][8]);

#ifdef __cplusplus
}
#endif

#endif // INCLUDED_CHECKERSGAMEAPI
