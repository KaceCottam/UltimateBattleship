#pragma once

#include <SFML/Graphics.hpp>

class Tile : public sf::RectangleShape
{
public:
	Tile(const sf::Vector2f &size = sf::Vector2f(40, 40), const sf::Color &myColor = sf::Color::Magenta, const sf::Vector2f &pos = sf::Vector2f(250, 250)) : sf::RectangleShape(size)
	{
		this->setOutlineColor(myColor);
		this->setOutlineThickness(-2);
		this->setFillColor(sf::Color::Transparent);
		this->setPosition(pos);
	}

	bool getIsOccupied() const;
	void setIsOccupied(const bool &newStatus);

private:
	bool mIsOccupied;
};