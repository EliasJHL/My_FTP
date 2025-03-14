/*
** DeleCommand.cpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include/commands
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Thu Mar 13 15:07:52 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Sat Mar 14 21:32:54 2025 Elias Josué HAJJAR LLAUQUEN
*/

#include "DeleCommand.hpp"
#include "../Client.hpp"

myftp::DeleCommand::DeleCommand()
{
}

myftp::DeleCommand::~DeleCommand()
{
}

void myftp::DeleCommand::execute(Client &client, Server &server, int i, std::string arg) {
    if (remove(arg.c_str()) == 0) {
        write(client.get_fd(), "250 Requested file action okay, completed.\r\n", 44);
    } else {
        write(client.get_fd(), "550 Requested action not taken.\r\n", 34);
    }
};

bool myftp::DeleCommand::need_login() const {
    return true;
};