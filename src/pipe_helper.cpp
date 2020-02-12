#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include "pipe_helper.hpp"

namespace sandbox {
    Pipe::Pipe(std::string name)
    {
	#ifdef __unix__
	path = "/tmp/" + name;
	mkfifo(path.c_str(), 0666);
	#else

	#endif
    }
}
