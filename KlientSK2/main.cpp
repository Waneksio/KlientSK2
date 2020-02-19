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

/* GLOBAL VARIABLES:
-----------------------------------------------------------------------------*/
char * ip = "127.0.0.1";
char * port = "8080";
int my_id;
Player * myPlayer;
std::vector<Player*> otherPlayers;
std::string endLoop = std::string("end");
const int windowX = 800, windowY = 800;
int maxPlayersCount = 10;

/* FOOD:
-----------------------------------------------------------------------------*/
class Food
{
private:
    struct FoodPiece
    {
        float x;
        float y;
        int points;
    };
    std::vector<FoodPiece> foodPieces;

public:

};

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
    read(sock, message, sizeof(message));
    std::string id = std::string(message);
    my_id = std::stoi(message);
    std::cout << my_id << "\n";
    myPlayer = new Player(0, 0, 1, my_id);

    std::string newCoordinates = "-10 0";

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
        //keyboard:
        handleInputs(window);

        //loop break:
        if (newCoordinates.length() != write(sock, newCoordinates.data(), newCoordinates.length()))
            break;

        while (true)
        {
            read(sock, &message, sizeof(message));
            std::string newMessage = std::string(message);
            memset(message, 0, sizeof(message));

            if (newMessage.find(endLoop) != std::string::npos)
                break;

            //std::cout << newMessage << "\n";

            int position = newMessage.find(" ");
            std::string identifier = newMessage.substr(0, position);
            int integerId = std::stoi(identifier);
            newMessage = newMessage.substr(position + 1, newMessage.size());
            position = newMessage.find(" ");
            std::string coordinateX = newMessage.substr(0, position);
            newMessage = newMessage.substr(position + 1, newMessage.size());
            position = newMessage.find(" ");
            std::string coordinateY = newMessage.substr(0, position);
            std::string size = newMessage.substr(position + 1, newMessage.size());

            bool newPlayer = true;

            for (Player * player : otherPlayers) {
                if (player->mId == integerId) {
                    player->move(std::stoi(coordinateX), std::stoi(coordinateY), std::stoi(size));
                    newPlayer = false;
                    break;
                }
            }
            if (newPlayer) {
                otherPlayers.emplace_back(new Player(std::stoi(coordinateX), std::stoi(coordinateY), std::stoi(size), integerId));
            }
        }
        std::cout << "XD\n";

        //handle input:
        display(window);
    }
    close(sock);
    return 0;
}