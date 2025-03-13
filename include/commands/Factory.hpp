/*
** Factory.hpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include/commands
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Thu Mar 13 12:38:01 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Fri Mar 13 16:01:48 2025 Elias Josué HAJJAR LLAUQUEN
*/

#ifndef FACTORY_HPP_
# define FACTORY_HPP_

#include <map>
#include <string>
#include "../CommandsEnum.hpp"
#include "../ICommands.hpp"
#include "Client.hpp"

#include "NoopCommand.hpp"
#include "HelpCommand.hpp"
#include "PassCommand.hpp"
#include "UserCommand.hpp"
#include "RetrCommand.hpp"
#include "ListCommand.hpp"
#include "NoneCommand.hpp"
#include "QuitCommand.hpp"
#include "PwdCommand.hpp"
#include "CwdCommand.hpp"
#include "CdupCommand.hpp"
#include "PasvCommand.hpp"
#include "PortCommand.hpp"
//#include "StorCommand.hpp"
#include "DeleCommand.hpp"

namespace myftp {
    class Factory {
        public:
            Factory();
            ~Factory();
            myftp::ICommands *getCommand(COMMAND cmd);
        private:
            std::map<COMMAND, myftp::ICommands*> commands;
    };
}

#endif /* !FACTORY_HPP_ */
