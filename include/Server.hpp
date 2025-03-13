/*
** Server.hpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Wed Mar 12 13:17:27 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Fri Mar 13 14:59:59 2025 Elias Josué HAJJAR LLAUQUEN
*/

#ifndef SERVER_HPP_
# define SERVER_HPP_
#include <vector>
#include "Client.hpp"
#include "Accounts.hpp"

namespace myftp {

    class Client;

    class Server {
        public:
            Server(int port, char start_path[2048]);
            ~Server() {};
            void start_accounts();
            bool check_logins(std::string username, std::string password);
            void start_loop();
            std::vector<myftp::Client> _clients;
            std::vector<struct pollfd> _poll_fds;
            struct sockaddr_in _server_address_control;
            struct sockaddr_in _client_addr;
        private:
            int _server_socket;
            int _client_socket;
            std::string _start_path;
            std::vector<myftp::Accounts> _accounts;
            std::vector<struct pollfd> *_g_poll_fds;
    };
}

#endif /* !SERVER_HPP_ */
