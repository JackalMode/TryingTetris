//
// Created by Mitchell Steenbergen on 11/16/2024.
//

#ifndef M4OEP_SCREENS_H
#define M4OEP_SCREENS_H

#include <SFML/Graphics.hpp>

class Screens {
public:
    // Displays the pause screen
    void pauseScreen(sf::RenderWindow& window, sf::Font& font);
    // Displays the start screen
    void startScreen(sf::RenderWindow& window, sf::Font& font);
    // Displays the game over screen
    void gamerOverScreen(sf::RenderWindow& window, sf::Font& font);
};


#endif //M4OEP_SCREENS_H
