/*
** CwdCommand.cpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include/commands
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Thu Mar 13 15:38:36 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Sun Mar 15 19:34:08 2025 Elias Josué HAJJAR LLAUQUEN
*/

#include "CwdCommand.hpp"
#include "../Client.hpp"

myftp::CwdCommand::CwdCommand()
{
}

myftp::CwdCommand::~CwdCommand()
{
}

void myftp::CwdCommand::execute(Client &client, Server &server, int i, std::string arg) {
    char new_path[2048];
    std::string temp_path;

    if (arg.empty()) {
        write(client.get_fd(), "501 Syntax error in parameters or arguments.\r\n", 47);
        return;
    }

    if (arg == "/") {
        temp_path = client.get_home_path();
    } else if (arg[0] == '/') {
        temp_path = arg;
    } else {
        temp_path = client.get_path() + "/" + arg;
    }

    int ret = chdir(temp_path.c_str());
    if (ret != -1) {
        chdir(temp_path.c_str());
        getcwd(new_path, 2048);
        std::string test_path(new_path);

        if (test_path.find(client.get_home_path()) == std::string::npos) {
            chdir(client.get_path().c_str());
            write(client.get_fd(), "550 Requested action not taken.\r\n", 34);
            return;
        }

        client.set_path(std::string(new_path));
        write(client.get_fd(), "250 Requested file action okay, completed.\r\n", 44);
    } else {
        write(client.get_fd(), "550 Requested action not taken.\r\n", 34);
    }
};

bool myftp::CwdCommand::need_login() const {
    return true;
};

