/*
** QuitCommand.cpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include/commands
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Thu Mar 13 14:52:09 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Sat Mar 14 11:18:30 2025 Elias Josué HAJJAR LLAUQUEN
*/

#include "QuitCommand.hpp"
#include "../Client.hpp"

myftp::QuitCommand::QuitCommand()
{
}

myftp::QuitCommand::~QuitCommand()
{
}

void myftp::QuitCommand::execute(Client &client, Server &server, int i, std::string arg) {
    write(client.get_fd(), "221 Goodbye.\r\n", 14);
    close(server._poll_fds[i].fd);
    if (client._transfer_pid != -1)
        kill(client._transfer_pid, SIGKILL);
    server._poll_fds.erase(server._poll_fds.begin() + i);
    server._clients.erase(server._clients.begin() + i);
}

bool myftp::QuitCommand::need_login() const {
    return false;
};