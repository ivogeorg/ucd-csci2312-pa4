//
// Created by HosZul on 4/1/2016.
//

#include <iomanip>
#include <sstream>
#include "Strategic.h"

namespace Gaming
{
    const char Strategic::STRATEGIC_ID = 'T';

    Strategic::Strategic(const Game &g, const Position &p, double energy, Strategy *s):Agent(g,p,energy)
    {
        __strategy = s;
    }

    Strategic::~Strategic()
    {
        delete __strategy;
    }

    void Strategic::print(std::ostream &os) const
    {
        os << this -> STRATEGIC_ID << std::setw(4) << std::left << __id;
    }

    ActionType Strategic::takeTurn(const Surroundings &s) const
    {
        return (*this-> __strategy)(s);
    }
}