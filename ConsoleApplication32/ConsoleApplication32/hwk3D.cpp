#include "hwk3D.h"

GLfloat width;
GLfloat height;

Angel::vec4 blue_trajectory = Angel::vec4(0.0, 0.0, 1.0, 1.0);
Angel::vec4 green_start_marker = Angel::vec4(0.0, 1.0, 0.0, 1.0);
Angel::vec4 red_exit_marker = Angel::vec4(1.0, 0.0, 0.0, 1.0);
Angel::vec4 yelow_box_edge = Angel::vec4(1.0, 1.0, 0.0, 1.0);
int count;
struct pointNode* head = NULL;
struct pointNode* curr = NULL;
bool bPaused = false;
bool bComplete = false;
bool bStarted = false;

void randomDisplacement(GLfloat magnitude, GLfloat & x, GLfloat & y, GLfloat &z)
{
	GLfloat angle1 = ((GLfloat)rand() / (GLfloat)RAND_MAX) * (2 * PI);
	GLfloat angle2 = ((GLfloat)rand() / (GLfloat)RAND_MAX) * (2 * PI);
	x = magnitude * cos(angle1) * cos(angle2);
	y = magnitude * cos(angle1) * sin(angle2);
	z = magnitude * sin(angle1);
}
//this will count all the nodes after head;
int pointCount(struct pointNode* head)
{
	pointNode* tmp;
	tmp = head;
	int count_l = 0;

	while (tmp != NULL)
	{
		count_l++;
		tmp = tmp->next;
	}
	return count_l;
}

pointNode * AddNode(pointNode * node, GLfloat x, GLfloat y, GLfloat z)
{
	struct pointNode* tmp = NULL;
	while (node->next != NULL)
	{
		node = node->next;
	}

	tmp = (pointNode *)malloc(sizeof(pointNode));
	tmp->x = x;
	tmp->y = y;
	tmp->z = z;

	tmp->next = NULL;
	node->next = tmp;

	return tmp;
}

GLfloat * copyToArray(pointNode * head)
{
	GLfloat * retVal;
	pointNode * tmp;
	int count_l;
	count_l = pointCount(head);
	int i = 0;

	count_l *= 3;

	tmp = head;
	if (count_l > 0)
	{

		retVal = new GLfloat[count_l];
	}
	else
	{
		return NULL;
	}

	while (i < count_l)
	{
		retVal[i] = tmp->x;
		retVal[i + 1] = tmp->y;
		retVal[i + 2] = tmp->z;
		tmp = tmp->next;
		i += 3;
	}
	return retVal;
}
