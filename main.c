#include <stdio.h>
#include "Lista.h"

int main (){

    Productos *lista = crearListaProductos();

    agregarRemedio(lista, crearRemedio("Remedio 1", 1, 20.5));
    agregarRemedio(lista, crearRemedio("Remedio 2", 2, 200));
    agregarRemedio(lista, crearRemedio("Remedio 3", 3, 144));
    agregarRemedio(lista, crearRemedio("Remedio 4", 4, 265.99));
    agregarRemedio(lista, crearRemedio("Remedio 5", 5, 753.12));
    agregarRemedio(lista, crearRemedio("Remedio 6", 6, 432));

    mostrarProductos(lista);

    ListaPedidos *pedidos = crearListaPedidos();
    ingresarPedidos(pedidos, lista);

    mostrarFactura(pedidos);

    return 0;
}
