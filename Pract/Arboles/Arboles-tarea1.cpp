#include <iostream>    // Jhon Mario Aguirre Correa
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

#include <iomanip>

void dibujarA(struct nodo *raiz) {
    if (raiz == NULL) {
        cout<<"El arbol esta vacio."<< endl;
        return;
    }

    // Función auxiliar para calcular la altura del árbol
    auto altura = [](nodo* n, auto&& altura) -> int {
        if (n == NULL) return 0;
        return 1 + max(altura(n->izq, altura), altura(n->der, altura));
    };

    // Función recursiva para imprimir el árbol
    auto imprimirNivel = [](nodo* nodo, int nivel, int espaciado, auto&& imprimirNivel) {
        if (nodo == NULL) {
            cout<<setw(espaciado)<<" ";
            return;
        }
        if (nivel == 1) {
            cout << setw(espaciado) << nodo->inf;
        } else if (nivel > 1) {
            imprimirNivel(nodo->izq, nivel - 1, espaciado, imprimirNivel);
            cout<<setw(espaciado) << " ";
            imprimirNivel(nodo->der, nivel - 1, espaciado, imprimirNivel);
        }
    };

    int h = altura(raiz, altura);
    int espaciado = 4; // Ajusta este valor para cambiar el espaciado entre nodos

    for (int i = 1; i <= h; i++) {
        imprimirNivel(raiz, i, espaciado * (h - i + 1), imprimirNivel);
        cout<<endl<<endl;
    }
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

     case 3: cout<<"\n(3) Dibujar árbol.\n"; dibujarA(raiz); break;
 
     case 4: cout<<"\nHasta luego.\n"; break;

    default: cout<<"Opción no valida."; break;

  }
 } 
}
