//
// Created by Mitchell Steenbergen on 11/16/2024.
//

#include "Screens.h"

using namespace sf;

/**
 * Displays the start screen with game title, start prompt, and controls
 * @param window
 * @param font
 * @param highScores
 */
void Screens::startScreen(sf::RenderWindow &window, sf::Font &font, const std::array<int, 4>& highScores) {
    // Clear the window
    window.clear(Color(10, 10, 18));
    window.setView(window.getDefaultView());

    const auto size = window.getSize();
    const auto W = static_cast<float>(size.x);
    const auto H = static_cast<float>(size.y);

    // Main Panel, Nice little box
    RectangleShape panel({W * 0.6f, H * 0.7f});
    panel.setFillColor(Color(15, 15, 28));
    panel.setOutlineThickness(2.f);
    panel.setOutlineColor(Color(90, 90, 160));
    panel.setPosition(W * 0.2f, H * 0.15f);

    // Set up the title text for the start screen
    Text title;
    title.setFont(font);
    title.setString("TETRIS");
    title.setCharacterSize(80);
    title.setFillColor(Color(255, 230, 120));
    title.setStyle(Text::Bold);

    // Center the title text horizontally and position it at the top
    FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.left + titleBounds.width / 2.f, titleBounds.top + titleBounds.height / 2.f);
    title.setPosition(W * 0.5f, H * 0.22f);


    // Set up the start prompt text
    Text start;
    start.setFont(font);
    start.setString("Press 'P' to start");
    start.setCharacterSize(45);
    start.setFillColor(Color(200, 200, 220));

    // Center the start prompt text below the title
    FloatRect startBound = start.getLocalBounds();
    start.setOrigin(startBound.left + startBound.width / 2.f, startBound.top + startBound.height / 2.f);
    start.setPosition(W * 0.5f, H * 0.32f);

    // Set up the control instructions text
    Text control;
    control.setFont(font);
    control.setCharacterSize(25);
    control.setFillColor(Color(210, 210, 210));
    // arrow keys
    sf::String arrows = sf::String(L"\u2190 \u2191 \u2192");
    // Some absolute mumbo jumbo to get this to line up
    control.setString(
            L"Controls:\n"
            L" " + arrows + L"          : Move / Rotate\n"
                            L" \u2193              : Soft drop\n"
                            L" P              : Pause / Resume\n"
                            L" C              : Hold / Swap\n"
                            L" R              : Restart\n"
                            L" Esc            : Quit"
    );

    // Center the control instructions text below the start prompt
    FloatRect controlBound = control.getLocalBounds();
    control.setOrigin(controlBound.left + controlBound.width / 2.f, controlBound.top + controlBound.height / 2.f);
    control.setPosition(W * 0.5f, H * 0.46f);

    // Setting up the HighScore Board in the Start Menu
    std::string highScoreLines = "High Scores:\n";
    for(size_t i = 0; i < highScores.size(); i++){
        highScoreLines += std::to_string(i + 1) + ". " + std::to_string(highScores[i]) + "\n";
    }

    // Set up the high score text
    Text highScoreText;
    highScoreText.setFont(font);
    highScoreText.setString(highScoreLines);
    highScoreText.setCharacterSize(28);
    highScoreText.setFillColor(Color(200, 200, 220));

    // Center the high score board
    FloatRect highScoreBounds = highScoreText.getLocalBounds();
    highScoreText.setOrigin(highScoreBounds.left + highScoreBounds.width / 2.f, highScoreBounds.top + highScoreBounds.height / 2.f);
    highScoreText.setPosition(W * 0.5f, H * 0.68f);

    // Set the view to the default view for proper alignment
    window.setView(window.getDefaultView());

    // Draw the start screen elements
    window.draw(panel);
    window.draw(title);
    window.draw(start);
    window.draw(control);
    window.draw(highScoreText);
    window.display();


}

/**
 * Displays the pause screen with instructions to resume or exit
 * @param window
 * @param font
 */
void Screens::pauseScreen(sf::RenderWindow &window, sf::Font &font) {
    window.clear(Color(10, 10, 18));
    window.setView(window.getDefaultView());
    const auto size = window.getSize();
    const auto W = static_cast<float>(size.x);
    const auto H = static_cast<float>(size.y);

    // Center Card
    RectangleShape panel({W * 0.5f, H * 0.35f});
    panel.setFillColor(Color(15, 15 , 30));
    panel.setOutlineColor(Color(90, 90, 160));
    panel.setOutlineThickness(2.f);
    panel.setPosition(W * 0.25f, H * 0.325f);

    // Set up the pause text
    Text pauseText;
    pauseText.setFont(font);
    pauseText.setString("Game Paused\n\n"
                        "P   - Resume\n"
                        "R   - Restart\n"
                        "Esc - Exit");
    pauseText.setCharacterSize(45);
    pauseText.setFillColor(Color(230, 230, 230));

    // Set position to center of the smaller window
    FloatRect pauseBounds = pauseText.getLocalBounds();
    pauseText.setOrigin(pauseBounds.left + pauseBounds.width / 2.f, pauseBounds.top + pauseBounds.height / 2.f);
    pauseText.setPosition(W * 0.5f, H * 0.5f);

    // Draw the pause screen elements
    window.draw(panel);
    window.draw(pauseText);
    window.display();
}

/**
 * Displays the game over scren with options to restart, return to the menu, or exit.
 * @param window
 * @param font
 * @param highScores
 */
void Screens::gamerOverScreen(sf::RenderWindow &window, sf::Font &font, const std::array<int, 4>& highScores) {
    window.clear(Color(10, 10, 18));
    window.setView(window.getDefaultView());

    const auto size = window.getSize();
    const auto W = static_cast<float>(size.x);
    const auto H = static_cast<float>(size.y);

    // Center Card
    RectangleShape panel({W * 0.6f, H * 0.65f});
    panel.setFillColor(Color(15, 15 , 28));
    panel.setOutlineColor(Color(120, 70, 120));
    panel.setOutlineThickness(2.f);
    panel.setPosition(W * 0.2f, H * 0.18f);

    Text title;
    title.setFont(font);
    title.setString("GAME OVER");
    title.setCharacterSize(80);
    title.setFillColor(Color(255, 210, 120));
    title.setStyle(Text::Bold);

    // Center the title text horizontally and position it at the top
    FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.left + titleBounds.width / 2.f, titleBounds.top + titleBounds.height / 2.f);
    title.setPosition(W * 0.5f, H * 0.26f);

    // Set up the game over text
    Text gameOver;
    gameOver.setFont(font);
    gameOver.setString("R   - Restart\n"
                       "M   - Main Menu\n"
                       "Esc - Exit");
    gameOver.setCharacterSize(45);
    gameOver.setFillColor(Color(200, 200, 220));
    // Set position to center the game over text in the window
    FloatRect gameBounds = gameOver.getLocalBounds();
    gameOver.setOrigin(gameBounds.left + gameBounds.width / 2.f, gameBounds.top + gameBounds.height / 2.f);
    gameOver.setPosition(W * 0.5f, H * 0.40f);

    // Setting up the HighScore Board in the Start Menu
    std::string highScoreLines = "High Scores:\n";
    for(size_t i = 0; i < highScores.size(); i++){
        highScoreLines += std::to_string(i + 1) + ". " + std::to_string(highScores[i]) + "\n";
    }

    Text highScoreText;
    highScoreText.setFont(font);
    highScoreText.setString(highScoreLines);
    highScoreText.setCharacterSize(42);
    highScoreText.setFillColor(Color(200, 200, 220));

    FloatRect highScoreBounds = highScoreText.getLocalBounds();
    highScoreText.setOrigin(highScoreBounds.left + highScoreBounds.width / 2.f, highScoreBounds.top + highScoreBounds.height / 2.f);
    highScoreText.setPosition(W * 0.5f, H * 0.62f);

    // Draw the game over screen elements
    window.draw(panel);
    window.draw(title);
    window.draw(gameOver);
    window.draw(highScoreText);
    window.display();
}

