#include "game.h"
#include <iostream>
#include <vector>

Game::Game()
    : window(sf::VideoMode(widthWindow, heightWindow), "SFML Game"),
    player(playerTexture, window.getSize().x, window.getSize().y),
    menu(widthWindow, heightWindow)
{
    sf::RenderWindow window(sf::VideoMode(widthWindow, heightWindow), "SFML GAME");
    window.setFramerateLimit(frameRate);

    currentWave = 0;
    enemiesNumb = 0;
    enemiesPlus = 0;
    startWave = 5;
    waveDelay = 5.0f;

    currentState = GameState::Menu;

    if (!menuTexture.loadFromFile("Textures/rayquaza.jpg")) {
        //handle error
    }
    background.setTexture(menuTexture);
    //background.setScale(1.5f, 1.5f);
    background.setOrigin(background.getGlobalBounds().width / 2,
        background.getGlobalBounds().height / 2);
    background.setScale(1.36f, 1.36f);
    background.setPosition(sf::Vector2f(widthWindow / 2, heightWindow / 2));

    if (!inGameTexture.loadFromFile("Textures/grass.jpg")) {
        //handle error
    }
    mapInGame.setTexture(inGameTexture);
    //background.setScale(1.5f, 1.5f);
    mapInGame.setOrigin(mapInGame.getGlobalBounds().width / 2,
        mapInGame.getGlobalBounds().height / 2);
    mapInGame.setScale(1.8f, 1.8f);
    mapInGame.setPosition(sf::Vector2f(widthWindow / 2, heightWindow / 2));

    if (!playerTexture.loadFromFile("Textures/Pokemon_Unit.png")) {
        //handle error
    }
    if (!bulletTexture.loadFromFile("Textures/Pokemon_Ball.png")) {
        //handle error
    }
    if (!enemyTexture.loadFromFile("Textures/Pokemon_Unit.png")) {
        //handle error
    }
}

void Game::HandleEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (currentState == GameState::Menu) {
            switch (event.type) {
            case sf::Event::KeyReleased:
                switch (event.key.code) {
                case sf::Keyboard::Up:
                    if (currentState == GameState::Menu) menu.MoveUp();
                    break;
                case sf::Keyboard::Down:
                    if (currentState == GameState::Menu) menu.MoveDown();
                    break;
                case sf::Keyboard::Return:
                    if (currentState == GameState::Menu) {
                        switch (menu.getPressItem()) {
                        case 0:
                            std::cout << "Play has been pressed" << std::endl;
                            currentState = GameState::Game;
                            break;
                        case 1:
                            std::cout << "LeaderBoard has been pressed" << std::endl;
                            break;
                        case 2:
                            std::cout << "Exit has been pressed" << std::endl;
                            currentState = GameState::Exit;
                            break;
                        }
                    }
                    break;
                case sf::Keyboard::T:
                    if (currentState == GameState::Game) {
                        currentState = GameState::Menu;
                    }
                    break;
                case sf::Keyboard::W:
                    if (currentState == GameState::Menu) menu.MoveUp();
                    break;
                case sf::Keyboard::S:
                    if (currentState == GameState::Menu) menu.MoveDown();
                    break;
                }
                break;
            case sf::Event::Closed:
                window.close();
                break;
            }
        }
        else if (currentState == GameState::Game) {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left)
            {
                autoShoot = true;
            }
            if (event.type == sf::Event::MouseButtonReleased &&
                event.mouseButton.button == sf::Mouse::Left)
            {
                autoShoot = false;
            }
        }

        if (event.type == sf::Event::Closed) {
            window.close();
        }

    }
}

void Game::update() {
    srand(time(NULL));

    if (currentState == GameState::Game) {
        //Infomation
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::Vector2f playerPosition = player.getPlayerShape().getPosition();
        sf::FloatRect playerBounds = player.getPlayerShape().getGlobalBounds();

        spawnEnemies();

        // Calculate delta time------------------------------------------------------------------------------------------------------------------------
        deltaTime = clock.restart().asSeconds();

        //Player------------------------------------------------------------------------------------------------------------------------

        player.move(window.getSize().x, window.getSize().y, deltaTime);

        //Bullet------------------------------------------------------------------------------------------------------------------------

        //Auto activate bullet's shooting
        if (autoShoot && bulletFireClock.getElapsedTime().asSeconds() >= bulletFire)
        {
            Bullet bullet(bulletTexture, playerPosition, sf::Vector2f(mousePosition),
                widthWindow, heightWindow);
            bullets.push_back(bullet);
            bulletFireClock.restart();
        }

        //Bullet's running function
        for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();)
        {
            bulletIt->move(deltaTime);
            if (bulletIt->outsideWindow(widthWindow, heightWindow))
            {
                bulletIt = bullets.erase(bulletIt);
            }
            else {
                ++bulletIt;
            }
        }

        //std::cout << bullets.size() << std::endl;

        //Enemy------------------------------------------------------------------------------------------------------------------------

        //Collision between player and enemies
        for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();) {
            enemyIt->move(player.getPlayerShape().getPosition(), widthWindow, heightWindow, deltaTime);
            if (enemyIt->enemyAssault(playerBounds))
            {
                enemyIt = enemies.erase(enemyIt);
            }
            else
            {
                ++enemyIt;
            }
        }

        // Check collision between bullets and enemies
        for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
            bool bulletRemoved = false;
            sf::FloatRect bulletBounds = bulletIt->getBulletShape().getGlobalBounds();
            for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();) {
                if (enemyIt->getEnemyShape().getGlobalBounds().intersects(bulletBounds)) {
                    bulletIt = bullets.erase(bulletIt);
                    sf::Vector2f enemyPosition = enemyIt->getEnemyShape().getPosition();
                    enemyIt = enemies.erase(enemyIt);
                    bulletRemoved = true;
                    break;
                }
                else {
                    ++enemyIt;
                }
            }
            if (!bulletRemoved) {
                ++bulletIt;
            }
        }

    }

    //Menu------------------------------------------------------------------------------------------------------------------------
    else if (currentState == GameState::Menu) {
        Menu menu(window.getSize().x, window.getSize().y);
    }

}

void Game::render()
{
    window.clear();
    if (currentState == GameState::Menu) {
        window.draw(background);
        menu.draw(window);
    }
    else if (currentState == GameState::Game) {
        window.draw(mapInGame);
        //window.draw(player.getPlayerShape());
        //window.draw(player.getPlayerSprite());
        player.draw(window);
        for (auto& bullet : bullets) {
            //window.draw(bullet.getBulletShape());
            bullet.draw(window);
        }
        for (auto& enemy : enemies) {
            //window.draw(enemy.getEnemyShape());
            enemy.draw(window);
        }
    }
    window.display();
}

void Game::run() {
    while (window.isOpen()) {
        HandleEvents();
        update();
        render();
    }
}

void Game::spawnEnemies() {
    if (waveClock.getElapsedTime().asSeconds() >= waveDelay) {
        if (currentWave < 10) {
            enemiesPlus = 1;
        }
        else if (currentWave < 20 && currentWave >= 10) {
            enemiesPlus = 2;
        }
        else if (currentWave >= 20) {
            enemiesPlus = +3;
        }
        enemiesNumb = startWave + enemiesPlus;
        for (int i = 0; i < enemiesNumb; ++i) {
            if (rand() % 2 == 0) {
                spawnPosition_X = rand() % widthWindow;
                spawnPosition_Y = rand() % 2 == 0 ? 0 :
                    heightWindow;
            }
            else {
                spawnPosition_X = rand() % 2 == 0 ? 0 :
                    widthWindow;
                spawnPosition_Y = rand() % heightWindow;
            }
            Enemy enemy(enemyTexture, sf::Vector2f(spawnPosition_X, spawnPosition_Y));
            enemies.push_back(enemy);
            //enemies.emplace_back(enemyTexture, sf::Vector2f(spawnPosition_X, spawnPosition_Y));
        }
        startWave = enemiesNumb;
        currentWave++;
        waveClock.restart();
        std::cout << enemiesNumb << std::endl;
    }
}
