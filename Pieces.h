#ifndef _PIECES_H_
#define _PIECES_H_

//------------------------
// Pieces
//------------------------

class Pieces
{
public:
    int GetBlockType(int pPiece, int pRotation, int pX, int pY);
    int GetXInitialPosition(int pPiece, int pRotation);
    int GetYInitialPosition(int pPiece, int pRotation);
};

#endif // !_PIECES_H_