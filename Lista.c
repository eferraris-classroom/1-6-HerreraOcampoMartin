#include "Lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Productos *crearListaProductos(){
    Productos *p = (Productos*) malloc(sizeof(Productos));
    
    if(p == NULL){
        printf("No hay memoria libre.");
        exit(-1);
    }

    p->tam = 0;
    p->lista = NULL;

    return p;
}

Remedio *crearRemedio(char *nombre, int codigo, float precio){
    Remedio *r = (Remedio*) malloc(sizeof(Remedio));

    if(r == NULL){
        printf("No hay memoria.");
        exit(-1);
    }

    r->codigo = codigo;
    r->nombre = nombre;
    r->precio = precio;
    r->sig = NULL;

    return r;
}

void agregarRemedio(Productos *p, Remedio *r){
    p->tam += 1; 
    if(p->lista == NULL){
        p->lista = r;
        return;
    }

    Remedio *aux = p->lista;
    for (; aux->sig != NULL; aux = aux->sig) {}

    aux->sig = r;
}

void mostrarProductos(Productos *p){
    printf("Productos disponibles:\n");
    if(p->lista == NULL){
        printf("No hay productos disponibles.\n");
        return;
    }

    Remedio *aux = p->lista;
    for (; aux !=  NULL; aux = aux->sig){
        printf("Codigo: %d - Nombre: %s - Precio: %.2f\n", aux->codigo, aux->nombre, aux->precio);
    }
}

Remedio *verificarSiExisteRemedio(char *nombre, Productos *productosDisponibles){
    Remedio *aux = productosDisponibles->lista;
    
    if(aux == NULL){
        printf("No hay productos disponibles.");
        return NULL;
    }

    for (; aux != NULL; aux = aux->sig) {
        if(strcmp(aux->nombre, nombre) == 0){
            return aux;
        }
    }

    printf("No existe el remedio ingresado\n");
    return NULL;
}

ListaPedidos *crearListaPedidos(){
    ListaPedidos *lista = (ListaPedidos*) malloc(sizeof(ListaPedidos));

    if(lista == NULL){
        printf("No hay memoria");
        exit(-1);
    }

    lista->tam = 0;
    lista->lista = NULL;

    return lista;
}

void ingresarPedidos(ListaPedidos *l, Productos *productosDisponibles){
    agregarAPedidos(l, crearPedido("Remedio 1", 12, productosDisponibles));
    agregarAPedidos(l, crearPedido("Remedio 3", 2, productosDisponibles));
    agregarAPedidos(l, crearPedido("Remedio 6", 1, productosDisponibles));
    agregarAPedidos(l, crearPedido("Remedio 30", 2, productosDisponibles));
    agregarAPedidos(l, crearPedido("Remedio 2", 5, productosDisponibles));
}

ProductoPedido *crearPedido(char *nombre, int cantidad, Productos *productosDisponibles){
    Remedio *r = verificarSiExisteRemedio(nombre, productosDisponibles);

    if(r == NULL){
        printf("No existe el remedio %s\n", nombre);
        return NULL;
    }

    ProductoPedido *prod = (ProductoPedido*) malloc(sizeof(ProductoPedido));

    if(prod == NULL){
        printf("No hay memoria.");
        exit(-1);
    }

    prod->cantidad = cantidad;
    prod->remedio = r;
    prod->sig = NULL;

    return prod;
}

void agregarAPedidos(ListaPedidos *lista, ProductoPedido *nodoAInsertar){

    if(nodoAInsertar == NULL){
        return;
    }

    if(lista->lista == NULL){
        lista->lista = nodoAInsertar;
        return;
    }

    ProductoPedido *act = NULL, *ant = NULL;
    act = lista->lista;
    ant = act;

    while ( act != NULL && act->remedio->codigo < nodoAInsertar->remedio->codigo) {
        ant = act;
        act = act->sig;
    }

    if ( act != NULL && act == ant ) {
        //primer caso, el elemento que queremos insertar es el menor de la lista
        lista->lista = nodoAInsertar;
        nodoAInsertar->sig = act;
    } else if ( act != NULL && act != ant ) {
        //segundo caso, el elemento que queremos insertar queda en el "medio" de dos nodos
        nodoAInsertar->sig = act;
        ant->sig = nodoAInsertar;
    } else if ( act == NULL ) {
        //tercer caso, el elemento que queremos insertar queda al final de la lista
        ant->sig = nodoAInsertar;
    }

    lista->tam++;

}

void mostrarFactura(ListaPedidos *lista){
    printf("--- FACTURA ---\n");
    if(lista->lista == NULL){
        printf("No se selecciono ningun producto.\n");
        return;
    }

    float suma = 0;
    ProductoPedido *aux = lista->lista;
    for (; aux != NULL; aux = aux->sig) {
        printf("- %s (Codigo: %d) - Cantidad: %d - Precio por unidad: %.2f - Subtotal: %.2f\n",
               aux->remedio->nombre, 
               aux->remedio->codigo, 
               aux->cantidad,
               aux->remedio->precio,
               aux->cantidad * aux->remedio->precio);
        suma = suma + aux->cantidad * aux->remedio->precio;
    }

    printf("TOTAL A PAGAR: %.2f", suma);
}
