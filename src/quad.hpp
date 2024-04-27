#pragma once

#include <raylib.h>
#include <vector>
#include <array>
#include "triangle.hpp"

class Quad
{
public:
    Quad();
    ~Quad();
    void SetDimensions(Vector2 a, Vector2 b, Vector2 c, Vector2 d);
    void CalculateIsRect();
    void CalculateSides();
    void Draw();
    bool IsVector2Inside(Vector2 p);
    bool IsReady;

private:
    Vector2 a;
    Vector2 b;
    Vector2 c;
    Vector2 d;
    Vector2 center;
    Triangle* tri_abd;
    Triangle* tri_bcd;
    Color color;
    bool is_rect;
    bool is_square;
    float sideab;
    float sidebc;
    float sidecd;
    float sideda;
    float diaginal_len;

    std::vector<Vector2> GetPoints();
    void CalculateCenter(Vector2 p1, Vector2 p2);
};
