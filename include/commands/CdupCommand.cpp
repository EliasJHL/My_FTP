/*
** CdupCommand.cpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include/commands
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Thu Mar 13 15:09:46 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Fri Mar 13 15:16:15 2025 Elias Josué HAJJAR LLAUQUEN
*/

#include "CdupCommand.hpp"
#include "../Client.hpp"

myftp::CdupCommand::CdupCommand()
{
}

myftp::CdupCommand::~CdupCommand()
{
}

void myftp::CdupCommand::execute(Client &client, Server &server, int i, std::string arg) {
    char new_path[2048];
    if (chdir("..") == 0) {
        getcwd(new_path, 2048);
        client.set_path(std::string(new_path));
        write(client.get_fd(), "250 Requested file action okay, completed.\r\n", 44);
    } else {
        write(client.get_fd(), "550 Requested action not taken.\r\n", 34);
    }
};

bool myftp::CdupCommand::need_login() const {
    return true;
};