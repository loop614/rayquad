#pragma once
#include <raylib.h>
#include "angle.hpp"

class Triangle {
    public:
        Triangle();
        void Init();
        Vector2 a;
        Vector2 b;
        Vector2 c;
        Angle alpha;
        Angle beta;
        Angle gamma;
        float sidea;
        float sideb;
        float sidec;

    private:
        void CalculateSides();
        void CalculateAngles();
};