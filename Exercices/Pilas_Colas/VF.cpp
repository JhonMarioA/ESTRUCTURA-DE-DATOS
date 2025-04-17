#include <iostream>

using namespace std;

// Definición de la estructura del nodo
struct Nodo {
    int info;
    Nodo *sig;
};

// Función para verificar si la cola está vacía
bool vacia(Nodo *raiz) {
    return (raiz == NULL);
}

// Función para insertar un elemento en la cola
void insertar(Nodo *&raiz, Nodo *&fondo, int x) {
    Nodo *nuevo = new Nodo(); // Crear un nuevo nodo
    nuevo->info = x;          // Asignar el valor al nodo
    nuevo->sig = NULL;        // El siguiente nodo es NULL
    if (vacia(raiz)) {        // Si la cola está vacía
        raiz = nuevo;         // El nuevo nodo es la raíz
        fondo = nuevo;        // El nuevo nodo también es el fondo
    } else {                  // Si la cola no está vacía
        fondo->sig = nuevo;   // El último nodo apunta al nuevo nodo
        fondo = nuevo;        // El nuevo nodo se convierte en el fondo
    }
    cout << "Elemento " << x << " insertado en la cola.\n";
}

// Función para extraer un elemento de la cola
int extraer(Nodo *&raiz, Nodo *&fondo) {
    if (!vacia(raiz)) { // Si la cola no está vacía
        int informacion = raiz->info; // Obtener el valor del nodo raíz
        Nodo *bor = raiz;             // Guardar el nodo a eliminar
        if (raiz == fondo) {          // Si solo hay un nodo en la cola
            raiz = NULL;              // La cola queda vacía
            fondo = NULL;
        } else {                      // Si hay más de un nodo
            raiz = raiz->sig;         // La raíz pasa al siguiente nodo
        }
        delete bor;                   // Liberar la memoria del nodo eliminado
        cout << "Elemento " << informacion << " extraído de la cola.\n";
        return informacion;           // Retornar el valor extraído
    } else {
        cout << "La cola está vacía. No se puede extraer elementos.\n";
        return -1; // Retornar un valor especial para indicar que la cola está vacía
    }
}

// Función para imprimir los elementos de la cola
void imprimir(Nodo *raiz) {
    if (vacia(raiz)) {
        cout << "La cola está vacía.\n";
    } else {
        cout << "Listado de todos los elementos de la cola:\n";
        Nodo *reco = raiz;
        while (reco != NULL) {
            cout << reco->info << " -> ";
            reco = reco->sig;
        }
        cout << "NULL\n";
    }
}

// Función para liberar todos los nodos de la cola
void liberar(Nodo *&raiz, Nodo *&fondo) {
    Nodo *reco = raiz;
    while (reco != NULL) {
        Nodo *bor = reco;
        reco = reco->sig;
        delete bor;
    }
    raiz = NULL;
    fondo = NULL;
    cout << "La cola ha sido vaciada.\n";
}

int main() {
    Nodo *raiz = NULL; // Inicializar la raíz de la cola
    Nodo *fondo = NULL; // Inicializar el fondo de la cola
    int opc, val;

    do {
        cout << "\nMenú de colas\n";
        cout << "1. Entra nodo a la cola\n";
        cout << "2. Sale nodo de la cola\n";
        cout << "3. Mostrar cola\n";
        cout << "4. Vaciar cola\n";
        cout << "5. Ver si la cola está vacía\n";
        cout << "6. Salir\n";
        cout << "Escoja una opción: ";
        cin >> opc;

        switch (opc) {
            case 1:
                cout << "Indique valor: ";
                cin >> val;
                insertar(raiz, fondo, val);
                break;
            case 2:
                extraer(raiz, fondo);
                break;
            case 3:
                imprimir(raiz);
                break;
            case 4:
                liberar(raiz, fondo);
                break;
            case 5:
                if (vacia(raiz)) {
                    cout << "La cola está vacía.\n";
                } else {
                    cout << "La cola tiene información.\n";
                }
                break;
            case 6:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opción inválida. Intente de nuevo.\n";
                break;
        }
    } while (opc != 6);

    return 0;
}