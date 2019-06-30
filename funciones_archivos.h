#ifndef FUNCIONES_ARCHIVOS_H_INCLUDED
#define FUNCIONES_ARCHIVOS_H_INCLUDED

#define FALSO 0
#define VERDADERO 1
#define NOMBRE_ARCHIVO "usuarios.dat"
#define NOMBRE_ARCHIVO_CANCIONES "canciones.dat"

typedef struct
{
    int idUsuario;
    char nombreUsuario[30];
    char pass[20];
    int anioNacimiento;
    char genero;
    char pais[20];
    int playlist[50];
    int cantidad;
    int eliminado;

} stUsuario;

typedef struct
{
    int idCancion;
    char titulo[30];
    char artista[20];
    int duracion;
    char album[20];
    int anio;
    char genero[20];
    char comentario[100];
    int eliminado;
} stCancion;

int Nuevo_id_usuario ()
{
    int nuevoID = 0;

    FILE* fArchivo = fopen(NOMBRE_ARCHIVO, "rb");
    if (fArchivo != NULL)
    {
        stUsuario usuario;

        fseek(fArchivo, sizeof(stUsuario) * -1, SEEK_END);
        fread(&usuario, sizeof(stUsuario), 1, fArchivo);  ///Corregir que pasa si fread no es > 0

        nuevoID = usuario.idUsuario;
        nuevoID++;

        fclose(fArchivo);
    }

    return nuevoID;
}

int Usuario_existe (char nombre_usuario[30])
{
    int existe = FALSO;

    FILE* fArchivo = fopen(NOMBRE_ARCHIVO, "rb");
    if (fArchivo != NULL)
    {
        stUsuario usuario;

        while (fread(&usuario, sizeof(usuario), 1, fArchivo) > 0 && existe == FALSO)
        {
            if (strcmp(usuario.nombreUsuario,nombre_usuario) == 0)
            {
                existe = VERDADERO;
            }
        }

        fclose(fArchivo);
    }

    return existe;
}

void Registrar_usuario_archivo (stUsuario usuario)
{
    FILE* fArchivo = fopen(NOMBRE_ARCHIVO, "ab");
    if (fArchivo != NULL)
    {
        fwrite(&usuario, sizeof(usuario), 1, fArchivo);

        fclose(fArchivo);
    }
}

int nuevoIDCancion()
{
    int nuevoID = 0;

    FILE* pArchivo = fopen(NOMBRE_ARCHIVO_CANCIONES, "rb");
    if (pArchivo != NULL)
    {
        stCancion cancion;

        fseek(pArchivo, sizeof(stCancion) * -1, SEEK_END);
        fread(&cancion, sizeof(stCancion), 1, pArchivo);  ///Corregir que pasa si fread no es > 0

        nuevoID = cancion.idCancion;
        nuevoID++;

        fclose(pArchivo);
    }

    return nuevoID;
}

void registrarCancionArchivo (stCancion cancion)
{
    FILE* pArchivo = fopen(NOMBRE_ARCHIVO_CANCIONES, "ab");
    if (pArchivo != NULL)
    {
        fwrite(&cancion, sizeof(stCancion), 1, pArchivo);

        fclose(pArchivo);
    }
}

#endif // FUNCIONES_ARCHIVOS_H_INCLUDED
