#include <iostream>
#include <string.h>   // para strcmp, strcat
#include <cctype>    // para tolower()
using namespace std;


struct nodo{

 char palabra[20];
 char significado[50];
 char categoriaG[20];
 char sinonimos[50];

 struct nodo *izq;
 struct nodo *der;

};


///////////////////////////////////////////////////////////////////////////// 
 
nodo* encontrarP(struct nodo *&raiz, const char *palabraB){                               // Función aux para hallar una palabra, devuelve la dir del nodo

    struct nodo *temp = raiz;
 
      while(temp != NULL){
 
          int val = strcmp(palabraB, temp->palabra);
 
          if(val == 0){                // Caso en el que se encuentre
              return temp;
          }
 
          if(val < 0){                 // Si la palabra a buscar es menor al nodo
 
              temp = temp->izq;
 
           } else if(val > 0){         // Si la palabra a buscar es mayor al nodo
 
             temp = temp->der;
           }
      }
     return NULL;   
 }

/////////////////////////////////////////////////////////////////////////////

nodo* encontrarAnt(struct nodo *&raiz, const char *palabraB){                          // Función aux para hallar el padre (nodo anterior) al de una palabra

   
  struct nodo *temp = raiz;
  struct nodo *ant = NULL;
 
  while(temp != NULL){

      int val = strcmp(palabraB, temp->palabra);

      if(val == 0){                // Caso en el que se encuentre
          return ant;
      }

      ant = temp;

      if(val < 0){                 // Si la palabra a buscar es menor al nodo

          temp = temp->izq;

       } else if(val > 0){         // Si la palabra a buscar es mayor al nodo

         temp = temp->der;
       }
  }
 return NULL; 

}

/////////////////////////////////////////////////////////////////////////////    // Función aux para agregar sinónimos

void sinonimos(struct nodo *&nuevaPalabra){

     nuevaPalabra->sinonimos[0] = '\0';                  // Se inicia la cadena vacía
   
     char sin[20];
     int cont = 0;


     while(cont < 3){

        cout<<"\nIngrese hasta tres sinónimos (escriba '-' para finalizar antes).";    // Si se desea agregar menos de 3 sinónimos se pone '-'
        cout<<"\nSinonimo "<<cont+1<<": "; cin.getline(sin, 20);

        if(strcmp(sin, "-") == 0) break;
 
        if(cont > 0) (strcat(nuevaPalabra->sinonimos, ", "));                          // Separar con ','
        strcat(nuevaPalabra->sinonimos, sin);                                          // Concatenamos el char aux al char original
        cont++;

     }
}



/////////////////////////////////////////////////////////////////////////////           

void agregarPalabra(struct nodo *&raiz){

   struct nodo *nuevaPalabra = new nodo;
   struct nodo *temp = raiz;
   bool rai = false;
  
  
   cout<<"Ingrese la nueva palabra: "; cin>>nuevaPalabra->palabra;
   
     if(raiz == NULL){                                                 // Caso en el que sea la primera palabra

       raiz = nuevaPalabra;
       raiz->izq = raiz->der = NULL; 
       rai = true;


      } else if(encontrarP(raiz, nuevaPalabra->palabra) != NULL){            // Verificar que no exista la palabra

          cout<<"\nError, la palabra ya existe.\n";
          delete nuevaPalabra;
          return;
        }


    cout<<"\nIngrese la siguiente información: \n1) Significado: "; cin.ignore(); cin.getline(nuevaPalabra->significado, 50);
    cout<<"2) Categoría gramatical: "; cin.getline(nuevaPalabra->categoriaG, 20);
    cout<<"3) Sinonimos: "; sinonimos(nuevaPalabra);


     while(rai != true){

        if(strcmp(nuevaPalabra->palabra, temp->palabra) < 0){           // Caso en el que la nueva palabra sea menor a la palabra de nodo

           if(temp->izq == NULL){                                       // Se inserta si es valido hacerlo (NULL)

                temp->izq = nuevaPalabra;
                cout<<"\nPalabra agregada correctamente.\n";
                return;
            }
           temp = temp->izq;                                            // Sino, nos movemos un nodo

        } else if (strcmp(nuevaPalabra->palabra, temp->palabra) > 0){   // Caso en el que la nueva palabra sea mayor a la palabra de nodo

             if(temp->der == NULL){                                     // Se inserta si es valido hacerlo (NULL)

                temp->der = nuevaPalabra;
                cout<<"\nPalabra agregada correctamente.\n";
                 return;
              }
            temp = temp->der;                                           // Sino, nos movemos un nodo
          }

     }

}




///////////////////////////////////////////////////////////////////////////// 


void modificarE(struct nodo *&raiz){

    char  palabraB[20];
    int opc;
    struct nodo *palabra = NULL;

    cout<<"Ingrese la palabra: "; cin>>palabraB; 
 
    palabra = encontrarP(raiz, palabraB);

    if(palabra == NULL){
        cout<<"\nPalabra no encontrada.\n";

    } else{

        cout<<"\nModificar:\n1) Significado\n2) Categoría gramatica\n3) Sinónimos.\nOpc: "; cin>>opc;  cin.ignore(); 

        switch (opc)
        {
          case 1: {cout<<"\nPalabra: "<<palabra->palabra<<".\nSignificado actual: "<<palabra->significado<<"\nIngrese el nuevo significado: ";
                  cin.getline(palabra->significado, 50);  cout<<"\nElemento actualizado correctamente.\n"; break;}  

          case 2: {cout<<"\nPalabra: "<<palabra->palabra<<".\nCategoría gramatical actual: "<<palabra->categoriaG<<"\nIngrese la nueva categoría: ";
                  cin.getline(palabra->categoriaG, 20); cout<<"\nElemento actualizado correctamente.\n"; break;}  

          case 3: {cout<<"\nPalabra: "<<palabra->palabra<<".\nSinonimos actuales "<<palabra->sinonimos<<"\nIngrese los nuevos sinonimos: ";
                   sinonimos(palabra); cout<<"\nElemento actualizado correctamente.\n"; break;} 
        
          default: {cout<<"\nOpción invalida.\n"; return;}

        }
    }
}


/////////////////////////////////////////////////////////////////////////////

void mostrarE(struct nodo *raiz){

   char palabraB[20];
   cout<<"\nIngrese la palabra: "; cin>>palabraB;

    struct nodo *palabra = encontrarP(raiz, palabraB);

   if(palabra == NULL){
     cout<<"\nPalabra no encontrada.\n";
     return;

   } else {

     cout<<"\nElementos de la palabra ("<<palabra->palabra<<"):\n1) Significado: "<<palabra->significado<<"\n2) Categoría gramatical: "<<palabra->categoriaG;
     cout<<"\n3) Sinonimos: "<<palabra->sinonimos<<endl<<endl; return;

   }
}

/////////////////////////////////////////////////////////////////////////////

void eliminarP(struct nodo *&raiz){                                                //  PENDIENTE (Revisar caso en el que se elimine la raíz)

   char palabraB[20];

   cout<<"\nIngrese la palabra a eliminar: "; cin>>palabraB; 

   struct nodo *palabra = encontrarP(raiz, palabraB);

    if(palabra == NULL){        
       cout<<"\nLa palabra no se ha encontrado.\n";
       return;
    }

    struct nodo *ant = encontrarAnt(raiz, palabraB);


    if(palabra->izq == NULL && palabra->der == NULL){                                // Caso en el que el nodo no tenga hijos

       cout<<"\nLa palabra ("<<palabra->palabra<<") se ha eliminado correctamente.";

        if(ant->izq == palabra){

          ant->izq = NULL;

         } else if(ant->der == palabra){

           ant->der = NULL;
         }

       delete palabra;

    } else if (palabra->izq != NULL && palabra->der != NULL){                       // Caso en el que el nodo tengo dos hijos


                                                                                    // PENDIENTE

      

    } else if(palabra->izq != NULL){                                                // Caso en el que el nodo tenga un hijo por la izq

       if(ant->izq == palabra){

         ant->izq = palabra->izq;
         cout<<"\nLa palabra ("<<palabra->palabra<<") se ha eliminado correctamente.";
         delete palabra;
      
       } else if(palabra->der != NULL){

        ant->der = palabra->izq;
        cout<<"\nLa palabra ("<<palabra->palabra<<") se ha eliminado correctamente.";
        delete palabra;
       }


    } else if(palabra->der != NULL){                                                // Caso en el que el nodo tenga un hijo por la der

      if(ant->izq == palabra){

        ant->izq = palabra->der;
        cout<<"\nLa palabra ("<<palabra->palabra<<") se ha eliminado correctamente.";
        delete palabra;
     
      } else if(palabra->der != NULL){

       ant->der = palabra->der;
       cout<<"\nLa palabra ("<<palabra->palabra<<") se ha eliminado correctamente.";
       delete palabra;
      }

    }
   
}

/////////////////////////////////////////////////////////////////////////////     


void listCG(struct nodo *raiz, const char *categoriaB){

  if (raiz == NULL) {
      return;}

  listCG(raiz->izq, categoriaB);       // 1. Visitar subárbol izquierdo
  if (strcmp(raiz->categoriaG, categoriaB) == 0) cout<<endl<<"- "<<raiz->palabra;
  listCG(raiz->der, categoriaB);       // 3. Visitar subárbol derecho

}

/////////////////////////////////////////////////////////////////////////////

void listL(struct nodo *raiz, char letraB){ 

  if (raiz == NULL) {
    return;}

  listL(raiz->izq, letraB);       // 1. Visitar subárbol izquierdo
  if (tolower(raiz->palabra[0]) == tolower(letraB)) cout<<endl<<"- "<<raiz->palabra;      // Accediendo a la primer letra por medio del indice, y pasando a minusculas
  listL(raiz->der, letraB);       // 3. Visitar subárbol derecho

}

/////////////////////////////////////////////////////////////////////////////


int main(){
    
    int opc;
    char categoriaB[20];
    struct nodo *raiz = NULL;
    char letraB = '\0';

  while(true){
    
    cout<<"\nMENÚ DICCIONARIO\n\nOpciones:\n1) Agregar palabra.\n2) Modificar elementos de una palabra.\n3) Mostrar elementos de una palabra.\n4) Eliminar palabra.";
    cout<<"\n5) Listado de palabras por categoría gramatical.\n6) Listado de palabras por letra.\n10) Salir.\n";

    cout<<"\nIngrese una opción: "; cin>>opc;

    switch (opc){

     case 1: {cout<<"\n(1) Agregar palabra.\n"; agregarPalabra(raiz); break;}
 
     case 2: {cout<<"\n(2) Modificar elementos de una palabra.\n"; modificarE(raiz); break;}

     case 3: {cout<<"\n(3) Mostrar elementos de una palabra.\n"; mostrarE(raiz); break;}

     case 4: {cout<<"\n(4) Eliminar una palabra.\n"; eliminarP(raiz); break;}

     case 5: {cout<<"\n(5) Listado de palabras por categoría gramatical.\n"; cout<<"\nIngrese la categoría gramatical a buscar: "; cin.ignore(); cin.getline(categoriaB, 20);
              cout<<"\nListado de palabras en la categoría "<<categoriaB<<":\n"; listCG(raiz, categoriaB); cout<<endl; break;}

     case 6: {cout<<"\n(6) Listado de palabras por letra.\n"; cout<<"\nIngrese la letra a buscar: "; cin.ignore(); cin>>letraB;
              cout<<"\nListado de palabras por la letra "<<letraB<<":\n";  listL(raiz, letraB); cout<<endl; break;}

     case 10: {cout<<"\nHasta luego.\n"; return 0;}

    default: cout<<"Opción no valida."; break;

  }
 } 
}


