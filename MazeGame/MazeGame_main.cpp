#include <iostream>
#include <conio.h>
#include <thread>
#include <chrono>

using namespace std;

#define MAZE_WIDTH 20
#define MAZE_HEIGHT 20
#define MAX_BOMB 5

enum eMOVE_INPUT
{
	eLEFT = 75,
	eUP = 72,
	eDOWN = 80,
	eRIGHT = 77
};

struct _tagPoint
{
	int x;
	int y;
};

typedef _tagPoint POINT;
typedef _tagPoint* PPOINT;


void SetMaze(char(*Maze)[MAZE_WIDTH], PPOINT pPlayerPos, PPOINT pStartPos, PPOINT pEndPos);

/*
0 : wall
1 : road
2 : start point
3 : Goal point
4 : Bomb
5 : Bomb Effect
*/

void Output(char(*Maze)[MAZE_WIDTH], PPOINT pPlayerPos);

void MovePlayer(char(*Maze)[MAZE_WIDTH], PPOINT pPlayerPos, unsigned char cinput);

void CreateBomb(char(*Maze)[MAZE_WIDTH], const PPOINT pPlayer, PPOINT pBombArr, int* pBombCount);
void Fire(char(*Maze)[MAZE_WIDTH], PPOINT pPlayer, PPOINT pBombArr, int* pBombCount);

void MoveUp(char(*Maze)[MAZE_WIDTH], PPOINT pPlayerPos);
void MoveDown(char(*Maze)[MAZE_WIDTH], PPOINT pPlayerPos);
void MoveLeft(char(*Maze)[MAZE_WIDTH], PPOINT pPlayerPos);
void MoveRight(char(*Maze)[MAZE_WIDTH], PPOINT pPlayerPos);


int main()
{
	unsigned char GameLoop = 1;
	unsigned char cinput = 0;

	// 20x 20 size array , maze
	char Maze[MAZE_HEIGHT][MAZE_WIDTH] = { 0 };


	POINT tPlayerPos;
	POINT tStartPos;
	POINT tEndPos;
	int iBombCount = 0;
	POINT tBombPos[MAX_BOMB];

	SetMaze(Maze,&tPlayerPos,&tStartPos,&tEndPos);

	//key input getch()
	while (GameLoop)
	{
		Output(Maze, &tPlayerPos);
		if (tPlayerPos.x == tEndPos.x && tPlayerPos.y == tEndPos.y)
		{
			printf("\nGoal! Congratulation!\n");
			GameLoop ^= 1;
		}
		cinput = _getch();
		MovePlayer(Maze, &tPlayerPos, cinput);
		switch (cinput)
		{
		case 't':
		case 'T':
			//Bomb
			CreateBomb(Maze, &tPlayerPos, tBombPos, &iBombCount);
			break;
		case 'u':
		case 'U':
			Fire(Maze, &tPlayerPos, tBombPos, &iBombCount);
			break;
		case 'q':
		case 'Q':
			GameLoop ^= 1;
			break;
		}
	}


	return 0;
}

void SetMaze(char(*Maze)[MAZE_WIDTH], PPOINT pPlayerPos, PPOINT pStartPos, PPOINT pEndPos)
{
	pStartPos->x = 1;
	pStartPos->y = 1;

	pEndPos->x = 17;
	pEndPos->y = 18;

	*pPlayerPos = *pStartPos;

	//use stycpy_s()
	strcpy_s(Maze[0], "0000000000000000000");
	strcpy_s(Maze[1], "0211111111111111110");
	strcpy_s(Maze[2], "0000000000000000010");
	strcpy_s(Maze[3], "0111111111011111110");
	strcpy_s(Maze[4], "0100010101000010000");
	strcpy_s(Maze[5], "0100010101111111110");
	strcpy_s(Maze[6], "0111010100000101010");
	strcpy_s(Maze[7], "0001010111111101010");
	strcpy_s(Maze[8], "0001010000100001010");
	strcpy_s(Maze[9], "0001111110100001000");
	strcpy_s(Maze[10], "0001010101000011110");
	strcpy_s(Maze[11], "0101010101000000000");
	strcpy_s(Maze[12], "0101010101011111110");
	strcpy_s(Maze[13], "0111010101010000010");
	strcpy_s(Maze[14], "0100011101110111010");
	strcpy_s(Maze[15], "0100000000100001010");
	strcpy_s(Maze[16], "0111111000100011110");
	strcpy_s(Maze[17], "0100001000100010000");
	strcpy_s(Maze[18], "0111111111110011130");
	strcpy_s(Maze[19], "0000000000000000000");
}


void Output(char(*Maze)[MAZE_WIDTH], PPOINT pPlayerPos)
{
	system("cls");
	//print maze with double array
	for (int i = 0; i < MAZE_HEIGHT; i++)
	{
		for (int j = 0; j < MAZE_WIDTH; j++)
		{
			if (Maze[i][j] == '4')
				printf("¢Í");
			else if (Maze[i][j] == '5')
				printf("¡Ý");
			else if (pPlayerPos->x == j && pPlayerPos->y == i)
				printf("¡Ù");
			else if (Maze[i][j] == '0')
				printf("¢Ã");
			else if (Maze[i][j] == '1')
				printf("  ");
			else if (Maze[i][j] == '2')
				printf("¡Û");
			else if (Maze[i][j] == '3')
				printf("¡Ý");
		
		}
		printf("\n");
	}
	printf("\n");
	printf("x : %d , y : %d, %c", pPlayerPos->x, pPlayerPos->y, Maze[pPlayerPos->y][pPlayerPos->x]);
	//change number to graphic char
}




void MovePlayer(char(*Maze)[MAZE_WIDTH], PPOINT pPlayerPos, unsigned char cinput)
{

	/*if (cinput == 224 || cinput == 0)
	{
		switch (cinput)
		{
		case eLEFT:
			MoveLeft(Maze, pPlayerPos);
			break;
		case eRIGHT:
			MoveRight(Maze, pPlayerPos);
			break;
		case eUP:
		case eDOWN:

			break;
		}
	}*/
	switch (cinput)
	{
	case 'A':
	case 'a':
		MoveLeft(Maze, pPlayerPos);
		break;
	case 'D':
	case 'd':
		MoveRight(Maze, pPlayerPos);
		break;
	case 'W':
	case 'w':
		MoveUp(Maze, pPlayerPos);
		break;
	case 'S':
	case 's':
		MoveDown(Maze, pPlayerPos);
		break;
	}
}

void CreateBomb(char (*Maze)[MAZE_WIDTH],const PPOINT pPlayer, PPOINT pBombArr, int* pBombCount)
{
	if (*pBombCount >= MAX_BOMB) return;
	 
	for (int i = 0; i < *pBombCount; i++)
	{
		if (pBombArr[i].x == pPlayer->x && pBombArr[i].y == pPlayer->y) return;
	}

	pBombArr[*pBombCount] = *pPlayer;
	++(*pBombCount);

	Maze[pPlayer->y][pPlayer->x] = '4';
}

void Fire(char(*Maze)[MAZE_WIDTH], PPOINT pPlayer, PPOINT pBombArr, int* pBombCount)
{
	for (int i = 0; i < *pBombCount; ++i)
	{
		//reset position when player got damaged by bomb
		if (pBombArr[i].x - 1 == pPlayer->x || pBombArr[i].x + 1 == pPlayer->x || pBombArr[i].y - 1 == pPlayer->y || pBombArr[i].y + 1 == pPlayer->y)
		{
			pPlayer->x = 1;
			pPlayer->y = 1;
		}

		if (pBombArr[i].x == pPlayer->x && pBombArr[i].y == pPlayer->y)
		{
			pPlayer->x = 1;
			pPlayer->y = 1;
		}



		if (pBombArr[i].y - 1 >= 0) //Bomb upside
		{
			if (Maze[pBombArr[i].y - 1][pBombArr[i].x] == '0')
				Maze[pBombArr[i].y - 1][pBombArr[i].x] = '1';
		}

		if (pBombArr[i].y + 1 < MAZE_HEIGHT - 1) //Bomb downside
		{
			if (Maze[pBombArr[i].y + 1][pBombArr[i].x] == '0')
				Maze[pBombArr[i].y + 1][pBombArr[i].x] = '1';
		}

		if (pBombArr[i].x - 1 >= 0) //Bomb leftside
		{
			if (Maze[pBombArr[i].y][pBombArr[i].x - 1] == '0')
				Maze[pBombArr[i].y][pBombArr[i].x - 1] = '1';
		}

		if (pBombArr[i].x + 1 < MAZE_WIDTH - 1) //Bomb rightside
		{
			if (Maze[pBombArr[i].y][pBombArr[i].x + 1] == '0')
				Maze[pBombArr[i].y][pBombArr[i].x + 1] = '1';
		}
		Maze[pBombArr[i].y][pBombArr[i].x] = '1';
	}

	*pBombCount = 0;
}

void MoveUp(char(*Maze)[MAZE_WIDTH], PPOINT pPlayerPos)
{
	int x = pPlayerPos->x;
	int y = pPlayerPos->y;
	if (y - 1 <= 0 || Maze[y - 1][x] == '0') return;
	if (Maze[y - 1][x] == '4') return; // Bomb

	--pPlayerPos->y;
}

void MoveDown(char(*Maze)[MAZE_WIDTH], PPOINT pPlayerPos)
{
	int x = pPlayerPos->x;
	int y = pPlayerPos->y;
	if (y + 1 > MAZE_HEIGHT - 2 || Maze[y + 1][x] == '0') return;
	if (Maze[y + 1][x] == '4') return;// Bomb

	++pPlayerPos->y;
}

void MoveLeft(char(*Maze)[MAZE_WIDTH], PPOINT pPlayerPos)
{
	int x = pPlayerPos->x;
	int y = pPlayerPos->y;
	if (x - 1 <= 0 || Maze[y][x - 1] == '0') return;
	if (Maze[y][x - 1] == '4') return; // Bomb

	--pPlayerPos->x;
}

void MoveRight(char(*Maze)[MAZE_WIDTH], PPOINT pPlayerPos)
{
	int x = pPlayerPos->x;
	int y = pPlayerPos->y;
	if (x + 1 > MAZE_WIDTH - 2 || Maze[y][x + 1] == '0') return;
	if (Maze[y][x + 1] == '4') return; // Bomb

	++pPlayerPos->x;
}