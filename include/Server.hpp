/*
** Server.hpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Wed Mar 12 13:17:27 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Fri Mar 13 12:13:59 2025 Elias Josué HAJJAR LLAUQUEN
*/

#ifndef SERVER_HPP_
# define SERVER_HPP_
#include <vector>
#include "Client.hpp"

namespace myftp {
    class Server {
        public:
            Server(int port, char start_path[2048]) {
                _server_socket = socket(AF_INET, SOCK_STREAM, 0);
                if (_server_socket < 0)
                    throw std::runtime_error("Socket not valid");
                
                int option = 1;
                if (setsockopt(_server_socket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)) < 0)
                    throw std::runtime_error("Reusage of port impossible");

                _server_address_control.sin_family = AF_INET;
                _server_address_control.sin_port = htons(port);
                _server_address_control.sin_addr.s_addr = INADDR_ANY;

                if (bind(_server_socket, (struct sockaddr*) &_server_address_control, sizeof(_server_address_control)) < 0)
                    throw std::runtime_error("Error in socket");

                if (listen(_server_socket, 5) < 0)
                    throw std::runtime_error("Error with listen");

                _poll_fds.push_back({
                    .fd = _server_socket,
                    .events = POLLIN,
                    .revents = 0
                });

                _poll_fds[0].fd = _server_socket;
                _poll_fds[0].events = POLLIN;

                _start_path = std::string(start_path);

                start_accounts();
            };
            ~Server() {};
            void start_accounts() {
                _accounts.push_back(Accounts("Anonymous", " "));
                _accounts.push_back(Accounts());
            };
            void start_loop() {
                while (1) {
                    int poll_count = poll(_poll_fds.data(), _poll_fds.size(), 1000);
            
                    if (poll_count < 0)
                        throw std::runtime_error("poll error");
            
                    if (_poll_fds[0].revents & POLLIN) {
                        socklen_t client_len = sizeof(_client_addr);
                        _client_socket = accept(_server_socket, (struct sockaddr*) &_client_addr, &client_len);
            
                        if (_client_socket < 0) {
                            std::perror("Error new client");
                            continue;
                        }
                        
                        _poll_fds.push_back({
                            .fd = _client_socket,
                            .events = POLLIN | POLLOUT
                        });
            
                        _clients.push_back(Client(_client_socket, std::string(_start_path)));
            
                        printf("Connection from %s:%d\n", inet_ntoa(_client_addr.sin_addr), ntohs(_client_addr.sin_port));
                    }
                    
                    for (int i = _poll_fds.size() - 1; i >= 1; i--) {
                        int client_index = i - 1;
            
                        if (_poll_fds[i].revents & POLLIN) {
                            char buffer[1024];
                            std::string command;
                            int len = read(_poll_fds[i].fd, buffer, 1024);  
            
                            if (len <= 0) {
                                std::perror("Error reading from client\n");
                                close(_poll_fds[i].fd);
                                _poll_fds.erase(_poll_fds.begin() + i);
                                _clients.erase(_clients.begin() + client_index);
                                continue;
                            }
                            buffer[len] = '\0';
                            command.assign(buffer, len);
            
                            if (_clients[client_index].set_command(command.substr(0, 4), command.substr(0, 3))) {
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
                                _clients[client_index].set_data(argument);
                                _poll_fds[i].events |= POLLOUT;
                                continue;
                            }
                        }
                        if (_poll_fds[i].revents & POLLOUT) {
                            if (!_clients[client_index].has_to_process()) {
                                continue;
                            }
                            _clients[client_index].process_command(_accounts, _server_address_control, _poll_fds, _clients, i);
                            _poll_fds[i].events &= ~POLLOUT;
                        }
                    }
                }
                close(_server_socket);
            }
        private:
            int _server_socket;
            int _client_socket;
            std::string _start_path;
            struct sockaddr_in _server_address_control;
            struct sockaddr_in _client_addr;
            std::vector<Client> _clients;
            std::vector<Accounts> _accounts;
            std::vector<struct pollfd> _poll_fds;
            std::vector<struct pollfd> *_g_poll_fds;
    };
}

#endif /* !SERVER_HPP_ */
