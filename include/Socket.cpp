/*
** Socket.cpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Wed Mar 12 14:14:10 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Fri Mar 13 12:11:04 2025 Elias Josué HAJJAR LLAUQUEN
*/

#include "Socket.hpp"
#include <iostream>

myftp::Socket::~Socket()
{
}

void myftp::Socket::set_fd(int fd) {
    _fd = fd;
}

void myftp::Socket::set_data_fd(int fd) {
    _transfer_fd = fd;
}

void myftp::Socket::set_mode_transfer(myftp::DATA_TRANSFER data) {
    _data_transfer = data;
}

void myftp::Socket::set_data_port_mode(std::string ip, std::string port) {
    _port_client_ip = ip;
    _port_client_port = port;
}

int myftp::Socket::get_client_fd() {
    return _fd;
}

int myftp::Socket::get_data_fd() {
    return _transfer_fd;
}

myftp::DATA_TRANSFER myftp::Socket::get_data_mode() {
    return _data_transfer;
}

std::string myftp::Socket::get_ip_data_mode() {
    return _port_client_ip;
}

std::string myftp::Socket::get_port_data_mode() {
    return _port_client_ip;
}
