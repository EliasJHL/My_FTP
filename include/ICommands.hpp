/*
** ICommands.hpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Thu Mar 13 11:30:35 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Fri Mar 13 14:46:21 2025 Elias Josué HAJJAR LLAUQUEN
*/

#ifndef ICOMMANDS_HPP_
# define ICOMMANDS_HPP_

#include <vector>
#include <unistd.h>
#include <string>
#include "CommandsEnum.hpp"

namespace myftp {

    class Client;
    class Server;

    class ICommands {
        public:
            virtual ~ICommands() = default;
            virtual void execute(Client &client, Server &server, int i, std::string arg) = 0;
            virtual bool need_login() const = 0; 
    };
}

#endif /* !ICOMMANDS_HPP_ */
