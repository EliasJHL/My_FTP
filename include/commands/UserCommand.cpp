/*
** User.cpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include/commands
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Thu Mar 13 12:34:40 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Fri Mar 13 14:47:10 2025 Elias Josué HAJJAR LLAUQUEN
*/

#include "UserCommand.hpp"
#include "../Client.hpp"

myftp::UserCommand::UserCommand() {
}

myftp::UserCommand::~UserCommand() {
}

void myftp::UserCommand::execute(Client &client, Server &server, int i, std::string arg) {
    client.set_temp_username(arg);
    write(client.get_fd(), "331 User name okay, need password.\r\n", 36);
};

bool myftp::UserCommand::need_login() const {
    return false;
};