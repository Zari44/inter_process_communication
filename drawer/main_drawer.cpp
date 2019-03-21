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


int main(int argc, char *argv[]) {

  int pipe_read_from = std::atoi(argv[1]);
  int pipe_write_to = std::atoi(argv[2]);
  char buffer[BUFSIZ + 1];
  memset(buffer, '\0', sizeof(buffer));
  
  Application* app = Application::getInstance(pipe_read_from, pipe_write_to);
  app->start();

  printf("Drawer process exits\n");
  
  return 0;
}
