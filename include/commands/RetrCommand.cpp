/*
** RetrCommand.cpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include/commands
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Thu Mar 13 15:30:34 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Sun Mar 15 19:43:22 2025 Elias Josué HAJJAR LLAUQUEN
*/

#include "RetrCommand.hpp"
#include "../Client.hpp"
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

myftp::RetrCommand::RetrCommand()
{
}

myftp::RetrCommand::~RetrCommand()
{
}

bool check_file_in_home(myftp::Client &client, std::string arg) {
    char new_path[2048];
    std::string temp_path;

    if (arg == "/") {
        temp_path = client.get_home_path();
    } else if (arg[0] == '/') {
        temp_path = arg;
    } else {
        temp_path = client.get_path() + "/" + arg;
    }

    if (realpath(temp_path.c_str(), new_path) == nullptr) {
        write(client.get_fd(), "550 Path is not valid.\r\n", 24);
        return false;
    }
    std::string test_path(new_path);
    if (test_path.find(client.get_home_path()) == std::string::npos) {
        write(client.get_fd(), "550 Requested action not taken.\r\n", 33);
        return false;
    }
    return true;
}

void myftp::RetrCommand::execute(Client &client, Server &server, int i, std::string arg) {
    if (client._transfer_pid > 0) {
        int status;
        waitpid(client._transfer_pid, &status, WNOHANG);
        client._transfer_pid = -1;
    }
    if (client._transfer_pid != -1) {
        kill(client._transfer_pid, SIGKILL);
        client._transfer_pid = -1;
    }

    if (!check_file_in_home(client, arg))
        return;
    
    pid_t pid = fork();

    if (pid == -1) {
        write(client.get_fd(), "550 Error sending files failed.\r\n", 33);
        return;
    }
    if (pid > 0) {
        client._transfer_pid = pid;
        return;
    }
    if (client.get_mode_data() == DATA_PASV) {
        if (client.get_fd_data() == -1) {
            write(client.get_fd(), "425 Can't open data connection.\r\n", 33);
            exit(EXIT_SUCCESS);
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
            write(client.get_fd(), "226 Closing data connection.\r\n", 30);
            close(data_fd);
            exit(EXIT_SUCCESS);
        } else {
            write(client.get_fd(), "550 File not found.\r\n", 21);
            exit(EXIT_SUCCESS);
        }
    } else if (client.get_mode_data() == DATA_PORT) {
        if (client.get_ip() == "" || client.get_port() == "") {
            write(client.get_fd(), "425 Can't open data connection.\r\n", 33);
            exit(EXIT_SUCCESS);
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
                exit(EXIT_SUCCESS);
            }
            while(std::getline(dataFile, line)) {
                write(sock, line.c_str(), line.size());
                write(sock, "\n", 1);
            }
            dataFile.close();
            write(client.get_fd(), "226 Closing data connection.\r\n", 30);
            close(sock);
            exit(EXIT_SUCCESS);
        } else {
            write(client.get_fd(), "550 File not found.\r\n", 21);
            exit(EXIT_SUCCESS);
        }
    } else {
        write(client.get_fd(), "425 Can't open data connection.\r\n", 33);
        exit(EXIT_SUCCESS);
    }
};

bool myftp::RetrCommand::need_login() const {
    return true;
};
