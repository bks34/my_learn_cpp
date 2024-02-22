#pragma once

#include "resource.h"
#include<stdio.h>
#include<string.h>
#include<bitset>

using std::bitset;
typedef struct
{
	bitset<8> r;
	bitset<8> g;
	bitset<8> b;
}RGB_point;

typedef struct
{
	bitset<8> r;
	bitset<8> g;
	bitset<8> b;
	bitset<8> a;
}RGBA_point;
