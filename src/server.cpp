/*
** EPITECH PROJECT, 2024
** my_ftp
** File description:
** my_ftp
*/

#include "../include/Accounts.hpp"
#include "../include/Client.hpp"
#include "../include/Server.hpp"
#include <signal.h>
#include <filesystem>

void signal_process(int s) {
    exit(0);
}

void check_startup(int ac, char **av) {
    if (ac != 3)
        throw std::runtime_error("Usage: ./my_ftp <port> <path>");
    if (chdir(av[2]) < 0)
        throw std::runtime_error("Error with path");
}

int main(int ac, char **av) {
    try {
        char start_path[2048];
        check_startup(ac, av);
        getcwd(start_path, 2048);

        myftp::Server server(std::atoi(av[1]), start_path);
        
        signal(SIGINT, signal_process);

        server.start_loop();

    } catch (std::runtime_error &e) {
        std::cout << e.what() << std::endl;
        return 84;
    }
}