// ===============================
// LIBRERIAS
// ===============================

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <mmsystem.h>
#include <time.h>
#include <conio.h>
#include <string.h>


// ===============================
// ESTRUCTURAS
// ===============================


// Usuarios
struct usuario{
    char nombre[30];
    char contra[10];
};

typedef struct usuario usuario;


// Nodo canción
typedef struct _cancion cancion;

struct _cancion{

    const char *ruta;
    const char *nombre;

    cancion *prev;
    cancion *sig;
};


// Lista doble circular
typedef struct _listacanciones lista_can;

struct _listacanciones{

    cancion *primera;
    int num;

};


// ===============================
// VARIABLES GLOBALES
// ===============================


FILE *ap;


usuario U[100];


char nom[30];
char con[10];


int b=0;
int r=0;
int nusuarios=0;
int actual=0;


// ===============================
// PROTOTIPOS
// ===============================


// Pantallas
void inicio();
void creditos();
void menu();


// Usuarios
void leer();
void guardarR();
void registro();


// Reproducción
void reproducir(const char *ruta);
void parar();
void adelantar(cancion *actual);
void retroceder(cancion *actual);


// Lista canciones

lista_can *crearListaCanciones();

cancion *crearUnicaCancion(
    const char *rut,
    const char *nom
);


cancion *crearCancion(
    const char *rut,
    const char *nom,
    cancion *previa,
    cancion *siguiente
);


void agregar_cancion(
    lista_can *l,
    const char *rut,
    const char *nom
);


cancion *seleccionarCancionIndice(
    lista_can *lista,
    int indice
);


void listarCanciones(lista_can *lista);


int buscarCancion(
    lista_can *l,
    char *n
);



// ===============================
// PANTALLA INICIO
// ===============================


void inicio(){

system("CLS");


printf("\n\n");

printf("\t\t=============================================\n");
printf("\t\t              REPRODUCTOR MP3\n");
printf("\t\t=============================================\n");

printf("\n");
printf("\t\tSistema de reproduccion de musica\n");
printf("\t\tLista doble circular\n");
printf("\t\tControl de canciones\n");
printf("\t\tUsuarios registrados\n");

printf("\n");
printf("\t\t=============================================\n");


system("PAUSE");

}



// ===============================
// CREDITOS
// ===============================


void creditos(){

system("CLS");


printf("\n\n");
printf("\t\t================================\n");
printf("\t\t             CREDITOS\n");
printf("\t\t================================\n\n");


printf("\t\tAlva Salazar Jose Luis\n");
printf("\t\tGalvan Alvarez Luis Miguel\n");
printf("\t\tHernandez Ciprian Mariana\n");
printf("\t\tJuarez Flores Axel Daniel\n");


printf("\n\n");

system("PAUSE");

}



// ===============================
// MENU PRINCIPAL
// ===============================


void menu(){

printf("\n\n");
printf("\t\tMENU CANCIONES\n\n");


printf("1. Reproducir\n");
printf("2. Parar\n");
printf("3. Adelantar\n");
printf("4. Retroceder\n");
printf("5. Modo aleatorio\n");
printf("6. Lista de canciones\n");
printf("7. Buscar cancion\n");
printf("8. Salir\n");


printf("\nSelecciona una opcion: ");

}

// ===============================
// REPRODUCCION
// ===============================


void reproducir(const char *ruta){

    sndPlaySound(ruta, SND_ASYNC);

}


void parar(){

    sndPlaySound(NULL, SND_ASYNC);

}


void adelantar(cancion *actual){

    if(actual!=NULL)
        reproducir(actual->ruta);

}


void retroceder(cancion *actual){

    if(actual!=NULL)
        reproducir(actual->ruta);

}



// ===============================
// CREAR LISTA
// ===============================


lista_can *crearListaCanciones(){

    lista_can *l;

    l=(lista_can*)malloc(sizeof(lista_can));


    l->primera=NULL;
    l->num=0;


    return l;

}



// ===============================
// CREAR PRIMER NODO
// ===============================


cancion *crearUnicaCancion(
    const char *rut,
    const char *nom
){

    cancion *c;


    c=(cancion*)malloc(sizeof(cancion));


    c->ruta=rut;
    c->nombre=nom;


    // lista circular
    c->prev=c;
    c->sig=c;


    return c;

}



// ===============================
// INSERTAR NODO ENTRE DOS NODOS
// ===============================


cancion *crearCancion(
    const char *rut,
    const char *nom,
    cancion *previa,
    cancion *siguiente
){

    cancion *c;


    c=(cancion*)malloc(sizeof(cancion));


    c->ruta=rut;
    c->nombre=nom;


    c->prev=previa;
    c->sig=siguiente;


    previa->sig=c;
    siguiente->prev=c;


    return c;

}



// ===============================
// AGREGAR CANCION
// ===============================


void agregar_cancion(
    lista_can *l,
    const char *rut,
    const char *nom
){


    if(l->primera==NULL)
    {

        l->primera=
        crearUnicaCancion(rut,nom);

    }

    else
    {

        cancion *ultimo;


        ultimo=l->primera;


        while(ultimo->sig!=l->primera)
        {
            ultimo=ultimo->sig;
        }


        crearCancion(
            rut,
            nom,
            ultimo,
            l->primera
        );

    }


    l->num++;

}



// ===============================
// SELECCIONAR CANCION POR INDICE
// ===============================


cancion *seleccionarCancionIndice(
    lista_can *lista,
    int indice
){


    cancion *c;


    if(lista->num==0)
    {
        return NULL;
    }



    if(indice<0 || indice>=lista->num)
    {

        printf("\nIndice inexistente\n");

        return NULL;

    }



    c=lista->primera;


    for(int i=0;i<indice;i++)
    {

        c=c->sig;

    }



    return c;

}



// ===============================
// MOSTRAR LISTA DE CANCIONES
// ===============================


void listarCanciones(lista_can *lista){

    if(lista->primera==NULL)
    {

        printf("\nNo hay canciones\n");

        return;

    }



    cancion *actual;


    actual=lista->primera;



    for(int i=0;i<lista->num;i++)
    {

        printf("%d. %s\n",
        i+1,
        actual->nombre);


        actual=actual->sig;

    }


}



// ===============================
// BUSCAR CANCION POR NOMBRE
// ===============================


int buscarCancion(
    lista_can *l,
    char *n
){

    if(l->primera==NULL)
        return -1;



    cancion *c;


    c=l->primera;



    for(int i=0;i<l->num;i++)
    {


        if(strcmp(c->nombre,n)==0)
        {

            return i;

        }


        c=c->sig;


    }



    return -1;

}

// ===============================
// USUARIOS
// ===============================


void leer(){

    nusuarios=0;


    ap=fopen("usuarios.txt","r");


    if(ap==NULL)
    {
        return;
    }



    while(fscanf(ap,"%s %s",
    U[nusuarios].nombre,
    U[nusuarios].contra)!=EOF)
    {

        nusuarios++;

    }


    fclose(ap);

}



// ===============================
// GUARDAR USUARIO
// ===============================


void guardarR(){


    ap=fopen("usuarios.txt","a");


    if(ap==NULL)
    {
        printf("Error creando archivo");
        return;
    }



    fprintf(ap,"%s %s\n",
    nom,
    con);



    fclose(ap);



    printf("\nUsuario registrado correctamente\n");

}



// ===============================
// REGISTRO / LOGIN
// ===============================


void registro(){


    leer();



    printf("\nNombre de usuario: ");

    fflush(stdin);

    gets(nom);



    printf("Contrasenia: ");

    fflush(stdin);

    gets(con);



    for(int i=0;i<nusuarios;i++)
    {


        if(strcmp(nom,U[i].nombre)==0 &&
           strcmp(con,U[i].contra)==0)
        {

            printf("\nUsuario encontrado\n");

            b=1;

            actual=i;

            return;

        }


    }



    if(b==0)
    {

        printf("\nUsuario nuevo\n");

        guardarR();

    }



}



// ===============================
// MAIN
// ===============================


int main(){


    inicio();



    int op;

    int op2;

    int indice_cancion=-1;

    int num_canciones=10;

    int cancionrand;


    char n[64];



    lista_can *listagral;


    listagral=crearListaCanciones();



    // ===============================
    // CANCIONES
    // ===============================


    agregar_cancion(
    listagral,
    "musica\\1.wav",
    "Akon ft Snoop Dogg - I Wanna Love You");


    agregar_cancion(
    listagral,
    "musica\\2.wav",
    "Ariana Grande - 7 Rings");


    agregar_cancion(
    listagral,
    "musica\\3.wav",
    "Bob Sinclar - Love Generation");


    agregar_cancion(
    listagral,
    "musica\\4.wav",
    "Bruno Mars - Treasure");


    agregar_cancion(
    listagral,
    "musica\\5.wav",
    "Caifanes - Debajo de tu piel");


    agregar_cancion(
    listagral,
    "musica\\6.wav",
    "Ed Sheeran - I Don't Care");


    agregar_cancion(
    listagral,
    "musica\\7.wav",
    "Pato Banton - Go Pato");


    agregar_cancion(
    listagral,
    "musica\\8.wav",
    "Gorillaz - DARE");


    agregar_cancion(
    listagral,
    "musica\\9.wav",
    "Ir-Sais - Dream Girl");


    agregar_cancion(
    listagral,
    "musica\\10.wav",
    "Khalid - Talk");



    cancion *actualCancion=NULL;



    registro();



    do{


        system("CLS");



        if(actualCancion!=NULL)
        {

            printf("\nReproduciendo: %s\n",
            actualCancion->nombre);

        }



        menu();



        scanf("%d",&op);



        switch(op)
        {



        case 1:


            if(indice_cancion==-1)
            {
                indice_cancion=0;
            }


            actualCancion=
            seleccionarCancionIndice(
            listagral,
            indice_cancion);



            reproducir(
            actualCancion->ruta);



            break;




        case 2:


            parar();


            break;




        case 3:


            if(actualCancion!=NULL)
            {

                actualCancion=
                actualCancion->sig;


                indice_cancion++;


                if(indice_cancion>=num_canciones)
                {
                    indice_cancion=0;
                }


                reproducir(
                actualCancion->ruta);

            }


            break;




        case 4:


            if(actualCancion!=NULL)
            {

                actualCancion=
                actualCancion->prev;


                indice_cancion--;


                if(indice_cancion<0)
                {
                    indice_cancion=
                    num_canciones-1;
                }


                reproducir(
                actualCancion->ruta);

            }


            break;




        case 5:


            srand(time(NULL));


            cancionrand=
            rand()%num_canciones;



            actualCancion=
            seleccionarCancionIndice(
            listagral,
            cancionrand);



            indice_cancion=
            cancionrand;



            reproducir(
            actualCancion->ruta);



            break;




        case 6:


            listarCanciones(listagral);


            printf("\nNumero de cancion: ");

            scanf("%d",&op2);



            actualCancion=
            seleccionarCancionIndice(
            listagral,
            op2-1);



            indice_cancion=op2-1;



            reproducir(
            actualCancion->ruta);



            break;




        case 7:


            printf("\nNombre de la cancion: ");

            fflush(stdin);

            gets(n);



            indice_cancion=
            buscarCancion(
            listagral,
            n);



            if(indice_cancion!=-1)
            {


                actualCancion=
                seleccionarCancionIndice(
                listagral,
                indice_cancion);



                reproducir(
                actualCancion->ruta);



            }
            else
            {

                printf("\nCancion no encontrada");

                system("PAUSE");

            }


            break;




        case 8:


            creditos();

            break;



        default:


            printf("\nOpcion incorrecta");

            system("PAUSE");


        }



    }while(op!=8);



    return 0;

}
