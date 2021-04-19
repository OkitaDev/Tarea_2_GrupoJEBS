#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "TDA_Mapa/hashmap.h"

typedef struct tipoIdentificacion
{
  int id;
  int idPokedex;
}tipoIdentificacion;

typedef struct tipoEvoluciones
{
  char evolPrevia[25];
  char evolSiguiente[25];
}tipoEvoluciones;

typedef struct tipoPuntos
{
    int pSalud;
    int pCombate;
}tipoPuntos;

typedef struct tipoPokemon
{
    char nombrePokemon[25];
    char region[25];
    char sexo[25];
    char tipos[100];
    tipoPuntos puntos;
    tipoEvoluciones evol;
    tipoIdentificacion ident;
}tipoPokemon;

void ingresarPokemon(HashMap * mapa, char * lineaLeida)
{
    tipoPokemon * nuevoPokemon = (tipoPokemon *) malloc (sizeof(tipoPokemon));
    char * fragmento;

    //Lectura del ID
    fragmento = strtok(lineaLeida, ",");
    nuevoPokemon->ident.id = strtol(fragmento, NULL, 10);

    //Lectura del nombre
    fragmento = strtok(NULL, ",");
    strcpy(nuevoPokemon->nombrePokemon, fragmento);

    //Lectura de los tipos
    fragmento = strtok(NULL, ",");

    //Se verifica si posee 1 o mas tipos
    if(fragmento[0] == '"')
    {
        //Eliminacion de las primeras comillas
        memmove(fragmento, fragmento + 1, strlen(fragmento));
        strcpy(nuevoPokemon->tipos, fragmento);
        short largo;
        
        //Reiteracion hasta que no hayan mas tipos
        do
        {
            fragmento = strtok(NULL, ",");
            largo = strlen(fragmento) - 1;
            if(fragmento[largo] != '"') strcat(nuevoPokemon->tipos, fragmento);
        } while (fragmento[largo] != '"');

        //Eliminacion de la comillas finales
        fragmento[largo] = '\0';
        strcat(nuevoPokemon->tipos, fragmento);
    } 
    else strcpy(nuevoPokemon->tipos, fragmento);    

    //Lectura de los puntos de Combate
    fragmento = strtok(NULL, ",");
    nuevoPokemon->puntos.pCombate = strtol(fragmento, NULL, 10);

    //Lectura de los Puntos de Salud
    fragmento = strtok(NULL, ",");
    nuevoPokemon->puntos.pSalud = strtol(fragmento, NULL, 10);

    //Lectura del sexo del Pokemon
    fragmento = strtok(NULL,",");
    strcpy(nuevoPokemon->sexo, fragmento);

    //Lectura de las evoluciones
    fragmento = strtok(NULL,",");
    strcpy(nuevoPokemon->evol.evolPrevia, fragmento);
    fragmento = strtok(NULL,",");
    strcpy(nuevoPokemon->evol.evolSiguiente, fragmento);

    //Lectura del numero de la Pokedex
    fragmento = strtok(NULL, ",");
    nuevoPokemon->ident.idPokedex = strtol(fragmento, NULL, 10);

    //Lectura de la Region
    fragmento = strtok(NULL,",");
    strcpy(nuevoPokemon->region, fragmento);
}

HashMap * importarArchivo(HashMap * mapa)
{
    //Ingreso del nombre del archivo a implementar
    char nombreArchivo[40];
    printf("\nIngrese el nombre del archivo (Incluyendo el .cvs)\n\n");
    scanf("%39s", nombreArchivo);

    //Busqueda del archivo
    FILE * archivo = fopen(nombreArchivo, "r");

    if(archivo == NULL)
    {
        printf("\nArchivo NO IMPLEMENTADO!\n");
        return NULL;
    }

    //Lectura del archivo (saltandose la primera linea)
    char lineaLeida[100];
    short lecturaPrimeraLinea = 0;

    while(fgets(lineaLeida, 99, archivo))
    {
        if(lecturaPrimeraLinea != 0) ingresarPokemon(mapa, lineaLeida);
        lecturaPrimeraLinea++;
    }

    printf("\nArchivo IMPLEMENTADO!\n");
    fclose(archivo);
    return mapa;
}

HashMap * exportarArchivo(HashMap * mapa)
{
    char nombreArchivo[40];
    printf("\nIngrese el nombre del nuevo archivo (Incluyendo el .cvs)\n\n");
    scanf("%39s", nombreArchivo);

    FILE * archivo = fopen(nombreArchivo, "w");

    if(archivo == NULL)
    {
        printf("\nArchivo NO IMPLEMENTADO!\n");
        return NULL;
    }

    printf("\nArchivo EXPORTADO!\n");
    fclose(archivo);
    return mapa;
}
