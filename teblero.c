#include <stdio.h>
#define DIM 10
void main() {
	char tablero[DIM][DIM];
	char indice_abajo = 'a', indice_arriba = 'a';
	int x, y, indice_derecha, indice_izquierda = 0;
	for (x = 0; x < DIM; x++) {
		for (y = 0; y < DIM; y++) {
			if ((x + 1 * y + 1) % 2 == 0) {
				tablero[x][y] = 0;
			}
			else {
				tablero[x][y] = 1;
			}
		}
	}
	indice_abajo = 'a';
	indice_derecha = 8;
	indice_arriba = 'a';
	indice_izquierda = 8;
	for (x = 0; x < DIM; x++) {
		for (y = 0; y < DIM; y++) {
			if ((x == 0 && y == 0) || (x == 0 && y == 9) || (x == 9 && y == 0) || (x == 9 && y == 9)) {
				printf(" \t");
			}
			else if (x == 0) {
				printf("%c\t", indice_arriba);
				indice_arriba++;
			}
			else if (x == 9) {
				printf("%c\t", indice_abajo);
				indice_abajo++;
			}
			else if (y == 0) {
				printf("%d|\t", indice_izquierda);
				indice_izquierda--;
			}
			else if (y == 9) {
				printf("|%d\t", indice_derecha);
				indice_derecha--;
			}
			else if (tablero[x][y] == 0) {
				printf("*\t");
			}
			else if (tablero[x][y] == 1) {
				printf("'\t");
			}
		}
		printf("\n\n\n");
	}
	system("pause");
}
