## CSCI 2312: Programming Assignment 4   \<\<IN PROGRESS\>\>

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

PA4 leaves the clustering domain and gives a glimpse of the game domain. While it is a chance to put any C++ features we have covered to new use, its main goal is to give a fertile setting for dynamic (run-time) polymorphism of user types. You will create a class hierarchy with a rich tapestry of polymorphic behavior. You have to write quite a few more files than usual, though most are small: `Exceptions.cpp`, `Piece.cpp`, `Agent.cpp`, `Simple.cpp`, `Strategic.cpp`, `Resource.cpp`, `Food.cpp`, `Advantage.cpp`, `Game.cpp`, `DefaultAgentStrategy.cpp`, and `AggressiveAgentStrategy.cpp`.

PA4 is in the test-driven-development (TDD) style, just like the preceding assignments. It has 153 tests that your implementation should pass for full points. Because the different elements of the `Game` are quite intertwined, it is recommended that you follow roughly this order of implementation and testing:

1. Game smoke test.
2. Game printing.
3. Piece smoke test.
4. Piece printing.
5. Game populate.
6. Surroundings smoke test.
7. Action smoke test.
8. Other Piece tests.
9. Game play.

This assignment may be smaller in terms of the total lines of code relative to the preceding ones but is not trivial. It might take just as much time as the others since it introduces new language features and has several points of algorithmic complexity.

![alt text](https://github.com/ivogeorg/ucd-csci2312-pa4/blob/master/images/piece_hier.png "Piece class hierarchy")

