#include <iostream> // JHON MARIO AGUIRRE CORREA // 
#include <cstring>
#include <conio.h>
using namespace std;

struct canal{

  int numero;
  char nombreC[20];

  struct canal *sigC;
  struct canal *antC;
  struct programa *programas;
};


struct programa{

    int franjaHoraria;
    char nombreP[20];
    int clasificacion;

    struct programa *sigP;
    struct programa *antP;
};

/////////////////////////////////////////////////////////////////////////////////////

void agregarPrograma(struct canal *&canales, const int numero){

    struct canal *temp = canales; 
    struct programa *nuevoP = new(struct programa);
 
       if(canales == NULL){
         cout<<"\nAún no hay canales.\n";
         return;
       }

     do{
      
       if(temp->numero == numero){
         break;
        }
        temp = temp->sigC;

     } while(temp != canales);

       if(temp->numero != numero){
          cout<<"\nCanal no encontrado.\n";
          return;
       }

    cout<<"\nIngrese la información del nuevo programa:\n";
    cout<<"\nFranja horaria (Hora militar - Horas exactas): "; cin>>nuevoP->franjaHoraria;
    cout<<"Nombre: "; cin.ignore(); cin.getline(nuevoP->nombreP, 20);
    cout<<"Clasificación (int): +"; cin>>nuevoP->clasificacion;

    if(temp->programas == NULL){                                               // Caso en el que sea el primer programa del canal.

      temp->programas = nuevoP;
      nuevoP->sigP = NULL;
      nuevoP->antP = NULL;
      return;
    
    }else{
   
       struct programa *tempP = temp->programas;
      
       while(tempP != NULL){                                                   // Verificar que no exista un programa a la misma hora.

            if(tempP->franjaHoraria == nuevoP->franjaHoraria){
                cout<<"\nYa existe un programa en la hora ingresada.\n";
                delete nuevoP;
                return;
            }
            tempP = tempP->sigP;
          }
     tempP = temp->programas;

     while (true) {

      if(nuevoP->franjaHoraria < temp->programas->franjaHoraria) {            // Caso en el que el nuevo programa se agregue al inicio.
          
          nuevoP->sigP = temp->programas;
          nuevoP->antP = NULL;
          temp->programas->antP = nuevoP;
          temp->programas = nuevoP;
          break;
  
      }else if ((nuevoP->franjaHoraria < tempP->franjaHoraria) &&             // Caso en el que se agregue en una posición intermedia.
                 (tempP->antP == NULL || nuevoP->franjaHoraria > tempP->antP->franjaHoraria)) {  
          
          nuevoP->sigP = tempP;
          nuevoP->antP = tempP->antP;
          tempP->antP->sigP = nuevoP;
          tempP->antP = nuevoP;
          break;

      }else if (tempP->sigP == NULL) {                                        // Caso en el que el nuevo programa se agregue al final. 
         
        nuevoP->antP = tempP;
        tempP->sigP = nuevoP;
        nuevoP->sigP = NULL;
        break;
       }
       tempP = tempP->sigP;
     }
   }
   cout<<"\nPrograma agregado correctamente.\n";
   return;
}

/////////////////////////////////////////////////////////////////////////////////////

void agregarCanal(struct canal *&canales) {
 
    int opc;
    struct canal *nuevo = new canal;
    struct canal *temp = canales;

    cout<<"\nIngrese la información del nuevo canal.\n";
    cout<<"\nNúmero: "; cin >> nuevo->numero;
    cout<<"Nombre: "; cin.ignore(); cin.getline(nuevo->nombreC, 20);

    nuevo->sigC = NULL;
    nuevo->antC = NULL;
    nuevo->programas = NULL;

    if (canales == NULL) {                                                             // Caso en el que sea el primer canal agregado.
        canales = nuevo;
        canales->sigC = canales;
        canales->antC = canales;

     }else{

           do{    // Verificar que el canal no exista.
               if (nuevo->numero == temp->numero) {  
                   cout<<"\nEl canal ya existe.\n";   
                   return;  
               }  
               temp = temp->sigC;  
           } while (temp != canales);

         temp = canales;

    while (true) {

        if ((nuevo->numero < temp->numero) && (nuevo->numero > temp->antC->numero)) { // Caso en el que se agrege en una posición intermedia.
                
            nuevo->sigC = temp;
            nuevo->antC = temp->antC;
            temp->antC->sigC = nuevo;
            temp->antC = nuevo;
            break;

        }else if (nuevo->numero < canales->numero) {                                 // Caso en el que se agregue al inicio.
             
            nuevo->sigC = canales;
            nuevo->antC = canales->antC;
            canales->antC->sigC = nuevo;
            canales->antC = nuevo;
            canales = nuevo;  // Actualizar la cabeza de la lista.
            break;

        }else if (temp->sigC == canales) {                                            // Caso en el que se agregue al final.
                
            nuevo->sigC = canales;
            nuevo->antC = temp;
            temp->sigC = nuevo;
            canales->antC = nuevo;
            break;
            }

          temp = temp->sigC;
     }
    }

    cout<<"\nCanal ingresado correctamente.\n";

   while(true){

     cout<<"\n¿Desea ingresar un programa al canal? (1) Sí, (2) No): "; cin>>opc; 

     if(opc == 1){
       agregarPrograma(canales, nuevo->numero);

     }else if(opc == 2){
        return;

     }else{
       cout<<"\nOpción invalida.\n";
       return;
     }
   }
}

/////////////////////////////////////////////////////////////////////////////////////

void mostrarInfC(struct canal *&canales){

 int nroCB;
 char nombreCB[20];
 int opc;
 bool encontrado = false;

 cout<<"\nMostrar información de un canal.";
 cout<<"\nMostrar información por: (1) número. (2) nombre.\nOpción: "; cin>>opc;
 
 if(opc == 1){

     struct canal *tempC = canales;
     cout<<"\nIngrese el número del canal: "; cin>>nroCB;

     do{
 
         if(tempC->numero == nroCB){
            encontrado = true;
            break;
         }
        tempC = tempC->sigC;

     }while(tempC != canales);

      if(encontrado == false){
        cout<<"\nCanal no encontrado.\n";
        return;
      }

      cout<<"\n_______CANAL_________"<<endl;
      cout<<"Número: "<<tempC->numero<<endl;
      cout<<"Nombre: "<<tempC->nombreC<<endl;

      struct programa *tempP = tempC->programas;
      while(tempP != NULL) {
          cout<<"______PROGRAMA_______"<<endl;
          cout<<"Franja horaria: "<<tempP->franjaHoraria<<":00"<<endl;
          cout<<"Nombre: "<<tempP->nombreP<<endl;
          cout<<"Clasificación: +"<<tempP->clasificacion<<endl;
          tempP = tempP->sigP;
      }


  } else if(opc == 2){  

    struct canal *tempC = canales;
    cout<<"\nIngrese el nombre del canal: "; cin.ignore(); cin.getline(nombreCB, 20);

    do{
        if(strcmp(tempC->nombreC, nombreCB) == 0){
           encontrado = true;
           break;
        }
       tempC = tempC->sigC;

    }while(tempC != canales);

    if(encontrado == false){
      cout<<"\nCanal no encontrado.\n";
      return;
    }

     cout<<"\n_______CANAL_________"<<endl;
     cout<<"Número: "<<tempC->numero<<endl;
     cout<<"Nombre: "<<tempC->nombreC<<endl;

     struct programa *tempP = tempC->programas;
     while(tempP != NULL) {
         cout<<"______PROGRAMA_______"<<endl;
         cout<<"Franja horaria: "<<tempP->franjaHoraria<<":00"<<endl;
         cout<<"Nombre: "<<tempP->nombreP<<endl;
         cout<<"Clasificación: +"<<tempP->clasificacion<<endl;
         tempP = tempP->sigP;
     }

   }else{
         cout<<"\nOpción invalida.\n"; return;
    } 
}

/////////////////////////////////////////////////////////////////////////////////////

void eliminarP(struct canal *&canales){ 

  struct canal *tempC = canales;
  struct programa *tempP = NULL;
  struct programa *tempAux = NULL;
  int opc;
  int nroB;
  char nombreB[20];
  bool encontrado = false;

  cout<<"\nBorrar programas de un canal.\n(1) Buscar por número.\n(2) Buscar por nombre.\nOpción: "; cin>>opc;

  if(opc == 1){

    cout<<"\nIngrese el número del canal: "; cin>>nroB;

     do{
        if(tempC->numero == nroB){
         encontrado = true;
         break;
        }
        tempC = tempC->sigC;

     }while(tempC != canales);

   }else if(opc == 2){

    cout<<"\nIngrese el nombre del canal: "; cin.ignore(); cin.getline(nombreB, 20);
    
    do{
      if(strcmp(tempC->nombreC, nombreB) == 0){
       encontrado = true;
       break;
      }
      tempC = tempC->sigC;

   } while(tempC != canales);

  } else{cout<<"\nOpción invalida.\n";}

  if(encontrado == false){
    cout<<"\nCanal no encontrado.\n";
    return;
  }

  if(tempC->programas == NULL){
    cout<<"\nEl canal no tiene programas.\n";
  }

  tempP = tempC->programas;

  while(tempP != NULL){
     tempAux = tempP;
     tempP = tempP->sigP;
     delete tempAux;
  }

  tempC->programas = NULL;
  cout<<"\nProgramas eliminados correctamente.\n";
}

/////////////////////////////////////////////////////////////////////////////////////

void eliminarCanal(struct canal *&canales){

  struct canal *tempCEliminar = canales;
  struct programa *tempP = NULL;
  struct programa *tempAux = NULL;
  int opc;
  int nroB;
  char nombreB[20];
  bool encontrado = false;


  if(canales == NULL){
    cout<<"\nAún no hay canales registrados.\n";
  }

  cout<<"\nBorrar un canal.\n(1) Buscar por número.\n(2) Buscar por nombre.\nOpción: "; cin>>opc;
  
  if(opc == 1){

    cout<<"\nIngrese el número del canal: "; cin>>nroB;

     do{
        if(tempCEliminar->numero == nroB){
          encontrado = true;
          break;
        }
        tempCEliminar = tempCEliminar->sigC;

     }while(tempCEliminar != canales); 

  } else if(opc == 2){

    cout<<"\nIngrese el nombre del canal: "; cin.ignore(); cin.getline(nombreB, 20);
    
    do{
      if(strcmp(tempCEliminar->nombreC, nombreB) == 0){
        encontrado = true;
        break;
      }
      tempCEliminar = tempCEliminar->sigC;

   }while(tempCEliminar != canales);


  } else{cout<<"\nOpción invalida.\n"; return;}

  if(!encontrado){
    cout<<"\nCanal no encontrado.\n";
    return;
  }

  if(tempCEliminar->programas != NULL){

     tempP = tempCEliminar->programas;
     while(tempP != NULL){
        tempAux = tempP;
        tempP = tempP->sigP;
        delete tempAux;
     }
      tempCEliminar->programas = NULL;
      cout<<"\nProgramas del canal eliminados correctamente.\n";
  }

   if((tempCEliminar->antC == tempCEliminar) && (tempCEliminar->sigC == tempCEliminar)){  // Caso en el que sea el unico canal registrado.
     delete tempCEliminar;
     canales = NULL;
     cout<<"\nCanal eliminado correctamente.\n";
     return;
   } 
    
   if (tempCEliminar == canales) {                                    // Caso en el que sea el primer canal.
      canales = tempCEliminar->sigC;
    }                                                                
 
     tempCEliminar->antC->sigC = tempCEliminar->sigC;                 // Salta el if si es un canal intermedio o último.
     tempCEliminar->sigC->antC = tempCEliminar->antC;

   delete tempCEliminar;
   cout<<"\nCanal eliminado correctamente.\n";

}

/////////////////////////////////////////////////////////////////////////////////////
#define ESC 27
#define ENTER 13

void mostrarGuia(struct canal *&canales) {

    int cont = 0;

    if (canales == NULL) {
        cout<<"\nNo hay canales disponibles.\n";
        return;
    }

    struct canal *tempC = canales;
    struct programa *tempP = tempC->programas; 

    cout<<"\nMostrar guía.\n1) Flecha arriba, flecha abajo para moverse en los canales.\n2) Flecha izquierda, flecha derecha para moverse en los programas.";
    cout<<"\n3) Esc para volver.\n";

    cout<<"\n_______CANAL_________" << endl;
    cout<<"Número: "<<tempC->numero << endl;
    cout<<"Nombre: "<<tempC->nombreC << endl;

    int tecla = getch();

    while (tecla != ESC && tecla != ENTER) {

        switch (tecla) {

            case 72: // Sig canal
                    tempC = tempC->sigC; 
                    tempP = tempC->programas; 
                    cout<<"\nNúmero: "<<tempC->numero<<endl;
                    cout<<"Nombre: "<<tempC->nombreC<<endl;
                    cont = 0;
                
                break;

            case 80: // Ant canal
                    tempC = tempC->antC; 
                    tempP = tempC->programas; 
                    cout<<"\nNúmero: "<<tempC->numero<<endl;
                    cout<<"Nombre: "<<tempC->nombreC<<endl;
                    cont = 0;
                
                break;

            case 75: // Ant programa
               
                    if (tempP && tempP->antP) {
                        tempP = tempP->antP;
                       cout<<"\nFranja Horaria: "<<tempP->franjaHoraria<<":00"<<endl;
                       cout<<"Nombre: "<<tempP->nombreP<<endl;
                       cout<<"Clasificación: +"<<tempP->clasificacion<<endl;
                    }
                break;

            case 77: // Sig programa
             
                    if ((tempP) && (cont == 0)) { 

                       cout<<"\nFranja Horaria: "<<tempP->franjaHoraria<<":00"<<endl;
                       cout<<"Nombre: "<<tempP->nombreP<<endl;
                       cout<<"Clasificación: +"<<tempP->clasificacion<<endl;  
                       
                       if(tempP->sigP == NULL){ // Para el caso en el que se llegue al último programa
                        cont = 1;
                        break;
                       }
                       tempP = tempP->sigP;    
                    }
              break;

            default: break;
        }
        tecla = getch();
    }
}

/////////////////////////////////////////////////////////////////////////////////////

void mostrarPrueba(struct canal *&canales) {
  struct canal *temp = canales;

  if(canales == NULL) {
      cout << "\nNo hay canales registrados.\n";
      return;
  }

  do {
      cout<<"\n_______CANAL_________"<<endl;
      cout<<"Número: "<<temp->numero<<endl;
      cout<<"Nombre: "<<temp->nombreC<<endl;

      struct programa *tempP = temp->programas;
      while(tempP != NULL) {
          cout<<"______PROGRAMA_______"<<endl;
          cout<<"Franja horaria: "<<tempP->franjaHoraria<<":00"<<endl;
          cout<<"Nombre: "<<tempP->nombreP<<endl;
          cout<<"Clasificación: +"<<tempP->clasificacion<<endl;
          tempP = tempP->sigP;
      }

      temp = temp->sigC;

  } while(temp != canales);
}

/////////////////////////////////////////////////////////////////////////////////////

int main(){

    struct canal *canales = NULL;
    int opc;
    int nroCB;
    
    cout<<"\nBIENVENIDO A LEGÓN.\n";
    
    while(true){
  
    cout<<"\nMENÚ:\n1) Agregar canal.\n2) Agregar un programa a un canal.\n3) Consultar información de un canal.\n4) Eliminar un canal"; 
    cout<<"\n5) Eliminar todos los programas de un canal.\n6) Mostrar la guía de canales.\n7) Salir.\n\nIngrese una opción: ";  cin>>opc;
    
    switch(opc){
    
         case 1: {agregarCanal(canales); break;} 
  
         case 2: {cout<<"\nIngrese el numero del canal al que se le agregara el programa: "; cin>>nroCB; agregarPrograma(canales, nroCB); break;} //
  
         case 3: {mostrarInfC(canales); break;}
  
         case 4: {eliminarCanal(canales);break;}

         case 5: {eliminarP(canales); break;} 

         case 6: {mostrarGuia(canales); break;} 
  
         case 7: {cout<<"\nHasta luego.\n"; system ("pause"); return 0;} 

         case 8: {mostrarPrueba(canales);break;}
  
       default: {cout<<"Opción no valida."; break;}
  
      }
    }
  }

/*   
Estructura.

Función main.
 1) Agregar canales (lista doble circular) (número del canal, un nombre, una lista de programas).
    (Si se desea se pueden añadir programas) (ordenar según nro de canal) (NO CANALES REPETIDOS)

 2) Agregar un programa a un canal (lista doble no circular)
    (franja horaria -todos lo programas duran una hora, nombre, clasificación) (ordenar según franja horaria).
    (NO DOS PROGRAMAS A LA MISMA HORA)

 3) Consultar información de un canal (por nro o por nombre).

 4) Eliminar un canal de la guía (por nro o por el nombre). Borrado logico y del sistema por medio de delete, tener en cuenta la lista de programas, eliminar todos los programas.

 5) Eliminar todos los programas de un canal (por nro o por el nombre). Hacer el recorrido programa por programa, avanzando de nodo en nodo y eliminado el ant.

 6) Mostrar la guía de canales (por medio de las flechas del teclado) (información del canal (up, down) y su programación (left, right)).
 
 7) Salir

*/