#pragma once
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <ctime>
#include "Angel.h"

using namespace std;

#define PI 3.14159265
#define MIN_X 0
#define MIN_Y 1
#define MAX_X 2
#define MAX_Y 3

extern GLfloat width;
extern GLfloat height;

extern Angel::vec4 blue_trajectory;
extern Angel::vec4 green_start_marker;
extern Angel::vec4 red_exit_marker;
extern Angel::vec4 yelow_box_edge;
extern int count;
extern struct pointNode* head;
extern struct pointNode* curr;
extern bool bPaused;
extern bool bComplete;
extern bool bStarted;
void randomDisplacement(GLfloat magnitude, GLfloat &x, GLfloat &y, GLfloat &z);
int pointCount(struct pointNode* head);
pointNode* AddNode(struct pointNode* node, GLfloat x, GLfloat y, GLfloat z);
GLfloat* copyToArray(struct pointNode * head);

//This will be the basis of linked list to hold pointer data. 
struct pointNode
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
	pointNode *next;
};
