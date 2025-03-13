/*
** Socket.hpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Wed Mar 12 13:18:45 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Fri Mar 13 11:29:27 2025 Elias Josué HAJJAR LLAUQUEN
*/

#ifndef SOCKET_HPP_
# define SOCKET_HPP_

#include <string>

namespace myftp {

    enum DATA_TRANSFER {
        DATA_NONE = 0,
        DATA_PASV = 1,
        DATA_PORT = 2
    };

    class Socket {
        public:
            Socket(int fd) : _fd(fd), _transfer_fd(-1), _data_transfer(DATA_NONE), _port_client_ip(""), _port_client_port("")  {}
            ~Socket();
            void set_fd(int fd);
            void set_data_fd(int transfer_fd);
            void set_mode_transfer(DATA_TRANSFER data_mode);
            void set_data_port_mode(std::string ip, std::string port);
            
            int get_client_fd();
            int get_data_fd();
            DATA_TRANSFER get_data_mode();
            std::string get_ip_data_mode();
            std::string get_port_data_mode();

        private:
            int _fd;
            int _transfer_fd;
            DATA_TRANSFER _data_transfer;
            std::string _port_client_ip;
            std::string _port_client_port;
            
    };
}

#endif /* !SOCKET_HPP_ */
