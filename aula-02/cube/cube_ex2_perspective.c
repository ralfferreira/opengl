/*
 * cube_ex2_perspective.c
 * Exercício 1.2 - Substitui glFrustum() por gluPerspective(60.0, 1.0, 1.5, 20.0)
 * 
 * gluPerspective(fovy, aspect, zNear, zFar)
 * - fovy: ângulo de abertura vertical em graus (60.0)
 * - aspect: razão largura/altura da janela (1.0)
 * - zNear: plano de corte próximo (1.5)
 * - zFar: plano de corte distante (20.0)
 * 
 * Experimente:
 * - fovy maior = visão mais ampla (fish-eye)
 * - fovy menor = visão mais estreita (zoom)
 * - aspect diferente de 1.0 = distorção horizontal/vertical
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
           /* viewing transformation  */
   gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   glScalef (1.0, 2.0, 1.0);      /* modeling transformation */ 
   glutWireCube (1.0);
   glFlush ();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   
   /* Substituição: gluPerspective em vez de glFrustum */
   /* glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0); */
   gluPerspective(60.0, 1.0, 1.5, 20.0);
   
   /* Experimente diferentes valores:
    * gluPerspective(30.0, 1.0, 1.5, 20.0);  - mais zoom
    * gluPerspective(90.0, 1.0, 1.5, 20.0);  - mais amplo
    * gluPerspective(60.0, 2.0, 1.5, 20.0);  - esticado horizontalmente
    * gluPerspective(60.0, 0.5, 1.5, 20.0);  - esticado verticalmente
    */
   
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
   glutCreateWindow ("Exercicio 1.2 - gluPerspective");
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
