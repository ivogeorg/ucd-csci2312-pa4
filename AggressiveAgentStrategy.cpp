//
// Created by HosZul on 4/01/2016.
//

#include "AggressiveAgentStrategy.h"
#include "Game.h"

namespace Gaming {
    const double AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD = Game::STARTING_AGENT_ENERGY * .75;

    AggressiveAgentStrategy::AggressiveAgentStrategy(double agentEnergy) {
        __agentEnergy = agentEnergy;
    }

    AggressiveAgentStrategy::~AggressiveAgentStrategy() {
        //
    }

    ActionType AggressiveAgentStrategy::operator()(const Surroundings &s) const {
        std::vector<ActionType> action = {NW, N, NE, W, STAY, E, SW, S, SE};
        std::vector<int> pieceIndex;

        if (__agentEnergy >= DEFAULT_AGGRESSION_THRESHOLD) {
            for (int index = 0; index < s.array.size(); ++index) {
                if (s.array[index] == SIMPLE) {
                    pieceIndex.push_back(index);
                }
            }

            if (pieceIndex.size() > 0) {
                PositionRandomizer pr;
                Position pos = pr(pieceIndex);
                return action[(pos.x * 3 + pos.y)];
            }

            for (int i = 0; i < s.array.size(); ++i) {
                if (s.array[i] == STRATEGIC) {
                    pieceIndex.push_back(i);
                }
            }

            if (pieceIndex.size() > 0) {
                PositionRandomizer pr;
                Position pos = pr(pieceIndex);
                return action[(pos.x * 3 + pos.y)];
            }
        }
        for (int i = 0; i < s.array.size(); ++i) {
            if (s.array[i] == FOOD) {
                pieceIndex.push_back(i);
            }

        }

        if (pieceIndex.size() > 0) {
            PositionRandomizer pr;
            Position pos = pr(pieceIndex);
            return action[(pos.x * 3 + pos.y)];
        }

        for (int i = 0; i < s.array.size(); ++i) {
            if (s.array[i] == EMPTY) {
                pieceIndex.push_back(i);
            }

        }

        if (pieceIndex.size() > 0) {
            PositionRandomizer pr;
            Position pos = pr(pieceIndex);
            return action[(pos.x * 3 + pos.y)];
        }

        return STAY;
    }
}