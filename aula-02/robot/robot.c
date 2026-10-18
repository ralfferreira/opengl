/*
 * Exercício 2.1
 * 
 * Controles:
 *   Q/A - Base (rotação Y)
 *   W/S - Ombro (shoulder)
 *   E/D - Cotovelo (elbow)
 *   R/F - Pulso, giro em torno do braço
 *   Y/H - Pulso, dobra
 *   T/G - Garra (abrir/fechar)
 *   ESC - sair
 */
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

static int baseRotation = 0;
static int shoulderAngle = -45;
static int elbowAngle = 45;
static int wristRoll = 0;
static int wristPitch = 0;
static int fingerAngle = 20;

void init(void) 
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   glEnable(GL_DEPTH_TEST);
}

void drawPart(float sx, float sy, float sz, float r, float g, float b)
{
   glPushMatrix();
   glScalef(sx, sy, sz);
   glColor3f(r, g, b);
   glutSolidCube(1.0);
   glColor3f(1.0, 1.0, 1.0);
   glutWireCube(1.0);
   glPopMatrix();
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glPushMatrix();
   
   /* BASE - rotação em Y */
   glRotatef((GLfloat)baseRotation, 0.0, 1.0, 0.0);
   drawPart(2.0, 0.4, 2.0, 0.5, 0.5, 0.5);
   
   /* SHOULDER (ombro). 0.2 é o topo da base (altura 0.4). */
   glTranslatef(0.0, 0.2, 0.0);
   glRotatef((GLfloat)shoulderAngle, 0.0, 0.0, 1.0);
   glTranslatef(0.0, 1.0, 0.0);
   drawPart(0.5, 2.0, 0.5, 0.0, 0.5, 0.8);
   
   /* ELBOW (cotovelo) */
   glTranslatef(0.0, 1.0, 0.0);
   glRotatef((GLfloat)elbowAngle, 0.0, 0.0, 1.0);
   glTranslatef(0.0, 0.75, 0.0);
   drawPart(0.4, 1.5, 0.4, 0.8, 0.5, 0.0);
   
   /* WRIST (pulso): dobra no plano do braço, depois giro em torno dele */
   glTranslatef(0.0, 0.75, 0.0);
   glRotatef((GLfloat)wristPitch, 0.0, 0.0, 1.0);
   glRotatef((GLfloat)wristRoll, 0.0, 1.0, 0.0);
   glTranslatef(0.0, 0.15, 0.0);
   drawPart(0.6, 0.3, 0.6, 0.6, 0.0, 0.6);
   
   /* Dedos no plano do desenho. Push/pop para cada um sair do mesmo pulso. */
   glTranslatef(0.0, 0.15, 0.0);
   glPushMatrix();
      glTranslatef(0.2, 0.0, 0.0);
      glRotatef((GLfloat)fingerAngle, 0.0, 0.0, 1.0);
      glTranslatef(0.0, 0.4, 0.0);
      drawPart(0.15, 0.8, 0.15, 0.0, 0.8, 0.0);
   glPopMatrix();
   
   glPushMatrix();
      glTranslatef(-0.2, 0.0, 0.0);
      glRotatef((GLfloat)-fingerAngle, 0.0, 0.0, 1.0);
      glTranslatef(0.0, 0.4, 0.0);
      drawPart(0.15, 0.8, 0.15, 0.0, 0.8, 0.0);
   glPopMatrix();
   
   glPopMatrix();
   glutSwapBuffers();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei)w, (GLsizei)h); 
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0, (GLfloat)w/(GLfloat)h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(5.0, 5.0, 8.0, 0.0, 2.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 'q': baseRotation = (baseRotation + 5) % 360; break;
      case 'a': baseRotation = (baseRotation - 5) % 360; break;
      case 'w': shoulderAngle = (shoulderAngle + 5) % 360; break;
      case 's': shoulderAngle = (shoulderAngle - 5) % 360; break;
      case 'e': elbowAngle = (elbowAngle + 5) % 360; break;
      case 'd': elbowAngle = (elbowAngle - 5) % 360; break;
      case 'r': wristRoll = (wristRoll + 5) % 360; break;
      case 'f': wristRoll = (wristRoll - 5) % 360; break;
      case 'y': wristPitch = (wristPitch + 5) % 360; break;
      case 'h': wristPitch = (wristPitch - 5) % 360; break;
      case 't': if (fingerAngle < 45) fingerAngle += 5; break;
      case 'g': if (fingerAngle > -30) fingerAngle -= 5; break;
      case 27: exit(0); break;
   }
   glutPostRedisplay();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(700, 700); 
   glutInitWindowPosition(100, 100);
   glutCreateWindow("Exercicio 2.1");
   init();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   printf("Controles:\n");
   printf("  Q/A - Base\n  W/S - Ombro\n  E/D - Cotovelo\n");
   printf("  R/F - Pulso (giro)\n  Y/H - Pulso (dobra)\n");
   printf("  T/G - Garra\n  ESC - Sair\n");
   glutMainLoop();
   return 0;
}
