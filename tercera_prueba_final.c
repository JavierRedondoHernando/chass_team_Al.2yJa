#include<stdio.h>
#define DIM 10
#define MAX_PIEZAS 10
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


void pedir_destino(int *columna_aux, int *fila_aux);
int revision_peon(int tablero[DIM][DIM], int fila, int columna, int fila_aux, int columna_aux);
int revision_peon_n(int tablero[DIM][DIM], int fila, int columna, int fila_aux, int columna_aux);
int revision_caballo(int tablero[DIM][DIM], int fila, int columna, int fila_aux, int columna_aux);
int revision_alfil(int tablero[DIM][DIM], int fila, int columna, int fila_aux, int columna_aux);
int revision_torre(int tablero[DIM][DIM], int fila, int columna, int fila_aux, int columna_aux);
int revision_reina(int tablero[DIM][DIM], int fila, int columna, int fila_aux, int columna_aux);
int revision_rey(int tablero[DIM][DIM], int fila, int columna, int fila_aux, int columna_aux);
int caen_en_el_mismo_sitio(struct pieza *pieza);
void imprimir_tablero(char tablero_color[DIM][DIM], int tablero_piezas[DIM][DIM]);
void pieza_capturada(int tablero[DIM][DIM], struct todas *piezas, struct pieza *pieza, int fila_aux, int columna_aux);
void coronar(int tablero[DIM][DIM], struct todas *pieza);

void main() {

	struct todas piezas;

	/*//PIEZAS BLANCAS
	                                    todo esto ya no hace falta, lo podemos borrar
	struct pieza peon[MAX_PIEZAS];
	struct pieza caballo[MAX_PIEZAS];
	struct pieza alfil[MAX_PIEZAS];
	struct pieza torre[MAX_PIEZAS];
	struct pieza reina[MAX_PIEZAS];
	struct pieza rey;

	//PIEZAS NEGRAS
	struct pieza peon_n[MAX_PIEZAS];
	struct pieza caballo_n[MAX_PIEZAS];
	struct pieza alfil_n[MAX_PIEZAS];
	struct pieza torre_n[MAX_PIEZAS];
	struct pieza reina_n[MAX_PIEZAS];
	struct pieza rey_n;
	*/
	//VARAIBLES DEL MOVIMIENTO
	char pieza_elegida; //para el switch
	int fila_aux; //Posicion del destino
	int columna_aux; // Posicion de destino
	char aux_columna;
	int num_piezas;
	int mov_producido; //se ha movido una pieza
	int contador_mov; //contador blancas o negras

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
		if (i == 1) {
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
				tablero_color[fila][columna] = '*';
			}
			else {
				tablero_color[fila][columna] = '.';
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
			printf("Mueven Blancas \n\n\n");
			mov_producido = 0;
			while (mov_producido == 0) {

				imprimir_tablero(tablero_color, tablero_piezas);

				printf("Elija pieza: ");
				scanf_s("%c", &pieza_elegida);
				getchar();

				switch (pieza_elegida) {
				case 'p':
				case 'P':
					pedir_destino(&columna_aux, &fila_aux);
					num_piezas = 0;
					for (i = 0; i < 8; i++) {
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
						for (i = 0; i < 8; i++) {
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
					for (i = 0; i < 2; i++) {
						if (piezas.caballo[i].capturada == 0) {
							piezas.caballo[i].revisar = revision_caballo(tablero_piezas, piezas.caballo[i].fila, piezas.caballo[i].columna, fila_aux, columna_aux);
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
						for (i = 0; i < 2; i++) {
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
					for (i = 0; i < 2; i++) {
						if (piezas.alfil[i].capturada == 0) {
							piezas.alfil[i].revisar = revision_alfil(tablero_piezas, piezas.alfil[i].fila, piezas.alfil[i].columna, fila_aux, columna_aux);
							if (piezas.alfil[i].revisar == 1) {
								num_piezas = 1;
							}
						}
					}
					if (num_piezas == 1) {
						for (i = 0; i < 2; i++) {
							if (piezas.alfil[i].revisar == 1) {
								break;
							}
						}

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
					for (i = 0; i < 2; i++) {
						if (piezas.torre[i].capturada == 0) {
							piezas.torre[i].revisar = revision_torre(tablero_piezas, piezas.torre[i].fila, piezas.torre[i].columna, fila_aux, columna_aux);
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
						for (i = 0; i < 2; i++) {
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

					for (i = 0; i < 2; i++) {
						if (piezas.reina[i].capturada == 0) {
							piezas.reina[i].revisar = revision_reina(tablero_piezas, piezas.reina[i].fila, piezas.reina[i].columna, fila_aux, columna_aux);
							if (piezas.reina[i].revisar == 1) {
								num_piezas++;
							}
						}
					}
					if (piezas.reina[i].revisar == 1) {

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
					piezas.rey.revisar = revision_rey(tablero_piezas, piezas.rey.fila, piezas.rey.columna, fila_aux, columna_aux);

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
				system("cls");
			}
		}
		else {
			printf("Mueven Negras \n\n\n");
			mov_producido = 0;
			while (mov_producido == 0) {

				imprimir_tablero(tablero_color, tablero_piezas);

				printf("Elija pieza: ");
				scanf_s("%c", &pieza_elegida);
				getchar();

				switch (pieza_elegida) {
				case 'p':
				case 'P':
					pedir_destino(&columna_aux, &fila_aux);
					num_piezas = 0;
					for (i = 0; i < 8; i++) {
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
						for (i = 0; i < 8; i++) {
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
					for (i = 0; i < 2; i++) {
						if (piezas.caballo_n[i].capturada == 0) {
							piezas.caballo_n[i].revisar = revision_caballo(tablero_piezas, piezas.caballo_n[i].fila, piezas.caballo_n[i].columna, fila_aux, columna_aux);
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
						for (i = 0; i < 2; i++) {
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
					for (i = 0; i < 2; i++) {
						if (piezas.alfil_n[i].capturada == 0) {
							piezas.alfil_n[i].revisar = revision_alfil(tablero_piezas, piezas.alfil_n[i].fila, piezas.alfil_n[i].columna, fila_aux, columna_aux);
							if (piezas.alfil_n[i].revisar == 1) {
								num_piezas++;
							}
						}
					}
					if (num_piezas == 1) {
						for (i = 0; i < 2; i++) {
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
					for (i = 0; i < 2; i++) {
						if (piezas.torre_n[i].capturada == 0) {
							piezas.torre_n[i].revisar = revision_torre(tablero_piezas, piezas.torre_n[i].fila, piezas.torre_n[i].columna, fila_aux, columna_aux);
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
						for (i = 0; i < 2; i++) {
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

					for (i = 0; i < 2; i++) {
						if (piezas.reina_n[i].capturada == 0) {
							piezas.reina_n[i].revisar = revision_reina(tablero_piezas, piezas.reina_n[i].fila, piezas.reina_n[i].columna, fila_aux, columna_aux);
							if (piezas.reina_n[i].revisar == 1) {
								num_piezas++;
							}
						}

						if (piezas.reina_n[i].revisar == 1) {

							pieza_capturada(tablero_piezas, &piezas, &piezas.reina_n[i], fila_aux, columna_aux);

							mov_producido = 1;
						}
						else {
							printf("Movimiento no valido \n");
							system("pause");
						}
					}
					break;
				case 'k':
				case 'K':

					pedir_destino(&columna_aux, &fila_aux);
					piezas.rey_n.revisar = revision_rey(tablero_piezas, piezas.rey_n.fila, piezas.rey_n.columna, fila_aux, columna_aux);

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
				system("cls");
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
			if (tablero_piezas[fila][columna] == 0) {
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
				printf("r\t");
			}
			else if (tablero_piezas[fila][columna] == 8) {
				printf("k\t");
			}
			else if (tablero_piezas[fila][columna] == 9) {
				printf("t\t");
			}
			else if (tablero_piezas[fila][columna] == 10) {
				printf("a\t");
			}
			else if (tablero_piezas[fila][columna] == 11) {
				printf("c\t");
			}
			else if (tablero_piezas[fila][columna] == 12) {
				printf("p\t");
			}
			else {
				printf("%d\t", tablero_piezas[fila][columna]);
			}
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
	}while ((*fila_aux < 1) || (*fila_aux > 8));

	*columna_aux = aux_columna - 'a' + 1;
	*fila_aux = 9 - *fila_aux;
}

int revision_peon(int tablero[DIM][DIM],int fila, int columna, int fila_aux, int   columna_aux) {
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

int revision_caballo(int tablero[DIM][DIM], int fila, int columna, int fila_aux, int columna_aux) {
	if ((tablero[fila_aux][columna_aux] <= 6) && (tablero[fila_aux][columna_aux] >= 1)) {
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

int revision_alfil(int tablero[DIM][DIM], int fila, int columna, int fila_aux, int columna_aux) {
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
		if ((tablero[fila_aux][columna_aux] <= 6) && (tablero[fila_aux][columna_aux] >= 1)) {
			return 0;
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

int revision_torre(int tablero[DIM][DIM], int fila, int columna, int fila_aux, int columna_aux) {
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
		if ((tablero[fila_aux][columna_aux] <= 6) && (tablero[fila_aux][columna_aux] >= 1)) {
			return 0;
		}
		else if ((fila == fila_aux) && (columna != columna_aux)) {
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

int revision_reina(int tablero[DIM][DIM], int fila, int columna, int fila_aux, int columna_aux) {
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
		if ((tablero[fila_aux][columna_aux] <= 6) && (tablero[fila_aux][columna_aux] >= 1)) {
			return 0;
		}
		else if ((fila == fila_aux) && (columna != columna_aux)) {
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

int revision_rey(int tablero[DIM][DIM], int fila, int columna, int fila_aux, int columna_aux) {
	int revision = 0;

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
	else if ((tablero[fila_aux][columna_aux] <= 6) && (tablero[fila_aux][columna_aux] >= 1)) {
		return 0;
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
