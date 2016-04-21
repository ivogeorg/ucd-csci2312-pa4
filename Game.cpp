// Hosna Zulali
// 101485552
// Extended Due Date for 85% of Total

#include <iomanip>
#include "Game.h"
#include "Simple.h"
#include "Strategic.h"
#include "Advantage.h"
#include "Food.h"

using namespace std;
using namespace Gaming;

const unsigned int Game::MIN_WIDTH = 3;
const unsigned int Game::MIN_HEIGHT = 3;
const double Game::STARTING_AGENT_ENERGY = 20;
const double Game::STARTING_RESOURCE_CAPACITY = 10;
const unsigned  int Game::NUM_INIT_AGENT_FACTOR = 4;
const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;

PositionRandomizer Game::__posRandomizer;


    void Game::populate()
    {
        __numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
        __numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;

        unsigned int numStrategic = __numInitAgents / 2;
        unsigned int numSimple = __numInitAgents - numStrategic;
        unsigned int numAdvantages = __numInitResources / 4;
        unsigned int numFoods = __numInitResources - numAdvantages;

        default_random_engine gen;
        uniform_int_distribution<int> d(0, __width * __height - 1);

        while (numStrategic > 0)
        {
            int i = d(gen);

            if (__grid[i] == nullptr)
            {
                Position pos(i / __width, i % __width);

                __grid[i] = new Strategic(*this, pos, STARTING_AGENT_ENERGY);
                numStrategic --;
            }
        }

        while (numSimple > 0)
        {
            int i = d(gen);

            if (__grid[i] == nullptr)
            {
                Position pos(i / __width, i % __width);
                __grid[i] = new Simple(*this, pos, STARTING_AGENT_ENERGY);
                numSimple --;
            }
        }

        while (numAdvantages > 0)
        {
            int i = d(gen);

            if (__grid[i] == nullptr)
            {
                Position pos(i / __width, i % __width);
                __grid[i] = new Advantage(*this, pos, STARTING_RESOURCE_CAPACITY);
                numAdvantages --;
            }
        }

        while (numFoods > 0)
        {
            int i = d(gen);

            if (__grid[i] == nullptr)
            {
                Position pos(i / __width, i % __width);
                __grid[i] = new Food(*this, pos, STARTING_RESOURCE_CAPACITY);
                numFoods --;
            }
        }

    }

    Game::Game()
    {
        __width = 3;
        __height = 3;
        __numInitAgents = 0;
        __numInitResources = 0;
        __round = 0;
        __verbose = false;
        __status = NOT_STARTED ;


        for (int i = 0; i < __width*__height; ++i)
        {
            __grid.push_back(nullptr) ;
        }

    }


    Game::Game(unsigned width, unsigned height, bool manual)
    {
        if(width < MIN_WIDTH || height < MIN_HEIGHT)
        {
            throw InsufficientDimensionsEx(MIN_WIDTH, MIN_HEIGHT, width, height);
        }

        __numInitAgents = 0;
        __numInitResources = 0;
        __width = width;
        __height = height;
        __verbose = false;
        __status = NOT_STARTED;
        __round = 0;

        for (int i = 0; i < __width * __height; ++i)
        {
            __grid.push_back(nullptr) ;
        }

        if(!manual)
        {
            populate();
        }
    }

    Game::~Game()
    {
        for (int i = 0; i < __grid.size(); ++i)
        {
            if (__grid[i] != nullptr)
            {
                delete __grid[i];
            }
        }
    }


    unsigned int Game::getNumPieces() const
    {
        return (getNumAgents()+getNumResources());
    }

    unsigned int Game::getNumAgents() const
    {
        return (getNumSimple()+getNumStrategic());
    }

    unsigned int Game::getNumSimple() const
    {
        unsigned int numAgents =0;
        for (int i = 0; i < __grid.size(); ++i)
        {
            if(__grid[i]!= nullptr)
            {
                if (__grid[i]->getType() == SIMPLE)
                {
                    numAgents++;
                }
            }
        }
        return numAgents;
    }

    unsigned int Game::getNumStrategic() const
    {
        unsigned int numAgents = 0;
        
        for (int i = 0; i < __grid.size(); ++i)
        {
            if(__grid[i]!= nullptr)
            {
                if (__grid[i]->getType() == STRATEGIC)
                {
                    numAgents++;
                }
            }
        }
        return numAgents;
    }

    unsigned int Game::getNumResources() const
    {
        unsigned int numAgents =0;

        for (int i = 0; i < __grid.size(); ++i)
        {
            if(__grid[i]!= nullptr)
            {
                if (__grid[i]->getType() == FOOD || __grid[i]->getType() == ADVANTAGE)
                {
                    numAgents++;
                }
            }
        }
        return numAgents;
    }

    const Piece *Game::getPiece(unsigned int x, unsigned int y) const
    {

        if(__grid[((x*__width)+y)] != nullptr)
        {
            return __grid[((x*__width)+y)];
        }

        throw PositionEmptyEx(x,y);
    }


    void Game::addSimple(const Position &position)
    {

        if((position.x*__width + position.y)>__grid.size())
        {
            throw OutOfBoundsEx(__width,__height,position.x,position.y);
        }

        if((__grid[position.x*__width + position.y])!=nullptr)
        {
            throw PositionNonemptyEx(position.x,position.y);
        }

        __grid[position.x*__width + position.y] = new Simple(*this,position,STARTING_AGENT_ENERGY);
    }


    void Game::addSimple(const Position &position, double energy)
    {
        if((position.x*__width + position.y)>__grid.size())
        {
            throw OutOfBoundsEx(__width,__height,position.x,position.y);
        }

        if((__grid[position.x*__width + position.y])!=nullptr)
        {
            throw PositionNonemptyEx(position.x,position.y);
        }

        __grid[position.x*__width + position.y] = new Simple(*this,position,energy);
    }

    void Game::addSimple(unsigned x, unsigned y)
    {
        Position p(x,y);
        this->addSimple(p);
    }

    void Game::addSimple(unsigned x, unsigned y, double energy)
    {
        Position p(x,y);
        this->addSimple(p,energy);
    }

    void Game::addStrategic(const Position &position, Strategy *s)
    {
        if((position.x*__width + position.y)>__grid.size())
        {
            throw OutOfBoundsEx(__width, __height, position.x, position.y);
        }

        if((__grid[position.x*__width + position.y])!=nullptr)
        {
            throw PositionNonemptyEx(position.x, position.y);
        }

        __grid[position.x*__width + position.y] = new Strategic(*this, position, STARTING_AGENT_ENERGY, s);;
    }

    void Game::addStrategic(unsigned x, unsigned y, Strategy *s)
    {
        Position p(x,y);
        this->addStrategic(p,s);
    }

    void Game::addFood(const Position &position)
    {
        if((position.x*__width + position.y) > __grid.size())
        {
            throw OutOfBoundsEx(__width, __height, position.x, position.y);
        }

        if((__grid[position.x*__width + position.y])!=nullptr)
        {
            throw PositionNonemptyEx(position.x,position.y);
        }

        __grid[position.x*__width + position.y] = new Food(*this, position, STARTING_RESOURCE_CAPACITY);;
    }

    void Game::addFood(unsigned x, unsigned y)
    {
        Position p(x,y);
        this->addFood(p);
    }

    void Game::addAdvantage(const Position &position)
    {

        if((position.x*__width + position.y)>__grid.size())
        {
            throw OutOfBoundsEx(__width,__height,position.x,position.y);
        }

        if((__grid[position.x*__width + position.y])!=nullptr)
        {
            throw PositionNonemptyEx(position.x,position.y);
        }

        __grid[position.x*__width + position.y] = new Advantage(*this,position,STARTING_RESOURCE_CAPACITY);;
    }

    void Game::addAdvantage(unsigned x, unsigned y)
    {
        Position p(x,y);
        this->addAdvantage(p);
    }

    const Surroundings Game::getSurroundings(const Position &pos) const
    {
        Surroundings tp;
        int tX = pos.x-1;

        for (int i = 0; i < 3; ++i)
        {
            int tY = pos.y-1;
            for (int i = 0; i < 3; ++i)
            {
                if(((tX * __width) + tY)==((pos.x*__width)+pos.y))
                {
                    tp.array[(i * 3) + i] = SELF;
                }

                else if(tX < 0 ||tX >__height-1 || tY<0 || tY > __width-1)
                {
                    tp.array[(i * 3) + i] = INACCESSIBLE;
                }

                else if (__grid[(tX * __width) + tY] == nullptr)
                {
                    tp.array[(i * 3) + i] = EMPTY;
                }

                else
                {
                    tp.array[(i * 3) + i] = __grid[(tX * __width) + tY]->getType();
                }
                tY++;
            }
            tX++;

        }
        return tp;
    }


    const ActionType Game::reachSurroundings(const Position &from, const Position &to)
    {

        ActionType aT =STAY;
        int xtoX = to.x-from.x;
        int ytoY = to.y-from.y;

        if(xtoX == - 1 && ytoY == - 1)
        {
            aT = NW;
        }

        else if(xtoX == - 1 && ytoY == 1)
        {
            aT =NE;
        }

        else if(xtoX == - 1 && ytoY == 0)
        {
            aT = N;
        }

        else if(xtoX == 0 && ytoY == - 1)
        {
            aT =W;
        }
        else if(xtoX == 0 && ytoY == 0)
        {
            aT =STAY;
        }
        else if(xtoX == 0 && ytoY == 1)
        {
            aT =E;
        }
        else if(xtoX == 1 && ytoY == - 1)
        {
            aT =SW;
        }
        else if(xtoX == 1 && ytoY == 0)
        {
            aT =S;
        }
        else if(xtoX == 1 && ytoY == 1)
        {
            aT =SE;
        }

        return aT;
    }

    bool Game::isLegal(const ActionType &ac, const Position &pos) const
    {
        Surroundings strstr = getSurroundings(pos);
        std::vector <ActionType> direction = {NW,N,NE,W,STAY,E,SW,S,SE};

        int goTo;
        bool valid;

        for (int i = 0; i < direction.size(); ++i)
        {
            if(direction[i]== ac)
            {
                goTo = i;
                break;
            }
        }
        valid = strstr.array[goTo] != INACCESSIBLE;

        return valid;

    }

    const Position Game::move(const Position &pos, const ActionType &ac) const
    {
        Position posFinal;

        if(ac == N)
        {
            posFinal = Position(pos.x - 1, pos.y);
        }

        else if(ac == NW)
        {
            posFinal = Position(pos.x - 1, pos.y - 1);
        }

        else if(ac == NE)
        {
            posFinal = Position(pos.x - 1, pos.y + 1);
        }

        else if(ac == W)
        {
            posFinal = Position(pos.x, pos.y - 1);
        }

        else if(ac == STAY)
        {
            posFinal = Position(pos.x, pos.y);
        }

        else if(ac == SW)
        {
            posFinal = Position(pos.x + 1, pos.y - 1);
        }

        else if(ac == S)
        {
            posFinal = Position(pos.x + 1, pos.y);
        }

        else if(ac == E)
        {
            posFinal = Position(pos.x, pos.y + 1);
        }

        else if(ac == SE)
        {
            posFinal = Position(pos.x + 1, pos.y + 1);
        }

        return posFinal;
    }


    void Game::round() {

        if(__round == 0 && __verbose)
        {
            __status = PLAYING;
            std::cout << std::endl << *this;
        }

        for (int i = 0; i < __grid.size(); ++i)
        {
            if(__grid[i]!= nullptr)
            {
                if(__grid[i] -> isViable())
                {
                    if (! __grid[i] -> getTurned())
                    {
                        Agent * agent = dynamic_cast<Agent*>(__grid[i]);

                        if(agent)
                        {
                            __grid[i]->setTurned(true);

                            Position firstPos =
                                    __grid[i]->getPosition();

                            Surroundings surr = getSurroundings(firstPos);

                            ActionType aT = __grid[i]->takeTurn(surr);

                            if (aT != STAY)
                            {
                                Position finalPos = move(firstPos, aT);
                                int nP = (finalPos.x * __width + finalPos.y);
                                (*__grid[i]) * (*__grid[nP]);

                                if(! __grid[i]->isViable())
                                {
                                    delete __grid[i];
                                    __grid[i]= nullptr;
                                }

                                else
                                {
                                    __grid[i]->setPosition(finalPos);

                                    if (__grid[nP] != nullptr)
                                    {
                                        delete __grid[nP];
                                        __grid[nP] = __grid[i];
                                        __grid[i] = nullptr;
                                    }

                                    else
                                    {
                                        __grid[nP] = __grid[i];
                                        __grid[i] = nullptr;
                                    }
                                }

                                if(! __grid[nP]->isViable())
                                {
                                    delete __grid[nP];
                                    __grid[nP]= nullptr;
                                }
                            }
                        }
                    }
                }
            }
        }

        for (int i = 0; i < __grid.size(); ++i)
        {
            if(__grid[i] != nullptr)
            {
                if (!__grid[i]->isViable())
                {
                    delete __grid[i];

                    __grid[i] = nullptr;
                }
                else
                {
                    __grid[i]->setTurned(false);
                    __grid[i]->age();
                }
            }
        }

        if(getNumPieces()< 2 || getNumResources() < 1)
        {
            __status = OVER;
        }
        ++__round;

        if(__verbose)
        {
            std::cout << std::endl << *this;
        }

    }

    // play game until over
    void Game::play(bool verbose)
    {
        __verbose = verbose;
        round();

        if(getNumPieces()>1 && getNumResources() > 0)
        {
            play(verbose);
        }
    }


std::ostream & Gaming::operator <<(std::ostream &os, const Game &game)
    {
        os << "Round " << game.__round << std::endl;

        for (int count = 0; count < game.__height; ++count)
        {
            for (int i = 0; i < game.__width; ++i)
            {
                os << '[' << std::setw(5) << std::left << *game.__grid[i*game.__width+i] << ']';
            }

            os << std::endl;
        }

        if(game.__status == Game::NOT_STARTED)
        {
            os << "Not Started";
        }
        else if(game.__status == Game::PLAYING)
        {
            os << "Playing";
        }
        else
        {
            os << "Over!";
        }
        return os;
}