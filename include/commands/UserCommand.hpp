/*
** UserCommand.hpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include/commands
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Thu Mar 13 12:58:54 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Fri Mar 13 14:35:11 2025 Elias Josué HAJJAR LLAUQUEN
*/

#ifndef USERCOMMAND_HPP_
# define USERCOMMAND_HPP_

#include "../ICommands.hpp"

namespace myftp {
    class UserCommand : public ICommands{
        public:
            UserCommand();
            ~UserCommand();
            void execute(Client &client, Server &server, int i, std::string arg) override;
            bool need_login() const override;
    };
}

#endif /* !USERCOMMAND_HPP_ */
