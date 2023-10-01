//#define _CRT_SECURE_NO_WARNINGS
#include "game.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

Game::Game()
    : window(sf::VideoMode(widthWindow, heightWindow), "SFML Game"),
    player(playerTexture, window.getSize().x, window.getSize().y),
    menu(widthWindow, heightWindow)
{
    sf::RenderWindow window(sf::VideoMode(widthWindow, heightWindow), "SFML GAME");
    window.setFramerateLimit(frameRate);

    playerHP = 50;
    score = 0;
    currentWave = 0;
    enemiesNumb = 0;
    enemiesPlus = 0;
    startWave = 5;
    waveDelay = 3.0f;
    gameStart = false;
    autoShoot = false;

    currentState = GameState::Menu;

    if (!menuTexture.loadFromFile("Textures/rayquaza.jpg")) {
        //handle error
    }
    menuBackground.setTexture(menuTexture);
    //background.setScale(1.5f, 1.5f);
    menuBackground.setOrigin(menuBackground.getGlobalBounds().width / 2,
        menuBackground.getGlobalBounds().height / 2);
    menuBackground.setScale(1.36f, 1.36f);
    menuBackground.setPosition(sf::Vector2f(widthWindow / 2, heightWindow / 2));

    if (!inputTexture.loadFromFile("Textures/forest.jpg")) {
        //handle error
    }
    inputBackground.setTexture(inputTexture);
    //background.setScale(1.5f, 1.5f);
    inputBackground.setOrigin(inputBackground.getGlobalBounds().width / 2,
        inputBackground.getGlobalBounds().height / 2);
    inputBackground.setScale(1.0f, 1.0f);
    inputBackground.setPosition(sf::Vector2f(widthWindow / 2, heightWindow / 2));

    if (!inGameTexture.loadFromFile("Textures/grass.jpg")) {
        //handle error
    }
    mapInGame.setTexture(inGameTexture);
    //background.setScale(1.5f, 1.5f);
    mapInGame.setOrigin(mapInGame.getGlobalBounds().width / 2,
        mapInGame.getGlobalBounds().height / 2);
    mapInGame.setScale(1.8f, 1.8f);
    mapInGame.setPosition(sf::Vector2f(widthWindow / 2, heightWindow / 2));

    if (!font.loadFromFile("Texts/Roboto-Bold.ttf")); {
        //handle error
    }

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
                            inputPlayerName();
                            gameStart = true;
                            waveClock.restart();
                            currentWave = 0;
                            enemiesNumb = 0;
                            enemiesPlus = 0;
                            break;
                        case 1:
                            std::cout << "LeaderBoard has been pressed" << std::endl;
                            currentState = GameState::LeaderBoard;
                            break;
                        case 2:
                            std::cout << "Exit has been pressed" << std::endl;
                            currentState = GameState::Exit;
                            break;
                        }
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

        else if (currentState == GameState::LeaderBoard) {
            switch (event.type) {
            case sf::Event::KeyReleased:
                switch (event.key.code) {
                case sf::Keyboard::Return:
                case sf::Keyboard::T:
                    currentState = GameState::Menu;
                    break;
                }
                break;
            }
        }

        else if (currentState == GameState::Game) {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
                currentState = GameState::Menu;
                FILE* fp;
                if (fopen_s(&fp, "score.txt", "a") == 0) {
                    fprintf(fp, "%d\n", score);
                    fclose(fp);
                }
                playerHP = 50;
                score = 0;
                playerName = "";
                player.resetPosition(widthWindow, heightWindow);
                bullets.clear();
                enemies.clear();
                gameStart = false;
                waveClock.restart();
                currentWave = 0;
                enemiesNumb = 0;
                enemiesPlus = 0;
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

    //Menu--------------------------------------------------------------

    if (currentState == GameState::Menu) {
        Menu menu(window.getSize().x, window.getSize().y);
    }

    //LeaderBoard-------------------------------------------------------

    else if (currentState == GameState::LeaderBoard) {
        /*FILE* fp;
        fp = fopen("score.txt", "r");
        for (int i = 0; i < 5; i++) {
            fscanf(fp, "%s", &temp);
            nameFile[i] = temp;
            fscanf(fp, "%d", &scoreFile);
            userScore.push_back(std::make_pair(scoreFile[i], nameFile[i]));
        }
        sort(userScore.begin(), userScore.end());
        fclose(fp);
        fopen("score.txt", "w");
        for (int i = 5; i >= 1; i--) {
            strcpy(temp, userScore[i].second.c_str());
            fprintf(fp, "%s %d", temp, userScore[i].first);
        }
        fclose(fp);*/

        //loadLeaderBoard();

        leaderBoard.setFont(font);
        leaderBoard.setCharacterSize(40);
        leaderBoard.setString("LEADERBOARD");
        leaderBoard.setFillColor(sf::Color::Blue);
        leaderBoard.setOutlineThickness(3);
        leaderBoard.setOutlineColor(sf::Color::White);
        leaderBoard.setPosition(sf::Vector2f(20.0f, 20.0f));

        //Top01 Player
        //top1.setFont(font);
        //top1.setCharacterSize(20);
        //top1.setString(userScore[5].second);
        //top1.setFillColor(sf::Color::Black);
        //top1.setOutlineThickness(2);
        //top1.setOutlineColor(sf::Color::White);
        //top1.setPosition(sf::Vector2f(20.0f, 80.0f));
        
        //score1.setFont(font);
        //score1.setCharacterSize(20);
        //score1.setString(std::to_string(userScore[5].first));
        //score1.setFillColor(sf::Color::Black);
        //score1.setOutlineThickness(2);
        //score1.setOutlineColor(sf::Color::White);
        //score1.setPosition(sf::Vector2f(100.0f, 80.0f));

    }

    //Game--------------------------------------------------------------

    else if (currentState == GameState::Game) {
        //Infomation---------------------------
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::Vector2f playerPosition = player.getPlayerShape().getPosition();
        sf::FloatRect playerBounds = player.getPlayerShape().getGlobalBounds();
        
        spawnEnemies();

        nameText.setFont(font);
        nameText.setCharacterSize(20);
        nameText.setFillColor(sf::Color::White);
        nameText.setOutlineThickness(2);
        nameText.setOutlineColor(sf::Color::Black);
        nameText.setPosition(sf::Vector2f(20.0f, 20.0f));

        scoreText.setFont(font);
        scoreText.setCharacterSize(20);
        scoreText.setFillColor(sf::Color::White);
        std::stringstream scoreShow;
        scoreShow << "Score : " << score;
        scoreText.setString(scoreShow.str());
        scoreText.setOutlineThickness(2);
        scoreText.setOutlineColor(sf::Color::Black);
        scoreText.setPosition(sf::Vector2f(20.0f, 60.0f));

        HPText.setFont(font);
        HPText.setCharacterSize(20);
        HPText.setFillColor(sf::Color(250, 50, 250));
        std::stringstream HPShow;
        HPShow << "Health : " << playerHP;
        HPText.setString(HPShow.str());
        HPText.setOutlineThickness(2);
        HPText.setOutlineColor(sf::Color::Black);
        HPText.setPosition(sf::Vector2f(20.0f, 100.0f));

        //std::cout << enemiesNumb << std::endl;

        // Calculate delta time----------------
        
        deltaTime = clock.restart().asSeconds();

        //Player-------------------------------

        player.move(window.getSize().x, window.getSize().y, deltaTime);
        if (playerHP > 50) {
            playerHP = 50;
        }
        else if (playerHP == 0) {
            currentState = GameState::Menu;
            FILE* fp;
            if (fopen_s(&fp, "score.txt", "a") == 0) {
                fprintf(fp, "%d\n", score);
                fclose(fp);
            }
            playerHP = 50;
            score = 0;
            playerName = "";
            player.resetPosition(widthWindow, heightWindow);
            bullets.clear();
            enemies.clear();
            gameStart = false;
            waveClock.restart();
            currentWave = 0;
            enemiesNumb = 0;
            enemiesPlus = 0;
        }
        else if (playerHP < 0) {
            playerHP = 0;
        }

        //Bullet-------------------------------
        
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

        //Enemy--------------------------------

        //Collision between player and enemies
        for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();) {
            enemyIt->move(player.getPlayerShape().getPosition(), widthWindow, heightWindow, deltaTime);
            if (enemyIt->enemyAssault(playerBounds))
            {
                playerHP -= 5;
                score -= 1;
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
                    score += 2;
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
}

void Game::render() {
    window.clear();
    if (currentState == GameState::Menu) {
        window.draw(menuBackground);
        menu.draw(window);
    }
    else if (currentState == GameState::LeaderBoard) {
        window.draw(leaderBoard);
        //window.draw(top1);
        //window.draw(score1);
    }
    else if (currentState == GameState::Game) {
        window.draw(mapInGame);
        for (auto& bullet : bullets) {
            bullet.draw(window);
        }
        for (auto& enemy : enemies) {
            enemy.draw(window);
        }
        player.draw(window);
        window.draw(nameText);
        window.draw(scoreText);
        window.draw(HPText);
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

void Game::inputPlayerName() {
    sf::Text inputText;
    inputText.setFont(font);
    inputText.setCharacterSize(30);
    inputText.setFillColor(sf::Color::White);
    inputText.setString("Enter your name :");
    inputText.setOutlineThickness(3);
    inputText.setOutlineColor(sf::Color::Black);
    inputText.setOrigin(inputText.getGlobalBounds().width / 2,
        inputText.getGlobalBounds().height / 2);
    inputText.setPosition(sf::Vector2f(widthWindow / 2.0f, heightWindow / 2.0f));

    std::string inputBuffer;

    bool enteringName = true;
    while (enteringName) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    inputBuffer += static_cast<char>(event.text.unicode);
                    inputText.setString("Enter your name :\n" + inputBuffer);
                }
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
                playerName = inputBuffer;
                enteringName = false;
                inputBuffer = "";
            }
        }

        window.clear();
        window.draw(inputBackground);
        window.draw(inputText);
        window.display();
    }

    nameText.setString("Name : " + playerName);

    FILE* fp;
    if (fopen_s(&fp, "score.txt", "a") == 0) {
        fprintf(fp, "%s ", playerName.c_str());
        fclose(fp);
    }
}

//void Game::loadLeaderBoard() {
//    char temp[255];
//    int scoreFile[6];
//    std::string nameFile[6];
//    std::vector <std::pair<int, std::string>> userScore;
//
//    FILE* fp;
//    fp = fopen("score.txt", "r");
//    for (int i = 0; i < 5; i++) {
//        fscanf(fp, "%s", &temp);
//        nameFile[i] = temp;
//        fscanf(fp, "%d", &scoreFile);
//        userScore.push_back(std::make_pair(scoreFile[i], nameFile[i]));
//    }
//    sort(userScore.begin(), userScore.end());
//    fclose(fp);
//    fopen("score.txt", "w");
//    for (int i = 5; i >= 1; i--) {
//        strcpy(temp, userScore[i].second.c_str());
//        fprintf(fp, "%s %d", temp, userScore[i].first);
//    }
//    fclose(fp);
//}

void Game::spawnEnemies() {
    if (gameStart == true) {
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
            startWave = enemiesNumb;
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
            }
            currentWave++;
            waveClock.restart();

            if (playerHP == 0 || sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
                currentWave = 0;
                enemiesNumb = 0;
                enemiesPlus = 0;
            }
        }
    }
}
