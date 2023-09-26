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
    Menu, Game, Exit
};

class Game {
public:
    int widthWindow = 800;
    int heightWindow = 800;
    int frameRate = 60;
    float bulletFire = 0.1f;

    Game();
    void run();
private:
    void HandleEvents();
    void update();
    void render();
    void spawnEnemies();

    int currentWave;
    int enemiesNumb;
    int enemiesPlus;
    int startWave;
    float spawnPosition_X;
    float spawnPosition_Y;
    float waveDelay;
    bool autoShoot;

    sf::RenderWindow window;
    sf::Texture menuTexture;
    sf::Texture inGameTexture;
    sf::Texture playerTexture;
    sf::Texture bulletTexture;
    sf::Texture enemyTexture;

    sf::Clock clock;
    float deltaTime;

    Menu menu;
    GameState currentState;
    sf::Sprite background;
    sf::Sprite mapInGame;

    Player player;
    std::vector<Bullet> bullets;
    std::vector<Enemy> enemies;

    sf::Vector2f spawnPosition;
    sf::Clock bulletFireClock;
    sf::Clock waveClock;
};