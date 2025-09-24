# MyFTP

A custom FTP (File Transfer Protocol) server implemented in C++ from scratch. This project, part of the Epitech curriculum, provides a robust server capable of handling multiple clients and standard FTP commands, featuring both active and passive data transfer modes.

## Features

The server architecture is designed to be extensible and robust, handling core FTP functionalities.

- **Asynchronous I/O:** Uses `poll()` to manage multiple client connections concurrently on a single thread.
- **Command Handling:** Implements a Factory design pattern to dynamically handle various FTP commands.
- **Process-based Data Transfer:** Utilizes `fork()` for data transfer commands (`LIST`, `RETR`, `STOR`) to prevent the main server loop from blocking.
- **Data Transfer Modes:** Supports both Passive (`PASV`) and Active (`PORT`) modes for data connections.
- **User Authentication:** Includes a basic authentication system, with default support for an `Anonymous` user.

### Implemented FTP Commands
- `USER`: Specify the user for authentication.
- `PASS`: Specify the password for authentication.
- `QUIT`: Disconnect the client from the server.
- `HELP`: Display a help message.
- `NOOP`: Do nothing, but elicit a positive reply.
- `PWD`: Print working directory.
- `CWD`: Change working directory.
- `CDUP`: Change to the parent directory.
- `DELE`: Delete a file on the server.
- `LIST`: List files in the current directory.
- `PASV`: Enter passive mode for data transfer.
- `PORT`: Enter active mode for data transfer.
- `RETR`: Retrieve (download) a file from the server.
- `STOR`: Store (upload) a file to the server.

## Getting Started

### Prerequisites
- A C++ compiler (e.g., `g++`)
- `make` utility

### Building the Server

To compile the FTP server, navigate to the root directory of the project and run `make`:

```sh
make
```
This command will compile the source files and create an executable named `myftp` in the root directory.

### Building the Bonus Client

A basic command-line FTP client is included in the `bonus` directory. To build it:

```sh
cd bonus/
make
```
This will create an executable named `clientftp` inside the `bonus` directory.

## Usage

### Running the Server

The server requires a port number and a path to the directory that will serve as the FTP root.

```sh
./myftp <port> <path>
```
**Example:**
```sh
# This will start the server on port 2121, using /tmp/ftp_home as the root directory.
mkdir -p /tmp/ftp_home
./myftp 2121 /tmp/ftp_home
```

### Connecting with a Client

You can connect to the server using any standard FTP client. By default, the server accepts anonymous logins:
- **Username:** `Anonymous`
- **Password:** (empty)

You can also use the included bonus client:
```sh
./bonus/clientftp <ip> <port>
```
**Example:**
```sh
./bonus/clientftp 127.0.0.1 2121
```

## Makefile Commands

The main `Makefile` provides the following commands:
- `make all`: Compiles the server (default action).
- `make clean`: Removes the compiled server executable.
- `make fclean`: Performs a `clean` and removes any other generated files.
- `make re`: Force cleans and recompiles the entire project.
