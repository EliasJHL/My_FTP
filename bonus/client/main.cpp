/*
** client.c for bootstrap in /home/elias/Documents/Epitech/my_ftp/bootstrap
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Mon Feb 17 16:21:50 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Sun Mar 15 03:12:47 2025 Elias Josué HAJJAR LLAUQUEN
*/

#include "client.hpp"

int init(Client *client, int ac, char **av) {
    struct sockaddr_in addr;

    if (ac != 3)
        throw std::runtime_error("Usage : ./clientftp <ip> <port>");

    client->_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(av[2]));
    addr.sin_addr.s_addr = inet_addr(av[1]);

    if (connect(client->_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
        throw std::runtime_error("Impossible to connect");

    // char buffer[1024];
    // int len = read(sock, buffer, sizeof(buffer) - 1);
    // buffer[len] = '\0';
    // printf("Server said: %s", buffer);

    // char pasv[] = "PASV";

    // write(sock, pasv, strlen(pasv));
    // char pasv_response[1024];
    // len = read(sock, pasv_response, sizeof(pasv_response) - 1);
    // pasv_response[len] = '\0';
    // printf("Server said: %s", pasv_response);

    // char *cp = malloc(strlen(pasv_response) + 1);
    
    // strcpy(cp, pasv_response);
    // printf("Extracted data: %s\n", pasv_ip(cp));
    // strcpy(cp, pasv_response);
    // printf("Extracted data: %d\n", pasv_port(cp));

    // close(sock);
    
    return 0;
}

void login(Client *client) {
    char data[2048];
    std::string command;
    int size = 0;
    
    read(client->_fd, data, sizeof(data));
    std::cout << "Username (default Anonymous): ";
    std::getline(std::cin, command);
    if (command.empty())
        command = "Anonymous";
    write(client->_fd, std::string("USER " + command + "\r\n").c_str(), std::string("PASS " + command + "\r\n").size());
    read(client->_fd, data, sizeof(data));
    std::cout << "Password (default ' '): ";
    std::getline(std::cin, command);
    if (command.empty())
        command = " ";
    write(client->_fd, std::string("PASS " + command + "\r\n").c_str(), std::string("PASS " + command + "\r\n").size());
    size = read(client->_fd, data, sizeof(data));
    data[size] = '\0';
    std::cout << data;
}

void execute_ls(Client *client, std::string arg) {
    std::string ip;
    int port;
    char data[2048];
    int size = 0;
    struct sockaddr_in addr;
    int sock;

    std::regex const e{"([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+)"};
    std::smatch m;
    
    if (std::regex_search(arg, m, e)) {
        ip = m[1].str() + "." + m[2].str() + "." + m[3].str() + "." + m[4].str();
        port = std::stoi(m[5].str()) * 256 + std::stoi(m[6].str());
    }
    write(client->_fd, "LIST\r\n", 6);
    size = read(client->_fd, data, sizeof(data));
    data[size] = '\0';
    std::cout << data;

    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip.c_str());

    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1)
        throw std::runtime_error("Impossible to connect");

    size = read(sock, data, sizeof(data));
    data[size] = '\0';
    std::cout << data;
    
    size = read(client->_fd, data, sizeof(data));
    data[size] = '\0';
    std::cout << data;

    close(sock);
}

int main(int ac, char **av) {
    Client client;
    std::string command;
    char data[2048];
    int size = 0;

    try {
        init(&client, ac, av);
        login(&client);
        
        std::cout << "ftp> ";
        while (std::getline(std::cin, command)) {
            if (command == "ls") {
                write(client._fd, "PASV\r\n", 6);
                size = read(client._fd, data, sizeof(data));
                data[size] = '\0';
                std::cout << data;
                execute_ls(&client, std::string(data));
            }
            if (command == "pwd") {
                write(client._fd, "PWD\r\n", 5);
                size = read(client._fd, data, sizeof(data));
                data[size] = '\0';
                std::cout << data;
            }
            if (command == "quit" || command == "exit") {
                write(client._fd, "QUIT\r\n", 6);
                size = read(client._fd, data, sizeof(data));
                data[size] = '\0';
                std::cout << data;
                return 0;
            }
            std::cout << "ftp> ";
        }
        
    } catch (std::runtime_error &e) {
        std::cout << e.what() << std::endl;
        return 84;
    }
}