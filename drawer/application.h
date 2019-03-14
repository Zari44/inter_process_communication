#ifndef APPLICATION_H
#define APPLICATION_H

#include<simple2d.h>
#include<string>

struct Size{
	int width;
	int height;
};

class Application{
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
};

#endif