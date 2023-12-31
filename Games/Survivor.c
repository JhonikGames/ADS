#include <stdlib.h>
#include <stdio.h>

// PLAYER ZONE - W5 / H5
#define WIDTH 21
#define HEIGHT 9 

// MAP ZONE
#define MW 21 // Largura
#define MH 9 // Altura

#define MAXMATERIALS 10
#define CL '/'

// player position
int plr_pos[2] = {2,2};

/*    
	PLAIN-0 | GRASS-1 | POINTS-2 | VOID-3 | PLAYER-4
*/
const char mat[MAXMATERIALS] = {'-','~','0','#','+'};

const int map[MH][MW] = {
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0 },
	{ 0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0 },
	{ 0,0,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0 },
	{ 0,0,0,1,1,0,0,0,0,0,2,0,0,0,0,1,1,1,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0 },
	{ 0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0 },
};

char matrix[HEIGHT][WIDTH];

// auxiliary functions

void clear()
{
	system("cls");
}

void line()
{
	for(int i=0;i<30;i++){
		putchar(CL);
	}
	putchar('\n');
}

void reset()
{
	for(int x=0;x<HEIGHT;x++){
		for(int y=0;y<WIDTH;y++){
			if(map[x][y] < 0 || map[x][y] > MAXMATERIALS ){
				matrix[x][y] = mat[3];
			}
			else{
				matrix[x][y] = mat[map[x][y]];
			}
		}
	}
	matrix[plr_pos[0]][plr_pos[1]] = mat[4];
}

// evita o player sair fora do mapa
void fix()
{
    for(int i=0;i<2;i++){
        if(plr_pos[i] < 0){
            plr_pos[i] = 0;
        }
    }
    if(plr_pos[0] > MH-1){
        plr_pos[0] = MH-1;
    }
    if(plr_pos[1] > MW-1){
        plr_pos[1] = MW-1;
    }
}

// refaz a matriz do mapa atual de acordo com a posição do player
void remake()
{
    fix(); // essential
	int x = plr_pos[0]-2, y = plr_pos[1]-2;
	int xsize = x, ysize = y;
	for(x;x<xsize+HEIGHT;x++){
		for(y;y<ysize+WIDTH;y++){
			if(map[x][y] < 0 || map[x][y] > MAXMATERIALS ){
				matrix[x][y] = mat[3];
			}
			else{
				matrix[x][y] = mat[map[x][y]];
			}
		}
	}
	matrix[plr_pos[0]][plr_pos[1]] = mat[4];
}

// controls

void up()
{
	plr_pos[0]--;
	remake();
}

void down()
{
	plr_pos[0]++;
	remake();
}

void left()
{
	plr_pos[1]--;
	remake();
}

void right()
{
	plr_pos[1]++;
	remake();
}

// main

void window()
{
	for(int x=0;x<HEIGHT;x++){
		for(int y=0;y<WIDTH;y++){
			putchar(matrix[x][y]);
		}
		putchar('\n');
	}
	printf("Use WASD para andar - posicao A[%d] L[%d]:\n",plr_pos[0],plr_pos[1]);
	char key;
	scanf(" %c",&key);
	clear();
	switch(key){
		case 'w':
			up();
			break;
		case 's':
			down();
			break;
		case 'a':
			left();
			break;
		case 'd':
			right();
			break;
		default:
			puts("\nERROR\n");
			return;
			break;
	}
	window();
}

int main()
{
	int n;
	line();
	printf("\n\tWelcome to Survivor!\n\nPress 1 to start!\n");
	line();
	scanf("%d",&n);
	if(n==1){
		clear();
		reset();
		window();
	}
	return 0;
}
