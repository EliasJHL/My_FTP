/*
** CwdCommand.hpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include/commands
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Thu Mar 13 15:38:06 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Wed Mar 18 14:09:54 2025 Elias Josué HAJJAR LLAUQUEN
*/

#ifndef CWDCOMMAND_HPP_
# define CWDCOMMAND_HPP_

#include "../CommandsEnum.hpp"
#include "../ICommands.hpp"

namespace myftp {
    class CwdCommand : public ICommands{
        public:
            CwdCommand();
            ~CwdCommand();
            void execute(Client &client, Server &server, int i, std::string arg) override;
            bool need_login() const override;
    };
}


#endif /* !CWDCOMMAND_HPP_ */
