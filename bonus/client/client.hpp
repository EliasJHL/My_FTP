/*
** client.hpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/bonus/client
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Sat Mar 15 02:16:50 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Mon Mar 16 02:09:21 2025 Elias Josué HAJJAR LLAUQUEN
*/

#ifndef CLIENT_HPP_
# define CLIENT_HPP_

#include <iostream>
#include <regex>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <string.h>

class Client {
    public:
    int _fd;
    std::string username;
    std::string password;
        
    private:
    int _data_fd;
        
};

#endif /* !CLIENT_HPP_ */
