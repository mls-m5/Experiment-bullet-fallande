#include "box.h"
#include <GL/glut.h>

void Box::Render()
{
    glPushMatrix();
#if(BT_USE_DOUBLE_PRECISION)
    double m[15];
    body->getWorldTransform().getOpenGLMatrix(m);
    glMultMatrixd(m);
#else
    float m[15];
    body->getWorldTransform().getOpenGLMatrix(m);
    glMatrixMode(GL_MODELVIEW);
    glMultMatrixf(m);
    
#endif
    glScaled(dimensions.x(), dimensions.y(), dimensions.z());
    
    glutSolidCube(2.);
    glPopMatrix();
}

