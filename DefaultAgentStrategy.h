//
// Created by Ivo Georgiev on 12/8/15.
//

#ifndef PA5GAME_DEFAULTAGENTSTRATEGY_H
#define PA5GAME_DEFAULTAGENTSTRATEGY_H

#include "Strategy.h"

namespace Gaming {

    class DefaultAgentStrategy : public Strategy {
    public:

        DefaultAgentStrategy();
        ~DefaultAgentStrategy();
        ActionType operator()(const Surroundings &s) const override;
    };

}

#endif //PA5GAME_DEFAULTAGENTSTRATEGY_H
