/*
 * cube_ex2_perspective.c
 * Exercício 1.2 - Substitui glFrustum() por gluPerspective(60.0, 1.0, 1.5, 20.0)
 * 
 * gluPerspective(fovy, aspect, zNear, zFar)
 * - fovy: ângulo de abertura vertical em graus (60.0)
 * - aspect: razão largura/altura (1.0). F/f e A/a mudam os dois na hora.
 * - zNear: plano de corte próximo (1.5)
 * - zFar: plano de corte distante (20.0)
 * 
 * fovy comeca em 60 e aspect em 1, os valores do enunciado.
 * F/f muda fovy. A/a muda aspect.
 */
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

static GLdouble fovy = 60.0;
static GLdouble aspect = 1.0;
static int winW = 500, winH = 500;

static void setProjection(void)
{
   glViewport(0, 0, (GLsizei) winW, (GLsizei) winH);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(fovy, aspect, 1.5, 20.0);
   glMatrixMode(GL_MODELVIEW);
}

static void showParams(void)
{
   char title[96];
   sprintf(title, "Exercicio 1.2 - fovy %.0f  aspect %.1f", fovy, aspect);
   glutSetWindowTitle(title);
   printf("gluPerspective(%.0f, %.1f, 1.5, 20.0)\n", fovy, aspect);
   fflush(stdout);
}

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
   winW = w;
   winH = h;
   setProjection();
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 'f':
         if (fovy < 120.0) fovy += 10.0;
         break;
      case 'F':
         if (fovy > 20.0) fovy -= 10.0;
         break;
      case 'a':
         if (aspect < 3.0) aspect += 0.5;
         break;
      case 'A':
         if (aspect > 0.5) aspect -= 0.5;
         break;
      case 27:
         exit(0);
         break;
      default:
         return;
   }
   setProjection();
   showParams();
   glutPostRedisplay();
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
   showParams();
   printf("F/f muda fovy. A/a muda aspect. ESC sai.\n");
   glutMainLoop();
   return 0;
}
