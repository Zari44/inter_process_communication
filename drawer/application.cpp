#include "application.h"
#include <iostream>

Application::Application() {
	window_size.width = 640;
	window_size.height = 480;
	window->fps_cap = 5;
}

void Application::update_wrapper(){
	instance.update();
}

void Application::render_wrapper(){
	instance.render();
}

void Application::update() {
	
	std::cin >> command;
	std::cout << command << std::endl;
	if (command == "quit"){
		this->stop();
	}
}

void Application::render() {
	S2D_DrawQuad(100, 100, 1, 1, 1, 1,
         	 	 150, 100, 1, 1, 1, 1,
         	 	 150, 150, 1, 1, 1, 1,
         	 	 100, 150, 1, 1, 1, 1);
}

void Application::start() {
	void (Application::* ptrupdate)() = &Application::update;
	void (Application::* ptrrender)() = &Application::render;
	window = S2D_CreateWindow("Window", window_size.width, window_size.height, 
										update_wrapper, 
										render_wrapper, 
										0);
}

void Application::stop() {
	S2D_Close(window);
	S2D_FreeWindow(window);
}