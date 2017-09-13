// Comandos de compilado
//		cd Escritorio
// 		gcc Obligatorio_01.c -o Obligatorio_01.out
// 		./Obligatorio_01.out
// 
// Descripcion abstracta
//
// 		El programa dse diviode en dos partes acada una sera ejecutada 
// o bien por un hilo o por un proceso.Estas partes seran sincronisadas
// por una variable en moemoria compartida o global q se encarga de 
// coordinar el trabajo de cada parte (hilo/proceso). 
//		Parte Cronometraje : dependindo de la variable trabajo ara una 
// funcion o  otra.
//		Parte Interfas: El esperara al usuario en funcion de su nesesidad 
// cambiara la var global
// 		La var global tendra el reloj marca seleccionada * 100 sumada a 
// la opcion a acer

// < Carga dependintes >
	// Generales
		#include <stdio.h>
		#include <stdlib.h>
	// Para funciones de string
		#include <string.h>
	// Para reloj
		#include <unistd.h>
	// Para Procesos
	/*	#include <sys/shm.h>
		#include <sys/types.h>
		#include <sys/ipc.h>
	*/
	// Parra Hilos
		#include <pthread.h>

// Declara
//Estructuras
	typedef struct ListaIdentificar {
		struct nodoLista * ini;
		struct nodoLista * fin;
		int tam;
	}Lista;

	typedef struct nodoLista {
		char * dat;
		int tim;
		int sta;
		int id;
		struct nodoLista * sig;
	}Nodo;

//Var
	Lista * Reloj;
	Lista * Marcas;
	char * dir[2] = {"MyReloj.txt","MyMarcas.txt"};
	int trabajo = 0;

// head
	void gotoxy (int x, int y);
	void AniadirFichero(char * dir, char * name, int time);
	void ActualisarFichero(char * dir, char * name, char * rename, int d, int todo) ;
	void CargarFichero(Lista *lista, char * dir);
	void GuardarFichero(Lista *lista, char * dir) ;
	void ListaVaciar(Lista *lista);
	void ListaVisualisar(Lista *lista);
	void EliminarEnLista(Lista *lista, int pos);
	void InsertarNodo(Lista *lista, char * dat, int tim, int sta);
	void OpcionesInicio(int pos);
	void NuevoReloj();
	void ListaReloj(int pos);
	void VaciarLista(Lista *lista);
	void SolicitaDato(char * imp);
	void AniadirMarca(int index);
	void EliminarMarca(int index);
	void EjecutaOpciones(int opcion,char * name,int index);
	void ImprimeHora(int hora,int stado);
	void SumaReloj();
	void Pausar(int index);
	void PantallaError();
	void PantallaExito();
	void PantallaBinbenida();
	void PantallaDespedida();

	int ListaMarcas();
	int OpcioneReloj();
	int SeleccionReloj(char * dir);

	void * Cronometrar();
	void * Interfas();




// Funciones 
void gotoxy (int x, int y) {
	fflush(stdout);
	printf("\033[%d;%df", x, y);
}
void AniadirFichero(char * dir, char * name, int time){
	FILE * Ficheros;
	int tamano;
	Ficheros = fopen( dir,"r+");
		fseek(Ficheros , 0 , SEEK_SET );
		fscanf(Ficheros, "%d", &tamano);
		fseek(Ficheros , 0 , SEEK_SET );
		fprintf(Ficheros, "%d\n",++tamano);
		fseek ( Ficheros , 0 , SEEK_END );
		fprintf(Ficheros, "%-50.50s %-8.8d\n",name,time);
	fclose (Ficheros);
}
void ActualisarFichero(char * dir, char * name, char * rename, int d, int todo) {
	char Nombre[50];
	fpos_t posChar, posNum, posFin;
	int modi = 0;
	int Tiempo, tamano = 0, i;
	FILE * pFile;

	pFile = fopen (dir,"r+");
	fscanf (pFile, "%d", &tamano);
	for (i = 0; i < tamano; ++i){
		fgetpos(pFile, &posChar);

		fscanf(pFile, "%s", Nombre);
		fgetpos(pFile, &posFin);

		fscanf(pFile, "%d", &Tiempo);
		fgetpos(pFile, &posNum);

		if (strcmp(name,Nombre) == 0){
			fsetpos(pFile, &posChar);
			if (rename != NULL){
				fprintf(pFile, "\n%-50.50s %-8.8d",rename,d);
			}else {
				if (d==-1){
					tamano--;
					fprintf(pFile,"\n                                                           ");
				} else {
					fprintf(pFile, "\n%-50.50s %-8.8d",name,d);
				}
			}
			if (todo = 0)
				return;
		}
	}
	fseek ( pFile , 0 , SEEK_SET );
	fprintf(pFile,"%d\n",tamano);
	fclose (pFile);
}

void CargarFichero(Lista *lista, char * dir){
	char Nombre[50];
	int Tiempo = 0, tamano = 0, i;

	FILE * pFile;
	pFile = fopen (dir,"r");
	fscanf (pFile, "%d", &tamano);
	for (i = 0; i < tamano; ++i){
		fscanf (pFile, "%s", Nombre);
		fscanf (pFile, "%d", &Tiempo);
		printf("%-50.50s %-8.8d\n",Nombre,Tiempo);
		InsertarNodo(lista, Nombre,Tiempo,0);
	}
	fclose (pFile);
}
void GuardarFichero(Lista *lista, char * dir) {
	FILE * pFile;
	pFile = fopen (dir,"w");
	Nodo *aux = lista->ini;
	fprintf (pFile, "%d\n", lista->tam);
	while(aux != NULL){
		fprintf(pFile, "%-50.50s %-8.8d\n",aux->dat,aux->tim);
		aux = aux->sig;
	}
	fclose (pFile);
}

void ListaVaciar(Lista *lista){
	Nodo *actual = lista->ini;
	Nodo *borrar;
	while(actual != NULL){
		borrar = actual;
		actual = actual->sig;
		free(borrar->dat);
		free(borrar);
	}
	lista->ini = NULL;
	lista->fin = NULL;
	lista->tam = 0;
}
void ListaVisualisar(Lista *lista){
	Nodo *aux = lista->ini;
	printf("----\n");
	while(aux != NULL){
		printf("%s %d\n",aux->dat,aux->tim);
		aux = aux->sig;
	}
	printf("----\n");
}
void EliminarEnLista(Lista *lista, int pos){
	if(lista->tam == 0 && pos == 0){
		printf("Lista sin valores");
		return;
	}
	if(lista->tam <= 1 || pos >= lista->tam){
		printf("Posicion fuera de lista");
		return;
	}
	Nodo *actual;
	actual = lista->ini;
	if(pos > 0){
		Nodo *borrar;
		int i;
		for(i=1;i<pos;++i)
		    actual = actual ->sig;
		borrar = actual->sig;
		actual->sig = actual->sig->sig;
		if(actual->sig==NULL)
		    lista->fin = actual;
		free(borrar->dat);
		free(borrar);
		lista->tam--;
	}else if(pos == 0){
		lista->ini=lista->ini->sig;
		if(lista->tam==1)
		    lista->fin = NULL;
		free(actual->dat);
		free(actual);
		lista->tam--;
	}
}
void InsertarNodo(Lista *lista, char * dat, int tim, int sta){
	Nodo *nodo = (Nodo *)malloc(sizeof(Nodo));
	nodo->dat = (char *)malloc(50*sizeof(char));
	strcpy(nodo->dat, dat);
	nodo->tim = tim;
	nodo->sta = sta;
	nodo->id = lista->tam;
	nodo->sig = NULL;
	if(lista->tam == 0){
		lista->ini = nodo;
		lista->fin = nodo;
	}else{
		lista->fin->sig = nodo;
		lista->fin = nodo;
	}
	lista->tam++;
}



void OpcionesInicio(int pos){
	gotoxy(0,0);
	if(pos==-1){
		printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━┯━━━━━━━━━━━━━━━━━━━━━━━━━┯━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
		printf("┃    Seleccionar reloj    │       Nuevo reloj       │          Salir          ┃\n");
		printf("┃ ─────────────────────────────────────────────────────────────────────────── ┃\n");
		printf("┃            1            │            2            │            3            ┃\n");
		printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━┷━━━━━━━━━━━━━━━━━━━━━━━━━┷━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	}else{
		printf("┏━━━━━━━━━━━━━━━━━━━━━━┯━━━━━━━━━━━━━━━━━┯━━━━━━━━━━━━━━━━━┯━━━━━━━━━━━━━━━━━━┓\n");
		printf("┃  Seleccionar reloj   │   Nuevo reloj   │      Salir      │   Aniadir marca   ┃\n");
		printf("┃ ─────────────────────────────────────────────────────────────────────────── ┃\n");
		printf("┃           1          │        2        │        3        │        4         ┃\n");
		printf("┗━━━━━━━━━━━━━━━━━━━━━━┷━━━━━━━━━━━━━━━━━┷━━━━━━━━━━━━━━━━━┷━━━━━━━━━━━━━━━━━━┛\n");
	}
}
void NuevoReloj(){
	system("clear");
	char Nombre[50];
	int  Tiempo = -1;
	gotoxy(2,0);
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("┃                                 Nuevo reloj                                 ┃\n");
	printf("┃ ─────────────────────────────────────────────────────────────────────────── ┃\n");
	printf("┃                                                                             ┃\n");
	printf("┃   Nombre del reloj    ___________________________________________________   ┃\n");
	printf("┃                                                                             ┃\n");
	printf("┃   Tiempo en segundos  ___________________________________________________   ┃\n");
	printf("┃                                                                             ┃\n");
	printf("┃                                                                             ┃\n");
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	gotoxy(6,25);
	scanf("%sd",Nombre);
	gotoxy(8,25);
	scanf("%d",&Tiempo);
	ActualisarFichero(dir[0],Nombre,NULL,Tiempo,-1);
}
void ListaReloj(int pos){
	gotoxy(pos,0);
	Nodo *aux = Reloj->ini;
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("┃                                 Mi relojes                                  ┃\n");
	printf("┃ ─────────────────────────────────────────────────────────────────────────── ┃\n");
	while(aux != NULL){
		printf("┃  %-50.50s",aux->dat);
		ImprimeHora(aux->tim,aux->sta);
		gotoxy(pos,79);
		printf("┃\n");
		pos++;
		aux = aux->sig;
	}
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
};
int ListaMarcas(){
	int Input = 1,pos = 2, index = 3;
	int Tiempo = 0, tamano = 0, i;
	char Nombre[50];
	FILE * pFile;
	do{
		system("clear");
		pos = 2;
		gotoxy(pos,0);
		printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
		if(Input==1)
			printf("┃                               Menu seleccionar                              ┃\n");
		else
			printf("┃                                Fuera de rango                               ┃\n");
		printf("┃ ─────────────────────────────────────────────────────────────────────────── ┃\n");
		printf("┃                                                                             ┃\n");
		pos = 6;
		pFile = fopen (dir[1],"r");
		fscanf (pFile, "%d", &tamano);
		for (i = 0; i < tamano; ++i){
			index++;
			fscanf (pFile, "%s", Nombre);
			fscanf (pFile, "%d", &Tiempo);
			printf("┃       %d %-50.50s", index, Nombre);
			ImprimeHora(Tiempo,-1);
			gotoxy(pos,79);
			printf("┃\n");
			pos++;

		}
		fclose (pFile);
		printf("┃                                                                             ┃\n");
		printf("┃        1-Salir           2-Aniadir Marcar         n-Eliminar Marcas n        ┃\n");
		printf("┃                                                                             ┃\n");
		printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
		pos++;
		gotoxy(pos,35);
		scanf("%d",&Input);
	}while((trabajo != 4 || trabajo != 1) && (Input < 0 || Input > tamano+3));
	return Input;
};

void VaciarLista(Lista *lista){
	Nodo *actual = lista->ini;
	Nodo *borrar;
	while(actual != NULL){
		borrar = actual;
		actual = actual->sig;
		free(borrar->dat);
		free(borrar);
	}
	lista->ini = NULL;
	lista->fin = NULL;
	lista->tam = 0;
}

int OpcioneReloj(){
	int  Input = 1;
	do{
		system("clear");
		gotoxy(2,0);
		printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
		if(Input == 1){
		printf("┃                                  Opciones                                   ┃\n");
		}else{
		printf("┃                               Fuera de rango                                ┃\n");
		}
		printf("┃ ─────────────────────────────────────────────────────────────────────────── ┃\n");
		printf("┃                                                                             ┃\n");
		printf("┃   1 Cambair Tiempo                                                          ┃\n");
		printf("┃   2 Renombrer reloj                                                         ┃\n");
		printf("┃   3 Resetear reloj                                                          ┃\n");
		printf("┃   4 Eliminar reloj                                                          ┃\n");
		printf("┃   5 Pausar/Reanudar reloj                                                   ┃\n");
		printf("┃   6 Aniadior marcas                                                          ┃\n");
		printf("┃   7 Eliminar marcas                                                         ┃\n");
		printf("┃   8 Mostrar marcas                                                          ┃\n");
		printf("┃                                                                             ┃\n");
		printf("┃   Opcion:  ______________________________________________________________   ┃\n");
		printf("┃                                                                             ┃\n");
		printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
		gotoxy(14,14);
		scanf("%d",&Input);
	}while((trabajo != 4 || trabajo != 1) && (Input < 0 || Input > 9));
	return Input;
}
int SeleccionReloj(char * dir){
	int  Input = 1,pos,index;
	int Tiempo = 0, tamano = 0, i;
	char Nombre[50];
	FILE * pFile;
	do{
		system("clear");
		pos = 2, index = 0;
		gotoxy(pos,0);
		printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
		if (Input==1)
			printf("┃                               Menu seleccionar                              ┃\n");
		else
			printf("┃                                Fuera de rango                               ┃\n");
		printf("┃ ─────────────────────────────────────────────────────────────────────────── ┃\n");
		printf("┃                                                                             ┃\n");
		pos = 6;
		pFile = fopen (dir,"r");
		fscanf (pFile, "%d", &tamano);
		for (i = 0; i < tamano; ++i){
			fscanf (pFile, "%s", Nombre);
			fscanf (pFile, "%d", &Tiempo);
			printf("┃      %d %-50.50s", index, Nombre);
			ImprimeHora(Tiempo,-1);
			gotoxy(pos,79);
			printf("┃\n");
			pos++;
			index++;

		}
		fclose (pFile);
		printf("┃                                                                             ┃\n");
		printf("┃   Que reloj quieres selecionar  _________________________________________   ┃\n");
		printf("┃                                                                             ┃\n");
		printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
		pos++;
		gotoxy(pos,35);
		scanf("%d",&Input);
	}while((trabajo != 4 || trabajo != 1) && (Input < 0 || Input > tamano+1));
	return Input;
}
void SolicitaDato(char * imp){
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("┃                                Modificacion                                 ┃\n");
	printf("┃ ─────────────────────────────────────────────────────────────────────────── ┃\n");
	printf("%s\n", imp);
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
}
void AniadirMarca(int index){
	char auxchar[50];
	int tamano,Tiempo;
	FILE * pFile;
	pFile = fopen (dir[0],"r");
	fscanf (pFile, "%d", &tamano);
	for (int i = 0; i <= index; ++i){
		fscanf (pFile, "%s", auxchar);
		fscanf (pFile, "%d", &Tiempo);
	}
	fclose (pFile);
	AniadirFichero(dir[1],auxchar,Tiempo); 
}
void EliminarMarca(int index){
	char auxchar[50];
	int tamano,Tiempo;
	fpos_t posChar;
	FILE * pFile;
	pFile = fopen (dir[1],"r");
	fscanf (pFile, "%d", &tamano);
	for (int i = 0; i <= index; ++i){
		fgetpos(pFile, &posChar);
		fscanf (pFile, "%s", auxchar);
		fscanf (pFile, "%d", &Tiempo);
	}
	fsetpos(pFile, &posChar);
	fprintf(pFile,"\n                                                           ");
	fseek ( pFile , 0 , SEEK_SET );
	tamano--;
	fprintf(pFile,"%d\n",tamano);
	fclose (pFile);
}

void EjecutaOpciones(int opcion,char * name,int index){
	int newtime = -1,aux;
	char rename[50];

	switch(opcion){
		case 1: // Cambair   Tiempo
			SolicitaDato("┃  Nuevo tiempo (segundos)  ________                                             ┃");
			scanf("%d", &newtime);
			ActualisarFichero(dir[0],name, NULL, newtime,-1);
		break;
		case 2: // Renombrer reloj 
			SolicitaDato("┃  Nuevo Nombre (50 Maximo)  __________________________________________________  ┃");
			scanf("%s", rename);
			ActualisarFichero(dir[0],name, rename, -1,-1);
			ActualisarFichero(dir[1],name, rename, -1,-1);
		break;
		case 3: // Resetear  reloj
			ActualisarFichero(dir[0],name, NULL,  0,-1);
			ActualisarFichero(dir[1],name, NULL, -1,-1);
		break;
		case 4: // Eliminar  reloj 
			ActualisarFichero(dir[0],name, NULL, -1,-1);
			ActualisarFichero(dir[1],name, NULL, -1,-1);
		break;
		case 5: // Pausar    reloj 
			trabajo = (index*100) + 5; 
		break;
		case 6: // Aniadior   marcas
			AniadirMarca(index);
		break;
		case 7: // Eliminar  marcas
			ActualisarFichero(dir[1],name, NULL, -1,-1); 
		break;
		case 8: // Mostrar   marcas 
			aux = ListaMarcas();
			if (aux != 1){
				if (aux == 2)
					AniadirMarca(index);
				else
					EliminarMarca(aux-2);
			}
		break;
	}
}
void ImprimeHora(int hora,int stado){
	int i ;
	int D ,H ,M ,S;
	D = hora/(60*60*24);
	hora = hora%(60*60*24);
	H = hora/(60*60);
	hora = hora%(60*60);
	M = hora/60;
	hora = hora%(60);
	S = hora;
	printf(" %d",D/10);
	printf("%d",D%10);
	printf(":");
	printf("%d",H/10);
	printf("%d",H%10);
	printf(":");
	printf("%d",M/10);
	printf("%d",M%10);
	printf(":");
	printf("%d",S/10);
	printf("%d",S%10);
	if (stado == 1)
		printf(" | Parado");
	else if (stado == 0)
		printf(" | Corrindo");
}
void SumaReloj(){
	Nodo *aux = Reloj->ini;
	while(aux != NULL){
		if (aux->sta == 0)
			aux->tim++;
		aux = aux->sig;
	}
};
void Pausar(int index){
	Nodo *aux = Reloj->ini;
	for (int i = 0; i <= index; ++i){
		aux = aux->sig;
	}
	if (aux->sta == 0)
		aux->sta = 1;
	else
		aux->sta = 0;
}
void PantallaError();
void PantallaExito();
void PantallaBinbenida();
void PantallaDespedida();





//Funciones Principales
	void * Cronometrar(){
		int postCursor;
		while(trabajo!=4){
			postCursor=0;
			switch(trabajo%100){
				case 1: // Correr y muestra reloj
					SumaReloj();
					ListaReloj(8);
				break;
				case 2: // Correr reloj
					SumaReloj();
				break;
				case 3: // Actualisar
					VaciarLista(Reloj);
					VaciarLista(Marcas);
					CargarFichero(Reloj, dir[0]);
					CargarFichero(Marcas, dir[1]);
					trabajo = 3;
				break;
				case 5: // Correr reloj
					Pausar(trabajo/100);
				break;
			}
			sleep(1);
		}
		GuardarFichero(Reloj, dir[0]);
		GuardarFichero(Marcas, dir[1]);
	}
	void * Interfas(){
		FILE * pFile;
		char Nombre[50];
		int Eleccion,aux,Tiempo,index = -1,postCursor=0,tamano;
		while(trabajo!=4){
			system("clear");
			OpcionesInicio(index);
			scanf("%d",&Eleccion);
			switch(Eleccion){
				case 1:	// Nuevo reloj
					trabajo=2;
					NuevoReloj();
					trabajo=3;
				break;
				case 2: // Seleccion 
					trabajo=2;
					index = SeleccionReloj(dir[0]);

					pFile = fopen (dir[0],"r+");
					fscanf (pFile, "%d", &tamano);
					for (int i = 0; i <= index; ++i){
						fscanf (pFile, "%s", Nombre);
						fscanf (pFile, "%d", &Tiempo);
					}
					aux = OpcioneReloj();
					EjecutaOpciones(aux,Nombre,index);

					trabajo=3;
				break;
				case 3: // Salir
					trabajo=4;
				break;
				case 4: // Salir
					if(index !=-1){
						trabajo=2;
						AniadirMarca(index);
						trabajo=1;
					}
				break;
			}
		}
	}


//Funcion main
void main()
{
	Reloj = (Lista *) malloc (sizeof (Lista));
	Reloj->ini = NULL;
	Reloj->fin = NULL;
	Reloj->tam = 0;

	Marcas = (Lista *) malloc (sizeof (Lista));
	Marcas->ini = NULL;
	Marcas->fin = NULL;
	Marcas->tam = 0;

	system("clear");
	trabajo=1;
	CargarFichero(Reloj,dir[0]);
	CargarFichero(Marcas,dir[1]);
	pthread_t th1, th2; 
	pthread_create(&th1, NULL, Interfas, NULL);
	sleep(1);
	pthread_create(&th2, NULL, Cronometrar, NULL);
	pthread_join(th1,NULL);

}