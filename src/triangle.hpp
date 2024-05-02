#pragma once
#include <raylib.h>
#include "angle.hpp"

class Triangle {
    public:
        Triangle(Vector2 a, Vector2 b, Vector2 c);
        ~Triangle();
        Vector2 a;
        Vector2 b;
        Vector2 c;
        Angle* alpha;
        Angle* beta;
        Angle* gamma;
        float sidea;
        float sideb;
        float sidec;
        bool IsVecIn(Vector2 p);

    private:
        void CalculateSides();
        void CalculateAngles();
};
