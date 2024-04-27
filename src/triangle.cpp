#include "triangle.hpp"
#include <raymath.h>
#include <math.h>
#include <iostream>

Triangle::Triangle()
{
}

void Triangle::Init()
{
    this->CalculateSides();
    this->CalculateAngles();
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
    this->alpha.val = (180.0 / M_PI) * acos(
        (this->sideb * this->sideb + this->sidec * this->sidec - this->sidea * this->sidea) / (2 * this->sideb * this->sidec)
    );
    this->gamma.val = (180.0 / M_PI) * acos(
        (this->sidea * this->sidea + this->sideb * this->sideb - this->sidec * this->sidec) / (2 * this->sidea * this->sideb)
    );
    this->beta.val = 180.0 - this->alpha.val - this->gamma.val;

    std::cout << "alpha " << this->alpha.val << std::endl;
    std::cout << "beta " << this->beta.val << std::endl;
    std::cout << "gamma " << this->gamma.val << std::endl;
}
