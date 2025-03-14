/*
** Client.cpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Thu Mar 6 23:25:45 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Sat Mar 14 11:40:23 2025 Elias Josué HAJJAR LLAUQUEN
*/

#include "Client.hpp"
#include "Server.hpp"

myftp::Client::Client(int fd, std::string start_path) {
    _socket_data = new Socket(fd);
    _has_to_process = true;
    _is_login = false;
    _transfer_pid = -1;
    _command = myftp::COMMAND::NONE;
    _account_logged = new Accounts;
    _temp_username = "";
    _home_path = start_path;
    _current_path = start_path;
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
    _command = myftp::COMMAND::UNDEFINED;
    if (command == "USER")
        _command = USER;
    if (command == "PASS")
        _command = PASS;
    if (command == "HELP")
        _command = HELP;
    if (command == "QUIT")
        _command = QUIT;
    if (command == "PASV") {
        _command = myftp::COMMAND::PASV;
        if (_socket_data->get_data_mode() == DATA_NONE)
            set_mode_data(DATA_PASV);
    }
    if (command_three_char == "CWD")
        _command = CWD;
    if (command_three_char == "PWD")
        _command = PWD;
    if (command == "RETR")
        _command = RETR;
    if (command == "NOOP")
        _command = NOOP;
    if (command == "CDUP")
        _command = CDUP;
    if (command == "DELE")
        _command = DELE;
    if (command == "PORT") {
        _command = myftp::COMMAND::PORT;
        if (_socket_data->get_data_mode() == DATA_NONE)
            set_mode_data(DATA_PORT);
    }
    if (command == "LIST")
        _command = LIST;

    _has_to_process = true;
    return true;
}

void myftp::Client::login(std::string username, std::string password) {
    _is_login = true;
    _account_logged->add_account(_temp_username, _data);
}

void myftp::Client::set_home_path(std::string path) {
    _home_path = path;
}

std::string myftp::Client::get_home_path() {
    return _home_path;
}

void myftp::Client::set_temp_username(std::string username) {
    _temp_username = username;
}

std::string myftp::Client::get_temp_username() {
    return _temp_username;
}

void myftp::Client::set_path(std::string path) {
    _current_path = path;
}

std::string myftp::Client::get_path() {
    return _current_path;
}

void myftp::Client::process_command(myftp::Server &server, int i) {
    myftp::Factory CommandFactory;

    myftp::ICommands *command = CommandFactory.getCommand(_command);

    if (!command) {
        write(get_fd(), "500 Unknown command.\r\n", 22);
        return;
    }

    if (command->need_login() && !_is_login) {
        write(get_fd(), "530 Please login with USER and PASS.\r\n", 38);
        return;
    }

    command->execute(*this, server, i, _data);

    _has_to_process = false;
    _command = NONE;
}