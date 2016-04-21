// Hosna Zulali
// 101485552
// Extended Due Date for 85% of Total

#include "Strategic.h"
#include <sstream>

using namespace std;
using namespace Gaming;

    const char Strategic::STRATEGIC_ID = 'T';

    Strategic::Strategic(const Game &g, const Position &p, double energy, Strategy *s):Agent(g, p, energy)
    {
        __strategy = s;
    }

    Strategic::~Strategic()
    {
        // Blank
    }

    void Strategic::print(ostream &os) const
    {
        stringstream strstr;
        strstr << STRATEGIC_ID << __id;

        string s;
        getline(strstr,s);
        os << s;
    }

    ActionType Strategic::takeTurn(const Surroundings &s) const
    {
        return (*__strategy)(s);
    }
