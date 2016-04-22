#include "Simple.h"
#include <iomanip>
#include <sstream>

using namespace std;
using namespace Gaming;

    const char Simple::SIMPLE_ID = 'S';

    Simple::Simple(const Game &g, const Position &p, double energy):Agent(g, p, energy)
    {
        // blank
    }

    Simple::~Simple()
    {
        //Blank
    }

    void Simple::print(std::ostream &os) const
    {
        stringstream strstr;
        strstr << SIMPLE_ID << __id;

        string s;
        getline(strstr,s);

        os << s;
    }

    ActionType Simple::takeTurn(const Surroundings &s) const
    {

        vector <ActionType> act = {NW,N,NE,W,STAY,E,SW,S,SE};
        vector <int> pI;

        int numDir = 0;

        // Random
        random_device rd;
        mt19937 gen(rd());



        for (int index = 0; index < s.array.size(); ++index)
        {
            if(s.array[index] == FOOD || s.array[index] == ADVANTAGE)
            {
                pI.push_back(index);

                numDir++;
            }
        }

        if(numDir > 0)
        {
            uniform_int_distribution<> dis(0, numDir - 1);

            return act[pI[dis(gen)]];
        }

        for (int index = 0; index < s.array.size(); ++index)
        {
            if(s.array[index] == EMPTY)
            {
                pI.push_back(index);

                numDir++;
            }
        }

        if(numDir > 0)
        {
            uniform_int_distribution<> dis(0, numDir - 1);

            return act[pI[dis(gen)]];
        }

        return STAY;
    }