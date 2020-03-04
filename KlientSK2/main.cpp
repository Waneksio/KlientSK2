#include <unistd.h>
#include <errno.h>
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>
#include <cstdlib>
#include <cstdio>
#include <error.h>
#include <sys/epoll.h>
#include <iostream>
#include <vector>
#include <fcntl.h>
#include <cstring>
#include <netdb.h>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Food.h"

/* GLOBAL VARIABLES:
-----------------------------------------------------------------------------*/
char * ip = "127.0.0.1";
char * port = "8080";
int my_id;
Player * myPlayer;
std::vector<Player*> otherPlayers;
std::vector<Food*> snacks;
const int windowX = 800, windowY = 800;
int maxPlayersCount = 10;

/* HANDLING INPUT FROM SERVER:
-----------------------------------------------------------------------------*/
void handleInputs(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
                return;
                break;

            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                {
                    std::cout << "Esc\n";
                    window.close();
                }
                /*
                if (event.key.code == sf::Keyboard::Up)
                {
                    std::cout << "up\n";
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    std::cout << "down\n";
                }
                if (event.key.code == sf::Keyboard::Left)
                {
                    std::cout << "left\n";
                }
                if (event.key.code == sf::Keyboard::Right)
                {
                    std::cout << "right\n";
                }
                */
                break;

            default:
                break;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            std::cout << "up\n";
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            std::cout << "down\n";
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            std::cout << "left\n";
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            std::cout << "right\n";
        }
    }
}

void display(sf::RenderWindow& window)
{
    float radius = 100.0f;

    static sf::CircleShape playerCircle(radius);
    //playerCircle.setRadius(100.0f);
    playerCircle.setPointCount(10000);
    playerCircle.setFillColor(sf::Color(150, 50, 80));
    playerCircle.setOutlineThickness(-(radius / 10.0f));
    playerCircle.setOutlineColor(sf::Color(75, 25, 40));
    playerCircle.setPosition(((float)windowX) / 2.0f - radius, ((float)windowX) / 2.0f - radius);
    //playerCircle.move(1.0f, 1.0f);

    window.clear(sf::Color(22, 22, 33));
    window.draw(playerCircle);
    window.display();
}

int main()
{
/* NETWORK INITIALIZATION:
-----------------------------------------------------------------------------*/
    addrinfo hints {};
    hints.ai_family = AF_INET;
    hints.ai_protocol = IPPROTO_TCP;

    addrinfo* resolved;
    if (int err = getaddrinfo(ip, port, &hints, &resolved))
        error(1, 0, "Resolving address failed: %s", gai_strerror(err));

    int sock = socket(resolved->ai_family, resolved->ai_socktype, resolved->ai_protocol);
    if (connect(sock, resolved->ai_addr, resolved->ai_addrlen))
        error(1, errno, "Failed to connect");
    freeaddrinfo(resolved);

    char message[1024];
    int readIndex = 0;
    int check;
    while (0 < (check = read(sock, message, sizeof(message)))) {
        int id;
        int x;
        int y;
        memcpy(&id, &message[readIndex], sizeof(id));
        readIndex += sizeof(id);
        std::cout << check << "\n";
        std::cout << id << "\n";
        if (id != -1) {
            my_id = id;
            break;
        }
        memcpy(&x, &message[readIndex], sizeof(x));
        readIndex += sizeof(x);
        memcpy(&y, &message[readIndex], sizeof(y));
        readIndex += sizeof(y);
        memset(&message, 0, sizeof(message));
        snacks.emplace_back(new Food(x, y));
    }
    std::cout << my_id << "\n";
    myPlayer = new Player(0, 0, 1, my_id);

    char buffer[1024];
    int writeIndex = 0;
    int playerIndex;
    int newX = 0;
    int newY = 0;
    memcpy(&buffer[writeIndex], &newX, sizeof(newX));
    writeIndex += sizeof(newX);
    memcpy(&buffer[writeIndex], &newY, sizeof(newY));
    writeIndex += sizeof(newY);

/* SFML INITIALIZATION:
-----------------------------------------------------------------------------*/
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(windowX, windowY),
                            "Agario",
                            sf::Style::Default,
                            settings);
    window.setKeyRepeatEnabled(true);

/* MAIN LOOP:
-----------------------------------------------------------------------------*/
    //while (true)
    while (window.isOpen())
    {
        // TODO: displaying players and food, eating food
        //keyboard:
        handleInputs(window);

        //loop break:
        if (writeIndex != write(sock, buffer, writeIndex))
            break;

        while (true)
        {
            int readIndex = 0;
            int xShift;
            int yShift;
            int size;
            bool stop;

            if (0 >= read(sock, &message, sizeof(message)))
                break;


            memcpy(&playerIndex, &message[readIndex], sizeof(playerIndex));
            readIndex += sizeof(playerIndex);
            memcpy(&xShift, &message[readIndex], sizeof(xShift));
            readIndex += sizeof(xShift);
            memcpy(&yShift, &message[readIndex], sizeof(yShift));
            readIndex += sizeof(yShift);
            memcpy(&size, &message[readIndex], sizeof(size));
            readIndex += sizeof(size);
            memcpy(&stop, &message[readIndex], sizeof(stop));

            if (playerIndex == 0 && stop)
                break;

            if ((playerIndex == -1) || (size == -1)) {
                snacks.emplace_back(new Food(xShift, yShift));
                continue;
            }

            bool newPlayer = true;

            for (Player * player : otherPlayers) {
                if (player->mId == playerIndex) {
                    player->move(xShift, yShift, size);
                    newPlayer = false;
                    break;
                }
            }

            if (newPlayer) {
                otherPlayers.emplace_back(new Player(xShift, yShift, size, playerIndex));
            }
        }
        std::cout << snacks.size() << "\n";

        //handle input:
        display(window);
    }
    close(sock);
    return 0;
}