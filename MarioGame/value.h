#pragma once
#include <iostream>
#include <Windows.h>

enum constants
{
	g_iSTAGE_MAX_COUNT = 3,
	g_iMAP_WIDTH = 50,
	g_iMAP_HEIGHT = 10,
	g_iSTAGENAME_MAX = 50,
	g_iSTART_POS_X = 4,
	g_iSTART_POS_Y = 8,
	g_iLIFE_DEFAULT = 3,
	g_iLOADING_SEC = 3,
	g_iBULLET_COUNT_MAX = 10,
	g_iBULLET_RANGE_DEFAULT = 8
};

enum class eSTAGE_BLOCK_TYPE 
{
	SBT_WALL = '0',
	SBT_ROAD = '1',
	SBT_START = '2',
	SBT_END = '3',
	SBT_COIN = '4',
	SBT_MONSTER = '5'
};

enum class eGAME_STATE
{
	//default state : GAME_RETRY
	GAME_RETRY = 0,

	//zero life state : GAME_OVER
	GAME_OVER = 1,

	//head to next level state : GAME_STAGECLEAR
	GAME_STAGECLEAR = 2
};

enum eMONSTER_DIR
{
	MON_DIR_LEFT = -1,
	MON_DIR_RIGHT = 1
};