/*
** PwdCommand.hpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include/commands
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Thu Mar 13 15:36:12 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Fri Mar 13 15:36:31 2025 Elias Josué HAJJAR LLAUQUEN
*/

#ifndef PWDCOMMAND_HPP_
# define PWDCOMMAND_HPP_

#include "../CommandsEnum.hpp"
#include "../ICommands.hpp"

namespace myftp {
    class PwdCommand : public ICommands{
        public:
            PwdCommand();
            ~PwdCommand();
            void execute(Client &client, Server &server, int i, std::string arg) override;
            bool need_login() const override;
    };
}

#endif /* !PWDCOMMAND_HPP_ */
