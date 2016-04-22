// Hosna Zulali
// 101485552
// Extended Due Date for 85% of Total

#include "DefaultAgentStrategy.h"

using namespace std;
using namespace Gaming;

    DefaultAgentStrategy::DefaultAgentStrategy()
    {
        // Blank
    }

    DefaultAgentStrategy::~DefaultAgentStrategy()
    {
        // Blank
    }

    ActionType DefaultAgentStrategy::operator()(const Surroundings &s) const
    {
        vector <ActionType> action = {NW,N,NE,W,STAY,E,SW,S,SE};
        vector <int> pI;

        for (int index = 0; index < s.array.size(); ++index)
        {
            if(s.array[index] == ADVANTAGE)
            {
                pI.push_back(index);
            }
        }

        if(pI.size() > 0)
        {
            PositionRandomizer pR;
            Position pos = pR(pI);

            return action[((pos.x * 3.0) + pos.y)];
        }

        for (int index = 0; index < s.array.size(); ++index)
        {
            if(s.array[index]==FOOD)
            {
                pI.push_back(index);
            }
        }

        if(pI.size() > 0)
        {
            PositionRandomizer pR;
            Position pos = pR(pI);

            return action[((pos.x * 3.0) + pos.y)];
        }

        for (int index = 0; index < s.array.size(); ++index)
        {
            if(s.array[index] == EMPTY)
            {
                pI.push_back(index);
            }
        }

        if(pI.size() > 0)
        {
            PositionRandomizer pR;
            Position pos = pR(pI);

            return action[((pos.x * 3.0 + pos.y))];
        }

        for (int index = 0; index < s.array.size(); ++index)
        {
            if(s.array[index] == SIMPLE)
            {
                pI.push_back(index);
            }
        }

        if(pI.size() > 0)
        {
            PositionRandomizer pR;
            Position pos = pR(pI);

            return action[((pos.x * 3.0) + pos.y)];
        }

        return STAY;
    }