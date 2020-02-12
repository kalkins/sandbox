#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <k4a/k4a.h>
#include "k4a_helper.hpp"

int main()
{
    k4a_device_configuration_t config = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
    config.color_format = K4A_IMAGE_FORMAT_COLOR_MJPG;
    config.color_resolution = K4A_COLOR_RESOLUTION_OFF;
    config.depth_mode = K4A_DEPTH_MODE_NFOV_UNBINNED;
    config.camera_fps = K4A_FRAMES_PER_SECOND_30;

    k4a_device_t device;

    if (k4a_open_start(device, config)) {
	return -1;
    }

    std::string pipe_name = "sandbox_pipe";
    std::string pipe_path = "/tmp/" + pipe_name;

    mkfifo(pipe_path.c_str(), 0666);

    char c;
    std::string msg;
    std::vector<uint16_t> data = {1, 2, 3, 4};

    std::fstream pipe;

    while (true) {
	std::cout << "Opening pipe" << std::endl;
	pipe.open(pipe_path, std::ios::in);
	std::cout << "Waiting for message" << std::endl;
	pipe >> c;
	pipe.close();

	if (c == 'r') {
	    std::cout << "Sending response" << std::endl;
	    pipe.open(pipe_path, std::ios::out);
	    pipe << data.size() << std::endl;

	    for (auto d : data) {
		d++;
		pipe << d << std::endl;
	    }

	    std::cout << "Message sent" << std::endl;
	    pipe.close();
	} else if (msg == "q") {
	    break;
	}
    }

    k4a_close(device);
    return 0;
}
