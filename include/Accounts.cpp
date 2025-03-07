/*
** Accounts.cpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Thu Mar 6 23:25:34 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Fri Mar 6 23:39:28 2025 Elias Josué HAJJAR LLAUQUEN
*/

#include "Accounts.hpp"

myftp::Accounts::Accounts(std::string username, std::string password) {
    _username = username;
    _password = password;
}

myftp::Accounts::~Accounts() {
}

void myftp::Accounts::add_account(std::string username, std::string password) {
    _username = username;
    _password = password;
}

std::string myftp::Accounts::get_username() const {
    return _username;
}

bool myftp::Accounts::check_login(std::string username, std::string password) {
    return username == _username && password == _password;
}


