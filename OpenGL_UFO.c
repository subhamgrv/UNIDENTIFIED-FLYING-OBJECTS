#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef WIN32
#include <unistd.h>
#else
#define random rand
#endif

#include <GL/glut.h>

#ifndef M_PI
#define M_PI 3.14159265
#endif

#ifndef M_PI_2
#define M_PI_2 1.57079632
#endif

#define MAX_OBJECTS 15

#define MENU_ADD      1
#define MENU_REMOVE   2
#define MENU_START    3
#define MENU_STOP     4
#define MENU_EXIT     5

GLboolean animationRunning = GL_FALSE;

/* Structure describing a flying object */
typedef struct
{
    float velocity;
    float theta;
    float posX, posY, posZ;
    float rotation;
} FlyingObject;

FlyingObject fleet[MAX_OBJECTS];


/* -------------------------------------------------- */
/* Render Scene                                        */
/* -------------------------------------------------- */

void renderScene(void)
{
    int i;

    glClear(GL_DEPTH_BUFFER_BIT);

    /* Draw gradient background */
    glDisable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    glBegin(GL_POLYGON);
        glColor3f(0.0,0.0,0.0);
        glVertex3f(-20,20,-19);
        glVertex3f(20,20,-19);

        glColor3f(0.0,0.5,1.0);
        glVertex3f(20,-20,-19);
        glVertex3f(-20,-20,-19);
    glEnd();

    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);

    /* Draw each UFO */
    for(i = 0; i < MAX_OBJECTS; i++)
    {
        if(fleet[i].velocity == 0.0)
            continue;

        /* Dome */
        glPushMatrix();
        glTranslatef(fleet[i].posX, fleet[i].posY, fleet[i].posZ);
        glRotatef(290.0,1,0,0);
        glRotatef(fleet[i].rotation,0,0,1);
        glScalef(0.33,0.25,0.25);
        glTranslatef(0,-4,-1.5);

        glColor3f(1,1,1);
        glutWireSphere(1.5,15,15);
        glPopMatrix();


        /* Body */
        glPushMatrix();
        glTranslatef(fleet[i].posX, fleet[i].posY, fleet[i].posZ);
        glRotatef(290.0,1,0,0);
        glRotatef(fleet[i].rotation,0,0,1);
        glScalef(0.33,0.25,0.25);
        glTranslatef(0.75,-4,-1.5);

        glColor3f(1,0,0);
        glutSolidTeapot(1.15);
        glPopMatrix();


        /* Beam / Cone */
        glPushMatrix();
        glTranslatef(fleet[i].posX, fleet[i].posY, fleet[i].posZ);
        glRotatef(290.0,1,0,0);
        glRotatef(fleet[i].rotation,0,0,1);
        glScalef(0.33,0.25,0.25);
        glTranslatef(0.95,-4,-1.5);

        glColor3f(0,0,0);
        glutSolidCone(3.75,0.5,14,5);
        glPopMatrix();
    }

    glutSwapBuffers();
}


/* -------------------------------------------------- */
/* Update movement of one UFO                          */
/* -------------------------------------------------- */

void updateObject(int i)
{
    float t = fleet[i].theta += fleet[i].velocity;

    fleet[i].posZ = -9 + 4 * cos(t);
    fleet[i].posX = 4 * sin(2 * t);
    fleet[i].posY = 3 * sin(t / 3.4);

    fleet[i].rotation =
        (((2.0) + M_PI_2) * sin(t) - M_PI_2) * 180 / M_PI;

    if(fleet[i].velocity < 0)
        fleet[i].rotation += 180;
}


/* -------------------------------------------------- */
/* Add UFO                                             */
/* -------------------------------------------------- */

void createObject()
{
    int i;

    for(i = 0; i < MAX_OBJECTS; i++)
    {
        if(fleet[i].velocity == 0)
        {
            fleet[i].velocity = ((float)(random()%20))*0.0001 + 0.02;

            if(random() & 1)
                fleet[i].velocity *= -1;

            fleet[i].theta = ((float)(random()%257)) * 0.1111;

            updateObject(i);

            if(!animationRunning)
                glutPostRedisplay();

            return;
        }
    }
}


/* -------------------------------------------------- */
/* Remove UFO                                          */
/* -------------------------------------------------- */

void deleteObject()
{
    int i;

    for(i = MAX_OBJECTS-1; i >= 0; i--)
    {
        if(fleet[i].velocity != 0)
        {
            fleet[i].velocity = 0;

            if(!animationRunning)
                glutPostRedisplay();

            return;
        }
    }
}


/* -------------------------------------------------- */
/* Update all UFO positions                            */
/* -------------------------------------------------- */

void updateFleet()
{
    int i;

    for(i = 0; i < MAX_OBJECTS; i++)
        if(fleet[i].velocity != 0)
            updateObject(i);
}


/* -------------------------------------------------- */
/* Animation                                           */
/* -------------------------------------------------- */

void animateScene()
{
    updateFleet();
    glutPostRedisplay();
}


/* -------------------------------------------------- */
/* Window visibility                                   */
/* -------------------------------------------------- */

void visibilityHandler(int state)
{
    if(state == GLUT_VISIBLE)
    {
        if(animationRunning)
            glutIdleFunc(animateScene);
    }
    else
    {
        glutIdleFunc(NULL);
    }
}


/* -------------------------------------------------- */
/* Keyboard input                                      */
/* -------------------------------------------------- */

void keyboardHandler(unsigned char key,int x,int y)
{
    switch(key)
    {
        case ' ':
            if(!animationRunning)
            {
                updateFleet();
                glutPostRedisplay();
            }
            break;

        case 27:
            exit(0);
            break;
    }
}


/* -------------------------------------------------- */
/* Menu actions                                        */
/* -------------------------------------------------- */

void menuHandler(int option)
{
    switch(option)
    {
        case MENU_ADD:
            createObject();
            break;

        case MENU_REMOVE:
            deleteObject();
            break;

        case MENU_START:
            animationRunning = GL_TRUE;
            glutIdleFunc(animateScene);
            break;

        case MENU_STOP:
            animationRunning = GL_FALSE;
            glutIdleFunc(NULL);
            break;

        case MENU_EXIT:
            exit(0);
    }
}


/* -------------------------------------------------- */
/* Main Program                                        */
/* -------------------------------------------------- */

int main(int argc,char *argv[])
{
    glutInit(&argc,argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Flying UFO Simulation");

    glutDisplayFunc(renderScene);
    glutKeyboardFunc(keyboardHandler);
    glutVisibilityFunc(visibilityHandler);

    /* Menu */
    glutCreateMenu(menuHandler);
    glutAddMenuEntry("Add UFO",MENU_ADD);
    glutAddMenuEntry("Remove UFO",MENU_REMOVE);
    glutAddMenuEntry("Start Motion",MENU_START);
    glutAddMenuEntry("Stop Motion",MENU_STOP);
    glutAddMenuEntry("Exit",MENU_EXIT);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    /* OpenGL setup */
    glClearDepth(1.0);
    glClearColor(0,0,0,0);

    glMatrixMode(GL_PROJECTION);
    glFrustum(-1,1,-1,1,1,20);

    glMatrixMode(GL_MODELVIEW);

    /* Initial objects */
    createObject();
    createObject();
    createObject();

    glutMainLoop();

    return 0;
}