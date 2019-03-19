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
#include <fcntl.h>

void update_wrapper(){
	Application::getInstance()->update();
}

void render_wrapper(){
	Application::getInstance()->render();
}

Application::State::State(){
	draw = Application::State::nic;
	save = false;
	screenshot_filename = "";
	quit = false;
}

Application* Application::instance = NULL;

Application* Application::getInstance(int pipe_read_from_, int pipe_write_to_){
	if (Application::instance == NULL)
		Application::instance = new Application(pipe_read_from_, pipe_write_to_);
    return Application::instance;
}

Application::Application(int pipe_read_from_, int pipe_write_to_) :
	state(),
	pipe_read_from(pipe_read_from_), 
	pipe_write_to(pipe_write_to_) {
	//make read pipe not blockable

    if ( fcntl( pipe_read_from_, F_SETFL, fcntl(pipe_read_from_, F_GETFL) | O_NONBLOCK) < 0)
        exit(1);
	window_size.width = 640;
	window_size.height = 480;
}

void Application::start() {
	std::cout << "start" << std::endl;
	window = S2D_CreateWindow("Window", window_size.width, window_size.height,
										update_wrapper, render_wrapper, S2D_RESIZABLE);
	window->fps_cap = 1;
	window->viewport.mode = S2D_EXPAND; // allows to resize window
	S2D_Show(window);
}

void Application::update() {
	// std::cout << "Start update:\n";
	const int COMMAND_MAX_SIZE = 100;
	char buffer[BUFSIZ + 1];
    memset(buffer, '\0', sizeof(buffer));

	int data_processed = read(pipe_read_from, buffer, COMMAND_MAX_SIZE);

	if (data_processed >=0){
		std::string input_command(buffer);
		std::string message_back = parse_command(input_command);
	
		data_processed = write(pipe_write_to, message_back.c_str(), message_back.length());
	}
	else {
		// std::cout << "Read timeout" << std::endl;
	}
}

void Application::render() {

	if (state.quit){
		this->stop();
	}

	window->viewport.width  = window_size.width;
	window->viewport.height = window_size.height;

	switch (state.draw){
		case Application::State::nic:
		break;

		case Application::State::triangle:
            S2D_DrawTriangle(320,  50, 1, 0, 0, 1,
	  				 		 540, 430, 0, 1, 0, 1,
					 		 100, 430, 0, 0, 1, 1);
		break;

		case Application::State::rectangle:
        	S2D_DrawQuad(100, 100, 1, 0, 0, 1,
	 	 			     150, 100, 0, 1, 0, 1,
	 				     150, 150, 0, 0, 1, 1,
	 	  			     100, 150, 0, 0, 0, 1);
		break;

		default:
		break;

	}

	if (state.save){
		state.save = false;
		S2D_Screenshot(window, state.screenshot_filename.c_str());
	}
}

std::string Application::parse_command(std::string& command) {
	std::vector<std::string> strings;
	std::stringstream command_stream;
	command_stream << command;
	std::string word;

	while (std::getline(command_stream, word, ' ')) {
        std::cout << word << std::endl;
        strings.push_back(word);
    }

    std::string message_back = "";

    if (strings[0] == "quit") {
		state.quit = true;
		message_back = "Received command quit";
	}
    else if (strings.size() != 2) {
    	message_back = "Invalid command. Wrong number of parameters. It must have two parameters.";
    }
	else if (strings[0] == "SET_WIDTH") {
		message_back = "Received command set width";
		window_size.width = std::stoi(strings[1]);
		window->viewport.width = window_size.width;
	}
	else if (strings[0] == "SET_HEIGHT") {
		message_back = "Received command set height";
		window_size.height = std::stoi(strings[1]);
	}
	else if (strings[0] == "DRAW_RECTANGLE") {
		state.draw = Application::State::rectangle;
		message_back = "Received command draw rectangle";
	}
	else if (strings[0] == "DRAW_TRIANGLE") {
		state.draw = Application::State::triangle;
		message_back = "Received command draw triangle";
	}
	else if (strings[0] == "RENDER") {
		state.save = true;
		state.screenshot_filename = strings[1] + ".png";
		message_back = "Received command render screenshot";		
	}	
	else{
		message_back = "Received unknown command";
	}

	std::cout << message_back << std::endl;
	return message_back;
}

void Application::stop() {
	S2D_Close(window); //exit the window loop
	S2D_FreeWindow(window); //free the window
}