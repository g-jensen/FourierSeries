#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

class FourierVector : public sf::Vector2<float>
{
public:
	FourierVector(float x, float y);
	FourierVector(sf::Vector2f origin, sf::Vector2f end);

	// rotation degree per frame
	int rotations;

	sf::Color fillColor;
	
	sf::Vector2f origin;

	float angle_deg;
	float length;

	void draw(sf::RenderWindow& window);
	FourierVector add(FourierVector vector);
	void rotate(float angle_deg);

	FourierVector operator+(const FourierVector& v);
	FourierVector operator-(const FourierVector& v);
	FourierVector operator*(const float& scalar);
	friend std::ostream& operator<<(std::ostream& os, const FourierVector& v);
private:
};

