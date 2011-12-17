
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include "ship.h"
#include "common.h"

using namespace std;

Ship ship(vec(0,0,0),1);

void Render(){
    glClearColor(.1,.1,.1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    ship.Render();
    glutSwapBuffers();
}

void InitKeys(){
    
}

void _timer(int arg){
    ship.Update(1./40);
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

int main (int argc, char* argv[])
{
	cout << "Hej" << endl;
	
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_DOUBLE);
	
	glutCreateWindow("hej");

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
                          


        glutTimerFunc(100,_timer, 0);

	glutMainLoop();
	
	return 0;
}
