//
// Created by Mitchell Steenbergen on 11/16/2024.
//

#ifndef M4OEP_SCREENS_H
#define M4OEP_SCREENS_H

#include <SFML/Graphics.hpp>
#include <array>

class Screens {
public:
    // Displays the pause screen
    void pauseScreen(sf::RenderWindow& window, sf::Font& font);
    // Displays the start screen
    void startScreen(sf::RenderWindow& window, sf::Font& font, const std::array<int, 4>& highScores);
    // Displays the game over screen
    void gamerOverScreen(sf::RenderWindow& window, sf::Font& font, const std::array<int, 4>& highScores);
};


#endif //M4OEP_SCREENS_H
