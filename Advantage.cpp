// Hosna Zulali
// 101485552
// Extended Due Date for 85% of Total


#include "Advantage.h"
#include <sstream>

using namespace std;
using namespace Gaming;

const char Advantage::ADVANTAGE_ID = 'D';
const double Advantage::ADVANTAGE_MULT_FACTOR = 2.0;

    Advantage::Advantage(const Game &g, const Position &p, double capacity):Resource(g,p,capacity)
    {
        // Blank
    }

    Advantage::~Advantage()
    {
        // Blank
    }

    void Advantage::print(ostream &os) const
    {
        stringstream strstr;
        strstr << ADVANTAGE_ID << __id;

        string s;
        getline(strstr,s);

        os << s;
    }

    double Advantage::getCapacity() const
    {
        return (__capacity * ADVANTAGE_MULT_FACTOR);
    }

    double Advantage::consume()
    {
        double surr = getCapacity();

        __capacity = 0;

        finish();

        return surr;
    }