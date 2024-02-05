#pragma once

#include <SFML/Graphics.hpp>

class GameInstance
{
public:
	GameInstance(int iLengthScreen, int iHeigthScreen);

	int x;
	int y;

	void switchPlayer();

	int getPlayerTurn();

private:
	int playerTurn; // égal à 0 ou 1 en fonction de qui joue

};