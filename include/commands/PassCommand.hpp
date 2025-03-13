/*
** PassCommand.hpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include/commands
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Thu Mar 13 13:05:20 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Fri Mar 13 14:38:37 2025 Elias Josué HAJJAR LLAUQUEN
*/

#ifndef PASSCOMMAND_HPP_
# define PASSCOMMAND_HPP_

#include "../CommandsEnum.hpp"
#include "../ICommands.hpp"

namespace myftp {
    class PassCommand : public ICommands{
        public:
            PassCommand();
            ~PassCommand();
            void execute(Client &client, Server &server, int i, std::string arg) override;
            bool need_login() const override;
    };
}

#endif /* !PASSCOMMAND_HPP_ */
