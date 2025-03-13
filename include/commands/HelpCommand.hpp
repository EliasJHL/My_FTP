/*
** HelpCommand.hpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include/commands
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Thu Mar 13 12:56:18 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Fri Mar 13 13:02:03 2025 Elias Josué HAJJAR LLAUQUEN
*/

#ifndef HELPCOMMAND_HPP_
# define HELPCOMMAND_HPP_
#include "../ICommands.hpp"

namespace myftp {
    class HelpCommand : public ICommands  {
        public:
            HelpCommand();
            ~HelpCommand();
            void execute(Client &client, Server &server, int i, std::string arg) override;
            bool need_login() const override;
    };
}

#endif /* !HELPCOMMAND_HPP_ */
