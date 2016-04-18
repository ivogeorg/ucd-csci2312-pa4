//
// Created by HosZul on 4/1/2016.
//
#include "Exceptions.h"

namespace Gaming
{
    void GamingException::setName(std::string name)
    {
        __name = name;
    }

    std::ostream &operator << (std::ostream &os, const GamingException &ex)
    {
        os << ex.getName() << std::endl;
        return os;
    }

    DimensionEx::DimensionEx(unsigned expWidth, unsigned expHeight, unsigned width, unsigned height)
    {
        __width = width;
        __exp_width = expWidth;
        __height = height;
        __exp_height = expHeight;
        __name = "DimensionEx";
    }

    unsigned DimensionEx::getWidth() const
    {
        return __width;
    }

    unsigned DimensionEx::getExpWidth() const
    {
        return __exp_width;
    }

    unsigned DimensionEx::getHeight() const
    {
        return __height;
    }

    unsigned DimensionEx::getExpHeight() const
    {
        return __height;
    }

    void InsufficientDimensionsEx::__print_args(std::ostream &os) const
    {
      // os << getExpHeight() <<
    }

    InsufficientDimensionsEx::InsufficientDimensionsEx(unsigned minWidth, unsigned minHeight, unsigned width, unsigned height) : DimensionEx(minWidth, minHeight, width, height)
    {
        setName("InsufficientDimensionsEx");
    }

    void OutOfBoundsEx::__print_args(std::ostream &os) const
    {
        os << "Name: " << __name << std::endl;
        os << "Game Grid: " << __exp_height << 'x' << __exp_width << std::endl;
        os << "Coordinate: ("<< __width<< "," << __height << ")" << std::endl;
    }

    OutOfBoundsEx::OutOfBoundsEx(unsigned maxWidth, unsigned maxHeight, unsigned width, unsigned height) : DimensionEx(maxWidth, maxHeight, width, height)
    {
        __name = "OutOfBounds";
    }

    void PositionEx::__print_args(std::ostream &os) const
    {
       os << "Name: " << __name << std::endl;
        os << "Coordinate: (" << __x << "," << __y << ")" << std:: endl;
    }

    PositionEx::PositionEx(unsigned x, unsigned y)
    {
     __x = x;
        __y = y;
        __name = "PoisitionEx";
    }

    PositionNonemptyEx::PositionNonemptyEx(unsigned x, unsigned y) : PositionEx(x,y)
    {
        __name = "PositionNonEmptyEx";
    }

    PositionEmptyEx::PositionEmptyEx(unsigned x, unsigned y) : PositionEx(x,y)
    {
        __name = "PositionEmptyEx";
    }

    void PosVectorEmptyEx::__print_args(std::ostream &os) const
    {
        os << "Name: " << __name;
    }

    PosVectorEmptyEx::PosVectorEmptyEx()
    {
        __name = "PosVectorEmptyEx";
    }
}