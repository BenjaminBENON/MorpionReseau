#include "GameObject.h"

#include <algorithm>
#include <iostream>

GameObject::GameObject(sf::Vector2i mousePosition, GameInstance oGame)
{
	createObject(oGame.getPlayerTurn(), oGame);
	play(mousePosition, oGame);
	pShape->setPosition(position);
}



void GameObject::play(sf::Vector2i mousePosition, GameInstance oGame)
{
	if (mousePosition.x < oGame.x / 3)
	{
		if (mousePosition.y < oGame.y / 3)
		{
			position.x = oGame.x / 6;
			position.y = oGame.y / 6;
		}
		else if (mousePosition.y < (oGame.y * 2) / 3)
		{
			position.x = oGame.x / 6;
			position.y = oGame.y / 2;
		}
		else
		{
			position.x = oGame.x / 6;
			position.y = (oGame.y * 5) / 6;
		}
	}
	else if (mousePosition.x < (oGame.x * 2) / 3)
	{
		if (mousePosition.y < oGame.y / 3)
		{
			position.x = oGame.x / 2;
			position.y = oGame.y / 6;
		}
		else if (mousePosition.y < (oGame.y * 2) / 3)
		{
			position.x = oGame.x / 2;
			position.y = oGame.y / 2;
		}
		else
		{
			position.x = oGame.x / 2;
			position.y = (oGame.y * 5) / 6;
		}
	}
	else
	{
		if (mousePosition.y < oGame.y / 3)
		{
			position.x = (oGame.x * 5) / 6;
			position.y = oGame.y / 6;
		}
		else if (mousePosition.y < (oGame.y * 2) / 3)
		{
			position.x = (oGame.x * 5) / 6;
			position.y = oGame.y / 2;
		}
		else
		{
			position.x = (oGame.x * 5) / 6;
			position.y = (oGame.y * 5) / 6;
		}
	}
}





void GameObject::createObject(int iTurn, GameInstance oGame)
{
	int distance = std::min(oGame.x, oGame.y);
	int ecart = 5;

	switch (iTurn)
	{
	case 0:

		pShape = new sf::CircleShape(distance / 6 - ecart);
		pShape->setOrigin(distance / 6 - ecart, distance / 6 - ecart);
		break;

	case 1:

		pShape = new sf::RectangleShape(sf::Vector2f(oGame.x / 3 - ecart * 2, oGame.y / 3 - ecart * 2));
		pShape->setOrigin((oGame.x / 3 - ecart * 2) / 2, (oGame.y / 3 - ecart * 2) / 2);
		break;

	default:
		std::cout << "Erreur : aucun tour de joueur" << std::endl;
		break;
	}
}