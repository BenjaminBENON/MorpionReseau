#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class GameInstance
{
public:

    GameInstance(int iLengthScreen, int iHeightScreen);

    int x;
    int y;

    void switchPlayer();
    int getPlayerTurn();
    bool checkWin(int player);

    std::vector<std::vector<int>>& getBoard(); // Déclaration de la fonction getBoard

    void drawWindow(sf::RenderWindow& window);

private:

    int playerTurn;
    std::vector<std::vector<int>> board;
};