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

char * ip = "127.0.0.1";
char * port = "8080";
int my_id;
std::string endLoop = std::string("end");

int main()
{
    addrinfo hints {};
    hints.ai_family = AF_INET;
    hints.ai_protocol = IPPROTO_TCP;

    addrinfo * resolved;
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

    std::string newCoordinates = "-10 0";

    while (true) {
        if (newCoordinates.length() != write(sock, newCoordinates.data(), newCoordinates.length()))
            break;
        while (true) {
            read(sock, &message, sizeof(message));
            std::string newMessage = std::string(message);
            std::cout << newMessage << "\n";
            memset(message, 0, sizeof(message));
            if (endLoop == message)
                break;
        }
    }

    std::cout << message << "\n";
    close(sock);
    return 0;
}