// Hosna Zulali
// 101485552
// Extended Due Date for 85% of Total

#include "Exceptions.h"

using namespace std;
using namespace Gaming;

    void GamingException::setName(string name)
    {
        __name = name;
    }

    namespace Gaming
    {
        ostream &operator<<(ostream &os, const GamingException &ex)
        {
            os << ex.getName() << endl;
            return os;
        }
    }

    DimensionEx::DimensionEx(unsigned expWidth, unsigned expHeight, unsigned width, unsigned height)
    {
        __width = width;
        __height = height;
        __exp_width = expWidth;
        __exp_height = expHeight;
    }

    unsigned DimensionEx::getWidth() const
    {
        return __width;
    }

    unsigned DimensionEx::getHeight() const
    {
        return __height;
    }

    unsigned DimensionEx::getExpWidth() const
    {
        return __exp_width;
    }

    unsigned DimensionEx::getExpHeight() const
    {
        return __exp_height;
    }

    void InsufficientDimensionsEx::__print_args(std::ostream &os) const
    {
        // Blank
    }

    InsufficientDimensionsEx::InsufficientDimensionsEx(unsigned minWidth, unsigned minHeight, unsigned width, unsigned height):DimensionEx(minWidth,minHeight,width,height)
    {
        __name = "InsufficientDimensionsEx";
    }

    void OutOfBoundsEx::__print_args(std::ostream &os) const
    {
        os << __name << endl;
        os << __exp_height << 'x' << __exp_width << endl;
        os <<  __width <<" , "<< __height ;
    }

    OutOfBoundsEx::OutOfBoundsEx(unsigned maxWidth, unsigned maxHeight, unsigned width, unsigned height): DimensionEx(maxWidth,maxHeight,width,height)
    {
        __name = "OutOfBoundsEx";
    }

    void PositionEx::__print_args(std::ostream &os) const
    {
        os <<  __name << endl;
        os <<__x <<","<<__y;
    }

    PositionEx::PositionEx(unsigned x, unsigned y)
    {
        __x = x;
        __y = y;
    }

    PositionNonemptyEx::PositionNonemptyEx(unsigned x, unsigned y) : PositionEx(x,y)
    {
        __name = "PositionNonemptyEx";
    }

    PositionEmptyEx::PositionEmptyEx(unsigned x, unsigned y) : PositionEx(x,y)
    {
        __name = "PositionEmptyEx";
    }

    void PosVectorEmptyEx::__print_args(std::ostream &os) const
    {
        os << __name;
    }

    PosVectorEmptyEx::PosVectorEmptyEx()
    {
        __name = "PosVectorEmptyEx";
}