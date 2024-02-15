#include "GameInstance.h"

#include <iostream>

//#include <sstream> // Pour la construction manuelle de JSON

GameInstance::GameInstance(int iLengthScreen, int iHeightScreen)
{
    x = iLengthScreen;
    y = iHeightScreen;
    playerTurn = 0;

    // Initialisation du tableau
    board = std::vector<std::vector<int>>(3, std::vector<int>(3, -1));
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

bool GameInstance::checkWin(int player)
{
	// Vérifie les lignes et colonnes
	for (int i = 0; i < 3; i++) {
		if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
			return true; // Ligne gagnante
		if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
			return true; // Colonne gagnante
	}
	// Vérifie les diagonales
	if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
		return true; // Diagonale 1 gagnante
	if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
		return true; // Diagonale 2 gagnante
	return false;
}


//---------------------------GETS--------------------------


int GameInstance::getPlayerTurn()
{
    return playerTurn;
}

std::vector<std::vector<int>>& GameInstance::getBoard()
{
    return board;
}


//rendre l'état du jeu accessible via une requête HTTP
//std::string GameInstance::getGameStateAsJson() {
//    std::stringstream ss;
//    ss << "{ \"playerTurn\": " << playerTurn << ", \"board\": [";
//    for (size_t i = 0; i < board.size(); ++i) {
//        ss << "[";
//        for (size_t j = 0; j < board[i].size(); ++j) {
//            ss << board[i][j];
//            if (j < board[i].size() - 1) ss << ", ";
//        }
//        ss << "]";
//        if (i < board.size() - 1) ss << ", ";
//    }
//    ss << "] }";
//    return ss.str();
//}
