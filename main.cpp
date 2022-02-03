#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <GL/glut.h>
#include "CMP3_MCI.h"
#include "glm.h" ///使用外掛
CMP3_MCI mp3;
GLMmodel*model=NULL; ///指標，指到GLM的資料結構
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
FILE * fin=NULL;///宣告檔案指標
int angle[20]={};///增加關節
int angleID=0;///0,1,2,3
int oldX, oldY;

/// C/C++因為函式使用前, 要先宣告or定義, 有時候會順序不對
void display();
void motion(int x, int y);
void mouse(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);
void saveAll();
///可以在程式的最前面, 把全部的函式的外形, 先宣告一次
///(不要寫完整的定義)
int oldAngle[20]={};///舊的 ///TODO1602:增加關節
int newAngle[20]={};///新的, 之後會變舊的///TODO1602:增加關節

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 0.0f, 0.0f, -5.0f, 1.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

void timer(int t)///自動播放
{
    glutTimerFunc(10, timer, t+1);
    ///鬧鐘叫了, 再播下一個鬧鐘100ms之後叫, timer(t+1)
    if(t==0){///第1次要先讀新的
        if(fin==NULL) fin=fopen("motion.txt", "r");
        for(int i=0; i<20; i++){///增加關節
            fscanf(fin, "%d", &newAngle[i]);
        }
    }
    if(t%30==0){///我們要把新的變舊的
        for(int i=0; i<20; i++){///增加關節
            oldAngle[i] = newAngle[i];///新的變舊的
            fscanf(fin, "%d", &newAngle[i]);///再讀新的
        }
    }
    float Alpha = (t%30)/30.0;///0.0~~1.0
    for(int i=0; i<20; i++){///Alpha內插///增加關節
        angle[i] = Alpha*newAngle[i]+(1-Alpha)*oldAngle[i];
        ///printf("%d ", angle[i]);///印出角度,方便debug
    }
    ///printf(" %.2f\n", Alpha);///印出Alpha,方便debug
    glutPostRedisplay();///自動播放
}

void drawBody()///移出來變函式
{
    if(model==NULL){///我們需要 glm 來幫忙秀3D模型
        model = glmReadOBJ("fox/body.obj");///讀入3D模型,在執行目錄中
        glmUnitize(model);///....還缺一些...
        glmFacetNormals(model);///重算(面)法向量
        glmVertexNormals(model, 90);///重算(頂點vn)法向量
    }
    glPushMatrix();
        glScalef(0.6, 0.6, 0.6);///希望它小一點
        glRotatef(0, 0,1,0);///對Y軸轉180度
        glmDraw(model, GLM_SMOOTH | GLM_MATERIAL);
    glPopMatrix();
}
void drawArm()///另一個模型
{
    if(model2==NULL){
        model2 = glmReadOBJ("fox/Ruhand.obj");
        glmUnitize(model2);///大太了,就縮小 -1...+1
    }
    glPushMatrix();
        glScalef(0.5, 0.5, 0.5);///變小一點
        glRotatef(0,0,1,0);///轉一下 側面
        glmDraw(model2,  GLM_SMOOTH | GLM_MATERIAL);
    glPopMatrix();
}
void drawArm2()///另一個模型
{
    if(model3==NULL){
        model3 = glmReadOBJ("fox/Rdhand.obj");
        glmUnitize(model3);///大太了,就縮小 -1...+1
    }
    glPushMatrix();
        glScalef(0.5, 0.5, 0.5);///變小一點
        glRotatef(180,0,1,0);///轉一下 側面
        glmDraw(model3,  GLM_SMOOTH | GLM_MATERIAL);
    glPopMatrix();
}
void drawArm3()///另一個模型
{
    if(model4==NULL){
        model4 = glmReadOBJ("fox/Luhand.obj");
        glmUnitize(model4);///大太了,就縮小 -1...+1
    }
    glPushMatrix();
        glScalef(0.5, 0.5, 0.5);///變小一點
        glRotatef(0,0,1,0);///轉一下 側面
        glmDraw(model4,  GLM_SMOOTH | GLM_MATERIAL);
    glPopMatrix();
}
void drawArm4()///另一個模型
{
    if(model5==NULL){
        model5 = glmReadOBJ("fox/Ldhand.obj");
        glmUnitize(model5);///大太了,就縮小 -1...+1
    }
    glPushMatrix();
        glScalef(0.5, 0.5, 0.5);///變小一點
        glRotatef(180,0,1,0);///轉一下 側面
        glmDraw(model5,  GLM_SMOOTH | GLM_MATERIAL);
    glPopMatrix();
}
void drawLeg()///另一個模型
{
    if(model6==NULL){
        model6 = glmReadOBJ("fox/Ruleg.obj");
        glmUnitize(model6);///大太了,就縮小 -1...+1
    }
    glPushMatrix();
        glScalef(0.8, 0.8, 0.8);///變小一點
        glRotatef(0,0,1,0);///轉一下 側面
        glmDraw(model6,  GLM_SMOOTH | GLM_MATERIAL);
    glPopMatrix();
}
void drawLeg2()///另一個模型
{
    if(model7==NULL){
        model7 = glmReadOBJ("fox/Rdleg.obj");
        glmUnitize(model7);///大太了,就縮小 -1...+1
    }
    glPushMatrix();
        glScalef(0.9, 0.9, 0.9);///變小一點
        glRotatef(0,0,1,0);///轉一下 側面
        glmDraw(model7,  GLM_SMOOTH | GLM_MATERIAL);
    glPopMatrix();
}
void drawLeg3()///另一個模型
{
    if(model8==NULL){
        model8 = glmReadOBJ("fox/Luleg.obj");
        glmUnitize(model8);///大太了,就縮小 -1...+1
    }
    glPushMatrix();
        glScalef(0.8, 0.8, 0.8);///變小一點
        glRotatef(0,0,1,0);///轉一下 側面
        glmDraw(model8,  GLM_SMOOTH | GLM_MATERIAL);
    glPopMatrix();
}
void drawLeg4()///另一個模型
{
    if(model9==NULL){
        model9 = glmReadOBJ("fox/Ldleg.obj");
        glmUnitize(model9);///大太了,就縮小 -1...+1
    }
    glPushMatrix();
        glScalef(0.9, 0.9, 0.9);///變小一點
        glRotatef(0,0,1,0);///轉一下 側面
        glmDraw(model9,  GLM_SMOOTH | GLM_MATERIAL);
    glPopMatrix();
}
void drawHead()///另一個模型
{
    if(modela==NULL){
        modela = glmReadOBJ("fox/head.obj");
        glmUnitize(modela);///大太了,就縮小 -1...+1
    }
    glPushMatrix();
        glScalef(0.37, 0.37, 0.37);///變小一點
        glRotatef(0,0,1,0);///轉一下 側面
        glmDraw(modela,  GLM_SMOOTH | GLM_MATERIAL);
    glPopMatrix();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0.8,0.6,1);
    glPushMatrix();
        glTranslatef( angle[11]/200.0, angle[12]/200.0, 0);
        drawBody();///移出來變函式
        glPushMatrix();/// 右
            glTranslatef(0.13,0,-0.23);/// (3)等一下要掛在哪裡
            glRotatef(angle[0], 0,0,1);/// (1)有個轉動
            glRotatef(angle[9], 0,1,0);
            glTranslatef(0.1, 0, 0);/// (2)移動轉動的中心
            drawArm();///右上手臂
            glPushMatrix();
                glTranslatef(0.05,0.001,0.004);
                glRotatef(angle[1], 0,0,1);
                glRotatef(angle[10], 0,1,0);
                glTranslatef(0.1, 0, 0);
                drawArm2();///右下手臂
            glPopMatrix();
        glPopMatrix();

        glPushMatrix();/// 左
            glTranslatef(-0.13,0,-0.23);///(3)等一下要掛在哪裡
            glRotatef(angle[2], 0,0,1);///(1)有個轉動
            glRotatef(angle[13], 0,1,0);
            glTranslatef(-0.1, 0, 0);///(2)移動轉動的中心
            drawArm3();///左上手臂
            glPushMatrix();///TODO7:
                glTranslatef(-0.05,0.001,0);
                glRotatef(angle[3], 0,0,1);
                glRotatef(angle[14], 0,1,0);
                glTranslatef(-0.1, 0, 0);
                drawArm4();///左下手臂
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glPushMatrix();/// 右
            glTranslatef( angle[11]/200.0, angle[12]/200.0, 0);
            glTranslatef(0.12, -0.3, 0);/// (3)等一下要掛在哪裡
            glRotatef(angle[4], 0,0,1);/// (1)有個轉動
            glRotatef(angle[15], 1,0,0);
            glTranslatef(0, -0.08, 0);/// (2)移動轉動的中心
            drawLeg();///右上腿
            glPushMatrix();
                glTranslatef(0,-0.04,0);
                glRotatef(angle[5], 0,0,1);
                glRotatef(angle[16], 1,0,0);
                glTranslatef(0, -0.08, 0);
                drawLeg2();///右下腿
            glPopMatrix();
        glPopMatrix();

        glPushMatrix();/// 左
            glTranslatef( angle[11]/200.0, angle[12]/200.0, 0);
            glTranslatef(-0.12, -0.3, 0);///(3)等一下要掛在哪裡
            glRotatef(angle[6], 0,0,1);///(1)有個轉動
            glRotatef(angle[17], 1,0,0);
            glTranslatef(0, -0.08, 0);///(2)移動轉動的中心
            drawLeg3();///左上腿
            glPushMatrix();
                glTranslatef(0,-0.04,0);
                glRotatef(angle[7], 0,0,1);
                glRotatef(angle[18], 1,0,0);
                glTranslatef(0, -0.08, 0);
                drawLeg4();///左下腿
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
    glPushMatrix();
        glTranslatef( angle[11]/200.0, angle[12]/200.0, 0);
        glTranslatef(0,0.55,-0.23);
        glRotatef(angle[8], 0,1,0);
        glRotatef(angle[19], 1,0,0);
        glTranslatef(0, 0, 0);
        drawHead();///頭
    glPopMatrix();
    glutSwapBuffers();
}
void mouse(int button, int state, int x, int y)
{///備份(old)mouse位置
    oldX=x; oldY=y;///備份(old)mouse位置
}
///用函式來做事, 漂亮!!!
void saveAll()///(自己寫的函式)全部存檔
{        ///小心!裡面宣告,不會讓外面記起來
    if(fout==NULL) fout=fopen("motion.txt", "w+");///開檔
    for(int i=0; i<20; i++){///增加關節
         printf(      "%d ", angle[i]);///印畫面
        fprintf(fout, "%d ", angle[i]);///寫檔案
    }
     printf(      "\n");///跳行, 畫面不會亂
    fprintf(fout, "\n");///跳行, 畫面不會亂
}
void motion(int x, int y)
{///滑動,更新 angleID對應的angle[]
    angle[angleID] += (x-oldX);
    if(angleID==11) angle[angleID+1] += (oldY-y);///增加關節
    ///如果是移動的關節,一次動2個 angieID, angleID+1

    oldX=x; oldY=y;///增加關節
    ///不要一直saveAll() saveAll(); ///(自己寫的函式)全部存檔
    glutPostRedisplay();///重畫畫面
}
void readAll()
{
    if(fin==NULL) fin=fopen("motion.txt", "r");///開檔
    for(int i=0; i<20; i++){///增加關節
        ///scanf(   "%d", &a[i]);
        fscanf(fin, "%d", &angle[i]);///讀檔
    }
}
void keyboard(unsigned char key, int x, int y)
{///鍵盤,選angleID
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
    if(key=='a') angleID=11;///移動的關節 ///增加關節
    if(key=='s') saveAll();///調好動作,才存檔
    if(key=='r'){
        readAll();///這樣才漂亮!!!!
        glutPostRedisplay();///TODO4 重畫
    }
    if(key=='p'){///自動播放
        glutTimerFunc(0, timer, 0);
        mp3.Load("music.mp3");
        mp3.Play();
        /// 0ms 馬上開啟timer, timer(0)
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

    glEnable(GL_DEPTH_TEST);///把打光的函式，放在這裡...

    glEnable(GL_LIGHT0);///把打光的函式，放在這裡...
    glEnable(GL_NORMALIZE);///把打光的函式，放在這裡...
    glEnable(GL_COLOR_MATERIAL);///把打光的函式，放在這裡...
    glEnable(GL_LIGHTING);///把打光的函式，放在這裡...

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);///把打光的函式，放在這裡...
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);///把打光的函式，放在這裡...
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);///把打光的函式，放在這裡...
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);///把打光的函式，放在這裡...

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);///把打光的函式，放在這裡...
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);///把打光的函式，放在這裡...
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);///把打光的函式，放在這裡...
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);///把打光的函式，放在這裡...

    glutMainLoop();
}
