/*
 * cube_ex1_matrix.c
 * Exercício 1.1 - Mostra a matriz de modelview após chamar gluLookAt()
 * 
 * A matriz impressa no console demonstra que gluLookAt(0,0,5, 0,0,0, 0,1,0)
 * é equivalente a uma translação de (0, 0, -5).
 */
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

void printModelViewMatrix(void)
{
   GLfloat matrix[16];
   int i, j;
   
   glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
   
   printf("\n=== Matriz ModelView apos gluLookAt() ===\n");
   printf("(OpenGL armazena em column-major order)\n\n");
   
   /* Imprime a matriz em formato legível (row-major para visualização) */
   for (i = 0; i < 4; i++) {
      for (j = 0; j < 4; j++) {
         printf("%8.4f ", matrix[j * 4 + i]);
      }
      printf("\n");
   }
   printf("\n");
   printf("Observe: a ultima coluna contem a translacao (0, 0, -5, 1)\n");
   printf("Isso comprova que gluLookAt(0,0,5,...) = glTranslatef(0,0,-5)\n");
   printf("=========================================\n\n");
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT);
   glColor3f (1.0, 1.0, 1.0);
   glLoadIdentity ();             /* clear the matrix */
           /* viewing transformation  */
   gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   
   /* Imprime a matriz após gluLookAt (apenas uma vez) */
   static int printed = 0;
   if (!printed) {
      printModelViewMatrix();
      printed = 1;
   }
   
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
   glutCreateWindow ("Exercicio 1.1 - Mostra Matriz ModelView");
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
