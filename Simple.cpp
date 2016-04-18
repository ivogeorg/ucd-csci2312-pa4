//
// Created by HosZul on 4/1/2016.
//
#include "Simple.h"
#include "Strategy.h"
#include <iomanip>


namespace Gaming{

    const char Simple::SIMPLE_ID = 'S';

    Simple::Simple(const Game &g, const Position &p, double energy) : Agent(g, p, energy){

    }

    Simple::~Simple() {

    }

    void Simple::print(std::ostream &os) const {
        os << SIMPLE_ID << std::setw(4) << std::left <<__id;
    }

    ActionType Simple::takeTurn(const Surroundings &s) const {


        ActionType aT;
        std::vector<int> pos;

        std::random_device rd;
        std::mt19937 gen(rd());

        for (int i = 0; i < s.array.size(); i++)
        {
            if (s.array[i] == ADVANTAGE || s.array[i] == FOOD)
            {
                pos.push_back(i);
            }
        }

        if (pos.size() == 0)
        {
            for (int i = 0; i < s.array.size(); i++)
            {
                if (s.array[i] == EMPTY) {
                    pos.push_back(i);
                }
            }
        }

        if (pos.size() > 0)
        {
            std::uniform_int_distribution<> dis(0, (int) (pos.size()-1));
            int index = dis(gen);

            if (pos.size() == 1)
            {
                index = pos[0];
            }

            switch (pos[index])
            {
                case 1 :
                    aT = N;
                    break;
                case 2 :
                    aT = NE;
                    break;
                case 5 :
                    aT = E;
                    break;
                case 8 :
                    aT = SE;
                    break;
                case 7 :
                    aT = S;
                    break;
                case 6 :
                    aT = SW;
                    break;
                case 3 :
                    aT = W;
                    break;
                case 0 :
                    aT = NW;
                    break;
                case 4 :
                    aT = STAY;
                    break;
                default :
                    aT = STAY;
            }
            return aT;

        }

        return STAY;

    }
}