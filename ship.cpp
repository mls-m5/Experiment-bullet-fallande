#include "ship.h"
#include <GL/gl.h>
#include <math.h>
#include <iostream>

using namespace std;

void Ship::Update(double t)
{
    if (activeCmd[CMD_LEFT]){
        angle += .1;
    }
    if (activeCmd[CMD_RIGHT]){
        angle -= .1;
    }
    
    double sx(-sin(angle)), sy(cos(angle));
    
    if (activeCmd[CMD_FORWARD]){
        vel.x += sx * t;
        vel.y += sy * t;
    }
    
    if (activeCmd[CMD_BACKWARD]){
        vel.x -= sx * t;
        vel.y -= sy * t;
    }
    
    pos += vel;
}

void Ship::Render()
{
    glPushMatrix();
    glScaled(.1, .1, .1);
    glTranslated(pos.x, pos.y, pos.z);
    glRotated(angle * 180 / pi, 0,0,1);
        
    glBegin(GL_TRIANGLE_FAN);
    
    glColor3f(1,1,1);
    glVertex2f(0,1);
    glVertex2f(.3,-1);
    glVertex2f(0,-.8);
    glVertex2f(-.3, -1);

    
    
    glEnd();
    glPopMatrix();
}

void Ship::Turn(double a)
{
    angle += a;
}

void Ship::Command(Commands cmd, bool state)
{
    activeCmd[cmd] = state;
}

Ship::Ship(vec position, double a):
    pos(position), angle(a)
{
    for (int i = 0; i < CMD_MAX; ++i){
        activeCmd[i] = false;
    }
}

