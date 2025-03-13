/*
** PortCommand.hpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include/commands
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Thu Mar 13 15:02:37 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Fri Mar 13 15:02:55 2025 Elias Josué HAJJAR LLAUQUEN
*/

#ifndef PORTCOMMAND_HPP_
# define PORTCOMMAND_HPP_

#include "../CommandsEnum.hpp"
#include "../ICommands.hpp"

namespace myftp {
    class PortCommand : public ICommands{
        public:
            PortCommand();
            ~PortCommand();
            void execute(Client &client, Server &server, int i, std::string arg) override;
            bool need_login() const override;
    };
}

#endif /* !PORTCOMMAND_HPP_ */
