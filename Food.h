//
// Created by Ivo Georgiev on 11/22/15.
//

#ifndef PA5GAME_FOOD_H
#define PA5GAME_FOOD_H

#include "Game.h"
#include "Resource.h"

namespace Gaming {

    class Food : public Resource {
    private:
        static const char FOOD_ID;

    public:
        Food(const Game &g, const Position &p, double capacity);
        ~Food();

        PieceType getType() const override { return PieceType::FOOD; }

        void print(std::ostream &os) const override;
    };

}


#endif //PA5GAME_FOOD_H
