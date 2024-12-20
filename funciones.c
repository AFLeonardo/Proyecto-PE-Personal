#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "estructuras.h"
#include "funciones.h"
#include <windows.h>
#include <time.h>

int menu_principal()
{
    int opcion;
    printf("\n");
    printf("$$\\                                                                             \n");
    printf("$$ |                                                                            \n");
    printf("$$ | $$$$$$\\         $$$$$$\\   $$$$$$\\   $$$$$$\\  $$$$$$$$\\        $$\\  $$$$$$\\  \n");
    printf("$$ | \\____$$\\       $$  __$$\\ $$  __$$\\  \\____$$\\ $$  __$$ |       \\__| \\____$$\\ \n");
    printf("$$ | $$$$$$$ |      $$ /  $$ |$$ |  \\__| $$$$$$$ |$$ |  $$ |      $$\\  $$$$$$$ | \n");
    printf("$$ |$$  __$$ |      $$ |  $$ |$$ |      $$  __$$ |$$ |  $$ |      $$ |$$  __$$ | \n");
    printf("$$ |\\$$$$$$$ |      \\$$$$$$$ |$$ |      \\$$$$$$$ |$$ |  $$ |      $$ |\\$$$$$$$ | \n");
    printf("\\__| \\_______|       \\____$$ |\\__|       \\_______|\\__|  \\__|      $$ | \\_______| \n");
    printf("                    $$\\   $$ |                              $$\\   $$ |          \n");
    printf("                    \\$$$$$$  |                              \\$$$$$$  |          \n");
    printf("                     \\______/                                \\______/            \n");
    
    printf("=============================================================================================\n");
    printf("\n                                      Menu principal\n");
    printf("=============================================================================================\n");
    printf("1) Articulos\n");
    printf("2) Insumos\n");
    printf("3) Mercados\n");
    printf("4) Empleados\n");
    printf("5) Proveedores\n");
    printf("6) Ventas\n");
    printf("7) Compras\n");
    printf("8) Control de Inventario\n");
    printf("9) Reportes\n");
    printf("10) Salir\n");

    printf("Ingrese una opcion: ");
    scanf("%d", &opcion);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    return opcion;
}

void menu_articulos(FILE *articulosf)
{
    char agregar, agregar_insumo;
    struct Articulos x_articulo;
    struct Insumo LecturaInsumo;
    struct Mercado mercado;
    char *estaciones[4] = {"p", "v", "o", "i"}, agregar_mercado;
    bool temporadaValida, clave_valida = false;
    int i, cant_insumos, n_mercados;
    FILE *InsumoF, *MercadoF;
    float costo_produccion = 0;

    printf(" $$$$$$\\              $$\\     $$\\                     $$\\                     \n");
    printf("$$  __$$\\             $$ |    \\__|                    $$ |                    \n");
    printf("$$ /  $$ | $$$$$$\\  $$$$$$\\   $$\\  $$$$$$$\\ $$\\   $$\\ $$ | $$$$$$\\   $$$$$$$\\ \n");
    printf("$$$$$$$$ |$$  __$$\\ \\_$$  _|  $$ |$$  _____|$$ |  $$ |$$ |$$  __$$\\ $$  _____|\n");
    printf("$$  __$$ |$$ |  \\__|  $$ |    $$ |$$ /      $$ |  $$ |$$ |$$ /  $$ |\\$$$$$$\\  \n");
    printf("$$ |  $$ |$$ |        $$ |$$\\ $$ |$$ |      $$ |  $$ |$$ |$$ |  $$ | \\____$$\\ \n");
    printf("$$ |  $$ |$$ |        \\$$$$  |$$ |\\$$$$$$$\\ \\$$$$$$  |$$ |\\$$$$$$  |$$$$$$$  |\n");
    printf("\\__|  \\__|\\__|         \\____/ \\__| \\_______| \\______/ \\__| \\______/ \\_______/ \n");

    if ((InsumoF = fopen("Insumos.dat", "r")) == NULL) 
    {
        printf("No existen insumos necesarios para crear artículos. Agregue insumos primero.\n");
        return;
    }
    if ((MercadoF = fopen("Mercados.dat", "r")) == NULL) 
    {
        printf("No existen mercados registrados. Agregue mercados primero.\n");
        fclose(InsumoF);
        return;
    }

    while (agregar != 'N' && agregar != 'n')
    {
        memset(&x_articulo, 0, sizeof(struct Articulos));
        cant_insumos = 0;
        n_mercados = 0;
        agregar_insumo = 's';
        printf("\nINGRESA LA INFORMACION.\n\n");

        
        do
        {
            printf("1) Clave del articulo: ");
            scanf("%d", &x_articulo.clave_articulo);
            if (x_articulo.clave_articulo > 1000 || x_articulo.clave_articulo < 1)
                printf("Clave invalida. Valores admitidos 1 a 1000\n");
        } while (x_articulo.clave_articulo > 1000 || x_articulo.clave_articulo < 1);

        
        do
        {
            printf("2) Descripcion: ");
            fflush(stdin);
            gets(x_articulo.descripcion);
            if (strlen(x_articulo.descripcion) < 10)
                printf("\nLos caracteres minimos son 10.\n");
        } while (strlen(x_articulo.descripcion) < 10);

        
        do
        {
            temporadaValida = false;
            printf("3) Temporada de siembra: ");
            fflush(stdin);
            gets(x_articulo.temp_siembra);

            for (i = 0; i < 4; i++)
            {
                if (strcmp(convertir_a_minusculas(x_articulo.temp_siembra), estaciones[i]) == 0)
                    temporadaValida = true;
            }

            if (!temporadaValida)
                printf("\n*** Estacion invalida ***\nSolo se permite:\nP - Primavera\nV - Verano\nO - Otoño\nI - Invierno.\n");
        } while (!temporadaValida);

        
        do
        {
            temporadaValida = false;
            printf("4) Temporada de cosecha: ");
            fflush(stdin);
            gets(x_articulo.temp_cosecha);

            for (i = 0; i < 4; i++)
            {
                if (strcmp(convertir_a_minusculas(x_articulo.temp_cosecha), estaciones[i]) == 0)
                    temporadaValida = true;
            }

            if (!temporadaValida)
                printf("\n*** Estacion invalida ***\nSolo se permite:\nP - Primavera\nV - Verano\nO - Otoño\nI - Invierno.\n");
        } while (!temporadaValida);

        
        do
        {
            printf("5) Inventario: ");
            scanf("%d", &x_articulo.inventario);

            if (x_articulo.inventario < 0)
                printf("Valor invalido.\nValor minimo 0.\n");
        } while (x_articulo.inventario < 0);

        
        do
        {
            printf("6) Precio de venta: ");
            scanf("%f", &x_articulo.precio_venta);

            if (x_articulo.precio_venta <= 0)
                printf("Valor invalido.\nEl precio debe ser mayor a 0.\n");
        } while (x_articulo.precio_venta <= 0);

        
        costo_produccion = 0;

        
        while (cant_insumos < 9 && (agregar_insumo == 's' || agregar_insumo == 'S'))
        {
            clave_valida = false;
            do
            {
                printf("7) Clave del insumo [%d]: ", cant_insumos + 1);
                scanf("%d", &x_articulo.insumos_requeridos[cant_insumos]);

                fseek(InsumoF, (x_articulo.insumos_requeridos[cant_insumos] - 1) * sizeof(struct Insumo), SEEK_SET);
                fread(&LecturaInsumo, sizeof(struct Insumo), 1, InsumoF);

                if (LecturaInsumo.clave_insumo == x_articulo.insumos_requeridos[cant_insumos])
                {
                    costo_produccion += LecturaInsumo.precio_compra[0];  
                    clave_valida = true;
                }

                if (!clave_valida)
                    printf("\nClave del insumo no encontrada\n");

            } while (!clave_valida);

            do
            {
                printf("Quieres agregar otro insumo al articulo(s/n): ");
                fflush(stdin);
                scanf("%c", &agregar_insumo);

                if (agregar_insumo != 'S' && agregar_insumo != 's' && agregar_insumo != 'N' && agregar_insumo != 'n')
                    printf("\nValor no valido, solo se permite (s/n)\n");
            } while (agregar_insumo != 'S' && agregar_insumo != 's' && agregar_insumo != 'N' && agregar_insumo != 'n');

            if (agregar_insumo == 's')
                cant_insumos++;
        }

        if (cant_insumos >= 10)
            printf("\nHa llegado al limite de insumos 10.\n");

        x_articulo.costo_produccion = costo_produccion;
        printf("El costo de produccion fue de %.2f \n", x_articulo.costo_produccion);

        agregar_mercado = 's';
        while (n_mercados < 9 && (agregar_mercado == 's' || agregar_mercado == 'S'))
        {
            clave_valida = false;
            do
            {
                printf("8) Clave del mercado [%d]: ", n_mercados + 1);
                scanf("%d", &x_articulo.clave_mercados[n_mercados]);

                fseek(MercadoF, (x_articulo.clave_mercados[n_mercados] - 1) * sizeof(struct Mercado), SEEK_SET);
                fread(&mercado, sizeof(struct Mercado), 1, MercadoF);

                if (mercado.clave_mercado == x_articulo.clave_mercados[n_mercados])
                    clave_valida = true;

                if (!clave_valida)
                    printf("\nClave del mercado no encontrada\n");

            } while (!clave_valida);

            do
            {
                printf("Deseas agregar otro mercado(s/n): ");
                fflush(stdin);
                scanf("%c", &agregar_mercado);

                if (agregar_mercado != 'S' && agregar_mercado != 's' && agregar_mercado != 'N' && agregar_mercado != 'n')
                    printf("\nValor no valido, solo se permite (s/n)\n");
            } while (agregar_mercado != 'S' && agregar_mercado != 's' && agregar_mercado != 'N' && agregar_mercado != 'n');

            if (agregar_mercado == 's')
                n_mercados++;
        }

        if (n_mercados >= 10)
            printf("Ha llegado al limite de mercados 10.\n");

        fseek(articulosf, (x_articulo.clave_articulo - 1) * sizeof(struct Articulos), SEEK_SET);
        fwrite(&x_articulo, sizeof(struct Articulos), 1, articulosf);

        printf("Deseas agregar otro articulo al inventario? (S/N): ");
        fflush(stdin);
        scanf("%c", &agregar);
    }
    fclose(InsumoF);
    fclose(MercadoF);
}

void menu_insumos(FILE *insumosf)
{
    char agregar, agregar_proveedor;
    struct Insumo insumos;
    struct Proveedor proveedores;
    FILE *proveedorlocal;
    int cant_proveedores;
    bool clave_valida;

    if((proveedorlocal = fopen("Proveedores.dat", "r")) == NULL)
        printf("\nError.\nNo existen proveedores.\nAgrega en el menu correspondiente.\n");
    else
    {
        while (agregar != 'N' && agregar != 'n')
        {
            agregar_proveedor = 's';
            cant_proveedores = 0;
            printf(" $$$$$$\\                                                                 \n");
            printf(" \\_$$  _|                                                                \n");
            printf("   $$ |  $$$$$$$\\   $$$$$$$\\ $$\\   $$\\ $$$$$$\\$$$$\\   $$$$$$\\   $$$$$$$\\ \n");
            printf("   $$ |  $$  __$$\\ $$  _____|$$ |  $$ |$$  _$$  _$$\\ $$  __$$\\ $$  _____|\n");
            printf("   $$ |  $$ |  $$ |\\$$$$$$\\  $$ |  $$ |$$ / $$ / $$ |$$ /  $$ |\\$$$$$$\\  \n");
            printf("   $$ |  $$ |  $$ | \\____$$\\ $$ |  $$ |$$ | $$ | $$ |$$ |  $$ | \\____$$\\ \n");
            printf(" $$$$$$\\ $$ |  $$ |$$$$$$$  |\\$$$$$$  |$$ | $$ | $$ |\\$$$$$$  |$$$$$$$  |\n");
            printf(" \\______|\\__|  \\__|\\_______/  \\______/ \\__| \\__| \\__| \\______/ \\_______/ \n");

            printf("\nINGRESA LA INFORMACION.\n\n");

            do
            {
                printf("1) Clave del insumo: ");
                scanf("%d", &insumos.clave_insumo);
                if (insumos.clave_insumo > 100 || insumos.clave_insumo < 1)
                    printf("Clave invalida. Valores admitidos 1 a 100. \n");

            }while (insumos.clave_insumo > 100 || insumos.clave_insumo < 1);

            do
            {
                printf("2) Descripcion: ");
                fflush(stdin);
                gets(insumos.descripcion);
                if (strlen(insumos.descripcion) < 10)
                    printf("Los caracteres minimos son 10.\n");

            }while(strlen(insumos.descripcion) < 10);

            do
            {
                printf("3) Punto de reorden: ");
                scanf("%d", &insumos.punto_reorden);
                if (insumos.punto_reorden <= 0)
                    printf("\nClave invalida. Valores admitidos mayores que 0.\n");

            }while (insumos.punto_reorden <= 0);

            do
            {
                printf("4) Inventario: ");
                scanf("%d", &insumos.inventario);

                if (insumos.inventario < 0)
                    printf("\nValor invalido, minimo 0.\n");

            }while(insumos.inventario < 0 && cant_proveedores < 10);

            while(agregar_proveedor == 's' && cant_proveedores < 10)
            {
                do
                {
                    clave_valida = false;
                    printf("5) Clave del proveedor: ");
                    scanf("%d", &insumos.clave_proveedor[cant_proveedores]);

                    fseek(proveedorlocal, (insumos.clave_proveedor[cant_proveedores] -1) * sizeof(struct Proveedor), SEEK_SET);
                    fread(&proveedores, sizeof(struct Proveedor), 1, proveedorlocal);

                    if(proveedores.numero_proveedor == insumos.clave_proveedor[cant_proveedores])
                        clave_valida = true;
                    else
                        printf("Clave del proveedor invalida.\nIngresa una clave valida.\n");

                } while (!clave_valida);

                do
                {
                    printf("6) Precio: ");
                    scanf("%f", &insumos.precio_compra[cant_proveedores]);
                    if (insumos.precio_compra[cant_proveedores] <= 0)
                        printf("Precio invalido\n");

                } while(insumos.precio_compra[cant_proveedores] <= 0);

                do
                {
                    printf("Quieres agregar otro proveedor al insumo?(s/n): \n");
                    fflush(stdin);
                    scanf("%c", &agregar_proveedor);
                    agregar_proveedor = tolower(agregar_proveedor);

                    if (agregar_proveedor != 's' && agregar_proveedor != 'n')
                        printf("Valor no valido, solo se permite (s/n) \n");

                } while (agregar_proveedor != 's' && agregar_proveedor != 'n');

                if(agregar_proveedor == 's')
                    cant_proveedores++;
            }

            if(cant_proveedores > 10)
                printf("El maximo son 10 proveedores.\n");

            fseek(insumosf, (insumos.clave_insumo - 1) * sizeof(struct Insumo), SEEK_SET);
            fwrite(&insumos, sizeof(struct Insumo), 1, insumosf);

            do
            {
                printf("Agregar otro insumo (S/N): ");
                fflush(stdin);
                scanf("%c", &agregar);
                if (agregar != 'S' && agregar != 's' && agregar != 'N' && agregar != 'n')
                    printf("Valor no valido.\nSolo se permite S o N.\n");

            } while (agregar != 'S' && agregar != 's' && agregar != 'N' && agregar != 'n');

            if (agregar == 's' || agregar == 'S')
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        }
        printf("\nInsumo agregado con exito.\n");
        Sleep(1500);
        fclose(proveedorlocal);
    }
}

void menu_empleados(FILE *fempleados)
{
    struct Empleado empleados;
    bool rfc_valido = true, correo_correcto = true, validardia = true;
    char agregar = 's';

    printf("$$$$$$$$\\                         $$\\                           $$\\                      \n");
    printf("$$  _____|                        $$ |                          $$ |                     \n");
    printf("$$ |      $$$$$$\\$$$$\\   $$$$$$\\  $$ | $$$$$$\\   $$$$$$\\   $$$$$$$ | $$$$$$\\   $$$$$$$\\ \n");
    printf("$$$$$\\    $$  _$$  _$$\\ $$  __$$\\ $$ |$$  __$$\\  \\____$$\\ $$  __$$ |$$  __$$\\ $$  _____| \n");
    printf("$$  __|   $$ / $$ / $$ |$$ /  $$ |$$ |$$$$$$$$ | $$$$$$$ |$$ /  $$ |$$ /  $$ |\\$$$$$$\\  \n");
    printf("$$ |      $$ | $$ | $$ |$$ |  $$ |$$ |$$   ____|$$  __$$ |$$ |  $$ |$$ |  $$ | \\____$$\\ \n");
    printf("$$$$$$$$\\ $$ | $$ | $$ |$$$$$$$  |$$ |\\$$$$$$$\\ \\$$$$$$$ |\\$$$$$$$ |\\$$$$$$  |$$$$$$$  | \n");
    printf("\\________|\\__| \\__| \\__|$$  ____/ \\__| \\_______| \\_______| \\_______| \\______/ \\_______/  \n");
    printf("                        $$ |                                                             \n");
    printf("                        $$ |                                                             \n");
    printf("                        \\__|     \n");
    printf("\nINGRESA LA INFORMACION.\n");

    while(agregar != 'n' && agregar != 'N')
    {
        do
        {
            printf("1) Numero de empleado: ");
            scanf("%d", &empleados.numero_empleado);

            if(empleados.numero_empleado < 1 || empleados.numero_empleado > 1000)
                printf("Numero de empleado invalido\n");

        }while(empleados.numero_empleado < 1 || empleados.numero_empleado > 1000);

        do
        {
            printf("2) Nombre completo: ");
            fflush(stdin);
            gets(empleados.nombre_completo);
            if (strlen(empleados.nombre_completo) < 20)
                printf("Los caracteres minimos son 20 \n");

        }while (strlen(empleados.nombre_completo) < 20);

        do
        {
            printf("3) RFC: ");
            fflush(stdin);
            gets(empleados.RFC);

            if (strlen(empleados.RFC) != 13)
            {
                printf("Los caracteres deben de ser 13.\n");
                rfc_valido = false;
            }
            else
                rfc_valido = validar_rfc(empleados.RFC);

            if (rfc_valido == false)
                printf("RFC invalido. No cumple con la estructurada adecuada\n");

        }while(rfc_valido == false);

        do
        {
            printf("4) Correo electronico: ");
            fflush(stdin);
            gets(empleados.correo);

            correo_correcto = validar_correo(empleados.correo);

            if (!correo_correcto)
                printf("El correo no cumple con el formato\n");

        }while(!correo_correcto);

        do
        {
            printf("5) Comision entre 0 y 1: ");
            scanf("%f", &empleados.comision);

            if(empleados.comision < 0 || empleados.comision > 1)
                printf("Comision invalida \n");

        }while(empleados.comision < 0 || empleados.comision > 1);

        do
        {
            printf("6) Año de contratacion: ");
            scanf("%d", &empleados.fecha.anio);

            if (empleados.fecha.anio < 1990 || empleados.fecha.anio > 2024)
                printf("Anio de nacimiento invalido, debe de estar entre 1990 y 2024\n");
        }while (empleados.fecha.anio < 1990 || empleados.fecha.anio > 2024);

        do
        {
            printf("7) Mes de contratacion: ");
            scanf("%d", &empleados.fecha.mes);
            if (empleados.fecha.mes < 1 || empleados.fecha.mes > 12)
                printf("Mes de contratacion invalido, debe de estar entre 1 y 12\n");

        }while (empleados.fecha.mes < 1 || empleados.fecha.mes > 12);

        do
        {
            printf("8) Dia de contratacion: ");
            scanf("%d", &empleados.fecha.dia);
            validardia = validarDiaMes(empleados.fecha.dia, empleados.fecha.mes, empleados.fecha.anio);
            if (!validardia)
                printf("Ingrese un dia valido correspondiente al mes\n");

        }while (!validardia);


        printf("9) Direccion:\n");
        do
        {
            printf("Calle: ");
            fflush(stdin);
            gets(empleados.direccion.calle);
            if (!validarchar(empleados.direccion.calle))
                printf("Ingrese una calle valida.\n");

        }while (!(validarchar(empleados.direccion.calle)));

        do
        {
            printf("Número: ");
            gets(empleados.direccion.numero);
            if (!validarnumerodireccion(empleados.direccion.numero))
                printf("Ingrese un numero valido.\n");

        }while (!(validarnumerodireccion(empleados.direccion.numero)));

        do
        {
            printf("Colonia: ");
            fflush(stdin);
            gets(empleados.direccion.colonia);
            if (!validarchar(empleados.direccion.colonia))
                printf("Ingrese una colonia valida.\n");

        }while (!validarchar(empleados.direccion.colonia));

        do
        {

            printf("Municipio: ");
            fflush(stdin);
            gets(empleados.direccion.municipio);
            if (!validarchar(empleados.direccion.municipio))
                printf("Ingrese un municipio valido.\n");

        }while (strlen(empleados.direccion.municipio) < 0);

        do
        {
            printf("Estado: ");
            fflush(stdin);
            gets(empleados.direccion.estado);
            if (!validarchar(empleados.direccion.estado))
                printf("Ingrese un estado valido.\n");

        }while (!validarchar(empleados.direccion.estado));

        fseek(fempleados, (empleados.numero_empleado - 1) * sizeof(struct Empleado), SEEK_SET);
        fwrite(&empleados, sizeof(struct Empleado), 1, fempleados);
        printf("\nEmpleado dado de alta con exito!\n");

        do
        {
            printf("Agregar otro empleado? (S/N): ");
            fflush(stdin);
            scanf("%c", &agregar);
            if (agregar != 'S' && agregar != 's' && agregar != 'N' && agregar != 'n')
                printf("Valor no valido.\nSolo se permite S o N.\n");

        }while (agregar != 'S' && agregar != 's' && agregar != 'N' && agregar != 'n');
    }
}

void menu_proveedores(FILE *fproveedores)
{
    struct Proveedor proveedores;
    char agregar = 's';
    bool rfc_valido = true,
         correo_correcto = true,
         validardia = true;
    int i;

    printf("$$$$$$$\\                                                           $$\\                                          \n");
    printf("$$  __$$\\                                                          $$ |                                         \n");
    printf("$$ |  $$ | $$$$$$\\   $$$$$$\\  $$\\    $$\\  $$$$$$\\   $$$$$$\\   $$$$$$$ | $$$$$$\\   $$$$$$\\   $$$$$$\\   $$$$$$$\\ \n");
    printf("$$$$$$$  |$$  __$$\\ $$  __$$\\ \\$$\\  $$  |$$  __$$\\ $$  __$$\\ $$  __$$ |$$  __$$\\ $$  __$$\\ $$  __$$\\ $$  _____|\n");
    printf("$$  ____/ $$ |  \\__|$$ /  $$ | \\$$\\$$  / $$$$$$$$ |$$$$$$$$ |$$ /  $$ |$$ /  $$ |$$ |  \\__|$$$$$$$$ |\\$$$$$$\\  \n");
    printf("$$ |      $$ |      $$ |  $$ |  \\$$$  /  $$   ____|$$   ____|$$ |  $$ |$$ |  $$ |$$ |      $$   ____| \\____$$\\ \n");
    printf("$$ |      $$ |      \\$$$$$$  |   \\$  /   \\$$$$$$$\\ \\$$$$$$$\\ \\$$$$$$$ |\\$$$$$$  |$$ |      \\$$$$$$$\\ $$$$$$$  |\n");
    printf("\\__|      \\__|       \\______/     \\_/     \\_______| \\_______| \\_______| \\______/ \\__|       \\_______|\\_______/ \n");
    printf("                                                                                                               \n");

    while(agregar != 'n' && agregar != 'N')
    {
        printf("\nINGRESA LA INFORMACION.\n\n");
        do
        {
            printf("1) Ingrese su numero de proveedor: ");
            scanf("%d", &proveedores.numero_proveedor);

            if(proveedores.numero_proveedor < 1 || proveedores.numero_proveedor > 100)
                printf("Numero de proveedor invalido. Valores validos de 1-100\n");

        }while(proveedores.numero_proveedor < 1 || proveedores.numero_proveedor > 100);

        do
        {
            printf("2) Nombre completo: ");
            fflush(stdin);
            gets(proveedores.nombre_completo);
            if (strlen(proveedores.nombre_completo) < 10)
                printf("Los caracteres minimos son 10 \n");

        }while (strlen(proveedores.nombre_completo) < 10);

        do
        {
            printf("3) RFC: ");
            fflush(stdin);
            gets(proveedores.RFC);

            if (strlen(proveedores.RFC) != 13)
            {
                printf("Los caracteres deben ser 13.\n");
                rfc_valido = false;
            }
            else
                rfc_valido = validar_rfc(proveedores.RFC);

            if (!rfc_valido)
                printf("RFC invalido.\nNo cumple con la estructurada adecuada\n");

        }while(!rfc_valido);

        do
        {
            printf("4) Correo electronico: ");
            fflush(stdin);
            gets(proveedores.correo);

            correo_correcto = validar_correo(proveedores.correo);

            if (!correo_correcto)
                printf("El correo no cumple con el formato\n");

        }while(!correo_correcto);


        do
        {
            printf("5) Descuento: ");
            scanf("%f", &proveedores.descuento);

            if (proveedores.descuento < 0 || proveedores.descuento > 1)
                printf("Descuento invalido debe de estar entre 0 y 1.\n");

        }while (proveedores.descuento < 0 || proveedores.descuento > 1);

        do
        {
            printf("6) Año de nacimiento: ");
            scanf("%d", &proveedores.fecha.anio);
            if (proveedores.fecha.anio < 1950 || proveedores.fecha.anio > 2006)
                printf("Anio de nacimiento invalido, debe de estar entre 1950 y 2006\n");

        }while (proveedores.fecha.anio < 1950 || proveedores.fecha.anio> 2006);

        do
        {
            printf("7) Mes de nacimiento: ");
            scanf("%d", &proveedores.fecha.mes);
            if (proveedores.fecha.mes < 1 || proveedores.fecha.mes > 12)
                printf("Mes de nacimiento invalido, debe de estar entre 1 y 12\n");

        }while (proveedores.fecha.mes < 1 || proveedores.fecha.mes > 12);

        do
        {
            printf("8) Dia de nacimiento: ");
            scanf("%d", &proveedores.fecha.dia);
            validardia = validarDiaMes(proveedores.fecha.dia, proveedores.fecha.mes, proveedores.fecha.anio);
            if (!validardia)
                printf("Ingrese un dia valido correspondiente al mes\n");

        }while (!validardia);

        printf("9) Dirección: \n");

        do
        {
            printf("Calle: ");
            fflush(stdin);
            gets(proveedores.direccion.calle);
            if (!validarchar(proveedores.direccion.calle))
                printf("Ingresa una calle valida.\n");

        }while (!validarchar(proveedores.direccion.calle));

        do
        {
            printf("Número: ");
            gets(proveedores.direccion.numero);
            if (!validarnumerodireccion(proveedores.direccion.numero))
                printf("Ingrese un numero valido.\n");

        }while (!validarnumerodireccion(proveedores.direccion.numero));

        do
        {
            printf("Colonia: ");
            fflush(stdin);
            gets(proveedores.direccion.colonia);
            if (!validarchar(proveedores.direccion.colonia))
                printf("Ingresa una colonia valida.\n");

        }while (!validarchar(proveedores.direccion.colonia));

        do
        {
            printf("Municipio: ");
            fflush(stdin);
            gets(proveedores.direccion.municipio);
            if (!validarchar(proveedores.direccion.municipio))
                printf("Ingresa un municipio valido.\n");

        }while (!validarchar(proveedores.direccion.municipio));

        do
        {
            printf("Ingrese el estado: ");
            fflush(stdin);
            gets(proveedores.direccion.estado);
            if (!validarchar(proveedores.direccion.estado))
                printf("Estado invalido. Ingrese un estado valido.\n");

        }while (!validarchar(proveedores.direccion.estado));

        for (i = 0; i < 10; i++)
            proveedores.articulos_produce[i] = 0;

        fseek(fproveedores, (proveedores.numero_proveedor - 1) * sizeof(struct Proveedor), SEEK_SET);
        fwrite(&proveedores, sizeof(struct Proveedor), 1, fproveedores);
        printf("\nProveedor dado de alta con exito!\n");

        do
        {
            printf("Agregar otro proveedor? (S/N): ");
            fflush(stdin);
            scanf("%c", &agregar);
            if (agregar != 'S' && agregar != 's' && agregar != 'N' && agregar != 'n')
                printf("Valor no valido.\nSolo se permite S o N.\n");

        }while (agregar != 'S' && agregar != 's' && agregar != 'N' && agregar != 'n');
    }
}

void menu_mercados(FILE *mercadosf)
{
    char agregar = 's';
    struct Mercado mercados;
    bool correo_correcto = true, rfc_valido=true, validardia=true;

    printf("$$\\      $$\\                                               $$\\                      \n");
    printf("$$$\\    $$$ |                                              $$ |                     \n");
    printf("$$$$\\  $$$$ | $$$$$$\\   $$$$$$\\   $$$$$$$\\  $$$$$$\\   $$$$$$$ | $$$$$$\\   $$$$$$$\\ \n");
    printf("$$\\$$\\$$ $$ |$$  __$$\\ $$  __$$\\ $$  _____| \\____$$\\ $$  __$$ |$$  __$$\\ $$  _____|\n");
    printf("$$ \\$$$  $$ |$$$$$$$$ |$$ |  \\__|$$ /       $$$$$$$ |$$ /  $$ |$$ /  $$ |\\$$$$$$\\  \n");
    printf("$$ |\\$  /$$ |$$   ____|$$ |      $$ |      $$  __$$ |$$ |  $$ |$$ |  $$ | \\____$$\\ \n");
    printf("$$ | \\_/ $$ |\\$$$$$$$\\ $$ |      \\$$$$$$$\\ \\$$$$$$$ |\\$$$$$$$ |\\$$$$$$  |$$$$$$$  |\n");
    printf("\\__|     \\__| \\_______|\\__|       \\_______| \\_______| \\_______| \\______/ \\_______/ \n");

    printf("\nINGRESA LA INFORMACION: \n");

    while (agregar != 'N' && agregar != 'n')
    {
        do
        {
            printf("\n1) Clave del mercado: ");
            scanf("%d", &mercados.clave_mercado);
            if (mercados.clave_mercado <= 0)
                printf("Clave invalida.\nValores admitidos mayores que 0\n");

        }while (mercados.clave_mercado <= 0);

        do
        {
            printf("2) Nombre completo: ");
            fflush(stdin);
            gets(mercados.nombre_completo);
            if (strlen(mercados.nombre_completo) < 10)
                printf("Los caracteres minimos son 10.\n");

        }while (strlen(mercados.nombre_completo) < 10);

        do
        {
            printf("3) RFC: ");
            fflush(stdin);
            gets(mercados.RFC);

            if (strlen(mercados.RFC) != 13)
            {
                printf("Los caracteres deben ser 13.\n");
                rfc_valido = false;
            }

            else
                rfc_valido = validar_rfc(mercados.RFC);

            if (!rfc_valido)
                printf("RFC invalido. No cumple con la estructurada adecuada\n");

        }while(!rfc_valido);

        do
        {
            printf("4) Correo electronico: ");
            fflush(stdin);
            gets(mercados.correo);

            correo_correcto = validar_correo(mercados.correo);

            if (!correo_correcto)
                printf("El correo no cumple con el formato\n");

        }while(!correo_correcto);

        do
        {
            printf("5) Descuento: ");
            scanf("%f", &mercados.descuento);

            if (mercados.descuento < 0 || mercados.descuento > 1)
                printf("Descuento invalido debe de estar entre 0 y 1.\n");

        }while (mercados.descuento < 0 || mercados.descuento > 1);

        do
        {
            printf("6) Año de nacimiento: ");
            scanf("%d", &mercados.fecha.anio);
            if (mercados.fecha.anio < 1950 || mercados.fecha.anio > 2006)
                printf("Año de nacimiento invalido, debe de estar entre 1950 y 2006\n");

        }while (mercados.fecha.anio < 1950 || mercados.fecha.anio > 2006);

        do
        {
            printf("7) Mes de nacimiento: ");
            scanf("%d", &mercados.fecha.mes);
            if (mercados.fecha.mes < 1 || mercados.fecha.mes > 12)
                printf("Mes de nacimiento invalido, debe de estar entre 1 y 12\n");

        }while (mercados.fecha.mes < 1 || mercados.fecha.mes > 12);

        do
        {
            printf("8) Dia de nacimiento: ");
            scanf("%d", &mercados.fecha.dia);
            validardia = validarDiaMes(mercados.fecha.dia, mercados.fecha.mes, mercados.fecha.anio);
            if (!validardia)
                printf("Ingrese un dia valido correspondiente al mes\n");
        }while (!validardia);

        printf("9) Direccion \n");

        do
        {
            printf("Calle: ");
            fflush(stdin);
            gets(mercados.direccion.calle);
            if (!(validarchar(mercados.direccion.calle)))
                printf("Ingrese calle valida.\n");

        } while (!(validarchar(mercados.direccion.calle)));

        do
        {
            printf("Numero: ");
            gets(mercados.direccion.numero);
            if (!(validarnumerodireccion(mercados.direccion.numero)))
                printf("Ingrese un numero valido.\n");

        } while (!(validarnumerodireccion(mercados.direccion.numero)));

        do
        {
            printf("Colonia: ");
            fflush(stdin);
            gets(mercados.direccion.colonia);
            if (!(validarchar(mercados.direccion.colonia)))
                printf("Ingrese una colonia valida.\n");

        } while (!(validarchar(mercados.direccion.colonia)));

        do
        {
            printf("Municipio: ");
            fflush(stdin);
            gets(mercados.direccion.municipio);
            if (!(validarchar(mercados.direccion.municipio)))
                printf("Ingrese municipio valida.\n");

        } while (!(validarchar(mercados.direccion.municipio)));

        do
        {
            printf("Ingrese el estado: ");
            fflush(stdin);
            gets(mercados.direccion.estado);
            if (!(validarchar(mercados.direccion.estado)))
                printf("Ingrese un estado valido.\n");

        }while (!(validarchar(mercados.direccion.estado)));

        fseek(mercadosf, (mercados.clave_mercado - 1) * sizeof(struct Mercado), SEEK_SET);
        fwrite(&mercados, sizeof(struct Mercado), 1, mercadosf);

        do
        {
            printf("Agregar otro mercado (S/N): ");
            fflush(stdin);
            scanf("%c", &agregar);
            if (agregar != 'S' && agregar != 's' && agregar != 'N' && agregar != 'n')
                printf("Valor no valido.\nSolo se permite S o N.\n");

        } while (agregar != 'S' && agregar != 's' && agregar != 'N' && agregar != 'n');
    }
}

void menu_control_ventas(FILE *fventas)
{
    int clave_mercado, clave_articulo, Cantidad_articulo, num_empleado, anio_venta, mes_venta, dia_venta, clave_valida;
    float precioarticulo, total, descuento_mercado;
    char agregar_articulo, factura, agregar_venta = 'S', articulo_descripcion[150];
    FILE *articulof, *empleadof;
    struct Articulos articuloleido;
    bool validardia = true;
    time_t t = time(NULL);
    struct tm *tm_info;
    time(&t);

    tm_info = localtime(&t);
    dia_venta = tm_info->tm_mday;
    mes_venta = tm_info->tm_mon + 1;
    anio_venta = tm_info->tm_year + 1900;

    empleadof = fopen("Empleados.dat", "r");
    if (empleadof == NULL)
    {
        printf("Error al abrir el archivo de empleados.\n");
        return;
    }
        
    printf("$$\\    $$\\                       $$\\                          \n");
    printf("$$ |   $$ |                      $$ |                         \n");
    printf("$$ |   $$ | $$$$$$\\  $$$$$$$\\  $$$$$$\\    $$$$$$\\   $$$$$$$\\ \n");
    printf("\\$$\\  $$  |$$  __$$\\ $$  __$$\\ \\_$$  _|   \\____$$\\ $$  _____| \n");
    printf(" \\$$\\$$  / $$$$$$$$ |$$ |  $$ |  $$ |     $$$$$$$ |\\$$$$$$$\\ \n");
    printf("  \\$$$  /  $$   ____|$$ |  $$ |  $$ |$$\\ $$  __$$ | \\____$$\\ \n");
    printf("   \\$  /   \\$$$$$$$\\ $$ |  $$ |  \\$$$$  |\\$$$$$$$ |$$$$$$$  | \n");
    printf("    \\_/     \\_______|\\__|  \\__|   \\____/  \\_______|\\_______/ \n");

    printf("\nINGRESA LA INFORMACION.\n\n");

    while (agregar_venta != 'n' && agregar_venta != 'N')
    {
        total = 0;

        do
        {
            printf("1) Ingrese la clave de mercado: ");
            scanf("%d", &clave_mercado);

            if (!validarmercado(clave_mercado))
                printf("\nClave de mercado no encontrada.\n");

        } while (!validarmercado(clave_mercado));

        do
        {
            printf("2) Ingrese la clave del articulo: ");
            scanf("%d", &clave_articulo);

            if (!validararticulo(clave_articulo))
                printf("Clave de articulo no encontrada.\n");

        } while (!validararticulo(clave_articulo));

        do
        {
            do
            {
                printf("3) Ingrese la cantidad: ");
                scanf("%d", &Cantidad_articulo);

                if (Cantidad_articulo < 0)
                    printf("Por favor, ingresa una cantidad mayor a 0.\n");
            } while (Cantidad_articulo < 0);

            clave_valida = validarcantidad(Cantidad_articulo, clave_articulo);

            if (clave_valida == 0 || clave_valida == 3)
            {
                printf("No se puede proceder con la venta.\n");
                system("pause");
                agregar_venta = 'n';
            }
        } while (clave_valida != 1 && agregar_venta != 'n');

        precioarticulo = precio(clave_articulo, &articulo_descripcion);
        printf("4) Precio del articulo: $%.2f\n", precioarticulo);
        descuento_mercado = descuento(clave_mercado);
        total += precioarticulo * Cantidad_articulo * (1 - descuento_mercado);

        if (clave_valida == 1)
        {
            do
            {
                printf("5) Número de empleado: ");
                scanf("%d", &num_empleado);

                if (!validarempleado(num_empleado, empleadof))
                    printf("Numero de empleado no encontrado.\n");

            } while (!validarempleado(num_empleado, empleadof));

            do
            {
                printf("Deseas agregar otro articulo? (S/N): ");
                fflush(stdin);
                scanf("%c", &agregar_articulo);

                if (agregar_articulo != 'S' && agregar_articulo != 's' &&
                    agregar_articulo != 'N' && agregar_articulo != 'n')
                    printf("Respuesta no valida. Solo se permite S o N.\n");

            } while (agregar_articulo != 'S' && agregar_articulo != 's' &&
                     agregar_articulo != 'N' && agregar_articulo != 'n');

            printf("Total de la venta (con descuento aplicado): $%.2f\n", total);

            do
            {
                printf("Deseas recibir una factura? (S/N): ");
                fflush(stdin);
                scanf("%c", &factura);

                if (factura != 'S' && factura != 's' && factura != 'N' && factura != 'n')
                    printf("Respuesta no valida. Solo se permite S o N.\n");

            } while (factura != 'S' && factura != 's' &&
                     factura != 'N' && factura != 'n');

            if (factura == 'S' || factura == 's')
                imprimir_factura(clave_mercado, clave_articulo, articulo_descripcion,
                                 Cantidad_articulo, precioarticulo, num_empleado,
                                 total, dia_venta, mes_venta, anio_venta, descuento_mercado);

            fprintf(fventas, "Clave mercado: %d\n", clave_mercado);
            fprintf(fventas, "Clave articulo: %d\n", clave_articulo);
            fprintf(fventas, "Cantidad: %d\n", Cantidad_articulo);
            fprintf(fventas, "Precio: %.2f\n", precioarticulo);
            fprintf(fventas, "Num. empleado: %d\n", num_empleado);
            fprintf(fventas, "Comision: %.2f\n", generar_comision(num_empleado, total));
            fprintf(fventas, "Fecha de venta: %02d/%02d/%04d\n", dia_venta, mes_venta, anio_venta);
            fprintf(fventas, "Total: %.2f\n", total);

            do
            {
                printf("Deseas iniciar otra venta? (S/N): ");
                fflush(stdin);
                scanf("%c", &agregar_venta);

                if (agregar_venta != 'S' && agregar_venta != 's' &&
                    agregar_venta != 'N' && agregar_venta != 'n')
                    printf("Respuesta no valida. Solo se permite S o N.\n");

            } while (agregar_venta != 'S' && agregar_venta != 's' &&
                     agregar_venta != 'N' && agregar_venta != 'n');
        }
    }
    fclose(empleadof);
}

void menu_control_compras(FILE *fcompras)
{
    int Num_proveedor, insumo, cantidad, id_compra = 0, ultimo_id_compra = 0, provedor;
    float precio_insumo, total = 0, descuento, precio;
    char agregar_insumo, agregar_compra = 's', entregado = 'n';

    printf(" $$$$$$\\                                                                  \n");
    printf("$$  __$$\\                                                                 \n");
    printf("$$ /  \\__| $$$$$$\\  $$$$$$\\$$$$\\   $$$$$$\\   $$$$$$\\   $$$$$$\\   $$$$$$$\\ \n");
    printf("$$ |      $$  __$$\\ $$  _$$  _$$\\ $$  __$$\\ $$  __$$\\  \\____$$\\ $$  _____| \n");
    printf("$$ |      $$ /  $$ |$$ / $$ / $$ |$$ /  $$ |$$ |  \\__| $$$$$$$ |\\$$$$$$$\\ \n");
    printf("$$ |  $$\\ $$ |  $$ |$$ | $$ | $$ |$$ |  $$ |$$ |      $$  __$$ | \\____$$\\ \n");
    printf("\\$$$$$$  |\\$$$$$$  |$$ | $$ | $$ |$$$$$$$  |$$ |      \\$$$$$$$ |$$$$$$$  | \n");
    printf(" \\______/  \\______/ \\__| \\__| \\__|$$  ____/ \\__|       \\_______|\\_______/ \n");
    printf("                                  $$ |                                     \n");
    printf("                                  $$ |                                     \n");
    printf("                                  \\__|                                     \n");
    printf("\nINGRESA LA INFORMACION.\n\n");

    while (fscanf(fcompras, "ID compra: %d\n", &id_compra) == 1)
    {
        if (id_compra > ultimo_id_compra)
            ultimo_id_compra = id_compra;

        for (int i = 0; i < 6; i++)
            fscanf(fcompras, "%*[^\n]\n");
    }
    id_compra = ultimo_id_compra + 1;
    
    while(agregar_compra == 'S' || agregar_compra == 's')
    {
        total = 0;
        agregar_insumo = 's';
        do
        {
            printf("1) Numero de proveedor: ");
            scanf("%d", &Num_proveedor);

            if (!validarproveedor(Num_proveedor))
                printf("Numero de proveedor invalido.\n");

        } while (!validarproveedor(Num_proveedor));

        while (agregar_insumo == 's' || agregar_insumo == 'S')
        {
            do
            {
                printf("2) Numero de insumo: ");
                scanf("%d", &insumo);

                if (!validarnumeroinsumo(insumo))
                    printf("Numero de insumo invalido.\n");

            } while (!validarnumeroinsumo(insumo));

            do
            {
                printf("3) Cantidad: ");
                scanf("%d", &cantidad);

                if (cantidad < 0)
                    printf("Cantidad invalida.\n");

            } while (cantidad < 0);

            precio_insumo = precioinsumo(insumo);
            printf("\n* Precio unitario del insumo: $%.2f *\n", precio_insumo);

            descuento = descuento_proveedor(Num_proveedor);
            printf("Con un descuento del: %%%.2f\n", descuento * 100);
            total += precio_insumo * cantidad * (1 - descuento);

            fprintf(fcompras, "ID compra: %d\n", id_compra);
            fprintf(fcompras, "Numero de proveedor: %d\n", Num_proveedor);
            fprintf(fcompras, "Numero de insumo: %d\n", insumo);
            fprintf(fcompras, "Cantidad: %d\n", cantidad);
            fprintf(fcompras, "Precio: %.2f\n", precio_insumo);
            fprintf(fcompras, "Entregado: %c\n", entregado);

            do
            {
                printf("Agregar otro insumo? (S/N): ");
                fflush(stdin);
                scanf("%c", &agregar_insumo);

                if (agregar_insumo != 'S' && agregar_insumo != 's' && agregar_insumo != 'N' && agregar_insumo != 'n')
                    printf("Valor no valido. Solo se permite S o N.\n");

            } while (agregar_insumo != 'S' && agregar_insumo != 's' && agregar_insumo != 'N' && agregar_insumo != 'n');
        }

        printf("Total de la compra: $%.2f\n", total);
        fprintf(fcompras, "Total: %.2f\n\n", total);

        do
        {
            printf("Agregar otra compra? (S/N): ");
            fflush(stdin);
            scanf("%c", &agregar_compra);

            if (agregar_compra != 'S' && agregar_compra != 's' && agregar_compra != 'N' && agregar_compra != 'n')
                printf("Valor no valido. Solo se permite S o N.\n");

        }while(agregar_compra != 'S' && agregar_compra != 's' && agregar_compra != 'N' && agregar_compra != 'n');

        if (agregar_compra == 's' || agregar_compra == 'S')
            id_compra++;
    }
}

void menu_control_inventario(FILE *farchivo) {
    int num_proveedor, numero_compra, id_compras = 0, clave_insumo, cantidad, num_proveedorFile;
    int pos_compra = -1, opcion, proveedores_faltantes[100], i;
    char recepcion = 's', respuesta[5], entregado;
    struct Insumo insumoLeido;
    FILE *archivo_insumo;
    float precio, total;

    printf("$$$$$$\\                                            $$\\                         $$\\           \n");
    printf("\\_$$  _|                                           $$ |                        \\__|          \n");
    printf("  $$ |  $$$$$$$\\  $$\\    $$\\  $$$$$$\\  $$$$$$$\\  $$$$$$\\    $$$$$$\\   $$$$$$\\  $$\\  $$$$$$\\  \n");
    printf("  $$ |  $$  __$$\\ \\$$\\  $$  |$$  __$$\\ $$  __$$\\ \\_$$  _|   \\____$$\\ $$  __$$\\ $$ |$$  __$$\\ \n");
    printf("  $$ |  $$ |  $$ | \\$$\\$$  / $$$$$$$$ |$$ |  $$ |  $$ |     $$$$$$$ |$$ |  \\__|$$ |$$ /  $$ | \n");
    printf("  $$ |  $$ |  $$ |  \\$$$  /  $$   ____|$$ |  $$ |  $$ |$$\\ $$  __$$ |$$ |      $$ |$$ |  $$ | \n");
    printf("$$$$$$\\ $$ |  $$ |   \\$  /   \\$$$$$$$\\ $$ |  $$ |  \\$$$$  |\\$$$$$$$ |$$ |      $$ |\\$$$$$$  | \n");
    printf("\\______|\\__|  \\__|    \\_/     \\_______|\\__|  \\__|   \\____/  \\_______|\\__|      \\__| \\______/  \n\n\n");

    opcion = verificar_entregas(farchivo);

    switch (opcion)
    {
        case 1:
            printf("¡Todas las compras han sido entregadas!\n");
            system("pause");
            return;
            break;
        case 2:
            printf("No hay compras registradas en el archivo.\n");
            system("pause");
            return;
            break;
        case 3:
        printf("Aún hay compras pendientes de entrega!\n");

        for (i = 0; i < 100; i++) {
            proveedores_faltantes[i] = -1;
        }

        lista_proveedores_no_entregado(farchivo, proveedores_faltantes);

        printf("Proveedores con compras no entregadas:\n");
        for (i = 0; proveedores_faltantes[i] != -1; i++) {
            printf("\tProveedor: %d\n", proveedores_faltantes[i]);
        }
        break;

    }
    
    printf("\nINGRESA LA INFORMACION.\n\n");

    while (recepcion == 'S' || recepcion == 's') {
        archivo_insumo = fopen("Insumos.dat", "r+");
        if (archivo_insumo == NULL) {
            printf("Error al abrir el archivo de insumos.\n");
            return;
        }

        do {
            printf("1) Número de proveedor: ");
            scanf("%d", &num_proveedor);

            if (!validarproveedor(num_proveedor))
                printf("Número de proveedor inválido. Ingresa uno existente.\n");
        } while (!validarproveedor(num_proveedor));

        printf("+--------------------+--------------------+------------------------------------------+--------------------+\n");
        printf("| %-18s | %-18s | %-40s | %-18s |\n", "ID Compra", "Insumo", "Descripcion", "Cantidad");
        printf("+--------------------+--------------------+------------------------------------------+--------------------+\n");

        rewind(farchivo);
        while (fscanf(farchivo, "ID compra: %d\n", &id_compras) == 1) {
            long start_position = ftell(farchivo); 

            fscanf(farchivo, "Numero de proveedor: %d\n", &num_proveedorFile);
            fscanf(farchivo, "Numero de insumo: %d\n", &clave_insumo);
            fscanf(farchivo, "Cantidad: %d\n", &cantidad);
            fscanf(farchivo, "Precio: %f\n", &precio);
            fscanf(farchivo, "Entregado: %c\n", &entregado);
            fscanf(farchivo, "Total: %f\n", &total);

            if (num_proveedor == num_proveedorFile && entregado == 'n') {
                fseek(archivo_insumo, (clave_insumo - 1) * sizeof(struct Insumo), SEEK_SET);
                fread(&insumoLeido, sizeof(struct Insumo), 1, archivo_insumo);

                printf("| %-18d | %-18d | %-40s | %-18d |\n", id_compras, clave_insumo, insumoLeido.descripcion, cantidad);
            }
        }

        printf("+--------------------+--------------------+------------------------------------------+--------------------+\n");

        do {
            printf("2) ID de compra: ");
            scanf("%d", &numero_compra);

            rewind(farchivo);
            pos_compra = -1;

            while (fscanf(farchivo, "ID compra: %d\n", &id_compras) == 1) {
                long posicion_inicial = ftell(farchivo);

                fscanf(farchivo, "Numero de proveedor: %d\n", &num_proveedorFile);
                fscanf(farchivo, "Numero de insumo: %d\n", &clave_insumo);
                fscanf(farchivo, "Cantidad: %d\n", &cantidad);
                fscanf(farchivo, "Precio: %f\n", &precio);
                fscanf(farchivo, "Entregado: %c\n", &entregado);
                fscanf(farchivo, "Total: %f\n", &total);

                if (numero_compra == id_compras) {
                    pos_compra = posicion_inicial - 14;
                    break;
                }
            }

            if (pos_compra == -1) {
                printf("Número de compra inválido.\n");
            }
        } while (pos_compra == -1);

        do {
            printf("¿Le fue recibida la compra? (si/no): ");
            scanf("%s", respuesta);

            if (strcmp(respuesta, "si") != 0 && strcmp(respuesta, "no") != 0) {
                printf("Respuesta inválida. Ingresa 'si' o 'no'.\n");
            }
        } while (strcmp(respuesta, "si") != 0 && strcmp(respuesta, "no") != 0);

        if (strcmp(respuesta, "si") == 0) {
            fseek(archivo_insumo, (clave_insumo - 1) * sizeof(struct Insumo), SEEK_SET);
            fread(&insumoLeido, sizeof(struct Insumo), 1, archivo_insumo);

            insumoLeido.inventario += cantidad;

            fseek(archivo_insumo, (clave_insumo - 1) * sizeof(struct Insumo), SEEK_SET);
            fwrite(&insumoLeido, sizeof(struct Insumo), 1, archivo_insumo);

            fseek(farchivo, pos_compra, SEEK_SET);
            fprintf(farchivo, "ID compra: %d\n", id_compras);
            fprintf(farchivo, "Numero de proveedor: %d\n", num_proveedorFile);
            fprintf(farchivo, "Numero de insumo: %d\n", clave_insumo);
            fprintf(farchivo, "Cantidad: %d\n", cantidad);
            fprintf(farchivo, "Precio: %.2f\n", precio);
            fprintf(farchivo, "Entregado: %c\n", 's');
            fprintf(farchivo, "Total: %.2f\n", total);
        }

        do {
            printf("¿Agregar otra recepción? (S/N): ");
            scanf(" %c", &recepcion);

            if (recepcion != 'S' && recepcion != 's' && recepcion != 'N' && recepcion != 'n') {
                printf("Valor no válido. Solo se permite S o N.\n");
            }
        } while (recepcion != 'S' && recepcion != 's' && recepcion != 'N' && recepcion != 'n');

        fclose(archivo_insumo);
    }
}

void menu_reportes() {
    char opcion;
    FILE *archivo, *archivo_compras;
    struct Articulos articulo;
    int i, anio_venta, dia_venta, mes_venta, clavearticuloreporte, clavearticulo;
    int dia_reporte, mes_reporte, anio_reporte, num_empleados = 0, id_compra, num_proveedor, clave_insumo, cantidad;
    bool validardia = false, hay_comision = false;
    float total, total_reportes = 0.0, articulostotal = 0.0, preciocompra;
    struct Empleado *empleados;
    char entregado;

    do {
        printf("$$$$$$$\\                                            $$\\                         \n");
        printf("$$  __$$\\                                           $$ |                        \n");
        printf("$$ |  $$ | $$$$$$\\   $$$$$$\\   $$$$$$\\   $$$$$$\\  $$$$$$\\    $$$$$$\\   $$$$$$$\\ \n");
        printf("$$$$$$$  |$$  __$$\\ $$  __$$\\ $$  __$$\\ $$  __$$\\ \\_$$  _|  $$  __$$\\ $$  _____| \n");
        printf("$$  __$$< $$$$$$$$ |$$ /  $$ |$$ /  $$ |$$ |  \\__|  $$ |    $$$$$$$$ |\\$$$$$$\\  \n");
        printf("$$ |  $$ |$$   ____|$$ |  $$ |$$ |  $$ |$$ |        $$ |$$\\ $$   ____| \\\\____$$\\ \n");
        printf("$$ |  $$ |\\$$$$$$$\\ $$$$$$$  |\\$$$$$$  |$$ |        \\\\\$$$  |\\$$$$$$$\\ $$$$$$$  | \n");
        printf("\\__|  \\__| \\\\_______|$$  ____/  \\______/ \\__|         \\\\\____/  \\\\_______|\\_______/  \n");
        printf("                    $$ |                                                         \n");
        printf("                    $$ |                                                         \n");
        printf("                    \\__|                                                         \n\n");
        printf("a) Listado de articulos\nb) Total de venta por fecha\nc) Total de venta por articulo\n");
        printf("d) Listado de articulos a solicitar\ne) Saldos por pagar\nf) Calculo de comisiones\ng) Compras pendientes de recepcion\nh) Salir\n");
        printf("%20s", "\nOpcion: ");
        fflush(stdin);
        scanf(" %c", &opcion);

        if (opcion < 'a' || opcion > 'h') {
            printf("Ingrese una opcion valida\n");
        }

    } while (opcion < 'a' || opcion > 'h');

    while (opcion != 'h') 
    {
        switch (opcion) 
        {
            case 'a':
            {
                if ((archivo = fopen("Articulos.dat", "r")) == NULL) 
                    printf("ERROR.\nNo se pudo abrir el archivo.\n");
                else {
                    printf("\n---------------------------------------------------------------------------------------------------------------\n");
                    printf("%-20s %-20s %-10s %-10s %-10s %-15s %-20s\n",
                        "Clave del Articulo", "Descripcion", "Siembra", "Cosecha",
                        "Inventario", "Precio de venta", "Clave del Insumo");
                    printf("---------------------------------------------------------------------------------------------------------------\n");

                    while (fread(&articulo, sizeof(struct Articulos), 1, archivo) == 1) 
                    {
                        if (articulo.clave_articulo == 0)
                            continue;
                        else {
                            printf("%-20d %-20s %-10s %-10s %-10d %-15.2f [",
                            articulo.clave_articulo, articulo.descripcion, articulo.temp_siembra,
                            articulo.temp_cosecha, articulo.inventario, articulo.precio_venta);

                            int primero = 1; 
                            for (i = 0; i < 10; i++) 
                            {
                                if (articulo.insumos_requeridos[i] != 0) 
                                {
                                    if (!primero) 
                                        printf(", ");
                                    printf("%d", articulo.insumos_requeridos[i]);
                                    primero = 0;
                                }
                            }
                            printf("]\n");
                        }
                    }
                }
                fclose(archivo);
                printf("\nEstos son los articulos registrados.\n");
                system("pause");
            }
            break;

            case 'b':
            {
                if ((archivo = fopen("Ventas.txt", "r")) == NULL) 
                    printf("ERROR.\nNo se pudo abrir el archivo.\n");
                else {
                    do {
                        printf("\nAño: ");
                        scanf("%d", &anio_reporte);
                        if (anio_reporte < 1990 || anio_reporte > 2024) {
                            printf("Año de venta invalido, debe de estar entre 1990 y 2024\n");
                        }
                    } while (anio_reporte < 1990 || anio_reporte > 2024);

                    do {
                        printf("Mes: ");
                        scanf("%d", &mes_reporte);
                        if (mes_reporte < 1 || mes_reporte > 12) {
                            printf("Mes invalido, debe de estar entre 1 y 12\n");
                        }
                    } while (mes_reporte < 1 || mes_reporte > 12);

                    do {
                        printf("Dia: ");
                        scanf("%d", &dia_reporte);
                        validardia = validarDiaMes(dia_reporte, mes_reporte, anio_reporte);
                        if (!validardia) {
                            printf("Ingrese un dia valido correspondiente al mes\n");
                        }
                    } while (!validardia);

                    total_reportes = 0.0;

                    while (fscanf(archivo, 
                                "Clave mercado: %*d\n"
                                "Clave articulo: %*d\n"
                                "Cantidad: %*d\n"
                                "Precio: %*f\n"
                                "Num. empleado: %*d\n"
                                "Comision: %*f\n"
                                "Fecha de venta: %02d/%02d/%04d\n"
                                "Total: %f\n", 
                                &dia_venta, &mes_venta, &anio_venta, &total) == 4) {
                        if (dia_reporte == dia_venta && mes_reporte == mes_venta && anio_reporte == anio_venta) {
                            total_reportes += total;
                        }
                    }

                    if (total_reportes > 0) {
                        printf("\nEl total de ventas para el %02d/%02d/%04d es: $ %.2f\n", 
                            dia_reporte, mes_reporte, anio_reporte, total_reportes);
                    } else {
                        printf("\nNo hay ventas registradas para la fecha %02d/%02d/%04d\n", 
                            dia_reporte, mes_reporte, anio_reporte);
                    }
                    system("pause");
                    fclose(archivo);
                }
            }
            break;

            case 'c':
                if ((archivo = fopen("Ventas.txt", "r")) == NULL) 
                    printf("ERROR.\nNo se pudo abrir el archivo.\n");
                else {
                    printf("\nIngrese la clave del articulo: ");
                    scanf("%d", &clavearticuloreporte);

                    while (fscanf(archivo, 
                        "Clave mercado: %*d\n"
                        "Clave articulo: %d\n"
                        "Cantidad: %*d\n"
                        "Precio: %*f\n"
                        "Num. empleado: %*d\n"
                        "Comision: %*f\n"
                        "Fecha de venta: %*02d/%*02d/%*04d\n"
                        "Total: %f\n", &clavearticulo, &total) == 2) {
                            if (clavearticuloreporte == clavearticulo) 
                                articulostotal += total;
                    }

                    if (articulostotal > 0) 
                        printf("El total de ventas para el articulo %d es: $ %.2f\n", clavearticuloreporte, articulostotal);
                    else 
                        printf("No hay ventas registradas para el articulo %d\n", clavearticuloreporte);
                    system("pause");
                }
                fclose(archivo);
                break;

            case 'd':
                printf("Funcionalidad no implementada.\n");
                break;

            case 'e':
                {
                    if ((archivo_compras = fopen("Compras.txt", "r")) == NULL) {
                        printf("ERROR.\nNo se pudo abrir el archivo de compras.\n");
                    } else {
                        printf("\n--- REPORTE DE SALDOS POR PAGAR ---\n");
                        printf("+--------------------+--------------------+\n");
                        printf("| Numero Proveedor   | Saldo por Pagar    |\n");
                        printf("+--------------------+--------------------+\n");

                        int proveedor_actual;
                        float saldo_pendiente = 0;
                        int hay_saldo = 0;

                        while (fscanf(archivo_compras, "ID compra: %d\n", &id_compra) == 1) {
                            fscanf(archivo_compras, "Numero de proveedor: %d\n", &num_proveedor);
                            fscanf(archivo_compras, "Numero de insumo: %d\n", &clave_insumo);
                            fscanf(archivo_compras, "Cantidad: %d\n", &cantidad);
                            fscanf(archivo_compras, "Precio: %f\n", &preciocompra);
                            fscanf(archivo_compras, "Entregado: %c\n", &entregado);
                            fscanf(archivo_compras, "Total: %f\n", &total);

                            
                            if (entregado == 'n') {
                                saldo_pendiente += total;
                                proveedor_actual = num_proveedor;
                                hay_saldo = 1;
                            }
                        }

                        fclose(archivo_compras);

                        if (hay_saldo) {
                            printf("| %-18d | %-18.2f |\n", proveedor_actual, saldo_pendiente);
                            printf("+--------------------+--------------------+\n");
                            system("pause");
                        } else {
                            printf("No se encontraron saldos por pagar.\n");
                        }
                    }

                }
                break;

            case 'f':
                {
                    if ((archivo = fopen("Empleados.dat", "r")) == NULL)
                        printf("Error al abrir el archivo de empleados.\n");
                    else
                    {
                        fseek(archivo, 0, SEEK_END);
                        num_empleados = ftell(archivo) / sizeof(struct Empleado);
                        rewind(archivo);

                        empleados = (struct Empleado*) malloc(num_empleados * sizeof(struct Empleado));
                        if (empleados == NULL)
                        {
                            printf("Error al asignar memoria.\n");
                            fclose(archivo);
                        }

                        fread(empleados, sizeof(struct Empleado), num_empleados, archivo);
                        fclose(archivo);

                        printf("-------------------------------------------------------------------------------------------------------------\n");
                        printf("| %-9s | %-40s | %-15s | %-8s | %-18s | %-40s |\n",
                                "Num Empl", "Nombre Completo", "RFC", "Comision", "Fecha contratación", "Dirección");
                        printf("-------------------------------------------------------------------------------------------------------------\n");


                        for (int i = 0; i < num_empleados; i++)
                        {
                            if (empleados[i].comision > 0)
                            {
                                hay_comision = true;
                                printf("| %-9d | %-40s | %-15s | %-8.2f | %02d/%02d/%04d     | %s, %s, %s, %s |\n",
                                    empleados[i].numero_empleado,
                                    empleados[i].nombre_completo,
                                    empleados[i].RFC,
                                    empleados[i].comision,
                                    empleados[i].fecha.dia,
                                    empleados[i].fecha.mes,
                                    empleados[i].fecha.anio,
                                    empleados[i].direccion.calle,
                                    empleados[i].direccion.numero,
                                    empleados[i].direccion.colonia,
                                    empleados[i].direccion.estado);
                            }
                        }
                        if (!hay_comision)
                            printf("No se encontraron empleados con comision.\n");

                        printf("-------------------------------------------------------------------------------------------------------------\n");
                        system("pause");
                        free(empleados);
                    }
                    fclose(archivo);
                }
                break;
            
            case 'g':
            {
                if ((archivo_compras = fopen("Compras.txt", "r")) == NULL)
                    printf("ERROR.\nNo se pudo abrir el archivo de compras.\n");
                else {
                    printf("\n--- REPORTE DE COMPRAS PENDIENTES DE RECIBIR ---\n");
                    printf("+------------+--------------------+--------------------+--------------------+----------+---------+\n");
                    printf("| %-10s | %-18s | %-18s | %-18s | %-8s | %-7s |\n",
                        "ID Compra", "Numero Proveedor", "Clave Insumo", "Cantidad", "Precio", "Total");
                    printf("+------------+--------------------+--------------------+--------------------+----------+---------+\n");

                    while (fscanf(archivo_compras, "ID compra: %d\n", &id_compra) == 1) {
                        fscanf(archivo_compras, "Numero de proveedor: %d\n", &num_proveedor);
                        fscanf(archivo_compras, "Numero de insumo: %d\n", &clave_insumo);
                        fscanf(archivo_compras, "Cantidad: %d\n", &cantidad);
                        fscanf(archivo_compras, "Precio: %f\n", &preciocompra);
                        fscanf(archivo_compras, "Entregado: %c\n", &entregado);
                        fscanf(archivo_compras, "Total: %f\n", &total);

                        if (entregado == 'n') {
                            printf("| %-10d | %-18d | %-18d | %-18d | %-8.2f | %-7.2f |\n",
                                id_compra, num_proveedor, clave_insumo, cantidad, preciocompra, total);
                        }
                    }
                    printf("+------------+--------------------+--------------------+--------------------+----------+---------+\n");
                }
                fclose(archivo_compras);
                system("pause");
            }
            break;

        }

        do {
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
            printf("$$$$$$$\\                                            $$\\                         \n");
            printf("$$  __$$\\                                           $$ |                        \n");
            printf("$$ |  $$ | $$$$$$\\   $$$$$$\\   $$$$$$\\   $$$$$$\\  $$$$$$\\    $$$$$$\\   $$$$$$$\\ \n");
            printf("$$$$$$$  |$$  __$$\\ $$  __$$\\ $$  __$$\\ $$  __$$\\ \\_$$  _|  $$  __$$\\ $$  _____| \n");
            printf("$$  __$$< $$$$$$$$ |$$ /  $$ |$$ /  $$ |$$ |  \\__|  $$ |    $$$$$$$$ |\\$$$$$$\\  \n");
            printf("$$ |  $$ |$$   ____|$$ |  $$ |$$ |  $$ |$$ |        $$ |$$\\ $$   ____| \\\\____$$\\ \n");
            printf("$$ |  $$ |\\$$$$$$$\\ $$$$$$$  |\\$$$$$$  |$$ |        \\\\\$$$  |\\$$$$$$$\\ $$$$$$$  | \n");
            printf("\\__|  \\__| \\\\_______|$$  ____/  \\______/ \\__|         \\\\\____/  \\\\_______|\\_______/  \n");
            printf("                    $$ |                                                         \n");
            printf("                    $$ |                                                         \n");
            printf("                    \\__|                                                         \n");
            printf("a) Listado de articulos\nb) Total de venta por fecha\nc) Total de venta por articulo\n");
            printf("d) Listado de articulos a solicitar\ne) Saldos por pagar\nf) Calculo de comisiones\ng) Compras pendientes de recepcion\nh) Salir\n");
            printf("%20s", "\nOpcion: ");
            fflush(stdin);
            scanf(" %c", &opcion);

            if (opcion < 'a' || opcion > 'h') {
                printf("Ingrese una opcion valida\n");
            }

        } while (opcion < 'a' || opcion > 'h');
    }
}


void lista_proveedores_no_entregado(FILE *farchivo, int *lista) {
    char entregado;
    int num_proveedor, i = 0;
    int Id;

    rewind(farchivo); 

    while (fscanf(farchivo, "ID compra: %d\n", &Id) == 1) {
        fscanf(farchivo, "Numero de proveedor: %d\n", &num_proveedor);
        fscanf(farchivo, "Numero de insumo: %*d\n");
        fscanf(farchivo, "Cantidad: %*d\n");
        fscanf(farchivo, "Precio: %*f\n");
        fscanf(farchivo, "Entregado: %c\n", &entregado);
        fscanf(farchivo, "Total: %*f\n");

        if (entregado == 'n') {
            
            int ya_en_lista = 0;
            for (int j = 0; j < i; j++) {
                if (lista[j] == num_proveedor) {
                    ya_en_lista = 1;
                    break;
                }
            }

            if (!ya_en_lista && i < 100) {
                lista[i] = num_proveedor;
                i++;
            }
        }
    }

    if (i < 100) {
        lista[i] = -1;
    }
}

int verificar_entregas(FILE *farchivo) {
    char entregado;
    int total_compras = 0;
    int entregadas = 0,Id;

    rewind(farchivo);
    while (fscanf(farchivo, "ID compra: %d\n", &Id) == 1) {
       
        fscanf(farchivo, "Numero de proveedor: %*d\n");
        fscanf(farchivo, "Numero de insumo: %*d\n");
        fscanf(farchivo, "Cantidad: %*d\n");
        fscanf(farchivo, "Precio: %*f\n");
        fscanf(farchivo, "Entregado: %c\n", &entregado);
        fscanf(farchivo, "Total: %*f\n");

        total_compras++;
        if (entregado == 's') 
            entregadas++; 
    }

    if (total_compras == 0)
        return 2; 
    else if (total_compras == entregadas)
        return 1; 
    else 
        return 3; 
}

bool validar_rfc(char *frfc)
{
    int i;


    if (strlen(frfc) != 13)
        return false;


    for (i = 0; i < 4; i++)
    {
        if (!((frfc[i] >= 'A' && frfc[i] <= 'Z') || (frfc[i] >= 'a' && frfc[i] <= 'z')))
            return false;
    }


    for (i = 4; i < 10; i++)
    {
        if (frfc[i] < '0' || frfc[i] > '9')
            return false;
    }


    for (i = 10; i < 13; i++)
    {
        if (!((frfc[i] >= 'A' && frfc[i] <= 'Z') || (frfc[i] >= 'a' && frfc[i] <= 'z') || (frfc[i] >= '0' && frfc[i] <= '9')))
            return false;
    }

    return true;
}

bool validar_correo(char * fcorreo)
{
    int arroba = 0, punto = 0, i;

    for(i = 0; fcorreo[i] != '\0'; i++)
    {
        if(fcorreo[i] == '@')
            arroba = i;

        else if(fcorreo[i] == '.')
            punto = i;
    }

    if(arroba != -0 && punto != -0 && punto > arroba + 1)
        return true;

    else
        return false;
}

bool validarDiaMes(int fdia, int fmes, int fanio)
{
    int diasEnMes;

    switch (fmes)
    {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            diasEnMes = 31;
            break;
        case 4: case 6: case 9: case 11:
            diasEnMes = 30;
            break;
        case 2:
            if ((fanio % 4 == 0 && fanio % 100 != 0) || (fanio % 400 == 0))
                diasEnMes = 29;
            else
                diasEnMes = 28;
            break;
    }
    return fdia >= 1 && fdia <= diasEnMes;
}

bool validarchar(char * fcadena)
{
    bool todoschar=true;
    int i=0;

    while ((fcadena[i] != '\0') && (todoschar))
    {
        if ((fcadena[i] >= 'A' && fcadena[i] <= 'Z') || (fcadena[i] >= 'a' && fcadena[i] <= 'z') || fcadena[i] == ' ')
            todoschar=true;
        else
            todoschar=false;

        i++;
    }
    return(todoschar);
}

bool validarnumerodireccion(char *fnumero)
{
    int i, len = strlen(fnumero);

    for (i = 0; i < len; i++)
    {
        if (fnumero[i] < '0' || fnumero[i] > '9')
            return false;
    }
    return true;
}

float generar_comision(int num_empleado, float total)
{
    FILE *empleadof;
    struct Empleado lectura_empleado;
    float comision;

    if((empleadof = fopen("Empleados.dat", "r")) == NULL)
        printf("Lo siento no podemos abrir el archivo empleados.\n");
    else
    {
        fseek(empleadof, (num_empleado - 1) * sizeof(struct Empleado), SEEK_SET);
        fread(&lectura_empleado, sizeof(struct Empleado), 1, empleadof);
        comision = lectura_empleado.comision * total;
    }
    fclose(empleadof);
    return comision;
}

bool validarmercado(int fmercado)
{
    FILE *mercado;
    struct Mercado mercados;
    bool mercadovalido = false;


    if((mercado = fopen("Mercados.dat", "r")) == NULL)
        printf("Error con el archivo de mercados\n");

    else
    {
        fseek(mercado, (fmercado - 1) * sizeof(struct Mercado), SEEK_SET);
        fread(&mercados, sizeof(struct Mercado), 1, mercado);

        if (fmercado == mercados.clave_mercado)
            mercadovalido = true;
    }
    fclose(mercado);
    return mercadovalido;
}

bool validararticulo(int farticulo)
{
    FILE *articuloptr;
    struct Articulos articulo;
    bool articulovalido = false;

    if((articuloptr = fopen("Articulos.dat", "r")) == NULL)
        printf("Error con el archivo de mercados\n");

    else
    {
        fseek(articuloptr, (farticulo - 1) * sizeof(struct Articulos), SEEK_SET);
        fread(&articulo, sizeof(struct Articulos), 1, articuloptr);

        if (farticulo == articulo.clave_articulo)
            articulovalido = true;
    }
    fclose(articuloptr);
    return articulovalido;
}

int validarcantidad(int cantidad_articulos, int fclave) {
    FILE *articulolocal;
    struct Articulos articulos;

    if ((articulolocal = fopen("Articulos.dat", "r+")) == NULL)
    {
        printf("Error al abrir el archivo de articulos.\n");
        return -1; 
    }

    fseek(articulolocal, (fclave - 1) * sizeof(struct Articulos), SEEK_SET);
    fread(&articulos, sizeof(struct Articulos), 1, articulolocal);
    
    if (articulos.clave_articulo == fclave) 
    {
        printf("\nCantidad en almacen: %d\n", articulos.inventario);

        
        if (articulos.inventario <= 0) 
        {
            printf("El inventario se encuentra vacio, favor de rebastecerlo.\n");
            fclose(articulolocal);
            return 0; 
        }

        
        if (articulos.inventario >= cantidad_articulos)
        {
            articulos.inventario -= cantidad_articulos;

            fseek(articulolocal, (fclave - 1) * sizeof(struct Articulos), SEEK_SET);
            fwrite(&articulos, sizeof(struct Articulos), 1, articulolocal);

            fclose(articulolocal);
            return 1; 
        } 
        else
        {
            printf("Almacen insuficiente.\n");
            fclose(articulolocal);
            return 2;
        }
    }
    printf("Clave no encontrada.\n");
    fclose(articulolocal);
    return 3; 
}

float precio(int fclave, char *descripcion)
{
    FILE *articulolocal;
    struct Articulos articuloleido;
    float precioarticulo;

    if ((articulolocal = fopen("Articulos.dat", "r")) == NULL)
        printf("Error al abrir el archivo de articulos.\n");

    else
    {
        fseek(articulolocal, (fclave - 1) * sizeof(struct Articulos), SEEK_SET);
        fread(&articuloleido, sizeof(struct Articulos), 1, articulolocal);
        precioarticulo = articuloleido.precio_venta;
        strcpy(descripcion, articuloleido.descripcion);

    }
    fclose(articulolocal);
    return precioarticulo;
}

bool validarempleado(int fempleado, FILE *empleado)
{
    struct Empleado empleadoleido;
    bool empleadovalido = false;

    fseek(empleado, (fempleado - 1) * sizeof(struct Empleado), SEEK_SET);
    fread(&empleadoleido, sizeof(struct Empleado), 1, empleado);

    if (empleadoleido.numero_empleado == fempleado)
        empleadovalido = true;
    
    return empleadovalido;
}

float descuento(int fclave)
{
    FILE *mercadolocal;
    struct Mercado mercadoleido;
    float descuento = 0.0;

    if((mercadolocal = fopen("Mercados.dat", "r")) == NULL)
        printf("Error al abrir el archivo de mercado\n");

    else
    {
        fseek(mercadolocal, (fclave - 1) * sizeof(struct Mercado), SEEK_SET);
        fread(&mercadoleido, sizeof(struct Mercado), 1, mercadolocal);
        descuento = mercadoleido.descuento;
    }
    fclose(mercadolocal);
    return descuento;
}

void imprimir_factura(int mercado, int articulo, char descripcion[150], int cantidad, float precio_unitario, int empleado, float total, int dia, int mes, int anio, float descuento) 
{
    int descuento_porcentaje = (int)(descuento * 100); 
    printf("\n\t\t=========================================\n");
    printf("\t\t                 FACTURA                 \n");
    printf("\t\t=========================================\n");
    printf("\t\tCliente (No. Mercado):       %d\n", mercado);
    printf("\t\tArticulo (ID):               %d\n", articulo);
    printf("\t\tDescripcion:                 %s\n", descripcion);
    printf("\t\tFecha de venta:              %02d/%02d/%04d\n", dia, mes, anio);
    printf("\t\tDescuento del:               %d%%\n", descuento_porcentaje);
    printf("\t\t-----------------------------------------\n");
    printf("\t\tCantidad:                    %d\n", cantidad);
    printf("\t\tPrecio unitario:             $%.2f\n", precio_unitario);
    printf("\t\t-----------------------------------------\n");
    printf("\t\tEmpleado (ID):               %d\n", empleado);
    printf("\t\t=========================================\n");
    printf("\t\tTOTAL A PAGAR:               $%.2f\n", total);
    printf("\t\t=========================================\n");
}

char *convertir_a_minusculas(char *cadena)
{
    int i;
    for (i = 0; cadena[i]; i++)
        cadena[i] = tolower(cadena[i]);

    return cadena;
}

void crearRegistrosVacios(const char *nombreArchivo, void *registroVacio, size_t tamanoRegistro, int cantidad)
{
    FILE *archivo = fopen(nombreArchivo, "w");
    if (!archivo)
    {
        printf("Error al abrir el archivo");
        return;
    }

    for (int i = 0; i < cantidad; i++)
    {
        fwrite(registroVacio, tamanoRegistro, 1, archivo);
    }

    fclose(archivo);
}

bool validarproveedor(int NumeroProveedor)
{
    FILE *proveedorlocal;
    struct Proveedor proveedor;
    bool proovedorvalido = false;

    if ((proveedorlocal = fopen("Proveedores.dat", "r")) == NULL)
        printf("Error al abrir el archivo de proveedores.\n");
    else
    {
        fseek(proveedorlocal, (NumeroProveedor - 1) * sizeof(struct Proveedor), SEEK_SET);
        fread(&proveedor, sizeof(struct Proveedor), 1, proveedorlocal);

        if (proveedor.numero_proveedor == NumeroProveedor)
            proovedorvalido = true;
    }

    fclose(proveedorlocal);
    return proovedorvalido;
}

bool validarnumeroinsumo(int fnumero)
{
    FILE *insumolocal;
    struct Insumo insumos;
    bool numerovalido = false;

    if((insumolocal = fopen("Insumos.dat", "r")) == NULL)
        printf("Error al abrir el archivo de insumos");

    else
    {
        fseek(insumolocal, (fnumero - 1) * sizeof(struct Insumo), SEEK_SET);
        fread(&insumos, sizeof(struct Insumo), 1, insumolocal);

        if (insumos.clave_insumo == fnumero)
            numerovalido = true;
    }
    fclose(insumolocal);
    return numerovalido;
}

float precioinsumo(int fnumero)
{
    FILE *insumolocal;
    struct Insumo insumos;
    float precio_total = 0;
    int i;
    bool insumo_encontrado = false;

    if ((insumolocal = fopen("Insumos.dat", "r")) == NULL)
        printf("Error al abrir el archivo de Insumos.\n");

    else
    {
        fseek(insumolocal, (fnumero - 1) * sizeof(struct Insumo), SEEK_SET);
        fread(&insumos, sizeof(struct Insumo), 1, insumolocal);

        if (insumos.clave_insumo == fnumero)
        {
            insumo_encontrado = true;

            for (i = 0; i < 10; i++)
                precio_total += insumos.precio_compra[i];
        }
    }
    fclose(insumolocal);
    return precio_total;
}

float descuento_proveedor(int NumProveedor)
{
    FILE *proveedorlocal;
    struct Proveedor proveedorleido;
    float descuento = 0.0;

    if((proveedorlocal = fopen("Proveedores.dat", "r")) == NULL)
        printf("Error al abrir el archivo de proveedores");

    else
    {
        fseek(proveedorlocal, (NumProveedor - 1) * sizeof(struct Proveedor), SEEK_SET);
        fread(&proveedorleido, sizeof(struct Proveedor), 1, proveedorlocal);
        descuento = proveedorleido.descuento;
    }
    fclose(proveedorlocal);
    return descuento;
}

bool validar_compra(int numero_compra)
{
    FILE *archivo;
    int id_compra, num_proveedor, clave_insumo, cantidad;
    bool compra_valida = false;
    float precio, total;

    if ((archivo = fopen("Compras.txt", "r")) == NULL)
    {
        printf("Error al abrir el archivo\n");
        return false;
    }
    while (!feof(archivo))
    {
        fscanf(archivo, "ID compra: %d\n", &id_compra);
        fscanf(archivo, "Numero de proveedor: %d\n", &num_proveedor);
        fscanf(archivo, "Numero de insumo: %d\n", &clave_insumo);
        fscanf(archivo, "Cantidad: %d\n", &cantidad);
        fscanf(archivo, "Precio: %f\n", &precio);
        fscanf(archivo, "Entregado: %c\n", &precio);
        fscanf(archivo, "Total: %f\n", &total);

        if (numero_compra == id_compra)
            compra_valida = true;
    }

    fclose(archivo);
    return compra_valida;
}
