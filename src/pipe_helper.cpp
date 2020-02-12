#include <iostream>
#include "pipe_helper.hpp"

#ifdef __unix_
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#else
#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include <strsafe.h>
#endif

namespace sandbox {
    Pipe::Pipe(std::string name)
    {
#ifdef __unix__
        path = "/tmp/" + name;
        mkfifo(path.c_str(), 0666);
#else
        path = "\\\\.\\pipe\\" + name;
        LPTSTR pipename = const_cast<LPSTR>(TEXT(path.c_str()));
        pipe = CreateNamedPipe(
            pipename,                 // pipe name
            PIPE_ACCESS_DUPLEX,       // read/write access
            PIPE_TYPE_MESSAGE |       // message type pipe
            PIPE_READMODE_MESSAGE |   // message-read mode
            PIPE_WAIT,                // blocking mode
            PIPE_UNLIMITED_INSTANCES, // max. instances
            BUFSIZE,            // output buffer size
            BUFSIZE,            // input buffer size
            0,                        // client time-out
            NULL
        );

        bool connected = ConnectNamedPipe(pipe, NULL) ? TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);

        if (!connected) {
            CloseHandle(pipe);
            std::cout << "Could not open named pipe" << std::endl;
            throw;
        }
#endif
    }

    Pipe::~Pipe()
    {
#ifndef __unix__
        CloseHandle(pipe);
#endif
    }

    char Pipe::read()
    {
#ifdef __unix__
			stream.open(path, std::ios::in);
			char data;
			stream >> data;
			stream.close();
			return data;
#else
			bool success = false;
			TCHAR data;

			success = ReadFile(pipe, &data, sizeof(TCHAR), &bytesRead, NULL);

			return data;
#endif
    }

    void Pipe::write(char data)
    {
#ifdef __unix__
        stream.open(path, std::ios::out);
        stream << data << std::endl;
        stream.close();
#else
        bool success = false;
        success = WriteFile(pipe, &data, sizeof(char), &bytesWritten, NULL);
#endif
    }

    void Pipe::write(std::string data)
    {
        for (char c : data) {
            write(c);
        }
    }
}
