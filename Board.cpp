#include "Board.h"
// #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

/*
===================================
Init the board blocks with free positions
===================================
*/
void Board::InitBoard()
{
    for (int i = 0; i < BOARD_WIDTH; ++i)
        for (int j = 0; j < BOARD_HEIGHT; ++j)
            mBoard[i][j] = POS_FREE;
}

/*

======================================
Store a piece in the board by filling the blocks

Parameters:

>> pX: Horizontal position in blocks
>> pY: Vertical position in blocks
>> pPiece: Piece to draw
>> pRotation: 1 of the 4 possible rotations
======================================
*/
void Board::StorePiece(int pX, int pY, int pPiece, int pRotation)
{
    for (int i1 = pX, i2 = 0; i1 < pX + PIECE_BLOCKS; ++i1, ++i2)
        for (int j1 = pY, j2 = 0; j1 < pY + PIECE_BLOCKS; ++j1, ++j2)
            if (mPieces->GetBlockType(pPiece, pRotation, j2, i2) != 0)
                mBoard[i1][j1] = POS_FILLED;
}

/*
======================================
Check if the game is over becase a piece have achived the upper position

Returns true or false
======================================
*/
bool Board::IsGameOver()
{
    // If the first line has blocks, then, game over
    for (int i = 0; i < BOARD_WIDTH; ++i)
        if (mBoard[i][0] == POS_FILLED)
            return true;
    return false;
}

/*
======================================
Delete a line of the board by moving all above lines down

Parameters:

>> pY: Vertical position in blocks of the line to delete
======================================
*/
void Board::DeleteLine(int pY)
{
    for (int r = pY; r > 0; --r)
        for (int c = 0; c < BOARD_WIDTH; ++c)
            mBoard[c][r] = mBoard[c][r - 1];
}

/*
======================================
Delete all the lines that should be removed
======================================
*/
void Board::DeletePossibleLines()
{
    for (int r = 0; r < BOARD_HEIGHT; ++r)
    {
        int c = 0;
        while (c < BOARD_WIDTH)
        {
            if (mBoard[c][r] != POS_FILLED)
                break;
            ++c;
        }
        if (c == BOARD_WIDTH)
            DeleteLine(r);
    }
}

/*
======================================
Returns 1 (true) if the this block of the board is empty, 0 if it is filled

Parameters:

>> pX: Horizontal position in blocks
>> pY: Vertical position in blocks
======================================
*/
bool Board::IsFreeBlock(int pX, int pY)
{
    if (mBoard[pX][pY] == POS_FREE)
        return true;
    else
        return false;
}

/*
======================================
Returns the horizontal position (in pixels) of the block given like parameter

Parameters:

>> pPos: Horizontal position of the block in the board
======================================
*/
int Board::GetXPosInPixels(int pPos)
{
    return (BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2))) + pPos * BLOCK_SIZE;
}

/*
======================================
Returns the vertical position (in pixels) of the block given like parameter

Parameters:

>> pPos: Horizontal position of the block in the board
======================================
*/
int Board::GetYPosInPixels(int pPos)
{
    return (mScreenHeight - (BOARD_HEIGHT * BLOCK_SIZE)) + (pPos * BLOCK_SIZE);
}

/*
======================================
Check if the piece can be stored at this position without any collision
Returns true if the movement is possible, false if it not possible

Parameters:

>> pX: Horizontal position in blocks
>> pY: Vertical position in blocks
>> pPiece: Piece to draw
>> pRotation: 1 of the 4 possible rotations
======================================
*/
bool Board::IsPossibleMovement(int pX, int pY, int pPiece, int pRotation)
{
    for (int i1 = pX, i2 = 0; i1 < pX + BLOCK_SIZE; ++i1, ++i2)
        for (int j1 = pY, j2 = 0; j1 < pY + BLOCK_SIZE; ++j1, ++j2)
        {
            if (i1 < 0 || i1 > BOARD_WIDTH - 1 || j1 > BOARD_HEIGHT - 1)
                if (mPieces->GetBlockType(pPiece, pRotation, j2, i2) != 0)
                    return false;

            if (j1 >= 0)
                if ((mPieces->GetBlockType(pPiece, pRotation, j2, i2) != 0) && !IsFreeBlock(i1, j1))
                    return false;
        }
    return true;
}

TEST_CASE("testing the add function")
{
    Pieces pieces;
    Board board{&pieces, 500};

    CHECK(board.IsGameOver() == false);
    CHECK(board.IsFreeBlock(0, 0) == true);
    CHECK(board.IsFreeBlock(2, 2) == true);
    CHECK(board.IsFreeBlock(2, 3) == true);
    CHECK(board.IsFreeBlock(3, 2) == true);
    CHECK(board.IsFreeBlock(3, 3) == true);
    board.StorePiece(0, 0, 0, 0);
    CHECK(board.IsFreeBlock(0, 0) == true);
    CHECK(board.IsFreeBlock(2, 2) == false);
    CHECK(board.IsFreeBlock(2, 3) == false);
    CHECK(board.IsFreeBlock(3, 2) == false);
    CHECK(board.IsFreeBlock(3, 3) == false);
}