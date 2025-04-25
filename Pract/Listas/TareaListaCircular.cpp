#include <iostream> // JHON MARIO AGUIRRE CORREA
#include <cstring>
#include <time.h>

using namespace std;

struct jugador{
  
    int ID;
    char nombre[20];
    struct jugador *sig;

};


//////////////////////////////////////////////////////////////////////////////////


void ingresarJ(struct jugador *&listaJ){

    struct jugador *nuevo = new struct jugador;

    if(listaJ == NULL){

     listaJ = nuevo;
     nuevo->sig = listaJ;

    } else {

      struct jugador *temp = listaJ;

      while(temp->sig != listaJ){

        temp = temp->sig;

      }

      temp->sig = nuevo;
      nuevo->sig = listaJ;

    }

    cout<<"\nIngresar jugador.\n";
    cout<<"\nIngrese el ID: "; cin>>nuevo->ID;
    cout<<"Ingrese el nombre: "; cin.ignore(); cin.getline(nuevo->nombre, 20);

    return;
}

//////////////////////////////////////////////////////////////////////////////////

void retirarJ(struct jugador *&listaJ){

  int idB;
  bool encontrado = false;
  struct jugador *tempE = listaJ;
  struct jugador *tempAnt = listaJ;

  if(listaJ == NULL){

    cout<<"\nAún no hay jugadores.\n";
    return;
  }

  cout<<"\nIngrese el id del jugador a retirar: "; cin>>idB;   

  if(listaJ->sig == listaJ){                                     // Caso en el que el jugador a eliminar sea el unico.

     if(listaJ->ID == idB){

      delete listaJ;
      listaJ = NULL;
      return;
     }

    cout<<"\nJugador no encontrado.\n"; return;
       
  } else {                                                       // Caso en el que hayan varios jugadores.                            

    do{                          

     if(tempE->ID == idB){
       
        encontrado = true;
        break;}

     tempAnt = tempE;
     tempE = tempE->sig;

  } while(tempE != listaJ);
}


  if(encontrado == false){

     cout<<"\nJugador no encontrado.\n"; return;
  }

  if (tempE == listaJ) {                               // Caso en el que el jugador a eliminar sea el primero.
    
    struct jugador *ultimoJ = listaJ;                  // Se recorre hasta el último jugador (Antes de llegar al primero de nuevo).

    while(ultimoJ->sig != listaJ){   

        ultimoJ = ultimoJ->sig;
    }
    
    
    listaJ = listaJ->sig;   
    ultimoJ->sig = listaJ;                             // Actualizamos el ultimo jugador para que apunte al primero.

  }

  tempAnt->sig = tempE->sig;                           // Eliminación del jugador de la lista.
  delete tempE; 

  return; 
}




//////////////////////////////////////////////////////////////////////////////////

void jugar(struct jugador *&listaJ){

int dado;
struct jugador *temp = listaJ;
struct jugador *tempAnt = listaJ;

srand(time(NULL)); //Generamos número aleatorio en base al tiempo
	dado = rand() % 6 + 1;


  if(listaJ == NULL){

    cout<<"\nAún no hay jugadores.\n";
    return;
  }

 
 cout<<"\nJugar\n";
 cout<<"\n¡El conteo será de "<<dado<<"!"<<endl;

 for(int i=1; i<dado; i++){                   // Recorrer las posiciones que indica el dado y a su anterior.
    
    tempAnt = temp;
    temp = temp->sig;
 }

struct jugador *antU = listaJ;
struct jugador *ultimo = listaJ;

 while(ultimo->sig != listaJ){                // Encontrar el último y penultimo jugador.
                                            
  antU = ultimo;
  ultimo = ultimo->sig;
 }

  if(temp == listaJ){                         // Caso en el que se elimine al primer jugador.

      listaJ = temp->sig;   // La cabeza cambia al siguiente jugador
      ultimo->sig = listaJ;
      
   } 
   
   else if(temp == ultimo){                   // Caso en el que se elimine el último jugador.

    antU->sig = listaJ;
    ultimo = antU;
    listaJ = temp->sig;  // La cabeza cambia al siguiente jugador
    
   } 

   else {                                    // Caso en el que se elimine un jugador intermedio.

     tempAnt->sig = temp->sig;
     listaJ = temp->sig;       // La cabeza cambia al siguiente jugador

   }
   
 

  cout<<"\n¡El jugador "<<temp->nombre<<" con ID: "<<temp->ID<<" ha sido eliminado.!\n";
  delete temp;

  if(listaJ->sig == listaJ){                     // Caso en el que solo quede un jugador.

    cout<<"\nEl ganador del juego ha sido "<<listaJ->nombre<<" con ID: "<<listaJ->ID<<endl;
    delete listaJ;
    listaJ = NULL;
    return;

 } 

  return; 

}





//////////////////////////////////////////////////////////////////////////////////

void mostrarJ(struct jugador *listaJ){

    struct jugador *temp = listaJ;

    if(listaJ == NULL){

      cout<<"\nAún no hay jugadores.\n";
      return;
    }

    cout<<"\nMostrar jugadores.\n";
    cout<<"\nJugadores actuales:\n\n";

    do{
        
       cout<<"_________________________\n";
       cout<<temp->ID<<endl;
       cout<<temp->nombre<<endl;
    
       temp = temp->sig;

    }
    while(temp != listaJ);

    return;
}





//////////////////////////////////////////////////////////////////////////////////

int main(){

  struct jugador *listaJ = NULL;
  int opc;
  
  cout<<"\nBienvenido al juego de la ronda.\n";
  
  while(true){

  cout<<"\nMENÚ:\n1) Ingresar un nuevo jugador.\n2) Retirar un jugador.\n3) Jugar a la ronda.\n4) Ver jugadores.\n5) Salir.\n\nIngrese una opción: ";
  cin>>opc;
  
  switch(opc){
  
     case 1: {ingresarJ(listaJ); break;}

     case 2: {retirarJ(listaJ); break;}

     case 3: {jugar(listaJ); break;}

     case 4: {mostrarJ(listaJ); break;}

     case 5: {cout<<"\nHasta luego.\n"; system ("pause"); return 0;}

     default: {cout<<"Opción no valida."; break;}

    }
  }
}