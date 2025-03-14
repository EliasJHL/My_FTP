/*
** PortCommand.cpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include/commands
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Thu Mar 13 15:02:58 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Sat Mar 14 21:15:45 2025 Elias Josué HAJJAR LLAUQUEN
*/

#include "PortCommand.hpp"
#include "../Client.hpp"
#include <regex>

myftp::PortCommand::PortCommand() {
}

myftp::PortCommand::~PortCommand()
{
}

void myftp::PortCommand::execute(Client &client, Server &server, int i, std::string argument) {
    if (client.get_mode_data() != DATA_PORT) {
        write(client.get_fd(), "500 Passive is already running.\r\n", 33);
        return;
    }

    socklen_t data_len = sizeof(server._server_address_control);
    getsockname(client.get_fd(), (struct sockaddr*) &server._server_address_control, &data_len);
    std::string ip;
    int port;

    std::regex const e{"([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+)"};
    std::smatch m;
    
    if (std::regex_search(argument, m, e)) {
        ip = m[1].str() + "." + m[2].str() + "." + m[3].str() + "." + m[4].str();
        port = std::stoi(m[5].str()) * 256 + std::stoi(m[6].str());
        client.set_port_data(ip, std::to_string(port));
        write(client.get_fd(), "200 Command okay.\r\n", 19);
    } else {
        write(client.get_fd(), "501 Syntax error in parameters or arguments.\r\n", 47);
    }
};

bool myftp::PortCommand::need_login() const {
    return true;
};