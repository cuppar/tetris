#ifndef _BOARD_H_
#define _BOARD_H_

// ------- Include --------

#include "Pieces.h"

// ------- Define --------

#define BOARD_LINE_WIDTH 6
#define BLOCK_SIZE 16
#define BOARD_POSITION 320
#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define MIN_VERTICAL_MARGIN 20
#define MIN_HORIZONTAL_MARGIN 20
#define PIECE_BLOCKS 5

//------------------------
// Board
//------------------------

class Board
{
public:
    Board(Pieces *pPieces, int pScreenHeight)
        : mPieces(mPieces), mScreenHeight(pScreenHeight)
    {
        InitBoard();
    };

    int GetXPosInPixels(int pPos);
    int GetYPosInPixels(int pPos);
    bool IsFreeBlock(int pX, int pY);
    bool IsPossibleMovement(int pX, int pY, int pPiece, int pRotation);
    void StorePiece(int pX, int pY, int pPiece, int pRotation);
    void DeletePossibleLines();
    bool IsGameOver();

private:
    enum
    {
        POS_FREE,
        POS_FILLED
    };                                     // POS_FREE = free position of the board; POS_FILLED = filled position of the board
    int mBoard[BOARD_WIDTH][BOARD_HEIGHT]; // Board that contains the pieces
    Pieces *mPieces;
    int mScreenHeight;

    void InitBoard();
    void DeleteLine(int pY);
};

#endif // !_BOARD_H_
