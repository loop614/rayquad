#include "triangle.hpp"
#include <raymath.h>
#include <math.h>
#include <iostream>

Triangle::Triangle(Vector2 a, Vector2 b, Vector2 c)
{
    this->a = {a.x, a.y};
    this->b = {b.x, b.y};
    this->c = {c.x, c.y};
    this->CalculateSides();
    this->CalculateAngles();
}

Triangle::~Triangle() {
    delete this->alpha;
    delete this->beta;
    delete this->gamma;
}

void Triangle::CalculateSides()
{
    this->sidea = Vector2Distance(this->b, this->c);
    this->sideb = Vector2Distance(this->a, this->c);
    this->sidec = Vector2Distance(this->a, this->b);

    std::cout << "sidea " << this->sidea << std::endl;
    std::cout << "sideb " << this->sideb << std::endl;
    std::cout << "sidec " << this->sidec << std::endl;
}

void Triangle::CalculateAngles()
{
    float p180i = 180.0 / M_PI;
    this->alpha = new Angle(p180i * acos(
        (this->sideb * this->sideb + this->sidec * this->sidec - this->sidea * this->sidea) / (2 * this->sideb * this->sidec)));
    this->gamma = new Angle(p180i * acos(
        (this->sidea * this->sidea + this->sideb * this->sideb - this->sidec * this->sidec) / (2 * this->sidea * this->sideb)));
    this->beta = new Angle(180.0 - this->alpha->val - this->gamma->val);

    std::cout << "alpha " << this->alpha->val << std::endl;
    std::cout << "beta " << this->beta->val << std::endl;
    std::cout << "gamma " << this->gamma->val << std::endl;
}

bool Triangle::IsVecIn(Vector2 p)
{
    float A = 0.5 * (-this->b.y * this->c.x + this->a.y * (-this->b.x + this->c.x) + this->a.x * (this->b.y - this->c.y) + this->b.x * this->c.y);
    float sign = A < 0 ? -1 : 1;
    float s = sign * (this->a.y * this->c.x - this->a.x * this->c.y + (this->c.y - this->a.y) * p.x + (this->a.x - this->c.x) * p.y);
    float t = sign * (this->a.x * this->b.y - this->a.y * this->b.x + (this->a.y - this->b.y) * p.x + (this->b.x - this->a.x) * p.y);

    return s > 0 && t > 0 && (s + t) < 2 * A * sign;
}
