#include <SFML/Graphics.hpp>
#include <mysqlx/xdevapi.h>
#include <iostream>
#include <vector>
#include "Button.h"
using namespace sf;
RenderWindow window(VideoMode(600, 600), L"DZ8", Style::Default);
sf::Font font;
std::vector<Button> buttons;
mysqlx::RowResult result1;
mysqlx::RowResult result2;
std::vector < mysqlx::Row> result1_c;
std::vector < mysqlx::Row> result2_c;
float left = 0.0f;
float right = 0.0f;
void init(std::string select, std::string table_, std::string orderby, mysqlx::RowResult& result, std::vector < mysqlx::Row>& result_c, int x, int y) {
	try {
		mysqlx::SessionSettings sesssett("localhost", 33060, "user", "passwd", "DZ9");
		mysqlx::Session session(sesssett);
		mysqlx::Schema schema = session.getDefaultSchema();
		mysqlx::Table table = schema.getTable(table_);
		result = session.sql("SELECT " + select + " FROM " + table_ + " ORDER BY " + orderby).execute();
		int j = 1;
		for (auto row : result.fetchAll()) {
			result_c.push_back(row);
			Button button(Vector2f(x+130, y + j * 20), Vector2f(20, 20), j, table_);
			buttons.push_back(button);
			button.draw(window);
			j++;
		}
		session.close();
}
catch (const mysqlx::Error& e) {
	std::cout << "Ошибка: " << e.what() << std::endl;
}
}
void drawDataTable(int x, int y, mysqlx::RowResult &result, std::vector < mysqlx::Row>& result_c) {
		for (int i = 0; i < result.getColumnCount(); i++) {
			auto& col = result.getColumn(i);
			std::string lab = col.getColumnLabel();
			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f(x + i * 150, y),sf::Color(255, 0, 0)),
				sf::Vertex(sf::Vector2f(x + i * 150, y + 20.f),sf::Color(255, 0, 0)),
				sf::Vertex(sf::Vector2f(x + i * 150, y),sf::Color(255, 0, 0)),
				sf::Vertex(sf::Vector2f(x + i * 150 + 150, y),sf::Color(255, 0, 0))
			};
			window.draw(line, 4, sf::Lines);
			sf::Text text;

			text.setFont(font);
			text.setString(lab);
			text.setCharacterSize(15);
			text.setFillColor(sf::Color(0, 0, 0));
			text.setStyle(Text::Bold);
			text.setPosition(x + i * 150 + 5, y);
			window.draw(text);
			

		}
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(x + result.getColumnCount() * 150, y),sf::Color(255, 0, 0)),
			sf::Vertex(sf::Vector2f(x + result.getColumnCount() * 150, y + 20.f),sf::Color(255, 0, 0))
		};
		window.draw(line, 4, sf::Lines);
		int j = 1;
		for (mysqlx::Row row : result_c) {

			for (int i = 0; i < row.colCount(); i++) {
				std::stringstream ss;
				ss << row[i];
				std::string lab = ss.str();
				sf::Vertex line[] =
				{
					sf::Vertex(sf::Vector2f(x + i * 150, y + j * 20),sf::Color(0, 0, 0)),
					sf::Vertex(sf::Vector2f(x + i * 150, y + 20.f + j * 20),sf::Color(0, 0, 0)),
					sf::Vertex(sf::Vector2f(x + i * 150, y + j * 20),sf::Color(0, 0, 0)),
					sf::Vertex(sf::Vector2f(x + i * 150 + 150, y + j * 20),sf::Color(0, 0, 0))
				};
				window.draw(line, 4, sf::Lines);
				sf::Text text;
				sf::Font font;
				if (font.loadFromFile("Arial.ttf"))
				{
					text.setFont(font);
					text.setString(lab);
					text.setCharacterSize(15);
					text.setFillColor(sf::Color(0, 0, 0));
					text.setPosition(x + i * 150 + 5, y + j * 20);
					window.draw(text);
				}
					
			}
			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f(x + result.getColumnCount() * 150, y + j * 20),sf::Color(0, 0, 0)),
				sf::Vertex(sf::Vector2f(x + result.getColumnCount() * 150, y + 20.f + j * 20),sf::Color(0, 0, 0))
			};
			window.draw(line, 4, sf::Lines);
			j++;
		}
		sf::Vertex lineEnd[] =
		{
			sf::Vertex(sf::Vector2f(x, y + j * 20),sf::Color(0, 0, 0)),
			sf::Vertex(sf::Vector2f(x + result.getColumnCount() * 150, y + j * 20),sf::Color(0, 0, 0))
		};
		window.draw(lineEnd, 4, sf::Lines);
	
}
float getCost(std::string table_, std::string id, std::string cost_col, std::string id_col) {
	try {
		mysqlx::SessionSettings sesssett("localhost", 33060, "user", "passwd", "DZ9");
		mysqlx::Session session(sesssett);
		mysqlx::Schema schema = session.getDefaultSchema();
		mysqlx::Table table = schema.getTable(table_);
		std::stringstream ss;
		ss << "SELECT " << cost_col << " FROM " << table_ << " WHERE " << id_col << "=" << id;
		std::stringstream ss2;
		ss2 << session.sql(ss.str().c_str()).execute().fetchOne()[0];
		return std::stof(ss2.str());
		session.close();
	}
	catch (const mysqlx::Error& e) {
		std::cout << "Ошибка: " << e.what() << std::endl;
	}
}
std::string getFloat(float value, int factor)
{
	int integerValue = std::round(value / factor) * factor; //(5689 / 100) * 100 = 5600
	int decimal = value - integerValue;  // 5689 - 5600;
	return std::to_string((int)(value / factor)) + "." + std::to_string(decimal);
	// result = "56" + "." + "89" 
	// lastly, print result
}
void drawResult(std::string result) {
	sf::Text text;
	sf::Font font;
	if (font.loadFromFile("Arial.ttf"))
	{
		text.setFont(font);
		text.setString(result);
		text.setCharacterSize(25);
		text.setFillColor(sf::Color(0, 0, 0));
		text.setPosition(470, 65);
		RectangleShape back(Vector2f(100, 30));
		back.setPosition(465, 65);
		window.draw(back);
		window.draw(text);
	}
}
int main()
{
	window.clear(Color(200, 200, 200));
	init("core_name", "core", "core_cost", result1,result1_c, 10, 50);
	init("wood_name", "wood", "wood_cost", result2,result2_c, 240, 50);
	//setlocale(LC_ALL, "Russian");
	font.loadFromFile("Arial.ttf");
	drawDataTable(10, 50, result1, result1_c);
	drawDataTable(240, 50, result2, result2_c);
	RectangleShape plus_1(Vector2f(50, 10));
	RectangleShape plus_2(Vector2f(10, 50));
	plus_1.setFillColor(Color(0, 0, 0));
	plus_2.setFillColor(Color(0, 0, 0));
	plus_1.setPosition(175, 75);
	plus_2.setPosition(195, 55);
	window.draw(plus_1);
	window.draw(plus_2);
	RectangleShape equal_1(Vector2f(50, 10));
	RectangleShape equal_2(Vector2f(50, 10));
	equal_1.setFillColor(Color(0, 0, 0));
	equal_2.setFillColor(Color(0, 0, 0));
	equal_1.setPosition(400, 65);
	equal_2.setPosition(400, 85);
	window.draw(equal_1);
	window.draw(equal_2);
	drawResult("0");
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
			}
			else if (event.type == Event::MouseMoved) {
				for (Button &button : buttons) {
					if (button.AABB(Mouse::getPosition(window))) {
						button.shape.setFillColor(Color(255, 0, 0));
						button.draw(window);
					} else {
						button.shape.setFillColor(Color(0, 0, 0));
						button.draw(window);
					}
				}
			}
			else if (event.type == Event::MouseButtonPressed) {
				Button* focused=nullptr;
				for (Button &button : buttons) {
					if (button.AABB(Mouse::getPosition(window))) {
						button.focus = true;
						if (button.table._Equal("core")) {
							left = getCost(button.table, std::to_string(button.data), "core_cost", "core_id");
						}else if (button.table._Equal("wood")) {
							right = getCost(button.table, std::to_string(button.data), "wood_cost", "wood_id");
						}
						drawResult((getFloat((left + right)*100,100)));
						button.draw(window);
						focused = &button;
						break;
					}
				}
				if (focused != nullptr) {
					for (Button& button : buttons) {
						if (!button.AABB(Mouse::getPosition(window))) {
							if (focused->table._Equal(button.table)) {
								button.focus = false;
								button.draw(window);
							}

						}
					}
				}
			}
		}
		//window.clear(Color(200, 200, 200));
		/*
		*/
		window.display();
	}
	return 0;
}