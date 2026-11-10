#include <windows.h>
#include <GL/freeglut.h>
#include <stdio.h>

GLfloat x1 = 100.0f;
GLfloat y1 = 150.0f;
GLsizei rsize = 50;

GLint x2 = 100;
GLint y2 = 20;
// Vetor de translacao
GLfloat xstep = 3.0f;
GLfloat ystep = 3.0f; //definem o fator de translçao

GLint x2step = 3.0;
GLint y2step = 3.0;


GLfloat windowWidth;
GLfloat windowHeight;

void Desenha(void)
{
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();

     glClear(GL_COLOR_BUFFER_BIT);
     glColor3f(1.0f, 0.0f, 0.0f);
     glBegin(GL_QUADS);
               glVertex2i(x1,y1+rsize);
               glVertex2i(x1,y1);
               glColor3f(0.0f, 0.0f, 1.0f);
               glVertex2i(x1+rsize,y1);
               glVertex2i(x1+rsize,y1+rsize);//soma na coluna e na linha
        glEnd();

     glBegin(GL_TRIANGLES);
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex2f(x2,y2);
            glVertex2f(x2,y2+rsize);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex2f(x2+rsize,y2+rsize);
        glEnd();


     glutSwapBuffers(); //usar qunado for usar glut double
}

void Timer(int value) //pode ter qualuer nome mas precisa ser void e receber um inteiro como parametro
{
    // Muda a direção quando chega na borda esquerda ou direita
    //tamanho limite do quadrado
      if(x1 > windowWidth-rsize || x1 < 0) //veerifica se pode continuar indo para a direita
            xstep = -xstep; //redefine o fator de deslogcamento

    // Muda a direção quando chega na borda superior ou inferior
    if(y1 > windowHeight-rsize || y1 < 0)  //verifica se vai sumir para cima
          ystep = -ystep; //rdefine o faor de deslovcamento

    // Verificação de bordas.  Se a window for menor e o quadrado sair do volume de visualização
   if(x1 > windowWidth-rsize)//quando o usuario redefinir o tamanho da janela, o objeto pode sumir, essa linha faz o objeto voltar quando o usuario soltar o mouse na mesma linha, e na coluna limite (traz o cubo para a nova dimensao da janela)
         x1 = windowWidth-rsize-1;

   if(y1 > windowHeight-rsize)
         y1 = windowHeight-rsize-1;// coloca no valor limite da coluna

    x1 += xstep; //a cada execucao as coordenadas sao recalculadas
    y1 += ystep; //para deslocar apenas na horizontal ou vertical, basta retirar o x ou o y

    //************************************
    if(x2 > windowWidth-rsize || x2 < 0) //veerifica se pode continuar indo para a direita
            x2step = -x2step; //redefine o fator de deslogcamento

    // Muda a direção quando chega na borda superior ou inferior
    if(y2 > windowHeight-rsize || y2 < 0)
          y2step = -y2step;

    // Verificação de bordas.  Se a window for menor e o quadrado sair do volume de visualização
   if(x2 > windowWidth-rsize)
         x2 = windowWidth-rsize-1;

   if(y2 > windowHeight-rsize)
         y2 = windowHeight-rsize-1;
    x2 += x2step;
    y2 += y2step;


    glutPostRedisplay(); //redesenha o objeto na nova posicao definida
    glutTimerFunc(5,Timer, 0); //chama o redesnho a cada 5 milisegundos, tempo mais alto = desenho mais lent (controla a velocidade)
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h) //define o valor da variavel global toda vez que o usuario redefinir o tamanho da janela
{
     printf("\n w: %d      h: %d ", w, h);
     glViewport(0, 0, w, h);
     glMatrixMode(GL_PROJECTION); //
     glLoadIdentity();
     glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
     windowWidth = w;
     windowHeight = h;
     gluOrtho2D(0.0f, windowWidth, 0.0f, windowHeight);
}

int main(int argc, char** argv)
{
     glutInit(&argc,argv);
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); //glut double -> gerencia dois frame buffer para nao ocorrer sujeira na tela
     glutInitWindowSize(640,480);
     glutInitWindowPosition(10,10);
     glutCreateWindow("Animacao");
     glutDisplayFunc(Desenha);
     glutReshapeFunc(AlteraTamanhoJanela);
     glutTimerFunc(5, Timer, 0);
     glutMainLoop();
}


