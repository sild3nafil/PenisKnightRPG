#pragma once
#include  <SDL.h>

#define MAPX 101
#define MAPY 75

SDL_Texture* mapTex;

char randommap[MAPY][MAPX]={};
char map1_1[MAPY][MAPX] = {
	"11111111111111111111                    11111111111111111111                    11111111111111111111",
	"10000000000000000001                    10000000000000000001                    10000000000000000001",
	"10000000000000000001                    10000000000000000001                    10000000000000000001",
	"10233322202220333001                    10000000000000000001                    10000000000000000001",
	"10232020202020003001                    10000000000000000001                    10000000000000000001",
	"1023202020222000300111111111111111111111102020202022203333311111111111111111111110202020202220333331",
	"1000002220200000000D00000000000000000000D000000000000000000D00000000000000000000D0000000000000000001",
	"108800003330aa00990D00000000000000000000D000000000000000000D00000000000000000000D0000000000000000001",
	"1088000044000000990D00000000000000000000D000000000000000000D00000000000000000000D0000000000000000001",
	"1000000044000000000D00000000000000000000D000000000000000000D00000000000000000000D0000000000000000001",
	"1003000000d00000300111111111111111111111100000000000000000011111111111111111111110000000000000000001",
	"1003000000d000003001                    10000000000000000001                    10000000000000000001",
	"10033300000000333051                    10000000000000000001                    10000000000000000001",
	"10000000000000000001                    10660000000000000001                    10000000000000000001",
	"11111111DDDD11111111                    11FF1111DDDD11111111                    11111111DDDD11111111",
	"       100001                                  100001                                  100001       ",
	"       100001                                  100001                                  100001       ",
	"       100001                                  100001                                  100001       ",
	"       100001                                  100001                                  100001       ",
	"       100001                                  100001                                  100001       ",
	"       100001                                  100001                                  100001       ",
	"       100001                                  100001                                  100001       ",
	"       100001                                  100001                                  100001       ",
	"       100001                                  100001                                  100001       ",
	"       100001                                  100001                                  100001       ",
	"       100001                                  100001                                  100001       ",
	"       100001                                  100001                                  100001       ",
	"       100001                                  100001                                  100001       ",
	"       100001                                  100001                                  100001       ",
	"       100001                                  100001                                  100001       ",
	"11111111DDDD11111111                    11111111DDDD11111111                           1DDDD11111111",
	"10222020222020202221                    10000000000000000001                           1000000000001",
	"10000000000000000001                    10000000000000000001                           1000000000001",
	"10222022202220333331                    10000000000000000001                           1000000000001",
	"10202020202020333331                    10000000000000000001                           1000000000001",
	"1020202020222033333111111111111111111111100000000000000000011111111111111111111111111111202220333331",
	"1022202220200000000D00000000000000000000D000000000000000000D00000000000000000000D0000000000000000001",
	"1000aa00aa00aa00000D00000000000000000000D000000000000000000D00000000000000000000D0000000000000000001",
	"1005000500050002220D00000000000000000000D000000000000000000D00000000000000000000D0000000000000000001",
	"1005aa00a0050000200D00000000000000000000D000000000000000000D00000000000000000000D0000000000000000001",
	"1005000005050000200111111111111111111111100000000000000000011111111111111111111110000000000000000001",
	"1000aa0aa000aa000001                    10000000000000000001                    10000000000000000001",
	"10000000000000aaa051                    10000000000000000001                    10000000000000000001",
	"123456789abcde000001                    10000000000000000001                    10000000000000000001",
	"11111111DDDD11111111                    11111111DDDD11111111                    11111111DDDD11111111",
	"       100001                                  100001                                  100001       ",
	"       100001                                  100001                                  100001       ",
	"       100001                                  100001                                  100001       ",
	"       100001                                  100001                                  100001       ",
	"       100001                                  100001                                  100001       ",
	"       100001                                  100001                                  100001       ",
	"       100001                                  100001                                  100001       ",
	"       100001                                  100001                                  100001       ",
	"       100001                                  100001                                  100001       ",
	"       100001                                  100001                                  100001       ",
	"       100001                                  100001                                  100001       ",
	"       100001                                  100001                                  100001       ",
	"       100001                                  100001                                  100001       ",
	"       100001                                  100001                                  100001       ",
	"       100001                                  100001                                  100001       ",
	"11111111DDDD11111111                    11111111DDDD11111111                    11111111DDDD11111111",
	"10222020222020202221                    10000000000000000001                    10000000000000000001",
	"10000000000000000001                    10000000000000000001                    10000000000000000001",
	"10222022202220333331                    10000000000000000001                    10000000000000000001",
	"10202020202020333331                    10000000000000000001                    10000000000000000001",
	"1020202020222033333111111111111111111111102020202022203333311111111111111111111110202020202220333331",
	"1022202220200000000D00000000000000000000D000000000000000000D00000000000000000000D0000000000000000001",
	"1000aa00aa00aa00000D00000000000000000000D000000000000000000D00000000000000000000D0000000000000000001",
	"1005000500050002220D00000000000000000000D000000000000000000D00000000000000000000D0000000000000000001",
	"1005aa00a0050000200D00000000000000000000D000000000000000000D00000000000000000000D0000000000000000001",
	"1005000005050000200111111111111111111111100000000000000000011111111111111111111110000000000000000001",
	"1000aa0aa000aa000001                    10000000000000000001                    10000000000000000001",
	"10000000000000aaa051                    10000000000000000001                    10000000000000000001",
	"123456789abcde000001                    10000000000000000001                    10000000000000000001",
	"11111111111111111111                    11111111111111111111                    11111111111111111111",

	 
};

char Black[15][21] = {
	"                    ",
	"                    ",
	"                    ",
	"                    ",
	"                    ",
	"                    ",
	"                    ",
	"                    ",
	"                    ",
	"                    ",
	"                    ",
	"                    ",
	"                    ",
	"                    ",
	"                    ",
};
char Hpath[15][21] = {
	"                    ",
	"                    ",
	"                    ",
	"                    ",
	"                    ",
	"11111111111111111111",
	"00000000000000000000",
	"00000000000000000000",
	"00000000000000000000",
	"00000000000000000000",
	"11111111111111111111",
	"                    ",
	"                    ",
	"                    ",
	"                    ",
};
char Vpath[15][21] = {
	"       100001       ",
	"       100001       ",
	"       100001       ",
	"       100001       ",
	"       100001       ",
	"       100001       ",
	"       100001       ",
	"       100001       ",
	"       100001       ",
	"       100001       ",
	"       100001       ",
	"       100001       ",
	"       100001       ",
	"       100001       ",
	"       100001       "
};
char T1[3][15][21] = {
	{
	"11111111111111111111",
	"10000000000000000001",
	"10000000000000000001",
	"10222022202220333331",
	"10202020202020333331",
	"10202020202220333331",
	"10222022202000000000",
	"10000000000000000000",
	"10000000000000000000",
	"10000000000000000000",
	"10003000000000000001",
	"10003300000000000001",
	"10000000000000000051",
	"123456789abcde000001",
	"11111111000011111111",},
	{
	"11111111111111111111",
	"10000000000000000001",
	"10333000000000033301",
	"10300000000000000301",
	"10344444444440000301",
	"10000000333000000001",
	"10000000000000000000",
	"10000000000000000000",
	"10000044444444000000",
	"10000000333000000000",
	"10300000000000003001",
	"10300000000000003001",
	"10333000000000333051",
	"14444444444444000001",
	"11111111000011111111",},
	{
	"11111111111111111111",
	"10000000000030000001",
	"10000000000030000001",
	"10000000000030000001",
	"10333333333330000001",
	"10000000000000000001",
	"10033333330000000000",
	"10000000030000033300",
	"10000000030000000000",
	"10000000030000000000",
	"10000000030000000001",
	"10000000030000000001",
	"10000000000000000001",
	"10000000000000000001",
	"11111111000011111111",}
};
char T2[3][15][21] = {
	{
	"11111111111111111111",
	"10000000000000000001",
	"10900000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"00000000000000000000",
	"00000000000000000000",
	"00000000000000000000",
	"00000000000000000000",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000901",
	"10000000000000000001",
	"11111111000011111111"},
	{
	"11111111111111111111",
	"10000000000000000001",
	"10900000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"1F110000000000000001",
	"060100000000000000F0",
	"000100000000000000F0",
	"000100000000000000F0",
	"000100000000000000F0",
	"11110000000000000001",
	"10000000000000000001",
	"10000000000000000901",
	"10000000FFFF00000001",
	"11111111000011111111"},
	{
	"11111111111111111111",
	"10000000000000000001",
	"10000000000000000001",
	"10033333000000000001",
	"10030003000000000001",
	"10030903000000000001",
	"00030003000000000000",
	"00033333000000000000",
	"00000900000000000000",
	"00000000000000000000",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"11111111000011111111"}
};
char T3[3][15][21] = {
	{
	"11111111111111111111",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"00000000606000000001",
	"00000000000000000001",
	"00000000000000000001",
	"00000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"11111111000011111111"},
	{
	"11111111111111111111",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"00000000eee000000001",
	"00000000eee000000001",
	"00000000000000000001",
	"00000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"11111111000011111111"},
	{
	"  111111111111111111",
	"  100000000000000001",
	"  100000000000000001",
	"  100000000000000001",
	"  100000000000000001",
	"11100000000000000001",
	"00000000ddd000000001",
	"00000000000ddd000001",
	"00000000000000000001",
	"00000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"11111111000011111111"}
};
char M1[3][15][21] = {
	{
	"11111111000011111111",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000606000000000",
	"10000000000000000000",
	"10000000000000000000",
	"10000000000000000000",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"11111111000011111111"},
	{
	"11111111000011111111",
	"10000001000010000001",
	"10000001000010000001",
	"100dd001000010000001",
	"10000001000010000001",
	"100000d1000011111111",
	"1XXXXXX1606000000000",
	"10000000000000000000",
	"10000000000000000000",
	"10000000000000000000",
	"10000000000011111111",
	"1000000000001       ",
	"1000000000001       ",
	"1000000000001       ",
	"11111111000011111111" },
	{
	"11111111000011111111",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"1000000XXXXXX0000000",
	"1000000X0000X0000000",
	"1000000X0000X0000000",
	"1000000XXXXXX0000000",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"11111111000011111111"}
};
char M2[3][15][21] = {
	{
	"11111111000011111111",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"00000000000000000000",
	"00000000000000000000",
	"00000000000000000000",
	"00000000000000000000",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"11111111000011111111"},
	{
	"       100001       ",
	"       100001       ",
	"       100001       ",
	"       100001       ",
	"       100001       ",
	"11111111000011111111",
	"00000000000000000000",
	"00000000000000000000",
	"00000000000000000000",
	"00000000000000000000",
	"11111111000011111111",
	"       100001       ",
	"       100001       ",
	"       100001       ",
	"       100001       "},
	{
	"     X11000011X     ",
	"    X1000000001X    ",
	"   X100000000001X   ",
	"  X10000000000001X  ",
	" X1000000000000001X ",
	"11000000000000000011",
	"00000000000000000000",
	"00000000000000000000",
	"00000000000000000000",
	"00000000000000000000",
	"11000000000000000011",
	" X1000000000000001X ",
	"  X10000000000001X  ",
	"   X100000000001X   ",
	"    X1110000111X    "}

};
char M3[3][15][21] = {
	{
	"11111111000011111111",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"00000000008000000001",
	"00000000000000000001",
	"00000000000000000001",
	"00000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"11111111000011111111"},
	{
	"11111111000011111111",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"100XXXXXXXXXXXXXXXXX",
	"000X777777777777777X",
	"000X777777777777777X",
	"000X777777777777777X",
	"000XXXXXXXXXXXXXXXXX",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"11111111000011111111"},
	{
	"11111111000011111111",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"11111111111111111111",
	"00000000008000000001",
	"00000000000000000001",
	"00000000000000000001",
	"00000000000000000001",
	"11111111111111111111",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"11111111000011111111"},
};
char B1[3][15][21] = {
	{
	"11111111000011111111",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"1000000000c000000000",
	"10000000000000000000",
	"10000000000000000000",
	"10000000000000000000",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"11111111111111111111"},
	{
	"11111111000011111111",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000022222000000000",
	"10002222200000000000",
	"10002222222000000000",
	"10000000000000000000",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"11111111111111111111"},
	{
	"11111111000011111111",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000001111",
	"10000000000000001000",
	"10000000000000001000",
	"10000000000000001000",
	"10000000000000001000",
	"10000000000000001111",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"11111111111111111111"},

};
char B2[3][15][21] = {
	{
	"11111111000011111111",
	"10000000000000000001",
	"10044444444444444401",
	"10404444444444444401",
	"10440444444444444401",
	"10444044444444444401",
	"00444404444444444400",
	"00444440444444444400",
	"00444444044444444400",
	"00444444404444444400",
	"10444444440444444401",
	"10444444444044444401",
	"10444444444404444401",
	"10000000000000000001",
	"11111111111111111111"},
	{
	"11111111000011111111",
	"10000000000000000001",
	"10444444444044444401",
	"10444444444044444401",
	"10444444444044444401",
	"10444444444044444401",
	"00444444444044444400",
	"00444444444044444400",
	"00000000000000000000",
	"00444444444044444400",
	"10444444444044444401",
	"10444444444044444401",
	"10444444444044444401",
	"10000000000000000001",
	"11111111111111111111"},
	{
	"11111111000011111111",
	"10000000000000000001",
	"10444444444444444401",
	"10444444444444444401",
	"10444444444444444401",
	"10444444444444444401",
	"00444444444444444400",
	"00444444444444444400",
	"00444444444444444400",
	"00444444444444444400",
	"10444444444444444401",
	"10444444444444444401",
	"10444444444444444401",
	"10000000000000000001",
	"11111111111111111111"}
};
char B3[3][15][21] = {
	{
	"11111111000011111111",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"00000000000000000001",
	"00000000000000000001",
	"00000000034444000001",
	"00000aaaabaaa3000001",
	"10000000050000000001",
	"10000000050000000001",
	"10000000030000000001",
	"10000000000000000001",
	"11111111111111111111"},
	{
	"1111111100001       ",
	"1000000000001       ",
	"10011111111111111111",
	"10000000000000000001",
	"10000000000000000001",
	"11111111111111100001",
	"00000000000000000001",
	"00000000000000000001",
	"00000000000000000001",
	"00000000000000000001",
	"11111111111111111111",
	"                    ",
	"                    ",
	"                    ",
	"                    "},
	{
	"11111111000011111111",
	"1      X0000X      1",
	"1      XX  XX      1",
	"1      XX  XX      1",
	"1      XX  XX      1",
	"1XXXXXXXX  XX      1",
	"00XXXX000000X      1",
	"007777000000X      1",
	"007777000000X      1",
	"00XXXX000000X      1",
	"1XXXXXXXXXXXXXXXXXX1",
	"1111               1",
	"   11              1",
	"    11             1",
	"     111111111111111"}
};