#include <stdio.h> 
#define DIM2 9
void main() {
	int piezas[DIM2][DIM2];
	int x, x1;
	char y_0, y1_0;
	int y, y1;
	for (x = 0; x < DIM2; x++) {
		for (y = 0; y < DIM2; y++) {
				piezas[x][y] = 0;
		}
	}
	piezas[8][8] = 2;
	while (1) {
		scanf_s("%d %c", &x, &y_0);
		scanf_s("%d %c", &x1, &y1_0);
		y = y_0 - 'a' + 1;
		y1 = y1_0 - 'a' + 1;
		
		if ((piezas [9 - x][y] == 2) && ((x - x1)*(x - x1) == (y - y1)*(y - y1))) {
			piezas[9 - x][y] = 0;
			piezas[9 - x1][y1] = 2;
		}
		for (x = 0; x < DIM2; x++) {
			for (y = 0; y < DIM2; y++) {
				printf("%d\t", piezas[x][y]);
			}
			printf("\n\n\n");
		}
		system("pause");
	}
}
