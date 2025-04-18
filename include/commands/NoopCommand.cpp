/*
** Noop.cpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include/commands
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Thu Mar 13 12:34:40 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Sat Mar 14 11:32:45 2025 Elias Josué HAJJAR LLAUQUEN
*/

#include "NoopCommand.hpp"
#include "../Client.hpp"

myftp::NoopCommand::NoopCommand() {
}

myftp::NoopCommand::~NoopCommand()
{
}

void myftp::NoopCommand::execute(Client &client, Server &server, int i, std::string arg) {
    write(client.get_fd(), "200 Command okay.\r\n", 19);
};

bool myftp::NoopCommand::need_login() const {
    return false;
};