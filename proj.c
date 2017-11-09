#include <stdio.h>
#include <stdlib.h>

int main(){
	int i, j;
	int cols = 3, rows = 3, side = 6;
	char rubik[rows*side+1][cols];

	FILE *fp = fopen("input.in", "r");


	for(i = 0;i < cols*side; i++){		//file reading
		for(j = 0; j < rows+1; j++){
			rubik[i][j] = fgetc(fp);
		}
	}

	fclose(fp);

	for(i=0;i<side*rows;i++){
		for(j=0;j<cols;j++){
			printf("%c", rubik[i][j]);
		}
		printf("\n");
	}

	return 0;
}