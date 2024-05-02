#pragma once

#include <raylib.h>
#include <vector>
#include <array>
#include "triangle.hpp"

class Quad
{
public:
    Quad(Vector2 a, Vector2 b, Vector2 c, Vector2 d, bool orderVectors = false);
    ~Quad();

    void CalculateIsRect();
    void CalculateSides();
    void CalculateIsTilted();
    void Draw();
    bool IsVector2In(Vector2 p);
    bool IsReady;

private:
    Vector2 a;
    Vector2 b;
    Vector2 c;
    Vector2 d;
    Vector2 center;
    Angle* alpha;
    Angle* beta;
    Angle* gamma;
    Angle* delta;
    bool is_tilted;
    bool is_square;
    bool is_rect;
    float sideab;
    float sidebc;
    float sidecd;
    float sideda;
    float diaginal_len;
    Triangle* tri_abd;
    Triangle* tri_bcd;
    Color color;

    void OrderVectors(Vector2 a, Vector2 b, Vector2 c, Vector2 d);
    std::vector<Vector2> GetPoints();
    void CalculateCenter(Vector2 p1, Vector2 p2);
    bool AreAllSidesEqual();
    bool IsVecInRect(Vector2 p);
    bool IsVecInDefault(Vector2 p);
};
