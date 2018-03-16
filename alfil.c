#include <stdio.h> //recomiendo usas desde aqui...
#define DIM2 9
void main() {
	int piezas[DIM2][DIM2];
	int x, x1;
	char y_0, y1_0;
	int y, y1; //hacen falta para poder hacer las cuentas ya que recogemos un char pero queremos el int
	for (x = 0; x < DIM2; x++) {
		for (y = 0; y < DIM2; y++) {
				piezas[x][y] = 0;
		}
	}
	piezas[8][8] = 2;//esta es solo la posición del alfil
	while (1) {
		scanf_s("%d %c", &x, &y_0);//posicion de la pieza en las coordenadas de ajedrez
		scanf_s("%d %c", &x1, &y1_0);//la posicion de ajedrez a la que te lo quieres llevar
		y = y_0 - 'a' + 1;//transforma la y deletra a la coordenada que queremos
		y1 = y1_0 - 'a' + 1;
		//...hasta aqui para todas las piezas, es solo la lógica para llamar a los elementos de la matriz
		if ((piezas [9 - x][y] == 2) && ((x - x1)*(x - x1) == (y - y1)*(y - y1))) {//este condicional es basicamente toda la logica del alfil
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
