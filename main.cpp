#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <GL/glut.h>
#include "CMP3_MCI.h"
#include "glm.h" ///�ϥΥ~��
CMP3_MCI mp3;
GLMmodel*model=NULL; ///���СA����GLM����Ƶ��c
GLMmodel*model2=NULL;
GLMmodel*model3=NULL;
GLMmodel*model4=NULL;
GLMmodel*model5=NULL;
GLMmodel*model6=NULL;
GLMmodel*model7=NULL;
GLMmodel*model8=NULL;
GLMmodel*model9=NULL;
GLMmodel*modela=NULL;
FILE * fout=NULL;
FILE * fin=NULL;///�ŧi�ɮ׫���
int angle[20]={};///�W�[���`
int angleID=0;///0,1,2,3
int oldX, oldY;

/// C/C++�]���禡�ϥΫe, �n���ŧior�w�q, ���ɭԷ|���Ǥ���
void display();
void motion(int x, int y);
void mouse(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);
void saveAll();
///�i�H�b�{�����̫e��, ��������禡���~��, ���ŧi�@��
///(���n�g���㪺�w�q)
int oldAngle[20]={};///�ª� ///TODO1602:�W�[���`
int newAngle[20]={};///�s��, ����|���ª�///TODO1602:�W�[���`

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 0.0f, 0.0f, -5.0f, 1.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

void timer(int t)///�۰ʼ���
{
    glutTimerFunc(10, timer, t+1);
    ///�x���s�F, �A���U�@�Ӿx��100ms����s, timer(t+1)
    if(t==0){///��1���n��Ū�s��
        if(fin==NULL) fin=fopen("motion.txt", "r");
        for(int i=0; i<20; i++){///�W�[���`
            fscanf(fin, "%d", &newAngle[i]);
        }
    }
    if(t%30==0){///�ڭ̭n��s�����ª�
        for(int i=0; i<20; i++){///�W�[���`
            oldAngle[i] = newAngle[i];///�s�����ª�
            fscanf(fin, "%d", &newAngle[i]);///�AŪ�s��
        }
    }
    float Alpha = (t%30)/30.0;///0.0~~1.0
    for(int i=0; i<20; i++){///Alpha����///�W�[���`
        angle[i] = Alpha*newAngle[i]+(1-Alpha)*oldAngle[i];
        ///printf("%d ", angle[i]);///�L�X����,��Kdebug
    }
    ///printf(" %.2f\n", Alpha);///�L�XAlpha,��Kdebug
    glutPostRedisplay();///�۰ʼ���
}

void drawBody()///���X���ܨ禡
{
    if(model==NULL){///�ڭ̻ݭn glm �������q3D�ҫ�
        model = glmReadOBJ("fox/body.obj");///Ū�J3D�ҫ�,�b����ؿ���
        glmUnitize(model);///....�ٯʤ@��...
        glmFacetNormals(model);///����(��)�k�V�q
        glmVertexNormals(model, 90);///����(���Ivn)�k�V�q
    }
    glPushMatrix();
        glScalef(0.6, 0.6, 0.6);///�Ʊ楦�p�@�I
        glRotatef(0, 0,1,0);///��Y�b��180��
        glmDraw(model, GLM_SMOOTH | GLM_MATERIAL);
    glPopMatrix();
}
void drawArm()///�t�@�Ӽҫ�
{
    if(model2==NULL){
        model2 = glmReadOBJ("fox/Ruhand.obj");
        glmUnitize(model2);///�j�ӤF,�N�Y�p -1...+1
    }
    glPushMatrix();
        glScalef(0.5, 0.5, 0.5);///�ܤp�@�I
        glRotatef(0,0,1,0);///��@�U ����
        glmDraw(model2,  GLM_SMOOTH | GLM_MATERIAL);
    glPopMatrix();
}
void drawArm2()///�t�@�Ӽҫ�
{
    if(model3==NULL){
        model3 = glmReadOBJ("fox/Rdhand.obj");
        glmUnitize(model3);///�j�ӤF,�N�Y�p -1...+1
    }
    glPushMatrix();
        glScalef(0.5, 0.5, 0.5);///�ܤp�@�I
        glRotatef(180,0,1,0);///��@�U ����
        glmDraw(model3,  GLM_SMOOTH | GLM_MATERIAL);
    glPopMatrix();
}
void drawArm3()///�t�@�Ӽҫ�
{
    if(model4==NULL){
        model4 = glmReadOBJ("fox/Luhand.obj");
        glmUnitize(model4);///�j�ӤF,�N�Y�p -1...+1
    }
    glPushMatrix();
        glScalef(0.5, 0.5, 0.5);///�ܤp�@�I
        glRotatef(0,0,1,0);///��@�U ����
        glmDraw(model4,  GLM_SMOOTH | GLM_MATERIAL);
    glPopMatrix();
}
void drawArm4()///�t�@�Ӽҫ�
{
    if(model5==NULL){
        model5 = glmReadOBJ("fox/Ldhand.obj");
        glmUnitize(model5);///�j�ӤF,�N�Y�p -1...+1
    }
    glPushMatrix();
        glScalef(0.5, 0.5, 0.5);///�ܤp�@�I
        glRotatef(180,0,1,0);///��@�U ����
        glmDraw(model5,  GLM_SMOOTH | GLM_MATERIAL);
    glPopMatrix();
}
void drawLeg()///�t�@�Ӽҫ�
{
    if(model6==NULL){
        model6 = glmReadOBJ("fox/Ruleg.obj");
        glmUnitize(model6);///�j�ӤF,�N�Y�p -1...+1
    }
    glPushMatrix();
        glScalef(0.8, 0.8, 0.8);///�ܤp�@�I
        glRotatef(0,0,1,0);///��@�U ����
        glmDraw(model6,  GLM_SMOOTH | GLM_MATERIAL);
    glPopMatrix();
}
void drawLeg2()///�t�@�Ӽҫ�
{
    if(model7==NULL){
        model7 = glmReadOBJ("fox/Rdleg.obj");
        glmUnitize(model7);///�j�ӤF,�N�Y�p -1...+1
    }
    glPushMatrix();
        glScalef(0.9, 0.9, 0.9);///�ܤp�@�I
        glRotatef(0,0,1,0);///��@�U ����
        glmDraw(model7,  GLM_SMOOTH | GLM_MATERIAL);
    glPopMatrix();
}
void drawLeg3()///�t�@�Ӽҫ�
{
    if(model8==NULL){
        model8 = glmReadOBJ("fox/Luleg.obj");
        glmUnitize(model8);///�j�ӤF,�N�Y�p -1...+1
    }
    glPushMatrix();
        glScalef(0.8, 0.8, 0.8);///�ܤp�@�I
        glRotatef(0,0,1,0);///��@�U ����
        glmDraw(model8,  GLM_SMOOTH | GLM_MATERIAL);
    glPopMatrix();
}
void drawLeg4()///�t�@�Ӽҫ�
{
    if(model9==NULL){
        model9 = glmReadOBJ("fox/Ldleg.obj");
        glmUnitize(model9);///�j�ӤF,�N�Y�p -1...+1
    }
    glPushMatrix();
        glScalef(0.9, 0.9, 0.9);///�ܤp�@�I
        glRotatef(0,0,1,0);///��@�U ����
        glmDraw(model9,  GLM_SMOOTH | GLM_MATERIAL);
    glPopMatrix();
}
void drawHead()///�t�@�Ӽҫ�
{
    if(modela==NULL){
        modela = glmReadOBJ("fox/head.obj");
        glmUnitize(modela);///�j�ӤF,�N�Y�p -1...+1
    }
    glPushMatrix();
        glScalef(0.37, 0.37, 0.37);///�ܤp�@�I
        glRotatef(0,0,1,0);///��@�U ����
        glmDraw(modela,  GLM_SMOOTH | GLM_MATERIAL);
    glPopMatrix();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0.8,0.6,1);
    glPushMatrix();
        glTranslatef( angle[11]/200.0, angle[12]/200.0, 0);
        drawBody();///���X���ܨ禡
        glPushMatrix();/// �k
            glTranslatef(0.13,0,-0.23);/// (3)���@�U�n���b����
            glRotatef(angle[0], 0,0,1);/// (1)�������
            glRotatef(angle[9], 0,1,0);
            glTranslatef(0.1, 0, 0);/// (2)������ʪ�����
            drawArm();///�k�W���u
            glPushMatrix();
                glTranslatef(0.05,0.001,0.004);
                glRotatef(angle[1], 0,0,1);
                glRotatef(angle[10], 0,1,0);
                glTranslatef(0.1, 0, 0);
                drawArm2();///�k�U���u
            glPopMatrix();
        glPopMatrix();

        glPushMatrix();/// ��
            glTranslatef(-0.13,0,-0.23);///(3)���@�U�n���b����
            glRotatef(angle[2], 0,0,1);///(1)�������
            glRotatef(angle[13], 0,1,0);
            glTranslatef(-0.1, 0, 0);///(2)������ʪ�����
            drawArm3();///���W���u
            glPushMatrix();///TODO7:
                glTranslatef(-0.05,0.001,0);
                glRotatef(angle[3], 0,0,1);
                glRotatef(angle[14], 0,1,0);
                glTranslatef(-0.1, 0, 0);
                drawArm4();///���U���u
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glPushMatrix();/// �k
            glTranslatef( angle[11]/200.0, angle[12]/200.0, 0);
            glTranslatef(0.12, -0.3, 0);/// (3)���@�U�n���b����
            glRotatef(angle[4], 0,0,1);/// (1)�������
            glRotatef(angle[15], 1,0,0);
            glTranslatef(0, -0.08, 0);/// (2)������ʪ�����
            drawLeg();///�k�W�L
            glPushMatrix();
                glTranslatef(0,-0.04,0);
                glRotatef(angle[5], 0,0,1);
                glRotatef(angle[16], 1,0,0);
                glTranslatef(0, -0.08, 0);
                drawLeg2();///�k�U�L
            glPopMatrix();
        glPopMatrix();

        glPushMatrix();/// ��
            glTranslatef( angle[11]/200.0, angle[12]/200.0, 0);
            glTranslatef(-0.12, -0.3, 0);///(3)���@�U�n���b����
            glRotatef(angle[6], 0,0,1);///(1)�������
            glRotatef(angle[17], 1,0,0);
            glTranslatef(0, -0.08, 0);///(2)������ʪ�����
            drawLeg3();///���W�L
            glPushMatrix();
                glTranslatef(0,-0.04,0);
                glRotatef(angle[7], 0,0,1);
                glRotatef(angle[18], 1,0,0);
                glTranslatef(0, -0.08, 0);
                drawLeg4();///���U�L
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
    glPushMatrix();
        glTranslatef( angle[11]/200.0, angle[12]/200.0, 0);
        glTranslatef(0,0.55,-0.23);
        glRotatef(angle[8], 0,1,0);
        glRotatef(angle[19], 1,0,0);
        glTranslatef(0, 0, 0);
        drawHead();///�Y
    glPopMatrix();
    glutSwapBuffers();
}
void mouse(int button, int state, int x, int y)
{///�ƥ�(old)mouse��m
    oldX=x; oldY=y;///�ƥ�(old)mouse��m
}
///�Ψ禡�Ӱ���, �}�G!!!
void saveAll()///(�ۤv�g���禡)�����s��
{        ///�p��!�̭��ŧi,���|���~���O�_��
    if(fout==NULL) fout=fopen("motion.txt", "w+");///�}��
    for(int i=0; i<20; i++){///�W�[���`
         printf(      "%d ", angle[i]);///�L�e��
        fprintf(fout, "%d ", angle[i]);///�g�ɮ�
    }
     printf(      "\n");///����, �e�����|��
    fprintf(fout, "\n");///����, �e�����|��
}
void motion(int x, int y)
{///�ư�,��s angleID������angle[]
    angle[angleID] += (x-oldX);
    if(angleID==11) angle[angleID+1] += (oldY-y);///�W�[���`
    ///�p�G�O���ʪ����`,�@����2�� angieID, angleID+1

    oldX=x; oldY=y;///�W�[���`
    ///���n�@��saveAll() saveAll(); ///(�ۤv�g���禡)�����s��
    glutPostRedisplay();///���e�e��
}
void readAll()
{
    if(fin==NULL) fin=fopen("motion.txt", "r");///�}��
    for(int i=0; i<20; i++){///�W�[���`
        ///scanf(   "%d", &a[i]);
        fscanf(fin, "%d", &angle[i]);///Ū��
    }
}
void keyboard(unsigned char key, int x, int y)
{///��L,��angleID
    if(key=='0') angleID=0;
    if(key=='1') angleID=1;
    if(key=='2') angleID=2;
    if(key=='3') angleID=3;
    if(key=='4') angleID=4;
    if(key=='5') angleID=5;
    if(key=='6') angleID=6;
    if(key=='7') angleID=7;
    if(key=='8') angleID=8;
    if(key=='9') angleID=9;
    if(key=='b') angleID=10;
    if(key=='c') angleID=13;
    if(key=='d') angleID=14;
    if(key=='e') angleID=15;
    if(key=='f') angleID=16;
    if(key=='g') angleID=17;
    if(key=='h') angleID=18;
    if(key=='i') angleID=19;
    if(key=='a') angleID=11;///���ʪ����` ///�W�[���`
    if(key=='s') saveAll();///�զn�ʧ@,�~�s��
    if(key=='r'){
        readAll();///�o�ˤ~�}�G!!!!
        glutPostRedisplay();///TODO4 ���e
    }
    if(key=='p'){///�۰ʼ���
        glutTimerFunc(0, timer, 0);
        mp3.Load("music.mp3");
        mp3.Play();
        /// 0ms ���W�}��timer, timer(0)
    }
}
int main(int argc,char**argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(720,720);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("The Fox");
    glutIdleFunc(display);

    glutDisplayFunc(display);
    glutMotionFunc(motion);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);

    glEnable(GL_DEPTH_TEST);///�⥴�����禡�A��b�o��...

    glEnable(GL_LIGHT0);///�⥴�����禡�A��b�o��...
    glEnable(GL_NORMALIZE);///�⥴�����禡�A��b�o��...
    glEnable(GL_COLOR_MATERIAL);///�⥴�����禡�A��b�o��...
    glEnable(GL_LIGHTING);///�⥴�����禡�A��b�o��...

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);///�⥴�����禡�A��b�o��...
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);///�⥴�����禡�A��b�o��...
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);///�⥴�����禡�A��b�o��...
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);///�⥴�����禡�A��b�o��...

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);///�⥴�����禡�A��b�o��...
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);///�⥴�����禡�A��b�o��...
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);///�⥴�����禡�A��b�o��...
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);///�⥴�����禡�A��b�o��...

    glutMainLoop();
}
