#include <iostream> // Jhon Mario Aguirre Correa
using namespace std;

struct nodo {
    int info;
    struct nodo *sig;
};


// ________________________________________________________________________________________

void insertarN(struct nodo *&raiz){

    struct nodo *nuevo = new(nodo);
    cout<<"Ingrese el int: "; cin>>nuevo->info;

    if(raiz == NULL){
        raiz = nuevo;
        raiz->sig = NULL;

    } else{
       nuevo->sig = raiz;
       raiz = nuevo;
      }
}

// ________________________________________________________________________________________

void imprimirP(struct nodo *&raiz) {

    if (raiz == NULL) {
        cout<<"La pila está vacía."<<endl;
        return;
    }

    struct nodo *auxTemp = NULL;
    
    
    while (raiz != NULL) {
        cout<<raiz->info<<" "; 
        struct nodo *temp = raiz; 
        raiz = raiz->sig; 
        temp->sig = auxTemp; // Apilar el nodo en la auxiliar
        auxTemp = temp;
    }

    cout<<endl;

    // Restaurar la pila original desde la auxiliar
    while (auxTemp != NULL) {
        struct nodo *temp = auxTemp;
        auxTemp = auxTemp->sig;
        temp->sig = raiz;
        raiz = temp;
    }
}

// ________________________________________________________________________________________

int extraer(struct nodo *&raiz) {              // Extraer el nodo superior de la pila 
    if (raiz == NULL) {
        cout<<"La pila está vacía."<<endl;
        return -1;
    }
    
    int informacion = raiz->info;
    struct nodo *bor = raiz;
    raiz = raiz->sig;
    delete bor;  // Liberar memoria correctamente
    return informacion;
}

// ________________________________________________________________________________________


void liberar(struct nodo *&raiz) {                                  // Liberar toda la pila
    struct nodo *reco = raiz;
    struct nodo *bor;

    if (raiz == NULL) {
        cout<<"La pila ya está vacía."<<endl;
        return;
    }

    while (reco != NULL) {
        bor = reco;
        reco = reco->sig;
        delete bor;  
    }
    raiz = NULL;
    cout<<"Pila liberada." <<endl;
}

// ________________________________________________________________________________________


int cantidad(struct nodo *&raiz) { // Contar los nodos de la pila 
    if (raiz == NULL) {
        return 0;
    }

    struct nodo *auxTemp = NULL;
    int contador = 0;

    // Pasar nodos a la pila auxiliar mientras contamos
    while (raiz != NULL) {
        contador++;
        struct nodo *temp = raiz;
        raiz = raiz->sig;
        temp->sig = auxTemp;
        auxTemp = temp;
    }

    // Restaurar la pila original desde la auxiliar
    while (auxTemp != NULL) {
        struct nodo *temp = auxTemp;
        auxTemp = auxTemp->sig;
        temp->sig = raiz;
        raiz = temp;
    }

    return contador;
}


// ________________________________________________________________________________________

int main(){

    int opc;
    struct nodo *raiz = NULL;

    while(true){
    cout<<"MENÚ PILAS\n";
    cout<<"1) Insertar nodo.\n2) Imprimir pila.\n3) Extraer (Sale último nodo en llegar).\n4) Cantidad.\n5) Liberar (Vaciar pila).\n6) Salir\nIngrese una opción: "; cin>>opc;

     switch(opc){

    case 1:
        insertarN(raiz);
        break;

    case 2:
        imprimirP(raiz);
        break;

    case 3:
        cout<<"Elemento extraído: "<<extraer(raiz)<<endl;
        break;

    case 4:
        cout<<"Cantidad de nodos en la pila: "<<cantidad(raiz)<<endl;
        break;

    case 5:
        liberar(raiz);
        break;

    case 6:
        liberar(raiz);
        cout<<"\nHasta luego.\n";
        system("pause");
        return 0;

    default:
        cout<<"Opción no válida.\n";
        break;

    }
   }
  }

