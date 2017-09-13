# Cronometro
Obligatorio de sistema operativao

## Estructuras
- Cargo dependencias
- Declaro variavles
- Declaro Funciones
- Ejecuto main
- Redacto Funciones

## Seudo Codigo
Inicialiso variavles
	Trabajo int
	array dir con directorios
	listas
	cominso hilos o procesos



### Descripcion Hilo uno Oproceso hijo
-  Cronometraje
	- recorrera lista y sumara uno a cada estado 1
	- Minreas trabajo no sea 4 
			si 1 
			- IMPRIME OPCIONES DE INICIO
			- Imprimo en el recorido
			si 2
				Nada
			si 3
			- Actualiso listas
			si 4
			- Guardara el estado actual de las listas 
			- Finalzra del while
-  Interfase
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
				Trabajo 4

## Funciones
### Ficheros
	Actualisar ficheros
	Eliminar fichero
	Cargar fichero
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
