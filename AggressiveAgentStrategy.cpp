// Hosna Zulali
// 101485552
// Extended Due Date for 85% of Total

#include "Game.h"
#include "AggressiveAgentStrategy.h"


using namespace std;
using namespace Gaming;


    const double AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD = Game::STARTING_AGENT_ENERGY* 0.75;
    
    AggressiveAgentStrategy::AggressiveAgentStrategy(double agentEnergy)
    {
        __agentEnergy = agentEnergy;
    }
    
    AggressiveAgentStrategy::~AggressiveAgentStrategy()
    {
        // Blank
    }
    
    ActionType AggressiveAgentStrategy::operator()(const Surroundings &s) const
    {
        vector <ActionType> action = {NW,N,NE,W,STAY,E,SW,S,SE};
        vector <int> pI;
    
        if(this -> __agentEnergy >= DEFAULT_AGGRESSION_THRESHOLD)
        {
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
    
            for (int index = 0; index < s.array.size(); ++index)
            {
                if(s.array[index] == STRATEGIC)
                {
                    pI.push_back(index);
                }
            }

        }
    
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
            if(s.array[index] == FOOD)
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

            return action[((pos.x * 3.0) + pos.y)];
        }
    
        return STAY;
    
}