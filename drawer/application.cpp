// SET_WIDTH W - 
// komenda określa szerokość ekranu w pikselach, W jest liczbą całkowitą określającą ilość pikseli.
// SET_HEIGHT H - 
// komenda określa wysokość ekranu w pikselach, H jest liczbą całkowitą określającą ilość pikseli.
// DRAW_RECTANGLE X,Y,W,H - 
// komenda służy do rysowania prostokąta, którego lewy górny róg ma współrzędne X,Y a W i H 
// oznaczają odpowiednio szerokość i wysokość prostokąta.
// DRAW_TRIANGLE X1,Y1,X2,Y2,X3,Y3 - 
// komenda służy do rysowania trójkąta którego rogi mają współrzędne poziome i pionowe 
// odpowiednio w punktach (X1,Y1), (X2,Y2) oraz (X3,Y3).
// RENDER NAME - przygotowuje obraz oraz zapisuje go do pliku w wybranym formacie graficznym
 // (BMP, PNG, JPEG) pod nazwą określoną parametrem “NAME”.


#include "application.h"
// #include<simple2d.h>
#include <iostream>
#include<vector>
#include <sstream>

void update_wrapper(){
	std::cout << "update_wrapper" << std::endl;
	Application::getInstance()->update();
}

void render_wrapper(){
	std::cout << "render_wrapper" << std::endl;
	Application::getInstance()->render();
}

Application* Application::instance = NULL;

Application::Application() {
	window_size.width = 640;
	window_size.height = 480;
}

Application* Application::getInstance(){
	if (Application::instance == NULL)
		Application::instance = new Application();
    return Application::instance;
}

void Application::start() {
	std::cout << "start" << std::endl;
	window = S2D_CreateWindow("Window", window_size.width, window_size.height,
										update_wrapper, render_wrapper, 0);
	window->fps_cap = 1;
	S2D_Show(window);
}

void Application::update() {
	std::string command;
	std::cin >> command;
	// std::cout << command << std::endl;
	parse_command(command);
}

void Application::render() {
	S2D_DrawQuad(100, 100, 1, 1, 1, 1,
         	 	 150, 100, 1, 1, 1, 1,
         	 	 150, 150, 1, 1, 1, 1,
         	 	 100, 150, 1, 1, 1, 1);
}

void Application::parse_command(std::string& command) {
	std::vector<std::string> strings;
	std::stringstream command_stream;
	command_stream << command;
	std::string word;

	while (std::getline(command_stream, word, ' ')) {
        std::cout << word << std::endl;
        strings.push_back(word);
    }

    if (strings.size() != 2) {
    	std::cout << "Invalid command. It must have two parameters.";
    	return;
    }

	if (strings[0] == "SET_WIDTH") {
		window_size.width = std::stoi(strings[1]);
	}
	else if (strings[0] == "SET_HEIGHT") {
		window_size.height = std::stoi(strings[1]);
	}
	else if (strings[0] == "DRAW_RECTANGLE") {

	}
	else if (strings[0] == "DRAW_TRIANGLE") {
		
	}
	else if (strings[0] == "RENDER") {
		
	}	
	else if (strings[0] == "quit") {
		this->stop();
	}
}

void Application::stop() {
	S2D_Close(window);
	S2D_FreeWindow(window);
}