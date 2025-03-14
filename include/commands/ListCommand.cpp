/*
** ListCommand.cpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include/commands
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Thu Mar 13 15:19:04 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Sat Mar 14 12:24:26 2025 Elias Josué HAJJAR LLAUQUEN
*/

#include "ListCommand.hpp"
#include "../Client.hpp"

myftp::ListCommand::ListCommand()
{
}

myftp::ListCommand::~ListCommand()
{
}

void myftp::ListCommand::execute(Client &client, Server &server, int i, std::string arg) {
    if (client._transfer_pid != -1) {
        kill(client._transfer_pid, SIGKILL);
        client._transfer_pid = -1;
    }
    
    pid_t pid = fork();

    if (pid == -1) {
        write(client.get_fd(), "550 Error sending files failed.\r\n", 33);
        return;
    }
    if (pid > 0) {
        client._transfer_pid = pid;
        return;
    }
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen("ls -l", "r");
    if (!pipe) {
        write(client.get_fd(), "501 Syntax error in parameters or arguments.\r\n", 47);
        exit(EXIT_SUCCESS);
    }
    while (fgets(buffer, sizeof buffer, pipe) != NULL) 
        result += buffer;
    pclose(pipe);
    result = result.substr(result.find("\n") + 1);
    if (client.get_mode_data() == DATA_PASV) {
        write(client.get_fd(), "150 File status okay; about to open data connection.\r\n", 54);
        int data_fd = accept(client.get_fd_data(), NULL, NULL);
        write(data_fd, result.c_str(), result.size());
        close(data_fd);
        write(client.get_fd(), "226 Closing data connection.\r\n", 31);
        exit(EXIT_SUCCESS);
    } else if (client.get_mode_data() == DATA_PORT) {
        write(client.get_fd(), "150 File status okay; about to open data connection.\r\n", 54);
        int sock;
        struct sockaddr_in addr;
        sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        addr.sin_family = AF_INET;
        addr.sin_port = htons(atoi(client.get_port().c_str()));
        addr.sin_addr.s_addr = inet_addr(client.get_ip().c_str());
        if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
            write(client.get_fd(), "425 Can't open data connection.\r\n", 33);
            exit(EXIT_SUCCESS);
        }
        write(sock, result.c_str(), result.size());
        close(sock);
        write(client.get_fd(), "226 Closing data connection.\r\n", 31);
        exit(EXIT_SUCCESS);
    } else {
        write(client.get_fd(), "425 Can't open data connection.\r\n", 33);
        exit(EXIT_SUCCESS);
    }
};

bool myftp::ListCommand::need_login() const {
    return true;
};