/*
** Client.cpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Thu Mar 6 23:25:45 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Sat Mar 7 11:03:26 2025 Elias Josué HAJJAR LLAUQUEN
*/

#include "Client.hpp"

myftp::Client::Client(int fd) {
    _fd = fd;
    _pasv_fd = -1;
    _has_to_process = true;
    _is_login = false;
    _command = NONE;
    _account_logged = new Accounts;
    _temp_username = "";
    _data = "220 Service ready for new user.\n";
};

myftp::Client::~Client() {
}

void myftp::Client::set_data(std::string data) {
    _data = data;
    _has_to_process = true;
}

bool myftp::Client::has_to_process() {
    return _has_to_process;
}

bool myftp::Client::set_command(std::string command) {
    bool command_exists = false;

    if (command == "USER") {
        _command = USER;
        command_exists = true;
    }
    if (command == "PASS") {
        _command = PASS;
        command_exists = true;
    }
    if (command == "HELP") {
        _command = HELP;
        command_exists = true;
    }
    if (command == "QUIT") {
        _command = QUIT;
        command_exists = true;
    }
    if (command == "PASV") {
        _command = PASV;
        command_exists = true;
    }
    if (command == "CWD") {
        _command = CWD;
        command_exists = true;
    }
    if (command == "RETR") {
        _command = RETR;
        command_exists = true;
    }

    if (!command_exists) {
        write(_fd, "500 Unknown command.\n", 21);
        return false;
    }

    const bool no_need_login = _command == USER || _command == PASS || 
                               _command == HELP || _command == QUIT;

    if (!_is_login && !no_need_login) {
        write(_fd, "530 Please login with USER and PASS.\n", 37);
        return false;
    }
    _has_to_process = true;
    return true;
}

bool myftp::Client::check_if_login() {
    if (!_is_login) {
        write(_fd, "530 Please login with USER and PASS.\n", 37);
        return false;
    }
    return true;
}

bool check_logins(std::vector<myftp::Accounts> accounts, char *username, char *password) {
    for (int i = 0; i < accounts.size(); i++) {
        if (accounts[i].check_login(username, password)) {
            return true;
        }
    }
    return false;
}

void myftp::Client::process_command(std::vector<myftp::Accounts> accounts, struct sockaddr_in server_address_control) {
    if (_command == HELP) {
        write(_fd, "214 Help message.\n", 19);
    }
    if (_command == USER) {
        _temp_username = _data;
        write(_fd, "331 User name okay, need password.\n", 36);
    }
    if (_command == PASS) {
        if (_temp_username == "" || _temp_username.empty()) {
            write(_fd, "332 Need account for login.\n", 29);
        } else if (_temp_username == "Anonymous" && _data == "") {
            _is_login = true;
            _account_logged->add_account("Anonymous", "");
            write(_fd, "230 User logged in, proceed.\n", 30);
        } else if (check_logins(accounts, (char*)_temp_username.c_str(), (char*)_data.c_str())) {
            _is_login = true;
            _account_logged->add_account(_temp_username, _data);
            write(_fd, "230 User logged in, proceed.\n", 30);
        } else {
            write(_fd, "530 Login incorrect.\n", 21);
        }
    }
    if (_command == QUIT) {
        write(_fd, "221 Goodbye.\n", 13);
        close(_fd);
        if (_pasv_fd != -1) {
            close(_pasv_fd);
        }
    }
    if (_command == PASV) {
        char pasv[1024];
        std::string ip_adress;
        
        socklen_t data_len = sizeof(server_address_control);
        getsockname(_fd, (struct sockaddr*) &server_address_control, &data_len);
        
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
        
        _pasv_fd = data_socket;

        ip_adress.assign(ip_str);
        
        std::replace(ip_adress.begin(), ip_adress.end(), '.', ',');
        sprintf(pasv, "227 Entering Passive Mode (%s,%d,%d).\n", ip_adress.c_str(), port1, port2);
        write(_fd, pasv, strlen(pasv));
    }
    if (_command == RETR) {
        std::cout << "Retrieving file " << _data << std::endl;
        std::ifstream dataFile;
        dataFile.open(_data, std::ios::in);
        if (dataFile.is_open()) {
            write(_fd, "150 File status okay; about to open data connection.\n", 53);
            int data_fd = accept(_pasv_fd, NULL, NULL);
            std::string line;
            while (std::getline(dataFile, line)) {
                write(data_fd, line.c_str(), line.size());
            }
            dataFile.close();
            write(_fd, "226 Closing data connection.\n", 30);
            close(data_fd);
        } else {
            write(_fd, "550 File not found.\n", 20);
        }
    }
    if (_command == NONE) {
        write(_fd, _data.c_str(), _data.size());
    }
    _has_to_process = false;
    _command = NONE;
}