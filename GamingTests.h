//
// Created by Ivo Georgiev on 11/22/15.
//

#ifndef PA5GAME_GAMINGTESTS_H
#define PA5GAME_GAMINGTESTS_H


#include "ErrorContext.h"

using namespace Testing;


// - - - - - - - - - Tests: class Piece - - - - - - - - - -

// Smoketest: constructor, copy constructor, destructor, resources
void test_piece_smoketest(ErrorContext &ec);

// Piece id-s, names, and printing
void test_piece_print(ErrorContext &ec, unsigned int numRuns);

// Piece aging and viability
void test_piece_aging(ErrorContext &ec, unsigned int numRuns);

// Piece energy/capacity
void test_piece_energy(ErrorContext &ec, unsigned int numRuns);

// Taking turns
void test_piece_turntaking(ErrorContext &ec, unsigned int numRuns);

// Piece interaction operator*
void test_piece_interaction(ErrorContext &ec, unsigned int numRuns);


// - - - - - - - - - Tests: struct Surroundings - - - - - - - - - -

// Surroundings (vector of enums of type PieceType)
void test_surroundings_smoketest(ErrorContext &ec);


// - - - - - - - - - Tests: enum ActionType - - - - - - - - - -

// Action smoke test
void test_action_smoketest(ErrorContext &ec);


// - - - - - - - - - Tests: class Game - - - - - - - - - -

// Smoketest: constructor, copy constructor, destructor, number of pieces
void test_game_smoketest(ErrorContext &ec);

// Population of the game grid
void test_game_populate(ErrorContext &ec, unsigned int numRuns);

// Printing of a game
void test_game_print(ErrorContext &ec, unsigned int numRuns);

// Playing and termination of a game
void test_game_play(ErrorContext &ec, unsigned int numRuns);

#endif //PA5GAME_GAMINGTESTS_H
