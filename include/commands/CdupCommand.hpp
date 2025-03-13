/*
** CdupCommand.hpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include/commands
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Thu Mar 13 15:09:23 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Fri Mar 13 15:09:39 2025 Elias Josué HAJJAR LLAUQUEN
*/

#ifndef CDUPCOMMAND_HPP_
# define CDUPCOMMAND_HPP_

#include "../CommandsEnum.hpp"
#include "../ICommands.hpp"

namespace myftp {
    class CdupCommand : public ICommands{
        public:
            CdupCommand();
            ~CdupCommand();
            void execute(Client &client, Server &server, int i, std::string arg) override;
            bool need_login() const override;
    };
}

#endif /* !CDUPCOMMAND_HPP_ */
