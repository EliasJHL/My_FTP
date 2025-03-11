/*
** Client.hpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Thu Mar 6 23:23:31 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Wed Mar 11 13:35:48 2025 Elias Josué HAJJAR LLAUQUEN
*/

#ifndef CLIENT_HPP_
# define CLIENT_HPP_
#include <iostream>
#include <poll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>
#include <unistd.h>
#include <algorithm>
#include <string>
#include <cstring>
#include <fstream>
#include "Accounts.hpp"

namespace myftp {

    class Accounts;
    
    enum COMMAND {
        NONE = 0,
        PASV = 1,
        QUIT = 2,
        USER = 3,
        PASS = 4,
        HELP = 5,
        CWD = 6,
        RETR = 7,
        NOOP = 8,
        PWD = 9,
        CDUP = 10,
        DELE = 11,
        PORT = 12
    };

    enum DATA_TRANSFER {
        DATA_NONE = 0,
        DATA_PASV = 1,
        DATA_PORT = 2
    };
    
    class Client {
        public:
            Client(int fd, std::string current_path);
            ~Client();
            void set_data(std::string data);
            bool has_to_process();
            bool set_command(std::string command, std::string command_three_char);
            bool check_if_login();
            void process_command(std::vector<myftp::Accounts> accounts, struct sockaddr_in server_address_control, std::vector<struct pollfd> &poll_fds, std::vector<myftp::Client> &clients, int i);
        private:
            int _fd;
            int _transfer_fd;
            bool _has_to_process;
            bool _is_login;
            DATA_TRANSFER _data_transfer;
            std::string _port_client_ip;
            std::string _port_client_port;
            Accounts *_account_logged;
            std::string _temp_username;
            std::string _home_path;
            std::string _current_path;
            COMMAND _command;
            std::string _data;
    };
}

#endif /* !CLIENT_HPP_ */
