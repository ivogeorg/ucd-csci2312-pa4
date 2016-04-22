// Hosna Zulali
// 101485552
// Extended Due Date for 85% of Total

#include <iomanip>

#include "Simple.h"
#include "Strategic.h"
#include "Game.h"
#include "Food.h"
#include "Advantage.h"


using namespace std;
using namespace Gaming;

PositionRandomizer Game::__posRandomizer;

const unsigned int Game::MIN_WIDTH = 3;
const unsigned int Game::MIN_HEIGHT = 3;
const double Game::STARTING_AGENT_ENERGY = 20;
const double Game::STARTING_RESOURCE_CAPACITY = 10;
const unsigned  int Game::NUM_INIT_AGENT_FACTOR = 4;
const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;

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
            // Random Index
            int rT = d(gen);   

            if (__grid[rT] == nullptr)
            {
                Position pos(rT / __width, rT % __width);

                __grid[rT] = new Strategic(*this, pos, STARTING_AGENT_ENERGY);

                numStrategic --;
            }
        }

        while (numSimple > 0)
        {
            // Random index
            int rT = d(gen);

            if (__grid[rT] == nullptr)
            {
                Position pos(rT / __width, rT % __width);

                __grid[rT] = new Simple(*this, pos, STARTING_AGENT_ENERGY);

                numSimple --;
            }
        }

        while (numAdvantages > 0)
        {
            // Random Index
            int rT = d(gen);

            // Empty
            if (__grid[rT] == nullptr)
            {
                Position pos(rT / __width, rT % __width);

                __grid[rT] = new Advantage(*this, pos, STARTING_RESOURCE_CAPACITY);

                numAdvantages --;
            }
        }

        while (numFoods > 0)
        {
           // Random Index
            int rT = d(gen);

            // Empty
            if (__grid[rT] == nullptr)
            {
                Position pos(rT / __width, rT % __width);

                __grid[rT] = new Food(*this, pos, STARTING_RESOURCE_CAPACITY);

                numFoods --;
            }
        }
    }

    Game::Game()
    {
        __round = 0;
        __width = 3;
        __height = 3;
        __numInitAgents = 0;
        __numInitResources = 0;
        __status = NOT_STARTED ;
        __verbose = false;

        for (int index = 0; index < __width*__height; ++index)
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

        __round = 0;
        __width = width;
        __height = height;
        __numInitAgents = 0;
        __numInitResources = 0;
        __verbose = false;
        __status = NOT_STARTED;

        for (int index = 0; index < __width*__height; ++index)
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
        for (int index = 0; index < __grid.size(); ++index)
        {
            if (__grid[index] != nullptr)
            {
                delete __grid[index];
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
        unsigned int nA =0;

        for (int index = 0; index < __grid.size(); ++index)
        {
            if(__grid[index]!= nullptr)
            {
                if (__grid[index]->getType() == SIMPLE)
                {
                    nA++;
                }
            }
        }
        return nA;
    }

    unsigned int Game::getNumStrategic() const
    {
        unsigned int nA = 0;

        for (int index = 0; index < __grid.size(); ++index)
        {
            if(__grid[index]!= nullptr)
            {
                if (__grid[index]->getType() == STRATEGIC)
                {
                    nA++;
                }
            }
        }
        return nA;
    }

    unsigned int Game::getNumResources() const
    {
        unsigned int nA = 0;

        for (int index = 0; index < __grid.size(); ++index)
        {
            if(__grid[index]!= nullptr)
            {
                if (__grid[index]->getType() == FOOD || __grid[index]->getType() == ADVANTAGE)
                {
                    nA++;
                }
            }
        }
        return nA;
    }

    const Piece *Game::getPiece(unsigned int x, unsigned int y) const
    {
        if(__grid[((x*__width)+y)] != nullptr)
        {
            return __grid[((x*__width)+y)];
        }
        throw PositionEmptyEx(x,y);
    }

    void Game::addSimple(const Position &pos)
    {
        if(((pos.x*__width) + pos.y)>__grid.size())
        {
            throw OutOfBoundsEx(__width, __height, pos.x, pos.y);
        }

        if((__grid[(pos.x*__width) + pos.y])!=nullptr)
        {
            throw PositionNonemptyEx(pos.x, pos.y);
        }

        __grid[(pos.x*__width) + pos.y] = new Simple(*this,pos,STARTING_AGENT_ENERGY);
    }

    void Game::addSimple(const Position &pos, double energy)
    {
        if(((pos.x*__width) + pos.y)>__grid.size())
        {
            throw OutOfBoundsEx(__width, __height, pos.x, pos.y);
        }

        if((__grid[(pos.x*__width) + pos.y])!=nullptr)
        {
            throw PositionNonemptyEx(pos.x, pos.y);
        }

        __grid[(pos.x*__width) + pos.y] = new Simple(*this,pos,energy);;
    }

    void Game::addSimple(unsigned x, unsigned y)
    {
        Position pos(x,y);
        this->addSimple(pos);
    }

    void Game::addSimple(unsigned x, unsigned y, double energy)
    {
        Position pos(x,y);
        this->addSimple(pos,energy);
    }

    void Game::addStrategic(const Position &pos, Strategy *str)
    {
        if(((pos.x*__width) + pos.y)>__grid.size())
        {
            throw OutOfBoundsEx(__width, __height, pos.x, pos.y);
        }

        if((__grid[(pos.x*__width) + pos.y])!=nullptr)
        {
            throw PositionNonemptyEx(pos.x, pos.y);
        }

        __grid[(pos.x*__width) + pos.y] = new Strategic(*this, pos, STARTING_AGENT_ENERGY, str);
    }

    void Game::addStrategic(unsigned x, unsigned y, Strategy *str)
    {
        Position pos(x,y);
        this->addStrategic(pos,str);
    }

    void Game::addFood(const Position &pos)
    {
        if(((pos.x*__width) + pos.y) > __grid.size())
        {
            throw OutOfBoundsEx(__width, __height, pos.x, pos.y);
        }

        if((__grid[pos.x*__width + pos.y])!=nullptr)
        {
            throw PositionNonemptyEx(pos.x,pos.y);
        }

        __grid[(pos.x*__width) + pos.y] = new Food(*this, pos, STARTING_RESOURCE_CAPACITY);;
    }

    void Game::addFood(unsigned x, unsigned y)
    {
        Position pos(x,y);
        this->addFood(pos);
    }

    void Game::addAdvantage(const Position &pos)
    {
        if(((pos.x*__width) + pos.y)>__grid.size())
        {
            throw OutOfBoundsEx(__width, __height, pos.x, pos.y);
        }

        if((__grid[(pos.x*__width) + pos.y])!=nullptr)
        {
            throw PositionNonemptyEx(pos.x, pos.y);
        }

        __grid[(pos.x*__width) + pos.y] = new Advantage(*this,pos,STARTING_RESOURCE_CAPACITY);
    }

    void Game::addAdvantage(unsigned x, unsigned y)
    {
        Position pos(x,y);
        this->addAdvantage(pos);
    }

    const Surroundings Game::getSurroundings(const Position &pos) const
    {
        Surroundings surr;
        int surrX = pos.x - 1;

        for (int index = 0; index < 3; ++index)
        {
            int surrY = pos.y-1;

            for (int i = 0; i < 3; ++i)
            {
                if(((surrX * __width) + surrY)==((pos.x*__width)+pos.y))
                {
                    surr.array[(index * 3) + i] = SELF;
                }

                else if(surrX < 0 ||surrX >__height-1 || surrY<0 || surrY > __width-1)
                {
                    surr.array[(index * 3) + i] = INACCESSIBLE;
                }

                else if (__grid[(surrX * __width) + surrY] == nullptr)
                {
                    surr.array[(index * 3) + i] = EMPTY;
                }

                else
                {
                    surr.array[(index * 3) + i] = __grid[(surrX * __width) + surrY]->getType();
                }
                surrY++;
            }
            surrX++;

        }
        return surr;
    }


    const ActionType Game::reachSurroundings(const Position &from, const Position &to)
    {

        ActionType surr =STAY;
        int xFinal = to.x - from.x;
        int yFinal = to.y - from.y;

        if(xFinal == - 1 && yFinal == - 1)
        {
            surr = NW;
        }

        else if(xFinal == - 1 && yFinal == 1)
        {
            surr =NE;
        }

        else if(xFinal == - 1 && yFinal == 0)
        {
            surr = N;
        }

        else if(xFinal == 0 && yFinal == - 1)
        {
            surr =W;
        }

        else if(xFinal == 0 && yFinal == 1)
        {
            surr =E;
        }

        else if(xFinal == 1 && yFinal == 0)
        {
            surr =S;
        }

        else if(xFinal == 1 && yFinal == - 1)
        {
            surr =SW;
        }

        else if(xFinal == 1 && yFinal == 1)
        {
            surr =SE;
        }

        else if(xFinal == 0 && yFinal == 0)
        {
            surr =STAY;
        }

        return surr;
    }

    bool Game::isLegal(const ActionType &ac, const Position &pos) const
    {
        std::vector <ActionType> direction = {NW,NE,N,W,E,S,SW,SE,STAY};

        int dI;
        bool valid;

        for (int index = 0; index < direction.size(); ++index)
        {
            if(direction[index]== ac)
            {
                dI = index;
                break;
            }
        }
        valid = getSurroundings(pos).array[dI] != INACCESSIBLE;

        return valid;

    }

    const Position Game::move(const Position &pos, const ActionType &ac) const
    {

        Position nP;

        if(ac == NW)
        {
            nP = Position(pos.x - 1, pos.y - 1);
        }

        else if(ac == NE)
        {
            nP = Position(pos.x - 1, pos.y + 1);
        }

        else if(ac == N)
        {
            nP = Position(pos.x - 1, pos.y);
        }

        else if(ac == W)
        {
            nP = Position(pos.x, pos.y - 1);
        }

        else if(ac == E)
        {
            nP = Position(pos.x, pos.y + 1);
        }

        else if(ac == S)
        {
            nP = Position(pos.x + 1, pos.y);
        }

        else if(ac == SW)
        {
            nP = Position(pos.x + 1, pos.y - 1);
        }

        else if(ac == SE)
        {
            nP = Position(pos.x + 1, pos.y + 1);
        }

        else if(ac == STAY)
        {
            nP = Position(pos.x, pos.y);
        }

        return nP;
    }

    // Again
    void Game::round()
    {
        if(__round == 0 && __verbose)
        {
            __status = PLAYING;
            std::cout << std::endl << *this;
        }

        for (int index = 0; index < __grid.size(); ++index)
        {
            if(__grid[index]!= nullptr)
            {

                if(__grid[index]->isViable())
                {

                    if (! __grid[index]->getTurned())
                    {
                        Agent * agent = dynamic_cast<Agent*>(__grid[index]);

                        if(agent)
                        {
                            __grid[index]->setTurned(true);

                            Position cP = __grid[index]->getPosition();

                            ActionType aT = __grid[index]->takeTurn(getSurroundings(cP));

                            if (aT != STAY)
                            {
                                Position newPos = move(cP, aT);

                                int nP = (newPos.x * __width + newPos.y);
                                (*__grid[index]) * (*__grid[nP]);

                                if(! __grid[index]->isViable())
                                {
                                    delete __grid[index];
                                    __grid[index]= nullptr;
                                }

                                else
                                {
                                    __grid[index]->setPosition(newPos);

                                    if (__grid[nP] != nullptr)
                                    {
                                        delete __grid[nP];

                                        __grid[nP] = __grid[index];
                                        __grid[index] = nullptr;
                                    }

                                    else
                                    {
                                        __grid[nP] = __grid[index];
                                        __grid[index] = nullptr;
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
                    //delete__drid[i]
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

    void Game::play(bool verbose)
    {
        round();
        __verbose = verbose;

        if(getNumPieces()> 1 && getNumResources() > 0)
        {
            play(verbose);
        }
    }

    //Ostream
    std::ostream & Gaming::operator<<(std::ostream &os, const Game &game)
    {
        os << "Round " << game.__round << std::endl;

        for (int index = 0; index < game.__height; ++index)
        {
            for (int i = 0; i < game.__width; ++i)
            {
                os << '[' << *game.__grid[index*game.__width+i] << ']';
            }

            os << std::endl;
        }

        if(game.__status == Game::NOT_STARTED)
        {
            os << "Status: " << "Not Started" << std::endl;
        }

        else if(game.__status == Game::PLAYING)
        {
            os << "Status: " << "Playing" << std::endl;
        }

        else
        {
            os << "Status: " << "Over!" << std::endl;
        }

        return os;
    }