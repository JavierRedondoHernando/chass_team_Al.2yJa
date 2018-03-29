#include <stdio.h> 
#define DIM2 9

void main(){
	int piezas[DIM2][DIM2];
	int x, x1, y, y1;
	int numpiezas, existe_pieza;
	char pieza_in;
	int pieza;
	char y_0, y1_0;
	for (x = 0; x < DIM2; x++) {
		for (y = 0; y < DIM2; y++) {
			piezas[x][y] = 0;
		}
	}
	piezas[7][7] = 2;
	piezas[8][8] = 2;
	for (x = 0; x < DIM2; x++) {
		for (y = 0; y < DIM2; y++) {
			printf("%d\t", piezas[x][y]);
		}
		printf("\n\n\n");
	}
	do {
		existe_pieza = 0;
		printf("Que pieza quiere mover?  ");
		scanf_s("%c",&pieza_in);
		if (pieza_in == '\n') {
			system("cls");
			printf("Que pieza quiere mover?  ");
			scanf_s("%c", &pieza_in);
		}
		if (pieza_in == 'a') {
			pieza = 2;
		}
		printf("\nIntroduzca la primera coordenada de destino: ");
		scanf_s("%d", &x1);
		printf("\nIntroduzca la segunda coordenada de destino: ");
		getchar();
		scanf_s("%c", &y1_0);
		system("cls");
		x1 = 9 - x1;
		y1 = y1_0 - 'a' + 1;
		if (pieza == 2) {
			numpiezas = 0;
			for (x = 0; x < DIM2; x++) {
				for (y = 0; y < DIM2; y++) {
					if ((piezas[x][y] == 2) && ((x - x1)*(x - x1) == (y - y1)*(y - y1))) {
						numpiezas++;
					}
				}
			}
		}
			if (numpiezas > 1) {
				printf("Hay mas de una combinacion, especifique las coordenadas de la pieza\n");
				printf("Introduzca las coordenadas iniciales,\nPrimera coordenada: ");
				scanf_s("%d", &x);
				printf("\nIntroduzca la segunda coordenada: ");
				getchar();
				scanf_s("%c", &y_0);
				x = 9 - x;
				y = y_0 - 'a' + 1;
				switch(piezas[x][y]) {
				case 2:
					piezas[x][y] = 0;
					piezas[x1][y1] = 2;
					existe_pieza++;
					break;
				default:
					printf("Hay no hay un alfil.\n");
				}
			}
			else if ((numpiezas == 0) && (pieza==2)) {
				printf("No hay alfiles que se puedan mover ahi.\n");
			}
			else {
				if (pieza == 2) {
					for (x = 0; x < DIM2; x++) {
						for (y = 0; y < DIM2; y++) {
							if ((piezas[x][y] == 2) && ((x - x1)*(x - x1) == (y - y1)*(y - y1))) {
								break;
							}
						}
						if ((piezas[x][y] == 2) && ((x - x1)*(x - x1) == (y - y1)*(y - y1))) {
							break;
						}
					}
				}
				switch (piezas[x][y]) {
				case 2:
					piezas[x][y] = 0;
					piezas[x1][y1] = 2;
					existe_pieza++;
					break;
				}
			}
		for (x = 0; x < DIM2; x++) {
			for (y = 0; y < DIM2; y++) {
				printf("%d\t", piezas[x][y]);
			}
			printf("\n\n\n");
		}
		system("pause");
	} while (existe_pieza != 1);
	
	system("pause");
}
