/*
** StorCommand.hpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include/commands
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Fri Mar 14 12:45:49 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Sat Mar 14 12:46:20 2025 Elias Josué HAJJAR LLAUQUEN
*/

#ifndef STORCOMMAND_HPP_
# define STORCOMMAND_HPP_

#include "../CommandsEnum.hpp"
#include "../ICommands.hpp"

namespace myftp {
    class StorCommand : public ICommands{
        public:
            StorCommand();
            ~StorCommand();
            void execute(Client &client, Server &server, int i, std::string arg) override;
            bool need_login() const override;
    };
}
#endif /* !STORCOMMAND_HPP_ */
