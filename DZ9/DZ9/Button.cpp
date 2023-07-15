#include "Button.h"

Button::Button(sf::Vector2f pos, sf::Vector2f size, uint64_t data, std::string table)
{
	this->shape = sf::RectangleShape(size);
	this->shape.setPosition(pos);
	this->shape.setFillColor(sf::Color(0, 0, 0));
	this->shape.setOutlineColor(sf::Color(255, 255, 255));
	this->data = data;
	this->table = table;
}

void Button::draw(sf::RenderWindow& window)
{
	if (focus) {
		shape.setOutlineThickness(1);
		shape.setSize(sf::Vector2f(18, 18));
		shape.setOrigin(sf::Vector2f(-1, -1));
	}
	else {
		shape.setOutlineThickness(0);
		shape.setSize(sf::Vector2f(20, 20));
		shape.setOrigin(sf::Vector2f(0, 0));
	}
	window.draw(this->shape);
}

bool Button::AABB(sf::Vector2i loc) {
	return loc.x >= shape.getPosition().x && loc.x <= shape.getPosition().x + shape.getSize().x &&
		loc.y >= shape.getPosition().y && loc.y <= shape.getPosition().y + shape.getSize().y;
}

void Button::onclick() {

}
