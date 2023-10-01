#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "menu.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"

enum class GameState {
    Menu, Game, LeaderBoard, Exit
};

class Game {
public:
    int widthWindow = 800;
    int heightWindow = 800;
    int frameRate = 60;
    float bulletFire = 0.01f;

    Game();
    void run();
private:
    void HandleEvents();
    void update();
    void render();
    void inputPlayerName();
    //void loadLeaderBoard();
    void spawnEnemies();

    int playerHP;
    int score;
    int currentWave;
    int enemiesNumb;
    int enemiesPlus;
    int startWave;
    float spawnPosition_X;
    float spawnPosition_Y;
    float waveDelay;
    bool gameStart;
    bool autoShoot;

    sf::RenderWindow window;
    sf::Texture menuTexture;
    sf::Texture inputTexture;
    sf::Texture inGameTexture;
    sf::Texture playerTexture;
    sf::Texture bulletTexture;
    sf::Texture enemyTexture;

    sf::Clock clock;
    float deltaTime;

    Menu menu;
    GameState currentState;

    sf::Font font;

    std::string playerName;

    //char temp[255];
    //int scoreFile[6];
    //std::string nameFile[6];
    //std::vector <std::pair<int, std::string>> userScore;

    sf::Text leaderBoard;
    //sf::Text top1;
    //sf::Text score1;
    //sf::Text top2;
    //sf::Text score2;
    //sf::Text top31;
    //sf::Text score3;
    //sf::Text top4;
    //sf::Text score4;
    //sf::Text top5;
    //sf::Text score5;

    sf::Text nameText;
    sf::Text scoreText;
    sf::Text HPText;

    Player player;
    std::vector<Bullet> bullets;
    std::vector<Enemy> enemies;
    sf::Vector2f spawnPosition;

    sf::Sprite menuBackground;
    sf::Sprite inputBackground;
    sf::Sprite mapInGame;
    sf::Clock bulletFireClock;
    sf::Clock waveClock;
};