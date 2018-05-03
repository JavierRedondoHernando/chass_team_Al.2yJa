#define _CRT_SECURE_NO_WARNINGS

/*El menú está estructurado de la siguiente manera: 
-Primero se ejecuta el main()
-En el main() se llama a la función menu_principal(), que devuelve un código de petición del usuario
-Según dicho código se ejecuta luego en el main() la parte del switch correspondiente
-Una vez ejecutado el proceso se vuelve al menú principal a no ser que se quiera salir.
*/

#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

#define MAXJUGADORES 200
#define MAXPARTIDAS 200
#define LONGNOMBRES 12
#define LONGFECHA 20
#define SIZE 26

int menu_principal(void);
int confirmacion(char[]);
void funcionfecha(char[]);
int verif_password(char[]);
void escribir_password(char[]);

typedef struct {
	char nombre[LONGNOMBRES];
	char password[LONGNOMBRES];
	int partidas_jugadas;
	int partidas_ganadas;
	int empates_jugador;
	int puntos;
}datos_jug;

typedef struct {
	char titulo[LONGNOMBRES];
	char Nombre_jugador1[LONGNOMBRES];
	char Nombre_jugador2[LONGNOMBRES];
	char fecha_ultima[LONGFECHA];
}datos_partidas;

void main() {

	//-------------VARIABLES LOCALES----------------------

	FILE * datos;
	FILE * partidas;
	errno_t Error1, Error2;

	datos_jug jugadores[MAXJUGADORES],jugadores_en_partida[2], aux;
	datos_partidas vect_partidas[MAXPARTIDAS];
	int codigo_peticion;
	int i, j, k, booleana, num_jugador, num_partida;
	char opcioncolor, fecha[128], password_aux[LONGNOMBRES], password_aux2[LONGNOMBRES];

	//-------------------INICIO---------------------------
	SetConsoleTitle("CHESS PRO");
	system("color 0F");
	//****************************************************
	//----Cargar el programa y los ficheros de memoria----

	printf("\n\n\n\n\n\n\t\t\t\t     CHESS PRO\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nCargando \333");
	Sleep(2500);

	Error1 = fopen_s(&datos, "memoria_datos.txt", "r");
	printf("\333");
	Sleep(200);
	Error2 = fopen_s(&partidas, "memoria_partidas_guardadas.txt", "r");
	printf("\333");
	Sleep(200);
	if ((Error1 != NULL) || (Error2 != NULL)) {
		system("color 0C");
		for (i = 7; i > 0; i--) {
			system("cls");
			printf("Fallo al ejecutar el programa.\n\nFaltan los ficheros de memoria o son defectuosos.\n\n");
			printf("El programa se cerrara en %d segundos", i);
			Sleep(1000);
		}
		exit(1);
	}
	printf("\333");
	Sleep(200);
	_fcloseall();
	printf("\333\333\333");
	Sleep(400);
	system("cls");
	//---El programa ha cargado correctamente e inicia el menú--
	//**********************************************************
	do {
		for (i = 0; i < MAXJUGADORES; i++) {
			for (k = 0; k < LONGNOMBRES; k++) {
				jugadores[i].nombre[k] = '\0';
			}
			jugadores[i].partidas_jugadas = 0;
			jugadores[i].partidas_ganadas = 0;
			jugadores[i].empates_jugador = 0;
			jugadores[i].puntos = 0;
		}

		for (i = 0; i < MAXPARTIDAS; i++) {
			for (k = 0; k < LONGNOMBRES; k++) {
				vect_partidas[i].titulo[k] = '\0';
				vect_partidas[i].Nombre_jugador1[k] = '\0';
				vect_partidas[i].Nombre_jugador2[k] = '\0';
			}

			for (k = 0; k < LONGFECHA; k++) {
				vect_partidas[i].fecha_ultima[k] = '\0';
			}
		}
		for (i = 0; i < 2; i++) {
			for (k = 0; k < LONGNOMBRES; k++) {
				jugadores_en_partida[i].nombre[k] = '\0';
				jugadores_en_partida[i].password[k] = '\0';
			}
			jugadores_en_partida[i].partidas_ganadas = 0;
			jugadores_en_partida[i].partidas_jugadas = 0;
			jugadores_en_partida[i].empates_jugador = 0;
			jugadores_en_partida[i].puntos = 0;
		}
		do {
			codigo_peticion = menu_principal();
		} while (codigo_peticion == 1);

		switch (codigo_peticion) {//El código de petición se obtiene en la función menu_principal()
		case 00:
			break;
		case 11://-----------------------------------------------------
			i = 0;
			system("Cls()");
			fopen_s(&datos, "memoria_datos.txt", "r");
			while (fscanf(datos, "%s %s %d %d %d %d", jugadores[i].nombre, jugadores[i].password,
				&jugadores[i].partidas_jugadas, &jugadores[i].partidas_ganadas,
				&jugadores[i].empates_jugador, &jugadores[i].puntos) != EOF) {
				i++;
			}
			fclose(datos);
			for (k = 0; k < 2; k++, i++) {
				do {
					printf("\n\tPARTIDA NUEVA\n");
					printf("\n> Nuevos jugadores");
					printf("\n\nIntroduce el nombre del Jugador %d: ", k + 1);
					gets(jugadores_en_partida[k].nombre);
					for (j = 0; j < LONGNOMBRES; j++) {
						if (jugadores_en_partida[k].nombre[j] == ' ') {
							jugadores_en_partida[k].nombre[j] = '_';
						}
						if (j == LONGNOMBRES - 1) {
							jugadores_en_partida[k].nombre[j] = '\0';
						}
					}

					for (j = 0; j < i; j++) {
						if (strcmp(jugadores_en_partida[k].nombre, jugadores[j].nombre) == 0) {
							booleana = 0;
							break;
						}
						else {
							booleana = 1;
						}
					}
					if (booleana == 0) {
						printf("\nEl jugador que has introducido ya existe\n\n");
						system("Pause()");
						system("cls");
					}
				} while (booleana == 0);
				printf("\nIntroduce una contrase\244a para \"%s\": ", jugadores_en_partida[k].nombre);
				escribir_password(jugadores_en_partida[k].password);
				jugadores[i] = jugadores_en_partida[k];
				printf("\n\nDatos guardados correctamente\n\n");
				system("Pause()");
				system("Cls()");
			}
			fopen_s(&datos, "memoria_datos.txt", "w");
			for (j = 0; j < i; j++) {
				fprintf(datos, "%s %s %d %d %d %d\n", jugadores[j].nombre, jugadores[j].password,
					jugadores[j].partidas_jugadas, jugadores[j].partidas_ganadas,
					jugadores[j].empates_jugador, jugadores[j].puntos);
			}
			fclose(datos);
			break;
		case 12://-----------------------------------------------------
			system("cls");
			printf("\n\tPARTIDA NUEVA\n");
			printf("\n>> Seleccionar jugadores\n\n");
			i = 0;
			fopen_s(&datos, "memoria_datos.txt", "r");
			while (fscanf(datos, "%s %s %d %d %d %d", jugadores[i].nombre, jugadores[i].password,
				&jugadores[i].partidas_jugadas, &jugadores[i].partidas_ganadas,
				&jugadores[i].empates_jugador, &jugadores[i].puntos) != EOF) {
				i++;
			}
			fclose(datos);
			if (i < 2) {
				printf("\n\n\n\t\t   (No hay sufucuentes jugadores registrados)\n\n\n");
				system("Pause()");
			}
			else {
				//Ordenación del vector jugadores en orden alfabético
				for (j = 0; j < i; j++) {
					for (k = j + 1; k < i; k++) {
						if (strcmp(jugadores[j].nombre, jugadores[k].nombre) == 1) {
							aux = jugadores[j];
							jugadores[j] = jugadores[k];
							jugadores[k] = aux;
						}
					}
				}
				booleana = 1;
				do {
					for (k = 0; k < 2;k++) {
						if (booleana == 1) {
							while (1) {
								system("Cls()");
								printf("\n\tPARTIDA NUEVA\n");
								printf("\n>> Seleccionar jugadores\n\n");

								for (j = 0; j < i; j++) {
									printf("(%d) >> %s\n", j + 1, jugadores[j].nombre);
								}
								printf("\nNumero para el Jugador %d: ", k + 1);
								scanf("%d", &num_jugador);
								getchar();
								if ((num_jugador > 0) && (num_jugador < (i + 1))) {
									system("Cls()");
									printf("\n\tPARTIDA NUEVA\n\n\n>> %s\n\n", jugadores[num_jugador - 1].nombre);

									if ((k == 1) && (strcmp(jugadores_en_partida[0].nombre, jugadores[num_jugador - 1].nombre) == 0)) {
										printf("ATENCION: Este jugador ya ha sido seleccionado por el otro jugador\n\n");
										system("Pause()");
										k--;
										break;
									}
									if (verif_password(jugadores[num_jugador - 1].password) == 1) {
										strcpy(jugadores_en_partida[k].nombre, jugadores[num_jugador - 1].nombre);
										strcpy(jugadores_en_partida[k].password, jugadores[num_jugador - 1].password);
										jugadores_en_partida[k].partidas_jugadas = jugadores[num_jugador - 1].partidas_jugadas;
										jugadores_en_partida[k].partidas_ganadas = jugadores[num_jugador - 1].partidas_ganadas;
										jugadores_en_partida[k].empates_jugador = jugadores[num_jugador - 1].empates_jugador;
										jugadores_en_partida[k].puntos = jugadores[num_jugador - 1].puntos;
										system("Pause()");
										break;
									}
									else {
										if (confirmacion("volver a intentarlo") == 1) {
											booleana = 1;
											continue;
										}
										else {
											booleana = 0;
											break;
										}
									}

								}
								else {
									printf("El valor introducido no es aceptable");
								}
							}
						}
					}
					if (booleana == 1) {
						system("Cls()");
						printf("\n\tPARTIDA NUEVA\n");
						printf("\n\n\t\t\t%s   vs   %s\n\n", jugadores_en_partida[0].nombre, jugadores_en_partida[1].nombre);

						if (confirmacion("comenzar la partida con estos jugadores") == 1) {
							break;
						}
						else {
							continue;
						}
					}
					else {
						break;
					}
				} while (1);
				if (booleana == 0) {
					break;
				}

				printf("Partida\n");
				system("Pause()");

				//Ejecución de la partida aquí

			}
			break;

			break;
		case 20://-----------------------------------------------------
			system("Cls()");
			printf("\n\tPARTIDA GUARDADA\n");
			printf("\n>> Seleccionar partida\n\n");
			fopen_s(&partidas, "memoria_partidas_guardadas.txt", "r");
			i = 0;
			while (fscanf(partidas, "%s %s %s %s", vect_partidas[i].titulo, vect_partidas[i].Nombre_jugador1,
				vect_partidas[i].Nombre_jugador2, vect_partidas[i].fecha_ultima) != EOF) {
				i++;
			}
			fclose(partidas);
			if (i == 0) {
				printf("\n\n\t\t   (No hay ninguna partida guardada)\n\n");
				system("Pause()");
				break;
			}
			else {
				while (1) {
					system("Cls()");
					printf("\n\tPARTIDA GUARDADA\n");
					printf("\n>> Seleccionar partida\n\n");
					for (j = 0; j < i; j++) {
						printf("(%d) >> ", j + 1);
						for (k = 0; k < LONGNOMBRES; k++) {
							printf("%c", vect_partidas[j].titulo[k]);
						}
						printf(" - ");
						for (k = 0; k < LONGNOMBRES; k++) {
							printf("%c", vect_partidas[j].Nombre_jugador1[k]);
						}
						printf(" vs ");
						for (k = 0; k < LONGNOMBRES; k++) {
							printf("%c", vect_partidas[j].Nombre_jugador2[k]);
						}
						printf(" - ");
						for (k = 0; k < LONGFECHA; k++) {
							printf("%c", vect_partidas[j].fecha_ultima[k]);
						}
						printf("\n");
					}
					printf("\n\nNumero de la partida: ");
					scanf("%d", &num_partida);
					if ((num_partida > 0) && (num_partida < (i + 1))) {
						system("Cls()");
						printf("\n\tPARTIDA GUARDADA\n\n >> ");
						printf("%s %s vs %s %s", vect_partidas[num_partida - 1].titulo,
							vect_partidas[num_partida - 1].Nombre_jugador1,
							vect_partidas[num_partida - 1].Nombre_jugador2,
							vect_partidas[num_partida - 1].fecha_ultima);
						printf("\n\nPara iniciar esta partida primero deben iniciarse los jugadores.\n\n\n");
						system("Pause()");
						break;
					}
					else {
						printf("\nEl valor introducido no es aceptable\n\n");
						system("Pause()");
						break;
					}
				}

			}
			break;
		case 30://-----------------------------------------------------
			i = 0;
			fopen_s(&datos, "memoria_datos.txt", "r");
			printf("  NOMBRE      PARTIDAS JUGADAS    PARTIDAS GANADAS     EMPATES    PUNTOS\n\n");
			while (fscanf(datos, "%s %s %d %d %d %d", jugadores[i].nombre, jugadores[i].password,
				&jugadores[i].partidas_jugadas, &jugadores[i].partidas_ganadas,
				&jugadores[i].empates_jugador, &jugadores[i].puntos) != EOF) {
				i++;
			}
			if (i == 0) {
				printf("\n\t\t   (No hay ningun jugador registrado)\n");
			}
			else {
				//Ordenación del vector jugadores de mayor a menor puntuación
				for (j = 0; j < MAXJUGADORES; j++) {
					for (k = j + 1; k < MAXJUGADORES; k++) {
						if (jugadores[j].puntos < jugadores[k].puntos) {
							aux = jugadores[j];
							jugadores[j] = jugadores[k];
							jugadores[k] = aux;
						}
					}
				}
				for (j = 0; j < i; j++) {
					printf("> ");
					for (k = 0; k < LONGNOMBRES; k++) {
						printf("%c", jugadores[j].nombre[k]);
					}
					printf("\t    %d\t\t\t %d\t\t  %d\t    %d \n", jugadores[j].partidas_jugadas,
						jugadores[j].partidas_ganadas, jugadores[j].empates_jugador, jugadores[j].puntos);
				}
			}
			printf("\n\n");
			system("Pause()");
			fclose(datos);
			break;
		case 411://----------------------------------------------------
			system("cls");
			printf("\n\tCONFIGURACION\n\n");
			printf("\n>> Modificar la contrase\244a de un jugador");
			i = 0;
			fopen_s(&datos, "memoria_datos.txt", "r");
			while (fscanf(datos, "%s %s %d %d %d %d", jugadores[i].nombre, jugadores[i].password,
				&jugadores[i].partidas_jugadas, &jugadores[i].partidas_ganadas,
				&jugadores[i].empates_jugador, &jugadores[i].puntos) != EOF) {
				i++;
			}
			fclose(datos);
			if (i == 0) {
				printf("\n\n\n\t\t   (No hay ningun jugador registrado)\n\n\n");
				system("Pause()");
			}
			else {
				//Ordenación del vector jugadores en orden alfabético
				for (j = 0; j < i; j++) {
					for (k = j + 1; k < i; k++) {
						if (strcmp(jugadores[j].nombre, jugadores[k].nombre) == 1) {
							aux = jugadores[j];
							jugadores[j] = jugadores[k];
							jugadores[k] = aux;
						}
					}
				}
				do {
					printf("\n\nSeleccione el numero del jugador a modificar");
					printf("\t(Ordenado Alfabeticamente)\n\n");
					for (j = 0; j < i; j++) {
						printf("(%d) >> ", j + 1);
						for (k = 0; k < LONGNOMBRES; k++) {
							printf("%c", jugadores[j].nombre[k]);
						}
						printf("\n");
					}
					printf("\nNumero jugador: ");
					scanf("%d", &num_jugador);
					getchar();
					if ((num_jugador > 0) && (num_jugador < i+1)) {
						system("cls");
						printf("\n\tCONFIGURACION\n\n");
						printf("\n>> %s\n", jugadores[num_jugador - 1].nombre);
						if (verif_password(jugadores[num_jugador - 1].password) == 1) {
							printf("---------------------------------------\n\nIntroduzca nueva contrase\244a (maximo %d caracteres): ",
								LONGNOMBRES);
							escribir_password(password_aux);
							printf("\n\nVuelva a escribir la contrase\244a para confirmar: ");
							escribir_password(password_aux2);

							if (strcmp(password_aux, password_aux2) == 0) {
								strcpy(jugadores[num_jugador - 1].password, password_aux);
								fopen_s(&datos, "memoria_datos.txt", "w");
								for (j = 0; j < i; j++) {
									fprintf(datos, "%s %s %d %d %d %d\n", jugadores[j].nombre, jugadores[j].password,
										jugadores[j].partidas_jugadas, jugadores[j].partidas_ganadas,
										jugadores[j].empates_jugador, jugadores[j].puntos);

								}
								fclose(datos);
								printf("\n\nSu nueva contrase\244a para \" %s \" se ha guardado correctamente\n\n",
									jugadores[num_jugador - 1].nombre);
								system("Pause()");
								break;
							}
							else {
								printf("\nLas dos contrase\244as no coinciden\n\n");
							}
						}
					}
					else {
						printf("\nEl valor introducido no es aceptable\n\n");
					}
				} while (confirmacion("volver a intentarlo") == 1);
			}
			break;
		case 412://----------------------------------------------------
			i = 0;
			fopen_s(&datos, "memoria_datos.txt", "r");
			while (fscanf(datos, "%s %s %d %d %d %d", jugadores[i].nombre, jugadores[i].password,
				&jugadores[i].partidas_jugadas, &jugadores[i].partidas_ganadas,
				&jugadores[i].empates_jugador, &jugadores[i].puntos) != EOF) {
				i++;
			}
			fclose(datos);
			do {
				system("cls");
				printf("\n\tCONFIGURACION\n\n");
				printf(">> Crear nuevo jugador\n\n");
				printf("\nIntroduce el nombre del Jugador: ");
				gets(jugadores[i].nombre);
				for (j = 0; j < LONGNOMBRES; j++) {
					if (jugadores[i].nombre[j] == ' ') {
						jugadores[i].nombre[j] = '_';
					}
					if (j == LONGNOMBRES - 1) {
						jugadores[i].nombre[j] = '\0';
					}
				}

				for (j = 0; j < i; j++) {
					if (strcmp(jugadores[i].nombre, jugadores[j].nombre) == 0) {
						booleana = 0;
						break;
					}
					else {
						booleana = 1;
					}
				}
				if (booleana == 0) {
					printf("\nEl jugador que has introducido ya existe\n\n");
					system("Pause()");
					system("cls");
				}
			} while (booleana == 0);
			printf("\nIntroduce una contrase\244a para \"%s\": ", jugadores[i].nombre);
			escribir_password(jugadores[i].password);

			fopen_s(&datos, "memoria_datos.txt", "w");
			for (j = 0; j <= i; j++) {
				fprintf(datos, "%s %s %d %d %d %d\n", jugadores[j].nombre, jugadores[j].password,
					jugadores[j].partidas_jugadas, jugadores[j].partidas_ganadas,
					jugadores[j].empates_jugador, jugadores[j].puntos);
			}
			fclose(datos);
			printf("\n\nDatos guardados correctamente\n\n");
			system("Pause()");
			system("Cls()");
			break;
		case 413://----------------------------------------------------
			system("cls");
			printf("\n\tCONFIGURACION\n\n");
			printf("\n>> Borrar un jugador");
			i = 0;
			fopen_s(&datos, "memoria_datos.txt", "r");
			while (fscanf(datos, "%s %s %d %d %d %d", jugadores[i].nombre, jugadores[i].password,
				&jugadores[i].partidas_jugadas, &jugadores[i].partidas_ganadas,
				&jugadores[i].empates_jugador, &jugadores[i].puntos) != EOF) {
				i++;
			}
			fclose(datos);
			if (i == 0) {
				printf("\n\n\n\t\t   (No hay ningun jugador registrado)\n\n\n");
				system("Pause()");
			}
			else {
				//Ordenación del vector jugadores en orden alfabético
				for (j = 0; j < i; j++) {
					for (k = j + 1; k < i; k++) {
						if (strcmp(jugadores[j].nombre, jugadores[k].nombre) == 1) {
							aux = jugadores[j];
							jugadores[j] = jugadores[k];
							jugadores[k] = aux;
						}
					}
				}
				do {
					system("cls");
					printf("\n\tCONFIGURACION\n\n");
					printf("\n>> Borrar un jugador");
					printf("\n\nSeleccione el numero del jugador que deseas borrar");
					printf("    (Ordenado Alfabeticamente)\n");
					for (j = 0; j < i; j++) {
						printf(" (%d) >> ", j + 1);
						printf("%s", jugadores[j].nombre);
						printf("\n");
					}
					printf("\nNumero de jugador: ");
					scanf("%d", &num_jugador);
					getchar();
					if ((num_jugador > 0) && (num_jugador < i+1)) {
						system("cls");
						printf("\n\tCONFIGURACION\n\n");
						printf("\n>> %s\n", jugadores[num_jugador - 1].nombre);
						if (verif_password(jugadores[num_jugador - 1].password) == 1) {
							fopen_s(&datos, "memoria_datos.txt", "w");
							for (j = 0; j < i; j++) {
								if (j != (num_jugador - 1)) {
									fprintf(datos, "%s %s %d %d %d %d\n", jugadores[j].nombre, jugadores[j].password,
										jugadores[j].partidas_jugadas, jugadores[j].partidas_ganadas,
										jugadores[j].empates_jugador, jugadores[j].puntos);
								}
							}
							fclose(datos);
							printf("\nEl jugador que ha seleccionado ha sido borrado correctamente\n\n");
							system("Pause()");
							break;
						}
						else {
							printf("\nLas dos contrase\244as no coinciden\n\n");
						}
					}
					else {
						system("cls()");
						printf("\nEl valor introducido no es aceptable\n\n");
					}
				} while (confirmacion("volver a intentarlo") == 1);
			}
			break;
		case 421://----------------------------------------------------
			system("cls");
			printf("\n\tCONFIGURACION\n\n");
			printf("\n>> Partidas guardadas");
			funcionfecha(fecha);
			printf("\n\t\t\t\t\tFecha actual: %s\n\n", fecha);

			fopen_s(&partidas, "memoria_partidas_guardadas.txt", "r");
			i = 0;
			while (fscanf(partidas, "%s %s %s %s", vect_partidas[i].titulo, vect_partidas[i].Nombre_jugador1,
				vect_partidas[i].Nombre_jugador2, vect_partidas[i].fecha_ultima) != EOF) {
				printf("> ");
				for (k = 0; k < LONGNOMBRES; k++) {
					printf("%c", vect_partidas[i].titulo[k]);
				}
				printf(" - ");
				for (k = 0; k < LONGNOMBRES; k++) {
					printf("%c", vect_partidas[i].Nombre_jugador1[k]);
				}
				printf(" vs ");
				for (k = 0; k < LONGNOMBRES; k++) {
					printf("%c", vect_partidas[i].Nombre_jugador2[k]);
				}
				printf(" - ");
				for (k = 0; k < LONGFECHA; k++) {
					printf("%c", vect_partidas[i].fecha_ultima[k]);
				}
				printf("\n");
				i++;
			}
			if (i == 0) {
				printf("\n\n\t\t   (No hay ninguna partida guardada)\n\n");
			}
			printf("\n\n");
			system("Pause()");
			fclose(partidas);
			getchar();
			break;
		case 422://----------------------------------------------------
			break;
		case 423://----------------------------------------------------
			system("cls");
			printf("\n\tCONFIGURACION\n\n");
			printf("\n>> Partidas guardadas\n\n");
			if (confirmacion("eliminar TODAS LAS PARTIDAS guardadas") == 1) {
				printf("\n\tCONFIGURACION\n\n");
				printf("\n>> Partidas guardadas\n\n");
				printf("Si elimina todas las partidas no se podran recuperar.\n");
				if (confirmacion("eliminarlas de todos modos") == 1) {
					remove("memoria_partidas_guardadas.txt");
					fopen_s(&partidas, "memoria_partidas_guardadas.txt", "w");
					fclose(partidas);
					printf("\n\tCONFIGURACION\n\n");
					printf("\nSe han eliminado todas las partidas guardadas\n\n");
					system("Pause()");
					break;
				}
			}
			printf("No se ha eliminado ninguan partida\n\n");
			system("Pause()");
			break;
		case 431://----------------------------------------------------
			do {
				system("cls");
				printf("\n\tCONFIGURACION\n\n");
				printf("\n>> Cambiar colores de pantalla");
				printf("\n\n Elija entre los siguientes modos preestablecidos\n\n\t(1) >> NEGRO[Fondo]/BLANCO BRILLANTE[Letra]");
				printf("\n\n\t(2) >> NEGRO[Fondo]/GRIS[Letra]\n\n\t(3) >> AZUL[Fondo]/BLANCO BRILLANTE[Letra]");
				printf("\n\n\t(4) >> VERDE[Fondo]/AMARILLO[Letra]\n\n\t(0) >> Volver al menu principal\n\nOpcion: ");
				scanf("%c", &opcioncolor);
				switch (opcioncolor) {
				case '1':
					system("color 0F");
					break;
				case '2':
					system("color 07");
					break;
				case '3':
					system("color 1F");
					break;
				case '4':
					system("color 2B");
				case '0':
					break;
				default:
					if ((opcioncolor != '\n') && (opcioncolor != '\0')) {
						printf("\n\nOpcion incorrecta.\n\n");
						system("Pause()");
					}
					break;
				}
			} while (opcioncolor != '0');
			getchar();
			break;

			
		}
	}while (codigo_peticion != 00);
}

//----------------------FUNCIONES SECUNDARIAS-----------------------
//******************************************************************


//MENÚS--------**********

int menu_principal(void) {

	char peticion;

	/*
	CÓDIGOS PETICIÓN
	-00 : SALIR DEL PROGRAMA
	-01 : VOLVER AL MENU PRINCIPAL
	-11 : CREAR NUEVOS JUGADORES Y JUGAR
	-12 : SELECCIONAR JUGADORES EXISTENTE Y JUGAR
	20 : SELECCIONAR PARTIDA GUARDADA Y JUGAR
	-30 : VISUALIZAR PUNTUACIONES
	-411: MODIFICAR LA CONTRASEÑA DE UN JUGADOR
	-412: CREAR UN NUEVO JUGADOR
	-413: BORRAR JUGADOR****(está incompleta)
	-421: VER LAS PARTIDAS GUARDADAS
	422: BORRAR UNA PARTIDA
	-423: BORRAR TODAS LAS PARTIDAS
	-431: CAMBIAR COLORES DE LA PANTALLA

	*/
	
	system("Cls()");
	printf("\n\tCHESS PRO\n\n\n");
	printf("      MENU PRINCIPAL \n___________________________\n");
	printf("\n\t(1) >> PARTIDA NUEVA\n\n\t(2) >> PARTIDA GUARDADA\n\n\t(3) >> PUNTUACIONES");
	printf("\n\n\t(4) >> CONFIGURACION\n\n\t(0) >> SALIR\n\n\nOpcion: ");

	scanf("%c", &peticion);
	/*La petición, aunque sea un número, lo trato como caracter por si el usuario introduce erróneamente
	una letra en vez de un número, para que no se atasque el programa*/
	
	system("Cls()");

	switch (peticion) {
	case '1'://--------------------PARTIDA NUEVA-----------------
		getchar();
		do {
			printf("\n\tPARTIDA NUEVA\n");
			printf("\n\n\t(1) >> Nuevos jugadores\n\n\t(2) >> Seleccionar jugadores\n\n\t(0) >> Volver al menu principal\n\nOpcion: ");
			scanf("%c", &peticion);

			switch (peticion) {
			case '1':
				getchar();
				return 11;
				break;
			case '2':
				getchar();
				return 12;
				break;
			case '0':
				getchar();
				return 01;
				break;
			default:
				if ((peticion != '\n') && (peticion != '\0')) {
					printf("\n\nOpcion incorrecta.\n\n");
					system("Pause()");
					system("Cls()");
				}
			}
		} while (1);
		break;

	case '2'://------------------PARTIDA GUARDADA----------------
		getchar();
		printf("\n\tPARTIDA GUARDADA\n\n\n");
		return 20;
		
		break;
	case '3'://--------------------PUNTUACIONES------------------
		getchar();
		printf("\n\tPUNTUACIONES\n\n\n");
		return 30;
		break;
	case '4'://-------------------CONFIGURACIÓN------------------
		getchar();
		do {
			system("cls");
			printf("\n\tCONFIGURACION\n");
			printf("\n\n\t(1) >> Jugadores\n\n\t(2) >> Partidas");
			printf("\n\n\t(3) >> Pantalla \n\n\t(0) >> Volver al menu principal\n\nOpcion: ");
			scanf("%c", &peticion);
			
			switch (peticion) {
			case '1':
				do {
					system("cls");
					printf("\n\tCONFIGURACION\n\n");
					printf(">> Jugadores\n\n");
					printf("\n\t(1) >> Modificar la contrase\244a de un jugador\n\n\t(2) >> Crear nuevo jugador");
					printf("\n\n\t(3) >> Borrar jugador\n\n\t(0) >> Volver al menu principal\n\nOpcion: ");
					scanf("%c", &peticion);
					switch (peticion) {
					case '1':
						getchar();
						return 411;
						break;
					case '2':
						getchar();
						return 412;
						break;
					case '3':
						getchar();
						return 413;
						break;
					case '0':
						getchar();
						return 01;
						break;
					default:
						if ((peticion != '\n') && (peticion != '\0')) {
							printf("\n\nOpcion incorrecta.\n\n");
							system("Pause()");
							system("Cls()");
						}
					}
				} while (1);
				break;
			case '2':
				do {
					system("cls");
					printf("\n\tCONFIGURACION\n\n");
					printf(">> Partidas\n\n");
					printf("\n\t(1) >> Ver las partidas guardadas\n\n\t(2) >> Borrar una partida");
					printf("\n\n\t(3) >> Borrar todas las partidas\n\n\t(0) >> Volver al menu principal\n\nOpcion: ");
					scanf("%c", &peticion);
					switch (peticion) {
					case '1':
						return 421;
						break;
					case '2':
						return 422;
						break;
					case '3':
						getchar();
						return 423;
						break;
					case '0':
						getchar();
						return 01;
						break;
					default:
						if ((peticion != '\n') && (peticion != '\0')) {
							printf("\n\nOpcion incorrecta.\n\n");
							system("Pause()");
							system("Cls()");
						}
					}
				} while (1);
			
				break;
			case '3':
				do {
					system("cls");
					printf("\n\tCONFIGURACION\n\n");
					printf("\n>> Pantalla\n\n");
					printf("\n\t(1) >> Cambiar colores de pantalla\n\n\t(0) >> Volver al menu principal\n\nOpcion: ");
					scanf("%c", &peticion);
					switch (peticion) {
					case '1':
						return 431;
						break;
					case '0':
						getchar();
						return 01;
						break;
					default:
						if ((peticion != '\n') && (peticion != '\0')) {
							printf("\n\nOpcion incorrecta.\n\n");
							system("Pause()");
							system("Cls()");
						}
					}
				} while (1);
				break;
			case '0':
				getchar();
				return 01;
				break;
			default:
				if ((peticion != '\n') && (peticion != '\0')) {
					printf("\n\nOpcion incorrecta.\n\n");
					system("Pause()");
					system("Cls()");
				}
			}
		} while (1);
		break;
	case '0'://-----------------------SALIR----------------------
		getchar();
		printf("\n\tSALIR\n\n\n");
		if (confirmacion("salir de CHESS PRO") == 1) {
			return 00;
		}
		else {
			return 01;
		}
		break;
	default://-----------------------DEFAULT---------------------
		if ((peticion != '\n') && (peticion != '\0')) {
			getchar();
			printf("\n\nOpcion incorrecta.\n\n");
			system("Pause()");
		}
		return 01;
	}
}

int confirmacion(char cadena[]) {

	char opcion;
	do {
		printf("¿Quiere %s?\n\n\n\t(1) >> SI\n\n\t(0) >> NO\n\nOpcion: ", cadena);
		scanf_s("%c", &opcion, 1);

		switch (opcion) {
		case '1':
			getchar();
			system("Cls()");
			return 1;
			break;
		case '0':
			getchar();
			return 0;
		default:
			if ((opcion != '\n') && (opcion != '\0')) {
				printf("\n\nOpcion incorrecta.\n\n");
				system("Pause()");
			}
		}
	} while (1);
}
//FÍN MENÚS----**********

void funcionfecha(char cadena[]) { 
	time_t tiempo = time(0); 
	struct tm *tlocal = localtime(&tiempo); 
	char output[128]; 

	strftime(output, 128, "%d/%m/%y_%H:%M:%S", tlocal);  
	strcpy(cadena, output);
}

int verif_password(char password[]) {

	char password_aux[LONGNOMBRES];

	printf("\nIntroduzca la Contrase\244a: ");
	escribir_password(password_aux);
	if ((strcmp(password, password_aux) == 0)) {
		printf("\n\nContrase\244a correcta\n\n");
		return 1;
	}
	else {
		printf("\n\n----------------------------------------------------");
		printf("\a\n\nLa contrase\244a es incorrecta.\n\n");
		system("Pause()");
		system("cls");
		return 0;
	}
}

void escribir_password(char password_aux[]) {
	int j=0;
	
	do {	//Este paso permite no hacer visible la contraseña.
		password_aux[j] = _getche();
		if (password_aux[j] == '\b') {
			if (j > 0) {
				password_aux[j - 1] = '\0';
				password_aux[j] = '\0';
				printf(" ");
				printf("\b");
				j--;
			}
			else
				printf(" ");
			password_aux[j] = '\0';
			continue;
		}
		else if (password_aux[j] == '\r') {
			j++;
		}
		else {
			j++;
			printf("\b*");
		}

	} while (password_aux[j - 1] != '\r');
	password_aux[j - 1] = '\0';
}
