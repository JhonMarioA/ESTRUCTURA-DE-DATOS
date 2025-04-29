#include <iostream>
using namespace std;


struct nodo{

    int inf;
    struct nodo *izq;
    struct nodo *der;
};



///////////////////////////////////////////////////////////////////////////////

void agregarNodo(struct nodo *&raiz){

    int opc;

    struct nodo *nuevo = new(nodo); nuevo->izq = NULL; nuevo->der = NULL; 
    struct nodo *temp = raiz;

    cout<<"\nIngrese por favor la inf del nodo a agregar: "; cin>>nuevo->inf; 

    if(raiz == NULL){                                // Caso en el que sea el primer nodo del arbol
        raiz = nuevo;
        cout<<"\nNodo agregado correctamente.\n";
        return;
    }

 while(true){

    cout<<"\n(1) Ingresar nodo en el sub arbol izquierdo.\n(2) Ingresar nodo en el sub arbol derecho.\n Opc: "; cin>>opc;


     if(opc == 1){                                    // Caso en el que desee agregar a la izquierda
 
        if(temp->izq == NULL){                        // En el caso de que ya sea correcto agregar, es decir en su sig es NULL

         temp->izq = nuevo;
         cout<<"\nNodo agregado correctamente.\n";
         return;
        }

        temp = temp->izq;

      } else if(opc == 2){                            // Caso en el que se desee agregar a la derecha

         if(temp->der == NULL){                       // En el caso de que ya sea correcto agregar, es decir en su sig es NULL

             temp->der = nuevo;
             cout<<"\nNodo agregado correctamente.\n";
             return;
            }

            temp = temp->der;

      } else {cout<<"\nOpción invalida.\n"; return;}
   }
}


//////////////////////////////////////////////////////////////////////////////////////

void inorden(struct nodo *raiz) {
  if (raiz == NULL) {
      return;
  }

  inorden(raiz->izq);       // 1. Visitar subárbol izquierdo
  cout<< raiz->inf << " "; // 2. Visitar el nodo actual
  inorden(raiz->der);       // 3. Visitar subárbol derecho
}


//////////////////////////////////////////////////////////////////////////////////////



int main(){
    
    int opc;
    struct nodo *raiz = NULL;

  while(true){
    
    cout<<"\nMENÚ\nOpciones:\n1) Agregar nodo.\n2) Mostrar contenido (In-order).\n3) Dibujar el árbol.\n4) Salir.\n";
    cout<<"\nIngrese una opción: "; cin>>opc;

    switch (opc){

     case 1: cout<<"\n(1) Agregar nodo.\n"; agregarNodo(raiz); break;

     case 2: cout<<"\n(2) Añadir nodo.\n"; inorden(raiz); break;

     case 3: cout<<"\n(3) Añadir nodo.\n"; break;
 
     case 4: cout<<"\nHasta luego.\n"; break;

    default: cout<<"Opción no valida."; break;

  }
 } 
}
