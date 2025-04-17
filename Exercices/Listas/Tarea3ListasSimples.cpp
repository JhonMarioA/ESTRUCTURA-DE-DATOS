#include <iostream> //JHON MARIO AGUIRRE CORREA // 
#include <cstring>
using namespace std;


////////////////////////////////////////////////////////////////////////////////

struct vehiculo{
    char placa [7];
    char marca [20];
    char modelo [20];
    int año;
    char color[20];
    char tipo;
    long valor;
    char estado;
    
    struct hojaDeVida *hoja; // Para enlazar la lista hoja de vida
    struct vehiculo *sig;
};


////////////////////////////////////////////////////////////////////////////////

struct hojaDeVida{
    
    char inf[200];
    struct hojaDeVida *sigH;

}; 

//////////////////////////////////////////////////////////////////////////////// 

void agregarInfoH(struct vehiculo *&primero, const char *placaB){
    struct hojaDeVida *nuevoH = new struct hojaDeVida;

    cout << "\nIngrese la información del vehículo:\n";
    cin.ignore();
    cin.getline(nuevoH->inf, 200);
    nuevoH->sigH = NULL;

    struct vehiculo *temp = primero;
    
    // Buscar el vehículo por su placa
    while (temp != NULL) {
        if (strcmp(temp->placa, placaB) == 0) {
            break;
        }
        temp = temp->sig;
    }

    // Si no se encontró el vehículo
    if (temp == NULL) {
        cout << "\nNo se encontró un vehículo con esa placa.\n";
        delete nuevoH;
        return;
    }

    // Agregar la hoja de vida a la lista del vehículo
    if (temp->hoja == NULL) {
        temp->hoja = nuevoH;
    } else {
        struct hojaDeVida *tempH = temp->hoja;
        while (tempH->sigH != NULL) {
            tempH = tempH->sigH;
        }
        tempH->sigH = nuevoH;
    }
}




////////////////////////////////////////////////////////////////////////////////

void registrarV(struct vehiculo *&primero){
    
    
    cout<<"\n1. Registrar vehículos.\n";
    
    struct vehiculo *nuevo = new struct vehiculo;
    
    if (primero == NULL) {                                                 ///// 
        primero = nuevo;
        
    } else {
    struct vehiculo *temp = primero;
    while (temp->sig != NULL) { // Moverse al último nodo
        temp = temp->sig;
   }
    temp->sig = nuevo;
  }
    nuevo->sig = NULL;    
    nuevo->hoja = NULL;                                                  /////

    cout<<"\nIngrese la siguiente información del vehiculo:\n";
    cout<<"1. Placa: "; cin.ignore(); cin.getline(nuevo->placa, 7);
    cout<<"2. Marca: "; cin.getline(nuevo->marca, 20);
    cout<<"3. Modelo: "; cin.getline(nuevo->modelo, 20);
    cout<<"4. Año: "; cin>>nuevo->año;
    cout<<"5. Color: "; cin.ignore(); cin.getline(nuevo->color, 20);
    cout<<"6. Tipo (P-propio, C-consignado): "; cin>>nuevo->tipo;
    cin.ignore();
    cout<<"7. Valor: "; cin>>nuevo->valor;
    cout<<"8. Estado (A-activo, E-eliminado): "; cin>>nuevo->estado;
    cin.ignore();
    
    int opc;
    
    while(true){
        
    cout<<"\n¿Desea ingresar información a la hoja de vida (1-Si, 2-No)?: \n"; cin>>opc;
    
    if(opc==1){
        
        agregarInfoH(primero, nuevo->placa);
        return;
        
    } else if(opc==2){
        
        return;
        
    } else{ cout<<"\nOpción no valida.\n";}
    
  }
}



////////////////////////////////////////////////////////////////////////////////

void mostrarDatos(const struct vehiculo *temp){
    
    cout<<"\n1. Placa: "<<temp->placa;
    cout<<"\n2. Marca: "<<temp->marca;
    cout<<"\n3. Modelo: "<<temp->modelo;
    cout<<"\n4. Año: "<<temp->año;
    cout<<"\n5. Color: "<<temp->color;
    cout<<"\n6. Tipo (P-propio, C-consignado): "<<temp->tipo;
    cout<<"\n7. Valor: "<<temp->valor;
    cout<<"\n8. Estado (A-activo, E-eliminado): "<<temp->estado;

          // Buscar hojas de vida en la lista del vehículo
        bool tieneHoja = false;
        struct hojaDeVida *hojaTemp = temp->hoja; // Acceder a las hojas de vida del vehículo actual
        cout<<"\n9. Información, hoja de vida:\n";
        while (hojaTemp) {
        cout<< "- "<<hojaTemp->inf<<endl;
        tieneHoja = true;
        hojaTemp = hojaTemp->sigH;
        }

       if (!tieneHoja) {
       cout<<"No tiene información registrada.\n";
       }
       
       return;
}




////////////////////////////////////////////////////////////////////////////////

void consultarVEspe(struct vehiculo *primero){
    
    int opc;
    char marcaB[20];
    int precioMin, precioMax; 
    int tipoB;
    
    struct vehiculo *temp = primero;
    
    if (primero == NULL) {
    cout<<"\nNo hay vehículos registrados.\n";
    return;
    }
    
    while(true){
        
     cout<<"\n3. Consultar vehiculos\n";
     
     cout<<"1) Consultar vehiculos por marca.\n";
     cout<<"2) Consultar vehiculos por rango de precio.\n";
     cout<<"3) Consultar vehiculos por tipo.\n";
     cout<<"Ingrese una opción: "; cin>>opc;
     
     switch(opc){
         
         case 1: { 
             
             cout<<"\nIngrese la marca a buscar: "; cin.ignore(); cin.getline(marcaB, 20);
             temp = primero;
             
             while(temp != NULL){
                 
                 if(strcmp(temp->marca, marcaB)==0 && temp->estado == 'A' ){
                     
                    mostrarDatos(temp);
          
                   cout<<"\n------------------------------------\n";  
           }
        temp = temp->sig;
     }
             
            return;}
             
             
        
         case 2: {
             
             cout<<"\nIngrese el precio minimo: "; cin>>precioMin;
             cout<<"\nIngrese el precio maximo: "; cin>>precioMax;
             temp = primero;
             
             while(temp != NULL){
                 
                 if(temp->valor >= precioMin && temp->valor <= precioMax && temp->estado == 'A'){
                     
                          mostrarDatos(temp);
          
                    cout<<"\n------------------------------------\n";  
                    
         }
           temp = temp->sig;  
     }
     return;}
             
             
         
         case 3: {
             
             cout<<"\nIngrese el tipo a buscar (1. P-propio, 2. C-consignado): "; cin>>tipoB;
             temp = primero;
             
             
             if(tipoB == 1){
             
             while(temp != NULL){
                 
                 if(temp->tipo == 'P' && temp->estado == 'A'){
                     
                      mostrarDatos(temp);
                      
                     cout<<"\n------------------------------------\n";  
           }
        temp = temp->sig;
      }
             
             return;}
             
             
             else if(tipoB == 2){
                
                 
                   while(temp != NULL){
                 
                 if(temp->tipo == 'C' && temp->estado == 'A'){
                     
                      mostrarDatos(temp);
                      cout<<"\n------------------------------------\n";}
                     
                      temp = temp->sig;}
                      
                  return;}
             
    cout<<"\nOpción invalida.\n"; return;}
             
            default: {cout<<"\nOpción invalida.\n"; break;} 
         }
       }
     }




////////////////////////////////////////////////////////////////////////////////

void modificarVvt(struct vehiculo *&primero){
    
    int opc;
    char placaB[7];
    struct vehiculo *temp = primero;
    long nuevoValor;
    char nuevoTipo;
    bool encontrado = false;
    
    if (primero == NULL) {
    cout<<"\nNo hay vehículos registrados.\n";
    return;
    }
    
    cout<<"\n4. Actualizar o modificar la información de un vehículo registrado en el sistema (valor, o, tipo).";
    cout<<"\nModificar (1. Valor, 2. Tipo): "; cin>>opc;
    cout<<"\nIngrese la placa del vehiculo a modificar: "; cin>>placaB;
    
    
    while(temp != NULL){
        
        if(strcmp(temp->placa, placaB)==0){
            
            encontrado = true;
            break;
        }
        
        temp = temp->sig;
    }
    
    if(encontrado == false){
        
        cout<<"\nVehiculo no encontrado.\n";
        return;
    }
    
    if(opc==1){
        
        cout<<"Ingrese el nuevo valor: "; cin>>nuevoValor;
        temp->valor = nuevoValor;
    
        return;
    }
    
    else if(opc==2){
        
        cout<<"Ingrese el nuevo tipo (P-propio, C-consignado): "; cin>>nuevoTipo;
        temp->tipo = nuevoTipo;
      
        return;
    }
    
    cout<<"\nOpción no valida."; return;
   
}




////////////////////////////////////////////////////////////////////////////////

void eliminaroactivarV(struct vehiculo *primero){
    
     char placaB[7];
     struct vehiculo *temp = primero;
     bool encontrado = false;
     char nuevoEstado;
     
     if (primero == NULL) {
    cout<<"\nNo hay vehículos registrados.\n";
    return;
    }
    
     cout<<"\n5. Eliminar-activar un vehículo del sistema.";
     cout<<"\nIngrese la placa del vehiculo: "; cin>>placaB;
     
     while(temp != NULL){
         
         if(strcmp(temp->placa, placaB)==0){
             
             encontrado = true;
             break;
 
         }
         temp = temp->sig;
     }
     
     if(encontrado == false){
         
         cout<<"\nVehiculo no encontrado.\n";
         return;
     }
     
     cout<<"\nEstado actual del vehiculo: "<<temp->estado<<".";
     cout<<"\nIngrese el nuevo estado del vehiculo (A-activo, E-eliminado): "; cin>>nuevoEstado;
    
    temp->estado = nuevoEstado;
    
    cout<<"\nEstado actualizado con exito.\n";
    
}



////////////////////////////////////////////////////////////////////////////////

void moverVEliminados(struct vehiculo *&primero, struct vehiculo *&vehiculosEliminados) {
    struct vehiculo *temp = primero, *anterior = NULL;
    
    while (temp != NULL) {
        if (temp->estado == 'E') { 
            struct vehiculo *eliminado = temp; // Guardar el nodo a mover
            temp = temp->sig; // Avanzar antes de modificar punteros

            if (anterior == NULL) { 
                primero = eliminado->sig;
            } else {
                anterior->sig = eliminado->sig;
            }

            eliminado->sig = NULL; 
            
            if (vehiculosEliminados == NULL) {
                vehiculosEliminados = eliminado;
            } else {
              
                struct vehiculo *aux = vehiculosEliminados;
                while (aux->sig != NULL) {
                    aux = aux->sig;
                }
                aux->sig = eliminado; 
            }

            cout<<"\nVehículo con placa "<<eliminado->placa<<" movido a la lista de eliminados.\n";
        } else {
            anterior = temp; 
            temp = temp->sig; 
        }
    }
}




////////////////////////////////////////////////////////////////////////////////

void consultarLT(struct vehiculo *primero, struct vehiculo *vehiculosEliminados) {
    
    int opc;
    struct vehiculo *temp = primero;
    struct vehiculo *tempE = vehiculosEliminados; 
    
    cout<<"\nLista total de vehículos (A-activos E-eliminados):\n"; 
    cout<<"\nSeleccione el estado de los vehículos que desea ver (1. Activos 2. Eliminados): ";
    cin>>opc;
    
    if(opc==1){
        
    temp = primero;
        
    while (temp != NULL) {
        
        if(temp->estado == 'A'){
        
        mostrarDatos(temp);
         
        cout<<"\n------------------------------------\n";   
        temp = temp->sig;
    }
   }
  }
  
    else if(opc == 2) {
    // Mostrar eliminados en la lista original
    while (temp != NULL) {
        if(temp->estado == 'E') {
            mostrarDatos(temp);
        }
        cout<<"\n------------------------------------\n";
        temp = temp->sig;
    }

    // Mostrar los eliminados en la lista de eliminados
    while (tempE != NULL) {
        
         mostrarDatos(tempE);
      
        cout<<"\n------------------------------------\n";
        tempE = tempE->sig;
    }
}

  else {cout<<"\nOpción no valida.\n"; return; }
  return; 
}


////////////////////////////////////////////////////////////////////////////////

int main(){
    
    int opc;
    char placaB[7];
    struct vehiculo *primero = NULL;
    struct vehiculo *vehiculosEliminados = NULL;
    
    while(true){
        
    cout<<"\nBIENVENIDO AL CONCESIONARIO\n";
    cout<<"\n1. Registrar vehículos.";
    cout<<"\n2. Agregar características a la hoja de vida de un vehículo";
    cout<<"\n3. Consultar las existencias de vehículos activos por marca-modelo, y, por rango de precio, y, por tipo.";
    cout<<"\n4. Actualizar o modificar la información de un vehículo registrado en el sistema (valor, o, tipo).";
    cout<<"\n5. Eliminar-activar un vehículo del sistema.";
    cout<<"\n6. Mover vehículos borrados a una nueva lista.";
    cout<<"\n7. Consultar lista total de vehículos (A-activos E-eliminados)";
    cout<<"\n8. Salir.\n";
    cout<<"\nElija una opción: "; cin>>opc;
    
    switch(opc){
        
        case 1: {registrarV(primero); break;} 
        
        case 2: {cout<<"Ingrese la placa del vehiculo: "; cin>>placaB; agregarInfoH(primero, placaB); break;} 
        
        case 3: {consultarVEspe(primero); break;} 
        
        case 4: {modificarVvt(primero); break;} 
        
        case 5: {eliminaroactivarV(primero); break;} 
        
        case 6: {moverVEliminados(primero, vehiculosEliminados); break;} 
        
        case 7: {consultarLT(primero, vehiculosEliminados); break;}
        
        case 8: {cout<<"\nHasta luego.\n"; return 0;} 
        
        default:{cout<<"\nOpción no valida.\n";}
        
    }
  }
    return 0;
}



/*

Placa, marca, modelo, año, color, tipo (P-propio, C-consignado), valor, estado (A-activo, E-eliminado).


1. Registrar vehículos que ingresan al negocio.
2. Agregar características a la hoja de vida de un vehículo (la hoja de vida es una lista simple de datos adicionales de cada vehículo).
3. Consultar las existencias de vehículos activos por marca-modelo, y, por rango de precio, y, por tipo.
4. Actualizar o modificar la información de un vehículo registrado en el sistema (valor, o, tipo).
5. Eliminar-activar (de forma lógica) un vehículo del sistema.
6. Mover vehículos borrados (borrado lógico) a una nueva lista (desaparecen de la lista original, con todo y su hoja de vida). 
7. Consultar lista total de vehículos (El usuario escoge la lista a consultar: A-ctivos B-orrados)
8. Salir


*/