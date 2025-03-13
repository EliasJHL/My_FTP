/*
** QuitCommand.hpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include/commands
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Thu Mar 13 14:50:02 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Fri Mar 13 14:51:10 2025 Elias Josué HAJJAR LLAUQUEN
*/

#ifndef QUITCOMMAND_HPP_
# define QUITCOMMAND_HPP_

#include "../ICommands.hpp"

namespace myftp {
    class QuitCommand : public ICommands {
        public:
            QuitCommand();
            ~QuitCommand();
            void execute(Client &client, Server &server, int i, std::string arg) override;
            bool need_login() const override;
    };
}

#endif /* !QUITCOMMAND_HPP_ */
