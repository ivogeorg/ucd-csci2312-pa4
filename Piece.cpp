// Hosna Zulali
// 101485552
// Extended Due Date for 85% of Total

#include "Piece.h"

using namespace std;
using namespace Gaming;

unsigned int Piece::__idGen = 0;

    Piece::Piece(const Game &g, const Position &pos):__game(g)
    {
        __id = __idGen++;

        __turned = false;

        __finished = false;

        __position = pos;
    }

    Piece::~Piece()
    {
        // Blank
    }

    ostream & Gaming::operator<<(ostream &os, const Piece &pc)
    {
        if(&pc != nullptr)
        {
            pc.print(os);
        }

        return os;
    }

