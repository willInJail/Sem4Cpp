#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Board
{
private:
    static const int SIZE = 8;
    static const int CELL_SIZE = 64;

    std::vector<std::vector<int>> cells;

    sf::Vector2i selected;
    bool hasSelection = false;

public:
    Board();

    void Draw(sf::RenderWindow& window);

    void HandleClick(int mouseX, int mouseY);

private:
    void GenerateBoard();

    bool IsAdjacent(sf::Vector2i a, sf::Vector2i b);

    void Swap(sf::Vector2i a, sf::Vector2i b);

    bool FindMatches(std::vector<std::vector<bool>>& marked);

    void RemoveMatches(const std::vector<std::vector<bool>>& marked);

    void DropCells();

    sf::Color GetColor(int id);

    void TriggerBonus(int x, int y, int color);

    void TriggerBomb();
};