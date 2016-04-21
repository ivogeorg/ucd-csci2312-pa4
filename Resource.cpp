// Hosna Zulali
// 101485552
// Extended Due Date for 85% of Total

#include "Resource.h"

using namespace std;
using namespace Gaming;

const double Resource::RESOURCE_SPOIL_FACTOR = 1.2;

    Resource::Resource(const Game &g, const Position &p, double capacity):Piece(g,p)
    {
        __capacity = capacity;
    }

    Resource::~Resource()
    {
        // Blank
    }

    double Resource::consume()
    {
        double consume = __capacity;
        this->__capacity = 0;

        finish();

        return consume;
    }

    void Resource::age()
    {
        __capacity /= RESOURCE_SPOIL_FACTOR;

        if (__capacity < 1)
            __capacity = 0;
    }

    ActionType Resource::takeTurn(const Surroundings &s) const
    {
        return STAY;
    }

    Piece &Resource::operator*(Piece &other)
    {
        return *this;
    }

    Piece &Resource::interact(Agent *)
    {
        return *this;
    }

    Piece &Resource::interact(Resource *)
    {
        return *this;
    }

