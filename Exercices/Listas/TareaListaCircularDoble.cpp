#include <iostream> // JHON MARIO AGUIRRE CORREA
#include <cstring>
#include <time.h>

using namespace std; 


struct jugador{

  int id;
  char nombre [20];

  struct jugador *sig;
  struct jugador *ant;

};


////////////////////////////////////////////////////////////////////////////


void ingresarJ (struct jugador *&listaJ){

    struct jugador *nuevo = new struct jugador;
    struct jugador *temp = listaJ;

    
    cout<<"\nIngresar un nuevo jugador.\n";
    cout<<"\nIngrese el ID: "; cin>>nuevo->id;
    cout<<"Ingrese el nombre: "; cin.ignore(); cin.getline(nuevo->nombre, 20);

    

   if(listaJ == NULL) {

    listaJ = nuevo; 
    nuevo->sig = listaJ;
    nuevo->ant = listaJ;

   } else {

    while(temp->sig != listaJ){
 
        temp = temp->sig;
    }

     temp->sig = nuevo;
     nuevo->ant = temp; // El nuevo ahora tambien apunta a su anterior. (Anterior último).
     nuevo->sig = listaJ;
     listaJ->ant = nuevo; // Actualizar el primer nodo para que apunte al nuevo último
   } 

   cout<<"\nJugador ingresado correctamente.\n";

}

////////////////////////////////////////////////////////////////////////////

void retirarJ (struct jugador *&listaJ){

    struct jugador *temp = listaJ;
    struct jugador *ultimo = listaJ;
    int idB;
    bool encontrado = false;

    if(listaJ == NULL){
       cout<<"\nAún no hay jugadores.\n";
       return;
    }
  
   cout<<"\nIngrese el ID del jugador a retirar: "; cin>>idB;

   do{
     
      if(temp->id == idB){ 
         encontrado = true;
         break;
      }

      temp = temp->sig; 
   } while(temp != listaJ); 


  if(encontrado == false){
    cout<<"\nJugador no encontrado.\n";
    return;
  }

  while(ultimo->sig != listaJ){
 
    ultimo = ultimo->sig;
  }

  if(listaJ->sig == listaJ){  // 1) Caso en el que el jugador a retirar sea el unico de la lista.

    if(listaJ->id == idB){
    
      delete listaJ;
      listaJ = NULL;
      return; 
    }

  } else if(temp == listaJ){  // 2) Caso en el que el jugador a retirar sea el primero de la lista. 
    
     listaJ = temp->sig;
     listaJ->ant = temp->ant;
     ultimo->sig = listaJ;

    
  } else if (temp == ultimo){  // 3) Caso en el que el jugador a retirar sea el último.

     ultimo = temp->ant;
     ultimo->sig = listaJ;
     listaJ->ant = ultimo;

  } else{                     // 4) Caso en el que el jugador a retirar sea intermedio.
 
    temp->ant->sig = temp->sig; ///
    temp->sig->ant = temp->ant; ///

  }

   delete temp;
   cout<<"\nJugador retirado correctamente.\n";
}




////////////////////////////////////////////////////////////////////////////

void jugar(struct jugador *&listaJ){

  int dado;
  int opc;
  struct jugador *temp = listaJ;
  
  srand(time(NULL)); // Generamos número aleatorio en base al tiempo
  dado = rand() % 6 + 1;

  if(listaJ == NULL){
    cout<<"\nAún no hay jugadores.\n";
    return;
  }

  if(listaJ->sig == listaJ){ // Caso en el que solo haya un jugador.
    
    cout<<"\nSolo hay un jugador: "<<listaJ->nombre<<" con ID: "<<listaJ->id<<endl;
    return;
  } 

  cout<<"\nJugar\n";
  cout<<"\n¡El conteo será de "<<dado<<"!"<<endl;
  cout<<"\n¿En qué sentido desea recorrer la lista?\n1) De cabeza a cola.\n2) De cola a cabeza.\nOpción: "; cin>>opc;

// ________________________________________________________________________________________________________

  if(opc == 1){ // Recorrer la lista de cabeza a cola.
    for(int i = 1; i < dado; i++){
      temp = temp->sig;
    }

    if(temp == listaJ){ // Caso en el que se elimine el primer jugador de la lista.

      listaJ = temp->sig;
      listaJ->ant = temp->ant;
      temp->ant->sig = listaJ;

    } else if(temp->sig == listaJ){ // Caso en el que se elimine el último jugador de la lista.

      temp->ant->sig = listaJ;
      listaJ->ant = temp->ant;

    } else { // Caso en el que se elimine un jugador intermedio.

      temp->ant->sig = temp->sig;
      temp->sig->ant = temp->ant;
    }

// ________________________________________________________________________________________________________

  } else if(opc == 2){ // Recorrer la lista de cola a cabeza.
    for(int i = 1; i < dado; i++){
      temp = temp->ant;
    }

    if(temp == listaJ){ // Caso en el que el jugador a eliminar sea el primero.

      listaJ = temp->ant;
      temp->sig->ant = temp->ant;
      temp->ant->sig = temp->sig;
     
    } else if(temp->ant == listaJ){ // Caso en el que el jugador a eliminar sea el último.

      temp->ant->sig = listaJ;
      listaJ->ant = temp->ant;

    } else { // Caso en el que el jugador a eliminar sea intermedio.

      listaJ = temp->ant;
      temp->ant->sig = temp->sig;
      temp->sig->ant = temp->ant;
    }

  } else {
    cout<<"\nOpción inválida."; 
    return;
  }

// ________________________________________________________________________________________________________

  cout<<"\n¡El jugador "<<temp->nombre<<" con ID: "<<temp->id<<" ha sido eliminado!\n";
  delete temp;

  if(listaJ->sig == listaJ){ // Caso en el que solo quede un jugador.
    
    cout<<"\nEl ganador del juego ha sido "<<listaJ->nombre<<" con ID: "<<listaJ->id<<endl;
    delete listaJ;
    listaJ = NULL;
    return;
  } 

  return; 
}



////////////////////////////////////////////////////////////////////////////

void mostrarJ(struct jugador *&listaJ){

  int opc;
  struct jugador *temp = listaJ;

   if(listaJ == NULL){
    cout<<"\nNo hay jugadores.\n";
    return;
   }

  cout<<"\nMostrar jugadores.\n";
  cout<<"\n1) Mostrar del inicio al final.\n2) Mostrar del final al inicio.\nOpc: "; cin>>opc; cout<<endl;
  
   if(opc == 1){

      do{
 
         cout<<"___________________"<<endl<<temp->id<<endl<<temp->nombre<<endl;
         temp = temp->sig;

        } while(temp != listaJ);

   } else if(opc == 2){

    temp = listaJ->ant; 
    do{
 
      cout<<"___________________"<<endl<<temp->id<<endl<<temp->nombre<<endl;
      temp = temp->ant;

      } while(temp != listaJ->ant); 

   } else{

     cout<<"\nOpción invalida.\n";
   }
  
}

////////////////////////////////////////////////////////////////////////////


int main(){

    struct jugador *listaJ = NULL;
    int opc;
    
    cout<<"\nBienvenido al juego de la ronda V2.\n";
    
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