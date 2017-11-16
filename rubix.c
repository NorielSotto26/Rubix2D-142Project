#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define NSquares 9
#define NFaces 6
#define NSides 3
#define Clockwise true
#define WHITE 0
#define RED 1
#define BLUE 2
#define ORANGE 3
#define GREEN 4
#define YELLOW 5



void printCube(char **cube);
void checkCube(char **cube);
void rotate_cube(char **cube,int move,bool clockwise);

int main(){
	FILE *fp;
	char **cube,i=0,j;

								//malloc, initialize space
	cube  = (char**)malloc(NFaces*sizeof(char*));	
	for(i=0;i<NSquares;i++)
	cube[i] = (char*)malloc(NSquares*sizeof(char));

  	fp = fopen("input/3x3.txt","r");
	// fp = fopen("input/4x4.txt","r");
	// fp = fopen("input/5x5.txt","r");

	i=0;
	while(!feof(fp)){
		for (j=0;j!=NSquares;j++){
			if((j+1)%NSides!=0) fscanf(fp, "%c",&cube[i][j]);
			else fscanf(fp, "%c\n",&cube[i][j]);
		}
		i++;
	}

	printCube(cube);
	printf("MOVE: rotate_cube(cube,ORANGE,!Clockwise)\n");
	rotate_cube(cube,   ORANGE,   !Clockwise);
	printCube(cube);
	printf("MOVE: rotate_cube(cube,GREEN,Clockwise)\n");
	rotate_cube(cube,   GREEN,   Clockwise);
	printCube(cube);
	printf("MOVE: rotate_cube(cube,YELLOW,!Clockwise)\n");
	rotate_cube(cube,   YELLOW,   !Clockwise);
	printCube(cube);
	printf("MOVE: rotate_cube(cube,RED,Clockwise)\n");
	rotate_cube(cube,   RED,   Clockwise);
	printCube(cube);
	printf("MOVE: rotate_cube(cube,ORANGE,!Clockwise)\n");
	rotate_cube(cube,   ORANGE,   !Clockwise);
	printCube(cube);
	printf("\n");
	checkCube(cube);

}

void printCube(char **cube){
	int i,j,k;

	for(i=0;i!=NFaces;i++){
		for(j=0;j!=NSquares;j=j+NSides)
			switch(i){
				case 0:
					for(k=0;k!=NSides;k++) printf("  ");
					for(k=0;k!=NSides;k++) printf("%c ", cube[i][j+k]);
					printf("\n");
					break;
				case 1:
					for(k=0;k!=NSides;k++) printf("%c ", cube[i][j+k]);
					for(k=0;k!=NSides;k++) printf("%c ", cube[i+1][j+k]);
					for(k=0;k!=NSides;k++) printf("%c ", cube[i+2][j+k]);
					for(k=0;k!=NSides;k++) printf("%c ", cube[i+3][j+k]);
					printf("\n");
					break;
				case 5:
					for(k=0;k!=NSides;k++) printf("  ");
					for(k=0;k!=NSides;k++) printf("%c ", cube[i][j+k]);
					printf("\n");
					break;
				default:
					break;

			}
	}
}

void checkCube(char **cube){
	int i,j,k,equal=0;
	char temp;

	for(i=0;i!=NFaces;i++){
		for(j=0;j!=NSquares;j=j+NSides)
			switch(i){
				case 0: temp = cube[i][j];
						for(k=0;k!=NSides;k++){
							if (cube[i][j+k] != temp){
								equal = 1;
								break;
							}
						}
						break;
				case 1:	temp = cube[i][j];
						for(k=0;k!=NSides;k++){
							if (cube[i][j+k] != temp){
								equal = 1;
								break;
							}
						}
						temp = cube[i+1][j];
						for(k=0;k!=NSides;k++) {
							if (cube[i+1][j+k] != temp){
								equal = 1;
								break;
							}
						}

						temp = cube[i+2][j];
						for(k=0;k!=NSides;k++) {
							if (cube[i+2][j+k] != temp){
								equal = 1;
								break;
							}
						}

						temp = cube[i+3][j];
						for(k=0;k!=NSides;k++) {
							if (cube[i+3][j+k] != temp){
								equal = 1;
								break;
							}
						}
						break;
				case 5: temp = cube[i][j];
				        for(k=0;k!=NSides;k++) {
				        	if (cube[i][j+k] != temp){
				        		equal = 1;
								break;
							}	
				        }
				        break;
				default:break;
			}
	}
	//printf("equal?? %i \n\n", equal);
}

void rotate_face(char ** cube, int move, bool clockwise){
	int temp,i;
	if(clockwise){
		temp=cube[move][0];
		cube[move][0] = cube[move][NSquares-NSides];
		cube[move][NSquares-NSides] = cube[move][NSides*NSides-1];
		cube[move][NSides*NSides-1] = cube[move][NSides-1];
		cube[move][NSides-1] = temp;
		for(i=0;i<NSides-2;i++){
			temp=cube[move][NSides*NSides-2-i];
			cube[move][NSides*NSides-2-i] = cube[move][2*NSides-1+(NSides*i)];
			cube[move][2*NSides-1+(4*i)] = cube[move][1+i];
			cube[move][1+i] = cube[move][NSides*(NSides-1)-(NSides*(i+1))];
			cube[move][NSides*(NSides-1)-(NSides*(i+1))] = temp;
		}
	}else{
		temp=cube[move][0];
		cube[move][0]=cube[move][NSides-1];
		cube[move][NSides-1]=cube[move][NSides*NSides-1];
		cube[move][NSides*NSides-1]=cube[move][NSides*(NSides-1)];
		cube[move][NSides*(NSides-1)]=temp;
		for(i=0;i<NSides-2;i++){
			temp = cube[move][NSides*NSides-2-i];
			cube[move][NSides*NSides-2-i] = cube[move][NSides*(NSides-1)-(NSides*(i+1))];
			cube[move][NSides*(NSides-1)-(NSides*(i+1))] = cube[move][1+i];
			cube[move][1+i] = cube[move][2*NSides-1+(4*i)];
			cube[move][2*NSides-1+(4*i)] = temp;
		}

	}
}

void rotate_cube(char **cube,int move,bool clockwise){
	char temp[3];
	int i,j;
	rotate_face(cube,move,clockwise);
	switch(move){
		case 0:
			if(clockwise){
				for(i = 0; i < NSides; i++)	temp[i]=cube[1][i];
				for(i = 0; i < NSides; i++)	cube[1][i]=cube[2][i];
				for(i = 0; i < NSides; i++)	cube[2][i]=cube[3][i];
				for(i = 0; i < NSides; i++)	cube[3][i]=cube[4][i];
				for(i = 0; i < NSides; i++)	cube[4][i]=temp[i];
			}else{
				for(i = 0; i < NSides; i++)	temp[i]=cube[1][i];
				for(i = 0; i < NSides; i++)	cube[1][i]=cube[4][i];
				for(i = 0; i < NSides; i++)	cube[4][i]=cube[3][i];
				for(i = 0; i < NSides; i++)	cube[3][i]=cube[2][i];
				for(i = 0; i < NSides; i++)	cube[2][i]=temp[i];
			}
			break;
		case 1:
			if(clockwise){
				for(i = 0; i < NSides; i++)	temp[i]=cube[0][i*NSides];
				for(i = 0, j = NSides-1; i < NSides; i++, j--)	cube[0][i*NSides]=cube[4][j*NSides+(NSides-1)];
				for(i = 0, j = NSides-1; i < NSides; i++, j--)	cube[4][j*NSides+(NSides-1)]=cube[5][i*NSides];
				for(i = 0; i < NSides; i++)	cube[5][i*NSides]=cube[2][i*NSides];
				for(i = 0; i < NSides; i++)	cube[2][i*NSides]=temp[i];
			}else{
				for(i = 0, j = NSides-1; i < NSides; i++, j--)	temp[i]=cube[0][j*NSides];
				for(i = 0; i < NSides; i++)	cube[0][i*NSides]=cube[2][i*NSides];
				for(i = 0, j = NSides-1; i < NSides; i++, j--)	cube[2][i*NSides]=cube[5][j*NSides];
				for(i = 0, j = NSides-1; i < NSides; i++, j--)	cube[5][j*NSides]=cube[4][i*NSides+NSides-1];
				for(i = 0; i < NSides; i++)	cube[4][i*NSides+NSides-1]=temp[i];
			}
			break;
		case 2:
			if(clockwise){
				for(i = 0; i < NSides; i++)	temp[i]=cube[0][i+(NSquares-NSides)];
				for(i = 0, j = NSides-1; i < NSides; i++, j--)	cube[0][i+(NSquares-NSides)]=cube[1][j*NSides+(NSides-1)];
				for(i = 0; i < NSides; i++)	cube[1][i*NSides+NSides-1]=cube[5][i];
				for(i = 0, j = NSides-1; i < NSides; i++, j--)	cube[5][i]=cube[3][j*NSides];
				for(i = 0; i < NSides; i++)	cube[3][i*NSides]=temp[i];
			}else{
				for(i = 0, j = NSides-1; i < NSides; i++, j--)	temp[i]=cube[0][j+(NSquares-NSides)];
				for(i = 0; i < NSides; i++)	cube[0][i+(NSquares-NSides)]=cube[3][i*NSides];
				for(i = 0, j = NSides-1; i < NSides; i++, j--)	cube[3][i*NSides]=cube[5][j];
				for(i = 0; i < NSides; i++)	cube[5][i]=cube[1][i*NSides+NSides-1];
				for(i = 0; i < NSides; i++)	cube[1][i*NSides+NSides-1]=temp[i];
			}
			break;
		case 3:
			if(clockwise){
				for(i = 0, j = NSides-1; i < NSides; i++, j--)	temp[i]=cube[0][j*NSides+(NSides-1)];
				for(i = 0; i < NSides; i++)	cube[0][i*NSides+NSides-1]=cube[2][i*NSides+NSides-1];
				for(i = 0; i < NSides; i++)	cube[2][i*NSides+NSides-1]=cube[5][i*NSides+NSides-1];
				for(i = 0, j = NSides-1; i < NSides; i++, j--)	cube[5][i*NSides+NSides-1]=cube[4][j*NSides];
				for(i = 0; i < NSides; i++)	cube[4][i*NSides]=temp[i];
			}else{
				for(i = 0; i < NSides; i++)	temp[i]=cube[0][i*NSides+NSides-1];
				for(i = 0, j = NSides-1; i < NSides; i++, j--)	cube[0][i*NSides+NSides-1]=cube[4][j*NSides];
				for(i = 0, j = NSides-1; i < NSides; i++, j--)	cube[4][i*NSides]=cube[5][j*NSides+(NSides-1)];
				for(i = 0; i < NSides; i++)	cube[5][i*NSides+NSides-1]=cube[2][i*NSides+NSides-1];
				for(i = 0; i < NSides; i++)	cube[2][i*NSides+NSides-1]=temp[i];
			}
			break;
		case 4:
			if(clockwise){
				for(i = 0, j = NSides-1; i < NSides; i++, j--)	temp[i]=cube[0][j];
				for(i = 0; i < NSides; i++)	cube[0][i]=cube[3][i*NSides+NSides-1];
				for(i = 0, j = NSides-1; i < NSides; i++, j--)	cube[3][i*NSides+NSides-1]=cube[5][j+(NSquares-NSides)];
				for(i = 0; i < NSides; i++)	cube[5][i+(NSquares-NSides)]=cube[1][i*NSides];
				for(i = 0; i < NSides; i++)	cube[1][i*NSides]=temp[i];
			}else{
				for(i = 0; i < NSides; i++)	temp[i]=cube[0][i];
				for(i = 0, j = NSides-1; i < NSides; i++, j--)	cube[0][i]=cube[1][j*NSides];
				for(i = 0; i < NSides; i++)	cube[1][i*NSides]=cube[5][i+(NSquares-NSides)];
				for(i = 0, j = NSides-1; i < NSides; i++, j--)	cube[5][i+(NSquares-NSides)]=cube[3][j*NSides+(NSides-1)];
				for(i = 0; i < NSides; i++)	cube[3][i*NSides+NSides-1]=temp[i];
			}
			break;
		case 5:
			if(clockwise){
				for(i = 0; i < NSides; i++)	temp[i]=cube[4][i+(NSquares-NSides)];
				for(i = 0; i < NSides; i++)	cube[4][i+(NSquares-NSides)]=cube[3][i+(NSquares-NSides)];
				for(i = 0; i < NSides; i++)	cube[3][i+(NSquares-NSides)]=cube[2][i+(NSquares-NSides)];
				for(i = 0; i < NSides; i++)	cube[2][i+(NSquares-NSides)]=cube[1][i+(NSquares-NSides)];
				for(i = 0; i < NSides; i++)	cube[1][i+(NSquares-NSides)]=temp[i];
			}else{
				for(i = 0; i < NSides; i++)	temp[i]=cube[4][i+(NSquares-NSides)];
				for(i = 0; i < NSides; i++)	cube[4][i+(NSquares-NSides)]=cube[1][i+(NSquares-NSides)];
				for(i = 0; i < NSides; i++)	cube[1][i+(NSquares-NSides)]=cube[2][i+(NSquares-NSides)];
				for(i = 0; i < NSides; i++)	cube[2][i+(NSquares-NSides)]=cube[3][i+(NSquares-NSides)];
				for(i = 0; i < NSides; i++)	cube[3][i+(NSquares-NSides)]=temp[i];
			}
			break;
		default:
			break;	
	}
}
