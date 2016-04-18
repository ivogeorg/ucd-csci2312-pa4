//
// Created by HosZul on 4/01/2016.
//

#include <iomanip>
#include <vector>
#include <set>
#include "Food.h"
#include "Advantage.h"
#include "Simple.h"
#include "Strategic.h"
#include "Game.h"

namespace Gaming {
    PositionRandomizer Game::__posRandomizer;

    const unsigned Game::MIN_WIDTH = 3;
    const unsigned Game::MIN_HEIGHT = 3;
    const unsigned int Game::NUM_INIT_AGENT_FACTOR = 4;
    const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;
    const double Game::STARTING_AGENT_ENERGY = 20;
    const double Game::STARTING_RESOURCE_CAPACITY = 10;

    void Game::populate() {
        std::default_random_engine gen;
        std::uniform_int_distribution<int> d(0, __width * __height - 1);

        __numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
        __numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;

        unsigned int numStrategic = __numInitAgents / 2;
        unsigned int numSimple = __numInitAgents - numStrategic;
        unsigned int numAdvantages = __numInitResources / 4;
        unsigned int numFoods = __numInitResources - numAdvantages;

        while (numStrategic > 0) {
            int i = d(gen);

            if (__grid[i] == nullptr && i != (__width * __height)) {
                Position pos(i / __width, i % __width);
                __grid[i] = new Simple(*this, pos, STARTING_AGENT_ENERGY);
                numStrategic--;
            }

        }

        while (numAdvantages > 0) {
            int i = d(gen);

            if (__grid[i] == nullptr && i != (__width * __height)) {
                Position pos(i / __width, i % __width);
                __grid[i] = new Advantage(*this, pos, STARTING_RESOURCE_CAPACITY);
                numAdvantages--;
            }
        }

        while (numStrategic > 0) {
            int i = d(gen);

            if (__grid[i] == nullptr && i != (__width * __height)) {
                Position pos(i / __width, i % __width);
                __grid[i] = new Simple(*this, pos, STARTING_AGENT_ENERGY);
                numStrategic--;
            }
        }

        while (numFoods > 0) {
            int i = d(gen);

            if (__grid[i] == nullptr && i != (__width * __height)) {
                Position pos(i / __width, i % __width);
                __grid[i] = new Food(*this, pos, STARTING_RESOURCE_CAPACITY);
                numFoods--;
            }
        }

        while (numSimple > 0) {
            int i = d(gen);

            if (__grid[i] == nullptr && i != (__width * __height)) {
                Position pos(i / __width, i % __width);
                __grid[i] = new Simple(*this, pos, STARTING_AGENT_ENERGY);
                numSimple--;
            }

        }
    }

    Game::Game() {
        __width = 3;
        __height = 3;
        __round = 0;
        __verbose = false;
        __status = NOT_STARTED;
        __width = MIN_WIDTH;
        __height = MIN_HEIGHT;

        for (int count = 0; count < __width * __height; ++count) {
            __grid.push_back(nullptr);
        }

        //if (!manual) {
        //    populate();
        // }
    }

    Game::Game(const Game &newG)
    {
        __height = newG.__height;
        __width = newG.__width;
        __status = newG.__status;
        __grid = newG.__grid;
    }

    Game::~Game()
    {
        for(int count = 0; count < __grid.size(); ++count)
        {
            if (__grid[count] != nullptr)
            {
                delete __grid[count];
            }
        }
    }

    //Get
    unsigned int Game::getNumPieces() const
    {
        return getNumAgents()+getNumResources();
    }

    unsigned int Game::getNumAgents() const
    {
        return getNumSimple()+getNumStrategic();
    }

    unsigned int Game::getNumSimple() const
    {
        unsigned int numAgents = 0;

        for (auto it = __grid.begin();
                it != __grid.end(); ++it)
        {
            Simple *s = dynamic_cast<Simple*>(*it);
            if (s) numAgents++;
        }
        return numAgents;
    }

    unsigned int Game::getNumResources() const {
        unsigned int numAgents = 0;

        for (auto it = __grid.begin(); it != __grid.end(); ++it) {
            Resource *resource = dynamic_cast<Resource*>(*it);
            if (resource) {
                numAgents++;
            }
        }
        return numAgents;
    }

    unsigned int Game::getNumStrategic() const
    {
        unsigned int numAgents = 0;

        for (auto it = __grid.begin(); it != __grid.end(); ++it)
        {
            Strategic *strategic = dynamic_cast<Strategic*>(*it);
            if (strategic)
            {
                numAgents++;
            }
        }
        return numAgents;
    }
}

