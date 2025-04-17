// EPS         // Jhon Mario Aguirre Correa

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>

using namespace std;


struct registro{

int id;
char nombre[20];
char apellido[20];
int edad;
char sexo;
int celular;
char fecha[26];
struct registro *sig;

};


////////////////////////////////////////////

const char* fecha() {              // Función que devuelve la fecha (cadena estatica)       
  time_t t;
  time(&t);
  return ctime(&t);  
}

////////////////////////////////////////////

bool vacia(struct registro *&raiz){       // Si la cola esta vacia = 1

  if(raiz == NULL){
    return 1;
  } else {return 0;}
}

////////////////////////////////////////////

bool encontrado(struct registro *&raiz, struct registro *&final, int id){   // Función para verifica si existe alguien

  struct registro *auxRaiz = NULL, *auxFinal = NULL;
  struct registro *temp; bool enc = 0;

  while (raiz != NULL) {
   
    if(id == raiz->id){
       enc = 1;
    }

    temp = raiz;                          // Mover nodo a la cola auxiliar
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
    
  raiz = auxRaiz;                         // Restaurar la cola original desde la auxiliar
  final = auxFinal;

 return enc;
}

////////////////////////////////////////////

void registrar(struct registro *&raiz, struct registro *&final, int edad){

    struct registro *nuevo = new(registro);
   
      cout<<"\nPor favor ingrese la siguiente información:\n";
      cout<<"\nId: "; cin>>nuevo->id;

         if(encontrado(raiz, final, nuevo->id)){
            cout<<"\nLa persona con este ID ya existe en la cola.\n"; return;}

      cout<<"Nombre: "; cin.ignore(); cin.getline(nuevo->nombre, 20);
      cout<<"Apellido: "; cin.getline(nuevo->apellido, 20);
      nuevo->edad = edad;;
      cout<<"Sexo (M - F): "; cin>>nuevo->sexo;
      cout<<"Celular: "; cin>>nuevo->celular;
    
      nuevo->sig = NULL;

        if (raiz == NULL)
         {raiz = nuevo; final = nuevo;}

        else
         {final->sig = nuevo; final = nuevo;}

      cout<<"\nPersona registrada correctamente.\n";
}

////////////////////////////////////////////

void sigTurno(struct registro *&raiz, struct registro *&final, struct registro *&raizA){

    struct registro *atender = NULL;

    atender = raiz;                  // El siguiente turno será el primero de la cola en el momento.
    raiz = raiz->sig;

    if(raizA == NULL){              // Enviando el turno atendido a la pila.
        raizA = atender;
        raizA->sig = NULL;

    } else
      {atender->sig = raizA;
       raizA = atender;}

     cout<<"\nSiguiente turno:\nId: "<<atender->id<<"  Nombre: "<<atender->nombre<<" Edad: "<<atender->edad<<endl;

}




////////////////////////////////////////////

void mostrarA(struct registro *raizA){

  struct registro *auxTemp = NULL;

  if(vacia(raizA)){
    cout<<"\nAún no se han atendido personas.\n";
    return;
  }

  cout<<"\nPersonas atendidas:\n";

    while (raizA != NULL) {
      cout<<"Nombre: "<<raizA->nombre<<" - Id: "<<raizA->id<<" - Edad: "<<raizA->edad<<endl; 
      struct registro *temp = raizA; 
      raizA = raizA->sig; 
      temp->sig = auxTemp;                             // Apilar en la pila en la auxiliar
      auxTemp = temp;
    }

    cout<<endl;

    while (auxTemp != NULL) {                          // Restaurar la pila original desde la auxiliar
      struct registro *temp = auxTemp;
      auxTemp = auxTemp->sig;
      temp->sig = raizA;
      raizA = temp;
    }
}

////////////////////////////////////////////


void liberar(struct registro *&raiz){                 

   struct registro *borrar = NULL;

   while(raiz != NULL){

     borrar = raiz;
     raiz = raiz->sig;
     delete borrar;
   }
}

////////////////////////////////////////////

void retirarP(struct registro *&raiz, struct registro *&final, int id){      

  struct registro *raizAux = NULL; struct registro *finalAux = NULL;
  struct registro *temp = NULL;
  struct registro *retirar = NULL;

  while(raiz != NULL){

    temp = raiz;

    if(temp->id == id){                      // Encontramos el turno a retirar.
       retirar = raiz;
       raiz = raiz->sig;
       
    } else {

       temp = raiz;
       raiz = raiz->sig;

       if(raizAux == NULL){
           raizAux = temp;
           finalAux = temp;
        
        } else {
           finalAux->sig = temp;
           finalAux = temp;  
          }
      }
  } 

      raiz = raizAux;                          // Volvemos a la cola original sin el turno a retirar.

      if (raizAux == NULL)                     // Caso en el que se elimine el último nodo.
         final = NULL;
      else
         final = finalAux;

       delete retirar;
       cout<<"\nPersona con id "<<id<<" retirada correctamente.\n";
}


////////////////////////////////////////////

void guardarInfA(struct registro *&raizA){                          

  ofstream archivo("PersonasAtendidas.bin", ios::binary | ios::app);

  if(!archivo.is_open()) {
      cout<<"\nError al intentar abrir el archivo."<<endl;
      return;
  }

   const char* fechaA = fecha();              // Obtenemos la fecha

 while (raizA != NULL) {
    strcpy(raizA->fecha, fechaA);             // Copiar la fecha antes de guardar

    archivo.write(reinterpret_cast<const char*>(raizA), sizeof(struct registro));

    struct registro *temp = raizA;
    raizA = raizA->sig;
    delete temp;
}

  archivo.close();
}


////////////////////////////////////////////


int main(){

    int opc;
    int cont1=1, cont2=1, cont3=1;
    int edad;
    int id;
    

    struct registro *raiz1 = NULL, *final1 = NULL;        // Cola para mayores de 50 años
    struct registro *raiz2 = NULL, *final2 = NULL;        // Cola para personas mayores a 40 años y menores o iguales a 55 años.
    struct registro *raiz3 = NULL, *final3 = NULL;        // Cola para personas igual o menores a 40 años.
    struct registro *raizA = NULL;

    while(true){
    cout<<"\nMENÚ\n";
    cout<<"\n1) Registrar.\n2) Mostrar siguiente turno.\n3) Retirar persona de la cola.\n4) Consultar listado de personas atendidas.";
    cout<<"\n5) Salir\nIngrese una opción: "; cin>>opc;

     switch(opc){

     case 1:{cout<<"\nPor favor ingrese la edad: "; cin>>edad;

        if(edad > 50){

            registrar(raiz1, final1, edad); 
           
        }else if(edad > 40 && edad <= 55){

            registrar(raiz2, final2, edad); 
            
          }else{

             registrar(raiz3, final3, edad); 
            }

         break;}

     case 2:{
     
      bool vac1 = vacia(raiz1);
      bool vac2 = vacia(raiz2);
      bool vac3 = vacia(raiz3);

      if(vac1 && vac2 && vac3){
        cout<<"\nNo hay personas en la cola.\n";
        break;}

      if(cont1 <= 3 && vac1){    // Caso en el que cont1 (prioridad alta) sea menor o igual a 3 pero este vacia.
        cont1 = 4;}
 
      if(cont2 <= 2 && vac2){    // Caso en el que cont2 (prioridad media) sea menor o igual a 2 pero este vacia.
        cont2 = 3;}

      if(cont3 <= 1 && vac3){   // Caso en el que cont2 (prioridad media) sea menor o igual a 1 pero este vacia.
        cont3 = 2;}


     if(cont1 <= 3){                           // Tres turnos para la cola 1

        sigTurno(raiz1, final1, raizA); 
        cont1 += 1;
        cont3 = 1;
        break;
     
        } else if(cont2 <= 2){                   // Dos turnos para la cola 2          

            sigTurno(raiz2, final2, raizA); 
            cont2 += 1;
            break;

         } else if(cont3 == 1){                  // Un turno para la cola 3

             sigTurno(raiz3, final3, raizA); 
             cont3 += 1;                         
             cont1 = 1;                          // Reiniciar contadores
             cont2 = 1;
             break;
          } 
     
        }
      case 3: {cout<<"\nIngrese el ID de la persona a retirar: "; cin>>id;             //////////////////////

        if(encontrado(raiz1, final1, id)){

           retirarP(raiz1, final1, id);
           break;

          } else if(encontrado(raiz2, final2, id)){

             retirarP(raiz2, final2, id);
             break;

           } else if(encontrado(raiz3, final3, id)){

             retirarP(raiz3, final3, id);
             break;

            } else {
              cout<<"\nLa persona a retirar no está en la cola.\n";
              break;
             }
          }
  
      case 4: {mostrarA(raizA); break;}

      case 5: {
        
        if((vacia(raiz1) && vacia(raiz2) && vacia(raiz3))){             // Verificar que esten vacias las colas.
              
              guardarInfA(raizA);                                       // Guardar el registro de atendidos.         

              liberar(raiz1); liberar(raiz2); liberar(raiz3); liberar(raizA);          // Liberar memoria.
              cout<<"\nHasta luego.\n"; system("pause"); return 0;

        } else {
          cout<<"\nAún no se han atendido todos los turnos.\n"; break;}
        }

     default: {cout<<"Opción no válida.\n"; break;}

    }
   }
  }