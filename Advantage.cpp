//
// Created by HosZul on 4/1/2016.
//

#include <iomanip>
#include <sstream>
#include "Advantage.h"

namespace Gaming
{
    const char Advantage::ADVANTAGE_ID = 'D';
    const double Advantage::ADVANTAGE_MULT_FACTOR = 2.0;

    Advantage::Advantage(const Game &g, const Position &p, double capacity): Resource(g,p,capacity*ADVANTAGE_MULT_FACTOR )
    {
        __capacity = capacity * ADVANTAGE_MULT_FACTOR;
    }

    Advantage:: ~Advantage()
    {
        //
    }

    void Advantage::print(std::ostream &os) const
    {
        os << ADVANTAGE_ID << std::setw(4) << std::left << __id;
    }

    double Advantage::getCapacity() const
    {
        return __capacity;
    }

    double Advantage::consume()
    {
        double consume = __capacity;
        __capacity = 0;
        finish();
        return __capacity*ADVANTAGE_MULT_FACTOR;
    }
}
