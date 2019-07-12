#include <sglib.h>
#include "CheckersGame.h"
#include "Checker.h"
#include "CaptureList.h"

static bool findCaptureAndMatchPosition(const char board[8][8],
                                        CaptureList *captureList,
                                        const int startPosition[2],
                                        const int finalPosition[2]);

//Function that check if a coordinate is in the rigth range and on a black field
static bool checkCoordinate(const int position[2])
{
    //check if position in the right range
    if (position == NULL ||
        position[0] < 0 ||
        position[0] > 7 ||
        position[1] < 0 ||
        position[1] > 7)
        return false;

    //check if position is a black field
    return (position[0] % 2 == position[1] % 2);
}

//Function that copy board state to destination
static void copyBoard(char destinationBoard[8][8], const char originalBoard[8][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            destinationBoard[i][j] = originalBoard[i][j];
        }
    }
}

//we try to make capture and match position
static bool tryToMakeCaptureAndMatchPosition(const char board[8][8],
                                             CaptureList *captureList,
                                             const int startPosition[2],
                                             const int currentPosition[2],
                                             const int capturedPosition[2],
                                             const int finalPosition[2])
{

    if (checkCoordinate(currentPosition) &&
        (board[currentPosition[0]][currentPosition[1]] == BLACK_EMPTY_FIELD &&
         board[capturedPosition[0]][capturedPosition[1]] != BLACK_EMPTY_FIELD &&
         (board[capturedPosition[0]][capturedPosition[1]] != board[startPosition[0]][startPosition[1]] ||
          board[capturedPosition[0]][capturedPosition[1]] != board[startPosition[0]][startPosition[1]])))
    {
        //make board copy
        char currentBoard[8][8];
        copyBoard(currentBoard, board);

        //make sub move. It means remove captured figure and move figure to its new position without check
        //put current figure to current cell
        currentBoard[currentPosition[0]][currentPosition[1]] = currentBoard[startPosition[0]][startPosition[1]];

        //remove figure from startpostion
        currentBoard[startPosition[0]][startPosition[1]] = BLACK_EMPTY_FIELD;

        //remove captured figure
        currentBoard[capturedPosition[0]][capturedPosition[1]] = BLACK_EMPTY_FIELD;

        //create new capture list
        CaptureList *currentCaptureList = CreateCaptureList(currentPosition, captureList);

        //recursively call makeCaptureAndMatchPosition to find end of list and match end position
        if (findCaptureAndMatchPosition(currentBoard,
                                        currentCaptureList,
                                        currentPosition,
                                        finalPosition))
        {
            captureList->next = currentCaptureList;
            return true;
        }
    }
}

//We try to find blackDiagonalBlack Pattern
bool findFigureBlackDiagonalPattern(const char board[8][8],
                                    const int offset[2],
                                    const int startPosition[2],
                                    int startPointOfPattern[2])
{
    int currentPosition[2] = {
        startPosition[0] + offset[0] * 2,
        startPosition[1] + offset[1] * 2};

    int capturedPosition[2] = {
        startPosition[0] + offset[0],
        startPosition[1] + offset[1]};

    if (checkCoordinate(currentPosition))
        return false;

    //check if captured position is white field then we recursively continue;
    if (board[currentPosition[0]][currentPosition[1]] == BLACK_EMPTY_FIELD)
    {
        return findFigureBlackDiagonalPattern(board,
                                              offset,
                                              startPosition,
                                              startPointOfPattern);
    }

    //check if captured position is cell with figure which hasen't the same color and second position is empty black field
    if (
        board[capturedPosition[0]][capturedPosition[1]] != BLACK_EMPTY_FIELD &&
        (board[capturedPosition[0]][capturedPosition[1]] != board[startPosition[0]][startPosition[1]] ||
         board[capturedPosition[0]][capturedPosition[1]] != board[startPosition[0]][startPosition[1]]))
    {
        startPointOfPattern[0] = startPosition[0];
        startPointOfPattern[1] = startPosition[1];
        return true;
    }
}

//We try to find capture, and match last jump final position with some final position
//this function can call recursively trought the tryToMakeCaptureAndMatchPosition
//it is little bit dirty but it allows to avoid code dublication
static bool findCaptureAndMatchPosition(const char board[8][8],
                                        CaptureList *captureList,
                                        const int startPosition[2],
                                        const int finalPosition[2])
{

    //we try to make capture and match current position with final position
    //if it will by succesfully then captureList will be updated
    //maximum we can find 4 capture paths for each direction
    if (board[startPosition[0]][startPosition[1]] == WHITE_CHECKER || board[startPosition[0]][startPosition[1]] == BLACK_CHECKER)
    {
        //first is right-top
        {
            int currentPosition[2] = {startPosition[0] + 2,
                                      startPosition[1] + 2};
            int capturedPosition[2] = {startPosition[0] + 1,
                                       startPosition[1] + 1};
            if (tryToMakeCaptureAndMatchPosition(board,
                                                 captureList,
                                                 startPosition,
                                                 currentPosition,
                                                 capturedPosition,
                                                 finalPosition))
            {
                return true;
            }
        }

        //left-top
        {
            int currentPosition[2] = {startPosition[0] - 2,
                                      startPosition[1] + 2};
            int capturedPosition[2] = {startPosition[0] - 1,
                                       startPosition[1] + 1};
            if (tryToMakeCaptureAndMatchPosition(board,
                                                 captureList,
                                                 startPosition,
                                                 currentPosition,
                                                 capturedPosition,
                                                 finalPosition))
            {
                return true;
            }
        }

        //left-bottom
        {
            int currentPosition[2] = {startPosition[0] - 2,
                                      startPosition[1] - 2};
            int capturedPosition[2] = {startPosition[0] - 1,
                                       startPosition[1] - 1};
            if (tryToMakeCaptureAndMatchPosition(board,
                                                 captureList,
                                                 startPosition,
                                                 currentPosition,
                                                 capturedPosition,
                                                 finalPosition))
            {
                return true;
            }
        }

        //left-bottom
        {
            int currentPosition[2] = {startPosition[0] - 2,
                                      startPosition[1] - 2};
            int capturedPosition[2] = {startPosition[0] - 1,
                                       startPosition[1] - 1};
            if (tryToMakeCaptureAndMatchPosition(board,
                                                 captureList,
                                                 startPosition,
                                                 currentPosition,
                                                 capturedPosition,
                                                 finalPosition))
            {
                return true;
            }
        }

        //right-bottom
        {
            int currentPosition[2] = {startPosition[0] + 2,
                                      startPosition[1] - 2};
            int capturedPosition[2] = {startPosition[0] + 1,
                                       startPosition[1] - 1};
            if (tryToMakeCaptureAndMatchPosition(board,
                                                 captureList,
                                                 startPosition,
                                                 currentPosition,
                                                 capturedPosition,
                                                 finalPosition))
            {
                return true;
            }
        }
    } //if (board[startPosition[0]][startPosition[1]] == WHITE_CHECKER || board[startPosition[0]][startPosition[1]] == BLACK_CHECKER)

    // //we try find capture of king for four diag
    // if (board[startPosition[0]][startPosition[1]] == WHITE_KING || board[startPosition[0]][startPosition[1]] == BLACK_KING)
    // {

    //     //first we have to get restricted offset
    //     bool hasRestrictedOffset = false;
    //     int restrictOffset[2];
    //     if (captureList->previous != NULL)
    //     {
    //         hasRestrictedOffset = true;
    //         restrictOffset[0] = (startPosition[0] - captureList->previous->position[0]) > 0 ? 1 : -1;
    //         restrictOffset[1] = (startPosition[1] - captureList->previous->position[1]) > 0 ? 1 : -1;
    //     }

    //     //first is right-top
    //     {
    //         int offset[2] = {1, 1};
    //         //check if current offset isn't restrict
    //         if (!hasRestrictedOffset || (offset[0] != restrictOffset[0] && offset[1] != restrictOffset[1]))
    //         {
    //             int startPointOfPattern[2];
    //             //try to pattern that allows to capture figure by king
    //             if (findFigureBlackDiagonalPattern(board,
    //                                                offset,
    //                                                startPosition,
    //                                                startPointOfPattern))
    //             {
    //                 int currentPosition[2] = {startPosition[0] + offset[0] * 2,
    //                                           startPosition[1] + offset[1] * 2};
    //                 int capturedPosition[2] = {startPointOfPattern[0] + offset[0],
    //                                            startPointOfPattern[1] + offset[1]};
    //                 //move ahead anf try to match recursively
    //                 if (tryToMakeCaptureAndMatchPosition(board,
    //                                                      captureList,
    //                                                      startPosition,
    //                                                      currentPosition,
    //                                                      capturedPosition,
    //                                                      finalPosition))
    //                 {
    //                     return true;
    //                 }
    //             }
    //         }
    //     }

    //     //left-top
    //     {
    //         int offset[2] = {-1, 1};
    //         //check if current offset isn't restrict
    //         if (!hasRestrictedOffset || (offset[0] != restrictOffset[0] && offset[1] != restrictOffset[1]))
    //         {
    //             int startPointOfPattern[2];
    //             //try to pattern that allows to capture figure by king
    //             if (findFigureBlackDiagonalPattern(board,
    //                                                offset,
    //                                                startPosition,
    //                                                startPointOfPattern))
    //             {
    //                 int currentPosition[2] = {startPosition[0] + offset[0] * 2,
    //                                           startPosition[1] + offset[1] * 2};
    //                 int capturedPosition[2] = {startPointOfPattern[0] + offset[0],
    //                                            startPointOfPattern[1] + offset[1]};
    //                 //move ahead anf try to match recursively
    //                 if (tryToMakeCaptureAndMatchPosition(board,
    //                                                      captureList,
    //                                                      startPosition,
    //                                                      currentPosition,
    //                                                      capturedPosition,
    //                                                      finalPosition))
    //                 {
    //                     return true;
    //                 }
    //             }
    //         }
    //     }

    //     //left-bottom
    //     {
    //         int offset[2] = {-1, -1};
    //         //check if current offset isn't restrict
    //         if (!hasRestrictedOffset || (offset[0] != restrictOffset[0] && offset[1] != restrictOffset[1]))
    //         {
    //             int startPointOfPattern[2];
    //             //try to pattern that allows to capture figure by king
    //             if (findFigureBlackDiagonalPattern(board,
    //                                                offset,
    //                                                startPosition,
    //                                                startPointOfPattern))
    //             {
    //                 int currentPosition[2] = {startPosition[0] + offset[0] * 2,
    //                                           startPosition[1] + offset[1] * 2};
    //                 int capturedPosition[2] = {startPointOfPattern[0] + offset[0],
    //                                            startPointOfPattern[1] + offset[1]};
    //                 //move ahead anf try to match recursively
    //                 if (tryToMakeCaptureAndMatchPosition(board,
    //                                                      captureList,
    //                                                      startPosition,
    //                                                      currentPosition,
    //                                                      capturedPosition,
    //                                                      finalPosition))
    //                 {
    //                     return true;
    //                 }
    //             }
    //         }
    //     }

    //     //right-bottom
    //     {
    //         int offset[2] = {1, -1};
    //         //check if current offset isn't restrict
    //         if (!hasRestrictedOffset || (offset[0] != restrictOffset[0] && offset[1] != restrictOffset[1]))
    //         {
    //             int startPointOfPattern[2];
    //             //try to pattern that allows to capture figure by king
    //             if (findFigureBlackDiagonalPattern(board,
    //                                                offset,
    //                                                startPosition,
    //                                                startPointOfPattern))
    //             {
    //                 int currentPosition[2] = {startPosition[0] + offset[0] * 2,
    //                                           startPosition[1] + offset[1] * 2};
    //                 int capturedPosition[2] = {startPointOfPattern[0] + offset[0],
    //                                            startPointOfPattern[1] + offset[1]};
    //                 //move ahead anf try to match recursively
    //                 if (tryToMakeCaptureAndMatchPosition(board,
    //                                                      captureList,
    //                                                      startPosition,
    //                                                      currentPosition,
    //                                                      capturedPosition,
    //                                                      finalPosition))
    //                 {
    //                     return true;
    //                 }
    //             }
    //         }
    //     }

    //     //so we cant find captured piece, but for the kings we have to check condition
    //     // when king capture piece and it can move forward and try to capture figures on dioganals
    //     if (hasRestrictedOffset)
    //     {
    //         int currentPosition[2] = {startPosition[0] - restrictOffset[0] * 2,
    //                                   startPosition[1] - restrictOffset[1] * 2};

    //         //check if current field is valid
    //         if (checkCoordinate(currentPosition)) return false;

    //         //check if current field is empty
    //         if(board[currentPosition[0], currentPosition[1]] == BLACK_EMPTY_FIELD)
    //              {
    //                 //try to capture diagonals

    //                 //make board copy
    //                 char currentBoard[8][8];
    //                 copyBoard(currentBoard, board);

    //                 if(findCaptureAndMatchPosition(currentBoard,
    //                                             captureList,
    //                                             const int startPosition[2],
    //                                             const int finalPosition[2])
    //              }
    //     }
    // }

    return false;
}

bool checkMove(const char initialBoardStatus[8][8],
               const int firstPosition[2],
               const int finalPosition[2],
               int *defietedEnemyPositions[2],
               int *defietedEnemiesCount)
{
    //check if start and end positions is black fields
    if (!checkCoordinate(firstPosition) || !checkCoordinate(firstPosition))
        return false;
    CaptureList *captureList = CreateCaptureList(firstPosition, NULL);
    return findCaptureAndMatchPosition(initialBoardStatus,
                                       captureList,
                                       firstPosition,
                                       finalPosition);
}

void resetBoard(char board[8][8])
{

    //fill board with white fields
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            board[i][j * 2 + 1 - i % 2] = WHITE_FIELD;
        }
    }

    //fill board with white chekers
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            board[i][j * 2 + i % 2] = WHITE_CHECKER;
        }
    }

    //fill board with Black Fields
    for (int i = 3; i < 5; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            board[i][j * 2 + i % 2] = BLACK_EMPTY_FIELD;
        }
    }

    //fill board with black chekers
    for (int i = 5; i < 8; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            board[i][j * 2 + i % 2] = BLACK_CHECKER;
        }
    }
}