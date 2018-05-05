#include<stdio.h>
#define DIM 10


struct pieza {
	int fila;
	int columna;
	int revisar;
	int capturada;
	int valor;
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


void main() {

	//PIEZAS BLANCAS
	struct pieza peon[8];
	struct pieza caballo[2];
	struct pieza alfil[2];
	struct pieza torre[2];
	struct pieza reina;
	struct pieza rey;

	//PIEZAS NEGRAS
	struct pieza peon_n[8];
	struct pieza caballo_n[2];
	struct pieza alfil_n[2];
	struct pieza torre_n[2];
	struct pieza reina_n;
	struct pieza rey_n;

	//VARAIBLES DEL MOVIMIENTO
	char pieza_elegida; //para el switch
	int fila_aux; //Posicion del destino
	int columna_aux; // Posicion de destino
	char aux_columna;
	int num_piezas;
	int mov_producido; //se ha movido una pieza
	int contador_mov; //contador blancas o negras
	int captura;
	int valorCaida;

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
	for (i = 0; i < 8; i++) {
		peon[i].capturada = 0;
		peon[i].valor = 1;
		peon[i].fila = 7;
		peon[i].columna = i + 1;
		tablero_piezas[peon[i].fila][peon[i].columna] = peon[i].valor;
	}
	for (i = 0; i < 2; i++) {
		caballo[i].valor = 2;
		caballo[i].fila = 8;
		caballo[i].capturada = 0;

		alfil[i].valor = 3;
		alfil[i].fila = 8;
		alfil[i].capturada = 0;

		torre[i].valor = 4;
		torre[i].fila = 8;
		torre[i].capturada = 0;

		if (i == 0) {
			alfil[i].columna = 3;
			caballo[i].columna = 2;
			torre[i].columna = 1;
		}
		else {
			alfil[i].columna = 6;
			caballo[i].columna = 7;
			torre[i].columna = 8;
		}
		tablero_piezas[alfil[i].fila][alfil[i].columna] = alfil[i].valor;
		tablero_piezas[caballo[i].fila][caballo[i].columna] = caballo[i].valor;
		tablero_piezas[torre[i].fila][torre[i].columna] = torre[i].valor;
	}
	rey.capturada = 0;
	rey.valor = 5;
	rey.fila = 8;
	rey.columna = 5;
	tablero_piezas[rey.fila][rey.columna] = rey.valor;
	reina.capturada = 0;
	reina.valor = 6;
	reina.fila = 8;
	reina.columna = 4;
	tablero_piezas[reina.fila][reina.columna] = reina.valor;

	//PIEZAS NEGRAS
	for (i = 0; i < 8; i++) {
		peon_n[i].capturada = 0;
		peon_n[i].valor = 12;
		peon_n[i].fila = 2;
		peon_n[i].columna = i + 1;
		tablero_piezas[peon_n[i].fila][peon_n[i].columna] = peon_n[i].valor;
	}
	for (i = 0; i < 2; i++) {
		caballo_n[i].valor = 11;
		caballo_n[i].fila = 1;
		caballo_n[i].capturada = 0;

		alfil_n[i].valor = 10;
		alfil_n[i].fila = 1;
		alfil_n[i].capturada = 0;

		torre_n[i].valor = 9;
		torre_n[i].fila = 1;
		torre_n[i].capturada = 0;
		if (i == 0) {
			alfil_n[i].columna = 3;
			caballo_n[i].columna = 2;
			torre_n[i].columna = 1;
		}
		else {
			alfil_n[i].columna = 6;
			caballo_n[i].columna = 7;
			torre_n[i].columna = 8;
		}
		tablero_piezas[alfil_n[i].fila][alfil_n[i].columna] = alfil_n[i].valor;
		tablero_piezas[caballo_n[i].fila][caballo_n[i].columna] = caballo_n[i].valor;
		tablero_piezas[torre_n[i].fila][torre_n[i].columna] = torre_n[i].valor;
	}
	rey_n.capturada = 0;
	rey_n.valor = 8;
	rey_n.fila = 1;
	rey_n.columna = 5;
	tablero_piezas[rey_n.fila][rey_n.columna] = rey_n.valor;
	reina_n.capturada = 0;
	reina_n.valor = 7;
	reina_n.fila = 1;
	reina_n.columna = 4;
	tablero_piezas[reina_n.fila][reina_n.columna] = reina_n.valor;

	//ESPECIFICA BLANCOS Y NEGROS
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

		//IMPRIME EL TABLERO FINAL
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

		if (contador_mov % 2 == 0) {
			printf("Mueven Blancas \n");
		}
		else {
			printf("Mueven Negras \n");
		}
		scanf_s("%c", &pieza_elegida);
		
		

		if (contador_mov%2== 0) {
			mov_producido = 0;
			while (mov_producido == 0) {
				switch (pieza_elegida) {
				case 'p':
				case 'P':
					pedir_destino(&columna_aux, &fila_aux);
					num_piezas = 0;
					for (i = 0; i < 8; i++) {
						peon[i].revisar = revision_peon(tablero_piezas, peon[i].fila, peon[i].columna, fila_aux, columna_aux);
						if (peon[i].revisar == 1) {
							num_piezas++;
						}
					}
					if (num_piezas > 1) {
						i = caen_en_el_mismo_sitio(&peon);

						tablero_piezas[peon[i].fila][peon[i].columna] = 0;
						peon[i].fila = fila_aux;
						peon[i].columna = columna_aux;

						tablero_piezas[peon[i].fila][peon[i].columna] = peon[i].valor;
						mov_producido = 1;
					}

					else if (num_piezas == 1) {
						for (i = 0; i < 8; i++) {
							if (peon[i].revisar == 1) {
								break;
							}
						}
						tablero_piezas[peon[i].fila][peon[i].columna] = 0;
						peon[i].fila = fila_aux;
						peon[i].columna = columna_aux;

						tablero_piezas[peon[i].fila][peon[i].columna] = peon[i].valor;
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
						caballo[i].revisar = revision_caballo(tablero_piezas, caballo[i].fila, caballo[i].columna, fila_aux, columna_aux);
						if (caballo[i].revisar == 1) {
							num_piezas++;
						}
					}
					if (num_piezas > 1) {
						i = caen_en_el_mismo_sitio(&caballo);

						tablero_piezas[caballo[i].fila][caballo[i].columna] = 0;
						caballo[i].fila = fila_aux;
						caballo[i].columna = columna_aux;

						tablero_piezas[caballo[i].fila][caballo[i].columna] = caballo[i].valor;
						mov_producido = 1;
					}

					else if (num_piezas == 1) {
						for (i = 0; i < 2; i++) {
							if (caballo[i].revisar == 1) {
								break;
							}
						}
						tablero_piezas[caballo[i].fila][caballo[i].columna] = 0;
						caballo[i].fila = fila_aux;
						caballo[i].columna = columna_aux;

						tablero_piezas[caballo[i].fila][caballo[i].columna] = caballo[i].valor;
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
						alfil[i].revisar = revision_alfil(tablero_piezas, alfil[i].fila, alfil[i].columna, fila_aux, columna_aux);
						if (alfil[i].revisar == 1) {
							num_piezas = 1;
						}
					}
					if (num_piezas == 1) {
						for (i = 0; i < 2; i++) {
							if (alfil[i].revisar == 1) {
								break;
							}
						}
						tablero_piezas[alfil[i].fila][alfil[i].columna] = 0;
						alfil[i].fila = fila_aux;
						alfil[i].columna = columna_aux;

						tablero_piezas[alfil[i].fila][alfil[i].columna] = alfil[i].valor;
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
						torre[i].revisar = revision_torre(tablero_piezas, torre[i].fila, torre[i].columna, fila_aux, columna_aux);
						if (torre[i].revisar == 1) {
							num_piezas++;
						}
					}
					if (num_piezas > 1) {
						i = caen_en_el_mismo_sitio(&torre);

						tablero_piezas[torre[i].fila][torre[i].columna] = 0;
						torre[i].fila = fila_aux;
						torre[i].columna = columna_aux;

						tablero_piezas[torre[i].fila][torre[i].columna] = torre[i].valor;
						mov_producido = 1;	
					}

					else if (num_piezas == 1) {
						for (i = 0; i < 2; i++) {
							if (torre[i].revisar == 1) {
								break;
							}
						}
						tablero_piezas[torre[i].fila][torre[i].columna] = 0;
						torre[i].fila = fila_aux;
						torre[i].columna = columna_aux;

						tablero_piezas[torre[i].fila][torre[i].columna] = torre[i].valor;
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
					reina.revisar = revision_reina(tablero_piezas, reina.fila, reina.columna, fila_aux, columna_aux);

					if (reina.revisar == 1) {
						tablero_piezas[reina.fila][reina.columna] = 0;
						reina.fila = fila_aux;
						reina.columna = columna_aux;

						tablero_piezas[reina.fila][reina.columna] = reina.valor;
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
					rey.revisar = revision_rey(tablero_piezas, rey.fila, rey.columna, fila_aux, columna_aux);

					if (rey.revisar == 1) {

						tablero_piezas[rey.fila][rey.columna] = 0;
						rey.fila = fila_aux;
						rey.columna = columna_aux;

						tablero_piezas[rey.fila][rey.columna] = rey.valor;
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
			mov_producido = 0;
			while (mov_producido == 0) {
				switch (pieza_elegida) {
				case 'p':
				case 'P':
					pedir_destino(&columna_aux, &fila_aux);
					num_piezas = 0;
					for (i = 0; i < 8; i++) {
						peon_n[i].revisar = revision_peon_n(tablero_piezas, peon_n[i].fila, peon_n[i].columna, fila_aux, columna_aux);
						if (peon_n[i].revisar == 1) {
							num_piezas++;
						}
					}
					if (num_piezas > 1) {
						i = caen_en_el_mismo_sitio(&peon_n);

						tablero_piezas[peon_n[i].fila][peon_n[i].columna] = 0;

						peon_n[i].fila = fila_aux;
						peon_n[i].columna = columna_aux;

						tablero_piezas[peon_n[i].fila][peon_n[i].columna] = peon_n[i].valor;
						mov_producido = 1;
						getchar();
					}

					else if (num_piezas == 1) {
						for (i = 0; i < 8; i++) {
							if (peon_n[i].revisar == 1) {
								break;
							}
						}
						tablero_piezas[peon_n[i].fila][peon_n[i].columna] = 0;

						peon_n[i].fila = fila_aux;
						peon_n[i].columna = columna_aux;

						tablero_piezas[peon_n[i].fila][peon_n[i].columna] = peon_n[i].valor;
						mov_producido = 1;
						getchar();
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
						caballo_n[i].revisar = revision_caballo(tablero_piezas, caballo_n[i].fila, caballo_n[i].columna, fila_aux, columna_aux);
						if (caballo_n[i].revisar == 1) {
							num_piezas++;
						}
					}
					if (num_piezas > 1) {
						i = caen_en_el_mismo_sitio(&caballo);

						tablero_piezas[caballo_n[i].fila][caballo_n[i].columna] = 0;

						caballo_n[i].fila = fila_aux;
						caballo_n[i].columna = columna_aux;

						tablero_piezas[caballo_n[i].fila][caballo_n[i].columna] = caballo[i].valor;
						mov_producido = 1;
						getchar();
					}

					else if (num_piezas == 1) {
						for (i = 0; i < 2; i++) {
							if (caballo_n[i].revisar == 1) {
								break;
							}
						}
						tablero_piezas[caballo_n[i].fila][caballo_n[i].columna] = 0;

						caballo_n[i].fila = fila_aux;
						caballo_n[i].columna = columna_aux;

						tablero_piezas[caballo_n[i].fila][caballo_n[i].columna] = caballo_n[i].valor;
						mov_producido = 1;
						getchar();
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
						alfil_n[i].revisar = revision_alfil(tablero_piezas, alfil_n[i].fila, alfil_n[i].columna, fila_aux, columna_aux);
						if (alfil_n[i].revisar == 1) {
							num_piezas = 1;
						}
					}
					if (num_piezas == 1) {
						for (i = 0; i < 2; i++) {
							if (alfil_n[i].revisar == 1) {
								break;
							}
						}
						tablero_piezas[alfil_n[i].fila][alfil_n[i].columna] = 0;

						alfil_n[i].fila = fila_aux;
						alfil_n[i].columna = columna_aux;

						tablero_piezas[alfil_n[i].fila][alfil_n[i].columna] = alfil_n[i].valor;
						mov_producido = 1;
						getchar();
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
						torre_n[i].revisar = revision_torre(tablero_piezas, torre_n[i].fila, torre_n[i].columna, fila_aux, columna_aux);
						if (torre_n[i].revisar == 1) {
							num_piezas++;
						}
					}
					if (num_piezas > 1) {
						i = caen_en_el_mismo_sitio(&torre);

						tablero_piezas[torre_n[i].fila][torre_n[i].columna] = 0;

						torre_n[i].fila = fila_aux;
						torre_n[i].columna = columna_aux;

						tablero_piezas[torre_n[i].fila][torre_n[i].columna] = torre_n[i].valor;
						mov_producido = 1;
						getchar();
					}

					else if (num_piezas == 1) {
						for (i = 0; i < 2; i++) {
							if (torre_n[i].revisar == 1) {
								break;
							}
						}
						tablero_piezas[torre_n[i].fila][torre_n[i].columna] = 0;

						torre_n[i].fila = fila_aux;
						torre_n[i].columna = columna_aux;

						tablero_piezas[torre_n[i].fila][torre_n[i].columna] = torre_n[i].valor;
						mov_producido = 1;
						getchar();
					}
					else {
						printf("Movimiento no valido \n");
						system("pause");
					}
					break;

				case 'r':
				case 'R':

					pedir_destino(&columna_aux, &fila_aux);
					reina_n.revisar = revision_reina(tablero_piezas, reina_n.fila, reina_n.columna, fila_aux, columna_aux);

					if (reina_n.revisar == 1) {
						tablero_piezas[reina_n.fila][reina_n.columna] = 0;

						reina_n.fila = fila_aux;
						reina_n.columna = columna_aux;

						tablero_piezas[reina_n.fila][reina_n.columna] = reina_n.valor;
						mov_producido = 1;
						getchar();
					}
					else {
						printf("Movimiento no valido \n");
						system("pause");
					}
					break;
				case 'k':
				case 'K':

					pedir_destino(&columna_aux, &fila_aux);
					rey_n.revisar = revision_rey(tablero_piezas, rey_n.fila, rey_n.columna, fila_aux, columna_aux);

					if (rey_n.revisar == 1) {

						tablero_piezas[rey_n.fila][rey_n.columna] = 0;

						rey_n.fila = fila_aux;
						rey_n.columna = columna_aux;

						tablero_piezas[rey_n.fila][rey_n.columna] = rey_n.valor;
						mov_producido = 1;
						getchar();
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
		contador_mov++;
	
	} while (1);

	system("pause");
}

void pedir_destino(int *columna_aux, int *fila_aux) {
	char aux_columna;
	printf("Introduzca la columna:");
	getchar();
	scanf_s("%c", &aux_columna);
	printf("Introduzca la fila:");
	scanf_s("%d", fila_aux);

	*columna_aux = aux_columna - 'a' + 1;
	*fila_aux = 9 - *fila_aux;
}

int revision_peon(int tablero[DIM][DIM], int fila, int columna, int fila_aux, int   columna_aux) {
	if ((tablero[fila_aux][columna_aux] <= 6) && (tablero[fila_aux][columna_aux] >= 1)) {
		return 0;
	}
	if ((fila == fila_aux + 1) && (columna == columna_aux)) {
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
	if ((tablero[fila_aux][columna_aux] <= 6) && (tablero[fila_aux][columna_aux] >= 1)) {
		return 0;
	}
	if ((fila == fila_aux - 1) && (columna == columna_aux)) {
		return 1;
	}
	else if (((fila == fila_aux - 1) && (columna == columna_aux - 1)) && (tablero[fila_aux][columna_aux] < 7)&& (tablero[fila_aux][columna_aux] != 0)) {
		return 1;
	}
	else if (((fila == fila_aux - 1) && (columna == columna_aux + 1)) && (tablero[fila_aux][columna_aux] < 7) && (tablero[fila_aux][columna_aux] != 0)) {
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

