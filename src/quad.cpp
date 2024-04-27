#include "quad.hpp"
#include <raymath.h>
#include <iostream>


Quad::Quad()
{
    a = {0, 0};
    b = {0, 0};
    c = {0, 0};
    d = {0, 0};
    this->IsReady = false;
    this->center = {0, 0};
    this->tri_abd = new Triangle();
    this->tri_bcd = new Triangle();
    this->color = BLACK;
    this->is_tilted = false;
    this->is_rect = false;
    this->is_square = false;
    this->sideab = 0.0;
    this->sidebc = 0.0;
    this->sidecd = 0.0;
    this->sideda = 0.0;
    this->diaginal_len = 0.0;
}

Quad::~Quad() {
    delete this->tri_abd;
    delete this->tri_bcd;
}

void Quad::SetDimensions(Vector2 a, Vector2 b, Vector2 c, Vector2 d) {
    this->a = {a.x, a.y};
    this->b = {b.x, b.y};
    this->c = {c.x, c.y};
    this->d = {d.x, d.y};

    this->tri_abd->Init(this->a, this->b, this->d);
    this->tri_bcd->Init(this->b, this->c, this->d);
    this->CalculateIsRectIsSquare();
    this->CalculateSides();
    this->CalculateIsTilted();
}

void Quad::CalculateIsRectIsSquare()
{
    this->is_rect = false;
    if (this->tri_abd->alpha.is90())
    {
        this->diaginal_len = this->tri_abd->sidea;
        this->is_rect = true;
        this->is_square = this->tri_abd->beta.is45() and this->tri_abd->gamma.is45();
    }
    else if (this->tri_abd->beta.is90())
    {
        this->diaginal_len = this->tri_abd->sideb;
        this->is_rect = true;
        this->is_square = this->tri_abd->alpha.is45() and this->tri_abd->gamma.is45();
    }
    else if (this->tri_abd->gamma.is90())
    {
        this->diaginal_len = this->tri_abd->sidec;
        this->is_rect = true;
        this->is_square = this->tri_abd->alpha.is45() and this->tri_abd->beta.is45();
    }
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
        Vector2Angle({0, 1}, Vector2Subtract(this->b, this->a)) == 0 ||
        Vector2Angle({0, 1}, Vector2Subtract(this->c, this->b)) == 0 ||
        Vector2Angle({0, 1}, Vector2Subtract(this->d, this->c)) == 0 ||
        Vector2Angle({0, 1}, Vector2Subtract(this->d, this->a)) == 0);

    if (this->is_tilted) {
        std::cout << "it is tilted" << std::endl;
    } else {
        std::cout << "it is not tilted" << std::endl;
    }
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
    if (this->is_rect) {
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
