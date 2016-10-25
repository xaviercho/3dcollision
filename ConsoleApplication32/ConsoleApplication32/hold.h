#pragma once

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

#define X               0
#define Y               1
#define Z               2
#define SCALE_VECTOR    1.0
#define SCALE_ANGLE     1.0

void m_glewInitAndVersion(void);
void reshape(int width, int height);

GLuint program[8];
GLuint VAO[8];

enum { cube_vertices, trajectory, cube_indeces, wire_indeces };

/////Camera unv basis///////
Angel::vec4 n = vec4(0.0, 0.0, 1.0, 0.0);
Angel::vec4 v = vec4(0.0, 1.0, 0.0, 00);
Angel::vec4 u = vec4(1.0, 0.0, 0.0, 0.0);
Angel::vec4 eye = vec4(0.0, 0.0, 4.0, 1.0);

GLfloat theta = 0;
GLfloat phi = 0;
GLfloat theta_y = 0;
GLfloat theta_z = 0;

GLfloat step = 20;
int spinToggle = 0;
GLfloat d = 0.5;
vec3 finalpoint;
int w; int h;
int startx = 0;
int starty = 0;
int moving = 0;
bool bStarted = false;
int hits_wall = 0;
const int NumVertices = 36;
point4 points[NumVertices];
int Index = 0;

// RGBA colors
color4 orange = color4(0.184, 0.310, 0.310, 1.0);
color4 transparent = color4(1.000, 0.271, 0.100);
color4 trajectoryColor = color4(0.40, 0.80, 0.9, 1.0);
color4 red_transparent = color4(1.0, 0.1, 1.0, 1);//green
color4 pink_transparent = color4(0, 1.0, 0.0, 1);
//===========Rotation Related variables
int moveLight = GL_FALSE;
int moveObject = GL_FALSE;
int curx, cury;

//uniform variables locations
GLuint color_loc;
GLuint proj_loc;
GLuint model_view_loc;

//make sure you start with the default coordinate system
mat4 projmat = mat4(1.0);
mat4 modelviewStackTop = mat4(1.0);
mat4 modelviewStackBottom = mat4(1.0);


////////////BROWNIAN FUNCTIONS////////////////
void randomDisplacement(GLfloat magnitude, GLfloat &side1, GLfloat &side2, GLfloat &side3) {
	GLfloat angle = ((GLfloat)rand() / (GLfloat)RAND_MAX) * (2 * PI);
	GLfloat angle2 = ((GLfloat)rand() / (GLfloat)RAND_MAX) * (2 * PI);
	side1 = magnitude * cos(angle)* cos(angle2);
	side2 = magnitude * sin(angle)* cos(angle2);
	side3 = magnitude * sin(angle2);
}

//this will count all the nodes after head;
int pointCount(struct pointNode* head) {
	pointNode* tmp;
	tmp = head;
	int count_l = 0;

	while (tmp != NULL) {
		count_l++;
		tmp = tmp->next;
	}
	return count_l;
}


pointNode* getRandomStart(GLfloat xMin, GLfloat xMax, GLfloat yMin, GLfloat yMax, GLfloat zMin, GLfloat zMax) {
	struct pointNode* retVal;
	GLfloat xLen = xMax - xMin;
	GLfloat yLen = yMax - yMin;
	GLfloat zLen = zMax - zMin;

	GLfloat startX = ((GLfloat)rand() / (GLfloat)RAND_MAX) * xLen + xMin;
	GLfloat startY = ((GLfloat)rand() / (GLfloat)RAND_MAX) * yLen + yMin;
	GLfloat startZ = ((GLfloat)rand() / (GLfloat)RAND_MAX) * zLen + zMin;

	retVal = (pointNode*)malloc(sizeof(pointNode));
	retVal->x = startX;
	retVal->y = startY;
	retVal->z = startZ;
	retVal->next = NULL;

	return retVal;
}

pointNode* AddNode(struct pointNode* node, GLfloat x, GLfloat y, GLfloat z) {
	struct pointNode* tmp = NULL;
	while (node->next != NULL) {
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

//this function will determine the length of the displacement vectors
//it will be 1/50 the shortest side.
GLfloat calcDisplacement(GLfloat xMin, GLfloat xMax, GLfloat yMin, GLfloat yMax, GLfloat zMin, GLfloat zMax) {
	GLfloat lenX = xMax - xMin;
	GLfloat lenY = yMax - yMin;
	GLfloat lenZ = zMax - zMin;

	if (lenX < lenY) {
		if (lenX < lenZ)
			return lenX / 50.0;
		else
			return lenZ / 50.0;
	}
	else {
		if (lenY < lenZ)
			return lenY / 50.0;
		else
			return lenZ / 50.0;
	}
}

GLfloat TR_slope = ((GLfloat) 0.5 + (GLfloat) 0.1) / ((GLfloat)0.5 - (GLfloat) 0.1);
GLfloat BR_slope = ((GLfloat)-0.8 + (GLfloat) 1.4) / ((GLfloat)1 - (GLfloat) 0.5);
GLfloat TL_slope = ((GLfloat) 0.5 + (GLfloat) 0.1) / ((GLfloat)-0.5 + (GLfloat) 0.1);
GLfloat BL_slope = ((GLfloat)-0.8 + (GLfloat) 1.4) / ((GLfloat)-1 + (GLfloat) 0.5);
GLfloat b;

point4 vertices[20] = {
	point4(-1, -.1,  0.5, 1.0),//0//  top left diagonal
	point4(-0.5,  0.5,  0.5, 1.0),//1//left top straight
	point4(0.5,  0.5,  0.5, 1.0),//2// right top straight
	point4(1, -0.1,  0.5, 1.0),//3//top right diagonal

	point4(-1.0, -0.8, 0.5, 1.0),//4//side left straight 
	point4(1.0,  -0.8, 0.5, 1.0),//5// side right straight
	point4(-0.5, -1.4, 0.5, 1.0),//6//bot left straight
	point4(0.5, -1.4, 0.5, 1.0),//7//bot right straight
	//FRONT^^^^^^
	point4(-1, -.1,  -0.5, 1.0),//8//  top left diagonal
	point4(-0.5,  0.5, -0.5, 1.0),//9//left top straight
	point4(0.5,  0.5, -0.5, 1.0),//10// right top straight
	point4(1, -0.1,  -0.5, 1.0),//11//top right diagonal
    point4(-1.0, -0.8, -0.5, 1.0),//12//side left straight 
	point4(1.0,  -0.8, -0.5, 1.0),//13// side right straight
	point4(-0.5, -1.4, -0.5, 1.0),//14//bot left straight
	point4(0.5, -1.4, -0.5, 1.0)//15//bot right straight

};


GLubyte indices[] = {
	0, 8, 4,
	8, 12, 4,//side left square
	8, 9, 1,
	8, 0, 1,//diagonal left square top
	9, 10, 1,
	10, 1, 2, //top square
	10,2,3,
	11,10,3,//diagonal right top
	11, 3, 5,
	11, 13, 5, //side right square
	13, 5, 7,
	13, 15, 7, //diagonal bottom left
	14, 15, 6,
	6, 7, 15,//bottom square
	12,4,14,
	14,6,4,//bot diagonal left
		   //front octagon
		   3,5,7,
		   1,2,3,
		   1,0,4,
		   4,7,6,
		   7,3,1,
		   7,4,1,
		   //back octagon
		   11,13,15,
		   9,10,11,
		   9,8,12,
		   12,15,14,
		   15,11,9,
		   15,12,9
};


GLubyte indices_wire[] = {
	1, 0,
	3, 2,
	1, 2,
	4, 0,
	5, 3,
	6,4,
	7,5,
	6, 7,
	//FRONT^^^^
	0,8,
	1,9,
	2,10,
	3,11,
	4,12,
	5,13,
	6,14,
	7,15,
	9,10,
	10,11,
	11,13,
	13,15,
	15,14,
	14,12,
	12,8,
	8,9
};



///////////////////BROWNIAN STUFF//////////////////////
GLfloat* copyToArray(struct pointNode * head)
{
	GLfloat * retVal;
	pointNode * tmp;
	int count_l;
	count_l = pointCount(head);
	int i = 0;

	count_l *= 3;

	tmp = head;
	if (count_l > 0) {

		retVal = new GLfloat[count_l];
	}
	else {
		return NULL;
	}

	while (i < count_l) {
		retVal[i] = tmp->x;
		retVal[i + 1] = tmp->y;
		retVal[i + 2] = tmp->z;
		tmp = tmp->next;
		i += 3;
	}
	return retVal;
}


void idle(void) {
	glutPostRedisplay();
}



//this function will check to see if the node is within the box
bool checkNode(struct pointNode * curr, GLfloat xMin, GLfloat xMax, GLfloat yMin, GLfloat yMax, GLfloat zMin, GLfloat zMax) {
	//checks the range of the pionts and the slope  if it hit the top left diagonal 
	if (-1 >= curr->x <= -.5 && -.1 >= curr->y <= .5 && -.5 >= curr->z <.5) {
		b = 0.5 - (TL_slope*-0.5); //
		if (curr->y > TL_slope*curr->x + b) {
			hits_wall = 0;
			return false;
		}
	}
	//checks the range of the pionts and the slope  if it hit the bottom left diagonal 
	else if (curr->x < -0.8 && curr->y < -0.5 && -.5 >= curr->z <.5) {
		b = -1 - (BL_slope*-0.8);
		if (curr->y < BL_slope*curr->x + b) {
			hits_wall = 6;
			return false;
		}
	}
	//checks the range of the pionts and the slope  if it hit the top right diagonal 
	else if (curr->x > 0.5 && curr->y > -0.1) {
		b = 0.5 - (TR_slope*0.5);
		if (curr->y > TR_slope*curr->x + b) {
			hits_wall = 2;
			return false;
		}
	}
	//checks the range of the pionts and the slope  if it hit the bottom left diagonal 
	else if (curr->x > 0.5 && curr->y < -0.8 && -.5 >= curr->z <.5) {
		b = -0.8 - (BR_slope * 1);
		if (curr->y < BR_slope*curr->x + b) {
			hits_wall = 4;
			return false;
		}
	}
	//checks the range of the pionts and the slope  if it hit the top left side
	else if (curr->x < xMin) {
		hits_wall = 7;
		return false;
	}
	//checks the range of the pionts and the slope  if it hit the bottom
	else if (curr->y <= -1.4 && -.5 >= curr->x <= .5) {
		hits_wall = 5;
		return false;
	}
	//checks the range of the pionts and the slope  if it hit the back octagon
	else if (curr->z < zMin) {
		hits_wall = 9;
		return false;
	}
	//checks the range of the pionts and the slope  if it hit the right side
	else if (curr->x <= 1 && -.8 >= curr->y <= -.1) {
		hits_wall = 3;
		return false;
	}
	//checks the range of the pionts and the slope  if it hit the top
	else if (curr->y > yMax) {
		hits_wall = 1;
		return false;
	}
	//checks the range of the pionts and the slope  if it hit the front octagon
	else if (curr->z > zMax) {
		hits_wall = 8;
		return false;
	}
	else {
		return true;
	}
}
