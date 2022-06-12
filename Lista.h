#ifndef LISTA_H
#define LISTA_H

typedef struct remedio {
    char* nombre;
    int codigo;
    float precio;
    struct remedio *sig;
} Remedio;

typedef struct productos {
    int tam;
    Remedio *lista;
} Productos;

typedef struct pedido {
    Remedio *remedio;
    int cantidad;
    struct pedido *sig;
} ProductoPedido;

typedef struct listaPedidos{
    int tam;
    ProductoPedido *lista;
} ListaPedidos;

Productos *crearListaProductos();
Remedio *crearRemedio(char *nombre, int codigo, float precio);
void agregarRemedio(Productos *p, Remedio *r);
void mostrarProductos(Productos *p);
Remedio *verificarSiExisteRemedio(char *nombre, Productos *p);

ListaPedidos *crearListaPedidos();
ProductoPedido *crearPedido(char *nombre, int cantidad, Productos *productosDisponibles);
void ingresarPedidos(ListaPedidos *l, Productos *productosDisponibles);
void agregarAPedidos(ListaPedidos *lista, ProductoPedido *p);
void mostrarFactura(ListaPedidos *lista);

#endif
