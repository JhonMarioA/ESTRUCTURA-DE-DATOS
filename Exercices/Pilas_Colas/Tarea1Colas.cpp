#include <iostream> // Jhon Mario Aguirre Correa
using namespace std;

struct nodo{

    int info;
    struct nodo *sig;
};



// ________________________________________________________________________________________

void insertarN(struct nodo *&raiz, struct nodo *&final)
{
    struct nodo *nuevo;
    nuevo = new(nodo);

    cout<<"Ingrese la información: "; cin>>nuevo->info;
    nuevo->sig=NULL;


    if (raiz == NULL)
    {
        raiz = nuevo;
        final = nuevo;
    }
    else
    {
        final->sig = nuevo;
        final = nuevo;
    }
}

// ________________________________________________________________________________________

void imprimirC(struct nodo *&raiz, struct nodo *&final) {
  if (raiz == NULL) {
      cout<<"La cola está vacía."<<endl;
      return;
  }

  struct nodo *auxRaiz = NULL, *auxFinal = NULL;
  struct nodo *temp;

  cout<<"Elementos de la cola: ";

  while (raiz != NULL) {
      cout<<raiz->info<<" ";

      // Mover nodo a la cola auxiliar
      temp = raiz;
      raiz = raiz->sig;
      temp->sig = NULL;

      if (auxRaiz == NULL) {
          auxRaiz = temp;
          auxFinal = temp;
      } else {
          auxFinal->sig = temp;
          auxFinal = temp;
      }
  }
  cout<<endl;

  // Restaurar la cola original desde la auxiliar
  raiz = auxRaiz;
  final = auxFinal;
}


// ________________________________________________________________________________________


void extraer(struct nodo *&raiz, struct nodo *&final){

 if(raiz == NULL){
   cout<<"\nLa cola esta vacia.";
   return;
 }

struct nodo *bor = raiz;

 if(raiz == final){
   cout<<"Se ha eliminado correctamente el nodo: "<<raiz->info;
   delete raiz;
   delete final;

 } else {

 raiz = raiz->sig;
 cout<<"Se ha eliminado correctamente el nodo: "<<bor->info;
 delete bor;
 }
}



// ________________________________________________________________________________________

void cantidad(struct nodo *&raiz, struct nodo *&final) {
  if (raiz == NULL) {
      cout<<"\nLa cola está vacía."<<endl;
      return;
  }
  
  int cont = 0;
  struct nodo *auxRaiz = NULL, *auxFinal = NULL;
  struct nodo *temp;


  while (raiz != NULL) {
      cont += 1;

      // Mover nodo a la cola auxiliar
      temp = raiz;
      raiz = raiz->sig;
      temp->sig = NULL;

      if (auxRaiz == NULL) {
          auxRaiz = temp;
          auxFinal = temp;
      } else {
          auxFinal->sig = temp;
          auxFinal = temp;
      }
  }

  // Restaurar la cola original desde la auxiliar
  raiz = auxRaiz;
  final = auxFinal;

  cout<<"\nLa cantidad de nodos es: "<<cont;
}

// ________________________________________________________________________________________

void liberar(struct nodo *&raiz){

  struct nodo *temp = raiz;

  while(temp != NULL){

    struct nodo *bor = temp;
    temp = temp->sig;
    delete bor;
  }

  raiz = NULL;
  cout<<"\nSe a liberado la cola.\n";
}

// ________________________________________________________________________________________

int main(){

    int opc;
    struct nodo *raiz = NULL;
    struct nodo *final = NULL;

    while(true){
    cout<<"\nMENÚ COLAS\n";
    cout<<"\n1) Insertar nodo.\n2) Imprimir cola.\n3) Extraer (Sale el primero en llegar).\n4) Cantidad.\n5) Liberar (Vaciar cola).\n6) Salir\nIngrese una opción: "; cin>>opc;

     switch(opc){

    case 1:
        insertarN(raiz, final);
        break;

    case 2:
        imprimirC(raiz, final);
        break;

    case 3:
        extraer(raiz, final);
        break;

    case 4:
        cantidad(raiz, final);
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