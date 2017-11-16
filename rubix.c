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
#define N 12



void printCube(char **cube);
bool checkCube(char **cube);
void rotate_cube(char **cube,int move,bool clockwise);
void solveCube(char **cube);

int main(){
	FILE *fp;
	char **cube,i=0,j;

	cube  = (char**)malloc(NFaces*sizeof(char*));	
	for(i=0;i<NSquares;i++)
		cube[i] = (char*)malloc(NSquares*sizeof(char));

	// fp = fopen("input/3x3.txt","r");
	// fp = fopen("input/3x3-reverse.txt","r");
	fp = fopen("input/WC-RC.txt","r");
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

	solveCube(cube);

	// printCube(cube);
	// printf("MOVE: rotate_cube(cube,YELLOW,Clockwise)\n");
	// rotate_cube(cube,   YELLOW,   Clockwise);
	// printCube(cube);
	// printf("MOVE: rotate_cube(cube,YELLOW,Clockwise)\n");
	// rotate_cube(cube,   GREEN,   !Clockwise);
	// printCube(cube);
	// printf("MOVE: rotate_cube(cube,YELLOW,Clockwise)\n");
	// rotate_cube(cube,   RED,   Clockwise);
	// printCube(cube);
	// printf("MOVE: rotate_cube(cube,YELLOW,Clockwise)\n");
	// rotate_cube(cube,   BLUE,   Clockwise);
	// printCube(cube);

	// printCube(cube);
	// printf("MOVE: rotate_cube(cube,ORANGE,!Clockwise)\n");
	// rotate_cube(cube,   ORANGE,   !Clockwise);
	// printCube(cube);
	// printf("MOVE: rotate_cube(cube,GREEN,Clockwise)\n");
	// rotate_cube(cube,   GREEN,   Clockwise);
	// printCube(cube);
	// printf("MOVE: rotate_cube(cube,YELLOW,!Clockwise)\n");
	// rotate_cube(cube,   YELLOW,   !Clockwise);
	// printCube(cube);
	// printf("MOVE: rotate_cube(cube,RED,Clockwise)\n");
	// rotate_cube(cube,   RED,   Clockwise);
	// printCube(cube);
	// printf("MOVE: rotate_cube(cube,ORANGE,!Clockwise)\n");
	// rotate_cube(cube,   ORANGE,   !Clockwise);
	// printCube(cube);
}


bool checkCube(char **cube){
	int i,j,k,equal=0; 		//1 yung value ng equal pag not equal
	char temp;

	for(i=0;i!=NFaces;i++){
		for(j=0;j!=NSquares;j=j+NSides)
			switch(i){
				case 0: temp = cube[i][j];
						for(k=0;k!=NSides;k++){
							if (cube[i][j+k] != temp){
								equal = 1;
								return false;
							}
						}
						break;
				case 1:	temp = cube[i][j];
						for(k=0;k!=NSides;k++){
							if (cube[i][j+k] != temp){
								equal = 1;
								return false;
							}
						}
						temp = cube[i+1][j];
						for(k=0;k!=NSides;k++) {
							if (cube[i+1][j+k] != temp){
								equal = 1;
								return false;
							}
						}

						temp = cube[i+2][j];
						for(k=0;k!=NSides;k++) {
							if (cube[i+2][j+k] != temp){
								equal = 1;
								return false;
							}
						}

						temp = cube[i+3][j];
						for(k=0;k!=NSides;k++) {
							if (cube[i+3][j+k] != temp){
								equal = 1;
								return false;
							}
						}
						break;
				case 5: temp = cube[i][j];
				        for(k=0;k!=NSides;k++) {
				        	if (cube[i][j+k] != temp){
				        		equal = 1;
								return false;
							}	
				        }
				        break;
				default:break;
			}
	}
	
	return true;
	//printf("equal?? %i \n\n", equal);
}

void solveCube(char **cube){
	int maxMoves = 10;  //Moves limit
	int posMoves = 12;	//Possible moves in a rubix cube. rotate(color, clockwise or !clockwise)
	int limit = 3;		//Number of rotations to go full circle - 1

	int start, move;
	int nopts[maxMoves+2];
	int option[maxMoves+2][posMoves+2];
	/*
		nopts points to the value to use in a stack
				
		nopts[i]
					1	N	N	...
				i =	0	1	2	...	maxMoves+2
	
		option[][]
		posMoves+2	1	1
			.		.	.
			.		.	.
			2		N-1	N-1
			1		N	N	...	0
			0	
				0	1	2	...	maxMoves+2
	
	
	*/
	int i, candidate, counter;
	// counter counts number of the same moves occuring in a row

	if(checkCube(cube)){
		printf("DONE\n");
		return;
	}

	move = start = counter = 0; 
	nopts[start]= 1;
	while (nopts[start] >0){//while dummy stack is not empty
		if(nopts[move]>0){ 
			move++;
			nopts[move]=0; //initialize new move
			if(move < maxMoves+1){		//limits the number of moves to the maximum number of allowed moves
				for(candidate = posMoves; candidate >=1; candidate --) {
					nopts[move]++;
					option[move][nopts[move]] = candidate;
				}
			}
		}
		else {
			for(i=1;i<move;i++){
				char **temp = cube;
				switch(option[i][nopts[i]]){
					case 1:
						printf("MOVE: rotate_cube(cube,WHITE,Clockwise)\n");
						rotate_cube(temp,   WHITE,   Clockwise);
						break;
					case 2:
						printf("MOVE: rotate_cube(cube,WHITE,!Clockwise)\n");
						rotate_cube(temp,   WHITE,   !Clockwise);
						break;
					case 3:
						printf("MOVE: rotate_cube(cube,RED,Clockwise)\n");
						rotate_cube(temp,   RED,   Clockwise);
						break;
					case 4:
						printf("MOVE: rotate_cube(cube,RED,!Clockwise)\n");
						rotate_cube(temp,   RED,   !Clockwise);
						break;
					case 5:
						printf("MOVE: rotate_cube(cube,BLUE,Clockwise)\n");
						rotate_cube(temp,   BLUE,   Clockwise);
						break;
					case 6:
						printf("MOVE: rotate_cube(cube,BLUE,!Clockwise)\n");
						rotate_cube(temp,   BLUE,   !Clockwise);
						break;
					case 7:
						printf("MOVE: rotate_cube(cube,ORANGE,Clockwise)\n");
						rotate_cube(temp,   ORANGE,   Clockwise);
						break;
					case 8:
						printf("MOVE: rotate_cube(cube,ORANGE,!Clockwise)\n");
						rotate_cube(temp,   ORANGE,   !Clockwise);
						break;
					case 9:
						printf("MOVE: rotate_cube(cube,GREEN,Clockwise)\n");
						rotate_cube(temp,   GREEN,   Clockwise);
						break;
					case 10:
						printf("MOVE: rotate_cube(cube,GREEN,!Clockwise)\n");
						rotate_cube(temp,   GREEN,   !Clockwise);
						break;
					case 11:
						printf("MOVE: rotate_cube(cube,YELLOW,Clockwise)\n");
						rotate_cube(temp,   YELLOW,   Clockwise);
						break;
					case 12:
						printf("MOVE: rotate_cube(cube,YELLOW,!Clockwise)\n");
						rotate_cube(temp,   YELLOW,   !Clockwise);
						break;
				}
				printCube(temp);
			}
			printf("\n");
			if(checkCube(cube)){
				printf("DONE\n");
				return;
			}
			move--;
			nopts[move]--;
		}
			
		//Increments counter when a value is equal to the one before it, in the combination
		if(move > 1 && option[move][nopts[move]] == option[move-1][nopts[move-1]]) counter++;
		else counter = 0;	//resets when two different values are in a row
		
		//changes the move to be used whenever the limit is reached or two opposing moves are in a row
		while(counter == limit || (move > 1 && option[move][nopts[move]] % 2 == 0 && option[move-1][nopts[move-1]] + 1 == option[move][nopts[move]])){
			nopts[move]--;
			counter = 0;
		}
	}
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
