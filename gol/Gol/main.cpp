#include <windows.h>
#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>

// Posição e raio do Círculo (movido pelas setas)
GLfloat cx = 100.0f;
GLfloat cy = 200.0f;
GLfloat circleRadius = 25.0f;
GLfloat circleSpeed = 10.0f;

// Posição e tamanho do Quadrado que representa o Gol
GLfloat goalX = 450.0f;
GLfloat goalY = 200.0f;
GLsizei goalSize = 80;

GLfloat windowWidth;
GLfloat windowHeight;

// Variável para controlar para não floodar a mensagem no console a cada quadro
int golMarcado = 0;

// Função para desenhar um círculo preenchido
void DesenhaCirculo(GLfloat x, GLfloat y, GLfloat raio, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Centro do círculo
    for (int i = 0; i <= num_segments; i++) {
        GLfloat theta = 2.0f * 3.1415926f * (GLfloat)i / (GLfloat)num_segments;
        GLfloat px = raio * cosf(theta);
        GLfloat py = raio * sinf(theta);
        glVertex2f(x + px, y + py);
    }
    glEnd();
}

// Função de Detecção de Colisão (Círculo vs Quadrado do Gol)
void VerificaGol() {
    GLfloat goalLeft = goalX;
    GLfloat goalRight = goalX + goalSize;
    GLfloat goalBottom = goalY;
    GLfloat goalTop = goalY + goalSize;

    GLfloat circLeft = cx - circleRadius;
    GLfloat circRight = cx + circleRadius;
    GLfloat circBottom = cy - circleRadius;
    GLfloat circTop = cy + circleRadius;

    // Verifica se o círculo encostou/entrou na área do quadrado do gol
    if (circRight >= goalLeft && circLeft <= goalRight && circTop >= goalBottom && circBottom <= goalTop) {
        if (!golMarcado) {
            printf("\n GOOOOOOL! O circulo acertou o gol! \n");
            golMarcado = 1; // Marca que o gol foi feito nesta jogada
        }
    } else {
        golMarcado = 0; // Reseta quando o círculo sai de dentro do gol
    }
}

void Desenha(void)
{
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();

     glClear(GL_COLOR_BUFFER_BIT);

     // Desenha o Quadrado do Gol (Verde)
     glColor3f(0.0f, 1.0f, 0.0f);
     glBegin(GL_QUADS);
            glVertex2i(goalX, goalY + goalSize);
            glVertex2i(goalX, goalY);
            glVertex2i(goalX + goalSize, goalY);
            glVertex2i(goalX + goalSize, goalY + goalSize);
     glEnd();

     // Desenha o Círculo controlado pelas setas (Amarelo)
     glColor3f(1.0f, 1.0f, 0.0f);
     DesenhaCirculo(cx, cy, circleRadius, 30);

     // Verifica se ocorreu o gol
     VerificaGol();

     glutSwapBuffers();
}

// Função para capturar as setas direcionais do teclado
void TeclasEspeciais(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            cy += circleSpeed;
            if (cy > windowHeight - circleRadius) cy = windowHeight - circleRadius;
            break;
        case GLUT_KEY_DOWN:
            cy -= circleSpeed;
            if (cy < circleRadius) cy = circleRadius;
            break;
        case GLUT_KEY_LEFT:
            cx -= circleSpeed;
            if (cx < circleRadius) cx = circleRadius;
            break;
        case GLUT_KEY_RIGHT:
            cx += circleSpeed;
            if (cx > windowWidth - circleRadius) cx = windowWidth - circleRadius;
            break;
    }
    glutPostRedisplay();
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
     glViewport(0, 0, w, h);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
     windowWidth = w;
     windowHeight = h;
     gluOrtho2D(0.0f, windowWidth, 0.0f, windowHeight);
}

int main(int argc, char** argv)
{
     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
     glutInitWindowSize(640, 480);
     glutInitWindowPosition(10, 10);
     glutCreateWindow("Jogo do Gol - FreeGLUT");
     glutDisplayFunc(Desenha);
     glutReshapeFunc(AlteraTamanhoJanela);
     glutSpecialFunc(TeclasEspeciais);
     glutMainLoop();
}
