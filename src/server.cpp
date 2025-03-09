/*
** EPITECH PROJECT, 2024
** my_ftp
** File description:
** my_ftp
*/

#include "../include/Accounts.hpp"
#include "../include/Client.hpp"
#include <signal.h>
#include <filesystem>

int server_socket;
std::vector<struct pollfd> *g_poll_fds = nullptr;

bool command_exists(std::string c) {
    std::string command = c.substr(0, 4);

    if (command == "USER" || command == "PASS" || command == "PASV" ||
        command == "QUIT" || command == "HELP" || command == "CWD" || command == "RETR") {
        return true;
    }

    return false;
}

void start_accounts(std::vector<myftp::Accounts> &accounts) {
    accounts.push_back(myftp::Accounts("Anonymous", " "));
    accounts.push_back(myftp::Accounts());
}

void signal_process(int s) {
    if (server_socket >= 0) {
        close(server_socket);
    }
    if (g_poll_fds) {
        for (const auto& fd : *g_poll_fds) {
            if (fd.fd >= 0) {
                close(fd.fd);
            }
        }
    }
    exit(0);
}

int main(int ac, char **av) {
    int server_socket, client_socket;
    struct sigaction sigIntHandler;
    struct sockaddr_in server_address_control;
    struct sockaddr_in client_addr;
    std::vector<myftp::Client> clients;
    std::vector<struct pollfd> poll_fds;
    g_poll_fds = &poll_fds;
    std::vector<myftp::Accounts> accounts;
    char start_path[2048];

    if (ac != 3) {
        printf("Usage: ./my_ftp <port> <path>\n");
        return 84;
    }

    if (chdir(av[2]) < 0) {
        perror("Error with path");
        return 84;
    }

    getcwd(start_path, 2048);
    start_accounts(accounts);
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket not valid\n");
        return 84;
    }

    // TOASK ne pas oublier -> permet de réutiliser le port -> demander si utile
    int option = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)) < 0) {
        return 84;
    }

    server_address_control.sin_family = AF_INET;
    server_address_control.sin_port = htons(atoi(av[1]));
    server_address_control.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr*) &server_address_control, sizeof(server_address_control)) < 0) {
        perror("Error in socket");
        return 84;
    }
    
    if (listen(server_socket, 5) < 0) {
        perror("Error with listen");
        return 84;
    }

    poll_fds.push_back({
        .fd = server_socket,
        .events = POLLIN,
        .revents = 0
    });

    poll_fds[0].fd = server_socket;
    poll_fds[0].events = POLLIN;

    signal(SIGINT, signal_process);

    while (1) {
        int poll_count = poll(poll_fds.data(), poll_fds.size(), 1000);

        if (poll_count < 0) {
            perror("poll error");
            break;
        }

        if (poll_fds[0].revents & POLLIN) {
            socklen_t client_len = sizeof(client_addr);
            client_socket = accept(server_socket, (struct sockaddr*) &client_addr, &client_len);

            if (client_socket < 0) {
                perror("Error new client");
                continue;
            }
            
            poll_fds.push_back({
                .fd = client_socket,
                .events = POLLIN | POLLOUT
            });

            clients.push_back(myftp::Client(client_socket, std::string(start_path)));

            printf("Connection from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        }
        
        for (int i = poll_fds.size() - 1; i >= 1; i--) {
            int client_index = i - 1;

            if (poll_fds[i].revents & POLLIN) {
                char buffer[1024];
                std::string command;
                int len = read(poll_fds[i].fd, buffer, 1024);  

                if (len <= 0) {
                    printf("Error reading from client\n");
                    close(poll_fds[i].fd);
                    poll_fds.erase(poll_fds.begin() + i);
                    clients.erase(clients.begin() + client_index);
                    continue;
                }
                buffer[len] = '\0';
                command.assign(buffer, len);

                if (clients[client_index].set_command(command.substr(0, 4), command.substr(0, 3))) {
                    size_t pos = command.find(' ');
                    std::string argument;
                    if (pos != std::string::npos) {
                        if (command.substr(pos + 1) == "\r\n") {
                            argument = " ";
                        } else {
                            argument = command.substr(pos + 1);
                        }
                        argument.erase(argument.find_last_not_of("\r\n") + 1);
                    }
                    clients[client_index].set_data(argument);
                    poll_fds[i].events |= POLLOUT;
                    continue;
                }
            }
            if (poll_fds[i].revents & POLLOUT) {
                if (!clients[client_index].has_to_process()) {
                    continue;
                }
                clients[client_index].process_command(accounts, server_address_control, poll_fds, clients, i);
                poll_fds[i].events &= ~POLLOUT;
            }
        }
    }
    close(server_socket);
    return 0;
}