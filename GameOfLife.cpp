//
// Created by Patrick Niccolai on 2019-12-03.
//

#include "GameOfLife.h"
#include "LiveCell.h"
#include "DeadCell.h"
#include <iostream>
#include <time.h>
#include <vector>
#include <fstream>
using namespace std;

const int GRID_MARGIN = 50;
const int CELL_SIZE = 10;
const int GRID_WIDTH = 50;
const int GRID_HEIGHT = 80;
GLdouble width, height;
bool gameHasStarted = false;
int wd;
Cell *grid[GRID_HEIGHT][GRID_WIDTH];


//function initializes the grid when the program loads
void gridInit() {
    for(int row = 0; row < GRID_HEIGHT; row++){
        for(int col = 0; col < GRID_WIDTH; col++){
            grid[row][col] = new DeadCell({(row * CELL_SIZE) + GRID_MARGIN, (col * CELL_SIZE) + GRID_MARGIN}, CELL_SIZE, CELL_SIZE);
        }
    }
    ifstream inputFile;
    inputFile.open("../pattern1.txt");
    int x;
    int y;
    while(inputFile >> x >> y) {
        grid[x][y] = new LiveCell({(x * CELL_SIZE) + GRID_MARGIN, (y * CELL_SIZE) + GRID_MARGIN}, CELL_SIZE,CELL_SIZE);
    }
}
//This function updates the grid one tick each time it is called
void gridChanges(int dummy) {
    vector<vector<int>> gridMask(GRID_HEIGHT, vector<int> (GRID_WIDTH, 0));
    for(int row = 0; row < GRID_HEIGHT; row++){
        for(int col = 0; col < GRID_WIDTH; col++){
            Cell *topLeft, *top, *topRight, *left, *right, *bottomLeft, *bottom, *bottomRight;
            //creates a dummy cell to pass into the change function if the cell is next to a wall
            if(row-1 >= 0 && row-1 < GRID_HEIGHT && col-1 >= 0 && col-1 < GRID_WIDTH) {
                topLeft = grid[row-1][col-1];
            }
            else {
                topLeft = new DeadCell({0, 0}, 10, 10);
            }
            if(row-1 >= 0 && row-1 < GRID_HEIGHT && col >= 0 && col < GRID_WIDTH) {
                top = grid[row-1][col];
            }
            else {
                top = new DeadCell({0, 0}, 10, 10);
            }
            if(row-1 >= 0 && row-1 < GRID_HEIGHT && col+1 >= 0 && col+1 < GRID_WIDTH) {
                topRight = grid[row-1][col+1];
            }
            else {
                topRight = new DeadCell({0, 0}, 10, 10);
            }
            if(row >= 0 && row < GRID_HEIGHT && col-1 >= 0 && col-1 < GRID_WIDTH) {
                left = grid[row][col-1];
            }
            else {
                left = new DeadCell({0, 0}, 10, 10);
            }
            if(row >= 0 && row < GRID_HEIGHT && col+1 >= 0 && col+1 < GRID_WIDTH) {
                right = grid[row][col+1];
            }
            else {
                right = new DeadCell({0, 0}, 10, 10);
            }
            if(row+1 >= 0 && row+1 < GRID_HEIGHT && col-1 >= 0 && col-1 < GRID_WIDTH) {
                bottomLeft = grid[row+1][col-1];
            }
            else {
                bottomLeft = new DeadCell({0, 0}, 10, 10);
            }
            if(row+1 >= 0 && row+1 < GRID_HEIGHT && col >= 0 && col < GRID_WIDTH) {
                bottom = grid[row+1][col];
            }
            else {
                bottom = new DeadCell({0, 0}, 10, 10);
            }
            if(row+1 >= 0 && row+1 < GRID_HEIGHT && col+1 >= 0 && col+1 < GRID_WIDTH) {
                bottomRight = grid[row+1][col+1];
            }
            else {
                bottomRight = new DeadCell({0, 0}, 10, 10);
            }

            //have to make a mask for the grid because updating cells one at a time causes cells to update incorrectly
            if(grid[row][col]->change(*topLeft, *top, *topRight, *right, *bottomRight, *bottom, *bottomLeft, *left)) {
                gridMask[row][col] = 1;
            }
            else {
               gridMask[row][col] = 0;
            }
        }
    }
    for(int row = 0; row < GRID_HEIGHT; row++){
        for(int col = 0; col < GRID_WIDTH; col++) {
            if(gridMask[row][col] == 1) {
                grid[row][col] = new LiveCell({(row * CELL_SIZE) + GRID_MARGIN, (col * CELL_SIZE) + GRID_MARGIN}, CELL_SIZE, CELL_SIZE);
            }
            else {
                grid[row][col] = new DeadCell({(row * CELL_SIZE) + GRID_MARGIN, (col * CELL_SIZE) + GRID_MARGIN}, CELL_SIZE, CELL_SIZE);
            }
        }
    }
}

void init() {
    width = 900;
    height = 600;
    srand(time(0));
    gridInit();
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(1.0f, 0.0f, 1.0f, 1.0f); // Black and opaque
}

void displayFirstScreen(){
    // tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height);

    // do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f);

    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glColor3f(0, 0, 0);
    glRasterPos2i(10, 15);
    for (const char &letter : "Welcome to Conway's Game of Life") {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
    }

    glRasterPos2i(10, 35);
    for (const char &letter : "Click on a cell to change its color. Press C to continue") {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
    }
    //I want to display the grid on the starting screen so that people can click cells before the game starts
    for(int row = 0; row < GRID_HEIGHT; row++){
        for(int col = 0; col < GRID_WIDTH; col++){
            grid[row][col]->draw();
        }
    }

    glFlush();  // Render now
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void displayGameOfLife() {
    // tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height);

    // do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f);

    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glColor3f(0, 0, 0);
    glRasterPos2i(10, 15);
    for (const char &letter : "Press E to end the simulation") {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
    }

    //Create the grid
    for(int row = 0; row < GRID_HEIGHT; row++){
        for(int col = 0; col < GRID_WIDTH; col++){

            grid[row][col]->draw();
        }
    }

    glFlush();  // Render now
}

void displayEndScreen(){
    // tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height);

    // do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f);

    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glColor3f(0, 0, 0);
    glRasterPos2i(100, 100);
    for (const char &letter : "The End :^)") {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
    }

    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y) {
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }

    if (key == 99) {
        glutDisplayFunc(displayGameOfLife);
        if(!gameHasStarted) {
            glutTimerFunc(0, timer, 0);
            gameHasStarted = true;
        }
    }

    if (key == 101) {
        glutDisplayFunc(displayEndScreen);
    }

    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {

    glutPostRedisplay();
}

void cursor(int x, int y) {

    for(int row = 0; row < GRID_HEIGHT; row++){
        for(int col = 0; col < GRID_WIDTH; col++) {
            if(grid[row][col]->isOverlapping(x, y)) {
                grid[row][col]->hover();
            }
            else {
                grid[row][col]->unHover();
            }
        }
    }

    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {

    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        for(int row = 0; row < GRID_HEIGHT; row++){
            for(int col = 0; col < GRID_WIDTH; col++){
                if(grid[row][col]->isOverlapping(x, y)) {
                    //TODO: make this only work during the starting screen
                    //here whichever type of cell is in grid[row][col] should switch to the other type of cell
                    if(grid[row][col]->cellType()) {
                        grid[row][col] = new DeadCell({(row * CELL_SIZE) + GRID_MARGIN, (col * CELL_SIZE) + GRID_MARGIN}, CELL_SIZE, CELL_SIZE);
                    }
                    else {
                        grid[row][col] = new LiveCell({(row * CELL_SIZE) + GRID_MARGIN, (col * CELL_SIZE) + GRID_MARGIN}, CELL_SIZE, CELL_SIZE);
                    }
                    glutPostRedisplay();
                }
            }
        }
    }
    glutPostRedisplay();
}

void timer(int dummy) {
    gridChanges(0);

    glutPostRedisplay();
    glutTimerFunc(500, timer, dummy);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    init();

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int) width, (int) height);
    glutInitWindowPosition(100, 200); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Patrick and Nevin and Conway's Game of Life!" /* title */ );

    glutDisplayFunc(displayFirstScreen);

    // Our own OpenGL initialization
    initGL();

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);

    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);

    // handles mouse movement
    glutPassiveMotionFunc(cursor);

    // handles mouse click
    glutMouseFunc(mouse);

    // handles timer
    //glutTimerFunc(0, timer, 0);

    // Enter the event-processing loop
    glutMainLoop();
    timer(0);
    return 0;
}
