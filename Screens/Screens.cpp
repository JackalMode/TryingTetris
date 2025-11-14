//
// Created by Mitchell Steenbergen on 11/16/2024.
//

#include "Screens.h"

using namespace sf;

/**
 * Displays the start screen with game title, start prompt, and controls
 * @param window
 * @param font
 */
void Screens::startScreen(sf::RenderWindow &window, sf::Font &font) {
    // Clear the window with a black background
    window.clear(Color::Black);

    // Set up the title text for the start screen
    Text title;
    title.setFont(font);
    title.setString("TETRIS");
    title.setCharacterSize(48);
    title.setFillColor(Color::Yellow);
    title.setStyle(Text::Bold);

    // Center the title text horizontally and position it at the top
    FloatRect titleBounds = title.getLocalBounds();
    title.setPosition((window.getSize().x - titleBounds.width) / 2, (window.getSize().y / 2) - 150);


    // Set up the start prompt text
    Text start;
    start.setFont(font);
    start.setString("Press 'P' to start");
    start.setCharacterSize(24);
    start.setFillColor(Color::Yellow);

    // Center the start prompt text below the title
    FloatRect startBound = start.getLocalBounds();
    start.setPosition((window.getSize().x - startBound.width) / 2, (window.getSize().y / 2) - 50);

    // Set up the control instructions text
    Text control;
    control.setFont(font);
    control.setString("Controls:\n- Arrow Keys: Move Tetromino\n- P: Pause/Resume");
    control.setCharacterSize(15);
    control.setFillColor(Color::Yellow);

    // Center the control instructions text below the start prompt
    FloatRect controlBound = control.getLocalBounds();
    control.setPosition((window.getSize().x - controlBound.width) / 2, (window.getSize().y / 2) + 10);

    // Set the view to the default view for proper alignment
    window.setView(window.getDefaultView());

    // Draw the start screen elements
    window.draw(title);
    window.draw(start);
    window.draw(control);
    window.display();
}

/**
 * Displays the pause screen with instructions to resume or exit
 * @param window
 * @param font
 */
void Screens::pauseScreen(sf::RenderWindow &window, sf::Font &font) {
    // Set up the pause text
    Text pauseText;
    pauseText.setFont(font);
    pauseText.setString("Game Paused\nPress 'P' to Resume\nPress 'R' to Restart\nPress 'Escape' to Exit");
    pauseText.setCharacterSize(20);
    pauseText.setFillColor(Color::Yellow);

    // Set position to center of the smaller window
    FloatRect pauseBounds = pauseText.getLocalBounds();
    pauseText.setPosition((window.getSize().x - pauseBounds.width) / 2, (window.getSize().y / 2) - 70);

    // Set the view to the default view for proper alignment
    window.setView(window.getDefaultView());
    // Draw the pause screen elements
    window.draw(pauseText);
    window.display();
}

/**
 * Displays the game over scren with options to restart, return to the menu, or exit
 * @param window
 * @param font
 */
void Screens::gamerOverScreen(sf::RenderWindow &window, sf::Font &font) {
    // Set up the game over text
    Text gameOver;
    gameOver.setFont(font);
    gameOver.setString("Game Over\nPress 'R' to Restart\nPress 'M' to go to Menu\n 'Esc' to Exit");
    gameOver.setCharacterSize(20);
    gameOver.setFillColor(Color::Yellow);
    // Set position to center the game over text in the window
    FloatRect gameBounds = gameOver.getLocalBounds();
    gameOver.setPosition((window.getSize().x - gameBounds.width) / 2, (window.getSize().y / 2) - 70);

    // Set the view to the default view for proper alignment
    window.setView(window.getDefaultView());
    // Draw the game over screen elements
    window.draw(gameOver);
    window.display();
}

