#include <iostream>
#include <conio.h>  // Necesario para getch()
using namespace std; 

#define ESC 27
#define ENTER 13

int main() {
    int x;

    x = getch();  // Captura la tecla presionada

    while (x != ESC && x != ENTER) {

            switch (x) {
                case 72: cout<<"Flecha Arriba\n"; break;
                case 75: cout<<"Flecha Izquierda\n"; break;
                case 77: cout<<"Flecha Derecha\n"; break;
                case 80: cout<<"Flecha Abajo\n"; break;
                default: break;
            }
        x = getch();
    }

    return 0;
}
