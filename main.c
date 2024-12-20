#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "funciones.c"

main() 
{
    system("chcp 65001");
    system("cls");
    int opcion;
    bool ciclo = true;
    FILE *archivo;

    struct Articulos articuloVacio = {0, "", "", "", 
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 0, 0, 0
    };

    struct Insumo insumoVacio = {0, "", 0, 0, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    struct Proveedor proveedorVacio = {0, "", "", "", 0, 0, 0, 0, "", 
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    struct Mercado mercadoVacio = {0, "", "", "", 0, 0, 0, 0, ""};

    struct Empleado empleadoVacio = {0, "", "", "", 0.0, 
        {0, 0, 0}, {"", 0, "", "", ""}
    };

    while (ciclo) 
    {
        do 
        {
            opcion = menu_principal();
            if (opcion < 0 || opcion > 10)
                printf("Opción no válida. Intenta de nuevo\n");
        } while (opcion < 0 || opcion > 10);

        switch (opcion) 
        {
            case 1:
                if ((archivo = fopen("Articulos.dat", "r+")) == NULL) 
                {
                    printf("ERROR.\nSe está creando el archivo. Intenta de nuevo.\n");
                    crearRegistrosVacios("Articulos.dat", &articuloVacio, sizeof(struct Articulos), 1000);
                } 
                else 
                {
                    menu_articulos(archivo);
                    fclose(archivo);
                    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                }
                break;

            case 2:
                if ((archivo = fopen("Insumos.dat", "r+")) == NULL) 
                {
                    printf("ERROR.\nSe está creando el archivo. Intenta de nuevo.\n");
                    crearRegistrosVacios("Insumos.dat", &insumoVacio, sizeof(struct Insumo), 100);
                } 
                else 
                {
                    menu_insumos(archivo);
                    fclose(archivo);
                    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                }
                break;

            case 3:
                if ((archivo = fopen("Mercados.dat", "r+")) == NULL) 
                {
                    printf("ERROR.\nSe está creando el archivo. Intenta de nuevo.\n");
                    crearRegistrosVacios("Mercados.dat", &mercadoVacio, sizeof(struct Mercado), 100);
                } 
                else 
                {
                    menu_mercados(archivo);
                    fclose(archivo);
                    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                }
                break;

            case 4:
                if ((archivo = fopen("Empleados.dat", "r+")) == NULL) 
                {
                    printf("ERROR.\nSe está creando el archivo. Intenta de nuevo.\n");
                    crearRegistrosVacios("Empleados.dat", &empleadoVacio, sizeof(struct Empleado), 1000);
                } 
                else 
                {
                    menu_empleados(archivo);
                    fclose(archivo);
                    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                }
                break;

            case 5:
                if ((archivo = fopen("Proveedores.dat", "r+")) == NULL) 
                {
                    printf("ERROR.\nSe está creando el archivo. Intenta de nuevo.\n");
                    crearRegistrosVacios("Proveedores.dat", &proveedorVacio, sizeof(struct Proveedor), 100);
                } 
                else 
                {
                    menu_proveedores(archivo);
                    fclose(archivo);
                    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                }
                break;

            case 6:
                if ((archivo = fopen("Ventas.txt", "a")) == NULL) 
                    printf("ERROR.\nSe está creando el archivo. Intenta de nuevo.\n");
                else 
                {
                    menu_control_ventas(archivo);
                    fclose(archivo);
                    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                }
                break;

            case 7:
                if ((archivo = fopen("Compras.txt", "a+")) == NULL) 
                    printf("ERROR.\nSe está creando el archivo. Intenta de nuevo.\n");
                else 
                {
                    menu_control_compras(archivo);
                    fclose(archivo);
                    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                }
                break;

            case 8:
                if ((archivo = fopen("Compras.txt", "r+")) == NULL) 
                    printf("ERROR.\nNo se pudo abrir el archivo.\n");
                else 
                {
                    menu_control_inventario(archivo);
                    fclose(archivo);
                    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                }
                break;

            case 9:
                menu_reportes();
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                break;

            case 10:
                printf("HA SALIDO DEL SISTEMA.\n");
                ciclo = false;
                break;
        }
    }
}