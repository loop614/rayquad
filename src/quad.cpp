#include "quad.hpp"
#include <raymath.h>
#include <iostream>
#include <map>

Quad::Quad(Vector2 a, Vector2 b, Vector2 c, Vector2 d, bool orderVectors)
{
    if (orderVectors) {
        Vector2 root = Vector2{0,0};
        float min = std::numeric_limits<float>::max();
        float max = 0;
        for (Vector2 vec2 : {a, b, c, d}) {
            float d = Vector2DistanceSqr(root, vec2);
            if (d < min) {
                min = d;
                this->d = {vec2.x, vec2.y};
            }
            if (d > max) {
                max = d;
                this->b = {vec2.x, vec2.y};
            }
        }
        std::array<Vector2, 2> othertwo;
        size_t index = 0;
        for (Vector2 vec2 : {a, b, c, d}) {
            if (this->b.x == vec2.x && this->b.y == vec2.y) {
                continue;
            }
            if (this->d.x == vec2.x && this->d.y == vec2.y) {
                continue;
            }
            othertwo[index++] = {vec2.x, vec2.y};
            if (index == 2) {
                break;
            }
        }

        if (othertwo[0].x > othertwo[1].x) {
            this->a = {othertwo[1].x, othertwo[1].y};
            this->c = {othertwo[0].x, othertwo[0].y};
        } else {
            this->a = {othertwo[0].x, othertwo[0].y};
            this->c = {othertwo[1].x, othertwo[1].y};
        }
        std::cout << "a at " << this->a.x << "-" << this->a.y;
        std::cout << "b at " << this->b.x << "-" << this->b.y;
        std::cout << "c at " << this->c.x << "-" << this->c.y;
        std::cout << "d at " << this->d.x << "-" << this->d.y;

    } else {
        this->a = {a.x, a.y};
        this->b = {b.x, b.y};
        this->c = {c.x, c.y};
        this->d = {d.x, d.y};
    }
    this->alpha = new Angle(Vector2Angle(this->a, this->b));
    this->beta = new Angle(Vector2Angle(this->b, this->c));
    this->gamma = new Angle(Vector2Angle(this->c, this->d));
    this->delta = new Angle(Vector2Angle(this->d, this->a));

    this->tri_abd = new Triangle(this->a, this->b, this->d);
    this->tri_bcd = new Triangle(this->b, this->c, this->d);
    this->CalculateIsRect();
    this->CalculateSides();
    this->is_square = this->is_square && this->AreAllSidesEqual();
    this->CalculateIsTilted();
}

Quad::~Quad()
{
    delete this->alpha;
    delete this->beta;
    delete this->gamma;
    delete this->delta;
    delete this->tri_abd;
    delete this->tri_bcd;
}

void Quad::CalculateIsRect()
{
    this->is_rect = false;
    std::array<Angle*, 4> angles = {this->alpha, this->beta, this->gamma, this->delta};

    this->is_rect = true;
    for (auto angle : angles) {
        if (!angle->is90()) {
            this->is_rect = false;
        }
    }

    std::cout << (this->is_rect ? "it is rect" : "it is not rect") << std::endl;
}

void Quad::CalculateSides()
{
    this->sideab = Vector2Distance(this->a, this->b);
    this->sidebc = Vector2Distance(this->b, this->c);
    this->sidecd = Vector2Distance(this->c, this->d);
    this->sideda = Vector2Distance(this->d, this->a);
}

void Quad::CalculateIsTilted()
{
    this->is_tilted = !(
        Vector2Angle({1, 0}, Vector2Subtract(this->b, this->a)) == 0 ||
        Vector2Angle({1, 0}, Vector2Subtract(this->c, this->b)) == 0 ||
        Vector2Angle({1, 0}, Vector2Subtract(this->d, this->c)) == 0 ||
        Vector2Angle({1, 0}, Vector2Subtract(this->d, this->a)) == 0);

    std::cout << (this->is_tilted ? "it is tilted" : "it is not tilted") << std::endl;
}

void Quad::Draw()
{
    DrawLine(this->a.x, this->a.y, this->b.x, this->b.y, BLACK);
    DrawLine(this->b.x, this->b.y, this->c.x, this->c.y, BLACK);
    DrawLine(this->c.x, this->c.y, this->d.x, this->d.y, BLACK);
    DrawLine(this->d.x, this->d.y, this->a.x, this->a.y, BLACK);
}

bool Quad::IsVector2In(Vector2 x)
{
    if (this->is_rect)
    {
        return this->IsVecInRect(x);
    }

    return this->IsVecInDefault(x);
}

bool Quad::IsVecInRect(Vector2 p)
{
    Vector2 ab = Vector2Subtract(this->b, this->a);
    Vector2 am = Vector2Subtract(p, this->a);
    Vector2 bc = Vector2Subtract(this->c, this->b);
    Vector2 bm = Vector2Subtract(p, this->b);
    float dotABAM = Vector2DotProduct(ab, am);
    float dotABAB = Vector2DotProduct(ab, ab);
    float dotBCBM = Vector2DotProduct(bc, bm);
    float dotBCBC = Vector2DotProduct(bc, bc);

    return 0 <= dotABAM and dotABAM <= dotABAB and 0 <= dotBCBM and dotBCBM <= dotBCBC;
}

bool Quad::IsVecInDefault(Vector2 p)
{
    return this->tri_abd->IsVecIn(p) || this->tri_bcd->IsVecIn(p);
}

std::vector<Vector2> Quad::GetPoints()
{
    return std::vector<Vector2>{this->a, this->b, this->c, this->d};
}

void Quad::CalculateCenter(Vector2 p1, Vector2 p2)
{
    this->center = Vector2{
        (p1.x + p2.x) / 2,
        (p1.y + p2.y) / 2};
    std::cout << "found center at " << this->center.x << " - " << this->center.y << std::endl;
}

bool Quad::AreAllSidesEqual()
{
    float d = this->sideab;
    for (auto one : {this->sidebc, this->sidecd, this->sideda}) {
        if (d != one) {
            return false;
        }
    }
    return true;
}
