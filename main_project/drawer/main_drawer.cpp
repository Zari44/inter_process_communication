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
#include "application.h"



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
  // message = "";
  // window = S2D_CreateWindow("Window", 640, 480, update, render, 0);
  
  // S2D_Show(window);
  
  
  return 0;
}
