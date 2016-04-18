//
// Created by HosZul on 4/1/2016.
//

#include "Food.h"
#include "Agent.h"

using namespace std;
using namespace Gaming;

const double Agent::AGENT_FATIGUE_RATE = .3;

Agent::Agent(const Game &g, const Position &p, double energy) : Piece(g, p)
{
    __energy = energy;
}

Agent::~Agent()
{
    //
}

void Agent::age()
{
    __energy -= AGENT_FATIGUE_RATE;
}

Piece &Agent::operator*(Piece &other)
{
    return other.interact(this);
}


