/*
** PasvCommand.cpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include/commands
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Thu Mar 13 14:58:38 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Fri Mar 13 15:02:11 2025 Elias Josué HAJJAR LLAUQUEN
*/

#include "PasvCommand.hpp"
#include "../Client.hpp"

myftp::PasvCommand::PasvCommand()
{
}

myftp::PasvCommand::~PasvCommand()
{
}

void myftp::PasvCommand::execute(Client &client, Server &server, int i, std::string arg) {
    char pasv[1024];
    std::string ip_adress;
    
    socklen_t data_len = sizeof(server._server_address_control);
    getsockname(client.get_fd(), (struct sockaddr*) &server._server_address_control, &data_len);
    
    char ip_str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &server._server_address_control.sin_addr, ip_str, INET_ADDRSTRLEN);
    
    int port = 0;
    
    int data_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in data_addr;
    data_addr.sin_family = AF_INET;
    data_addr.sin_addr.s_addr = INADDR_ANY;
    
    bool is_available = false;
    int tries = 0;
    
    while (!is_available && tries < 20) {
        port = 50000 + (rand() % 10000);
        data_addr.sin_port = htons(port);
        
        if (bind(data_socket, (struct sockaddr*) &data_addr, sizeof(data_addr)) == 0) {
            is_available = true;
        } else {
            tries++;
        }
    }
    
    if (!is_available) {
        close(data_socket);
        write(client.get_fd(), "425 Can't open data connection.\r\n", 33);
        return;
    }
    
    int port1 = port / 256;
    int port2 = port % 256;
    
    if (listen(data_socket, 1) < 0) {
        write(client.get_fd(), "425 Can't open data connection.\r\n", 33);
        return;
    }
    
    client.set_fd_data(data_socket);
    ip_adress.assign(ip_str);
    
    std::replace(ip_adress.begin(), ip_adress.end(), '.', ',');
    sprintf(pasv, "227 Entering Passive Mode (%s,%d,%d).\r\n", ip_adress.c_str(), port1, port2);
    write(client.get_fd(), pasv, strlen(pasv));
};

bool myftp::PasvCommand::need_login() const {
    return true;
};