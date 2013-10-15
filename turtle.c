#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/*****************************************************
 * Turtle Graphics : CIS 343 : Winter 2013           *
 * Author: Conner Fallone                            *
 *****************************************************/
#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

int x;
int y;
int n;
int direction;
bool penDown;

void printArray(int floor[n][n], char** argv)
{
	int i,j;
	FILE *file2;

	file2 = fopen(argv[3], "w");
	
	for (i=0;i<n;i++)
	{
		for (j=0;j<n;j++)
		{
			if (floor[j][i] == 1)
			{
				printf("*");
				fputs("*", file2);
			}
			else
			{
				printf(" ");
				fputs(" ", file2);
			}
		}
		printf("\n");
		fputs("\n", file2);
	}
	fclose(file2);
}

void updateArray(int floor[n][n], int spacesMoved)
{
	int i,j;
	if(direction == UP)
	{
		for (i = y; i >= y - spacesMoved; i--)
		{
			if(i < 0)
				break;
			floor[x][i] = 1;
		}
	}
	else if(direction == RIGHT)
	{
		for (i = x; i <= x + spacesMoved; i++)
		{
			if(i > n-1)
				break;
			floor[i][y] = 1;
		}
	}
	else if(direction == DOWN)
	{
		for (i = y; i <= y + spacesMoved; i++)
		{
			if(i > n-1)
				break;
			floor[x][i] = 1;
		}
	}
	else if(direction == LEFT)
	{
		for (i = x; i >= x - spacesMoved; i--)
		{
			if(i < 0)
				break;
			floor[i][y] = 1;
		}
	}
}

void moveForward(char* temp, int floor[n][n])
{
	bool vertical;
	int spacesMoved = atoi(temp);
	if(penDown)
		updateArray(floor, spacesMoved);
	if (direction == RIGHT)
	{
		if ((x+= spacesMoved) > n - 1)
			x = n - 1;
	}
	else if (direction == LEFT)
	{
		if ((x-= spacesMoved) < 0)
			x = 0;
	}
	else if (direction == UP)
	{
		if ((y -= spacesMoved) < 0)
			y = 0;
	}
	else if (direction == DOWN)
	{
		if ((y += spacesMoved) > n - 1)
			y = n - 1;
	}
}

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		printf("Usage: %s n inputfile outputfile\n",argv[0]);
		return;
	}
	x = 0;
	y = 0;
	n = atoi(argv[1]);
	int i,j;
	direction = RIGHT;
	penDown = false;
	char s[100];
	FILE *file;

	file = fopen(argv[2], "r");

	int floor[n][n];
	for (i=0;i<n;i++)
	{
		for (j=0;j<n;j++)
		{
			floor[i][j] = 0;
		}
	}
	while (fgets(s,sizeof(s),file) != NULL)
	{
		s[strlen(s)-1] = '\0';
		if(strcmp(s,"1") == 0)
			penDown = false;
		else if(strcmp(s,"2") == 0)
			penDown = true;
		else if(strcmp(s,"3") == 0)
		{
			if (direction == RIGHT)
				direction = DOWN;
			else if (direction == DOWN)
				direction = LEFT;
			else if (direction == LEFT)
				direction = UP;
			else if (direction == UP)
				direction = RIGHT;
		}
		else if(strcmp(s,"4") == 0)
		{
			if (direction == RIGHT)
				direction = UP;
			else if (direction == UP)
				direction = LEFT;
			else if (direction == LEFT)
				direction = DOWN;
			else if (direction == DOWN)
				direction = RIGHT;
		}
		else if(s[0] == '5')
		{
			char* temp = strtok(s,",");
			temp = strtok(NULL," ");
			moveForward(temp,floor);
		}
		else if(strcmp(s,"6") == 0)
		{
			printArray(floor, argv);
			fclose(file);
		}
	}
}
