#pragma once
#include <SFML/Graphics.hpp>
class Button
{
public:
	uint64_t data;
	std::string table;
	sf::RectangleShape shape;
	Button(sf::Vector2f pos, sf::Vector2f size, uint64_t data, std::string table);
	void draw(sf::RenderWindow& window);
	bool AABB(sf::Vector2i loc);
	void onclick();
	bool focus;
};

