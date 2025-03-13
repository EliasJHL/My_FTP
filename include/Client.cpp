/*
** Client.cpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Thu Mar 6 23:25:45 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Fri Mar 13 12:11:51 2025 Elias Josué HAJJAR LLAUQUEN
*/

#include "Client.hpp"

myftp::Client::Client(int fd, std::string current_path) {
    _socket_data = new Socket(fd);
    _has_to_process = true;
    _is_login = false;
    _command = myftp::COMMAND::NONE;
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

int myftp::Client::get_fd() {
    return _socket_data->get_client_fd();
}

int myftp::Client::get_fd_data() {
    return _socket_data->get_data_fd();
}

myftp::DATA_TRANSFER myftp::Client::get_mode_data () {
    return _socket_data->get_data_mode();
}

std::string myftp::Client::get_ip() {
    return _socket_data->get_ip_data_mode();
}

std::string myftp::Client::get_port() {
    return _socket_data->get_port_data_mode();
}

void myftp::Client::set_fd(int fd) {
    _socket_data->set_fd(fd);
}

void myftp::Client::set_fd_data(int fd) {
    _socket_data->set_data_fd(fd);
}

void myftp::Client::set_mode_data(DATA_TRANSFER data) {
    _socket_data->set_mode_transfer(data);
}

void myftp::Client::set_port_data(std::string ip, std::string port) {
    _socket_data->set_data_port_mode(ip, port);
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
        _command = myftp::COMMAND::PASV;
        set_mode_data(DATA_PASV);
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
    if (command == "PORT") {
        _command = myftp::COMMAND::PORT;
        set_mode_data(DATA_PORT);
        command_exists = true;
    }
    if (command == "LIST") {
        _command = LIST;
        command_exists = true;
    }

    if (!command_exists) {
        write(get_fd(), "500 Unknown command.\r\n", 22);
        return false;
    }

    bool no_need_login = _command == USER || _command == PASS || 
                         _command == HELP || _command == QUIT ||
                         _command == NOOP;

    if (!_is_login && !no_need_login) {
        write(get_fd(), "530 Please login with USER and PASS.\r\n", 38);
        return false;
    }
    _has_to_process = true;
    return true;
}

bool myftp::Client::check_if_login() {
    if (!_is_login) {
        write(get_fd(), "530 Please login with USER and PASS.\r\n", 38);
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
        write(get_fd(), "214 Help message.\r\n", 19);
    }
    if (_command == USER) {
        _temp_username = _data;
        write(get_fd(), "331 User name okay, need password.\r\n", 36);
    }
    if (_command == PASS) {
        if (_temp_username == "" || _temp_username.empty()) {
            write(get_fd(), "332 Need account for login.\r\n", 29);
        } else if (check_logins(accounts, (char*)_temp_username.c_str(), (char*)_data.c_str())) {
            _is_login = true;
            _account_logged->add_account(_temp_username, _data);
            write(get_fd(), "230 User logged in, proceed.\r\n", 30);
        } else {
            write(get_fd(), "530 Login incorrect.\r\n", 22);
            _temp_username.clear();
        }
    }
    if (_command == QUIT) {
        write(get_fd(), "221 Goodbye.\r\n", 14);
        close(poll_fds[i].fd);
        poll_fds.erase(poll_fds.begin() + i);
        clients.erase(clients.begin() + i);
        close(get_fd());
        if (get_fd_data() != -1) {
            close(get_fd_data());
        }
    }
    if (_command == PASV) {
        char pasv[1024];
        std::string ip_adress;
        
        socklen_t data_len = sizeof(server_address_control);
        getsockname(get_fd(), (struct sockaddr*) &server_address_control, &data_len);
        
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
            write(get_fd(), "425 Can't open data connection.\r\n", 33);
            return;
        }
        
        int port1 = port / 256;
        int port2 = port % 256;
        
        if (listen(data_socket, 1) < 0) {
            write(get_fd(), "425 Can't open data connection.\r\n", 33);
            return;
        }
        
        set_fd_data(data_socket);

        ip_adress.assign(ip_str);
        
        std::replace(ip_adress.begin(), ip_adress.end(), '.', ',');
        sprintf(pasv, "227 Entering Passive Mode (%s,%d,%d).\r\n", ip_adress.c_str(), port1, port2);
        write(get_fd(), pasv, strlen(pasv));
    }
    if (_command == RETR) {
        if (get_mode_data() == DATA_PASV) {
            if (get_fd_data() == -1) {
                write(get_fd(), "425 Can't open data connection.\r\n", 33);
                return;
            }
        
            std::cout << "Retrieving file " << _data << std::endl;
            std::ifstream dataFile;
            dataFile.open(_data, std::ios::in);
            if (dataFile.is_open()) {
                write(get_fd(), "150 File status okay; about to open data connection.\r\n", 54);
                int data_fd = accept(get_fd_data(), NULL, NULL);
                std::string line;
                while (std::getline(dataFile, line)) {
                    write(data_fd, line.c_str(), line.size());
                    write(data_fd, "\n", 1);
                }
                dataFile.close();
                write(get_fd(), "226 Closing data connection.\r\n", 31);
                close(data_fd);
            } else {
                write(get_fd(), "550 File not found.\r\n", 21);
            }
        } else if (get_mode_data() == DATA_PORT) {
            if (get_ip() == "" || get_port() == "") {
                write(get_fd(), "425 Can't open data connection.\r\n", 33);
                return;
            }
            std::cout << "Retrieving file " << _data << std::endl;
            std::ifstream dataFile;
            dataFile.open(_data, std::ios::in);
            if (dataFile.is_open()) {
                int sock;
                struct sockaddr_in addr;
                std::string line;
                
                write(get_fd(), "150 File status okay; about to open data connection.\r\n", 54);
                
                sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
                
                addr.sin_family = AF_INET;
                addr.sin_port = htons(atoi(get_port().c_str()));
                addr.sin_addr.s_addr = inet_addr(get_ip().c_str());

                if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
                    write(get_fd(), "425 Can't open data connection.\r\n", 33);
                    return ;
                }
                while(std::getline(dataFile, line)) {
                    
                    write(sock, line.c_str(), line.size());
                    write(sock, "\n", 1);
                }
                dataFile.close();
                write(get_fd(), "226 Closing data connection.\r\n", 31);
                close(sock);
            } else {
                write(get_fd(), "550 File not found.\r\n", 21);
            }
        } else {
            write(get_fd(), "425 Can't open data connection.\r\n", 33);
        }
    }
    if (_command == NOOP) {
        write(get_fd(), "200 Command okay.\r\n", 19);
    }
    if (_command == PWD) {
        std::string pwd;
        pwd = "257 " + _current_path + " created.\r\n";
        write(get_fd(), pwd.c_str(), pwd.size());
    }
    if (_command == CWD) {
        char new_path[2048];
        std::string temp_path = _current_path + "/" + _data;

        if (chdir(temp_path.c_str()) == 0) {
            getcwd(new_path, 2048);
            _current_path = new_path;
            write(get_fd(), "250 Requested file action okay, completed.\r\n", 44);
        } else {
            write(get_fd(), "550 Requested action not taken.\r\n", 34);
        }
    }
    if (_command == CDUP) {
        char new_path[2048];
        if (chdir("..") == 0) {
            getcwd(new_path, 2048);
            _current_path = new_path;
            write(get_fd(), "250 Requested file action okay, completed.\r\n", 44);
        } else {
            write(get_fd(), "550 Requested action not taken.\r\n", 34);
        }
    }
    if (_command == DELE) {
        if (remove(_data.c_str()) == 0) {
            write(get_fd(), "250 Requested file action okay, completed.\r\n", 44);
        } else {
            write(get_fd(), "550 Requested action not taken.\r\n", 34);
        }
    }
    if (_command == PORT) {
        if (get_mode_data() != DATA_PORT) {
            write(get_fd(), "500 Passive is already running.\r\n", 33);
            return;
        }

        socklen_t data_len = sizeof(server_address_control);
        getsockname(get_fd(), (struct sockaddr*) &server_address_control, &data_len);
        std::string ip;
        int port;
        std::vector<std::string> args;
        size_t pos = 0;
        std::string arg;
        if (!_data.empty()) {
            _data.erase(0, 1);
            _data.pop_back();
        } else {
            write(get_fd(), "500 Syntax error, command unrecognized.\r\n", 41);
            return;
        }

        std::cout << _data << std::endl;
        
        while ((pos = _data.find(',')) != std::string::npos) {
            arg = _data.substr(0, pos);
            args.push_back(arg);
            _data.erase(0, pos + 1);
        }
        args.push_back(_data);
        std::cout << args.size() << std::endl;

        for (int i = 0; i < 4; i++) {
            ip += args[i];
            if (i < 3) {
                ip += ".";
            }
        }
        port = atoi(args[4].c_str()) * 256 + atoi(args[5].c_str());

        if (args.size() != 6) {
            write(get_fd(), "501 Syntax error in parameters or arguments.\r\n", 47);
            return;
        }

        set_port_data(ip, std::to_string(port));

        write(get_fd(), "200 Command okay.\r\n", 19);
    }
    if (_command == LIST) {
        if (get_mode_data() == DATA_NONE) {
            write(get_fd(), "425 Can't open data connection.\r\n", 33);
            return;
        }
        char buffer[128];
        std::string result = "";
        FILE* pipe = popen("ls -l", "r");
        if (!pipe) {
            write(get_fd(), "501 Syntax error in parameters or arguments.\r\n", 47);
            return;
        }
        while (fgets(buffer, sizeof buffer, pipe) != NULL) 
            result += buffer;
        pclose(pipe);
        if (get_mode_data() == DATA_PASV) {
            int data_fd = accept(get_fd_data(), NULL, NULL);
            write(data_fd, result.c_str(), result.size());
            close(data_fd);
        } else if (get_mode_data() == DATA_PORT) {
            int sock;
            struct sockaddr_in addr;
            sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            addr.sin_family = AF_INET;
            addr.sin_port = htons(atoi(get_port().c_str()));
            addr.sin_addr.s_addr = inet_addr(get_ip().c_str());
            if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
                write(get_fd(), "425 Can't open data connection.\r\n", 33);
                return;
            }
            write(sock, result.c_str(), result.size());
            close(sock);
        }
        write(get_fd(), "226 Closing data connection.\r\n", 31);
        set_mode_data(DATA_NONE);
    }
    if (_command == NONE) {
        write(get_fd(), _data.c_str(), _data.size());
    }
    _has_to_process = false;
    _command = NONE;
}