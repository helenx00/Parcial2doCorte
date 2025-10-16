# Proyecto 2do corte   Inventario básico (Lista simple – SLL)

Este proyecto implementa un sistema de gestión de inventario utilizando listas enlazadas simples en lenguaje C.  
Forma parte de un ejercicio académico para practicar estructuras dinámicas, funciones y manejo de memoria.


# Estructura principal

Cada producto del inventario se representa mediante una estructura (`struct Node`) que almacena:

```c
typedef struct Node {
    int id;
    char name[40];
    int cantidad;
    struct Node* next;
} Producto;
