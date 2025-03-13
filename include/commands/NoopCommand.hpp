/*
** Noop.hpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include/commands
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Thu Mar 13 12:31:06 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Fri Mar 13 14:51:55 2025 Elias Josué HAJJAR LLAUQUEN
*/

#ifndef NOOPCOMMAND_HPP_
# define NOOPCOMMAND_HPP_

#include "../ICommands.hpp"

namespace myftp {
    class NoopCommand : public ICommands {
        public:
            NoopCommand();
            ~NoopCommand();
            void execute(Client &client, Server &server, int i, std::string arg) override;
            bool need_login() const override;
    };
}

#endif /* !NOOP_HPP_ */
