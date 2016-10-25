/*
 *
 *
 */

#include "hwk1.h"
#include "hold.h"
#include "Angel.h"
#include<assert.h>
#include <cstdlib>
#include <ctime>
#include <math.h>

///////CONSTANT/////////////////////
#ifndef M_PI
#define M_PI            3.14159265358979323846
#endif


// OpenGL initialization
void
init(){
/**
***  Create and initialize buffer objects
**/
//////////////BROWNIAN INIT////////////////
//Start the Brownian motion
	head = getRandomStart(minX, maxX, minY, maxY, minZ, maxZ);
	curr = head;
	glGenBuffers(8, buffers);
//Vertex buffer for the vertex coordinates
	glBindBuffer(GL_ARRAY_BUFFER, buffers[cube_vertices]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//Elements buffer for the pointers
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[cube_indeces]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[wire_indeces]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_wire), indices_wire, GL_STATIC_DRAW);
	glGenVertexArrays(8, VAO);
// Load shaders and use the resulting shader programs
	program[0] = InitShader("vshader30_TwoCubes_FullPipe.glsl", "fshader30_TwoCubes.glsl");
	program[1] = InitShader("vshader30_TwoCubes_FullPipe.glsl", "fshader6_2.glsl");
	program[4] = InitShader("vshader30_TwoCubes_FullPipe.glsl", "fshader30_TwoCubes.glsl");
	program[5] = InitShader("vshader30_TwoCubes_FullPipe.glsl", "fshader6_2.glsl");
	program[6] = InitShader("vshader30_TwoCubes_FullPipe.glsl", "fshader30_TwoCubes.glsl");
	program[7] = InitShader("vshader30_TwoCubes_FullPipe.glsl", "fshader6_2.glsl");
////////BROWNIAN SHADERS////////////////////////
	program[2] = InitShader("vshader23_v110.glsl", "fshader23_v110.glsl");
	draw_color_loc = glGetUniformLocation(program[2], "vColor");
// set up vertex attributes arrays
//glUseProgram(program[2]);
	glBindVertexArray(VAO[2]);
	GLuint vPosition = glGetAttribLocation(program[2], "vPosition");
	glEnableVertexAttribArray(vPosition);
//done with this packet
	glBindVertexArray(0);

//VAO[0] the Cube 
	glUseProgram(program[4]);
	glBindVertexArray(VAO[4]);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[cube_vertices]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[cube_indeces]);
	GLuint vPosition_Cube2 = glGetAttribLocation(program[4], "vPosition");
	glEnableVertexAttribArray(vPosition_Cube2);
	glVertexAttribPointer(vPosition_Cube2, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
//done with this packet
	glBindVertexArray(0);

//VAO[1] the wireframe
	glUseProgram(program[5]);
	glBindVertexArray(VAO[5]);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[cube_vertices]);
	GLuint vPosition_Wire2 = glGetAttribLocation(program[5], "vPosition");
		glEnableVertexAttribArray(vPosition_Wire2);
		glVertexAttribPointer(vPosition_Wire2, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[wire_indeces]);
//done with this packet
	glBindVertexArray(0);

//VAO[0] the Cube 
	glUseProgram(program[6]);
	glBindVertexArray(VAO[6]);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[cube_vertices]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[cube_indeces]);
	GLuint vPosition_Cube3 = glGetAttribLocation(program[6], "vPosition");
	glEnableVertexAttribArray(vPosition_Cube3);
	glVertexAttribPointer(vPosition_Cube3, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	//done with this packet
	glBindVertexArray(0);

	//VAO[1] the wireframe
	glUseProgram(program[7]);
	glBindVertexArray(VAO[7]);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[cube_vertices]);
	GLuint vPosition_Wire4 = glGetAttribLocation(program[7], "vPosition");
	glEnableVertexAttribArray(vPosition_Wire4);
	glVertexAttribPointer(vPosition_Wire4, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[wire_indeces]);
	//done with this packet
	glBindVertexArray(0);

	//VAO[0] the Cube 
	glUseProgram(program[0]);
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[cube_vertices]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[cube_indeces]);
	GLuint vPosition_Cube = glGetAttribLocation(program[0], "vPosition");
	glEnableVertexAttribArray(vPosition_Cube);
	glVertexAttribPointer(vPosition_Cube, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	//done with this packet
	glBindVertexArray(0);

	//VAO[1] the wireframe
	glUseProgram(program[1]);
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[cube_vertices]);
	GLuint vPosition_Wire = glGetAttribLocation(program[1], "vPosition");
	glEnableVertexAttribArray(vPosition_Wire);
	glVertexAttribPointer(vPosition_Wire, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[wire_indeces]);
	//done with this packet
	glBindVertexArray(0);

	glUseProgram(0);

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void
display(void){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Make sure you start with the Default Coordinate Systems
	projmat = mat4(1.0);
	modelviewStackTop = mat4(1.0);
	mat4 modelviewStackBottom = modelviewStackTop;
	glUniformMatrix4fv(projmat_loc, 1, GL_TRUE, projmat);

	//Set up the camera optics
	projmat = projmat*Perspective(30, 1.0, 0.1, 20.0);
	//Position and orient the camera
	modelviewStackTop = modelviewStackTop*LookAt(eye, eye - n, v);
	modelviewStackTop = modelviewStackTop*Translate(0.15, 0.15, -2.5);
	//Spin the whole scene by pressing the X key
	modelviewStackTop = modelviewStackTop*RotateX(theta);
	modelviewStackTop = modelviewStackTop*RotateY(theta_y);
	modelviewStackTop = modelviewStackTop*RotateY(phi);
	modelviewStackTop = modelviewStackTop*RotateZ(theta_z);

	modelviewStackBottom = modelviewStackTop; //mvstack.push

	if (bComplete == true) {
		if (hits_wall == 1) {
			glUseProgram(program[0]);
			color_loc = glGetUniformLocation(program[0], "color");
			proj_loc = glGetUniformLocation(program[0], "projection");
			model_view_loc = glGetUniformLocation(program[0], "modelview");
			glUniformMatrix4fv(proj_loc, 1, GL_TRUE, projmat);
			glUniformMatrix4fv(model_view_loc, 1, GL_TRUE, modelviewStackTop);
			glUniform4fv(color_loc, 1, orange);
			glEnable(GL_POLYGON_OFFSET_FILL);
			glPolygonOffset(1.0, 1.0);
			glBindVertexArray(VAO[0]);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, BUFFER_OFFSET(12)); //top 
			glDisable(GL_POLYGON_OFFSET_FILL);

			modelviewStackTop = modelviewStackBottom; //mvstack.pop
		}
		else if (hits_wall == 2){
			
			glUseProgram(program[0]);
			color_loc = glGetUniformLocation(program[0], "color");
			proj_loc = glGetUniformLocation(program[0], "projection");
			model_view_loc = glGetUniformLocation(program[0], "modelview");
			glUniformMatrix4fv(proj_loc, 1, GL_TRUE, projmat);
			glUniformMatrix4fv(model_view_loc, 1, GL_TRUE, modelviewStackTop);
			glUniform4fv(color_loc, 1, orange);
			glEnable(GL_POLYGON_OFFSET_FILL);
			glPolygonOffset(1.0, 1.0);
			glBindVertexArray(VAO[0]);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, BUFFER_OFFSET(18)); //top right
			glDisable(GL_POLYGON_OFFSET_FILL);

			modelviewStackTop = modelviewStackBottom; //mvstack.pop
		}
		else if (hits_wall == 3){
			glUseProgram(program[0]);
			color_loc = glGetUniformLocation(program[0], "color");
			proj_loc = glGetUniformLocation(program[0], "projection");
			model_view_loc = glGetUniformLocation(program[0], "modelview");
			glUniformMatrix4fv(proj_loc, 1, GL_TRUE, projmat);
			glUniformMatrix4fv(model_view_loc, 1, GL_TRUE, modelviewStackTop);
			glUniform4fv(color_loc, 1, orange);
			glEnable(GL_POLYGON_OFFSET_FILL);
			glPolygonOffset(1.0, 1.0);
			glBindVertexArray(VAO[0]);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, BUFFER_OFFSET(24)); //right
			glDisable(GL_POLYGON_OFFSET_FILL);
			modelviewStackTop = modelviewStackBottom; //mvstack.pop
		}
		else if (hits_wall == 4){
			glUseProgram(program[0]);
			color_loc = glGetUniformLocation(program[0], "color");
			proj_loc = glGetUniformLocation(program[0], "projection");
			model_view_loc = glGetUniformLocation(program[0], "modelview");
			glUniformMatrix4fv(proj_loc, 1, GL_TRUE, projmat);
			glUniformMatrix4fv(model_view_loc, 1, GL_TRUE, modelviewStackTop);
			glUniform4fv(color_loc, 1, orange);
			glEnable(GL_POLYGON_OFFSET_FILL);
			glPolygonOffset(1.0, 1.0);
			glBindVertexArray(VAO[0]);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, BUFFER_OFFSET(30));//bottom right
			glDisable(GL_POLYGON_OFFSET_FILL);
			modelviewStackTop = modelviewStackBottom; //mvstack.pop
		}
		else if (hits_wall == 5){
			glUseProgram(program[0]);
			color_loc = glGetUniformLocation(program[0], "color");
			proj_loc = glGetUniformLocation(program[0], "projection");
			model_view_loc = glGetUniformLocation(program[0], "modelview");
			glUniformMatrix4fv(proj_loc, 1, GL_TRUE, projmat);
			glUniformMatrix4fv(model_view_loc, 1, GL_TRUE, modelviewStackTop);
			glUniform4fv(color_loc, 1, orange);
			glEnable(GL_POLYGON_OFFSET_FILL);
			glPolygonOffset(1.0, 1.0);
			glBindVertexArray(VAO[0]);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, BUFFER_OFFSET(36));  //bottom 
			glDisable(GL_POLYGON_OFFSET_FILL);
			modelviewStackTop = modelviewStackBottom; //mvstack.pop
		}
		else if (hits_wall == 6) {
			glUseProgram(program[0]);
			color_loc = glGetUniformLocation(program[0], "color");
			proj_loc = glGetUniformLocation(program[0], "projection");
			model_view_loc = glGetUniformLocation(program[0], "modelview");
			glUniformMatrix4fv(proj_loc, 1, GL_TRUE, projmat);
			glUniformMatrix4fv(model_view_loc, 1, GL_TRUE, modelviewStackTop);
			glUniform4fv(color_loc, 1, orange);
			glEnable(GL_POLYGON_OFFSET_FILL);
			glPolygonOffset(1.0, 1.0);
			glBindVertexArray(VAO[0]);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, BUFFER_OFFSET(42)); //bottom left
			glDisable(GL_POLYGON_OFFSET_FILL);
			modelviewStackTop = modelviewStackBottom; //mvstack.pop
		}
		else if (hits_wall == 7){
			glUseProgram(program[0]);
			color_loc = glGetUniformLocation(program[0], "color");
			proj_loc = glGetUniformLocation(program[0], "projection");
			model_view_loc = glGetUniformLocation(program[0], "modelview");
			glUniformMatrix4fv(proj_loc, 1, GL_TRUE, projmat);
			glUniformMatrix4fv(model_view_loc, 1, GL_TRUE, modelviewStackTop);
			glUniform4fv(color_loc, 1, orange);
			glEnable(GL_POLYGON_OFFSET_FILL);
			glPolygonOffset(1.0, 1.0);
			glBindVertexArray(VAO[0]);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, BUFFER_OFFSET(6));//left
			glDisable(GL_POLYGON_OFFSET_FILL);
			modelviewStackTop = modelviewStackBottom; //mvstack.pop
		}
		else if (hits_wall == 8){
			glUseProgram(program[0]);
			color_loc = glGetUniformLocation(program[0], "color");
			proj_loc = glGetUniformLocation(program[0], "projection");
			model_view_loc = glGetUniformLocation(program[0], "modelview");
			glUniformMatrix4fv(proj_loc, 1, GL_TRUE, projmat);
			glUniformMatrix4fv(model_view_loc, 1, GL_TRUE, modelviewStackTop);
			glUniform4fv(color_loc, 1, orange);
			glEnable(GL_POLYGON_OFFSET_FILL);
			glPolygonOffset(1.0, 1.0);
			glBindVertexArray(VAO[0]);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, BUFFER_OFFSET(60));
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, BUFFER_OFFSET(54));
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, BUFFER_OFFSET(48));  //front octagon
			glDisable(GL_POLYGON_OFFSET_FILL);
			modelviewStackTop = modelviewStackBottom; //mvstack.pop
		}
		else if (hits_wall == 9){
			glUseProgram(program[0]);
			color_loc = glGetUniformLocation(program[0], "color");
			proj_loc = glGetUniformLocation(program[0], "projection");
			model_view_loc = glGetUniformLocation(program[0], "modelview");
			glUniformMatrix4fv(proj_loc, 1, GL_TRUE, projmat);
			glUniformMatrix4fv(model_view_loc, 1, GL_TRUE, modelviewStackTop);
			glUniform4fv(color_loc, 1, orange);
			glEnable(GL_POLYGON_OFFSET_FILL);
			glPolygonOffset(1.0, 1.0);
			glBindVertexArray(VAO[0]);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, BUFFER_OFFSET(78));
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, BUFFER_OFFSET(72));
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, BUFFER_OFFSET(66));// back octagon
			glDisable(GL_POLYGON_OFFSET_FILL);
			modelviewStackTop = modelviewStackBottom; //mvstack.pop
		}
else{
	glUseProgram(program[0]);
	color_loc = glGetUniformLocation(program[0], "color");
	proj_loc = glGetUniformLocation(program[0], "projection");
	model_view_loc = glGetUniformLocation(program[0], "modelview");
	glUniformMatrix4fv(proj_loc, 1, GL_TRUE, projmat);
	glUniformMatrix4fv(model_view_loc, 1, GL_TRUE, modelviewStackTop);
	glUniform4fv(color_loc, 1, orange);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.0, 1.0);
	glBindVertexArray(VAO[0]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, BUFFER_OFFSET(6));//top left
	glDisable(GL_POLYGON_OFFSET_FILL);
	modelviewStackTop = modelviewStackBottom; //mvstack.pop
	}
}
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//Render wireframe
	glUseProgram(program[1]);
	proj_loc = glGetUniformLocation(program[1], "projection");
	model_view_loc = glGetUniformLocation(program[1], "modelview");
	GLuint color_loc1 = glGetUniformLocation(program[1], "color");
	glUniformMatrix4fv(proj_loc, 1, GL_TRUE, projmat);
	glUniformMatrix4fv(model_view_loc, 1, GL_TRUE, modelviewStackTop);
	glBindVertexArray(VAO[1]);
	glDrawElements(GL_LINES, 100, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
	modelviewStackTop = modelviewStackBottom; //mvstack.pop
	// shows end point when trajectory is done
if(bComplete==true) {
	//Render wireframe
	glUseProgram(program[4]);
	proj_loc = glGetUniformLocation(program[4], "projection");
	model_view_loc = glGetUniformLocation(program[4], "modelview");
	GLuint color_loc2 = glGetUniformLocation(program[4], "color");
	glUniformMatrix4fv(proj_loc, 1, GL_TRUE, projmat);
	glUniformMatrix4fv(model_view_loc, 1, GL_TRUE, modelviewStackTop);
	glBindVertexArray(VAO[1]);
	glDrawElements(GL_LINES, 100, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
	modelviewStackTop = modelviewStackBottom*Translate(curr->x, curr->y, curr->z)*Scale(0.5 / 20, 0.5 / 20, 0.5 / 20); //mvstack.pop
	//Render surface mesh
	glUseProgram(program[5]);
	color_loc = glGetUniformLocation(program[5], "color");
	proj_loc = glGetUniformLocation(program[5], "projection");
	model_view_loc = glGetUniformLocation(program[5], "modelview");
	glUniformMatrix4fv(proj_loc, 1, GL_TRUE, projmat);
	glUniformMatrix4fv(model_view_loc, 1, GL_TRUE, modelviewStackTop);
	glUniform4fv(color_loc, 1, red_transparent);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.0, 1.0);
	glBindVertexArray(VAO[0]);
	glDrawElements(GL_TRIANGLES, 100, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
	glDisable(GL_POLYGON_OFFSET_FILL);
	modelviewStackTop = modelviewStackBottom; //mvstack.pop
}
//renders the start point
//Render wireframe
	glUseProgram(program[6]);
	proj_loc = glGetUniformLocation(program[6], "projection");
	model_view_loc = glGetUniformLocation(program[6], "modelview");
	GLuint color_loc = glGetUniformLocation(program[6], "color");
	glUniformMatrix4fv(proj_loc, 1, GL_TRUE, projmat);
	glUniformMatrix4fv(model_view_loc, 1, GL_TRUE, modelviewStackTop);
	glBindVertexArray(VAO[1]);
	glDrawElements(GL_LINES, 100, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
	modelviewStackTop = modelviewStackBottom*Translate(head->x, head->y, head->z)*Scale(0.5 / 15, 0.5 / 15, 0.5 / 15); //mvstack.pop
	 //Render surface mesh
	glUseProgram(program[7]);
	color_loc = glGetUniformLocation(program[7], "color");
	proj_loc = glGetUniformLocation(program[7], "projection");
	model_view_loc = glGetUniformLocation(program[7], "modelview");
	glUniformMatrix4fv(proj_loc, 1, GL_TRUE, projmat);
	glUniformMatrix4fv(model_view_loc, 1, GL_TRUE, modelviewStackTop);
	glUniform4fv(color_loc, 1, pink_transparent);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.0, 1.0);
	glBindVertexArray(VAO[0]);glDrawElements(GL_TRIANGLES, 100, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
	glDisable(GL_POLYGON_OFFSET_FILL);
	modelviewStackTop = modelviewStackBottom; //mvstack.pop

	 //Render surface mesh
	glUseProgram(program[0]);
	color_loc = glGetUniformLocation(program[0], "color");
	proj_loc = glGetUniformLocation(program[0], "projection");
	model_view_loc = glGetUniformLocation(program[0], "modelview");
	glUniformMatrix4fv(proj_loc, 1, GL_TRUE, projmat);
	glUniformMatrix4fv(model_view_loc, 1, GL_TRUE, modelviewStackTop);
	glUniform4fv(color_loc, 1, transparent);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.0, 1.0);
	glBindVertexArray(VAO[0]);
	glDrawElements(GL_TRIANGLES, 100, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
	glDisable(GL_POLYGON_OFFSET_FILL);

	modelviewStackTop = modelviewStackBottom; //mvstack.pop
	 
	//Draw trajectory
	glUseProgram(program[2]);
	color_loc = glGetUniformLocation(program[2], "color");
	model_view_loc = glGetUniformLocation(program[2], "modelview");
	glUniformMatrix4fv(proj_loc, 1, GL_TRUE, projmat);
	glUniformMatrix4fv(model_view_loc, 1, GL_TRUE, modelviewStackTop);

	//copy the trajectory into a buffer 
	GLfloat * trajectoryBuffer = copyToArray(head);
	glBindVertexArray(VAO[2]);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[trajectory]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * pointCount(head), trajectoryBuffer, GL_STREAM_DRAW);
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glUniform4fv(draw_color_loc, 1, blue_trajectory);
	glDrawArrays(GL_LINE_STRIP, 0, pointCount(head));

	//glutSwapBuffers();

	modelviewStackTop = modelviewStackBottom;
	delete[] trajectoryBuffer; 

	glDepthMask(GL_TRUE);

	glutSwapBuffers();
}

//----------------------------------------------------------------------------

void
keyboard(unsigned char key, int x, int y){
	switch (key) {

	case 'x': {	theta += step;
		if (theta > 360.0) {
			theta -= 360.0;
		}
	}
			  break;
	case 'X': {	theta -= step;
		if (theta < -360.0) {
			theta += 360.0;
		}
	}
			  break;

	
	case 'Z': {	theta_z -= step;
		if (theta_z < 360.0) {
			theta_z += 360.0;
		}
	}
			  break;
	case 'z': {	theta_z += step;
		if (theta_z > 360.0) {
			theta_z -= 360.0;
		}
	}
			  break;
	case 'y':{theta_y += step;
		if (theta_y > 360.0) {
			theta_y -= -360.0;
		}
	}
			  break;
	case 'Y': {	theta_y -= step;
		if (theta_y < 360.0) {
			theta_y += -360.0;
		}
	}
			  break;
	
	case 's': {
		bStarted = true;
		if (bStarted == true)
		{
			//bStarted = true;
			glutTimerFunc(1000, animate, 0);
		}
	}
			  break;
	case 'S': {
		bStarted = true;
		if (bStarted == true)
		{
			//bStarted = true;
			glutTimerFunc(1000, animate, 0);
		}
	}
			  break;
			 
	case 'i': case 'I': {
		bPaused = !bPaused;
		if (!bPaused)
			animate(0);
		break;
	}
	case 033:  // Escape key
	case 'q': case 'Q':
		exit(EXIT_SUCCESS);
		break;
	}
}


void animate(int i){
	GLfloat x, y, z;
	pointNode * last;
	if (!bPaused && !bComplete)
	{
		GLfloat displacement = calcDisplacement(minX, maxX, minY, maxY, minZ, maxZ);

		last = curr;
		randomDisplacement(displacement, x, y, z);
		curr = AddNode(curr, curr->x + x, curr->y + y, curr->z + z);
		int count_l;
		count_l = pointCount(head);

		glutPostRedisplay();
		//We only want to keep going if 
		if (checkNode(curr, minX, maxX, minY, maxY, minZ, maxZ)){
			//keep a roughly constant fps
			glutTimerFunc(17, animate, 0);
		}
		else{
			findExitPoint(last, curr);
			bComplete = true;
		}
	}
}
void findExitPoint(struct pointNode * prev, struct pointNode * last){
	GLfloat slope;
	GLfloat b; // y -intercept of  the line y = slope*x + b

	GLfloat yExit;
	GLfloat xExit;
	GLfloat zExit;

	//this will make sure one of the nodes is inside the other is outside
	if (checkNode(prev, minX, maxX, minY, maxY, minZ, maxZ) && !checkNode(last, minX, maxX, minY, maxY, minZ, maxZ)){
		slope = (last->y - prev->y) / (last->x - prev->x);  //last is current
		b = prev->y - slope*prev->x;

		if (last->x > maxX){
			yExit = slope * maxX + b;
			xExit = maxX;
			if (yExit < minY){
				yExit = minY;
				xExit = (yExit - b) / slope;
			}
			if (yExit > maxY){
				yExit = maxY;
				xExit = (yExit - b) / slope;
			}
		}
		else if (last->x < minX){
			yExit = slope * minX + b;
			xExit = minX;
			if (yExit < minY){
				yExit = minY;
				xExit = (yExit - b) / slope;
			}
			if (yExit > maxY)
			{
				yExit = maxY;
				xExit = (yExit - b) / slope;
			}
		}
		else if (last->y > maxY){
			yExit = maxY;
			xExit = (yExit - b) / slope;
		}
		else if (last->y < minY){
			yExit = minY;
			xExit = (yExit - b) / slope;
		}

	}
}

void specKey(int key, int x, int y){
	switch (key) {

	case GLUT_KEY_UP: // MOVE FORWARD
		eye[0] -= SCALE_VECTOR * n[0];
		eye[1] -= SCALE_VECTOR * n[1];
		eye[2] -= SCALE_VECTOR * n[2];
		break;
	case GLUT_KEY_DOWN: // MOVE BACKWARD
		eye[0] += SCALE_VECTOR * n[0];
		eye[1] += SCALE_VECTOR * n[1];
		eye[2] += SCALE_VECTOR * n[2];
		break;
	case GLUT_KEY_LEFT: // MOVE LEFT
		eye[0] -= SCALE_VECTOR * u[0];
		eye[1] -= SCALE_VECTOR * u[1];
		eye[2] -= SCALE_VECTOR * u[2];
		break;
	case GLUT_KEY_RIGHT: // MOVE RIGHT
		eye[0] += SCALE_VECTOR * u[0];
		eye[1] += SCALE_VECTOR * u[1];
		eye[2] += SCALE_VECTOR * u[2];
		break;
	}
}

static void
mouse(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			moving = 1;
			startx = x;
			starty = y;
		}
		if (state == GLUT_UP) {
			moving = 0;
		}
	}
}

static void
motion(int x, int y) {
	if (moving) {
		phi = phi + (x - startx);
		theta = theta + (y - starty);
		startx = x;
		starty = y;
		glutPostRedisplay();
	}
}

int main(int argc, char **argv){

	srand(time(NULL));
	rand();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Pointers-to-Vertex, VAOs, Multiple Pipelines");
	m_glewInitAndVersion();

	init();
	
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specKey);
	glutIdleFunc(idle);
	glutMouseFunc(mouse);
	glutMotionFunc( motion);
    
	glutMainLoop();
	return 0;
}

void m_glewInitAndVersion(void) {
	fprintf(stdout, "OpenGL Version: %s\n", glGetString(GL_VERSION));
	fprintf(stdout, "GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
}

void reshape(int width, int height) {
//the same objects are shown possibly distorted  
//original viewport is a square
glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}
