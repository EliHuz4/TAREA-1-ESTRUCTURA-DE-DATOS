#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h> // Libreria para obtener la hora actual de el PC
#include <string.h> // Libreria para comparar char
#include <assert.h> // Libreria para asegurar que se reserven bien los datos
#include <ctype.h> // Para revisar si se ingresa un digito o un caracter
#include "TDAS/list.c"
#include "TDAS/list.h"
#include "TDAS/queue.h"
#include "TDAS/stack.h"

typedef struct{ // Struct para guardar la hora actual del PC
    int Hora;
    int Minuto;
}TipoHora;

typedef struct{ // Struct Tipoticket para guardar los datos por ticket
    char ID[100]; // ID del ticket
    char Descripcion[2000]; // Descripcion del ticket
    TipoHora HoraRegistro; // Hora de registro del ticket
    char Prioridad[10]; // Prioridad del ticket
}TipoTicket;

void MostrarMenu() //Funcion para mostrar el menu principal
{
    printf("\n================================\n");
    printf("        SERVICIO TECNICO\n");
    printf("================================\n");
    printf("1) Registrar ticket\n"); //Ingresar un ticket nuevo, con su ID y descripcion del problema
    printf("2) Asignar Prioridad a ticket\n"); //Reasignar prioridad de un ticket mediante la busqueda de la ID
    printf("3) Mostrar Lista de Tickets Pendientes\n"); // Muestra una lista de tickets ya ingresados y aun sin resolver, se muestran por prioridad y hora de registro
    printf("4) Procesar Siguiente Ticket\n"); //Muestra el siguiente ticket de la lista con todos sus detalles, luego lo elimina
    printf("5) Buscar Ticket\n"); //Busca un ticket en especifico mediante la ID y muestra todos sus detalles
    printf("6) Salir\n\n");
}

TipoHora *GuardarHora(List *ListaTickets) { // Funcion para guardar la hora del sistema en el struct "TipoHora"
    time_t t; // Guardar tiempo actual
    struct tm *tm_info; //Puntero a la estructura de tm (contiene hora, mins y segundos) 

    time(&t); // Guardar el tiempo en "t"
    tm_info = localtime(&t); // Convierte t en valores int

    TipoHora *Hora = (TipoHora *)malloc(sizeof(TipoHora)); // Reserva espacio para guardar la hora
    if (Hora == NULL) { // Si no se pudo reservar memoria retornar NULL
        return NULL;
    }
    Hora->Hora = tm_info->tm_hour; // Guardar hora en el struct TipoHora
    Hora->Minuto = tm_info->tm_min; // Guardar minutos en el struct TipoHora

    return Hora; //Retorna la estructura
}

TipoTicket *createTicket(char ID[], char Descripcion[], char Prioridad[], TipoHora *Horas) { //Funcion para crear un ticket nuevo
    TipoTicket *new = (TipoTicket *)malloc(sizeof(TipoTicket)); // reservar espacio para nuevo nodo
    assert(new != NULL);                                        // comprobar que no falle la reserva

    //Copiar los datos al nuevo nodo
    strcpy(new->ID, ID);
    strcpy(new->Descripcion, Descripcion);
    strcpy(new->Prioridad, "BAJA"); //Prioridad por defecto para nuevos nodos es BAJA
    new->HoraRegistro.Hora = Horas->Hora;
    new->HoraRegistro.Minuto = Horas->Minuto;
    return new; //retorna el nodo nuevo creado
}


void ordenarTickets(List *ListaTickets) // Funcion para ordenar los ticket de la lista
{
    if ( ListaTickets == NULL || ListaTickets->size <= 1) return; // Si la lista esta vacia o con un solo elemento no se ordena

    bool flag = true; // Flag para indicar si hubo un cambio

    while(flag){
        flag = false;
        Node *nodoA = ListaTickets->head;
        Node *nodoB = nodoA->next;

        while (nodoB != NULL) {
            TipoTicket *a = (TipoTicket *)nodoA->data;
            TipoTicket *b = (TipoTicket *)nodoB->data;

            bool cambiar = false;

            // Compara prioridades, si A != Alta y B == Alta, cambiar es true
            if (strcmp(a->Prioridad, "ALTA") != 0 && strcmp(b->Prioridad, "ALTA") == 0){
                cambiar = true;
            }
            // Compara prioridades, si B == MEDIA y A == BAJA, cambiar es true
            else if (strcmp(b->Prioridad, "MEDIA") == 0 && strcmp(a->Prioridad, "BAJA") == 0){
                cambiar = true;
            }

            // Compara prioridades, si A == B, condiciona por hora de registro:
            else if (strcmp(a->Prioridad, b->Prioridad) == 0) {
                // Si A se ingreso despues que B, cambiar es true
                if (a->HoraRegistro.Hora > b->HoraRegistro.Hora)
                    cambiar = true;
                // Si A se ingreso a la misma hora que B, se compara por minuto
                // Si A se ingreso despues de B (En cuanto a minutos), cambiar es true
                else if (a->HoraRegistro.Hora == b->HoraRegistro.Hora && a->HoraRegistro.Minuto > b->HoraRegistro.Minuto)
                    cambiar = true;
            }

            // Si despues de todas las condiciones, cambiar es true, se hace un swap entre A y B mediante un auxiliar
            if (cambiar) {
                void *temp = nodoA->data;
                nodoA->data = nodoB->data;
                nodoB->data = temp;
                flag = true;
            }
            // Se avanza a los siguientes nodos de A y B
            nodoA = nodoB;
            nodoB = nodoB->next;
        }
    }
}

void BuscarTicket(List *ListaTickets) //Funcion para buscar un ticket especifico mediante ID
{
    TipoTicket *Ticket;
    ListaTickets->current = ListaTickets->head;

    if(ListaTickets->size == 0)
    {
        printf("\n\nLISTA DE TICKETS ESTA VACIA");
        return;
    }
    printf("\n\nIngrese la ID del ticket: ");
    char temp[100];
    scanf("%99s", temp);
    for(int i = 0; i < ListaTickets->size; i++) // Se recorre la lista en busca de la ID mediante un char Auxiliar
    {
        Ticket = (TipoTicket*) ListaTickets->current->data;
        if((strcmp(temp,Ticket->ID) == 0)) // Si se encuentra la ID, se muestra la informacion
        {
            printf("\n\n======================\n");
            printf("INFORMACION DEL TICKET\n");
            printf("======================\n");
            printf("ID: %s\n", Ticket->ID);
            printf("Descripcion: %s\n", Ticket->Descripcion);
            printf("Prioridad: %s\n", Ticket->Prioridad);
            printf("Hora de Registro: %i:%i\n", Ticket->HoraRegistro.Hora, Ticket->HoraRegistro.Minuto);
            return;
        }
        ListaTickets->current = ListaTickets->current->next;
    }
    printf("\n\nNO SE ENCONTRO EL TICKET CON LA ID %s\n", temp); // Si se llega al final de la lista y no se encuentra la ID se devuelve un mensaje
}

void registrarTicket(List *ListaTickets) // Funcion para registrar un ticket y guardarlo en la lista
{
    char tempID[100];
    char tempDescripcion[2000];
    char tempPrioridad[10];
    printf("\nIngrese ID del ticket: ");
    scanf("%99s", tempID); //se lee la ID mediante un Aux
    getchar();

    Node *nodoAUX = ListaTickets->head;
    while(nodoAUX != NULL) // Se busca el ticket para verificar que no exitan dos tickets con la misma ID
    {
        TipoTicket *TicketAux = (TipoTicket*) nodoAUX->data;
        if(strcmp(tempID, TicketAux->ID) == 0) // Si se encuentra otro ticket con la misma ID se muestra un mensaje
        {
            printf("\nTICKET %s YA HA SIDO INGRESADO\n", tempID);
            return;
        }
        nodoAUX = nodoAUX->next;
    }

    printf("Ingrese Descripcion del Problema: "); // Se ingresa el problema y se guarda en una variable Aux
    fgets(tempDescripcion, sizeof(tempDescripcion), stdin);

    size_t len = strlen(tempDescripcion); //Se obtiene el largo de la descripcion
    if (len > 0 && tempDescripcion[len - 1] == '\n') { // Si el largo de la descripcion es mayor a 0 y el ultimo caracter de esta es un salto de linea
        tempDescripcion[len - 1] = '\0';                // Se cambia el salto de linea por un caracter nulo 
    }
    TipoHora *Hora = GuardarHora(ListaTickets); //Se guarda la hora en un struct auxiliar
    strcpy(tempPrioridad, "BAJA"); // Se asigna la prioridad baja
    TipoTicket *Ticket = createTicket(tempID, tempDescripcion, tempPrioridad, Hora); // SE crea el ticket con los datos anteriormente guardados en auxiliares
    free(Hora); // Se libera la memoria del struct temporal
    list_pushBack(ListaTickets, Ticket); // Ingresa el ticket a la lista
    printf("\nTicket Ingresado con Exito!"); // Muestra mensaje de operacion realizada con exito
}

void AsignarPrioridad(List *ListaTickets) // Funcion para asignar la prioridad a los tickets
{
    TipoTicket *Ticket;
    ListaTickets->current = ListaTickets->head;

    if(ListaTickets->size == 0) // Si la lista esta vacia, muestra mensaje indicandolo
    {
        printf("\n\nLISTA DE TICKETS ESTA VACIA");
        return;
    }
    printf("\n\nIngrese la ID del ticket: "); //Se pide la ID del ticket a asignar nueva prioridad
    char temp[100];
    scanf("%99s", temp);
    while(ListaTickets->current != NULL) // Recorrer la lista para encontrar el ticket
    {
        Ticket = (TipoTicket*) ListaTickets->current->data;
        if((strcmp(temp,Ticket->ID) == 0)) //Si se encuentra al ticket se realiza un menu de seleccion de prioridad
        {
            char tempPrioridad[2];
            int seleccionPriori;
            printf("=================================================\n");
            printf("Indique nueva prioridad para el Ticket %s:\n\n",temp);
            printf("1) BAJA\n");
            printf("2) MEDIA\n");
            printf("3) ALTA\n\n");
            scanf("%1s", tempPrioridad);
            getchar();

            if(isdigit(tempPrioridad[0])) // Verifica si es un numero valido
            {
                seleccionPriori = atoi(tempPrioridad);
            }
            else{
                printf("\nEL PROGRAMA TUVO UN ERROR :(");
                return;
            }

            if(seleccionPriori == 1) //PRIORIDAD BAJA
            {
                strcpy(Ticket->Prioridad, "BAJA");
                printf("\n>>>LA PRIORIDAD DE EL TICKET %s SE ASIGNO COMO BAJA<<<\n\n", temp);
            }

            else if(seleccionPriori == 2) //PRIORIDAD MEDIA
            {
                strcpy(Ticket->Prioridad, "MEDIA");
                printf("\n>>>LA PRIORIDAD DE EL TICKET %s SE ASIGNO COMO MEDIA<<<\n\n", temp);
            }

            else if(seleccionPriori == 3) //PRIORIDAD ALTA
            {
                strcpy(Ticket->Prioridad, "ALTA");
                printf("\n>>>LA PRIORIDAD DE EL TICKET %s SE ASIGNO COMO ALTA<<<\n\n", temp);
            }

            else{ //OTRO NUMERO AL DE LAS OPCIONES ANTERIORES
                printf("\nPOR FAVOR SELECCIONAR UNA OPCION VALIDA\n");
            }

            ordenarTickets(ListaTickets); // ordena la lista 

            return;
        }
        ListaTickets->current = ListaTickets->current->next;
    }
    printf("\n\nNO SE ENCONTRO EL TICKET CON LA ID %s\n", temp); // Si no se encuentra el ticket muestra un mensaje
}

void MostrarTicketsPendientes(List *ListaTickets) // Funcion para mostrar tickets pendientes
{
    if(ListaTickets->size == 0|| ListaTickets->head == NULL) // Si la lista esta vacia se muestra mensaje
    {
        printf("\n\nNO HAY TICKETS PENDIENTES\n");
    }
    else{ // Si no esta vacia se muestra cada ticket dentro de la lista recorriendo la misma
        Node *Current = ListaTickets->head;

        printf("\n\n===========================\n");
        printf("LISTA DE TICKETS INGRESADOS\n");
        printf("===========================\n");

        while(Current != NULL)
        {
            TipoTicket *Ticket = (TipoTicket *) Current->data;
            printf("\nID: %s\n", Ticket->ID);
            printf("Descripcion: %s\n", Ticket->Descripcion);
            printf("Prioridad: %s\n", Ticket->Prioridad);
            printf("Hora de Registro: %i:%i\n", Ticket->HoraRegistro.Hora, Ticket->HoraRegistro.Minuto);
            Current = Current->next;
        }
        printf("\n===========================\n");
    }
}

void ProcesarSiguiente(List *ListaTickets) // Funcion para procesar el siguiente ticket
{
    if(ListaTickets->size == 0) // Si la lista esta vacia muestra un mensaje
    {
        printf("\nNO HAY TICKETS PENDIENTES");
    }
    else{ // Si la lista no esta vacia se despliega un menu para poder saber cual es el siguiente en la lista
        printf("\n========================\n");
        printf("SIGUIENTE TICKET EN COLA\n");
        printf("========================\n");

        TipoTicket *SgteTicket = (TipoTicket *) ListaTickets->head->data;

        printf("\nID: %s\n", SgteTicket->ID);
        printf("Descripcion: %s\n", SgteTicket->Descripcion);
        printf("Prioridad: %s\n", SgteTicket->Prioridad);
        printf("Hora de Registro: %i:%i\n\n", SgteTicket->HoraRegistro.Hora, SgteTicket->HoraRegistro.Minuto);

        printf("Seleccione la operacion:\n\n");
        printf("1) Procesar\n"); // Si la seleccion es 1 se procesa el ticket 
        printf("2) Regresar\n"); // Si la seleccion es 2 se regresa al menu principal

        char temp[2];
        int seleccion;
        scanf("%1s", temp);
        getchar();
        if(!isdigit(temp[0])) // Si se selecciona un caracter que no es un numero aparece un mensaje de error y se cierra el programa
        {
            printf("EL PROGRAMA TUVO UN ERROR :(");
            return;
        }
        else
        {
            bool swp = true; // swap para volver al menu principal
            while(swp == true){
                seleccion = atoi(temp);
                if(seleccion > 2 || seleccion < 1) // Si la opcion es otro numero al de las opciones, da chance a escoger otra alternativa
                {
                    printf("\nSELECIONE UNA OPCION VALIDA\n");
                    printf("1) Procesar\n");
                    printf("2) Regresar\n");
                    scanf("%1s", temp);
                    getchar();
                    if(!isdigit(temp[0])) { // Si la opcion es un char != digito entonces el programa se cierra
                        printf("EL PROGRAMA TUVO UN ERROR :(\n");
                        return;
                    }
                }
                else if(seleccion == 1)
                {
                    list_popFront(ListaTickets); // Si la opcion es 1 se elimina el ticket mostrado
                    free(SgteTicket); //Se libera la memoria de el ticket eliminado
                    printf("\nTicket Procesado con Exito!\n");
                    swp = false; // Se vuelve al menu principal
                }
                else if(seleccion == 2)
                {
                    swp = false; // Se vuelve al menu principal
                    return;
                }
            }
        }
    }
}

int main(){
    int seleccion; // Int para registrar la seleccion del usuario
    List *Tickets = list_create(); // Creacion de la lista de tickets

    while (true) // Bucle para menu principal
    {
        MostrarMenu(); // Muestra menu
        char temp[2]; // registra la opcion elegida por el usuario
        scanf("%1s", temp);
        getchar();

        if(isdigit(temp[0])) // Si la opcion fue un digito se almacena en un int
        {
            seleccion = atoi(temp);
        }
        else{
            printf("\nEL PROGRAMA TUVO UN ERROR :("); // Si la opcion fue distinta a un digito se cierra el programa
            break;
        }

        if(seleccion == 1) // Si la opcion es 1 se registra el ticket nuevo
        {
            registrarTicket(Tickets);
        }
        else if(seleccion == 2) // Si la opcion es 2 se le asigna una nueva prioridad a un ticket existente
        {
            AsignarPrioridad(Tickets);
        }
        else if(seleccion == 3) // Si la opcion es 3 se muestran todos los tickets de la lista (pendientes)
        {
            MostrarTicketsPendientes(Tickets);
        }
        else if(seleccion == 4) // Si la opcion es 4 se procesa el siguiente ticket de la lista (el primero)
        {
            ProcesarSiguiente(Tickets);
        }
        else if(seleccion == 5) // Si la opcion es 5 se busca un ticket mediante su ID
        {
            BuscarTicket(Tickets);
        }
        else if(seleccion == 6){ // Si la opcion es 6 se sale de el programa y se libera la memoria de la lista de tickets
            printf("\nVuelve Pronto!!\n\n");
            free(Tickets);
            break;
        }
        else if(seleccion > 6 || seleccion < 1){ // Si la opcion es otro numero al de las opciones se solicita seleccionar una opcion valida
            printf("\n\nPOR FAVOR SELECCIONAR UNA OPCION VALIDA\n");
        }
        printf("\n");
    }
    return 0;
}