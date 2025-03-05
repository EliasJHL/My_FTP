/*
** EPITECH PROJECT, 2024
** my_ftp
** File description:
** my_ftp
*/

#include "include/include.h"
#include <poll.h>

char *ip_pasv(char *str) {
    if (str == NULL) {
        return NULL;
    }
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '.') {
            str[i] = ',';
        }
    }
    return str;
}

bool command_exists(char *c) {
    if (strncmp(c, "USER", 4) == 0 || strncmp(c, "PASS", 4) == 0 ||
        strncmp("PASV", c, 4) == 0 || strncmp("quit", c, 4) == 0 ||
        strncmp("HELP", c, 4) == 0 || strncmp("CWD", c, 3) == 0 ||
        strncmp("RETR", c, 4) == 0) {
        return true;
    }
    return false;
}

bool check_logins(accounts_t *accounts, char *username, char *password) {
    for (int i = 0; accounts[i].username != NULL; i++) {
        if (strcmp(accounts[i].username, username) == 0 &&
            strcmp(accounts[i].password, password) == 0) {
            return true;
        }
    }
    return false;
}

// void pollin_accept_connection(int server_socket, struct pollfd *poll_fds, client_t *clients, int *proc_count, int *start_size) {
//     int client_socket;
//     struct sockaddr_in client_addr;
//     socklen_t client_len = sizeof(client_addr);
//     client_socket = accept(server_socket, (struct sockaddr*) &client_addr, &client_len);
//     if (client_socket < 0) {
//         perror("Error with accept");
//         exit(EXIT_FAILURE);
//     }

//     if (*proc_count >= start_size) {
//         start_size += 1;
//         struct pollfd *new_poll_fds = realloc(poll_fds, sizeof(struct pollfd) * start_size);
//         client_t *new_clients = realloc(clients, sizeof(client_t) * start_size);
        
//         poll_fds = new_poll_fds;
//         clients = new_clients;
//     }
    
//     poll_fds[*proc_count].fd = client_socket;
//     poll_fds[*proc_count].events = POLLIN;

//     clients[*proc_count].fd = client_socket;
//     clients[*proc_count].has_data = true;
//     clients[*proc_count].is_login = false;
//     clients[*proc_count].command = NONE;
//     clients[*proc_count].account_logged = NULL;
//     clients[*proc_count].username = NULL;
//     clients[*proc_count].data = strdup("220 Service ready for new user.\n");
//     poll_fds[*proc_count].events |= POLLOUT;
//     (*proc_count)++;

//     printf("Connection from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

// }

accounts_t *start_accounts() {
    accounts_t *accounts = malloc(sizeof(accounts_t) * 2);
    accounts[0].username = "Anonymous";
    accounts[0].password = "";
    accounts[1].username = NULL;
    accounts[1].password = NULL;
    return accounts;
}

int main(int ac, char **av) {
    int server_socket, client_socket;
    int start_size = 2;
    struct sockaddr_in server_address_control;
    struct pollfd *poll_fds = malloc(sizeof(struct pollfd) * start_size);
    struct sockaddr_in client_addr;
    client_t *clients = malloc(sizeof(client_t) * start_size);
    accounts_t *accounts = start_accounts();
    int proc_count = 1;

    if (ac != 3) {
        printf("Usage: ./my_ftp <port> <path>\n");
        exit(EXIT_FAILURE);
    }

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket not valid\n");
        exit(EXIT_FAILURE);
    }

    server_address_control.sin_family = AF_INET;
    server_address_control.sin_port = htons(atoi(av[1]));
    server_address_control.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr*) &server_address_control, sizeof(server_address_control)) < 0) {
        perror("Error in socket");
        exit(EXIT_FAILURE);
    }
    
    if (listen(server_socket, 5) < 0) {
        perror("Error with listen");
        exit(EXIT_FAILURE);
    }

    poll_fds[0].fd = server_socket;
    poll_fds[0].events = POLLIN;

    while (1) {
        int poll_count = poll(poll_fds, proc_count, 10);

        if (poll_fds[0].revents & POLLIN) {
            socklen_t client_len = sizeof(client_addr);
            client_socket = accept(server_socket, (struct sockaddr*) &client_addr, &client_len);

            if (proc_count >= start_size) {
                start_size += 1;
                struct pollfd *new_poll_fds = realloc(poll_fds, sizeof(struct pollfd) * start_size);
                client_t *new_clients = realloc(clients, sizeof(client_t) * start_size);

                poll_fds = new_poll_fds;
                clients = new_clients;
            }
            
            poll_fds[proc_count].fd = client_socket;
            poll_fds[proc_count].events = POLLIN;

            clients[proc_count].fd = client_socket;
            clients[proc_count].has_data = true;
            clients[proc_count].is_login = false;
            clients[proc_count].command = NONE;
            clients[proc_count].account_logged = malloc(sizeof(accounts_t));
            clients[proc_count].username = NULL;
            clients[proc_count].data = strdup("220 Service ready for new user.\n");
            poll_fds[proc_count].events |= POLLOUT;
            proc_count++;

            printf("Connection from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        }
        
        for (int i = 1; i < proc_count; i++) {
            if (poll_fds[i].revents & POLLIN) {
                char buffer[1024];
                int len = read(poll_fds[i].fd, buffer, 1024);
                
                if (len < 0) {
                    printf("Error reading from client\n");
                    continue;
                } else if (len == 0) {
                    close(poll_fds[i].fd);
                    poll_fds[i] = poll_fds[proc_count - 1];
                    clients[i] = clients[proc_count - 1];
                    proc_count--;
                    continue;
                }
                
                buffer[len] = '\0';
                printf("Received: %s", buffer);
                if (!command_exists(buffer)) {
                    strcpy(clients[i].data, "500 Unknown command.\n");
                    clients[i].has_data = true;
                    poll_fds[i].events |= POLLOUT;
                    continue;
                }
                if (strncmp(buffer, "USER", 4) == 0)
                    clients[i].command = USER;
                if (strncmp(buffer, "PASS", 4) == 0)
                    clients[i].command = PASS;
                    if (strncmp(buffer, "HELP", 4) == 0)
                    clients[i].command = HELP;
                if (strncmp(buffer, "QUIT", 4) == 0) {
                    clients[i].command = QUIT;
                    clients[i].has_data = true;
                    poll_fds[i].events |= POLLOUT;
                    continue;
                }
                if (!clients[i].is_login && clients[i].command != USER && clients[i].command != PASS) {
                    strcpy(clients[i].data, "530 Please login with USER and PASS.\n");
                    clients[i].has_data = true;
                    poll_fds[i].events |= POLLOUT;
                    continue;
                }
                if (strncmp(buffer, "PASV", 4) == 0)
                    clients[i].command = PASV;
                if (strncmp(buffer, "CWD", 3) == 0)
                    clients[i].command = CWD;
                if (strncmp(buffer, "RETR", 4) == 0)
                    clients[i].command = RETR;
                if (clients[i].data != NULL)
                    free(clients[i].data);
                clients[i].data = malloc(sizeof(char) * (strlen(buffer) - 4));
                if (strlen(buffer) > 5) {
                    strncpy(clients[i].data, buffer + 5, strlen(buffer) - 4);
                    clients[i].data[strlen(clients[i].data)] = '\0';
                } else {
                    clients[i].data = NULL;
                }
                //write(poll_fds[i].fd, "200 Command okay.\n", 18);
                clients[i].has_data = true;
                poll_fds[i].events |= POLLOUT;
            }
            if (poll_fds[i].revents & POLLOUT) {
                if (!clients[i].has_data) {
                    continue;
                }
                if (clients[i].command == HELP) {
                    write(poll_fds[i].fd, "214 Help message.\n", 19);
                }
                if (clients[i].command == USER) {
                    clients[i].username = malloc(sizeof(char) * strlen(clients[i].data) + 1);
                    strcpy(clients[i].username, clients[i].data);
                    write(poll_fds[i].fd, "331 User name okay, need password.\n", 36);
                }
                if (clients[i].command == PASS) {
                    if (clients[i].username == NULL) {
                        write(poll_fds[i].fd, "332 Need account for login.\n", 29);
                    } else if (strncmp(clients[i].username, "Anonymous", 9) == 0 && strlen(clients[i].data + 1) == 0) {
                        clients[i].is_login = true;
                        clients[i].account_logged->username = strdup(clients[i].username);
                        clients[i].account_logged->password = strdup("");
                        write(poll_fds[i].fd, "230 User logged in, proceed.\n", 30);
                    } else if (check_logins(accounts, clients[i].username, clients[i].data)) {
                        clients[i].is_login = true;
                        clients[i].account_logged->username = strdup(clients[i].username);
                        clients[i].account_logged->password = strdup(clients[i].data);
                        write(poll_fds[i].fd, "230 User logged in, proceed.\n", 30);
                    } else {
                        write(poll_fds[i].fd, "530 Login incorrect.\n", 21);
                    }
                }
                if (clients[i].command == PASV) {
                    char *pasv = malloc(1024);
                    
                    socklen_t addr_len = sizeof(server_address_control);
                    getsockname(poll_fds[i].fd, (struct sockaddr*) &server_address_control, &addr_len);
                    
                    char ip_str[INET_ADDRSTRLEN];
                    inet_ntop(AF_INET, &server_address_control.sin_addr, ip_str, INET_ADDRSTRLEN);

                    int port = 50000 + (rand() % 10000);
                    int port1 = port / 256;
                    int port2 = port % 256;

                    int data_socket = socket(AF_INET, SOCK_STREAM, 0);
                    struct sockaddr_in data_addr;
                    data_addr.sin_family = AF_INET;
                    data_addr.sin_port = htons(port);
                    data_addr.sin_addr.s_addr = INADDR_ANY;
                    
                    if (bind(data_socket, (struct sockaddr*) &data_addr, sizeof(data_addr)) < 0) {
                        perror("Error binding data socket");
                        exit(EXIT_FAILURE);
                    }
                    
                    if (listen(data_socket, 1) < 0) {
                        perror("Error on listen for data connection");
                        exit(EXIT_FAILURE);
                    }

                    clients[i].pasv_fd = data_socket;
                    
                    sprintf(pasv, "227 Entering Passive Mode (%s,%d,%d).\n", ip_pasv(ip_str), port1, port2);
                    write(poll_fds[i].fd, pasv, strlen(pasv));
                    free(pasv);
                }
                if (clients[i].command == QUIT) {
                    write(poll_fds[i].fd, "221 Service closing control connection.\n", 40);
                    close(poll_fds[i].fd);
                    poll_fds[i] = poll_fds[proc_count - 1];
                    clients[i] = clients[proc_count - 1];
                    proc_count--;
                } 
                if (clients[i].command == RETR) {
                    clients[i].data[strlen(clients[i].data) - 2] = '\0';
                    printf("Retrieving file: %s\n", clients[i].data);
                    FILE *file = fopen(clients[i].data, "r");
                    char *buffer = malloc(1024);
                    
                    if (file == NULL) {
                        write(poll_fds[i].fd, "550 File not found.\n", 20);
                    } else {
                        write(poll_fds[i].fd, "150 File status okay; about to open data connection.\n", 53);
                        int data_fd = accept(clients[i].pasv_fd, NULL, NULL);
                        
                        while (fgets(buffer, 1024, file) != NULL) {
                            write(data_fd, buffer, strlen(buffer));
                        }
                        write(poll_fds[i].fd, "226 Closing data connection.\n", 29);
                        fclose(file);
                    }
                    free(buffer);
                }
                if (clients[i].command == NONE) {
                    write(poll_fds[i].fd, clients[i].data, strlen(clients[i].data));
                }
                clients[i].command = NONE;
                clients[i].has_data = false;
                poll_fds[i].events &= ~POLLOUT;
            }
            
        }
    }

    close(server_socket);
    return 0;
}