
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <list>
#include "ship.h"
#include "common.h"
#include "physics.h"

using namespace std;

Ship ship(vec(0,0,0),1);

Physics *physics;

list<Unit *> objects;

void Render(){
    glClearColor(.1,.1,.1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glPushMatrix();
    
    glScalef(.1, .1, .1);
    
    for(auto a=objects.begin(); a!= objects.end(); ++a){
        (*a)->Render();
    }
    
    glPopMatrix();
    
    glutSwapBuffers();
}

void _timer(int arg){
    ship.Update(1./40);
    physics->Step(1./40);
    Render();
    glutTimerFunc(1000/40, _timer, 0);
}

void _knapp(int knapp, bool state){
    
    
    for (int i; i < CMD_MAX; ++i){
        if(MappingKeys[i] == knapp){
            ship.Command((Commands)i, state);
            return;
        }
    }
    
}

void InitKeys(){
    
    glutIgnoreKeyRepeat(true);
                           
           glutKeyboardFunc(
                       [](unsigned char key, int x, int y) {_knapp(key, true);}
                       );
   glutKeyboardUpFunc( [] (unsigned char key, int x, int y){_knapp(key, false);}
                                  );
           glutSpecialFunc(
                       [](int key, int x, int y) {_knapp(-key, true);}
                       );
   glutSpecialUpFunc( [] (int key, int x, int y){_knapp(-key, false);}
                                  );
}
   
void EnableLighting(){
    
    GLfloat light_diffuse[] = {1.0, 0.0, 0.0, 1.0};  /* Red diffuse light. */
    GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};  /* Infinite light location. */
    
    glEnable(GL_LIGHT0);
    
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    glEnable(GL_LIGHTING);
}

void CreateRagDoll(){
    const int partCount = 6;
    Box *part[partCount];

#define _BODY(index, dim, m, size) part[index] = physics->CreateRigidBox(btVector3 dim, m, btVector3 size);
#define _CONNECT(indexa, indexb, posa, posb) physics->PointConstraint(part[indexa], part[indexb], btVector3 posa, btVector3 posb, true);
    
    _BODY(0, (0,0,0), 1, (.2, .5, .05));
    _BODY(1, (0, -.55, 0), .3, (.5, .1, .1));
    _BODY(2, (.4, -1.05, 0), .5, (.2, .5, .1));
    _BODY(3, (-.4, -1.05, 0), .5, (.2, .5, .1));
    _BODY(4, (.4, -2.05, 0), .5, (.2, .5, .1));
    _BODY(5, (-.4, -2.05, 0), .5, (.2, .5, .1));
    
    
    _CONNECT(0, 1, (0,-.5, 0), (0,.05, 0));
    _CONNECT(1, 2, (.4, 0, 0), (0,.6, 0));
    _CONNECT(1, 3, (-.4, 0, 0), (0,.6, 0));
    _CONNECT(2, 4, (0, -.5, 0), (0,.5, 0));
    _CONNECT(3, 5, (0, -.5, 0), (0,.5, 0));
    
    for (int i = 0; i < partCount; ++i){
        objects.push_back(part[i]);
    }
    
#undef _BODY
    
}


int main (int argc, char* argv[])
{
	cout << "Hej" << endl;
	
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_DOUBLE);
	
        glutInitWindowSize(400,400);
        
	glutCreateWindow("hej");
        
        EnableLighting();
        
        glDepthFunc(GL_LESS);
        
        InitKeys();
        
        physics = new Physics();
        
        Box *a, *b;
        
        //objects.push_back(&ship);
        objects.push_back(physics->CreateRigidBox(btVector3(0,-56,0), 0, btVector3(50,50,50)));
        //objects.push_back(a = physics->CreateRigidBox(btVector3(-2,0,0),1));
        //objects.push_back(b = physics->CreateRigidBox(btVector3(0,2,0),1, btVector3(5,.1,1)));
        //physics->PointConstraint(a,b, btVector3(1,1,1), btVector3(-1,0,0));
        
        //objects.push_back(a = physics->CreateRigidBox(btVector3(1,3,0),.3,btVector3(.5,.5,.5)));
        //objects.push_back(physics->CreateRigidBox(btVector3(2,-5,0),0,btVector3(.5,.5,.5)));
        
        CreateRagDoll();

        glutTimerFunc(100,_timer, 0);

	glutMainLoop();
	
        delete physics;
        
	return 0;
}
