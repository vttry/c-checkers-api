//This example shows how to build game tree up to some depth of moves
//and print one of possible branches from initial state up to selected depth of moves

#include <stdio.h>
#include <stdlib.h>
#include <CheckersGameApi.h>

static void printBoard(char board[8][8])
{
    printf(" |A|B|C|D|E|F|G|H|\n");

    for (int i = 7; i >= 0; i--)
    {
        printf("%d", 8 - i);
        for (int j = 0; j < 8; j++)
        {
            printf("|%c", board[i][j]);
        }
        printf("|\n");
    }
}

void iterateAllNodes(GameTreeList *list, long *currentNodesCount)
{
    GameTreeList *currentGameTree = list;
    while (currentGameTree)
    {
        *currentNodesCount +=1 ;
        iterateAllNodes(currentGameTree->gameTree.children, currentNodesCount);
        currentGameTree = currentGameTree->next;
    }
}

int main(int argc, char *argv[])
{
    char board[8][8];
    resetBoardToInitialState(board);

    int maximumDepthofMoves = 7;
    printf("maximum depth of moves: %d\n", maximumDepthofMoves);

    GameTree *gameTree = generateGameTree(board, BLACK_PLAYER, generateThePossibleMovesForPiece, maximumDepthofMoves);

    if (!gameTree)
    {
        printf("I can't build gameTree\n");
        return 0;
    }

    //print some branch
    int currentStep = 1;
    GameTree *currentGameTree = gameTree;
    printf("initial state:\n");
    while (true)
    {
        printBoard(currentGameTree->board);
        if (!currentGameTree->children)
        {
            break;
        }
        printf("Step: %d\n", currentStep);
        currentStep++;
        currentGameTree = &currentGameTree->children->gameTree;
    }

    //calculate nodes count
    currentGameTree = gameTree;
    long nodesCount = 1;
    iterateAllNodes(gameTree->children, &nodesCount);
    printf("Total nodes in game three: %d\n", nodesCount);

    FreeGameTree(gameTree);
    
}