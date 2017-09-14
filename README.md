# Cronometro
	Obligatorio de sistema operativo

## Estructuras
	- Cargo dependencias
	- Declaro variables
	- Declaro Funciones
	- Ejecuto cuerpo
	- Especificaciones funciones

## Seudo Codigo
	Inicialiso variavles
	Declara int trabajo
					array dir con directorios
					listas
	Comienzo hilos o procesos
	Guarda para persistencia 
	Liberar espacio de lista

### Descripción Hilo 1 o Proceso padre
	- Cronometraje
	- Recorrera lista y sumara uno a cada estado 1
	- Minreas trabajo no sea 4 
		-1 
			- IMPRIME OPCIONES DE INICIO
			- Imprimo en el recorido
		-2
			-Nada
		-3
			- Actualiso listas
		-4
			- Guardara el estado actual de las listas 
			- Finalzra del while
	- Interfase
	- Declaro tring para nombre, int para posicion, 
	- Espero un int del usuario
		- Nuevo reloj
			- Cambio trabajo a 2 para q no me muestre nada
			- Espero un string y un int
			- Guardo en fichero reloj
			- Cambio trabajo a 3
		- Seleccionar reloj
			- Cambio trabajo a 2 para q no me muestre nada
			- Muestro lista de relojes enumerada
			- Espero un int del usuario
			- Recoro el fichero asta posicion 
			- Guardo el nombre y posicion
			- Muestro opciones disponivles
				- Cambiar nombre
					- Imprimo pantalla
					- Solicito un string
					- Recorre el fichero reloj y marcas reemplasando los string
					- Modifico var nombre
				- Cambiar timpo
					- Solicito Timpo nuevo
					- Reemplaso timpo en relojes
				- Resetear reloj
					- Elimino marcas con el nombre del reoj
					- Cambio a cero el timpo del reloj en fichero
				- Eliminar reloj
					- elimino todas las apariciones del nombre en amvos ficheros
				- Mostrar marcas
					- recore ficheros imprimindo
				- Añadir marcas
					- agregar a fichero marcas el nombre y el timpo
				- vaciar marcas
					-  Elimino apariciones de marcas en ficheros
				- Eliminar marca
					- Muestro marcas
					- Solicito int al user
					- posicion de el int con nombres
				- Salir
			- cambia trabajo a 3
		- Salir
			-Trabajo 4

## Funciones esperadas
	### Ficheros
		-Actualisar ficheros
		-Eliminar fichero
		-Cargar fichero
	### Listas
		- Cargar de fichero 
		- Guardar en fichero
		- Eliminar de fichero
	### Imprecion
		- Reloj
		- opciones inicio
		- Nuevo reloj
		- Lista de relojes
		- Opciones de reloj
		- Seleccionde  reloj
		- Cambiar nombre de reloj
		- cambiar timpo del reloj
		- Lista de marcas
		- opciones de marcas
		- eliminar Solicita pos de marca
		- Pantalla error
		- Pantalla exito
		- Pantalla binbenida 
		- Pantalla DESPEDIDA
	
## Funciones
		-void gotoxy (int x, int y);
			Posiciona en pantalla
		-void AniadirFichero(char * dir, char * name, int time);
			Añadir elementos name de timpo time en documento dir y suma uno al tamaño
		-void ActualisarFichero(char * dir, char * name, char * rename, int d, int todo);
			Modifica elementos name que exista en dir
			Si le pasas rename modificara el nombre
			Si le pasas d modificara el tiempo
			para todo en 0 modificara todos y en -1 solo el primer elemento
		-void CargarFichero(Lista *lista, char * dir);
			Carga en lista los elementos del dir
		-void GuardarFichero(char * dir);
			Guarda los ficheros de la lista global reloj
		-void ListaVaciar(Lista *lista);
			Libera el espacio en memoria de la lista
		-void ListaVisualisar(Lista *lista);
			Funcion para pruebas de lista 
		-void EliminarEnLista(Lista *lista, int pos);
			Elimina elementos de la lista segun su pos
		void InsertarNodo(Lista *lista, char * dat, int tim, int sta);
			Inserta un nuevo elemento en la lista 
		void OpcionesInicio(int pos, int Eleccion);
			Solo imprime en pantalla
		void NuevoReloj();
			Imprime en pantalla y captura el nombre y timpo del nuevo reloj
		void ListaReloj(int pos);
			Imprime todos los relojes en lista
		void VaciarLista(Lista *lista);
			Imprime todos los relojes en lista
		int ListaMarcas(char * name)
			Imprime todos los marcas en lista
		void SolicitaDato(int interuptor);
			IMmrime y solicita dato q se desea modificar
		void AniadirMarca(int index);
			Añade una nueva marca del reloj con posicion index
		void EliminarMarca(int index);
			Elimina la marca con posicion index
		void EjecutaOpciones(int opcion,char * name,int index);
			Ejecutara las opciones del reloj, no la solicita la opcion se le pasa en index
		void ImprimeHora(int hora,int stado);
			Imprime el reloj y si esta parado de estarlo
		void SumaReloj();
			Recore todo los relojes sumando uno a cada reloj activo
		void Pausar();
			Se le pausara el reloj (la posicion es obtenida de la variable global)
		void PantallaError();
		void PantallaExito();
		void PantallaBinbenida();
		void PantallaDespedida();
		void Cargando();
		int OpcioneReloj();
			Imprime y retorna la opcion del reloj selecionado 
		int SeleccionReloj(char * dir);
			Imprime la lista completa del fichero, para seleccionar uno, devolvera un int apropiado


		void * Cronometrar();
			Con ciclos continuos asta q global lo indique, cada 10 se guardara el timpo actual
			y dependindo de la opcion se solo sumara el tiempo, o imprimira , o guardara o cargara datos
		void * Interfas();
			Encargada de solicitar los comandos al usuario

## Testin
	Pruebas a supera;
	
