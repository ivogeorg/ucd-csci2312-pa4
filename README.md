## CSCI 2312: Programming Assignment 4

_inheritance, polymorphism, board games, randomization_

* * *

### Goals

1. Get experience with inheritance, polymorphism, and class hierarchies in the domain of board turn-based strategic games.
2. Enrich your pallette of C++ tools to define complex behavior:
  1. Abstract and concrete classes for hierarchical behavior extension.
  2. `virtual` functions and overriding to specialize behavior while supporting polymorphism.
  3. _functors_ to specify dynamic object behavior.
  4. The `<random>` library to randomize object behavior.
  5. A `virtual` binary operator to implement object interaction.
  6. STL classes for data management.
3. Develop in _one go_ a small-scale semi-interactive game with bare-bones ASCII visualization.
4. Continue using git and Github.
5. Develop good coding style.

### Synopsis

PA4 leaves the clustering domain and gives a glimpse of the game domain. While it is a chance to put any C++ features we have covered to new use, its main goal is to give a fertile setting for dynamic (run-time) polymorphism of user types. You will create a class hierarchy with a rich tapestry of polymorphic behavior. You have to write quite a few more files than usual, though most are small: `Exceptions.cpp`, `Piece.cpp`, `Agent.cpp`, `Simple.cpp`, `Strategic.cpp`, `Resource.cpp`, `Food.cpp`, `Advantage.cpp`, `Game.cpp`, `DefaultAgentStrategy.cpp`, and `AggressiveAgentStrategy.cpp`. See the [Detailed Instructions](https://github.com/ivogeorg/ucd-csci2312-pa4/blob/master/README.md#detailed-instructions) at the bottom of this file.

PA4 is in the test-driven-development (TDD) style, just like the preceding assignments. It has 153 tests that your implementation should pass for full points. Because the different elements of the `Game` are quite intertwined, it is recommended that you follow roughly this order of implementation and testing:

1. `Game` smoke test.
2. `Game` printing.
3. `Piece` smoke test.
4. `Piece` printing.
5. `Game` population.
6. `Surroundings` smoke test.
7. _Action_ smoke test.
8. Other `Piece` tests.
9. _Randomization_ test.
9. `Game` play.

This assignment may be smaller in terms of the total lines of code relative to the preceding ones but is not trivial. It might take just as much time as the others since it introduces new language features and has several points of algorithmic complexity.

### Submission

You don't need to submit anything. Once you fork the repository (this is your **remote** repository on Github, aka **origin**), you will clone it to your development machine (this is your local repository), and start work on it. Commit your changes to your local repository often and push them up to the remote repository occasionally. Make sure you push at least once before the due date. At the due date, your remote repository will be cloned and tested automatically by the grading script. _**Note:** Your code should be in the **master** branch of your remote repository._

### Grading

An autograding script will run the test suite against your files. Your grade will be based on the number of tests passed. (E.g. if your code passes 3 out of 6 test cases, your score will be 50% and the grade will be the corresponding letter grade in the course's grading scale). The test suite for PA4 has __153__ tests. **Note:** The testing and grading will be done with fresh original copies of all the provided files. In the course of development, you can modify them, if you need to, but your changes will not be used. Only your `Exceptions.cpp`, `Piece.cpp`, `Agent.cpp`, `Simple.cpp`, `Strategic.cpp`, `Resource.cpp`, `Food.cpp`, `Advantage.cpp`, `Game.cpp`, `DefaultAgentStrategy.cpp`, and `AggressiveAgentStrategy.cpp` files will be used.

### Compiler

Your program should run on **GCC 4.9.0** or later, or **Clang 3.3** or later. No other compilers are supported.

### Due Date

The assignment is due on **Sun, Apr 17, at 23:59 Mountain time**. No late work. The last commit to your PA4 repository before the deadline will be graded.

### Honor Code

Free Github repositories are public so you can look at each other's code. Please, don't do that. You can discuss any programming topics and the assignments in general but sharing of solutions diminishes the individual learning experience of many people. Assignments might be randomly checked for plagiarism and a plagiarism claim may be raised against you.

### Use of libraries

You are encouraged to make maximum use of the Standard Library, especially the Standard Template Library (STL).

### Coding style

Familiarize yourself with and start following [coding style guidelines](http://courses.cms.caltech.edu/cs11/material/cpp/donnie/cppstyle.html). There are others on the Web. Pick one and be consistent. _**Note:** If you stumble on the Google C++ Style Guide, be advised that it has been heavily criticized by many leading C++ programmers. I don't advise you to follow it, especially the more advanced features. This Guide is for entry-level coders at Google who need to be able to work with their legacy code. It is not advisable for new projects and novice programmers._

### References

Operator overloading [guidelines](http://courses.cms.caltech.edu/cs11/material/cpp/donnie/cpp-ops.html). For the implementation of `virtual Piece &operator*(Piece &other)`, see this [example](https://github.com/ivogeorg/ucd-csci2312-pa4/blob/master/examples/virtual_operator.cpp).

A very good [C++ tutorial](http://www.learncpp.com/), including many topics we are covering.

Two websites with C++ Reference, [here](http://en.cppreference.com/w/) and [here](http://www.cplusplus.com/).

### Detailed Instructions

#### I. Overview

PA5 creates a simple board turn-based Game where `Piece`-s move around and interact. This is how a short run of the Game looks like in print:

```
Round 0
[T998 ][T1000][F1001]
[S999 ][     ][     ]
[     ][     ][F1002]
Status: Playing...
Round 1
[     ][     ][F1001]
[     ][     ][     ]
[S999 ][     ][F1002]
Status: Playing...
Round 2
[     ][     ][F1001]
[     ][     ][     ]
[     ][S999 ][F1002]
Status: Playing...
Round 3
[     ][     ][F1001]
[     ][     ][     ]
[     ][     ][S999 ]
Status: Playing...
Round 4
[     ][     ][F1001]
[     ][S999 ][     ]
[     ][     ][     ]
Status: Playing...
Round 5
[     ][     ][S999 ]
[     ][     ][     ]
[     ][     ][     ]
Status: Over!
```

`Piece`-s are of different type and have polymorphic (i.e. different) behavior. The class hierarchy is as follows:

![alt text](https://github.com/ivogeorg/ucd-csci2312-pa4/blob/master/images/piece_hier.png "Piece class hierarchy")

The dotted boxes represent abstract classes, the rest represent concrete classes. The codes in the grid above correspond to instantiations of the concrete classes, i.e. these are the code names/id-s of objects of type `Food` (e.d. `F333`), `Advantage` (e.g. `D456`), `Simple` (e.g. `S146`), and `Strategic` (e.g. `T987`). The game executes rounds, gives each piece which is still on the board a turn, and then it prints itself, letting the Piece-s fill in their code names in the appropriate positions.

#### II. The grid, coordinates, and positions

The **grid** is two-dimensional. It has a width and height. Each **position** has coordinates (x, y), with x indexing rows from top to bottom, and y indexing columns from left to right. Both x and y and 0-indexed. The following grid is a 4 x 5, i.e. width = 4 and height = 5, and so x runs from 0 to 4 and y runs from 0 to 3.

|||||
| --- |	--- |	--- |	--- |
| (0,0) |	(0,1) |	(0,2) |	(0,3) |
| (1,0) |	(1,1) |	(1,2) |	(1,3) |
| (2,0)	| (2,1)	| (2,2)	| (2,3) |
| (3,0)	| (3,1)	| (3,2)	| (3,3) |
| (4,0)	| (4,1)	| (4,2)	| (4,3) |

Internally, the grid is represented as a vector of size 4 * 5 = 20. The indices correspond to grid positions as follows:

|||||
| --- |	--- |	--- | --- |
| 0 |	1 |	2 |	3 |
| 4 |	5 |	6 |	7 |
| 8	| 9	| 10 |	11 |
| 12 |	13 |	14 |	15 |
| 16	| 17	| 18	| 19 |

The `Game` uses both representations as they are good for different purposes. You have to come up with simple formulae to convert back and forth.

##### 2.1 Surroundings

The behavior of the `Piece`-s is based on what's around them. The `Surroundings` structure is a **3 x 3 grid** which creates a map of the 8 positions which surround the current position of a `Piece`. The 8 positions have the following relation with the position (x, y) of the `Piece`:

||||
| --- | --- | --- |
| (-1,-1) | (-1,0) | (-1,1) |
| (0,-1) | (x,y) | (0,1) |
| (1,-1) | (1,0) | (1,1) |
 

Surroundings holds an array of length 9 and the indices correspond to the positions around a Piece as follows:

||||
| --- | --- | --- |
| 0 | 1 | 2 |
| 3 |	4	| 5 |
| 6 |	7 | 8 |

A `Surroundings` structure's array is filled with values of the enumerated type `PieceType`: `EMPTY`, `INACCESSIBLE` (i.e. outside the `Game` grid), `SIMPLE`, `STRATEGIC`, `FOOD`, `ADVANTAGE`, and `SELF`. `SELF` is always in the middle, at index **4**.

#### III. Game play

The behavior of `Piece`-s is based on **actions**, which are picked by each `Piece`'s strategy. Each `Piece` on the `Game` board gets a turn each `Game` round.

##### 3.1 Action

Available actions are captured in the enumerated class `ActionType`: `N`, `NE`, `NW`, `E`, `W`, `SE`, `SW`, `S`, and `STAY`. The compass directions correspond to the 8 directions a `Piece` can move in a grid from its current position. `STAY` means no motion, i.e. stay where you are. 

`Resource`-s don't move so they always return `STAY`.

`Agent`-s can move in all directions that are legal depending on the current state of the `Game`, or `STAY` in place.

##### 3.2 Interaction

As `Piece`-s move around the grid they run into others. Each time that happens there is an **interaction** taking place. This is captured by the pure `virtual operator*` (aka _interaction operator_) that `Piece`-s overload. The interactions are as follows:

1. When an `Agent` moves onto a `Resource`, it consumes it completely.
2. When an `Agent` moves onto another `Agent`, they compete and might either both die, or one dies and the other wins.

##### 3.3 Strategies

Picking an `ActionType` based on the `Surroundings` is captured in the `Strategy` class. The `Simple` agent doesn't have a separate `Strategy` object, while the `Strategic` agent has a dedicated `Strategy` object.

The `Simple` agent's behavior/strategy is as follows:

1. It does not challenge other agents (i.e. it doesn't move onto them).
2. If there are adjacent Resource-s, returns a motion to one of them.
3. If there aren’t adjacent Resource-s, returns a move to an adjacent empty position.
4. If there aren't adjacent empty position, returns a STAY.

The default `Strategic` agent's strategy (captured in a `DefaultAgentStrategy` object) is as follows:

1. If there are adjacent Advantage-s, returns a motion to one of them. That is, it prefers Advantage to Food.
2. lf there aren't adjacent Advantage-s, returns a move to an adjacent Food.
3. If there arent' adjacent Food-s, return's a move to an adjacent empty position.
4. If there aren't adjacent empty positions, it returns a move to an adjacent Simple agent (i.e. attacking it).
5. If no adjacent Simple agents, returns STAY.

The _aggressive_ `Strategic` agent's strategy (captured in an `AggressiveAgentStrategy` object) is as follows:

1. If the Agent's energy >= aggressiveness threshold AND there are any adjacent Agent-s, challenge one of them.
2. Else if adjacent Advantage-s, move onto an Advantage.
3. Else if adjacent Food-s, move onto an Food.
4. Else if adjacent empty positions, move onto an empty position.
5. Else STAY.

##### 3.4 Randomization

Because in the above strategies there could be more than one of each kind of `Piece` types that are relevant to an `Agent`'s active behavior, an implemented functor class `PositionRandomizer` is provided in `Gaming.h`, and a `randomPosition` function in `Game` making use of it. Using this function reduces any bias in the motion of an `Agent` that might arise from the particular way it traverses its `Surroundings`. For example, if you were to always pick the first `Piece` of a particular type from the `Surroundings` to act upon, there would be an "upward" or "northward" bias of the motion of `Agent`-s since they traverse their `Surroundings` structure naturally from top to bottom and from left to right per the conventions mentioned in the previous section.

The function `randomPosition` takes a `std::vector<int>` of positions (as indices in the `Surroundings` array) where you found one or another kind or `Piece` (one vector for each kind) and returns a random `Position` (as an (x, y) in the same `Surroundings` grid) for the `Agent` to move onto (in implementation of its `Strategy`).

##### 3.5 Turns

The `Game` gives each `Piece` on the grid a turn in a top-left row-wise bottom-right manner. A `Piece`'s turn consists of the following:

1. The `Game` constructs the `Surroundings` of a `Piece`.
2. The `Game` calls the polymorphic `takeTurn` on the `Piece`, which returns an `ActionType`.
3. If the action is legal, the `Game` moves the `Piece` by calling `setPosition` on the `Piece`.
4. If the new position is non-empty, the Game calls the _interaction_ `operator*` on the two `Piece`-s (i.e. `p1 * p2`), which polymorphically performs one of the two interactions described above.
5. The `Game` checks if any of the two `Piece`-s have become unviable, by calling `isViable` on them, and removes the unviable ones from the board.

##### 3.6 Rounds

The `Game` is organized in a series of rounds. Each round effectively gives a turn to all the `Piece`-s which are still viable and on the `Game` grid. Though the `Game` is very simple, the `Game::round()` function is fairly complex due to all the little details that have to be taken care of. A round consists of the following steps:

1. Go through all the `Piece`-s that are still viable and on the grid (this doesn't change between rounds) and:
  1. If a `Piece` has not taken a turn, give it a turn. Use `Piece::getTurned()`.
  2. Call the `Piece::setTurned(true)` to avoid giving a moving `Piece` more than one turn per round (e.g. if it happens to move to a grid position you haven't covered in the current round).
  3. Perform the turn and implement all the consequences of the turn (e.g. interaction with another `Piece`).
  4. Delete any `Piece`-s which interacted and, as a result, became unviable.
2. Go through all the `Piece`-s that are still viable and on the grid after the current round, and:
  1. Call the polymorphic `Piece::age()`.
  2. Call the `Piece::setTurned(false)` to reset the turn for the next round.
  3. Delete any `Piece`-s which have aged to zero.

Some guidelines for implementing `Game::round()`:

1. Do it incrementally and use the tests to build in more and more detail.
2. It might be intuitive that you cycle through the `Game` grid for each round, but it is much better to cycle through a `std::set` of all the currently occupied positions of the grid. Cycling through the grid won't be able to handle some of the finer cases. Cycling through the `set`, if done correctly, will ensure a fair turn for all the `Pieces`.
3. Notice that a `Piece` might become unviable before its turn comes (e.g. a `Resource` gets consumed by an `Agent` that moves ahead of it, or an `Agent` gets challenged by another, and one or both die as a result).
4. Notice that a `Piece` might move to a new position, either through an interaction or through a move to a previously free position. In the first case, the position was already occupied, so it is still in the `set`. In the second case, the position was empty, so needs to be added to the `set`.

#### IV. Game constants

The following `static` constants have been used in the implementation of the game and are declared but not defined in the header files. You have to define them in the corresponding cpp files:

```
Advantage::ADVANTAGE_ID = 'D'
Advantage::ADVANTAGE_MULT_FACTOR = 2.0
Agent::AGENT_FATIGUE_RATE = 0.3
AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD = Game::STARTING_AGENT_ENERGY * 0.75
Food::FOOD_ID = 'F'
Game::NUM_INIT_AGENT_FACTOR = 4
Game::NUM_INIT_RESOURCE_FACTOR = 2
Game::MIN_WIDTH = 3
Game::MIN_HEIGHT = 3
Game::STARTING_AGENT_ENERGY = 20
Game::STARTING_RESOURCE_CAPACITY = 10
Resource::RESOURCE_SPOIL_FACTOR = 1.2
Simple::SIMPLE_ID = 'S'
Strategic::STRATEGIC_ID = 'T' 
```

#### V. Test suite

The `main.cpp`, `GamingTests.h`, `GamingTests.cpp`, `ErrorContext.h`, and `ErrorContext.cpp` contain the test suite for PA4. There is nothing to change here except to comment out tests in `main.cpp` that you haven't reached as you implement incrementally.

There are tests that generate exceptions which are caught and reported to `std::cerr`, which is not temprally interleaved with `std::out`. This may cause the exceptions to appear in "unexpected" places relative to the handler code. Note that this is only an artifact of the different regimes of flushing of the two output stream objects. 

Note that `Game` play tests can be declared `verbose` to print out the `Game` rounds. This is for you to implement. 

Finally, note that, due to the randomization mentioned above, the three runs of a `verbose == true` `Game` play test are likely to differ (i.e. the course of the `Game` is different).

Again, because the different elements of the `Game` are closely intertwined, it is recommended that you follow the following rough order of implementation and testing:

1. `Game` smoke test.
2. `Game` printing.
3. `Piece` smoke test.
4. `Piece` printing.
5. `Game` population.
6. `Surroundings` smoke test.
7. _Action_ smoke test.
8. Other `Piece` tests.
9. _Randomization_ test.
9. `Game` play.

#### VI. Classes

##### 6.1 `Game`

The `Game`-related headers are: `Game.h`, and `Gaming.h`. You will need to write a `Game.cpp` file. `Gaming.h` contains declarations of enumeration classes, structures, and inline classes which are provided for you.

##### 6.2 `Piece`

You have headers for all the `Piece` class hierarchy: `Piece.h`, `Agent.h`, `Resource.h`, `Simple.h`, `Strategic.h`, `Food.h`, and `Advantage.h`. Each will require the corresponding cpp file with implementation of the methods.

In addition, you have the abstract class header (no cpp necessary) `Strategy.h`, and the headers for two concrete classes which extend the abstract class: `DefaultAgentStrategy.h`, and `AggressiveAgentStrategy.h`. You will need to write two corresponding cpp files to implement these classes.

##### 6.3 `Piece` viability, energy, capacity, aging, finishing

The `Game` creates `Agent`-s with `STARTING_AGENT_ENERGY` and `Resource`-s with `STARTING_RESOURCE_CAPACITY`.

`Piece`-s age every round. Notice that `Piece::age()` is pure `virtual`. `Agent`-s age by _subtracting_ `AGENT_FATIGUE_RATE` from their energy, while `Resource`-s age by _dividing_ their capacity by the `RESOURCE_SPOIL_FACTOR`.

`Piece`-s are _viable_ while they are _**not** finished_ (`Piece::isFinished()`) AND their energy/capacity is _greater than 0.0_. Non-viable `Piec`e-s are removed at the end of each `Game` round.

`Piece::finish()` is called by any `Resource` which gets consumed or `Agent` which loses a challenge with another `Agent`. Specifically, it is called in the implementation of the double-dispatch `virtual` interaction operator `operator*()`. See next section for details on the operator.

##### 6.4 Interaction, energy, capacity, `Food`, and `Advantage`

Upon interaction between two `Piece`-s, energy/capacity is transferred as follows:

1. When two Agent-s interact, their energies are compared:
  1. If equal, both Agent-s call Piece::finish() and are taken out of the Game at the end of the round.  
  2. If unequal, the Agent with the larger wins, the smaller energy is subtracted from its energy, and the losing Agent calls Piece::finish() and is taken out of the Game at the end of the round.

2. When an Agent and a Resource interact, the Resource-s capacity is added to the Agent-s energy, the Resource calls Piece::finish() and is taken out of the Game at the end of the round. Notice that Resource::getCapacity is virtual and Advantage overrides it. The amount of capacity that is added to the Agent's energy is as follows:
  1. For Food, its capacity.  
  2. For Advantage, its capacity * `ADVANTAGE_MULT_FACTOR`.

For the implementation of the `Piece::operator*()`, take a look at [this](https://github.com/ivogeorg/ucd-csci2312-pa4/blob/master/examples/virtual_operator.cpp) page.

##### 6.5 `Game` dynamics

A `Game` can be populated manually (default) or automatically. For automatic population, use the following numbers have been useful:

```
__numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
__numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;
unsigned int numStrategic = __numInitAgents / 2;
unsigned int numSimple = __numInitAgents - numStrategic;
unsigned int numAdvantages = __numInitResources / 4;
unsigned int numFoods = __numInitResources - numAdvantages;
```

The `Game` is **over** when there are _no more `Resource`-s_ left on the grid. Note that this includes the rare case when `Agent`-s are taken off the board before all `Resource`-s have been consumed. The latter will age and disappear on their own.

The default `Game::Game()` constructor creates a **3 x 3** grid.

##### 6.5 `Game` population randomization

To randomize the positions of the Piece-s during automatic population, you can use code like this:

```C++
// simple pseudo-random number generator
// sufficient for our casual purposes
std::default_random_engine gen;
std::uniform_int_distribution<int> d(0, __width * __height);

// populate Strategic agents
while (numStrategic > 0) {
    int i = d(gen); // random index in the grid vector
    if (__grid[i] == nullptr) { // is position empty
        Position pos(i / __width, i % __width);
        __grid[i] = new Strategic(*this, pos, Game::STARTING_AGENT_ENERGY);
        numStrategic --;
    }
}

// populate Simple agents
// ...

// Note: you can reuse the generator
```

##### 6.6 `Agent` action randomization

Often and `Agent` will have more than one `Piece` of the same type in its `Surroundings`, and will have to pick which one of them to go to. To randomize the actions of `Agent`-s during game play, use the `Game::randomPosition`. This function uses the functor `PositionRandomizer` defined in `Gaming.h`:

```c++
class PositionRandomizer {
    std::default_random_engine __gen;
    std::uniform_int_distribution<int> *__dist[10];

public:
    PositionRandomizer() {
        for (int i = 0; i < 10; i++)
            __dist[i] = new std::uniform_int_distribution<int>(0, i);
    }

    ~PositionRandomizer() {
        for (int i = 0; i < 10; i++) delete __dist[i];
    }

    const Position operator()(const std::vector<int> &positionIndices) {
        if (positionIndices.size() == 0) throw PosVectorEmptyEx();

        int posIndex = (*__dist[positionIndices.size() - 1])(__gen);
        return Position(
                (unsigned) (positionIndices[posIndex] / 3),
                (unsigned) (positionIndices[posIndex] % 3));
    }
};
```

##### 6.7 RTTI & `std::dynamic_cast`

For the implementation of some functions, e.g. `Game::getNumSimple()`, you will need to know the runtime/dynamic derived type of an _upcast_ object (i.e. that is pointed to by a `Piece*` pointer). This is called _runtime type information (RTTI)_ and the following code illustrates the use of the C++ RTTI facility `std::dynamic_cast<>`:

```C++
// dynamic_cast returns a pointer of the argument type
// or NULL if the derived type of the object is not of
// the argument type
unsigned int Game::getNumSimple() const {
    unsigned int numAgents = 0;

    for (auto it = __grid.begin(); it != __grid.end(); ++it) {
        Simple *simple = dynamic_cast<Simple*>(*it);
        if (simple) numAgents ++;
    }

    return numAgents;
}
```

More on `dynamic_cast` in the [C++ Reference](http://en.cppreference.com/w/cpp/language/dynamic_cast).

##### 6.8 `std::set`

As mentioned above, `std::set` might be useful in the implementation of `Game::round()`. The following code contains a contrived example which you might find helpful:

```C++
#include <iostream>
#include <set>

int main() {
    std::set<int> iset;
    iset.insert(1);
    iset.insert(2);
    iset.insert(3);
    iset.insert(5);
    iset.insert(6);
    iset.insert(8);

    for (auto it = iset.begin(); it != iset.end(); ) {
        int elementToSearch = 6;
        std::cout << "Iterating through " << *it << ".";
        if (*it == 2) {
            std::cout << " Inserting 0." << std::endl;
            iset.insert(0);
            ++it;
        } else if (*it <= 3) {
            std::cout << std::endl;
            ++it;
        } else {
            std::cout << " Searching for " << elementToSearch << ". ";
            auto search = iset.find(elementToSearch);
            if (search != iset.end()) {
                // Note: std::distance is the way to compare iterators but it requires bidirectional or random-access
                // iterators to work in both directions (since they have to be mutually reachable by incrementing)
                // these iterators are not implemented for std::set in the Standard Library, and implementing one
                // is beyond the scope of this assignment, we resort to using the following hack to give us what we
                // need.
                int d = elementToSearch - *it;
                std::cout << "Found " << elementToSearch << ". Distance from " << *it << " is " << d << ". Erasing." <<
                std::endl;
                if (d == 0) {
                    it = iset.erase(search); // if erasing the current element, erase returns an iterator to the next
                } else {
                    iset.erase(search); // if erasing another element, we need to increment the iterator ourselves
                    ++it;
                }
            } else {
                std::cout << "No " << elementToSearch << " found." << std::endl;
                ++it;
            }
        }
    }

    for (int i: iset) std::cout << i << std::endl;

    return 0;
}
```

In particular, notice that `std::set::insert()` does not invalidate any iterators, and `std::set::erase()` only invalidates the iterator to the current element, returning an iterator to the next element. More on `std::set` in the [C++ Reference](http://en.cppreference.com/w/cpp/container/set).

* * * 

#### VII. TODO

_This section concerns future revisions of this assignment._

1. (Section [6.3](https://github.com/ivogeorg/ucd-csci2312-pa4/blob/master/README.md#63-piece-viability-energy-capacity-aging-finishing)) `Piece::finish()` is called by any `Resource` which gets consumed or `Agent` which loses a challenge with another `Agent`. Specifically, it is called in the implementation of the double-dispatch `virtual` interaction operator `operator*()`. See next section for details on the operator. **TODO: This is a game rule, and therefore should be _pulled up_ to the abstract classes. The leaf classes should not be relied upon to implement the game rules faithfully. This will open the possibility for an open implementation of leaf classes by students and team tournaments.**

2. Add tests for:
  1. Randomization in:
    1. Automatic game population.
    2. Gameplay.
  2. Rule enforcement in:
    1. Actions.
    2. Interaction.
    3. Termination.
  3. Fairness in:
    1. Gameplay.
  4. Exception throws.
  
3. Consider alternative game termination conditions.

4. Explain forward class declarations used to avoid circular header includes.

5. Remove inlines.

6. Add instructions for printing the game, in particular:
  1. The use of `std::stringstream` for dynamic stream formatting. See [this SO thread](http://stackoverflow.com/questions/1532640/which-iomanip-manipulators-are-sticky).
  2. The use of `Piece::operator<<()` and `virtual Piece::print()`.

7. Improve exception coverage.

8. Write and generate Doxygen documentation.

9. Elaborate on the turn taking and the methods (documentation).
