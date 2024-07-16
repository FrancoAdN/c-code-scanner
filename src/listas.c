#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "listas.h"

// //Inicio Control Doble Declaracion
void agregarDoble(ID id, short linea)
{

    char *msg = "Doble declaracion con identificador ";
    char *new_msg = malloc(strlen(id) + strlen(msg) + 1);
    strcat(new_msg, msg);
    strcat(new_msg, id);

    agregarError(new_msg, "Semantico", linea);
}

void agregarIdentificador(ID identificador)
{
    ListaId *nuevoNodo = malloc(sizeof(ListaId));
    strcpy(nuevoNodo->identificador, identificador);
    nuevoNodo->siguiente = NULL;

    if (ListaIdentificadores == NULL)
    {
        ListaIdentificadores = nuevoNodo;
    }
    else
    {
        ListaId *ultimo = ListaIdentificadores;
        while (ultimo->siguiente != NULL)
        {
            ultimo = ultimo->siguiente;
        }
        ultimo->siguiente = nuevoNodo;
    }
}

void agregarDeclaraciones(TipoVariable tipo)
{
    ListaId *actual = ListaIdentificadores;

    while (actual)
    {
        ListaDeclaracion *nuevoNodo = malloc(sizeof(ListaDeclaracion));
        strcpy(nuevoNodo->identificador, actual->identificador);
        nuevoNodo->tipo = tipo;
        nuevoNodo->siguiente = NULL;

        if (ListaVariablesDeclaradas == NULL)
        {
            ListaVariablesDeclaradas = nuevoNodo;
        }
        else
        {
            ListaDeclaracion *ultimo = ListaVariablesDeclaradas;
            while (ultimo->siguiente != NULL)
            {
                ultimo = ultimo->siguiente;
            }
            ultimo->siguiente = nuevoNodo;
        }
        ListaId *aux = actual;
        actual = actual->siguiente;
        free(aux);
    }

    ListaIdentificadores = NULL;
}

void reporteVariableDeclaradas()
{
    printf("\n\n");
    printf("Listado de Variables declaradas:\n");

    ListaDeclaracion *actual = ListaVariablesDeclaradas;

    while (actual != NULL)
    {
        printf("Variable declarada con tipo \"%s\", identificador \"%s\"\n", obtenerTipoDeDato(actual->tipo), actual->identificador);
        ListaDeclaracion *aux = actual;
        actual = actual->siguiente;
        free(aux);
    }
}

void agregarSentencia(char *tipo, short linea)
{
    ListaSent *nuevoNodo = malloc(sizeof(ListaSent));
    nuevoNodo->tipo = tipo;
    nuevoNodo->linea = linea;
    nuevoNodo->siguiente = NULL;

    if (ListaSentencias == NULL)
    {
        ListaSentencias = nuevoNodo;
    }
    else
    {
        ListaSent *ultimo = ListaSentencias;
        while (ultimo->siguiente != NULL)
        {
            ultimo = ultimo->siguiente;
        }
        ultimo->siguiente = nuevoNodo;
    }
}
void reporteSentencias()
{
    printf("\n\n");
    printf("Listado de Sentencias encontradas:\n");

    ListaSent *actual = ListaSentencias;

    while (actual != NULL)
    {
        printf("Sentencia de tipo \"%s\" encontrada en linea %i\n", actual->tipo, actual->linea);
        ListaSent *aux = actual;
        actual = actual->siguiente;
        free(aux);
    };
}
