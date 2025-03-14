/*
** CommandsEnum.hpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Thu Mar 13 14:02:38 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Sat Mar 14 12:56:42 2025 Elias Josué HAJJAR LLAUQUEN
*/

#ifndef COMMANDSENUM_HPP_
# define COMMANDSENUM_HPP_

namespace myftp {
    enum COMMAND {
        UNDEFINED = -1,
        NONE = 0,
        PASV = 1,
        QUIT = 2,
        USER = 3,
        PASS = 4,
        HELP = 5,
        CWD = 6,
        RETR = 7,
        NOOP = 8,
        PWD = 9,
        CDUP = 10,
        DELE = 11,
        PORT = 12,
        LIST = 13,
        STOR = 14
    };
}

#endif /* !COMMANDSENUM_HPP_ */
