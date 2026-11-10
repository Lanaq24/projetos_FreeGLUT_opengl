#include<GL/freeglut.h>
#include<time.h>
#include<cstdio>
GLfloat x = 1.0f;          // escala horizontal (F2)
GLfloat y = 1.0f;          // escala vertical (F2)
GLfloat poshorizontal = 1.0f;   // translacao no eixo X (F4)
GLfloat posvertical = 1.0f;  // translacao no eixo Y (F4)

// F3: valor minimo que a escala pode assumir, para o nome nunca sumir da tela
const GLfloat ESCALA_MINIMA = 0.2f;
const GLfloat ESCALA_PASSO  = 0.1f;   // quanto cada tecla +/- muda a escala
const GLfloat TRANSLACAO_PASSO = 0.3f; // quanto cada tecla a/d/w/s desloca o nome

// rotacao
GLfloat anguloX = 0.0f;
GLfloat anguloY = 0.0f;
GLfloat anguloZ = 0.0f;
const GLfloat ROTACAO_PASSO = 5.0f;

// PARTE 3: botoes
// eixoSelecionado indica qual angulo (X, Y ou Z) as teclas 'q'/'e' vao alterar
// 0 = X, 1 = Y, 2 = Z
int eixoSelecionado = 2; // comeca no Z

//tamanho ATUAL da janela (comeca com 800x600, mas e atualizado pela funcao reshape() quando a janela muda de tamanho)
int LARGURA_JANELA = 800;
int ALTURA_JANELA  = 600;

struct Botao {
    float xMin, yMin, xMax, yMax;
    char rotulo;
};

Botao botoes[3] = {
    { -4.5f, 15.0f, -1.5f, 18.0f, 'x' },
    { -0.5f, 15.0f,  2.5f, 18.0f, 'y' },
    {  3.5f, 15.0f,  6.5f, 18.0f, 'z' }
};

float r, g, b, mx, my;
bool check = true;

void desenhaBotoes(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-5, 20, -5, 20);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    for (int i = 0; i < 3; i++)
    {
        Botao &bt = botoes[i];
        bool selecionado = (i == eixoSelecionado);

        // muda a cor de fundo do botao quando ele esta selecionado
        if (selecionado)
            glColor3f(0.2f, 0.8f, 0.2f); // verde
        else
            glColor3f(0.75f, 0.75f, 0.75f); // cinza

        glBegin(GL_QUADS);
            glVertex2f(bt.xMin, bt.yMin);
            glVertex2f(bt.xMax, bt.yMin);
            glVertex2f(bt.xMax, bt.yMax);
            glVertex2f(bt.xMin, bt.yMax);
        glEnd();

        // borda preta do botao
        glColor3f(0, 0, 0);
        glBegin(GL_LINE_LOOP);
            glVertex2f(bt.xMin, bt.yMin);
            glVertex2f(bt.xMax, bt.yMin);
            glVertex2f(bt.xMax, bt.yMax);
            glVertex2f(bt.xMin, bt.yMax);
        glEnd();

        // ooloca s letsras no botao
        glRasterPos2f((bt.xMin + bt.xMax) / 2 - 0.2f, (bt.yMin + bt.yMax) / 2 - 0.2f);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, bt.rotulo);
    }
}

void desenha(void) {
    glClear(GL_COLOR_BUFFER_BIT); // limpa o buffer de cor da tela para que desenhos antigos nao fiquem "grudados" na tela

    // se check estiver true, tinge o fundo com a cor aleatória(clique do mouse)
    if (check) {
        glClearColor(r, g, b, 0);
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-5, 20, -5, 20); // define o sistema de coordenadas que vão ser usadas para desenhar

    glScalef(x, y, 0);
    glTranslatef(poshorizontal, posvertical , 0);

    // F5: rotacao em torno do eixo escolhido pelo usuario
    glRotatef(anguloX, 1, 0, 0); // rotacao em torno do eixo X
    glRotatef(anguloY, 0, 1, 0); // rotacao em torno do eixo Y
    glRotatef(anguloZ, 0, 0, 1); // rotacao em torno do eixo Z

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
        glVertex2f(2,6);
        glVertex2f(2,2);

        glVertex2f(2,2);
        glVertex2f(4,2);

        glVertex2f(5,2);
        glVertex2f(6,6);

        glVertex2f(6,6);
        glVertex2f(7, 2);

        glVertex2f(5.3,3);
        glVertex2f(6.7, 3);

        glVertex2f(8,2);
        glVertex2f(8,6);

        glVertex2f(8,6);
        glVertex2f(9.5,2);

        glVertex2f(9.5, 2);
        glVertex2f(9.5, 6);

        glVertex2f(10.5, 2);
        glVertex2f(11.5, 6);

        glVertex2f(11.5, 6);
        glVertex2f(12.5, 2);

        glVertex2f(10.9, 3);
        glVertex2f(12.3, 3);
    glEnd();
    desenhaBotoes();

    glFlush();
}

void listeningKey(unsigned char tecla, GLint xt, GLint yt)
{
    switch(tecla){
        //F2: escalamento
        case '+':
            x = x + ESCALA_PASSO;
            y = y + ESCALA_PASSO;
            break;
        case '-':
            x = x - ESCALA_PASSO;
            y = y - ESCALA_PASSO;
            // F3: nao deixa a escala chegar a zero ou negativa para o nome nao sumie
            if (x < ESCALA_MINIMA) x = ESCALA_MINIMA;
            if (y < ESCALA_MINIMA) y = ESCALA_MINIMA;
            break;

        // F4: translacao
        case 'a': // esquerda
            poshorizontal = poshorizontal - TRANSLACAO_PASSO;
            break;
        case 'd': // direita
            poshorizontal = poshorizontal + TRANSLACAO_PASSO;
            break;
        case 'w': // cima
            posvertical = posvertical + TRANSLACAO_PASSO;
            break;
        case 's': // baixo
            posvertical = posvertical - TRANSLACAO_PASSO;
            break;

        //  F5: rotacao
        case 'q': // anti-horario
            if (eixoSelecionado == 0) anguloX += ROTACAO_PASSO;
            if (eixoSelecionado == 1) anguloY += ROTACAO_PASSO;
            if (eixoSelecionado == 2) anguloZ += ROTACAO_PASSO;
            break;
        case 'e': // horario
            if (eixoSelecionado == 0) anguloX -= ROTACAO_PASSO;
            if (eixoSelecionado == 1) anguloY -= ROTACAO_PASSO;
            if (eixoSelecionado == 2) anguloZ -= ROTACAO_PASSO;
            break;
    }
    desenha();
}


void mouse(int button, int state, int mousex, int mousey)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {

        float ogX = -5.0f + (mousex / (float)LARGURA_JANELA) * 25.0f;
        float ogY = -5.0f + ((ALTURA_JANELA - mousey) / (float)ALTURA_JANELA) * 25.0f;

        printf("Clique em pixel(%d,%d) -> coordenada(%.2f, %.2f)\n", mousex, mousey, ogX, ogY);

        //verifica se o clique foi em cima de algum botao
        bool clicouBotao = false;
        for (int i = 0; i < 3; i++)
        {
            Botao &bt = botoes[i];
            if (ogX >= bt.xMin && ogX <= bt.xMax && ogY >= bt.yMin && ogY <= bt.yMax)
            {
                eixoSelecionado = i; //troca o eixo ativo -> o botao correspondente fica verde
                clicouBotao = true;
                break;
            }
        }

        //se nao clicou em nenhum botao -cor de fundo aleatoria
        if (!clicouBotao)
        {
            check = true;
            mx = mousex;
            my = 480 - mousey;
            r = (rand() % 10) / 10.0;
            g = (rand() % 10) / 10.0;
            b = (rand() % 10) / 10.0;
        }
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        glClearColor(1, 1, 1, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        check = false;
    }
    glutPostRedisplay();
}

//f1: mantem o nome visivel ao redimensionar a janela
void reshape(int novaLargura, int novaAltura)
{
    if (novaAltura == 0) novaAltura = 1;

    LARGURA_JANELA = novaLargura;
    ALTURA_JANELA  = novaAltura;

    // reajusta a area de desenho (em pixels) para o novo tamanho da janela
    glViewport(0, 0, novaLargura, novaAltura);

    //recalcula a projecao para o novo tamanho
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-5, 20, -5, 20);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(LARGURA_JANELA, ALTURA_JANELA);// define o tamanho da janela (LARGURA, ALTURA)
    glutInitWindowPosition(300, 100); //define onde a janela vai aparecer na tela (ESQUERDA, TOPO)
    glutCreateWindow("Ola Glut"); //cria a janela

    glutKeyboardFunc(listeningKey);
    glutMouseFunc(mouse); //registrado o callback do mouse
    glutDisplayFunc(desenha); //registra a função desenha como callback de renderização
    glutReshapeFunc(reshape); //mantem o nome exibido ao redimensionar a janela
    glClearColor(0, 0, 0.1, 1); //cor usada para limpar a tela

    glutMainLoop();
    return 0;
}
