//
// Created by HosZul on 4/1/2016.
//

#include "DefaultAgentStrategy.h"

namespace Gaming {
    DefaultAgentStrategy::DefaultAgentStrategy() {
        //
    }

    DefaultAgentStrategy::~DefaultAgentStrategy() {
        //
    }

    ActionType DefaultAgentStrategy::operator()(const Surroundings &s) const {
        std::vector<int> Advantages;
        std::vector<int> EmptySpot;
        std::vector<int> Foods;
        std::vector<int> agentSpot;
        std::vector<int> Simple;
        std::vector<int> pos;
        Position piecePos(1, 1);

        PositionRandomizer pr;
        Position ps;

        for (int i = 0; i < s.array.size(); i++) {
            if (s.array[i] == ADVANTAGE) {
                pos.push_back(i);
            }
        }

        if (pos.size() == 0) {
            for (int i = 0; i < s.array.size(); i++) {
                if (s.array[i] == EMPTY) {
                    pos.push_back(i);
                }
            }
        }

        if (pos.size() == 0) {
            for (int i = 0; i < s.array.size(); i++) {
                if (s.array[i] == SIMPLE) {
                    pos.push_back(i);
                }
            }
        }

        if (pos.size() == 0) {
            for (int i = 0; i < s.array.size(); i++) {
                if (s.array[i] == FOOD) {
                    pos.push_back(i);
                }
            }
        }
    }
}
