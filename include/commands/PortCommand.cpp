/*
** PortCommand.cpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include/commands
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Thu Mar 13 15:02:58 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Sat Mar 14 12:08:16 2025 Elias Josué HAJJAR LLAUQUEN
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

    std::regex const e{"\\([0-9]+,[0-9]+,[0-9]+,[0-9]+,[0-9]+,[0-9]+\\)"};
    std::smatch m;
    
    if (std::regex_match(argument, m, e)) {
        ip = m[0].str() + "." + m[1].str() + "." + m[2].str() + "." + m[3].str();
        port = atoi(m[4].str().c_str()) * 256 + atoi(m[5].str().c_str());
        client.set_port_data(ip, std::to_string(port));
        write(client.get_fd(), "200 Command okay.\r\n", 19);
    } else {
        write(client.get_fd(), "501 Syntax error in parameters or arguments.\r\n", 47);
    }
};

bool myftp::PortCommand::need_login() const {
    return true;
};