#include <iostream>           // Jhon Mario Aguirre Correa
#include <fstream>
#include <cstring>

using namespace std;

struct registro {
    int id;
    char nombre[20];
    char apellido[20];
    int edad;
    char sexo;
    int celular;
    char fecha[26];
    struct registro *sig;
};


///////////////////////////////////////////////

void cargarDatosBinarios(struct registro *&raizA, struct registro *&finalA) {

    ifstream archivo("PersonasAtendidas.bin", ios::binary);    // Abrir archivo en modo binario

     if (!archivo.is_open()) {
         cout<<"Error al abrir el archivo.\n"; return;}

    while (true) {
        struct registro *nuevo = new registro;
        archivo.read(reinterpret_cast<char*>(nuevo), sizeof(struct registro));   // Leer un registro
 
        if (archivo.eof()) {      // Verificar si ya no hay más datos para leer
            delete nuevo;
            break;                // Salir si se alcanzó el final del archivo
         }

         if (raizA == NULL) {                 // Insertar en la lista enlazada
             raizA = nuevo;
             finalA = nuevo;
         } else {
             finalA->sig = nuevo;
             finalA = nuevo;
         }
        nuevo->sig = NULL;                // Asegurar que el último nodo apunte a NULL
    }

    archivo.close(); 
}


///////////////////////////////////////////////


void mostrarLA(struct registro *&raizA, struct registro *&finalA){

    struct registro *auxTemp = NULL;

    cout<<"\nPersonas atendidas:\n";
  
      while (raizA != NULL) {
        cout<<"Nombre: "<<raizA->nombre<<" - Id: "<<raizA->id<<" - Edad: "<<raizA->edad<<"  - Fecha: "<<raizA->fecha<<endl; 
        struct registro *temp = raizA; 
        raizA = raizA->sig; 
        temp->sig = auxTemp;                            // Apilar en la pila auxiliar
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

///////////////////////////////////////////////

void buscarID(struct registro *&raizA, struct registro *&finalA){

    struct registro *auxTemp = NULL;
    int id;
    bool encontrado = false;

    cout<<"\nIngrese el ID de la persona a buscar: "; cin>>id;
   

      while (raizA != NULL) {
        
       if(raizA->id == id){

        cout<<"\nPersona encontrada:\n";
        cout<<"Nombre: "<<raizA->nombre<<" - Id: "<<raizA->id<<" - Edad: "<<raizA->edad<<endl; 
        encontrado = true;
       }

        struct registro *temp = raizA; 
        raizA = raizA->sig; 
        temp->sig = auxTemp;                            // Apilar en la pila auxiliar
        auxTemp = temp;
      }
  
      while (auxTemp != NULL) {                          // Restaurar la pila original desde la auxiliar
        struct registro *temp = auxTemp;
        auxTemp = auxTemp->sig;
        temp->sig = raizA;
        raizA = temp;
      }

    if(encontrado == false){
       cout<<"\nPersona no encontrada.\n";
    }
}


///////////////////////////////////////////////

int main() {

    
    struct registro *raizA = NULL, *finalA = NULL;
    cargarDatosBinarios(raizA, finalA);

    int opc = 0;

  while(true){

    cout<<"\nMostrar registro de personas atendidas.\n";
    cout<<"Opciones:\n1) Mostrar listado.    2) Buscar por id.     3) Salir.\n";
    cout<<"Ingrese una opción: "; cin>>opc;

     switch (opc)
     {
     case 1: {mostrarLA(raizA, finalA); break;}

     case 2: {buscarID(raizA, finalA); break;}

     case 3: {
          
           while (raizA != NULL) {                     // Liberar la memoria al final
              struct registro *borrar = raizA;
              raizA = raizA->sig;
             delete borrar;
         }
          
        cout<<"\nHasta luego.\n"; system("pause"); return 0;}
    
     default: break;
     }
   }  

    return 0;
}


