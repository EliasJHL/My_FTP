/*
** include.h for bootstrap in /home/elias/Documents/Epitech/my_ftp/bootstrap/include
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Mon Feb 17 16:22:22 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Thu Feb 26 22:42:44 2025 Elias Josué HAJJAR LLAUQUEN
*/

#ifndef INCLUDE_H_
    #define INCLUDE_H_

    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <errno.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <poll.h>
    #include <arpa/inet.h>
    #include <string.h>
    #include <regex.h>
    #include <stdbool.h>

    enum COMMAND {
        NONE = 0,
        PASV = 1,
        QUIT = 2,
        USER = 3,
        PASS = 4,
        HELP = 5,
        CWD = 6,
    };
    
    typedef struct accounts_s {
        char *username;
        char *password;
    } accounts_t;

    typedef struct client_s {
        int fd;
        bool has_data;
        bool is_login;
        accounts_t *account_logged;
        char *username;
        enum COMMAND command;
        char *data;
    } client_t;

#endif /* !INCLUDE_H_ */
