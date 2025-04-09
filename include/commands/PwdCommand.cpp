/*
** PwdCommand.cpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include/commands
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Thu Mar 13 15:36:34 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Mon Mar 16 02:48:10 2025 Elias Josué HAJJAR LLAUQUEN
*/

#include "PwdCommand.hpp"
#include "../Client.hpp"

myftp::PwdCommand::PwdCommand()
{
}

myftp::PwdCommand::~PwdCommand()
{
}

void myftp::PwdCommand::execute(Client &client, Server &server, int i, std::string arg) {
    std::string pwd;
    pwd = "257 " + client.get_path() + " created.\r\n";
    write(client.get_fd(), pwd.c_str(), pwd.size());
};

bool myftp::PwdCommand::need_login() const {
    return true;
};
