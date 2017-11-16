#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define NSides 9
#define NFaces 6
#define Clockwise true
#define WHITE 0
#define RED 1
#define BLUE 2
#define ORANGE 3
#define GREEN 4
#define YELLOW 5



void printCube(char **cube);
void rotate_cube(char **cube,int move,bool clockwise);

int main(){
	FILE *fp;
	char **cube,i=0,j;

								//malloc, initialize space
	cube  = (char**)malloc(NFaces*sizeof(char*));	
	for(i=0;i<NSides;i++)
		cube[i] = (char*)malloc(NSides*sizeof(char));

	fp = fopen("input.txt","r");
	char a,b,c;

	i=0;
	while(!feof(fp)){
		fscanf(fp, "%c%c%c\n",&a,&b,&c);
		cube[i][0] = a;
		cube[i][1] = b;
		cube[i][2] = c;
		fscanf(fp, "%c%c%c\n",&a,&b,&c);
		cube[i][3] = a;
		cube[i][4] = b;
		cube[i][5] = c;
		fscanf(fp, "%c%c%c\n",&a,&b,&c);
		cube[i][6] = a;
		cube[i][7] = b;
		cube[i][8] = c;
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
}

void printCube(char **cube){
	int i,j;

	for(i=0;i!=NFaces;i++){
		for(j=0;j!=NSides;j=j+3)
			switch(i){
				case 0:
					printf("      %c %c %c\n", cube[i][j],cube[i][j+1],cube[i][j+2]);
					break;
				case 1:
					printf("%c %c %c ", cube[i][j],cube[i][j+1],cube[i][j+2]);
					printf("%c %c %c ", cube[i+1][j],cube[i+1][j+1],cube[i+1][j+2]);
					printf("%c %c %c ", cube[i+2][j],cube[i+2][j+1],cube[i+2][j+2]);
					printf("%c %c %c\n", cube[i+3][j],cube[i+3][j+1],cube[i+3][j+2]);
					break;
				case 5:
					printf("      %c %c %c\n", cube[i][j],cube[i][j+1],cube[i][j+2]);
					break;
				default:
					break;

			}
	}
}

void rotate_face(char ** cube, int move, bool clockwise){
	int temp;
	if(clockwise){
		temp=cube[move][0];
		cube[move][0]=cube[move][6];
		cube[move][6]=cube[move][8];
		cube[move][8]=cube[move][2];
		cube[move][2]=temp;
		temp=cube[move][7];
		cube[move][7]=cube[move][5];
		cube[move][5]=cube[move][1];
		cube[move][1]=cube[move][3];
		cube[move][3]=temp;
	}else{
		temp=cube[move][0];
		cube[move][0]=cube[move][2];
		cube[move][2]=cube[move][8];
		cube[move][8]=cube[move][6];
		cube[move][6]=temp;
		temp=cube[move][7];
		cube[move][7]=cube[move][3];
		cube[move][3]=cube[move][1];
		cube[move][1]=cube[move][5];
		cube[move][5]=temp;

	}
}

void rotate_cube(char **cube,int move,bool clockwise){
	char temp[3];
	int i,j;
	rotate_face(cube,move,clockwise);
	switch(move){
		case 0:
			if(clockwise){
				for(i = 0; i < 3; i++)	temp[i]=cube[1][i];
				for(i = 0; i < 3; i++)	cube[1][i]=cube[2][i];
				for(i = 0; i < 3; i++)	cube[2][i]=cube[3][i];
				for(i = 0; i < 3; i++)	cube[3][i]=cube[4][i];
				for(i = 0; i < 3; i++)	cube[4][i]=temp[i];
			}else{
				for(i = 0; i < 3; i++)	temp[i]=cube[1][i];
				for(i = 0; i < 3; i++)	cube[1][i]=cube[4][i];
				for(i = 0; i < 3; i++)	cube[4][i]=cube[3][i];
				for(i = 0; i < 3; i++)	cube[3][i]=cube[2][i];
				for(i = 0; i < 3; i++)	cube[2][i]=temp[i];
			}
			break;
		case 1:
			if(clockwise){
				for(i = 0; i < 3; i++)	temp[i]=cube[0][i*3];
				for(i = 0, j = 2; i < 3; i++, j--)	cube[0][i*3]=cube[4][j*3+2];
				for(i = 0, j = 2; i < 3; i++, j--)	cube[4][j*3+2]=cube[5][i*3];
				for(i = 0; i < 3; i++)	cube[5][i*3]=cube[2][i*3];
				for(i = 0; i < 3; i++)	cube[2][i*3]=temp[i];
			}else{
				for(i = 0, j = 2; i < 3; i++, j--)	temp[i]=cube[0][j*3];
				for(i = 0; i < 3; i++)	cube[0][i*3]=cube[2][i*3];
				for(i = 0, j = 2; i < 3; i++, j--)	cube[2][i*3]=cube[5][j*3];
				for(i = 0, j = 2; i < 3; i++, j--)	cube[5][j*3]=cube[4][i*3+2];
				for(i = 0; i < 3; i++)	cube[4][i*3+2]=temp[i];
			}
			break;
		case 2:
			if(clockwise){
				for(i = 0; i < 3; i++)	temp[i]=cube[0][i+6];
				for(i = 0, j = 2; i < 3; i++, j--)	cube[0][i+6]=cube[1][j*3+2];
				for(i = 0; i < 3; i++)	cube[1][i*3+2]=cube[5][i];
				for(i = 0, j = 2; i < 3; i++, j--)	cube[5][i]=cube[3][j*3];
				for(i = 0; i < 3; i++)	cube[3][i*3]=temp[i];
			}else{
				for(i = 0, j = 2; i < 3; i++, j--)	temp[i]=cube[0][j+6];
				for(i = 0; i < 3; i++)	cube[0][i+6]=cube[3][i*3];
				for(i = 0, j = 2; i < 3; i++, j--)	cube[3][i*3]=cube[5][j];
				for(i = 0; i < 3; i++)	cube[5][i]=cube[1][i*3+2];
				for(i = 0; i < 3; i++)	cube[1][i*3+2]=temp[i];
			}
			break;
		case 3:
			if(clockwise){
				for(i = 0, j = 2; i < 3; i++, j--)	temp[i]=cube[0][j*3+2];
				for(i = 0; i < 3; i++)	cube[0][i*3+2]=cube[2][i*3+2];
				for(i = 0; i < 3; i++)	cube[2][i*3+2]=cube[5][i*3+2];
				for(i = 0, j = 2; i < 3; i++, j--)	cube[5][i*3+2]=cube[4][j*3];
				for(i = 0; i < 3; i++)	cube[4][i*3]=temp[i];
			}else{
				for(i = 0; i < 3; i++)	temp[i]=cube[0][i*3+2];
				for(i = 0, j = 2; i < 3; i++, j--)	cube[0][i*3+2]=cube[4][j*3];
				for(i = 0, j = 2; i < 3; i++, j--)	cube[4][i*3]=cube[5][j*3+2];
				for(i = 0; i < 3; i++)	cube[5][i*3+2]=cube[2][i*3+2];
				for(i = 0; i < 3; i++)	cube[2][i*3+2]=temp[i];
			}
			break;
		case 4:
			if(clockwise){
				for(i = 0, j = 2; i < 3; i++, j--)	temp[i]=cube[0][j];
				for(i = 0; i < 3; i++)	cube[0][i]=cube[3][i*3+2];
				for(i = 0, j = 2; i < 3; i++, j--)	cube[3][i*3+2]=cube[5][j+6];
				for(i = 0; i < 3; i++)	cube[5][i+6]=cube[1][i*3];
				for(i = 0; i < 3; i++)	cube[1][i*3]=temp[i];
			}else{
				for(i = 0; i < 3; i++)	temp[i]=cube[0][i];
				for(i = 0, j = 2; i < 3; i++, j--)	cube[0][i]=cube[1][j*3];
				for(i = 0; i < 3; i++)	cube[1][i*3]=cube[5][i+6];
				for(i = 0, j = 2; i < 3; i++, j--)	cube[5][i+6]=cube[3][j*3+2];
				for(i = 0; i < 3; i++)	cube[3][i*3+2]=temp[i];
			}
			break;
		case 5:
			if(clockwise){
				for(i = 0; i < 3; i++)	temp[i]=cube[4][i+6];
				for(i = 0; i < 3; i++)	cube[4][i+6]=cube[3][i+6];
				for(i = 0; i < 3; i++)	cube[3][i+6]=cube[2][i+6];
				for(i = 0; i < 3; i++)	cube[2][i+6]=cube[1][i+6];
				for(i = 0; i < 3; i++)	cube[1][i+6]=temp[i];
			}else{
				for(i = 0; i < 3; i++)	temp[i]=cube[4][i+6];
				for(i = 0; i < 3; i++)	cube[4][i+6]=cube[1][i+6];
				for(i = 0; i < 3; i++)	cube[1][i+6]=cube[2][i+6];
				for(i = 0; i < 3; i++)	cube[2][i+6]=cube[3][i+6];
				for(i = 0; i < 3; i++)	cube[3][i+6]=temp[i];
			}
			break;
		default:
			break;	
	}
}
