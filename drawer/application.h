#ifndef APPLICATION_H
#define APPLICATION_H

#include<simple2d.h>
#include<string>
#include<vector>

struct Size{
	int width;
	int height;
};

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

class Application{
public:
	static Application* instance;
	static Application* getInstance(int pipe_read_from_=0, int pipe_write_to_=0);
    void start();
	void update();
	void render();
    Application(Application const&)     = delete;
    void operator=(Application const&)  = delete;
private:
	Application(int pipe_read_from_, int pipe_write_to_);
	~Application();
	struct State{
		State();
		int draw;
		enum shape { nic = 0, triangle, rectangle, };
		bool quit;
		bool save;
		std::string screenshot_filename;
		std::vector<int> X;
		std::vector<int> Y;
	} state;
	S2D_Window *window;
	Size window_size;
	std::vector<std::string> parseCommand(std::string& command); 
	std::string chooseAction(const std::vector<std::string>& command_words);
	void stop();
	int pipe_read_from;
    int pipe_write_to;
    void draw_rectangle();
    void draw_triangle();
    void mapRectangleParametersToState(const std::vector<int>& parameters);
    void mapTriangleParametersToState(const std::vector<int>& coordinates);
    void parse_triangle_size(const std::string& size_command);
    void parse_rectangle_size(const std::string& size_command);
};

#endif