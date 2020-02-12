#ifndef PIPE_HELPER_H
#define PIPE_HELPER_H

#include <string>
#include <fstream>

namespace sandbox {
    class Pipe {
    public:
	Pipe(std::string name);

	template<typename T>
	T read() {
	    stream.open(path, std::ios::in);
	    char data;
	    stream >> data;
	    stream.close();
	    return data;
	}

	template<typename T>
	void write(T data) {
	    stream.open(path, std::ios::out);
	    stream << data << std::endl;
	    stream.close();
	}
    private:
	std::string path;
	std::fstream stream;
    };
}

#endif
