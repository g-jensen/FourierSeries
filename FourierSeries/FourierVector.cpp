#include "FourierVector.h"

FourierVector::FourierVector(float x, float y)
{
    this->x = x;
    this->y = y;
    this->fillColor = sf::Color::White;
    this->rotations = 1;
    this->origin = sf::Vector2f(0, 0);
    this->angle_deg = 0;

    this->length = sqrt(
        (x * x) + (y * y)
    );
}

FourierVector::FourierVector(sf::Vector2f origin, sf::Vector2f end)
{
    this->x = end.x;
    this->y = end.y;
    this->fillColor = sf::Color::White;
    this->rotations = 1;
    this->origin = origin;
    this->angle_deg = 0;

    float xDiff = origin.x - end.x;
    float yDiff = origin.y - end.y;
    this->length = sqrt(
        (xDiff * xDiff) + (yDiff * yDiff)
    );
    
}



void FourierVector::draw(sf::RenderWindow& window)
{
    sf::Vertex line[2];
    line[0].position = this->origin;
    line[0].color = fillColor;
    line[1].position = sf::Vector2f(this->x,this->y);
    line[1].color = fillColor;
    window.draw(line,2,sf::Lines);
}

FourierVector FourierVector::add(FourierVector vector)
{
    return FourierVector(sf::Vector2f(this->x,this->y),*this + vector);
}

void FourierVector::rotate(float angle_deg)
{
    //std::cout << this->length << std::endl;
    this->angle_deg += angle_deg;
    this->x = (cosf(this->angle_deg * 180. / M_PI) * this->length) + this->origin.x;
    this->y = (sinf(this->angle_deg * 180. / M_PI) * this->length) + this->origin.y;
}

FourierVector FourierVector::operator+(const FourierVector& v)
{
    return FourierVector(this->x + v.x,this->y + v.y);
}

FourierVector FourierVector::operator-(const FourierVector& v)
{
    return FourierVector(this->x - v.x, this->y - v.y);
}

FourierVector FourierVector::operator*(const float& scalar)
{
    return FourierVector(this->x * scalar, this->y * scalar);
}

std::ostream& operator<<(std::ostream& os, const FourierVector& v)
{
    std::cout << v.x << ", " << v.y;
    return os;
}
