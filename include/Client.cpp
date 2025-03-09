/*
** Client.cpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Thu Mar 6 23:25:45 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Mon Mar 9 01:25:18 2025 Elias Josué HAJJAR LLAUQUEN
*/

#include "Client.hpp"

myftp::Client::Client(int fd, std::string current_path) {
    _fd = fd;
    _pasv_fd = -1;
    _has_to_process = true;
    _is_login = false;
    _command = NONE;
    _account_logged = new Accounts;
    _temp_username = "";
    _home_path = "";
    _current_path = current_path;
    _data = "220 Service ready for new user.\r\n";
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

bool myftp::Client::set_command(std::string command, std::string command_three_char) {
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
    if (command_three_char == "CWD") {
        _command = CWD;
        command_exists = true;
    }
    if (command_three_char == "PWD") {
        _command = PWD;
        command_exists = true;
    }
    if (command == "RETR") {
        _command = RETR;
        command_exists = true;
    }
    if (command == "NOOP") {
        _command = NOOP;
        command_exists = true;
    }
    if (command == "CDUP") {
        _command = CDUP;
        command_exists = true;
    }
    if (command == "DELE") {
        _command = DELE;
        command_exists = true;
    }

    if (!command_exists) {
        write(_fd, "500 Unknown commano.\r\n", 22);
        return false;
    }

    bool no_need_login = _command == USER || _command == PASS || 
                         _command == HELP || _command == QUIT ||
                         _command == NOOP;

    if (!_is_login && !no_need_login) {
        write(_fd, "530 Please login with USER and PASS.\r\n", 38);
        return false;
    }
    _has_to_process = true;
    return true;
}

bool myftp::Client::check_if_login() {
    if (!_is_login) {
        write(_fd, "530 Please login with USER and PASS.\r\n", 38);
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

void myftp::Client::process_command(std::vector<myftp::Accounts> accounts, struct sockaddr_in server_address_control, std::vector<struct pollfd> &poll_fds, std::vector<myftp::Client> &clients, int i) {
    if (_command == HELP) {
        write(_fd, "214 Help message.\r\n", 20);
    }
    if (_command == USER) {
        _temp_username = _data;
        write(_fd, "331 User name okay, need password.\r\n", 37);
    }
    if (_command == PASS) {
        if (_temp_username == "" || _temp_username.empty()) {
            write(_fd, "332 Need account for login.\r\n", 30);
        } else if (_temp_username == "Anonymous" && _data == " ") {
            _is_login = true;
            _account_logged->add_account("Anonymous", " ");
            write(_fd, "230 User logged in, proceed.\r\n", 31);
        } else if (check_logins(accounts, (char*)_temp_username.c_str(), (char*)_data.c_str())) {
            _is_login = true;
            _account_logged->add_account(_temp_username, _data);
            write(_fd, "230 User logged in, proceed.\r\n", 31);
        } else {
            write(_fd, "530 Login incorrect.\r\n", 22);
        }
    }
    if (_command == QUIT) {
        write(_fd, "221 Goodbye.\r\n", 14);
        close(poll_fds[i].fd);
        poll_fds.erase(poll_fds.begin() + i);
        clients.erase(clients.begin() + i);
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
            write(_fd, "425 Can't open data connection.\r\n", 33);
            return;
        }
        
        int port1 = port / 256;
        int port2 = port % 256;
        
        if (listen(data_socket, 1) < 0) {
            write(_fd, "425 Can't open data connection.\r\n", 33);
            return;
        }
        
        _pasv_fd = data_socket;

        ip_adress.assign(ip_str);
        
        std::replace(ip_adress.begin(), ip_adress.end(), '.', ',');
        sprintf(pasv, "227 Entering Passive Mode (%s,%d,%d).\r\n", ip_adress.c_str(), port1, port2);
        write(_fd, pasv, strlen(pasv));
    }
    if (_command == RETR) {

        if (_pasv_fd == -1) {
            write(_fd, "425 Can't open data connection.\r\n", 33);
            return;
        }

        std::cout << "Retrieving file " << _data << std::endl;
        std::ifstream dataFile;
        dataFile.open(_data, std::ios::in);
        if (dataFile.is_open()) {
            write(_fd, "150 File status okay; about to open data connection.\r\n", 54);
            int data_fd = accept(_pasv_fd, NULL, NULL);
            std::string line;
            while (std::getline(dataFile, line)) {
                write(data_fd, line.c_str(), line.size());
                write(data_fd, "\n", 1);
            }
            dataFile.close();
            write(_fd, "226 Closing data connection.\r\n", 31);
            close(data_fd);
        } else {
            write(_fd, "550 File not found.\r\n", 21);
        }
    }
    if (_command == NOOP) {
        write(_fd, "200 Command okay.\r\n", 19);
    }
    if (_command == PWD) {
        std::string pwd;
        pwd = "257 " + _current_path + " created.\r\n";
        write(_fd, pwd.c_str(), pwd.size());
    }
    if (_command == CWD) {
        char new_path[2048];
        std::string temp_path = _current_path + "/" + _data;

        if (chdir(temp_path.c_str()) == 0) {
            getcwd(new_path, 2048);
            _current_path = new_path;
            write(_fd, "250 Requested file action okay, completed.\r\n", 44);
        } else {
            write(_fd, "550 Requested action not taken.\r\n", 34);
        }
    }
    if (_command == CDUP) {
        char new_path[2048];
        if (chdir("..") == 0) {
            getcwd(new_path, 2048);
            _current_path = new_path;
            write(_fd, "250 Requested file action okay, completed.\r\n", 44);
        } else {
            write(_fd, "550 Requested action not taken.\r\n", 34);
        }
    }
    if (_command == DELE) {
        if (remove(_data.c_str()) == 0) {
            write(_fd, "250 Requested file action okay, completed.\r\n", 44);
        } else {
            write(_fd, "550 Requested action not taken.\r\n", 34);
        }
    }
    if (_command == NONE) {
        write(_fd, _data.c_str(), _data.size());
    }
    _has_to_process = false;
    _command = NONE;
}