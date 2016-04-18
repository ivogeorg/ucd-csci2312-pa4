//
// Created by HosZul on 4/1/2016.
//
#include <iomanip>
#include <sstream>
#include "Food.h"

namespace Gaming
{
    const char Food::FOOD_ID = 'F';

    Food::Food(const Game &g, const Position &p, double capacity):Resource(g,p,capacity)
    {
        __capacity = capacity;
    }

    Food::~Food()
    {
        //
    }

    void Food::print(std::ostream &os) const
    {
        os << FOOD_ID << std::setw(4) << std::left << __id;
        os << std::setw(0);
    }
}