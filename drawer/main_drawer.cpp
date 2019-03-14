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



#include <string>
#include <iostream>
#include <application.h>
Application* Application::instance = NULL;


Application::Application() {
	window_size.width = 640;
	window_size.height = 480;
	window->fps_cap = 5;
}

Application* Application::getInstance(){
	if (Application::instance == NULL)
		Application::instance = new Application();
    return Application::instance;
}

void update_wrapper(){
	std::cout << "update_wrapper" << std::endl;
	// Application::getInstance()->update();
}
void render_wrapper(){
	std::cout << "render_wrapper" << std::endl;
	// Application::getInstance()->render();
}

void update_wrapper2(){
	std::cout << "update_wrapper2" << std::endl;
}
void render_wrapper2(){
	std::cout << "render_wrapper2" << std::endl;
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
	std::cout << "start" << std::endl;
	update_wrapper();
	render_wrapper();
	S2D_Window* window2  = S2D_CreateWindow("Window", 100, 100, 
										              update_wrapper2, 
										              render_wrapper2, 
										              0);
}

void Application::stop() {
	S2D_Close(window);
	S2D_FreeWindow(window);
}
// struct Point{
// 	int x;
// 	int y;
// 	Point(int x_, int y_) :
// 		x(x_), y(y_) 
// 	{}
// 	Point() : x(0), y(0) 
// 	{}
// 	Point& operator=(const Point& rhs){
// 		// if (*this == rhs)
// 			// return *this;
// 		this->x = rhs.x;
// 		this->y = rhs.y;
// 		return *this;
// 	}
// };

// struct Triangle {
// 	Point v1;
// 	Point v2;
// 	Point v3;
// };

// // struct Rectangle
// // {
// // 	Size size;
// // 	Point upper_left;
// // };

// void render_triange(const Triangle& triang) {
//   S2D_DrawTriangle(
//     triang.v1.x, triang.v1.y, 1, 1, 1, 1,
//     triang.v2.x, triang.v2.y, 1, 1, 1, 1,
//     triang.v3.x, triang.v3.y, 1, 1, 1, 1
//   );
// }

// void render() {

// }

// void DrawRectangle(const Rectangle& rect){
// 	Point v1 = rect.upper_left;
// 	Point v2 = Point(rect.upper_left.x + rect.size.width, v1.y);
// 	Point v3 = Point(v2.x, rect.upper_left.y + rect.size.height);
// 	Point v4 = Point(v1.x, v3.y);
// }

int main() {
  std::cout << "main" << std::endl;
  Application* app = Application::getInstance();
  app->start();
	// S2D_Window* window2  = S2D_CreateWindow("Window", 100, 100, 
	// 									              update_wrapper2, 
	// 									              render_wrapper2, 
	// 									              0);
  // message = "";
  // window = S2D_CreateWindow("Window", 640, 480, update, render, 0);
  
  // S2D_Show(window);
  
  
  return 0;
}
