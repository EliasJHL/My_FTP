/*
** NoneCommand.cpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include/commands
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Thu Mar 13 15:16:58 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Fri Mar 13 15:18:35 2025 Elias Josué HAJJAR LLAUQUEN
*/

#include "NoneCommand.hpp"
#include "../Client.hpp"

myftp::NoneCommand::NoneCommand()
{
}

myftp::NoneCommand::~NoneCommand()
{
}

void myftp::NoneCommand::execute(Client &client, Server &server, int i, std::string arg) {
    write(client.get_fd(), arg.c_str(), arg.size());
};

bool myftp::NoneCommand::need_login() const {
    return false;
};
