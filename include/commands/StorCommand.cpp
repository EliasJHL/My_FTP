/*
** StorCommand.cpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include/commands
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Fri Mar 14 12:46:44 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Sun Mar 15 01:33:56 2025 Elias Josué HAJJAR LLAUQUEN
*/

#include "StorCommand.hpp"
#include "../Client.hpp"

myftp::StorCommand::StorCommand()
{
}

myftp::StorCommand::~StorCommand()
{
}

void myftp::StorCommand::execute(Client &client, Server &server, int i, std::string arg) {
    write(client.get_fd(), "200 Command okay.\r\n", 19);
    // if (client._transfer_pid != -1) {
    //     kill(client._transfer_pid, SIGKILL);
    //     client._transfer_pid = -1;
    // }
    
    // pid_t pid = fork();

    // if (pid == -1) {
    //     write(client.get_fd(), "550 Error in file failed.\r\n", 28);
    //     return;
    // }
    // if (pid > 0) {
    //     client._transfer_pid = pid;
    //     return;
    // }
    
    // char buffer[10000];
    // size_t bytes;

    // if (client.get_mode_data() == DATA_PASV) {
    //     if (client.get_fd_data() == -1) {
    //         write(client.get_fd(), "425 Can't open data connection.\r\n", 33);
    //         exit(EXIT_SUCCESS);
    //     }
    
    //     std::cout << "Receiving file " << arg << std::endl;
    //     std::ofstream dataFile;
    //     dataFile.open(arg, std::ios::out);
    //     if (dataFile.is_open()) {
    //         write(client.get_fd(), "150 File status okay; about to open data connection.\r\n", 54);
    //         int data_fd = accept(client.get_fd_data(), NULL, NULL);
    //         if (data_fd == -1) {
    //             write(client.get_fd(), "425 Can't open data connection.\r\n", 33);
    //             exit(EXIT_SUCCESS);
    //         }
    //         while ((bytes = read(data_fd, buffer, 10000)) > 0) {
    //             dataFile.write(buffer, bytes);
    //         }
    //         dataFile.close();
    //         write(client.get_fd(), "226 Closing data connection.\r\n", 31);
    //         close(data_fd);
    //         exit(EXIT_SUCCESS);
    //     } else {
    //         write(client.get_fd(), "550 Failed to create file.\r\n", 28);
    //         exit(EXIT_SUCCESS);
    //     }
    // } else if (client.get_mode_data() == DATA_PORT) {
    //     if (client.get_ip() == "" || client.get_port() == "") {
    //         write(client.get_fd(), "425 Can't open data connection.\r\n", 33);
    //         exit(EXIT_SUCCESS);
    //     }
    //     std::cout << "Retrieving file " << arg << std::endl;
    //     std::ifstream dataFile;
    //     dataFile.open(arg, std::ios::in);
    //     if (dataFile.is_open()) {
    //         int sock;
    //         struct sockaddr_in addr;
    //         std::string line;
            
    //         write(client.get_fd(), "150 File status okay; about to open data connection.\r\n", 54);
            
    //         sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            
    //         addr.sin_family = AF_INET;
    //         addr.sin_port = htons(atoi(client.get_port().c_str()));
    //         addr.sin_addr.s_addr = inet_addr(client.get_ip().c_str());
    //         if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
    //             write(client.get_fd(), "425 Can't open data connection.\r\n", 33);
    //             exit(EXIT_SUCCESS);
    //         }
    //         while(std::getline(dataFile, line)) {
    //             write(sock, line.c_str(), line.size());
    //             write(sock, "\n", 1);
    //         }
    //         dataFile.close();
    //         write(client.get_fd(), "226 Closing data connection.\r\n", 31);
    //         close(sock);
    //         exit(EXIT_SUCCESS);
    //     } else {
    //         write(client.get_fd(), "550 File not found.\r\n", 21);
    //         exit(EXIT_SUCCESS);
    //     }
    // } else {
    //     write(client.get_fd(), "425 Can't open data connection.\r\n", 33);
    //     exit(EXIT_SUCCESS);
    // }
};

bool myftp::StorCommand::need_login() const {
    return true;
};
