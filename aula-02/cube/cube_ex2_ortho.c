/*
 * cube_ex2_ortho.c
 * Exercício 1.2 - Substitui gluPerspective() por glOrtho()
 * 
 * glOrtho(left, right, bottom, top, zNear, zFar)
 * Usa os mesmos parâmetros de glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0)
 * 
 * Diferença principal:
 * - glFrustum/gluPerspective: projeção perspectiva (objetos distantes parecem menores)
 * - glOrtho: projeção ortográfica (sem perspectiva, objetos mantêm tamanho)
 * 
 * Projeção ortográfica é útil para:
 * - CAD/desenho técnico
 * - Jogos 2D
 * - Visualização científica
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
   
   /* Substituição: glOrtho com mesmos parâmetros de glFrustum */
   /* glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0); */
   glOrtho(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
   
   /* Note que na projeção ortográfica:
    * - Não há efeito de perspectiva
    * - Linhas paralelas permanecem paralelas
    * - Objetos não diminuem com a distância
    * - O cubo aparece "achatado" pois não há profundidade visual
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
   glutCreateWindow ("Exercicio 1.2 - glOrtho (projecao ortografica)");
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
