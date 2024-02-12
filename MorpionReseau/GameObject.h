#pragma once

#include <SFML/Graphics.hpp>

#include "GameInstance.h"

class GameObject
{

public:
	GameObject(sf::Vector2i mousePosition, GameInstance oGame);

	void play(sf::Vector2i mousePosition, GameInstance oGame);

	sf::Shape* pShape;

	int verif;

private:
	void createObject(int iTurn, GameInstance oGame);

	sf::Vector2f position;

};