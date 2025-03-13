/*
** Pass.cpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include/commands
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Thu Mar 13 12:34:40 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Fri Mar 13 15:45:39 2025 Elias Josué HAJJAR LLAUQUEN
*/

#include "PassCommand.hpp"
#include "../Client.hpp"

myftp::PassCommand::PassCommand(){
}

myftp::PassCommand::~PassCommand(){
}

bool check_logins(std::vector<myftp::Accounts> accounts, char *username, char *password) {
    for (int i = 0; i < accounts.size(); i++) {
        if (accounts[i].check_login(username, password)) {
            return true;
        }
    }
    return false;
}

void myftp::PassCommand::execute(Client &client, Server &server, int i, std::string arg) {
    if (client.get_temp_username() == "" || client.get_temp_username().empty()) {
        write(client.get_fd(), "332 Need account for login.\r\n", 29);
    } else if (server.check_logins(client.get_temp_username(), arg)) {
        client.login(client.get_temp_username(), arg);
        write(client.get_fd(), "230 User logged in, proceed.\r\n", 30);
    } else {
        write(client.get_fd(), "530 Login incorrect.\r\n", 22);
        client.set_temp_username("");
    }
};

bool myftp::PassCommand::need_login() const {
    return false;
};