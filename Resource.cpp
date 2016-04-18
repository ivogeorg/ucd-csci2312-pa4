//
// Created by HosZul on 4/1/2016.
//

#include "Food.h"
#include "Resource.h"
#include "Gaming.h"
#include "Game.h"
#include "Agent.h"

namespace Gaming
{
    const double Resource::RESOURCE_SPOIL_FACTOR = 1.2;

    Resource::Resource(const Game &g, const Position &p, double capacity):Piece(g,p)
    {
        __capacity = capacity;
    }

    Resource::~Resource()
    {
        //
    }

    double Resource::consume()
    {
        double temp = __capacity;
        __capacity = 0;
        finish();
        return __capacity;
    }

    void Resource::age()
    {
         __capacity /= RESOURCE_SPOIL_FACTOR;

         if(__capacity < .01)
             __capacity = 0;
    }

    ActionType Resource::takeTurn(const Surroundings &s) const
    {
        return STAY;
    }

    Piece &Resource::interact(Agent *)
    {
        return *this;
    }

    Piece &Resource::operator*(Piece &other)
    {
        return *this;
    }

    Piece &Resource::interact(Resource *)
    {
        return *this;
    }
}
