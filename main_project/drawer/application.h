#ifndef APPLICATION_H
#define APPLICATION_H

#include<simple2d.h>
#include<string>

struct Size{
	int width;
	int height;
};

/*class Application{
public:
	void start();
	static Application& getInstance(){
        static Application instance;
        return instance;
    }
	Application(Application const&)     = delete;
    void operator=(Application const&)  = delete;
private:
	Application();
    static Application instance;	
    static void update_wrapper();
	static void render_wrapper();
	S2D_Window *window;
	Size window_size;
	std::string command;
	void update();
	void render();
	void stop();
	static void static_update() {};
	static void static_render() {};
};*/

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
	S2D_Window *window;
	Size window_size;
	std::string parse_command(std::string& command);
	void stop();
	int pipe_read_from;
    int pipe_write_to;
	int action;
	// enum actions 
	// {   
	// 	spring = 0, 
 //    	summer = 4, 
 //    	autumn = 8,
 //    	winter = 12
	// };
};

#endif