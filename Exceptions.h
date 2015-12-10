//
// Created by Ivo Georgiev on 12/4/15.
//

#ifndef PA5GAME_EXCEPTIONS_H
#define PA5GAME_EXCEPTIONS_H

#include <iostream>

namespace Gaming {

    class GamingException {
    protected:
        std::string __name;
        virtual void __print_args(std::ostream &os) const = 0;
        void setName(std::string name);
    public:
        std::string getName() const { return __name; };
        friend std::ostream &operator<<(std::ostream &os, const GamingException &ex);
    };

    class DimensionEx : public GamingException {
    protected:
        unsigned __exp_width, __exp_height, __width, __height;
    public:
        DimensionEx(unsigned expWidth, unsigned expHeight, unsigned width, unsigned height);
        unsigned getExpWidth() const;
        unsigned getExpHeight() const;
        unsigned getWidth() const;
        unsigned getHeight() const;
    };

    class InsufficientDimensionsEx : public DimensionEx {
        void __print_args(std::ostream &os) const override;

    public:
        InsufficientDimensionsEx(unsigned minWidth, unsigned minHeight, unsigned width, unsigned height);
    };

    class OutOfBoundsEx : public DimensionEx {
        void __print_args(std::ostream &os) const override;

    public:
        OutOfBoundsEx(unsigned maxWidth, unsigned maxHeight, unsigned width, unsigned height);
    };

}



#endif //PA5GAME_EXCEPTIONS_H
