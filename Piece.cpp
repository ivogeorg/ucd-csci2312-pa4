//
// Created by HosZul on 4/1/2016.
//

#include "Piece.h"
#include "Gaming.h"
#include "Game.h"

namespace Gaming {
    unsigned int Piece::__idGen = 1000;

    Piece::Piece(const Game &g, const Position &p) : __game(g), __position(p) {
        __id = __idGen++;
        __turned = false;
        __finished = false;
    }

    Piece::~Piece() {
        //
    }

    std::ostream &operator<<(std::ostream &os, const Piece &piece) {
        if (&piece != nullptr)
        {
            piece.print(os);
        }

        else
        {
            os << "";
        }

        return os;

    }


}