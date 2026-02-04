/*
 * cube_ex1_topdown.c
 * Exercício 1.1 - Câmera vê o cubo verticalmente de cima para baixo
 * 
 * gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ)
 * - eye: posição da câmera
 * - center: ponto para onde a câmera olha
 * - up: vetor que define "para cima" da câmera
 * 
 * Para ver de cima para baixo:
 * - Câmera em (0, 5, 0) - acima do cubo
 * - Olhando para (0, 0, 0) - origem onde está o cubo
 * - Up vector (0, 0, -1) - define a orientação da câmera
 */
#include <GL/glut.h>
#include <stdlib.h>

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT);
   glColor3f (1.0, 1.0, 1.0);
   glLoadIdentity ();             /* clear the matrix */
   
   /* Câmera de cima para baixo:
    * eye    = (0, 5, 0)  - câmera 5 unidades acima na direção Y
    * center = (0, 0, 0)  - olhando para a origem
    * up     = (0, 0, -1) - Z negativo é "para cima" na tela
    * 
    * Nota: up não pode ser paralelo à direção de visão!
    * Como olhamos para baixo (-Y), up não pode ser (0,1,0) nem (0,-1,0)
    */
   gluLookAt (0.0, 5.0, 0.0,   /* posição da câmera (eye) */
              0.0, 0.0, 0.0,   /* ponto de interesse (center) */
              0.0, 0.0, -1.0); /* vetor up */
   
   glScalef (1.0, 2.0, 1.0);      /* modeling transformation */ 
   glutWireCube (1.0);
   glFlush ();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
   glMatrixMode (GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Exercicio 1.1 - Camera de cima para baixo");
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
