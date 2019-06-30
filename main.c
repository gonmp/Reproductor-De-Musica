/**  Llenar las funciones correspondientes para:

        . Resgistrar usuarios en un archivo
        . Loguearse como usuario
        . Loguearse como administrador
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include "funciones_archivos.h"

#define VERDADERO 1
#define FALSO 0
#define ESC 27

int cerrando_sesion = FALSO;    // para saber si se esta cerrando la sesion
                                // asi las funciones no crean otras ventanas

// ventanas principales -------------------------
int Ventana_menu_principal ();
void Ventana_usuario (int idUsuario);
void Ventana_administrador ();
// ----------------------------------------------

// ventanas del menu principal ------------------
void Ingresar_usuario ();
void Ingresar_administrador ();
void Registrarse ();
void Salir ();
// ----------------------------------------------

// funciones del usuario ------------------------
void Usuario_ver_perfil (int idUsuario);
stUsuario buscarUsuarioPorID(int idUsuario);
stCancion buscarCancionPorID(int idCancion);
stUsuario buscarUsuarioPorNombre(char nombreUsuario[]);
void Usuario_mostrar_playlist (int idUsuario);
void Usuario_escuchar_cancion ();
void Usuario_canciones_recomendadas ();
void Usuario_listar_canciones ();
// ----------------------------------------------

// funciones del admin --------------------------
void Admin_administrar_usuarios ();
void Admin_administrar_canciones ();
// ----------------------------------------------

// funciones del admin para administrar usuarios
void Admin_listar_usuarios ();
void Admin_alta_usuario ();
void Admin_baja_usuario ();
void Admin_modificiar_usuario ();
void Admin_consultar_perfil ();
void Admin_cambiar_administrar_canciones ();
// ----------------------------------------------

// funciones del admin para administrar canciones
void Admin_listar_canciones ();
void Admin_alta_cancion ();
void Admin_baja_cancion ();
void Admin_modificiar_cancion ();
void Admin_consultar_cancion ();
void Admin_cambiar_administrar_usuarios ();
// ----------------------------------------------


// ----------------------------------------------
void Cerrar_sesion ();
// ----------------------------------------------



// **********************************************
// inicio del main ******************************
int main()
{
    int salir_del_programa = FALSO;

    while (salir_del_programa == FALSO)
    {
        salir_del_programa = Ventana_menu_principal();
    }

    return 0;
}
// fin del main *********************************
// **********************************************


// ----------------------------------------------
// menu principal -------------------------------
int Ventana_menu_principal ()
{
    system("cls");

    int salir_del_programa = FALSO;

    printf("\n\n-- menu principal --\n\n");

    printf("1 - para ingresar como usuario\n");
    printf("2 - para ingresar como administrador\n");
    printf("3 - para registrarse\n");
    printf("4 - para salir\n");

    char tecla = '0';
    tecla = getch();
    fflush(stdin);

    switch (tecla)
    {
        case '1':
            cerrando_sesion = FALSO;
            Ingresar_usuario();
            break;

        case '2':
            cerrando_sesion = FALSO;
            Ingresar_administrador();
            break;

        case '3':
            Registrarse();
            break;

        case '4':
            Salir();
            salir_del_programa = VERDADERO;
            break;

        default:
            printf("tecla incorrecta\n");
            break;
    }

    return salir_del_programa;
}
// ----------------------------------------------
// ventanas del menu principal ------------------
void Ingresar_usuario ()
{
    stUsuario usuario;
    printf("\ningresando usuario\n\n");

    printf("Ingrese su nombre de usuario:\n");
    char nombre_usuario[30];
    fflush(stdin);
    gets(nombre_usuario);

    usuario = buscarUsuarioPorNombre(nombre_usuario);

    char tecla = '0';
    while (usuario.idUsuario == -1 && tecla != ESC)
    {
        printf("\nUsuario invalido, Para salir del programa presione ESC\n");
        printf("Presione otra tecla para ingresar un nuevo usuario\n\n");
        fflush(stdin);
        tecla = getch();

        if (tecla != ESC)
        {
            printf("Ingrese un nombre de usuario:\n\n");
            fflush(stdin);
            gets(nombre_usuario);
        }
    }

    if (Usuario_existe(nombre_usuario) == VERDADERO)
    {
        Ventana_usuario(usuario.idUsuario);
    }
}
void Ingresar_administrador ()
{
    printf("\ningresando admin\n\n");
    Ventana_administrador();
}
void Registrarse ()
{
    stUsuario usuario;
    char nombre_usuario[30];

    usuario.idUsuario = Nuevo_id_usuario();

    printf("\nregistrandose\n");

    printf("Ingrese su nombre de usuario\n");
    fflush(stdin);
    gets(nombre_usuario);

    while (Usuario_existe(nombre_usuario) == VERDADERO)
    {
        printf("\nYa existe un usuario con ese nombre\nIngrese otro nombre de usuario:\n");
        fflush(stdin);
        gets(nombre_usuario);
    }

    strcpy(usuario.nombreUsuario, nombre_usuario);

    printf("Ingrese su password\n");
    fflush(stdin);
    fflush(stdin);
    gets(usuario.pass);

    printf("Ingrese su genero F - M\n");
    char genero;
    fflush(stdin);
    scanf("%c",&genero);
    genero = toupper(genero);

    while (genero != 'F' && genero != 'M')
    {
        printf("\ngenero incorrecto. Ingrese F - M\n");
        fflush(stdin);
        scanf("%c",&genero);
        genero = toupper(genero);
    }

    usuario.genero = genero;

    printf("Ingrese su pais\n");
    fflush(stdin);
    gets(usuario.pais);

    Registrar_usuario_archivo(usuario);
    printf("Su usuario ha sido registrado correctamente\n");
}
void Salir ()
{
    printf("\nsaliendo\n");
}
// ----------------------------------------------
// ----------------------------------------------

// usuario --------------------------------------
void Ventana_usuario (int idUsuario)
{
    while (cerrando_sesion != VERDADERO)
    {
        system("cls");

        printf("\n\n-- usuario --\n\n");

        printf("1 - ver perfil\n");
        printf("2 - mostrar playlist\n");
        printf("3 - escuchar cancion\n");
        printf("4 - canciones recomendadas\n");
        printf("5 - listar canciones\n");
        printf("6 - cerrar sesion\n");

        char tecla = '0';
        tecla = getch();
        fflush(stdin);

        switch (tecla)
        {
            case '1':
                Usuario_ver_perfil(idUsuario);
                break;

            case '2':
                Usuario_mostrar_playlist(idUsuario);
                break;

            case '3':
                Usuario_escuchar_cancion();
                break;

            case '4':
                Usuario_canciones_recomendadas();
                break;

            case '5':
                Usuario_listar_canciones();
                break;

            case '6':
                Cerrar_sesion();
                break;

            default:
                printf("tecla incorrecta\n");
                break;
        }
    }
}
// ----------------------------------------------
// funciones del usuario ------------------------
void Usuario_ver_perfil (int idUsuario)
{
    printf("viendo el perfil\n");

    stUsuario usuario = buscarUsuarioPorID(idUsuario);

    if(usuario.idUsuario == -1 || usuario.eliminado == 0)
    {
        printf("El usuario buscado no existe");
    }
    else
    {
        printf("\nNombre: %s\n", usuario.nombreUsuario);
        printf("Año de nacimiento: %i\n", usuario.anioNacimiento);

        if(usuario.genero == 'm')
        {
            printf("\nGenero: Masculino");
        }
        else
        {
            printf("\nGenero: Femenino");
        }
        printf("\nPais: %s\n", usuario.pais);
        printf("Playlists: \n");
        Usuario_mostrar_playlist(idUsuario);
    }
}

stUsuario buscarUsuarioPorID(int idUsuario)
{
    FILE *pArchivo = fopen(NOMBRE_ARCHIVO, "rb");
    stUsuario usuario;
    int flag = 0;

    if(pArchivo != NULL)
    {
        while(flag != 1 && fread(&usuario, sizeof(stUsuario), 1, pArchivo) > 0)
        {
            if(usuario.idUsuario == idUsuario)
            {
                flag = 1;
            }
        }

        if(flag == 0)
        {
            usuario.idUsuario = -1;
        }

        fclose(pArchivo);
    }

    return usuario;
}

stUsuario buscarUsuarioPorNombre(char nombreUsuario[])
{
    stUsuario usuario;
    FILE *pArchivo = fopen(NOMBRE_ARCHIVO, "rb");
    int flag = 0;

    if(pArchivo != NULL)
    {
        while(flag != 1 && fread(&usuario, sizeof(stUsuario), 1, pArchivo) > 0)
        {
            if(strcmp(nombreUsuario, usuario.nombreUsuario) == 0)
            {
                flag = 1;
            }
        }

        if(flag == 0)
        {
            usuario.idUsuario = -1;
        }

        fclose(pArchivo);
    }

    return usuario;
}

stCancion buscarCancionPorID(int idCancion)
{
    FILE *pArchivo = fopen(NOMBRE_ARCHIVO_CANCIONES, "rb");
    stCancion cancion;
    int flag = 0;

    if(pArchivo != NULL)
    {
        while(flag != 1 && fread(&cancion, sizeof(stCancion), 1, pArchivo) > 0)
        {
            if(cancion.idCancion == idCancion)
            {
                flag = 1;
            }
        }

        if(flag == 0)
        {
            cancion.idCancion = -1;
        }

        fclose(pArchivo);
    }

    return cancion;
}

void mostrarCancion(stCancion cancion)
{
    printf("\nNombre: %s\n", cancion.titulo);
    printf("Duracion: %d\n", cancion.duracion);
    printf("-----------------------------");
}

void Usuario_mostrar_playlist (int idUsuario)
{
    printf("mostrando playlist\n");

    stUsuario usuario = buscarUsuarioPorID(idUsuario);

    FILE *pArchivo = fopen(NOMBRE_ARCHIVO_CANCIONES, "ab");
    stCancion cancion;

    if(usuario.idUsuario == -1)
    {
        printf("El usuario buscado no existe");
    }
    else if(pArchivo != NULL)
    {
        for(int i = 0; i < usuario.cantidad; i++)
        {
            printf("\nCancion %d\n", i);
            cancion = buscarCancionPorID(usuario.playlist[i]);
            if(cancion.idCancion == -1)
            {
                printf("La cancion no existe");
            }
            else
            {
               mostrarCancion(cancion);
            }
        }

        fclose(pArchivo);
    }
}
void Usuario_escuchar_cancion ()
{
    printf("escuchando cancion\n");
}
void Usuario_canciones_recomendadas ()
{
    printf("viendo canciones recomendadas\n");
}
void Usuario_listar_canciones ()
{
    printf("listando canciones\n");
}
// ----------------------------------------------
// ----------------------------------------------

// admin ----------------------------------------
void Ventana_administrador()
{
    while (cerrando_sesion != VERDADERO)
    {
        system("cls");

        printf("\n\n-- administrador --\n\n");

        printf("1 - administrar usuarios\n");
        printf("2 - administrar canciones\n");
        printf("3 - cerrar sesion\n");

        char tecla = '0';
        tecla = getch();
        fflush(stdin);

        switch (tecla)
        {
            case '1':
                Admin_administrar_usuarios();
                break;

            case '2':
                Admin_administrar_canciones();
                break;

            case '3':
                Cerrar_sesion();
                break;

            default:
                printf("tecla incorrecta\n");
                break;
        }
    }
}
// ----------------------------------------------
// funciones del admin --------------------------
void Admin_administrar_usuarios ()
{
    while (cerrando_sesion != VERDADERO)
    {
        system("cls");

        printf("\n\n-- administrando usuarios --\n\n");

        printf("1 - listar usuarios\n");
        printf("2 - dar de alta usuario\n");
        printf("3 - dar de baja usuario\n");
        printf("4 - modificiar usuario\n");
        printf("5 - consultar perfil de usuario\n");
        printf("6 - pasar a administrar canciones\n");
        printf("7 - cerrar sesion\n");

        char tecla = '0';
        tecla = getch();
        fflush(stdin);

        switch (tecla)
        {
            case '1':
                Admin_listar_usuarios();
                break;

            case '2':
                Admin_alta_usuario();
                break;

            case '3':
                Admin_baja_usuario();
                break;

            case '4':
                Admin_modificiar_usuario();
                break;

            case '5':
                Admin_consultar_perfil();
                break;

            case '6':
                Admin_cambiar_administrar_canciones();
                break;

            case '7':
                Cerrar_sesion();
                break;

            default:
                printf("tecla incorrecta\n");
                break;
        }
    }
}
void Admin_administrar_canciones ()
{
    while (cerrando_sesion != VERDADERO)
    {
        system("cls");

        printf("\n\n-- administrando canciones --\n\n");

        printf("1 - listar canciones \n");
        printf("2 - dar de alta cancion\n");
        printf("3 - dar de baja cancion\n");
        printf("4 - modificiar cancion\n");
        printf("5 - consultar datos de cancion\n");
        printf("6 - cambiar a administrar usuarios\n");
        printf("7 - cerrar sesion\n");

        char tecla = '0';
        tecla = getch();
        fflush(stdin);

        switch (tecla)
        {
            case '1':
                Admin_listar_canciones();
                break;

            case '2':
                Admin_alta_cancion();
                break;

            case '3':
                Admin_baja_cancion();
                break;

            case '4':
                Admin_modificiar_cancion();
                break;

            case '5':
                Admin_consultar_cancion();
                break;

            case '6':
                Admin_cambiar_administrar_usuarios();
                break;

            case '7':
                Cerrar_sesion();
                break;

            default:
                printf("tecla incorrecta\n");
                break;
        }
    }
}
// ----------------------------------------------
// funciones del admin para administrar usuarios
void Admin_listar_usuarios ()
{
    printf("\nmostrando lista usuarios\n");
}
void Admin_alta_usuario ()
{
    printf("\ndando de alta usuario\n");
}
void Admin_baja_usuario ()
{
    printf("\ndando de baja usuario\n");
}
void Admin_modificiar_usuario ()
{
    printf("\nmodificando perfil de usuario\n");
}
void Admin_consultar_perfil ()
{
    printf("\nconsultando perfil usuario\n");


}
void Admin_cambiar_administrar_canciones()
{
    printf("\ncambiando a administrar canciones\n");
    Admin_administrar_canciones();
}
// ----------------------------------------------
// funciones del admin para administrar canciones
void Admin_listar_canciones ()
{
    printf("\nmostrando canciones\n");
}
void Admin_alta_cancion ()
{
    printf("\ndando de alta una cancion\n");
}
void Admin_baja_cancion ()
{
    printf("\ndando de baja una cancion\n");
}
void Admin_modificiar_cancion ()
{
    printf("\nmodificando una cancion\n");
}
void Admin_consultar_cancion ()
{
    printf("\nconsultando una cancion\n");
}
void Admin_cambiar_administrar_usuarios()
{
    printf("\ncambiando a administrar usuarios\n");
    Admin_administrar_usuarios();
}
// ----------------------------------------------

void Cerrar_sesion()
{
    printf("\ncerrando sesion\n\n");
    cerrando_sesion = VERDADERO;
}
