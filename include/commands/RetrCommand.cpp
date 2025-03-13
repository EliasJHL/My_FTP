/*
** RetrCommand.cpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include/commands
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Thu Mar 13 15:30:34 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Fri Mar 13 15:33:38 2025 Elias Josué HAJJAR LLAUQUEN
*/

#include "RetrCommand.hpp"
#include "../Client.hpp"

myftp::RetrCommand::RetrCommand()
{
}

myftp::RetrCommand::~RetrCommand()
{
}

void myftp::RetrCommand::execute(Client &client, Server &server, int i, std::string arg) {
    if (client.get_mode_data() == DATA_PASV) {
        if (client.get_fd_data() == -1) {
            write(client.get_fd(), "425 Can't open data connection.\r\n", 33);
            return;
        }
    
        std::cout << "Retrieving file " << arg << std::endl;
        std::ifstream dataFile;
        dataFile.open(arg, std::ios::in);
        if (dataFile.is_open()) {
            write(client.get_fd(), "150 File status okay; about to open data connection.\r\n", 54);
            int data_fd = accept(client.get_fd_data(), NULL, NULL);
            std::string line;
            while (std::getline(dataFile, line)) {
                write(data_fd, line.c_str(), line.size());
                write(data_fd, "\n", 1);
            }
            dataFile.close();
            write(client.get_fd(), "226 Closing data connection.\r\n", 31);
            close(data_fd);
        } else {
            write(client.get_fd(), "550 File not found.\r\n", 21);
        }
    } else if (client.get_mode_data() == DATA_PORT) {
        if (client.get_ip() == "" || client.get_port() == "") {
            write(client.get_fd(), "425 Can't open data connection.\r\n", 33);
            return;
        }
        std::cout << "Retrieving file " << arg << std::endl;
        std::ifstream dataFile;
        dataFile.open(arg, std::ios::in);
        if (dataFile.is_open()) {
            int sock;
            struct sockaddr_in addr;
            std::string line;
            
            write(client.get_fd(), "150 File status okay; about to open data connection.\r\n", 54);
            
            sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            
            addr.sin_family = AF_INET;
            addr.sin_port = htons(atoi(client.get_port().c_str()));
            addr.sin_addr.s_addr = inet_addr(client.get_ip().c_str());
            if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
                write(client.get_fd(), "425 Can't open data connection.\r\n", 33);
                return;
            }
            while(std::getline(dataFile, line)) {
                
                write(sock, line.c_str(), line.size());
                write(sock, "\n", 1);
            }
            dataFile.close();
            write(client.get_fd(), "226 Closing data connection.\r\n", 31);
            close(sock);
        } else {
            write(client.get_fd(), "550 File not found.\r\n", 21);
        }
    } else {
        write(client.get_fd(), "425 Can't open data connection.\r\n", 33);
    }
};

bool myftp::RetrCommand::need_login() const {
    return true;
};
