/*
** HelpCommand.cpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include/commands
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Thu Mar 13 12:57:36 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Fri Mar 13 14:50:24 2025 Elias Josué HAJJAR LLAUQUEN
*/

#include "HelpCommand.hpp"
#include "../Client.hpp"

myftp::HelpCommand::HelpCommand() {
}

myftp::HelpCommand::~HelpCommand() {
}

void myftp::HelpCommand::execute(Client &client, Server &server, int i, std::string arg) {
    write(client.get_fd(), "214 Help message.\r\n", 19);
};

bool myftp::HelpCommand::need_login() const {
    return false;
};