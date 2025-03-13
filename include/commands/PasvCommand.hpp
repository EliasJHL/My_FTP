/*
** PasvCommand.hpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include/commands
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Thu Mar 13 14:57:52 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Fri Mar 13 14:58:22 2025 Elias Josué HAJJAR LLAUQUEN
*/

#ifndef PASVCOMMAND_HPP_
# define PASVCOMMAND_HPP_

#include "../ICommands.hpp"

namespace myftp {
    class PasvCommand : public ICommands{
        public:
            PasvCommand();
            ~PasvCommand();
            void execute(Client &client, Server &server, int i, std::string arg) override;
            bool need_login() const override;
    };
}

#endif /* !PASVCOMMAND_HPP_ */
