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
	Application::getInstance()->update();
}

void render_wrapper(){
	Application::getInstance()->render();
}

Application* Application::instance = NULL;

Application* Application::getInstance(int pipe_read_from_, int pipe_write_to_){
	if (Application::instance == NULL)
		Application::instance = new Application(pipe_read_from_, pipe_write_to_);
    return Application::instance;
}

Application::Application(int pipe_read_from_, int pipe_write_to_) :
	pipe_read_from(pipe_read_from_), 
	pipe_write_to(pipe_write_to_) {
	window_size.width = 640;
	window_size.height = 480;
}

void Application::start() {
	std::cout << "start" << std::endl;
	window = S2D_CreateWindow("Window", window_size.width, window_size.height,
										update_wrapper, render_wrapper, S2D_RESIZABLE);
	window->fps_cap = 1;
	S2D_Show(window);
}

void Application::update() {
	std::cout << "Start update:\n";
	const int COMMAND_MAX_SIZE = 100;
	char buffer[BUFSIZ + 1];
    memset(buffer, '\0', sizeof(buffer));

	int data_processed = read(pipe_read_from, buffer, COMMAND_MAX_SIZE);

	std::string input_command(buffer);
	// std::cout << "Received command: " << command << std::endl;
	std::string message_back = parse_command(input_command);
	
	data_processed = write(pipe_write_to, message_back.c_str(), message_back.length());

	std::cout << "End update.\n";
}

void Application::render() {
	std::cout << "Start render\n";
	
	window->viewport.width  = window_size.width;
	window->viewport.height = window_size.height;

	switch(action) //operator sterujący czyli jakaś zmienna zawierająca liczbę np. typu int
	{
	    case Application::nothing:
	        std::cout << "Action: nothing\n";
	    	break;
	    case Application::quit:
	    	this->stop();
	        std::cout << "Action: quit\n";
	    	break;
	    case Application::save:
	        std::cout << "Action: save\n";
	    	break;
	    case Application::draw_rectangle:
	        std::cout << "Action: draw_rectangle\n";
	    	break;
	    case Application::draw_triangle:
	        std::cout << "Action: draw triangle\n";
	    	break;
	    default:
	        std::cout << "Action: unknown\n";
	    break;
	}
	action = Application::nothing;


	S2D_DrawQuad(100, 100, 1, 1, 1, 1,
         	 	 150, 100, 1, 1, 1, 1,
         	 	 150, 150, 1, 1, 1, 1,
         	 	 100, 150, 1, 1, 1, 1);

	std::cout << "Finished render\n";
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
		action = Application::quit;
		message_back = "Received comand quit\n";
	}
    else if (strings.size() != 2) {
    	message_back = "Invalid command. Wrong number of parameters. It must have two parameters.";
    }
	else if (strings[0] == "SET_WIDTH") {
		message_back = "Received comand set width\n";
		window_size.width = std::stoi(strings[1]);
	}
	else if (strings[0] == "SET_HEIGHT") {
		message_back = "Received comand set height\n";
		window_size.height = std::stoi(strings[1]);
	}
	else if (strings[0] == "DRAW_RECTANGLE") {
		action = Application::draw_rectangle;
		message_back = "Received comand draw rectangle\n";
	}
	else if (strings[0] == "DRAW_TRIANGLE") {
		action = Application::draw_triangle;
		message_back = "Received comand draw triangle\n";
	}
	else if (strings[0] == "RENDER") {
		action = Application::save;
		message_back = "Received comand render\n";
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