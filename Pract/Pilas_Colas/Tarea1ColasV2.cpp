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

int cantidad(struct nodo *&raiz, struct nodo *&final) {
  if (raiz == NULL) {
      cout<<"\nLa cola está vacía."<<endl;
      return 0;
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

  return cont;
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


void insertarPN(struct nodo *&raiz, struct nodo *&final){

   int PN;
   struct nodo *nuevo = new(nodo);
   struct nodo *auxRaiz = NULL, *auxFinal = NULL; 
   struct nodo *temp = NULL;


   cout<<"\nIngrese la posición del nodo a agregar: "; cin>>PN;

   if(PN >(cantidad(raiz, final))){

       cout<<"\nPosición invalida.";
       return;
    }

   cout<<"Ingrese el valor del nuevo nodo: "; cin>>nuevo->info;
 
   if(PN == 1){                         // Caso en el que se ingrese en la primera posición (primero en ingresar) 
 
     nuevo->sig = raiz;
     raiz = nuevo;

   }else{

      for(int i=0; i< (PN - 1); i++){   // Pasar nodos anterior a una cola auxiliar
       temp = raiz;
       raiz = raiz->sig;
       temp->sig = NULL;

       if (auxRaiz == NULL) {
           auxRaiz = temp;
           auxFinal = temp;
       }else{
           auxFinal->sig = temp;
           auxFinal = temp;
       }
     }

      auxFinal->sig = nuevo;          // Conectar el nuevo nodo a la cola auxiliar
      auxFinal = nuevo;

      while(raiz != NULL){            // Pasar el resto de nodos a la cola auxiliar
 
        temp = raiz;
        raiz = raiz->sig;
        temp->sig = NULL;
 
       if (auxRaiz == NULL) {
           auxRaiz = temp;
           auxFinal = temp;
       }else{
           auxFinal->sig = temp;
           auxFinal = temp;
       }
      }

      raiz = auxRaiz;           // Restaurar la cola original desde la auxiliar
      final = auxFinal;
     }

   cout<<"El nodo "<<nuevo->info<<" a sido agregado correctamente en la posición "<<PN<<".";
}


// ________________________________________________________________________________________ 


void eliminarPN(struct nodo *&raiz, struct nodo *&final){  

    int PN;
    struct nodo *auxRaiz = NULL, *auxFinal = NULL; 
    struct nodo *temp = NULL;
    struct nodo *bor = NULL;
 
 
    cout<<"\nIngrese la posición del nodo a borrar: "; cin>>PN;
 
    if(PN >(cantidad(raiz, final))){
        cout<<"\nPosición invalida.";
        return;
     }
 
    
    if(PN == 1){                         // Caso en el que se elimine en la primera posición (primero en ingresar)
      bor = raiz;
      raiz = raiz->sig;

    }else{
 
       for(int i=0; i< (PN - 1); i++){  // Pasar nodos anteriores al nodo a eliminar a una cola auxiliar
         temp = raiz;
         raiz = raiz->sig;
         temp->sig = NULL;
 
        if (auxRaiz == NULL) {
            auxRaiz = temp;
            auxFinal = temp;
        }else{
            auxFinal->sig = temp;
            auxFinal = temp;
        }
      }
         
         bor = raiz;                   // Saltar el nodo que se va a eliminar
         raiz = raiz->sig;            
        
       while(raiz != NULL){            // Pasar el resto de nodos a la cola auxiliar
         temp = raiz;
         raiz = raiz->sig;
         temp->sig = NULL;
  
        if (auxRaiz == NULL) {
            auxRaiz = temp;
            auxFinal = temp;
        }else{
            auxFinal->sig = temp;
            auxFinal = temp;
        }
       }

       raiz = auxRaiz;           // Restaurar la cola original desde la auxiliar
       final = auxFinal;
      }
 
    cout<<"\nEl nodo "<<bor->info<<" en la posición "<<PN<<" ha sido elminado correctamente.";
    delete bor;
 }
 


// ________________________________________________________________________________________


int main(){

    int opc;
    struct nodo *raiz = NULL;
    struct nodo *final = NULL;

    while(true){
    cout<<"\nMENÚ COLAS\n";
    cout<<"\n1) Insertar nodo.\n2) Imprimir cola.\n3) Extraer (Sale el primero en llegar).\n4) Cantidad.\n5) Liberar (Vaciar cola).\n6) Ingresar en un posición especifica.";
    cout<<"\n7) Eliminar en una posición especifica.\n8) Salir\nIngrese una opción: "; cin>>opc;

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
        cout<<"La cantidad de nodos es: "<<cantidad(raiz, final);
        break;

    case 5:
        liberar(raiz);
        break;

    case 6:
        insertarPN(raiz, final);
        break;

    case 7:
        eliminarPN(raiz, final);
        break;

    case 8:
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