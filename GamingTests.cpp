//
// Created by Ivo Georgiev on 11/22/15.
//

#include <iostream>
#include <cassert>
#include <regex>

#include "GamingTests.h"
#include "ErrorContext.h"
#include "Game.h"
#include "Exceptions.h"
#include "Simple.h"
#include "Strategic.h"
#include "Food.h"
#include "Advantage.h"
#include "AggressiveAgentStrategy.h"

using namespace Gaming;
using namespace Testing;

#define DESC(x) desc(x, __LINE__)  // ugly hack, but saves some time




// - - - - - - - - - - helper functions - - - - - - - - - -

// - - - - - - - - - - local classes - - - - - - - - - -


// - - - - - - - - - - T E S T S - - - - - - - - - -

// - - - - - - - - - - P I E C E - - - - - - - - - -

// Smoketest: constructor, copy constructor, destructor, resources
void test_piece_smoketest(ErrorContext &ec) {
    bool pass;

    ec.DESC("--- Test - Unit - Smoketest ---");

    ec.DESC("constructor, destructor for leaf classes from Piece hierarchy");
    pass = true;
    for (int i = 0; i < 10; i++) {
        Game g;                         // note: Game smoke test is needed first

        Position p0(0, 0);
        Simple s(g, p0, 10);

        Position p1(1, 0);
        Strategic t(g, p1, 20);

        Position p2(2, 2);
        Food f(g, p2, 5);

        Position p3(0, 2);
        Advantage a(g, p3, 3);
    }
    ec.result(pass);
}

void test_piece_print(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Piece - Id-s, names, printing ---");

    for (int run = 0; run < numRuns; run ++) {

        ec.DESC("piece id-s, names, and printing");

        {
            Game g;                         // note: Game smoke test is needed first

            Position p0(0, 0);
            Simple s(g, p0, 10);

            Position p1(1, 0);
            Strategic t(g, p1, 20);

            Position p2(2, 2);
            Food f(g, p2, 5);

            Position p3(0, 2);
            Advantage a(g, p3, 3);

            std::stringstream ss;
            ss << s << ' ' << t << ' ' << f << ' ' << a;

            int id = 0;
            std::regex re("S[[:d:]]{1,}[ ]"); // ECMAScript, by default
            std::smatch m;
            std::regex_search(ss.str(), m, re);
            if (m.size() != 1) { // parse problem
                pass = false;
            } else {
                std::string matchStr(m[0]);
                std::regex r("[[:d:]]{1,}");
                std::regex_search(matchStr, m, r);
                id = stoi(m[0]);
                pass = true;
            }

            std::stringstream compare;
            compare << 'S' << id << " T" << (id+1) << " F" << (id+2) << " D" << (id+3);

            pass = pass && (ss.str() == compare.str());

            ec.result(pass);
        }
    }
}

// Piece aging and viability
void test_piece_aging(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Piece - Viability & aging ---");

    for (int run = 0; run < numRuns; run++) {

        ec.DESC("app pieces start out viable");

        {
            Game g;                         // note: Game smoke test is needed first

            Position p0(0, 0);
            Simple s(g, p0, 10);

            Position p1(1, 0);
            Strategic t(g, p1, 20);

            Position p2(2, 2);
            Food f(g, p2, 5);

            Position p3(0, 2);
            Advantage a(g, p3, 3);

            pass = s.isViable() &&
                   t.isViable() &&
                   f.isViable() &&
                   a.isViable();

            ec.result(pass);
        }

        ec.DESC("pieces age polymorphically (with every round)");

        {
            Game g;                         // note: Game smoke test is needed first

            Position p0(0, 0);
            Simple s(g, p0, 10);

            Position p1(1, 0);
            Strategic t(g, p1, 20);

            Position p2(2, 2);
            Food f(g, p2, 5);

            Position p3(0, 2);
            Advantage a(g, p3, 3);

            Piece *pieces[] = { &s, &t, &f, &a };

            pass = true;
            for (int i = 0; i < 4; i++) {
                pass = pass && pieces[i]->isViable();
                for (int a = 0; a < 100; a++) pieces[i]->age();
                pass = pass && (! pieces[i]->isViable());
            }

            ec.result(pass);
        }



        // TODO test fatigue factor, spoil rate


    }
}

// Piece energy/capacity
void test_piece_energy(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Piece - Energy/capacity ---");

    for (int run = 0; run < numRuns; run++) {

        ec.DESC("getting agent energy and resource capacities");

        {
            Game g;

            Simple s(g, Position(0, 0), Game::STARTING_AGENT_ENERGY);
            Food f(g, Position(1, 1), Game::STARTING_RESOURCE_CAPACITY);
            Advantage a(g, Position(2, 2), Game::STARTING_RESOURCE_CAPACITY);

            Agent *agent = &s;
            Resource *r0 = &f, *r1 = &a;

            pass = (agent->getEnergy() == Game::STARTING_AGENT_ENERGY) &&
                    (r0->getCapacity() == Game::STARTING_RESOURCE_CAPACITY) &&
                    (r1->getCapacity() == Game::STARTING_RESOURCE_CAPACITY * Advantage::ADVANTAGE_MULT_FACTOR);

            ec.result(pass);
        }
    }
}

// Taking turns
void test_piece_turntaking(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Piece - Taking turns ---");

    for (int run = 0; run < numRuns; run++) {

        ec.DESC("3x3, manual, simple agent going for a resource");

        {
            Game g(3, 3);

            // populate the game environment
            g.addFood(0, 0); g.addAdvantage(2, 1);

            // create a Simple, passing it the game and a position
            Simple s(g, Position(1, 1), Game::STARTING_AGENT_ENERGY);

            // create an upcast pointer to the agent for polymorphic turn taking
            Piece *piece = &s;

            // get the Surroundings for the agent's position from the Game
            Surroundings surr = g.getSurroundings(Position(1, 1));

            // call takeTurn on the Piece pointer to the agent
            ActionType action = piece->takeTurn(surr);

            // if there is a resource, it should ask to there
            // and so on...
            pass = (action == ActionType::NW) || (action == ActionType::S);
            if (! pass) std::cout << action << std::endl;

            ec.result(pass);
        }

        ec.DESC("3x3, manual, simple agent moving to an empty position");

        {
            Game g(3, 3);

            // populate the game environment
            g.addStrategic(0, 1); g.addSimple(1, 1);

            // create a Simple, passing it the game and a position
            Simple s(g, Position(0, 2), Game::STARTING_AGENT_ENERGY);

            // create an upcast pointer to the agent for polymorphic turn taking
            Piece *piece = &s;

            // get the Surroundings for the agent's position from the Game
            Surroundings surr = g.getSurroundings(Position(0, 2));

            // call takeTurn on the Piece pointer to the agent
            ActionType action = piece->takeTurn(surr);

            // if there is a resource, it should ask to there
            // and so on...
            pass = (action == ActionType::S);
            if (! pass) std::cout << action << std::endl;

            ec.result(pass);
        }

        ec.DESC("3x3, manual, simple agent staying in place, not attacking");

        {
            Game g(3, 3);

            // populate the game environment
            g.addStrategic(0, 1); g.addSimple(1, 1); g.addSimple(1, 2);

            // create a Simple, passing it the game and a position
            Simple s(g, Position(0, 2), Game::STARTING_AGENT_ENERGY);

            // create an upcast pointer to the agent for polymorphic turn taking
            Piece *piece = &s;

            // get the Surroundings for the agent's position from the Game
            Surroundings surr = g.getSurroundings(Position(0, 2));

            // call takeTurn on the Piece pointer to the agent
            ActionType action = piece->takeTurn(surr);

            // if there is a resource, it should ask to there
            // and so on...
            pass = (action == ActionType::STAY);
            if (! pass) std::cout << action << std::endl;

            ec.result(pass);
        }

        ec.DESC("3x3, manual, resources don't move");

        {
            Game g(3, 3);

            Food f(g, Position(0, 0), Game::STARTING_RESOURCE_CAPACITY);
            Advantage a(g, Position(2, 1), Game::STARTING_RESOURCE_CAPACITY);

            // create an upcast pointer to the agent for polymorphic turn taking
            Piece *piece[2] = { &f, &a };

            // get the Surroundings for a Piece's position
            Surroundings surr[2] =
                    { g.getSurroundings(Position(0, 0)), g.getSurroundings(Position(2, 1)) };

            // call takeTurn on the Piece pointer
            ActionType actions[2] =
                    { piece[0]->takeTurn(surr[0]), piece[1]->takeTurn(surr[1]) };

            pass = (actions[0] == ActionType::STAY) &&
                    (actions[1] == ActionType::STAY);

            ec.result(pass);
        }

        ec.DESC("3x3, manual, default strategic agent choosing an advantage");

        {
            Game g(3, 3);

            // populate the game environment
            g.addFood(0, 0); g.addAdvantage(2, 1);

            // create a default Strategic, passing it the game and a position
            Strategic s(g, Position(1, 1), Game::STARTING_AGENT_ENERGY);

            // create an upcast pointer to the agent for polymorphic turn taking
            Piece *piece = &s;

            // get the Surroundings for the agent's position from the Game
            Surroundings surr = g.getSurroundings(Position(1, 1));

            // call takeTurn on the Piece pointer to the agent
            ActionType action = piece->takeTurn(surr);

            // if there is a resource, it should ask to there
            // and so on...
            pass = (action == ActionType::S);
            if (! pass) std::cout << action << std::endl;

            ec.result(pass);
        }

        ec.DESC("3x3, manual, hemmed in default strategic challenging a simple");

        {
            Game g(3, 3);

            // populate the game environment
            g.addSimple(0, 0); g.addSimple(0, 1); g.addSimple(0, 2);
            g.addStrategic(1, 0); g.addStrategic(1, 2);
            g.addSimple(2, 0); g.addSimple(2, 1); g.addSimple(2, 2);

            // create a default Strategic, passing it the game and a position
            Strategic s(g, Position(1, 1), Game::STARTING_AGENT_ENERGY);

            // create an upcast pointer to the agent for polymorphic turn taking
            Piece *piece = &s;

            // get the Surroundings for the agent's position from the Game
            Surroundings surr = g.getSurroundings(Position(1, 1));

            // call takeTurn on the Piece pointer to the agent
            ActionType action = piece->takeTurn(surr);

            // if there is a resource, it should ask to there
            // and so on...
            pass = (action == ActionType::NW) ||
                   (action == ActionType::N)  ||
                   (action == ActionType::NE) ||
                   (action == ActionType::SW) ||
                   (action == ActionType::S)  ||
                   (action == ActionType::SE);
            if (! pass) std::cout << action << std::endl;

            ec.result(pass);
        }

        ec.DESC("3x3, manual, hemmed in default strategic staying put");

        {
            Game g(3, 3);

            // populate the game environment
            g.addStrategic(0, 0); g.addStrategic(0, 1); g.addStrategic(0, 2);
            g.addStrategic(1, 0); g.addStrategic(1, 2);
            g.addStrategic(2, 0); g.addStrategic(2, 1); g.addStrategic(2, 2);

            // create a default Strategic, passing it the game and a position
            Strategic s(g, Position(1, 1), Game::STARTING_AGENT_ENERGY);

            // create an upcast pointer to the agent for polymorphic turn taking
            Piece *piece = &s;

            // get the Surroundings for the agent's position from the Game
            Surroundings surr = g.getSurroundings(Position(1, 1));

            // call takeTurn on the Piece pointer to the agent
            ActionType action = piece->takeTurn(surr);

            // if there is a resource, it should ask to there
            // and so on...
            pass = (action == ActionType::STAY);
            if (! pass) std::cout << action << std::endl;

            ec.result(pass);
        }

        ec.DESC("3x3, manual, hemmed in default strategic fleeing");

        {
            Game g(3, 3);

            // populate the game environment
            g.addStrategic(0, 0); g.addStrategic(0, 1); g.addStrategic(0, 2);
            g.addStrategic(1, 0);
            g.addStrategic(2, 0); g.addStrategic(2, 1); g.addStrategic(2, 2);

            // create a default Strategic, passing it the game and a position
            Strategic s(g, Position(1, 1), Game::STARTING_AGENT_ENERGY);

            // create an upcast pointer to the agent for polymorphic turn taking
            Piece *piece = &s;

            // get the Surroundings for the agent's position from the Game
            Surroundings surr = g.getSurroundings(Position(1, 1));

            // call takeTurn on the Piece pointer to the agent
            ActionType action = piece->takeTurn(surr);

            // if there is a resource, it should ask to there
            // and so on...
            pass = (action == ActionType::E);
            if (! pass) std::cout << action << std::endl;

            ec.result(pass);
        }

        ec.DESC("3x3, manual, hemmed in aggressive strategic attacking");

        {
            Game g(3, 3);

            // populate the game environment
            g.addStrategic(0, 0); g.addStrategic(0, 1); g.addStrategic(0, 2);
            g.addStrategic(1, 0);
            g.addStrategic(2, 0); g.addStrategic(2, 1); g.addStrategic(2, 2);

            // create an aggressive Strategic, passing it the game and a position
            Strategic s(g, Position(1, 1),
                        Game::STARTING_AGENT_ENERGY,
                        new AggressiveAgentStrategy(Game::STARTING_AGENT_ENERGY));

            // create an upcast pointer to the agent for polymorphic turn taking
            Piece *piece = &s;

            // get the Surroundings for the agent's position from the Game
            Surroundings surr = g.getSurroundings(Position(1, 1));

            // call takeTurn on the Piece pointer to the agent
            ActionType action = piece->takeTurn(surr);

            // if there is a resource, it should ask to there
            // and so on...
            pass = (action != ActionType::E);
            if (! pass) std::cout << action << std::endl;

            ec.result(pass);
        }

        ec.DESC("3x3, manual, strong aggressive strategic prefers to attack");

        {
            Game g(3, 3);

            // populate the game environment
            g.addFood(0, 0); g.addAdvantage(0, 2);
            g.addStrategic(1, 0);
            g.addFood(2, 1); g.addSimple(2, 2);

            // create an aggressive Strategic, passing it the game and a position
            Strategic s(g, Position(1, 1),
                        Game::STARTING_AGENT_ENERGY,
                        new AggressiveAgentStrategy(Game::STARTING_AGENT_ENERGY));

            // create an upcast pointer to the agent for polymorphic turn taking
            Piece *piece = &s;

            // get the Surroundings for the agent's position from the Game
            Surroundings surr = g.getSurroundings(Position(1, 1));

            // call takeTurn on the Piece pointer to the agent
            ActionType action = piece->takeTurn(surr);

            // if there is a resource, it should ask to there
            // and so on...
            pass = (action == ActionType::W) || (action == ActionType::SE);
            if (! pass) std::cout << action << std::endl;

            ec.result(pass);
        }

        ec.DESC("3x3, manual, weak aggressive strategic goes for an advantage");

        {
            Game g(3, 3);

            // populate the game environment
            g.addFood(0, 0); g.addAdvantage(0, 2);
            g.addStrategic(1, 0);
            g.addFood(2, 1); g.addSimple(2, 2);

            // create an aggressive Strategic, passing it the game and a position
            double energy = Game::STARTING_AGENT_ENERGY / 2; // weaken the agent
            Strategic s(g, Position(1, 1), energy, new AggressiveAgentStrategy(energy));

            // create an upcast pointer to the agent for polymorphic turn taking
            Piece *piece = &s;

            // get the Surroundings for the agent's position from the Game
            Surroundings surr = g.getSurroundings(Position(1, 1));

            // call takeTurn on the Piece pointer to the agent
            ActionType action = piece->takeTurn(surr);

            // if there is a resource, it should ask to there
            // and so on...
            pass = (action == ActionType::NE);
            if (! pass) std::cout << action << std::endl;

            ec.result(pass);
        }
    }
}

// Piece interaction operator*
void test_piece_interaction(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Piece - Interaction ---");

    for (int run = 0; run < numRuns; run++) {

        ec.DESC("3x3, manual, two agents with equal energy");

        {
            Game g;

            Simple s0(g, Position(2, 0), Game::STARTING_AGENT_ENERGY);
            Strategic s1(g, Position(1, 1), Game::STARTING_AGENT_ENERGY);

            Piece *pieces[2] = { &s0, &s1 };
            Piece &p0 = *pieces[0], &p1 = *pieces[1];
            p1 * p0;
            pass = (! p0.isViable()) && (! p1.isViable());

            ec.result(pass);
        }


        ec.DESC("3x3, manual, two agents with inequal energy");

        {
            Game g;

            Simple s0(g, Position(2, 0), Game::STARTING_AGENT_ENERGY);
            Strategic s1(g, Position(1, 1), Game::STARTING_AGENT_ENERGY * 1.1);

            Piece *pieces[2] = { &s0, &s1 };
            Piece &p0 = *pieces[0], &p1 = *pieces[1];
            p1 * p0;
            pass = (! p0.isViable()) && p1.isViable();

            ec.result(pass);
        }

        ec.DESC("3x3, manual, a simple agent and a resource");

        {
            Game g;

            Food s0(g, Position(2, 0), Game::STARTING_RESOURCE_CAPACITY);
            Strategic s1(g, Position(1, 1), Game::STARTING_AGENT_ENERGY * 1.1);

            Piece *pieces[2] = { &s0, &s1 };
            Piece &p0 = *pieces[0], &p1 = *pieces[1];
            p1 * p0;
            pass = (! p0.isViable()) && p1.isViable();

            ec.result(pass);
        }

        ec.DESC("3x3, manual, no interaction between resources");

        {
            Game g;

            Food s0(g, Position(2, 0), Game::STARTING_RESOURCE_CAPACITY);
            Food s1(g, Position(1, 1), Game::STARTING_RESOURCE_CAPACITY);

            Piece *pieces[2] = { &s0, &s1 };
            Piece &p0 = *pieces[0], &p1 = *pieces[1];
            p1 * p0;
            pass = p0.isViable() && p1.isViable();

            ec.result(pass);
        }
    }
}


// - - - - - - - - - - S U R R O U N D I N G S - - - - - - - - - -

// Surroundings (vector of enums of type PieceType) smoke test
void test_surroundings_smoketest(ErrorContext &ec) {
    bool pass;

    ec.DESC("--- Test - Surroundings - Smoketest ---");

    ec.DESC("printing PieceTypes");
    pass = true;
    for (int i = 0; i < 10; i ++) {
        std::stringstream ss;
        ss << PieceType::SIMPLE << ' '
        << PieceType::STRATEGIC << ' '
        << PieceType::FOOD << ' '
        << PieceType::ADVANTAGE << ' '
        << PieceType::INACCESSIBLE << ' '
        << PieceType::SELF << ' '
        << PieceType::EMPTY;

        pass = (ss.str() == "0 1 2 3 4 5 6");
//        if (! pass) std::cout << ss.str() << std::endl;
    }
    ec.result(pass);

    ec.DESC("3x3 grid, manual, surroundings of agents");
    pass = true;
    for (int i = 0; i < 10; i ++) {
        Game g;                     // note: Game smoke test required first

        Position p0(0, 0);
        g.addSimple(p0);

        Position p1(1, 0);
        g.addStrategic(p1);

        Position p2(2, 2);
        g.addFood(p2);

        Position p3(0, 2);
        g.addAdvantage(p3);

        // The surroundings of the simple agent
        Surroundings surr = g.getSurroundings(p0);
        std::stringstream ss0;
        for (int i = 0; i < 9; i++)
            ss0 << surr.array[i] << ' ';

        pass = (ss0.str() == "4 4 4 4 5 6 4 1 6 ");
        if (! pass) std::cout << ss0.str() << std::endl;

        // The surroundings of the strategic agent
        surr = g.getSurroundings(p1);
        std::stringstream ss1;
        for (int i = 0; i < 9; i++)
            ss1 << surr.array[i] << ' ';

        pass = pass && (ss1.str() == "4 0 6 4 5 6 4 6 6 ");
        if (! pass) std::cout << ss1.str() << std::endl;

    }
    ec.result(pass);

    ec.DESC("4x5 grid, manual, surroundings of agents");
    pass = true;
    for (int i = 0; i < 10; i ++) {
        Game g(4, 5);                     // note: Game smoke test required first

//        std::cout << g << std::endl;

        g.addSimple(0, 1); Position p0(0, 1);
        g.addAdvantage(1, 0);
        g.addAdvantage(1, 1);
        g.addFood(1, 3);
        g.addStrategic(2, 2); Position p1(2, 2);
        g.addFood(3, 1);
        g.addSimple(3, 2); Position p2(3, 2);
        g.addStrategic(4, 3); Position p3(4, 3);


        // The surroundings of the simple agent at p0
        Surroundings surr = g.getSurroundings(p0);
        std::stringstream ss0;
        for (int i = 0; i < 9; i++) ss0 << surr.array[i] << ' ';

        pass = (ss0.str() == "4 4 4 6 5 6 3 3 6 ");
        if (! pass) std::cout << ss0.str() << std::endl;


        // The surroundings of the strategic agent at p1
        surr = g.getSurroundings(p1);
        std::stringstream ss1;
        for (int i = 0; i < 9; i++)
            ss1 << surr.array[i] << ' ';

        pass = pass && (ss1.str() == "3 6 2 6 5 6 2 0 6 ");
        if (! pass) std::cout << ss1.str() << std::endl;


        // The surroundings of the simple agent at p2
        surr = g.getSurroundings(p2);
        std::stringstream ss2;
        for (int i = 0; i < 9; i++)
            ss2 << surr.array[i] << ' ';

        pass = pass && (ss2.str() == "6 1 6 2 5 6 6 6 1 ");
        if (! pass) std::cout << ss2.str() << std::endl;


        // The surroundings of the strategic agent at p3
        surr = g.getSurroundings(p3);
        std::stringstream ss3;
        for (int i = 0; i < 9; i++)
            ss3 << surr.array[i] << ' ';

        pass = pass && (ss3.str() == "0 6 4 6 5 4 4 4 4 ");
        if (! pass) std::cout << ss3.str() << std::endl;
    }
    ec.result(pass);
}


// - - - - - - - - - - A C T I O N - - - - - - - - - -

// Action smoke test
void test_action_smoketest(ErrorContext &ec) {
    bool pass;

    ec.DESC("--- Test - Action - Smoketest ---");

    ec.DESC("printing ActionType");

    pass = true;
    for (int i = 0; i < 10; i ++) {
        std::stringstream ss;
        ss << ActionType::N << ' '
        << ActionType::NE << ' '
        << ActionType::NW << ' '
        << ActionType::E << ' '
        << ActionType::W << ' '
        << ActionType::SE << ' '
        << ActionType::SW << ' '
        << ActionType::S << ' '
        << ActionType::STAY;

        pass = (ss.str() == "0 1 2 3 4 5 6 7 8");
//        if (! pass) std::cout << ss.str() << std::endl;
    }
    ec.result(pass);

    ec.DESC("3x3, manual, agent in the middle");

    pass = true;
    for (int i = 0; i < 10; i ++) {
        Game g;

        // not actually necessary for the test
        g.addSimple(1, 1); Position pos(1, 1);

        pass = g.isLegal(ActionType::N, pos) &&
                g.isLegal(ActionType::NE, pos) &&
                g.isLegal(ActionType::NW, pos) &&
                g.isLegal(ActionType::E, pos) &&
                g.isLegal(ActionType::W, pos) &&
                g.isLegal(ActionType::SE, pos) &&
                g.isLegal(ActionType::SW, pos) &&
                g.isLegal(ActionType::S, pos) &&
                g.isLegal(ActionType::STAY, pos);
    }
    ec.result(pass);

    ec.DESC("7x6, manual, agent in the SW corner");

    pass = true;
    for (int i = 0; i < 10; i ++) {
        Game g(7, 6);

        // not actually necessary for the test
        g.addSimple(5, 6); Position pos(5, 6);

        pass = g.isLegal(ActionType::N, pos) &&
               (! g.isLegal(ActionType::NE, pos)) &&
               g.isLegal(ActionType::NW, pos) &&
               (! g.isLegal(ActionType::E, pos)) &&
               g.isLegal(ActionType::W, pos) &&
               (! g.isLegal(ActionType::SE, pos)) &&
               (! g.isLegal(ActionType::SW, pos)) &&
               (! g.isLegal(ActionType::S, pos)) &&
               g.isLegal(ActionType::STAY, pos);
    }
    ec.result(pass);

    ec.DESC("7x6, movement from position to position");

    pass = true;
    for (int i = 0; i < 10; i ++) {
        Game g(13, 9); // width - y, height - x

        g.addSimple(0, 12); Position ne(0, 12);

        Position p0 = (g.isLegal(ActionType::NE, ne)) ?
                      g.move(ne, ActionType::NE) : ne;

        pass = (p0.x == ne.x) && (p0.y == ne.y);

        p0 = (g.isLegal(ActionType::S, ne)) ?
             g.move(ne, ActionType::S) : ne;

        pass = pass && (p0.x == ne.x+1) && (p0.y == ne.y);

        p0 = (g.isLegal(ActionType::W, ne)) ?
             g.move(ne, ActionType::W) : ne;

        pass = pass && (p0.x == ne.x) && (p0.y == ne.y-1);

        p0 = (g.isLegal(ActionType::SE, ne)) ?
             g.move(ne, ActionType::SE) : ne;

        pass = pass && (p0.x == ne.x) && (p0.y == ne.y);
    }
    ec.result(pass);

    ec.DESC("7x6, action needed to reach one position from another");

    pass = true;
    for (int i = 0; i < 10; i ++) {

        Game g(5, 5);

        g.addSimple(1, 1); Position simpos(1, 1);
        g.addFood(1, 2); Position foodpos(1, 2);

        pass = (Game::reachSurroundings(simpos, foodpos) == ActionType::E);

        g.addAdvantage(0, 1); Position adpos(0, 1);

        pass = pass && (Game::reachSurroundings(simpos, adpos) == ActionType::N);

        Position newpos(2, 0);

        pass = pass && (Game::reachSurroundings(simpos, newpos) == ActionType::SW);
    }
    ec.result(pass);
}


// - - - - - - - - - - G A M E - - - - - - - - - -

// Smoketest: constructor, copy constructor, destructor, number of pieces
void test_game_smoketest(ErrorContext &ec) {
    bool pass;

    ec.DESC("--- Test - Game - Smoketest ---");

    ec.DESC("constructor, empty game, default grid size, destructor");
    pass = true;
    for (int i = 0; i < 10; i ++) {
        Game g;

        pass = (g.getWidth() == 3 &&
                g.getHeight() == 3 &&
                g.getNumPieces() == 0);
    }
    ec.result(pass);

    ec.DESC("constructor with dimensions");
    pass = true;
    for (int i = 0; i < 10; i ++) {
        Game g(4, 5);

        pass = (g.getWidth() == 4 &&
                g.getHeight() == 5 &&
                g.getNumPieces() == 0);
    }
    ec.result(pass);

    ec.DESC("insufficient dimensions (exception generated)");
    pass = true;
    for (int i = 0; i < 10; i ++) {
        try {
            Game g(Game::MIN_WIDTH-1, 5);
            pass = false;
        } catch (InsufficientDimensionsEx &ex) {
            std::cerr << "Exception generated: " << ex << std::endl;
            pass = (ex.getName() == "InsufficientDimensionsEx");
        }
    }
    ec.result(pass);
}

// populate the game grid
void test_game_populate(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Game - Populate ---"); // note: piece smoke test needed first

    for (int run = 0; run < numRuns; run ++) {
        ec.DESC("3x3 grid, manual population");

        {
            Game g;

            pass = g.addSimple(0, 0);
            pass = pass && g.addStrategic(1, 1);
            pass = pass && g.addFood(0, 2);
            pass = pass && g.addFood(2, 1);
            pass = pass && g.addAdvantage(2, 2);

            pass = pass = pass &&
                    (g.getNumPieces() == 5) &&
                    (g.getNumAgents() == 2) &&
                    (g.getNumResources() == 3);

            ec.result(pass);
        }

        ec.DESC("4x5 grid, manual population");

        {
            Game g(4, 5);

            pass = g.addSimple(0, 0);
            pass = pass && g.addStrategic(1, 1);
            pass = pass && g.addFood(0, 2);
            pass = pass && g.addFood(2, 1);
            pass = pass && g.addAdvantage(2, 2);
            pass = pass && g.addSimple(4, 3);
            pass = pass && g.addAdvantage(2, 3);

            pass = pass && (! g.addFood(4, 3));
            pass = pass && (! g.addStrategic(0, 2));

            pass = pass &&
                          (g.getNumPieces() == 7) &&
                          (g.getNumAgents() == 3) &&
                          (g.getNumResources() == 4);

            ec.result(pass);
        }

        ec.DESC("4x5 grid, manual, out of bounds (exception generated)");

        {
            Game g(4, 5);

            pass = g.addSimple(0, 0);
            pass = pass && g.addStrategic(1, 1);
            pass = pass && g.addFood(0, 2);

            try {
                pass = pass && g.addAdvantage(4, 5);
                pass = false;
            } catch (OutOfBoundsEx &ex) {
                std::cerr << "Exception generated: " << ex << std::endl;
                pass = pass && (ex.getName() == "OutOfBoundsEx");
            }

            try {
                Position pos(6, 10);
                pass = pass && g.addStrategic(pos);
                pass = false;
            } catch (OutOfBoundsEx &ex) {
                std::cerr << "Exception generated: " << ex << std::endl;
                pass = pass && (ex.getName() == "OutOfBoundsEx");
            }

            ec.result(pass);
        }

        ec.DESC("3x3 grid, auto population");

        {
            Game g(3, 3, false);

            pass = (g.getNumAgents() == 2) &&
                    (g.getNumResources() == 4);

            ec.result(pass);
        }

        ec.DESC("4x5 grid, auto population");

        {
            Game g(4, 5, false);

            pass = (g.getNumAgents() == 5) &&
                   (g.getNumResources() == 10);

            ec.result(pass);
        }

        ec.DESC("9x9 grid, auto population");

        {
            Game g(9, 9, false);

            pass = (g.getNumAgents() == 20) &&
                   (g.getNumResources() == 40); // TODO sometimes this is 39

            if (! pass) std::cout << g.getNumAgents() << ' '
                << g.getNumResources() << ' ';

            ec.result(pass);
        }
    }
}

// Printing of a game
void test_game_print(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Game - Print ---");

    for (int run = 0; run < numRuns; run++) {

        ec.DESC("3x3 grid, automatic population");

        {
            Game g(3, 3, false);

            std::stringstream ss;
            ss << g;
            std::string line;
            getline(ss, line);
            std::regex re("Round [[:d:]]{1,3}");
            std::smatch m;
            std::regex_search(line, m, re);
            pass = (m.size() == 1);
//            if (! pass) std::cout << m[0] << ' ' << m[1] << ' ' << m.size() << std::endl;
            for (int i = 0; i < 3; i++) {
                getline(ss, line);
                std::regex re1("(\\[([[:alpha:]]{1}[[:d:]]{1,4}[ ]?|[ ]{5})\\]){3}");
                std::regex_search(line, m, re1);
                pass = pass && (m.size() == 3);
//                if (! pass) {
//                    std::cout << m[0] << ' ' << m[1] << ' ' << m.size() << std::endl;
//                }
            }
            getline(ss, line);
            std::regex re2("Status:");
            std::regex_search(line, m, re2);
            pass = pass && (m.size() == 1);

            ec.result(pass);
        }

        ec.DESC("7x6 grid, automatic population");

        {
            Game g(7, 6, false);

            std::stringstream ss;
            ss << g;
            std::string line;
            getline(ss, line);
            std::regex re("Round [[:d:]]{1,3}");
            std::smatch m;
            std::regex_search(line, m, re);
            pass = (m.size() == 1);
//            if (! pass) std::cout << m[0] << ' ' << m[1] << ' ' << m.size() << std::endl;
            for (int i = 0; i < 6; i++) {
                getline(ss, line);
                std::regex re1("(\\[([[:alpha:]]{1}[[:d:]]{1,4}[ ]?|[ ]{5})\\]){7}");
                std::regex_search(line, m, re1);
                pass = pass && (m.size() == 3);
//                if (! pass) {
//                    std::cout << m[0] << ' ' << m[1] << ' ' << m.size() << std::endl;
//                }
            }
            getline(ss, line);
            std::regex re2("Status:");
            std::regex_search(line, m, re2);
            pass = pass && (m.size() == 1);

            ec.result(pass);
        }
    }
}

// Playing and termination of a game
void test_game_play(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Game - Play ---");

    for (int run = 0; run < numRuns; run++) {

        ec.DESC("3x3 grid, manual, game w/o resources terminates immediately");

        {
            Game g; // manual = true, by default

            g.play(); // verbose = false, by default

            pass = (g.getNumResources() == 0);

            ec.result(pass);
        }

        ec.DESC("3x3 grid, manual, 1 simple, 1 resource");

        {
            Game g; // manual = true, by default
            g.addSimple(1, 1);
            g.addFood(2, 2);

            g.play(false); // verbose = false, by default

            pass = (g.getNumResources() == 0) &&
                   (g.getNumAgents() == 1);

            ec.result(pass);
        }

        ec.DESC("3x3 grid, manual, 1 simple, 2 resources");

        {
            Game g; // manual = true, by default
            g.addSimple(1, 1);
            g.addFood(2, 2);
            g.addAdvantage(1, 0);

            g.play(false); // verbose = false, by default

            pass = (g.getNumResources() == 0) &&
                   (g.getNumAgents() == 1);

            ec.result(pass);
        }

        ec.DESC("3x3 grid, manual, 1 simple, 3 resources");

        {
            Game g; // manual = true, by default
            g.addSimple(0, 0);
            g.addFood(0, 2);
            g.addFood(2, 2);
            g.addAdvantage(1, 0);

            g.play(false); // verbose = false, by default

            pass = (g.getNumResources() == 0) &&
                   (g.getNumAgents() == 1);

            ec.result(pass);
        }

        ec.DESC("3x3 grid, manual, 2 simple, 3 resources");

        {
            Game g; // manual = true, by default
            g.addSimple(0, 0);
            g.addSimple(0, 1);
            g.addFood(0, 2);
            g.addFood(2, 2);
            g.addAdvantage(1, 0);

            g.play(false); // verbose = false, by default

            pass = (g.getNumResources() == 0) &&
                   (g.getNumAgents() == 2);

            ec.result(pass);
        }

        ec.DESC("3x3 grid, manual, 3 simple, 3 resources");

        {
            Game g; // manual = true, by default
            g.addSimple(0, 0);
            g.addSimple(0, 1);
            g.addSimple(1, 1);
            g.addFood(0, 2);
            g.addFood(2, 2);
            g.addAdvantage(1, 0);

            g.play(false); // verbose = false, by default

            pass = (g.getNumResources() == 0) &&
                   (g.getNumAgents() == 3);

            ec.result(pass);
        }

        ec.DESC("3x3 grid, manual, 1 default strategic, 1 simple, 3 resources");

        {
            Game g; // manual = true, by default
            g.addSimple(0, 0);
            g.addStrategic(0, 1);
            g.addFood(0, 2);
            g.addFood(2, 2);
            g.addAdvantage(1, 0);

            g.play(false); // verbose = false, by default

            pass = (g.getNumResources() == 0) &&
                   (g.getNumStrategic() == 1) &&
                   (g.getNumSimple() == 1);

            ec.result(pass);
        }

        ec.DESC("3x3 grid, manual, 1 aggressive strategic, 3 resources");

        {
            Game g; // manual = true, by default
            g.addStrategic(0, 1, new AggressiveAgentStrategy(Game::STARTING_AGENT_ENERGY));
            g.addFood(0, 2);
            g.addFood(2, 2);
            g.addAdvantage(1, 0);

            g.play(false); // verbose = false, by default

            pass = (g.getNumResources() == 0) &&
                   (g.getNumStrategic() == 1);

            ec.result(pass);
        }

        ec.DESC("3x3 grid, manual, 1 aggressive strategic, 1 far simple, 3 res");

        {
            Game g; // manual = true, by default
            // In this configuration, the Simple and Strategic are far from each other
            // and they might or might not get close to each other before the
            // Resources run out
            g.addStrategic(0, 1, new AggressiveAgentStrategy(Game::STARTING_AGENT_ENERGY));
            g.addSimple(2, 1);
            g.addFood(0, 2);
            g.addFood(2, 2);
            g.addAdvantage(1, 0);

            g.play(false); // verbose = false, by default

            pass = (g.getNumResources() == 0) &&
                   (g.getNumStrategic() == 1 ) &&
                   (g.getNumSimple() <= 1); // randomized game play

            ec.result(pass);
        }


        ec.DESC("3x3 grid, manual, 1 aggressive strategic, 1 near simple, 3 res");

        {
            Game g; // manual = true, by default

            // In this configuration, the Simple gets an Advantage and when the
            // aggressive Strategic challenges it, the Strategic loses and disappears
            g.addSimple(0, 0);
            g.addStrategic(0, 1, new AggressiveAgentStrategy(Game::STARTING_AGENT_ENERGY));
            g.addFood(0, 2);
            g.addFood(2, 2);
            g.addAdvantage(1, 0);

            g.play(false); // verbose = false, by default

            pass = (g.getNumResources() == 0) &&
                   (g.getNumSimple() == 1) &&
                   (g.getNumStrategic() == 0);

            ec.result(pass);
        }

        ec.DESC("3x3 grid, manual, 1 def, 1 aggr, 1 simple, 2 resources");

        {
            Game g; // manual = true, by default
            // In this situation, the default flees, the aggressive attacks either
            // the default or the Simple, and the dies with it, leaving the other
            // one to win
            g.addStrategic(0, 0);
            g.addSimple(1, 0);
            g.addStrategic(0, 1, new AggressiveAgentStrategy(Game::STARTING_AGENT_ENERGY));
            g.addFood(0, 2);
            g.addFood(2, 2);

            g.play(false); // verbose = false, by default

            pass = (g.getNumResources() == 0) &&
                   ((g.getNumStrategic() == 1 && g.getNumSimple() == 0) ||
                    (g.getNumStrategic() == 0 && g.getNumSimple() == 1));

            ec.result(pass);
        }
    }
}
