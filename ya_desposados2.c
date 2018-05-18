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
#include <math.h>

//constantes para el menu

#define MAXJUGADORES 200
#define MAXPARTIDAS 200
#define LONGNOMBRES 12
#define LONGFECHA 20
#define DIM_MATRIX 8
#define SIZE 26

//constantes para el ajedrez
#define DIM 10
#define MAX_PIEZAS 10

int menu_principal(void);
int confirmacion(char[]);
int verif_password(char[]);
int tiempo_actual_a_minutos();
void funcionfecha(char[]);
void setup_datos(struct datos_jug* jugador);
void setup_partidas(struct datos_partidas* vect_partidas);

//prototipos de las funciones del ajedrez
void ajedrez();
void pedir_destino(int *columna_aux, int *fila_aux);
int revision_peon(int tablero[DIM][DIM], int fila, int columna, int fila_aux, int columna_aux);
int revision_peon_n(int tablero[DIM][DIM], int fila, int columna, int fila_aux, int columna_aux);
int revision_caballo(int tablero[DIM][DIM], int fila, int columna, int fila_aux, int columna_aux, int valor);
int revision_alfil(int tablero[DIM][DIM], int fila, int columna, int fila_aux, int columna_aux, int valor);
int revision_torre(int tablero[DIM][DIM], int fila, int columna, int fila_aux, int columna_aux, int valor);
int revision_reina(int tablero[DIM][DIM], int fila, int columna, int fila_aux, int columna_aux, int valor);
int revision_rey(int tablero[DIM][DIM], int fila, int columna, int fila_aux, int columna_aux, int valor);
int caen_en_el_mismo_sitio(struct pieza *pieza);
void imprimir_tablero(char tablero_color[DIM][DIM], int tablero_piezas[DIM][DIM]);
void pieza_capturada(int tablero[DIM][DIM], struct todas *piezas, struct pieza *pieza, int fila_aux, int columna_aux);
void coronar(int tablero[DIM][DIM], struct todas *pieza);
int check(int tablero[DIM][DIM], struct todas *pieza, int turno);



struct datos_jug {
	char nombre[LONGNOMBRES];
	char password[LONGNOMBRES];
	int partidas_jugadas;
	int minutos_jugados;
};

struct datos_partidas {
	char titulo[LONGNOMBRES];
	char Nombre_jugador1[LONGNOMBRES];
	char Nombre_jugador2[LONGNOMBRES];
	char fecha_ultima[LONGFECHA];
	int matriz_partida[DIM_MATRIX][DIM_MATRIX];
};

//a partir de aqui son las estructuras para las piezas del ajedrez

struct pieza {
	int fila;
	int columna;
	int revisar;
	int capturada;
	int valor;
};

struct todas {
	struct pieza peon[MAX_PIEZAS];
	struct pieza alfil[MAX_PIEZAS];
	struct pieza torre[MAX_PIEZAS];
	struct pieza caballo[MAX_PIEZAS];
	struct pieza reina[MAX_PIEZAS];
	struct pieza rey;
	struct pieza peon_n[MAX_PIEZAS];
	struct pieza alfil_n[MAX_PIEZAS];
	struct pieza torre_n[MAX_PIEZAS];
	struct pieza caballo_n[MAX_PIEZAS];
	struct pieza reina_n[MAX_PIEZAS];
	struct pieza rey_n;
};

void main() {

	//-------------VARIABLES LOCALES----------------------

	FILE * datos;
	FILE * partidas;
	errno_t Error1, Error2;

	struct datos_jug jugadores[MAXJUGADORES],jugadores_en_partida[2], aux;
	struct datos_partidas vect_partidas[MAXPARTIDAS];

	int codigo_peticion;
	int i, j, k, booleana, num_jugador, num_partida, tiempo_inicio;
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
			setup_datos(&jugadores[i]);
		}
		for (i = 0; i < 2; i++) {
			setup_datos(&jugadores_en_partida[i]);
		}
		for (i = 0; i < MAXPARTIDAS; i++) {
			setup_partidas(&vect_partidas[i]);
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
			while (fscanf(datos, "%s %s %d %d", jugadores[i].nombre, jugadores[i].password,
				&jugadores[i].partidas_jugadas, &jugadores[i].minutos_jugados) != EOF) {
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
				printf("\nIntroduce una contrase\244a para \"%s\" (sin espacios): ", jugadores_en_partida[k].nombre);
				gets(jugadores_en_partida[k].password);
				jugadores_en_partida[k].partidas_jugadas = 0;
				jugadores_en_partida[k].minutos_jugados = 0;
				jugadores[i] = jugadores_en_partida[k];
				printf("\n\nDatos guardados correctamente\n\n");
				system("Pause()");
				system("Cls()");
			}
			fopen_s(&datos, "memoria_datos.txt", "w");
			for (j = 0; j < i; j++) {
				fprintf(datos, "%s %s %d %d \n", jugadores[j].nombre, jugadores[j].password,
					jugadores[j].partidas_jugadas, jugadores[j].minutos_jugados);
			}
			fclose(datos);
			ajedrez();
			break;
		case 12://-----------------------------------------------------
			system("cls");
			printf("\n\tPARTIDA NUEVA\n");
			printf("\n>> Seleccionar jugadores\n\n");
			i = 0;
			fopen_s(&datos, "memoria_datos.txt", "r");
			while (fscanf(datos, "%s %s %d %d", jugadores[i].nombre, jugadores[i].password,
				&jugadores[i].partidas_jugadas, &jugadores[i].minutos_jugados) != EOF) {
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
										jugadores_en_partida[k].minutos_jugados = jugadores[num_jugador - 1].minutos_jugados;
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
			
				tiempo_inicio = tiempo_actual_a_minutos();
				ajedrez();
				system("Pause()");
				//Ejecución de la partida aquí

				for (j = 0; j < 2; j++) {
					jugadores_en_partida[j].minutos_jugados = jugadores_en_partida[j].minutos_jugados+(tiempo_actual_a_minutos() - tiempo_inicio);
				}
				for (k = 0; k < MAXJUGADORES; k++) {
					for (j = 0; j < 2; j++) {
						if (strcmp(jugadores[k].nombre, jugadores_en_partida[j].nombre) == 0) {
							jugadores[k].minutos_jugados = jugadores_en_partida[j].minutos_jugados;
							jugadores[k].partidas_jugadas++;
						}
					}
				}
				fopen_s(&datos, "memoria_datos.txt", "w");
				for(j=0;j<i;j++){
					fprintf(datos, "%s %s %d %d\n", jugadores[j].nombre, jugadores[j].password,
						jugadores[j].partidas_jugadas, jugadores[j].minutos_jugados);
				}
				fclose(datos);
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
				for (k = 0; k < DIM_MATRIX; k++) {
					fscanf(partidas, "%d %d %d %d %d %d %d %d", &vect_partidas[i].matriz_partida[k][0],
						&vect_partidas[i].matriz_partida[k][1], &vect_partidas[i].matriz_partida[k][2],
						&vect_partidas[i].matriz_partida[k][3], &vect_partidas[i].matriz_partida[k][4],
						&vect_partidas[i].matriz_partida[k][5], &vect_partidas[i].matriz_partida[k][6],
						&vect_partidas[i].matriz_partida[k][7]);
				}
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
						getchar();
						system("cls");
						printf("\n\tPARTIDA GUARDADA\n\n");
						if (confirmacion("vovler a intentarlo") == 1) {
							continue;
						}
						else {
							break;
						}
					}
				}

			}
			break;
		case 30://-----------------------------------------------------
			i = 0;
			fopen_s(&datos, "memoria_datos.txt", "r");
			printf("  NOMBRE      PARTIDAS JUGADAS    MINUTOS JUGADOS\n\n");
			while (fscanf(datos, "%s %s %d %d ", jugadores[i].nombre, jugadores[i].password,
				&jugadores[i].partidas_jugadas, &jugadores[i].minutos_jugados) != EOF) {
				i++;
			}
			if (i == 0) {
				printf("\n\t\t   (No hay ningun jugador registrado)\n");
			}
			else {
				//Ordenación del vector jugadores de más a menos minutos jugados
				for (j = 0; j < MAXJUGADORES; j++) {
					for (k = j + 1; k < MAXJUGADORES; k++) {
						if (jugadores[j].minutos_jugados < jugadores[k].minutos_jugados) {
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
					printf("\t    %d\t\t\t   %d\n", jugadores[j].partidas_jugadas,
						jugadores[j].minutos_jugados);
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
			while (fscanf(datos, "%s %s %d %d", jugadores[i].nombre, jugadores[i].password,
				&jugadores[i].partidas_jugadas, &jugadores[i].minutos_jugados) != EOF) {
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
					printf("\n>> Modificar la contrase\244a de un jugador");
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
							printf("---------------------------------------");
							printf("\n\nIntroduzca nueva contrase\244a(maximo %d caracteres y sin espacios) : ",
								LONGNOMBRES);
							gets(password_aux);
							printf("\n\nVuelva a escribir la contrase\244a para confirmar: ");
							gets(password_aux2);

							if (strcmp(password_aux, password_aux2) == 0) {
								strcpy(jugadores[num_jugador - 1].password, password_aux);
								fopen_s(&datos, "memoria_datos.txt", "w");
								for (j = 0; j < i; j++) {
									fprintf(datos, "%s %s %d %d\n", jugadores[j].nombre, jugadores[j].password,
										jugadores[j].partidas_jugadas, jugadores[j].minutos_jugados);

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
			while (fscanf(datos, "%s %s %d %d ", jugadores[i].nombre, jugadores[i].password,
				&jugadores[i].partidas_jugadas, &jugadores[i].minutos_jugados) != EOF) {
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
			gets(jugadores[i].password);

			fopen_s(&datos, "memoria_datos.txt", "w");
			for (j = 0; j <= i; j++) {
				fprintf(datos, "%s %s %d %d\n", jugadores[j].nombre, jugadores[j].password,
					jugadores[j].partidas_jugadas, jugadores[j].minutos_jugados);
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
			while (fscanf(datos, "%s %s %d %d", jugadores[i].nombre, jugadores[i].password,
				&jugadores[i].partidas_jugadas, &jugadores[i].minutos_jugados) != EOF) {
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
									fprintf(datos, "%s %s %d %d\n", jugadores[j].nombre, jugadores[j].password,
										jugadores[j].partidas_jugadas, jugadores[j].minutos_jugados);
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
			do {
				system("cls");
				printf("\n\tCONFIGURACION\n\n");
				printf("\n>> Borrar partida guardada");
				funcionfecha(fecha);
				printf("\n\t\t\t\t\tFecha actual: %s\n\n", fecha);

				fopen_s(&partidas, "memoria_partidas_guardadas.txt", "r");
				i = 0;
				while (fscanf(partidas, "%s %s %s %s", vect_partidas[i].titulo, vect_partidas[i].Nombre_jugador1,
					vect_partidas[i].Nombre_jugador2, vect_partidas[i].fecha_ultima) != EOF) {
					for (k = 0; k < DIM_MATRIX; k++) {
						fscanf(partidas, "%d %d %d %d %d %d %d %d", &vect_partidas[i].matriz_partida[k][0],
							&vect_partidas[i].matriz_partida[k][1], &vect_partidas[i].matriz_partida[k][2],
							&vect_partidas[i].matriz_partida[k][3], &vect_partidas[i].matriz_partida[k][4],
							&vect_partidas[i].matriz_partida[k][5], &vect_partidas[i].matriz_partida[k][6],
							&vect_partidas[i].matriz_partida[k][7]);
					}
					printf("(%d) >> ",i+1);
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
				fclose(partidas);
				if (i == 0) {
					printf("\n\n\t\t   (No hay ninguna partida guardada)\n\n");
					printf("\n\n");
					system("Pause()");
					getchar();
				}
				else {
					printf("\n\nNumero de partida que quieres borrar: ");
					scanf_s("%d", &num_partida);
					getchar();
					if ((num_partida > 0) && (num_partida < i + 1)) {
						fopen_s(&partidas, "memoria_partidas_guardadas.txt", "w");
						for (j = 0; j < i; j++) {
							if (j != (num_partida - 1)) {
								fprintf(partidas, "%s %s %s %s\n", vect_partidas[j].titulo, vect_partidas[j].Nombre_jugador1,
									vect_partidas[j].Nombre_jugador2, vect_partidas[j].fecha_ultima);
								for (k = 0; k < DIM_MATRIX; k++) {
									fprintf(partidas, "%d %d %d %d %d %d %d %d\n", vect_partidas[j].matriz_partida[k][0],
										vect_partidas[j].matriz_partida[k][1], vect_partidas[j].matriz_partida[k][2],
										vect_partidas[j].matriz_partida[k][3], vect_partidas[j].matriz_partida[k][4],
										vect_partidas[j].matriz_partida[k][5], vect_partidas[j].matriz_partida[k][6],
										vect_partidas[j].matriz_partida[k][7]);
								}
							}
						}
						fclose(partidas);
						printf("\nLa partida numero %d ha sido borrada con exito\n\n",num_partida);
						system("Pause()");
						break;
					}
					else {
						printf("\nEl valor introducido no es aceptable\n\n");
					}
				}
			} while (confirmacion("volver a intentarlo") == 1);
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
	-20 : SELECCIONAR PARTIDA GUARDADA Y JUGAR
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
		printf("\n\DATOS DE LOS JUGADORES\n\n\n");
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
				getchar();
				system("Pause()");
				system("Cls()");
				printf("\n\tNUEVA OPCION\n\n\n");
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
	gets(password_aux);
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


int tiempo_actual_a_minutos() {

	char matriz_tiempos[3][128];
	int i, j, k, vect_tiempo[3], long_num, tiempo_en_min;

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 128; j++) {
			matriz_tiempos[i][j] = '\0';
		}
		vect_tiempo[i] = 0;
	}

	time_t tiempo = time(0);
	struct tm *tlocal = localtime(&tiempo);
	char output[128];
	strftime(matriz_tiempos[0], 128, "%H", tlocal);
	strftime(matriz_tiempos[1], 128, "%M", tlocal);
	strftime(matriz_tiempos[2], 128, "%S", tlocal);

	for (k = 0; k < 3; k++) {
		long_num = strlen(matriz_tiempos[k]);
		for (i = 0; i < long_num; i++) {
			vect_tiempo[k] = vect_tiempo[k] + ((int)(matriz_tiempos[k][i] - '0')*(pow(10, long_num - i - 1)));
		}
	}

	tiempo_en_min = ((vect_tiempo[0] * 60) + vect_tiempo[1] + ((int)vect_tiempo[2] / 60));
	return tiempo_en_min;
}

void setup_datos(struct datos_jug* jugador) {
	int i, k;

	for (k = 0; k < LONGNOMBRES; k++) {
		jugador->nombre[k] = '\0';
		jugador->password[k] = '\0';
	}
	jugador->partidas_jugadas = 0;
	jugador->minutos_jugados = 0;
}

void setup_partidas(struct datos_partidas* vect_partidas) {
	int k;

	for (k = 0; k < LONGNOMBRES; k++) {
		vect_partidas->titulo[k] = '\0';
		vect_partidas->Nombre_jugador1[k] = '\0';
		vect_partidas->Nombre_jugador2[k] = '\0';
	}

	for (k = 0; k < LONGFECHA; k++) {
		vect_partidas->fecha_ultima[k] = '\0';
	}
}

//a partir de aqui son las funciones de la logica del ajedrez

void ajedrez() {

	struct todas piezas;

	//VARAIBLES DEL MOVIMIENTO
	char pieza_elegida; //para el switch
	int fila_aux; //Posicion del destino
	int columna_aux; // Posicion de destino
	char aux_columna;
	int num_piezas;
	int mov_producido; //se ha movido una pieza
	int contador_mov; //contador blancas o negras
	int jaque;

	//TABLERO
	char tablero_color[DIM][DIM]; //Casillas blancas o negras
	int tablero_piezas[DIM][DIM]; //Valores de lasa piezas
	int fila, columna; //Para bucle del tablero
	char indice_inferior, indice_superior;
	int indice_izquierda, indice_derecha;

	//PARAMETROS PARA LA IMPRESION DEL TABLERO
	indice_inferior = 'a';
	indice_superior = 'a';
	indice_derecha = '8';
	indice_izquierda = '8';

	//PARAMETROS DE REVISION DE MOVIMIENTO
	int i; //parametro para el eje x
	int j; //parametro para el eje y


		   //INICIALIZA EL TABLERO DE PIEZAS
	for (fila = 0; fila < DIM; fila++) {
		for (columna = 0; columna < DIM; columna++) {
			tablero_piezas[fila][columna] = 0;
		}
	}

	//INICIALIZAR EL TABLERO CON LAS PIEZAS 
	//PIEZAS BLANCAS
	for (i = 0; i < MAX_PIEZAS; i++) {
		if (i < 8) {
			piezas.peon[i].capturada = 0;
			piezas.peon[i].valor = 1;
			piezas.peon[i].fila = 7;
			piezas.peon[i].columna = i + 1;
			tablero_piezas[piezas.peon[i].fila][piezas.peon[i].columna] = piezas.peon[i].valor;
		}
		else {
			piezas.peon[i].capturada = 1;
			piezas.peon[i].valor = 1;
			piezas.peon[i].fila = 0;
			piezas.peon[i].columna = 0;
		}
		if (i < 2) {
			piezas.caballo[i].valor = 2;
			piezas.caballo[i].fila = 8;
			piezas.caballo[i].capturada = 0;

			piezas.alfil[i].valor = 3;
			piezas.alfil[i].fila = 8;
			piezas.alfil[i].capturada = 0;

			piezas.torre[i].valor = 4;
			piezas.torre[i].fila = 8;
			piezas.torre[i].capturada = 0;

			if (i == 0) {
				piezas.alfil[i].columna = 3;
				piezas.caballo[i].columna = 2;
				piezas.torre[i].columna = 1;
			}
			else {
				piezas.alfil[i].columna = 6;
				piezas.caballo[i].columna = 7;
				piezas.torre[i].columna = 8;
			}
			tablero_piezas[piezas.alfil[i].fila][piezas.alfil[i].columna] = piezas.alfil[i].valor;
			tablero_piezas[piezas.caballo[i].fila][piezas.caballo[i].columna] = piezas.caballo[i].valor;
			tablero_piezas[piezas.torre[i].fila][piezas.torre[i].columna] = piezas.torre[i].valor;
		}
		else {
			piezas.caballo[i].valor = 2;
			piezas.caballo[i].fila = 0;
			piezas.caballo[i].columna = 0;
			piezas.caballo[i].capturada = 1;

			piezas.alfil[i].valor = 3;
			piezas.alfil[i].fila = 0;
			piezas.alfil[i].columna = 0;
			piezas.alfil[i].capturada = 1;

			piezas.torre[i].valor = 4;
			piezas.torre[i].fila = 0;
			piezas.torre[i].columna = 0;
			piezas.torre[i].capturada = 1;

		}
	}
	for (i = 0; i < MAX_PIEZAS; i++) {
		if (i == 0) {
			piezas.reina[i].capturada = 0;
			piezas.reina[i].valor = 6;
			piezas.reina[i].fila = 8;
			piezas.reina[i].columna = 4;
			tablero_piezas[piezas.reina[i].fila][piezas.reina[i].columna] = piezas.reina[i].valor;
		}
		else {
			piezas.reina[i].capturada = 1;
			piezas.reina[i].valor = 6;
			piezas.reina[i].fila = 8;
			piezas.reina[i].columna = 4;
		}
	}
	piezas.rey.capturada = 0;
	piezas.rey.valor = 5;
	piezas.rey.fila = 8;
	piezas.rey.columna = 5;
	tablero_piezas[piezas.rey.fila][piezas.rey.columna] = piezas.rey.valor;


	//PIEZAS NEGRAS
	for (i = 0; i < 8; i++) {
		piezas.peon_n[i].capturada = 0;
		piezas.peon_n[i].valor = 12;
		piezas.peon_n[i].fila = 2;
		piezas.peon_n[i].columna = i + 1;
		tablero_piezas[piezas.peon_n[i].fila][piezas.peon_n[i].columna] = piezas.peon_n[i].valor;
	}
	for (i = 0; i < 2; i++) {
		piezas.caballo_n[i].valor = 11;
		piezas.caballo_n[i].fila = 1;
		piezas.caballo_n[i].capturada = 0;

		piezas.alfil_n[i].valor = 10;
		piezas.alfil_n[i].fila = 1;
		piezas.alfil_n[i].capturada = 0;

		piezas.torre_n[i].valor = 9;
		piezas.torre_n[i].fila = 1;
		piezas.torre_n[i].capturada = 0;
		if (i == 0) {
			piezas.alfil_n[i].columna = 3;
			piezas.caballo_n[i].columna = 2;
			piezas.torre_n[i].columna = 1;
		}
		else {
			piezas.alfil_n[i].columna = 6;
			piezas.caballo_n[i].columna = 7;
			piezas.torre_n[i].columna = 8;
		}
		tablero_piezas[piezas.alfil_n[i].fila][piezas.alfil_n[i].columna] = piezas.alfil_n[i].valor;
		tablero_piezas[piezas.caballo_n[i].fila][piezas.caballo_n[i].columna] = piezas.caballo_n[i].valor;
		tablero_piezas[piezas.torre_n[i].fila][piezas.torre_n[i].columna] = piezas.torre_n[i].valor;
	}
	for (i = 0; i < MAX_PIEZAS; i++) {
		if (i == 0) {
			piezas.reina_n[i].capturada = 0;
			piezas.reina_n[i].valor = 7;
			piezas.reina_n[i].fila = 1;
			piezas.reina_n[i].columna = 4;
			tablero_piezas[piezas.reina_n[i].fila][piezas.reina_n[i].columna] = piezas.reina_n[i].valor;
		}
		else {
			piezas.reina_n[i].capturada = 1;
			piezas.reina_n[i].valor = 7;
			piezas.reina_n[i].fila = 8;
			piezas.reina_n[i].columna = 4;
		}
	}
	piezas.rey_n.capturada = 0;
	piezas.rey_n.valor = 8;
	piezas.rey_n.fila = 1;
	piezas.rey_n.columna = 5;
	tablero_piezas[piezas.rey_n.fila][piezas.rey_n.columna] = piezas.rey_n.valor;


	//ESPECIFICA CASILLAS BLANCAS Y NEGRAS
	for (fila = 0; fila < DIM; fila++) {
		for (columna = 0; columna < DIM; columna++) {
			if ((fila + (1 * columna) + 1) % 2 == 0) {
				tablero_color[fila][columna] = '\261';
			}
			else {
				tablero_color[fila][columna] = '\333';
			}
		}
	}

	//ELEMENTOS AUXILIARES DEL TABLERO DE CASILLAS BLANCAS Y NEGRAS
	for (fila = 0; fila < DIM; fila++) {
		for (columna = 0; columna < DIM; columna++) {
			if ((fila == 0 && columna == 0) || (fila == 0 && columna == 9) || (fila == 9 && columna == 0) || (fila == 9 && columna == 9)) {
				tablero_color[fila][columna] = ' ';
			}
			else if (fila == 0) {
				tablero_color[fila][columna] = indice_superior;
				indice_superior++;
			}
			else if (fila == 9) {
				tablero_color[fila][columna] = indice_inferior;
				indice_inferior++;
			}
			else if (columna == 0) {
				tablero_color[fila][columna] = indice_izquierda;
				indice_izquierda--;
			}
			else if (columna == 9) {
				tablero_color[fila][columna] = indice_derecha;
				indice_derecha--;
			}
		}
	}

	contador_mov = 0;

	do {

		if (contador_mov % 2 == 0) {
			printf("Para salir pulse \"x\"\nMueven Blancas \n\n\n");
			mov_producido = 0;
			while (mov_producido == 0) {
				do {
					imprimir_tablero(tablero_color, tablero_piezas);
					jaque = check(tablero_piezas, &piezas, contador_mov);
					if (jaque == 1) {
						printf("CHECK \n");
					}
					printf("Elija pieza: ");
					scanf_s("%c", &pieza_elegida);
					getchar();

					switch (pieza_elegida) {
					case 'x':
					case 'X':
						return;
					case 'p':
					case 'P':
						pedir_destino(&columna_aux, &fila_aux);
						num_piezas = 0;
						for (i = 0; i < MAX_PIEZAS; i++) {
							if (piezas.peon[i].capturada == 0) {
								piezas.peon[i].revisar = revision_peon(tablero_piezas, piezas.peon[i].fila, piezas.peon[i].columna, fila_aux, columna_aux);
								if (piezas.peon[i].revisar == 1) {
									num_piezas++;
								}
							}
						}
						if (num_piezas > 1) {
							i = caen_en_el_mismo_sitio(&piezas.peon);

							pieza_capturada(tablero_piezas, &piezas, &piezas.peon[i], fila_aux, columna_aux);

							mov_producido = 1;
						}

						else if (num_piezas == 1) {
							for (i = 0; i < MAX_PIEZAS; i++) {
								if (piezas.peon[i].revisar == 1) {
									break;
								}
							}

							pieza_capturada(tablero_piezas, &piezas, &piezas.peon[i], fila_aux, columna_aux);

							mov_producido = 1;
						}
						else {
							printf("Movimiento no valido \n");
							system("pause");
						}

						break;
					case 'c':
					case'C':

						pedir_destino(&columna_aux, &fila_aux);
						num_piezas = 0;
						for (i = 0; i < MAX_PIEZAS; i++) {
							if (piezas.caballo[i].capturada == 0) {
								piezas.caballo[i].revisar = revision_caballo(tablero_piezas, piezas.caballo[i].fila, piezas.caballo[i].columna, fila_aux, columna_aux, piezas.caballo[i].valor);
								if (piezas.caballo[i].revisar == 1) {
									num_piezas++;
								}
							}
						}
						if (num_piezas > 1) {
							i = caen_en_el_mismo_sitio(&piezas.caballo);

							pieza_capturada(tablero_piezas, &piezas, &piezas.caballo[i], fila_aux, columna_aux);

							mov_producido = 1;
						}

						else if (num_piezas == 1) {
							for (i = 0; i < MAX_PIEZAS; i++) {
								if (piezas.caballo[i].revisar == 1) {
									break;
								}
							}

							pieza_capturada(tablero_piezas, &piezas, &piezas.caballo[i], fila_aux, columna_aux);

							mov_producido = 1;
						}
						else {
							printf("Movimiento no valido \n");
							system("pause");
						}

						break;
					case 'a':
					case 'A':

						pedir_destino(&columna_aux, &fila_aux);
						num_piezas = 0;
						for (i = 0; i < MAX_PIEZAS; i++) {
							if (piezas.alfil[i].capturada == 0) {
								piezas.alfil[i].revisar = revision_alfil(tablero_piezas, piezas.alfil[i].fila, piezas.alfil[i].columna, fila_aux, columna_aux, piezas.alfil[i].valor);
								if (piezas.alfil[i].revisar == 1) {
									num_piezas = 1;
								}
							}
						}
						if (num_piezas == 1) {
							for (i = 0; i < MAX_PIEZAS; i++) {
								if (piezas.alfil[i].revisar == 1) {

									pieza_capturada(tablero_piezas, &piezas, &piezas.alfil[i], fila_aux, columna_aux);

									mov_producido = 1;
								}
							}
						}
						else if (num_piezas > 1) {

							i = caen_en_el_mismo_sitio(&piezas.alfil);

							pieza_capturada(tablero_piezas, &piezas, &piezas.alfil[i], fila_aux, columna_aux);

							mov_producido = 1;
						}
						else {
							printf("Movimiento no valido \n");
							system("pause");
						}

						break;
					case 't':
					case 'T':

						pedir_destino(&columna_aux, &fila_aux);
						num_piezas = 0;
						for (i = 0; i < MAX_PIEZAS; i++) {
							if (piezas.torre[i].capturada == 0) {
								piezas.torre[i].revisar = revision_torre(tablero_piezas, piezas.torre[i].fila, piezas.torre[i].columna, fila_aux, columna_aux, piezas.torre[i].valor);
								if (piezas.torre[i].revisar == 1) {
									num_piezas++;
								}
							}
						}
						if (num_piezas > 1) {
							i = caen_en_el_mismo_sitio(&piezas.torre);

							pieza_capturada(tablero_piezas, &piezas, &piezas.torre[i], fila_aux, columna_aux);

							mov_producido = 1;
						}

						else if (num_piezas == 1) {
							for (i = 0; i < MAX_PIEZAS; i++) {
								if (piezas.torre[i].revisar == 1) {
									break;
								}
							}

							pieza_capturada(tablero_piezas, &piezas, &piezas.torre[i], fila_aux, columna_aux);

							mov_producido = 1;
						}
						else {
							printf("Movimiento no valido \n");
							system("pause");
						}
						break;

					case 'r':
					case 'R':

						pedir_destino(&columna_aux, &fila_aux);
						num_piezas = 0;
						for (i = 0; i < MAX_PIEZAS; i++) {
							if (piezas.reina[i].capturada == 0) {
								piezas.reina[i].revisar = revision_reina(tablero_piezas, piezas.reina[i].fila, piezas.reina[i].columna, fila_aux, columna_aux, piezas.reina[i].valor);
								if (piezas.reina[i].revisar == 1) {
									num_piezas++;
								}
							}
						}
						if (num_piezas == 1) {
							for (i = 0; i < MAX_PIEZAS; i++) {
								if (piezas.reina_n[i].revisar == 1) {

									pieza_capturada(tablero_piezas, &piezas, &piezas.reina[i], fila_aux, columna_aux);

									mov_producido = 1;
								}
							}
						}
						else if (num_piezas > 1) {

							i = caen_en_el_mismo_sitio(&piezas.reina);

							pieza_capturada(tablero_piezas, &piezas, &piezas.reina[i], fila_aux, columna_aux);

							mov_producido = 1;
						}
						else {
							printf("Movimiento no valido \n");
							system("pause");
						}
						break;
					case 'k':
					case 'K':

						pedir_destino(&columna_aux, &fila_aux);
						piezas.rey.revisar = revision_rey(tablero_piezas, piezas.rey.fila, piezas.rey.columna, fila_aux, columna_aux, piezas.rey.valor);

						if (piezas.rey.revisar == 1) {

							pieza_capturada(tablero_piezas, &piezas, &piezas.rey, fila_aux, columna_aux);

							mov_producido = 1;
						}
						else {
							printf("Movimiento no valido \n");
							system("pause");
						}
						break;
					default:
						break;

					}
					jaque = check(tablero_piezas, &piezas, contador_mov);
					if (jaque > 0) {
						printf("Movimiento no valido \n");
					}

					system("cls");

				} while (jaque > 0);
			}
		}
		else {
			printf("Para salir pulse \"x\"\nMueven Negras \n\n\n");
			mov_producido = 0;
			while (mov_producido == 0) {
				do {
					imprimir_tablero(tablero_color, tablero_piezas);
					jaque = check(tablero_piezas, &piezas, contador_mov);
					if (jaque == 1) {
						printf("CHECK \n");
					}

					printf("Elija pieza: ");
					scanf_s("%c", &pieza_elegida);
					getchar();

					switch (pieza_elegida) {
					case 'x':
					case 'X':
						return;
					case 'p':
					case 'P':
						pedir_destino(&columna_aux, &fila_aux);
						num_piezas = 0;
						for (i = 0; i < MAX_PIEZAS; i++) {
							if (piezas.peon_n[i].capturada == 0) {
								piezas.peon_n[i].revisar = revision_peon_n(tablero_piezas, piezas.peon_n[i].fila, piezas.peon_n[i].columna, fila_aux, columna_aux);
								if (piezas.peon_n[i].revisar == 1) {
									num_piezas++;
								}
							}
						}
						if (num_piezas > 1) {
							i = caen_en_el_mismo_sitio(&piezas.peon_n);

							pieza_capturada(tablero_piezas, &piezas, &piezas.peon_n[i], fila_aux, columna_aux);

							mov_producido = 1;
						}

						else if (num_piezas == 1) {
							for (i = 0; i < MAX_PIEZAS; i++) {
								if (piezas.peon_n[i].revisar == 1) {
									break;
								}
							}
							pieza_capturada(tablero_piezas, &piezas, &piezas.peon_n[i], fila_aux, columna_aux);

							mov_producido = 1;
						}
						else {
							printf("Movimiento no valido \n");
							system("pause");
						}

						break;
					case 'c':
					case'C':

						pedir_destino(&columna_aux, &fila_aux);
						num_piezas = 0;
						for (i = 0; i < MAX_PIEZAS; i++) {
							if (piezas.caballo_n[i].capturada == 0) {
								piezas.caballo_n[i].revisar = revision_caballo(tablero_piezas, piezas.caballo_n[i].fila, piezas.caballo_n[i].columna, fila_aux, columna_aux, piezas.caballo_n[i].valor);
								if (piezas.caballo_n[i].revisar == 1) {
									num_piezas++;
								}
							}
						}
						if (num_piezas > 1) {
							i = caen_en_el_mismo_sitio(&piezas.caballo);

							pieza_capturada(tablero_piezas, &piezas, &piezas.caballo_n[i], fila_aux, columna_aux);

							mov_producido = 1;
						}

						else if (num_piezas == 1) {
							for (i = 0; i < MAX_PIEZAS; i++) {
								if (piezas.caballo_n[i].revisar == 1) {
									break;
								}
							}
							pieza_capturada(tablero_piezas, &piezas, &piezas.caballo_n[i], fila_aux, columna_aux);

							mov_producido = 1;
						}
						else {
							printf("Movimiento no valido \n");
							system("pause");
						}

						break;
					case 'a':
					case 'A':

						pedir_destino(&columna_aux, &fila_aux);
						num_piezas = 0;
						for (i = 0; i < MAX_PIEZAS; i++) {
							if (piezas.alfil_n[i].capturada == 0) {
								piezas.alfil_n[i].revisar = revision_alfil(tablero_piezas, piezas.alfil_n[i].fila, piezas.alfil_n[i].columna, fila_aux, columna_aux, piezas.alfil_n[i].valor);
								if (piezas.alfil_n[i].revisar == 1) {
									num_piezas++;
								}
							}
						}
						if (num_piezas == 1) {
							for (i = 0; i < MAX_PIEZAS; i++) {
								if (piezas.alfil_n[i].revisar == 1) {
									break;
								}
							}
							pieza_capturada(tablero_piezas, &piezas, &piezas.alfil_n[i], fila_aux, columna_aux);

							mov_producido = 1;
						}
						else {
							printf("Movimiento no valido \n");
							system("pause");
						}

						break;
					case 't':
					case 'T':

						pedir_destino(&columna_aux, &fila_aux);
						num_piezas = 0;
						for (i = 0; i < MAX_PIEZAS; i++) {
							if (piezas.torre_n[i].capturada == 0) {
								piezas.torre_n[i].revisar = revision_torre(tablero_piezas, piezas.torre_n[i].fila, piezas.torre_n[i].columna, fila_aux, columna_aux, piezas.torre_n[i].valor);
								if (piezas.torre_n[i].revisar == 1) {
									num_piezas++;
								}
							}
						}
						if (num_piezas > 1) {
							i = caen_en_el_mismo_sitio(&piezas.torre);

							pieza_capturada(tablero_piezas, &piezas, &piezas.torre_n[i], fila_aux, columna_aux);

							mov_producido = 1;
						}

						else if (num_piezas == 1) {
							for (i = 0; i < MAX_PIEZAS; i++) {
								if (piezas.torre_n[i].revisar == 1) {
									break;
								}
							}

							pieza_capturada(tablero_piezas, &piezas, &piezas.torre_n[i], fila_aux, columna_aux);

							mov_producido = 1;
						}
						else {
							printf("Movimiento no valido \n");
							system("pause");
						}
						break;

					case 'r':
					case 'R':

						pedir_destino(&columna_aux, &fila_aux);
						num_piezas = 0;
						for (i = 0; i < MAX_PIEZAS; i++) {
							if (piezas.reina_n[i].capturada == 0) {
								piezas.reina_n[i].revisar = revision_reina(tablero_piezas, piezas.reina_n[i].fila, piezas.reina_n[i].columna, fila_aux, columna_aux, piezas.reina_n[i].valor);
								if (piezas.reina_n[i].revisar == 1) {
									num_piezas++;
								}
							}
						}
						if (num_piezas == 1) {
							for (i = 0; i < MAX_PIEZAS; i++) {
								if (piezas.reina_n[i].revisar == 1) {

									pieza_capturada(tablero_piezas, &piezas, &piezas.reina_n[i], fila_aux, columna_aux);

									mov_producido = 1;
								}
							}
						}
						else if (num_piezas > 1) {

							i = caen_en_el_mismo_sitio(&piezas.reina_n);

							pieza_capturada(tablero_piezas, &piezas, &piezas.reina_n[i], fila_aux, columna_aux);

							mov_producido = 1;
						}
						else {
							printf("Movimiento no valido \n");
							system("pause");
						}
						break;
					case 'k':
					case 'K':

						pedir_destino(&columna_aux, &fila_aux);
						piezas.rey_n.revisar = revision_rey(tablero_piezas, piezas.rey_n.fila, piezas.rey_n.columna, fila_aux, columna_aux, piezas.rey_n.valor);

						if (piezas.rey_n.revisar == 1) {

							pieza_capturada(tablero_piezas, &piezas, &piezas.rey_n, fila_aux, columna_aux);

							mov_producido = 1;
						}
						else {
							printf("Movimiento no valido \n");
							system("pause");
						}
						break;
					default:
						break;

					}
					jaque = check(tablero_piezas, &piezas, contador_mov);
					if (jaque > 0) {
						printf("Movimiento no valido \n");
					}
					system("cls");
				} while (jaque > 0);
			}
		}
		coronar(&tablero_piezas, &piezas);
		contador_mov++;

	} while (1);

	system("pause");
}

void imprimir_tablero(char tablero_color[DIM][DIM], int tablero_piezas[DIM][DIM]) {
	int fila, columna;
	for (fila = 0; fila < DIM; fila++) {
		for (columna = 0; columna < DIM; columna++) {
			if ((columna == 9) || (columna == 0)) {
				printf("\t");
			}
			if ((tablero_piezas[fila][columna] == 0)) {
				printf("%c\t", tablero_color[fila][columna]);
			}
			else if (tablero_piezas[fila][columna] == 1) {
				printf("P\t");
			}
			else if (tablero_piezas[fila][columna] == 2) {
				printf("C\t");
			}
			else if (tablero_piezas[fila][columna] == 3) {
				printf("A\t");
			}
			else if (tablero_piezas[fila][columna] == 4) {
				printf("T\t");
			}
			else if (tablero_piezas[fila][columna] == 5) {
				printf("K\t");
			}
			else if (tablero_piezas[fila][columna] == 6) {
				printf("R\t");
			}
			else if (tablero_piezas[fila][columna] == 7) {
				printf("r*\t");
			}
			else if (tablero_piezas[fila][columna] == 8) {
				printf("k*\t");
			}
			else if (tablero_piezas[fila][columna] == 9) {
				printf("t*\t");
			}
			else if (tablero_piezas[fila][columna] == 10) {
				printf("a*\t");
			}
			else if (tablero_piezas[fila][columna] == 11) {
				printf("c*\t");
			}
			else if (tablero_piezas[fila][columna] == 12) {
				printf("p*\t");
			}
			else {
				printf("%d\t", tablero_piezas[fila][columna]);
			}
			if (columna == 0) {
				printf("\t");
			}
		}
		if ((fila == 0) || (fila == 8)) {
			printf("\n\n\n");
		}
		printf("\n\n\n");
	}
}

void pedir_destino(int *columna_aux, int *fila_aux) {
	char aux_columna;
	do {
		printf("Introduzca la columna: ");
		scanf_s("%c", &aux_columna);
		getchar();
		if ((aux_columna < 'a') || (aux_columna > 'h')) {
			printf("\nColumna erronea\n");
		}
	} while ((aux_columna < 'a') || (aux_columna > 'h'));
	do {
		printf("Introduzca la fila: ");
		scanf_s("%d", fila_aux);
		getchar();
		if ((*fila_aux < 0) || (*fila_aux > 8)) {
			printf("\nFila erronea\n");
		}
	} while ((*fila_aux < 1) || (*fila_aux > 8));

	*columna_aux = aux_columna - 'a' + 1;
	*fila_aux = 9 - *fila_aux;
}

int revision_peon(int tablero[DIM][DIM], int fila, int columna, int fila_aux, int   columna_aux) {
	if ((tablero[fila_aux][columna_aux] <= 6) && (tablero[fila_aux][columna_aux] >= 1)) {
		return 0;
	}
	else if (((fila == fila_aux + 1) && (columna == columna_aux)) && (tablero[fila_aux][columna_aux] == 0)) {
		return 1;
	}
	else if (((fila == fila_aux + 1) && (columna == columna_aux - 1)) && (tablero[fila_aux][columna_aux] >= 7)) {
		return 1;
	}
	else if (((fila == fila_aux + 1) && (columna == columna_aux + 1)) && (tablero[fila_aux][columna_aux] >= 7)) {
		return 1;
	}
	else {
		return 0;
	}
}

int revision_peon_n(int tablero[DIM][DIM], int fila, int columna, int fila_aux, int columna_aux) {
	if (tablero[fila_aux][columna_aux] > 6) {
		return 0;
	}
	else if ((fila == fila_aux - 1) && (columna == columna_aux) && (tablero[fila_aux][columna_aux] == 0)) {
		return 1;
	}
	else if (((fila == fila_aux - 1) && (columna == columna_aux - 1)) && (tablero[fila_aux][columna_aux] < 7) && (tablero[fila_aux][columna_aux] > 0)) {
		return 1;
	}
	else if (((fila == fila_aux - 1) && (columna == columna_aux + 1)) && (tablero[fila_aux][columna_aux] < 7) && (tablero[fila_aux][columna_aux] > 0)) {
		return 1;
	}
	else {
		return 0;
	}
}

int revision_caballo(int tablero[DIM][DIM], int fila, int columna, int fila_aux, int columna_aux, int valor) {
	if (valor == 2) {
		if ((tablero[fila_aux][columna_aux] <= 6) && (tablero[fila_aux][columna_aux] >= 1)) {
			return 0;
		}
	}
	else if ((tablero[fila_aux][columna_aux] <= 12) && (tablero[fila_aux][columna_aux] >= 7)) {
		return 0;
	}
	if (((fila - fila_aux) == 2) && ((columna - columna_aux) == 1)) {
		return 1;
	}
	else if (((fila - fila_aux) == 2) && ((columna - columna_aux) == -1)) {
		return 1;
	}
	else if (((fila - fila_aux) == -2) && ((columna - columna_aux) == 1)) {
		return 1;
	}
	else if (((fila - fila_aux) == -2) && ((columna - columna_aux) == -1)) {
		return 1;
	}
	else if (((fila - fila_aux) == 1) && ((columna - columna_aux) == 2)) {
		return 1;
	}
	else if (((fila - fila_aux) == 1) && ((columna - columna_aux) == -2)) {
		return 1;
	}
	else if (((fila - fila_aux) == -1) && ((columna - columna_aux) == 2)) {
		return 1;
	}
	else if (((fila - fila_aux) == -1) && ((columna - columna_aux) == -2)) {
		return 1;
	}
	else {
		return 0;
	}
}

int revision_alfil(int tablero[DIM][DIM], int fila, int columna, int fila_aux, int columna_aux, int valor) {
	int revision;
	int i;
	int j;

	if ((fila - columna) == (fila_aux - columna_aux)) {  //DIAGONAL DECRECIENTE DE IZQUIERDA A DERECHA
		revision = 1;
	}
	else if ((fila + columna) == (fila_aux + columna_aux)) { //DIAGONAL CRECIENTE DE IZQUIERDA A DERECHA
		revision = 1;
	}
	else {
		return 0;
	}
	if (revision == 1) {

		if ((tablero[fila_aux][columna_aux] <= 6) && (tablero[fila_aux][columna_aux] >= 1) && (valor == 3)) {
			return 0;
		}
		else if ((tablero[fila_aux][columna_aux] <= 12) && (tablero[fila_aux][columna_aux] >= 7)) {
			return 0;
		}
		if ((fila - columna) == (fila_aux - columna_aux)) {

			if (columna > columna_aux) {
				j = fila;
				for (i = columna - 1; i > columna_aux; i--) {
					j = j - 1;  //NO QUIERO PERDER EL VALOR DE LA REINA.FILA Y USO UN AUXILIAR
					if (tablero[j][i] != 0) {
						return 0;
					}
				}
			}
			else {
				j = fila;
				for (i = columna + 1; i < columna_aux; i++) {
					j = j + 1;
					if (tablero[j][i] != 0) {
						return 0;
					}
				}
			}
		}
		else if (((fila + columna) == (fila_aux + columna_aux))) {

			if (columna > columna_aux) {
				j = fila;
				for (i = columna - 1; i > columna_aux; i--) {
					j = j + 1;  //NO QUIERO PERDER EL VALOR DE LA REINA.FILA Y USO UN AUXILIAR
					if (tablero[j][i] != 0) {
						return 0;
					}
				}
			}
			else {
				j = fila;
				for (i = columna + 1; i < columna_aux; i++) {
					j = j - 1;
					if (tablero[j][i] != 0) {
						return 0;
					}
				}
			}
		}
	}
	return 1;
}

int revision_torre(int tablero[DIM][DIM], int fila, int columna, int fila_aux, int columna_aux, int valor) {
	int revision;
	int i;

	if ((fila == fila_aux) && (columna != columna_aux)) {
		revision = 1;
	}
	else if ((fila != fila_aux) && (columna == columna_aux)) {
		revision = 1;
	}
	else {
		return 0;
	}
	if (revision == 1) {
		if (valor == 4) {
			if ((tablero[fila_aux][columna_aux] <= 6) && (tablero[fila_aux][columna_aux] >= 1)) {
				return 0;
			}
		}
		else if ((tablero[fila_aux][columna_aux] <= 12) && (tablero[fila_aux][columna_aux] >= 7)) {
			return 0;
		}
		if ((fila == fila_aux) && (columna != columna_aux)) {
			if (columna > columna_aux) {
				for (i = columna_aux + 1; i < columna; i++) { //EL MAS UNO ES PARA QUE SALTE LA CASILLA INCIAL POR SI HAY UN PIEZA CAPTURABLE
					if (tablero[fila][i] != 0) {
						return 0;
					}
				}
			}
			else {
				for (i = columna + 1; i < columna_aux; i++) { //EL MAS UNO ES PARA QUE SALTE LA CASILLA INCIAL 
					if (tablero[fila][i] != 0) {
						return 0;
					}
				}
			}
		}
		else if ((fila != fila_aux) && (columna == columna_aux)) {
			if (fila > fila_aux) {
				for (i = fila_aux + 1; i < fila; i++) { //EL MAS UNO ES PARA QUE SALTE LA CASILLA INCIAL POR SI HAY UN PIEZA CAPTURABLE
					if (tablero[i][columna] != 0) {
						return 0;
					}
				}
			}
			else {
				for (i = fila + 1; i < fila_aux; i++) {//EL MAS UNO ES PARA QUE SALTE LA CASILLA INCIAL
					if (tablero[i][columna] != 0) {
						return 0;
					}
				}
			}
		}
	}
	return 1;
}

int revision_reina(int tablero[DIM][DIM], int fila, int columna, int fila_aux, int columna_aux, int valor) {
	int revision;
	int i;
	int j;

	if ((fila == fila_aux) && (columna != columna_aux)) {
		revision = 1;
	}
	else if ((fila != fila_aux) && (columna == columna_aux)) {
		revision = 1;
	}
	else if ((fila - columna) == (fila_aux - columna_aux)) {
		revision = 1;
	}
	else if ((fila + columna) == (fila_aux + columna_aux)) {
		revision = 1;
	}
	else {
		return 0;
	}
	if (revision == 1) {
		if (valor == 6) {
			if ((tablero[fila_aux][columna_aux] <= 6) && (tablero[fila_aux][columna_aux] >= 1)) {
				return 0;
			}
		}
		else if ((tablero[fila_aux][columna_aux] <= 12) && (tablero[fila_aux][columna_aux] >= 7)) {
			return 0;
		}
		if ((fila == fila_aux) && (columna != columna_aux)) {
			if (columna > columna_aux) {
				for (i = columna_aux + 1; i < columna; i++) { //EL MAS UNO ES PARA QUE SALTE LA CASILLA INCIAL POR SI HAY UN PIEZA CAPTURABLE
					if (tablero[fila][i] != 0) {
						return 0;
					}
				}
			}
			else {
				for (i = columna + 1; i < columna_aux; i++) { //EL MAS UNO ES PARA QUE SALTE LA CASILLA INCIAL 
					if (tablero[fila][i] != 0) {
						return 0;
					}
				}
			}
		}
		else if ((fila != fila_aux) && (columna == columna_aux)) {
			if (fila > fila_aux) {
				for (i = fila_aux + 1; i < fila; i++) { //EL MAS UNO ES PARA QUE SALTE LA CASILLA INCIAL POR SI HAY UN PIEZA CAPTURABLE
					if (tablero[i][columna] != 0) {
						return 0;
					}
				}
			}
			else {
				for (i = fila + 1; i < fila_aux; i++) {//EL MAS UNO ES PARA QUE SALTE LA CASILLA INCIAL
					if (tablero[i][columna] != 0) {
						return 0;
					}
				}
			}
		}
		else if ((fila - columna) == (fila_aux - columna_aux)) {

			if (columna > columna_aux) {
				j = fila;
				for (i = columna - 1; i > columna_aux; i--) {
					j = j - 1;  //NO QUIERO PERDER EL VALOR DE LA REINA.FILA Y USO UN AUXILIAR
					if (tablero[j][i] != 0) {
						return 0;
					}
				}
			}
			else {
				j = fila;
				for (i = columna + 1; i < columna_aux; i++) {
					j = j + 1;
					if (tablero[j][i] != 0) {
						return 0;
					}
				}
			}
		}
		else if (((fila + columna) == (fila_aux + columna_aux))) {

			if (columna > columna_aux) {
				j = fila;
				for (i = columna - 1; i > columna_aux; i--) {
					j = j + 1;  //NO QUIERO PERDER EL VALOR DE LA REINA.FILA Y USO UN AUXILIAR
					if (tablero[j][i] != 0) {
						return 0;
					}
				}
			}
			else {
				j = fila;
				for (i = columna + 1; i < columna_aux; i++) {
					j = j - 1;
					if (tablero[j][i] != 0) {
						return 0;
					}
				}
			}
		}
	}
	return 1;
}

int revision_rey(int tablero[DIM][DIM], int fila, int columna, int fila_aux, int columna_aux, int valor) {
	int revision = 0;
	if (valor == 5) {
		if ((tablero[fila_aux][columna_aux] <= 6) && (tablero[fila_aux][columna_aux] >= 1)) {
			return 0;
		}
	}
	else if ((tablero[fila_aux][columna_aux] <= 12) && (tablero[fila_aux][columna_aux] >= 7)) {
		return 0;
	}
	if (((fila == fila_aux) && (columna != columna_aux)) && ((columna - columna_aux) * (columna - columna_aux)) == 1) {
		revision = 1;
	}
	else if (((fila != fila_aux) && (columna == columna_aux)) && ((fila - fila_aux) * (fila - fila_aux)) == 1) {
		revision = 1;
	}
	else if (((fila - columna) == (fila_aux - columna_aux)) && ((fila - fila_aux) * (fila - fila_aux)) == 1) {
		revision = 1;
	}
	else if (((fila + columna) == (fila_aux + columna_aux)) && ((fila - fila_aux) * (fila - fila_aux)) == 1) {
		revision = 1;
	}
	return revision;
}

int caen_en_el_mismo_sitio(struct pieza *pieza) {
	int i;
	int fila_busqueda, columna_busqueda;
	char busqueda_columna;
	do {
		printf("Hay mas de un movimiento posible, epecifique la pieza de origen.\n");
		printf("Introduzca la columna:");
		getchar();
		scanf_s("%c", &busqueda_columna);
		printf("Introduzca la fila:");
		scanf_s("%d", &fila_busqueda);
		getchar();
		columna_busqueda = busqueda_columna - 'a' + 1;
		fila_busqueda = 9 - fila_busqueda;
		for (i = 0; i < 10; i++) {
			if ((columna_busqueda == pieza[i].columna) && (fila_busqueda == pieza[i].fila)) {
				return i;
			}
		}
		printf("Coordenadas erroneas \n");
	} while ((columna_busqueda != pieza[i].columna) || (fila_busqueda != pieza[i].fila));
}

void pieza_capturada(int tablero[DIM][DIM], struct todas *piezas, struct pieza *pieza, int fila_aux, int columna_aux) {//la primera struct corresponde a la pieza que es capturad a la pieza capturada y la segunda a la que se mueve
	int i;
	if (tablero[fila_aux][columna_aux] == piezas->peon[0].valor) {// El primer condicional comprueba si hay una pieza y de que tipo es en la casilla de destino
		for (i = 0; i < MAX_PIEZAS; i++) {//El bucle junto al condicional sirve para elegir cual de todas las piezas es la correcta(en este caso cual de todos los peones)
			if ((piezas->peon[i].fila == fila_aux) && (piezas->peon[i].columna == columna_aux)) {
				piezas->peon[i].capturada = 1;
				piezas->peon[i].revisar = 0;
				tablero[pieza->fila][pieza->columna] = 0;

				pieza->fila = fila_aux;
				pieza->columna = columna_aux;

				tablero[pieza->fila][pieza->columna] = pieza->valor;
				break;
			}
		}
	}
	else if (tablero[fila_aux][columna_aux] == piezas->alfil[0].valor) {
		for (i = 0; i < MAX_PIEZAS; i++) {
			if ((piezas->alfil[i].fila == fila_aux) && (piezas->alfil[i].columna == columna_aux)) {
				piezas->alfil[i].capturada = 1;
				piezas->alfil[i].revisar = 0;
				tablero[pieza->fila][pieza->columna] = 0;

				pieza->fila = fila_aux;
				pieza->columna = columna_aux;

				tablero[pieza->fila][pieza->columna] = pieza->valor;
				break;
			}
		}
	}
	else if (tablero[fila_aux][columna_aux] == piezas->caballo[0].valor) {
		for (i = 0; i < MAX_PIEZAS; i++) {
			if ((piezas->caballo[i].fila == fila_aux) && (piezas->caballo[i].columna == columna_aux)) {
				piezas->caballo[i].capturada = 1;
				piezas->caballo[i].revisar = 0;
				tablero[pieza->fila][pieza->columna] = 0;

				pieza->fila = fila_aux;
				pieza->columna = columna_aux;

				tablero[pieza->fila][pieza->columna] = pieza->valor;
				break;
			}
		}
	}
	else if (tablero[fila_aux][columna_aux] == piezas->torre[0].valor) {
		for (i = 0; i < MAX_PIEZAS; i++) {
			if ((piezas->torre[i].fila == fila_aux) && (piezas->torre[i].columna == columna_aux)) {
				piezas->torre[i].capturada = 1;
				piezas->torre[i].revisar = 0;
				tablero[pieza->fila][pieza->columna] = 0;

				pieza->fila = fila_aux;
				pieza->columna = columna_aux;

				tablero[pieza->fila][pieza->columna] = pieza->valor;
				break;
			}
		}
	}
	else if (tablero[fila_aux][columna_aux] == piezas->reina[0].valor) {
		for (i = 0; i < MAX_PIEZAS; i++) {
			if ((piezas->reina[i].fila == fila_aux) && (piezas->reina[i].columna == columna_aux)) {
				piezas->reina[i].capturada = 1;
				piezas->reina[i].revisar = 0;
				tablero[pieza->fila][pieza->columna] = 0;

				pieza->fila = fila_aux;
				pieza->columna = columna_aux;

				tablero[pieza->fila][pieza->columna] = pieza->valor;
				break;
			}
		}
	}
	else if (tablero[fila_aux][columna_aux] == piezas->peon_n[0].valor) {
		for (i = 0; i < MAX_PIEZAS; i++) {
			if ((piezas->peon_n[i].fila == fila_aux) && (piezas->peon_n[i].columna == columna_aux)) {
				piezas->peon_n[i].capturada = 1;
				piezas->peon_n[i].revisar = 0;
				tablero[pieza->fila][pieza->columna] = 0;

				pieza->fila = fila_aux;
				pieza->columna = columna_aux;

				tablero[pieza->fila][pieza->columna] = pieza->valor;
				break;
			}
		}
	}
	else if (tablero[fila_aux][columna_aux] == piezas->alfil_n[0].valor) {
		for (i = 0; i < MAX_PIEZAS; i++) {
			if ((piezas->alfil_n[i].fila == fila_aux) && (piezas->alfil_n[i].columna == columna_aux)) {
				piezas->alfil_n[i].capturada = 1;
				piezas->alfil_n[i].revisar = 0;
				tablero[pieza->fila][pieza->columna] = 0;

				pieza->fila = fila_aux;
				pieza->columna = columna_aux;

				tablero[pieza->fila][pieza->columna] = pieza->valor;
				break;
			}
		}
	}
	else if (tablero[fila_aux][columna_aux] == piezas->caballo_n[0].valor) {
		for (i = 0; i < MAX_PIEZAS; i++) {
			if ((piezas->caballo_n[i].fila == fila_aux) && (piezas->caballo_n[i].columna == columna_aux)) {
				piezas->caballo_n[i].capturada = 1;
				piezas->caballo_n[i].revisar = 0;
				tablero[pieza->fila][pieza->columna] = 0;

				pieza->fila = fila_aux;
				pieza->columna = columna_aux;

				tablero[pieza->fila][pieza->columna] = pieza->valor;
				break;
			}
		}
	}
	else if (tablero[fila_aux][columna_aux] == piezas->torre_n[0].valor) {
		for (i = 0; i < MAX_PIEZAS; i++) {
			if ((piezas->torre_n[i].fila == fila_aux) && (piezas->torre_n[i].columna == columna_aux)) {
				piezas->torre_n[i].capturada = 1;
				piezas->torre_n[i].revisar = 0;
				tablero[pieza->fila][pieza->columna] = 0;

				pieza->fila = fila_aux;
				pieza->columna = columna_aux;

				tablero[pieza->fila][pieza->columna] = pieza->valor;
				break;
			}
		}
	}
	else if (tablero[fila_aux][columna_aux] == piezas->reina_n[0].valor) {
		for (i = 0; i < MAX_PIEZAS; i++) {
			if ((piezas->reina_n[i].fila == fila_aux) && (piezas->reina_n[i].columna == columna_aux)) {
				piezas->reina_n[i].capturada = 1;
				piezas->reina_n[i].revisar = 0;
				tablero[pieza->fila][pieza->columna] = 0;

				pieza->fila = fila_aux;
				pieza->columna = columna_aux;

				tablero[pieza->fila][pieza->columna] = pieza->valor;
				break;
			}
		}
	}
	else {

		tablero[pieza->fila][pieza->columna] = 0;

		pieza->fila = fila_aux;
		pieza->columna = columna_aux;

		tablero[pieza->fila][pieza->columna] = pieza->valor;
	}
}

void coronar(int tablero[DIM][DIM], struct todas *pieza) {
	int i, j;
	char opcion;
	for (i = 0; i < MAX_PIEZAS; i++) {
		if ((pieza->peon[i].fila == 1) && (pieza->peon[i].capturada == 0)) {
			printf("FELICIDADES PUEDE CORONAR: R-reina, A-alfil, T-torre, C-caballo\n");
			scanf_s("%c", &opcion);
			getchar();
			pieza->peon[i].capturada = 1;
			pieza->peon[i].revisar = 0;
			switch (opcion) {
			case 'R':
			case 'r':
				for (j = 0; j < MAX_PIEZAS; j++) {
					if (pieza->reina[j].capturada == 1) {
						pieza->reina[j].capturada = 0;
						pieza->reina[j].fila = pieza->peon[i].fila;
						pieza->reina[j].columna = pieza->peon[i].columna;
						tablero[pieza->peon[i].fila][pieza->peon[i].columna] = pieza->reina[j].valor;
						break;
					}
				}
				break;
			case 'A':
			case'a':
				for (j = 0; j < MAX_PIEZAS; j++) {
					if (pieza->alfil[j].capturada == 1) {
						pieza->alfil[j].capturada = 0;
						pieza->alfil[j].fila = pieza->peon[i].fila;
						pieza->alfil[j].columna = pieza->peon[i].columna;
						tablero[pieza->peon[i].fila][pieza->peon[i].columna] = pieza->alfil[j].valor;
						break;
					}
				}
				break;
			case 't':
			case'T':
				for (j = 0; j < MAX_PIEZAS; j++) {
					if (pieza->torre[j].capturada == 1) {
						pieza->torre[j].capturada = 0;
						pieza->torre[j].fila = pieza->peon[i].fila;
						pieza->torre[j].columna = pieza->peon[i].columna;
						tablero[pieza->peon[i].fila][pieza->peon[i].columna] = pieza->torre[j].valor;
						break;
					}
				}
				break;
			case 'C':
			case'c':
				for (j = 0; j < MAX_PIEZAS; j++) {
					if (pieza->caballo[j].capturada == 1) {
						pieza->caballo[j].capturada = 0;
						pieza->caballo[j].fila = pieza->peon[i].fila;
						pieza->caballo[j].columna = pieza->peon[i].columna;
						tablero[pieza->peon[i].fila][pieza->peon[i].columna] = pieza->caballo[j].valor;
						break;
					}
				}
				break;
			}
			break;
		}
		else if ((pieza->peon_n[i].fila == 1) && (pieza->peon_n[i].capturada == 0)) {
			printf("FELICIDADES PUEDE CORONAR: R-reina, A-alfil, T-torre, C-caballo\n");
			scanf_s("%c", &opcion);
			pieza->peon_n[i].capturada = 1;
			pieza->peon_n[i].revisar = 0;
			switch (opcion) {
			case 'R':
			case 'r':
				for (j = 0; j < MAX_PIEZAS; j++) {
					if (pieza->reina_n[j].capturada == 1) {
						pieza->reina_n[j].capturada = 0;
						pieza->reina_n[j].fila = pieza->peon_n[i].fila;
						pieza->reina_n[j].columna = pieza->peon_n[i].columna;
						tablero[pieza->peon[i].fila][pieza->peon[i].columna] = pieza->reina_n[j].valor;
						break;
					}
				}
				break;
			case 'A':
			case'a':
				for (j = 0; j < MAX_PIEZAS; j++) {
					if (pieza->alfil_n[j].capturada == 1) {
						pieza->alfil_n[j].capturada = 0;
						pieza->alfil_n[j].fila = pieza->peon_n[i].fila;
						pieza->alfil_n[j].columna = pieza->peon_n[i].columna;
						tablero[pieza->peon[i].fila][pieza->peon[i].columna] = pieza->alfil_n[j].valor;
						break;
					}
				}
				break;
			case 't':
			case'T':
				for (j = 0; j < MAX_PIEZAS; j++) {
					if (pieza->torre_n[j].capturada == 1) {
						pieza->torre_n[j].capturada = 0;
						pieza->torre_n[j].fila = pieza->peon_n[i].fila;
						pieza->torre_n[j].columna = pieza->peon_n[i].columna;
						tablero[pieza->peon[i].fila][pieza->peon[i].columna] = pieza->torre_n[j].valor;
						break;
					}
				}
				break;
			case 'C':
			case'c':
				for (j = 0; j < MAX_PIEZAS; j++) {
					if (pieza->caballo_n[j].capturada == 1) {
						pieza->caballo_n[j].capturada = 0;
						pieza->caballo_n[j].fila = pieza->peon_n[i].fila;
						pieza->caballo_n[j].columna = pieza->peon_n[i].columna;
						tablero[pieza->peon[i].fila][pieza->peon[i].columna] = pieza->caballo_n[j].valor;
						break;
					}
				}
				break;
			}
			break;
		}
	}
}

int check(int tablero[DIM][DIM], struct todas *pieza, int turno) {

	int i;
	int contador = 0;
	if (turno % 2 == 0) {
		for (i = 0; i < MAX_PIEZAS; i++) {
			if (pieza->peon[i].capturada == 0) {
				contador = contador + revision_peon(tablero, pieza->peon[i].fila, pieza->peon[i].columna, pieza->rey_n.fila, pieza->rey_n.columna);
			}
			if (pieza->caballo[i].capturada == 0) {
				contador = contador + revision_caballo(tablero, pieza->caballo[i].fila, pieza->caballo[i].columna, pieza->rey_n.fila, pieza->rey_n.columna, pieza->caballo[i].valor);
			}
			if (pieza->alfil[i].capturada == 0) {
				contador = contador + revision_alfil(tablero, pieza->alfil[i].fila, pieza->alfil[i].columna, pieza->rey_n.fila, pieza->rey_n.columna, pieza->alfil[i].valor);
			}
			if (pieza->torre[i].capturada == 0) {
				contador = contador + revision_torre(tablero, pieza->torre[i].fila, pieza->torre[i].columna, pieza->rey_n.fila, pieza->rey_n.columna, pieza->torre[i].valor);
			}
			if (pieza->reina[i].capturada == 0) {
				contador = contador + revision_reina(tablero, pieza->reina[i].fila, pieza->reina[i].columna, pieza->rey_n.fila, pieza->rey_n.columna, pieza->reina[i].valor);
			}
		}
	}
	else {
		for (i = 0; i < MAX_PIEZAS; i++) {
			if (pieza->peon_n[i].capturada == 0) {
				contador = contador + revision_peon_n(tablero, pieza->peon_n[i].fila, pieza->peon_n[i].columna, pieza->rey.fila, pieza->rey.columna);
			}
			if (pieza->caballo_n[i].capturada == 0) {
				contador = contador + revision_caballo(tablero, pieza->caballo_n[i].fila, pieza->caballo_n[i].columna, pieza->rey.fila, pieza->rey.columna, pieza->caballo_n[i].valor);
			}
			if (pieza->alfil_n[i].capturada == 0) {
				contador = contador + revision_alfil(tablero, pieza->alfil_n[i].fila, pieza->alfil_n[i].columna, pieza->rey.fila, pieza->rey.columna, pieza->alfil_n[i].valor);
			}
			if (pieza->torre_n[i].capturada == 0) {
				contador = contador + revision_torre(tablero, pieza->torre_n[i].fila, pieza->torre_n[i].columna, pieza->rey.fila, pieza->rey.columna, pieza->torre_n[i].valor);
			}
			if (pieza->reina_n[i].capturada == 0) {
				contador = contador + revision_reina(tablero, pieza->reina_n[i].fila, pieza->reina_n[i].columna, pieza->rey.fila, pieza->rey.columna, pieza->reina_n[i].valor);
			}
		}
	}
	if (contador > 0) {
		return 1;
	}
	else {
		return 0;
	}
}
