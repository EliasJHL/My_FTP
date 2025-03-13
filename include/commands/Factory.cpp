/*
** Factory.cpp for B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen in /home/elias/Documents/Epitech/my_ftp/B-NWP-400-MPL-4-1-myftp-elias-josue.hajjar-llauquen/include/commands
**
** Made by Elias Josué HAJJAR LLAUQUEN
** Login   <elias-josue.hajjar-llauquen@epitech.eu>
**
** Started on  Thu Mar 13 13:54:14 2025 Elias Josué HAJJAR LLAUQUEN
** Last update Fri Mar 13 15:40:43 2025 Elias Josué HAJJAR LLAUQUEN
*/

#include "Factory.hpp"

myftp::Factory::Factory() {
    commands[COMMAND::NOOP] = new NoopCommand();
    commands[COMMAND::HELP] = new HelpCommand();
    commands[COMMAND::USER] = new UserCommand();
    commands[COMMAND::PASS] = new PassCommand();
    commands[COMMAND::RETR] = new RetrCommand();
    commands[COMMAND::LIST] = new ListCommand();
    commands[COMMAND::NONE] = new NoneCommand();
    commands[COMMAND::QUIT] = new QuitCommand();
    commands[COMMAND::PWD] = new PwdCommand();
    commands[COMMAND::CWD] = new CwdCommand();
    commands[COMMAND::CDUP] = new CdupCommand();
    commands[COMMAND::PASV] = new PasvCommand();
    commands[COMMAND::PORT] = new PortCommand();
    //commands[COMMAND::STOR] = new StorCommand();
    commands[COMMAND::DELE] = new DeleCommand();
}

myftp::Factory::~Factory() {
    for (auto& pair : commands) {
        delete pair.second;
    }
    commands.clear();
}

myftp::ICommands* myftp::Factory::getCommand(COMMAND cmd) {
    auto it = commands.find(cmd);
    if (it != commands.end()) {
        return it->second;
    }
    return nullptr;
}
