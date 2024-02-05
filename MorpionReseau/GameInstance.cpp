#include "GameInstance.h"

#include <iostream>

GameInstance::GameInstance(int iLengthScreen, int iHeigthScreen)
{
	x = iLengthScreen;
	y = iHeigthScreen;
	playerTurn = 0;
}


void GameInstance::switchPlayer()
{
	switch (playerTurn)
	{
	case 0:
		playerTurn = 1;
		break;
	case 1:
		playerTurn = 0;
		break;
	default:
		std::cout << "Erreur : aucun tour de joueur" << std::endl;
		break;
	}
}


//---------------------------GETS--------------------------


int GameInstance::getPlayerTurn()
{
	return playerTurn;
}