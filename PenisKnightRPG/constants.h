#pragma once

enum MouseState
{
	NONE = 0,
	OUT = 1, // Mouse out
	IN_LB_SC = 2,  // Inside, Left Button, Single Click
	IN_RB_SC = 3,  // Inside, RIGHT Button, Single Click
	IN_LB_DC = 4,  // Inside, Left Button, Double Click
	IN_RB_DC = 5,  // Inside, RIGHT Button, Double Click
	IN_LB_PR = 6,  // Inside, Left Button, Press
	IN_RB_PR = 7,  // Inside, Left Button, Press
	IN_WU = 8,  // Inside, Wheel UP
	IN_WD = 9,  // Inside, Wheel DOWN
	HOVER = 10, // Mouse hover
	IN_LB_PR_HOVER = 11, // Inside, Left Button, Press, Hover
	IN_RB_PR_HOVER = 12 // Inside, Left Button, Press, Hover
};

struct Mouse
{
	MouseState state;
	int x;
	int y;
	int count;
};

#define WIDTH  640
#define HEIGHT 480

#define MUSIC 10
#define EFFECT 11
#define FOREVER -1
#define ONE 0
#define ALLCHANNEL -1

#define BOSS 0
#define WOMAN 1
#define RAT 2
#define SLIME 3
#define TOWER 4
#define HEALER 5