#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include "pipe_helper.hpp"

namespace sandbox {
    Pipe::Pipe(std::string name)
    {
	path = "/tmp/" + name;
	mkfifo(path.c_str(), 0666);
    }
}
