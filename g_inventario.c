#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Node {
    int id;
    char name[40];
    int cantidad; 
    struct Node* next;
} Producto;

typedef Producto *Lista; // puntero a la cabeza de la lista




// Función para obtener un entero validado 
int leer_entero(const char *mensaje) {
    int num;
    printf("%s", mensaje);
    // Bucle para forzar la entrada numérica
    while (scanf("%d", &num) != 1) {
        printf("Error. Ingrese solo un numero: ");
        while (getchar() != '\n'); // Limpiar buffer de entrada
    }
    while (getchar() != '\n'); // Limpiar buffer después de la lectura
    return num;
}

// Auxiliar: Crea y inicializa un nuevo producto
Lista crear_nodo(int id, const char *nombre, int cantidad) {
    Lista nuevo = (Lista)malloc(sizeof(Producto));
    if (nuevo == NULL) {
        perror("Error de memoria");
        exit(EXIT_FAILURE);
    }
    nuevo->id = id;
    strncpy(nuevo->name, nombre, 39);
    nuevo->name[39] = '\0';
    nuevo->cantidad = cantidad; // Usa 'cantidad'
    nuevo->next = NULL;
    return nuevo;
}

// Busca el producto por ID
Lista buscar_producto(Lista cabeza, int id) {
    Lista actual = cabeza;
    while (actual != NULL) {
        if (actual->id == id) {
            return actual; //encontrado
        }
        actual = actual->next;
    }
    return NULL; // No encontrado
}




//  Insertar producto al INICIO
Lista insertar_inicio(Lista cabeza, int id, const char *nombre, int cantidad) {
    Lista nuevo = crear_nodo(id, nombre, cantidad);
    nuevo->next = cabeza;
    return nuevo;
}

// REQ 1: Insertar producto al FINAL
Lista insertar_final(Lista cabeza, int id, const char *nombre, int cantidad) {
    Lista nuevo = crear_nodo(id, nombre, cantidad);
    
    if (cabeza == NULL) {
        return nuevo;
    }

    Lista actual = cabeza;
    while (actual->next != NULL) {
        actual = actual->next;
    }
    
    actual->next = nuevo;
    return cabeza;
}

// REQ 3: Actualizar cantidad (stock)
void actualizar_cantidad(Lista cabeza) {
    int id = leer_entero("Ingrese el ID del producto a actualizar: ");
    Lista prod = buscar_producto(cabeza, id);

    if (prod != NULL) {
        printf("Producto: %s (Cantidad actual: %d). ", prod->name, prod->cantidad);
        prod->cantidad = leer_entero("Ingrese la NUEVA cantidad: ");
        printf("Cantidad actualizada correctamente.\n");
    } else {
        printf("ERROR: Producto con ID %d no encontrado.\n", id);
    }
}

// Eliminar producto por ID
Lista eliminar_producto(Lista cabeza) {
    int id = leer_entero("Ingrese el ID del producto a eliminar: ");
    Lista actual = cabeza;
    Lista previo = NULL;

    //  El nodo a eliminar es la cabeza
    if (actual != NULL && actual->id == id) {
        cabeza = actual->next;
        free(actual);
        printf("Producto ID %d eliminado.\n", id);
        return cabeza;
    }

    // Buscar el nodo a eliminar (intermedio o final)
    while (actual != NULL && actual->id != id) {
        previo = actual;
        actual = actual->next;
    }

    // Si actual es NULL, no se encontró
    if (actual == NULL) {
        printf("ERROR: Producto con ID %d no encontrado.\n", id);
        return cabeza;
    }

    // Desenlazar y liberar:
    previo->next = actual->next;
    free(actual);
    printf("Producto ID %d eliminado.\n", id);
    return cabeza;
}

// REQ 5: Listar el inventario completo
void listar_inventario(Lista cabeza) {
    if (cabeza == NULL) {
        printf("\n--- El inventario esta vacio ---\n");
        return;
    }
    Lista actual = cabeza;
    printf("\n--- INVENTARIO ACTUAL ---\n");
    printf("ID\tCANTIDAD\tNOMBRE\n");
    printf("-----------------------------------------\n");
    while (actual != NULL) {
        printf("%d\t%d\t\t%s\n", actual->id, actual->cantidad, actual->name);
        actual = actual->next;
    }
    printf("-----------------------------------------\n");
}



//MENÚ PRINCIPAL


void menu() {
    Lista inventario = NULL;
    int opcion;
    int id, cantidad, pos;
    char nombre[40];
    Lista temp;

    do {
        printf("\n======== INVENTARIO ========\n");
        printf("1. Insertar producto (Inicio/Final)\n");
        printf("2. Buscar datos de producto por ID\n");
        printf("3. Actualizar cantidad por ID\n");
        printf("4. Eliminar producto por ID\n");
        printf("5. Listar inventario completo\n");
        printf("0. SALIR\n");
        opcion = leer_entero("Seleccione una opcion: ");

        switch (opcion) {
            case 1: // Insertar producto
                printf("\n--- INSERCION ---\n");
                id = leer_entero("ID: ");
                printf("Nombre (max 39 chars): ");
                scanf("%39[^\n]", nombre);
                while (getchar() != '\n');
                cantidad = leer_entero("Cantidad: ");

                pos = leer_entero("Donde insertar (1=Inicio, 2=Final): ");
                if (pos == 1) {
                    inventario = insertar_inicio(inventario, id, nombre, cantidad);
                    printf(">> Insertado al INICIO.\n");
                } else if (pos == 2) {
                    inventario = insertar_final(inventario, id, nombre, cantidad);
                    printf(">> Insertado al FINAL.\n");
                } else {
                    printf("Opcion de insercion invalida.\n");
                }
                break;
            case 2: // Buscar producto
                id = leer_entero("Ingrese el ID a buscar: ");
                temp = buscar_producto(inventario, id);
                if (temp != NULL) {
                    printf(">> Producto encontrado: ID %d, Nombre: %s, Cantidad: %d\n", temp->id, temp->name, temp->cantidad);
                } else {
                    printf(">> Producto con ID %d no encontrado.\n", id);
                }
                break;
            case 3: // Actualizar cantidad
                actualizar_cantidad(inventario);
                break;
            case 4: // Eliminar producto
                inventario = eliminar_producto(inventario);
                break;
            case 5: // Listar
                listar_inventario(inventario);
                break;
            case 0:
                printf("Saliendo y liberando memoria. ¡Adios!\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 0);
    
    // Liberar memoria
    Lista actual = inventario;
    Lista siguiente;
    while(actual != NULL) {
        siguiente = actual->next;
        free(actual);
        actual = siguiente;
    }
}

int main() {
    menu();
    return 0;
}
