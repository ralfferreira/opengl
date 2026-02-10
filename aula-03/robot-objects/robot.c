/*
 * Exercício 3 - Braço Robótico pegando objetos
 * 
 * Controles:
 *   Q/A - Base (rotação Y)
 *   W/S - Ombro (shoulder)
 *   E/D - Cotovelo (elbow)
 *   R/F - Pulso (wrist)
 *   T/G - Garra (abrir/fechar)
 *   P   - Pegar / Soltar objeto
 *   ESC - sair
 */
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define GRAB_DISTANCE 2.5f

static int baseRotation = 0;
static int shoulderAngle = -45;
static int elbowAngle = 45;
static int wristAngle = 0;
static int fingerAngle = 0;

/* Estado do objeto: 0 = na mesa, 1 = agarrado pela garra, 2 = dentro da caixa */
static int objectState = 0;

/* Posição do objeto quando está na mesa */
static float objX = 3.0f, objY = 0.3f, objZ = 0.0f;

/* Posição da caixa */
static float boxX = -3.0f, boxY = 0.0f, boxZ = 0.0f;

/* Calcula a posição mundial da garra via cinemática direta */
void getGripperPos(float *gx, float *gy, float *gz)
{
   float d2r = (float)(M_PI / 180.0);
   float bRad = baseRotation * d2r;
   float sRad = shoulderAngle * d2r;
   float eRad = elbowAngle * d2r;
   float totalAng = sRad + eRad;
   
   /* No frame da base (antes da rotação Y da base): */
   /* Ombro: translate (0,0.6,0), rotate Z, translate (0,2.0,0) total até cotovelo */
   float lx = -2.0f * sinf(sRad);
   float ly = 0.6f + 2.0f * cosf(sRad);
   
   /* Cotovelo: rotate Z acumulado, translate (0,1.5,0) até pulso */
   lx += -1.5f * sinf(totalAng);
   ly +=  1.5f * cosf(totalAng);
   
   /* Pulso + garra: translate (0, 0.45, 0) na mesma direção */
   lx += -0.45f * sinf(totalAng);
   ly +=  0.45f * cosf(totalAng);
   
   /* Aplica rotação da base (Y) para coordenadas do mundo */
   *gx =  lx * cosf(bRad);
   *gy =  ly;
   *gz = -lx * sinf(bRad);
}

float distancia(float x1, float y1, float z1, float x2, float y2, float z2)
{
   float dx = x1 - x2, dy = y1 - y2, dz = z1 - z2;
   return sqrtf(dx*dx + dy*dy + dz*dz);
}

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

void drawObject(void)
{
   glColor3f(1.0, 0.0, 0.0);
   glutSolidSphere(0.3, 16, 16);
   glColor3f(1.0, 1.0, 1.0);
   glutWireSphere(0.3, 8, 8);
}

void drawBox(void)
{
   glPushMatrix();
   glTranslatef(boxX, boxY, boxZ);
   
   /* Fundo */
   glPushMatrix();
   glTranslatef(0.0, 0.05, 0.0);
   drawPart(2.0, 0.1, 2.0, 0.6, 0.3, 0.1);
   glPopMatrix();
   
   /* Parede frente */
   glPushMatrix();
   glTranslatef(0.0, 0.55, 1.0);
   drawPart(2.0, 1.0, 0.1, 0.6, 0.3, 0.1);
   glPopMatrix();
   
   /* Parede trás */
   glPushMatrix();
   glTranslatef(0.0, 0.55, -1.0);
   drawPart(2.0, 1.0, 0.1, 0.6, 0.3, 0.1);
   glPopMatrix();
   
   /* Parede esquerda */
   glPushMatrix();
   glTranslatef(-1.0, 0.55, 0.0);
   drawPart(0.1, 1.0, 2.0, 0.6, 0.3, 0.1);
   glPopMatrix();
   
   /* Parede direita */
   glPushMatrix();
   glTranslatef(1.0, 0.55, 0.0);
   drawPart(0.1, 1.0, 2.0, 0.6, 0.3, 0.1);
   glPopMatrix();
   
   glPopMatrix();
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
   /* Chão */
   glPushMatrix();
   glTranslatef(0.0, -0.05, 0.0);
   drawPart(14.0, 0.1, 14.0, 0.15, 0.15, 0.15);
   glPopMatrix();
   
   /* Caixa (coordenadas do mundo) */
   drawBox();
   
   /* Objeto na mesa (estado 0) */
   if (objectState == 0) {
      glPushMatrix();
      glTranslatef(objX, objY, objZ);
      drawObject();
      glPopMatrix();
   }
   
   /* Objeto dentro da caixa (estado 2) */
   if (objectState == 2) {
      glPushMatrix();
      glTranslatef(boxX, 0.4f, boxZ);
      drawObject();
      glPopMatrix();
   }
   
   /* BRAÇO ROBÓTICO */
   glPushMatrix();
   
   /* BASE - rotação em Y */
   glRotatef((GLfloat)baseRotation, 0.0, 1.0, 0.0);
   drawPart(2.0, 0.4, 2.0, 0.5, 0.5, 0.5);
   
   /* SHOULDER (ombro) */
   glTranslatef(0.0, 0.6, 0.0);
   glRotatef((GLfloat)shoulderAngle, 0.0, 0.0, 1.0);
   glTranslatef(0.0, 1.0, 0.0);
   drawPart(0.5, 2.0, 0.5, 0.0, 0.5, 0.8);
   
   /* ELBOW (cotovelo) */
   glTranslatef(0.0, 1.0, 0.0);
   glRotatef((GLfloat)elbowAngle, 0.0, 0.0, 1.0);
   glTranslatef(0.0, 0.75, 0.0);
   drawPart(0.4, 1.5, 0.4, 0.8, 0.5, 0.0);
   
   /* WRIST (pulso) */
   glTranslatef(0.0, 0.75, 0.0);
   glRotatef((GLfloat)wristAngle, 0.0, 1.0, 0.0);
   glTranslatef(0.0, 0.25, 0.0);
   drawPart(0.6, 0.3, 0.6, 0.6, 0.0, 0.6);
   
   /* Área da garra */
   glTranslatef(0.0, 0.2, 0.0);
   
   /* Objeto agarrado (estado 1) - desenhado no sistema de coordenadas da garra */
   if (objectState == 1) {
      glPushMatrix();
      glTranslatef(0.0, 0.3, 0.0);
      drawObject();
      glPopMatrix();
   }
   
   /* END EFFECTOR - Dedo 1 */
   glPushMatrix();
      glTranslatef(0.0, 0.0, 0.2);
      glRotatef((GLfloat)fingerAngle, 1.0, 0.0, 0.0);
      glTranslatef(0.0, 0.4, 0.0);
      drawPart(0.15, 0.8, 0.15, 0.0, 0.8, 0.0);
   glPopMatrix();
   
   /* END EFFECTOR - Dedo 2 */
   glPushMatrix();
      glTranslatef(0.0, 0.0, -0.2);
      glRotatef((GLfloat)-fingerAngle, 1.0, 0.0, 0.0);
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
   gluPerspective(60.0, (GLfloat)w/(GLfloat)h, 1.0, 30.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(7.0, 6.0, 10.0, 0.0, 2.0, 0.0, 0.0, 1.0, 0.0);
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
      case 'r': wristAngle = (wristAngle + 5) % 360; break;
      case 'f': wristAngle = (wristAngle - 5) % 360; break;
      case 't': if (fingerAngle < 45) fingerAngle += 5; break;
      case 'g': if (fingerAngle > -30) fingerAngle -= 5; break;
      case 'p':
      case 'P':
         {
            float gx, gy, gz;
            getGripperPos(&gx, &gy, &gz);
            if (objectState == 0) {
               /* Pegar da mesa: só se a garra estiver perto do objeto */
               float d = distancia(gx, gy, gz, objX, objY, objZ);
               if (d < GRAB_DISTANCE) {
                  objectState = 1;
                  printf("Objeto agarrado! (dist=%.2f)\n", d);
               } else {
                  printf("Garra longe do objeto (dist=%.2f)\n", d);
               }
            } else if (objectState == 1) {
               /* Soltar: se perto da caixa -> dentro da caixa, senão -> de volta à mesa */
               float dBox = distancia(gx, gy, gz, boxX, 0.4f, boxZ);
               float dObj = distancia(gx, gy, gz, objX, objY, objZ);
               if (dBox < GRAB_DISTANCE) {
                  objectState = 2;
                  printf("Objeto solto na caixa! (dist=%.2f)\n", dBox);
               } else {
                  objectState = 0;
                  printf("Objeto solto na mesa! (dist=%.2f)\n", dObj);
               }
            } else if (objectState == 2) {
               /* Pegar da caixa: só se a garra estiver perto da caixa */
               float d = distancia(gx, gy, gz, boxX, 0.4f, boxZ);
               if (d < GRAB_DISTANCE) {
                  objectState = 1;
                  printf("Objeto retirado da caixa! (dist=%.2f)\n", d);
               } else {
                  printf("Garra longe da caixa (dist=%.2f)\n", d);
               }
            }
         }
         break;
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
   glutCreateWindow("Exercicio 3 - Pegando Objetos");
   init();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   printf("Controles:\n");
   printf("  Q/A - Base\n  W/S - Ombro\n  E/D - Cotovelo\n");
   printf("  R/F - Pulso\n  T/G - Garra\n");
   printf("  P   - Pegar/Soltar objeto\n  ESC - Sair\n");
   glutMainLoop();
   return 0;
}
