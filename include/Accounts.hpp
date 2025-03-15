/*
** include.hpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Thu Mar 6 21:30:04 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Sun Mar 15 02:03:33 2025 Elias Josué HAJJAR LLAUQUEN
*/

#ifndef INCLUDE_HPP_
# define INCLUDE_HPP_

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

namespace myftp {

    class Accounts {
        public:
            Accounts(std::string username="", std::string password="");
            ~Accounts();
            void add_account(std::string username, std::string password);
            std::string get_username() const;
            bool check_login(std::string username, std::string password);
        private:
            std::string _username;
            std::string _password;
    };
}


#endif /* !INCLUDE_HPP_ */
