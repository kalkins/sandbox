#ifndef PIPE_HELPER_H
#define PIPE_HELPER_H

#include <string>

#ifdef __unix__
#include <fstream>
#else
#include <windows.h>
#endif

namespace sandbox {
    class Pipe {
    public:
	Pipe(std::string name);

	template<typename T>
	T read() {
	    #ifdef __unix__
	    stream.open(path, std::ios::in);
	    char data;
	    stream >> data;
	    stream.close();
	    return data;
	    #else

	    #endif
	}

	template<typename T>
	void write(T data) {
	    #ifdef __unix__
	    stream.open(path, std::ios::out);
	    stream << data << std::endl;
	    stream.close();
	    #else

	    #endif
	}
    private:
	std::string path;
	#ifdef __unix__
	std::fstream stream;
	#else

	#endif
    };
}

#endif
