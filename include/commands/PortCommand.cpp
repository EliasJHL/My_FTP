/*
** PortCommand.cpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include/commands
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Thu Mar 13 15:02:58 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Fri Mar 13 20:50:34 2025 Elias Josué HAJJAR LLAUQUEN
*/

#include "PortCommand.hpp"
#include "../Client.hpp"

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
    std::vector<std::string> args;
    size_t pos = 0;
    std::string arg;
    if (!argument.empty()) {
        argument.erase(0, 1);
        argument.pop_back();
    } else {
        write(client.get_fd(), "500 Syntax error, command unrecognized.\r\n", 41);
        return;
    }
        
    while ((pos = argument.find(',')) != std::string::npos) {
        arg = argument.substr(0, pos);
        args.push_back(arg);
        argument.erase(0, pos + 1);
    }
    args.push_back(argument);
    std::cout << args.size() << std::endl;

    for (int i = 0; i < 4; i++) {
        ip += args[i];
        if (i < 3) {
            ip += ".";
        }
    }
    port = atoi(args[4].c_str()) * 256 + atoi(args[5].c_str());

    if (args.size() != 6) {
        write(client.get_fd(), "501 Syntax error in parameters or arguments.\r\n", 47);
        return;
    }

    client.set_port_data(ip, std::to_string(port));

    write(client.get_fd(), "200 Command okay.\r\n", 19);
};

bool myftp::PortCommand::need_login() const {
    return false;
};