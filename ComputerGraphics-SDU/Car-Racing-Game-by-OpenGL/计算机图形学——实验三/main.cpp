
#define RADIX 0.8
#define pai 3.14159265357/180
#define BMP_Header_Length 54


#include <stdlib.h>
#include <stdio.h>
#include <glut.h>
#include <iostream>
#include <string>
#include"BMPloader.h"


#include <math.h>


GLfloat colors[15][4]=
{   {0.0, 0.0, 0.0,0.0}, //黑色0
    {1.0, 0.0, 0.0,0.0}, //红色1
    {0.0, 1.0, 0.0,0.0}, //绿色2
    {0.0, 0.0, 1.0,0.0}, //蓝色3
    {0.0, 1.0, 1.0,0.0}, //青色4
    {1.0, 0.0, 1.0,0.0}, //洋红5
    {0.99,0.84, 0.0,0.0}, //金黄6
    {1.0, 1.0, 1.0,0.0}, //白色7
    {0.53, 0.80, 0.92,0.0}, //天蓝色8
    {0.45, 0.29, 0.07,0.0}, //棕色9
    {0.20, 0.80, 0.20,0.0}, //草地绿色10
    {0.03, 0.18, 0.33,0.0}, //靛青色11
    {0.50, 0.54, 0.53,0.0}, //灰色12
    {0.94, 1.0, 1.0,0.0}, //浅蓝色13
    {0.37, 0.15, 0.07,0.0} //深棕14
};


float distan = 0.0;
float far = 1.0;
float speed = 1.0;
int temp = 1;
int correct  = 0;
float turnangle = 0.0;
double rush = true ;


float xc = 0.0;
float yc = 0.0;
float zc = 0.0;


float xr = 0.0;
float yr = 5.0;
float zr = 20.0;


float zf = 0;
float yf = 5.0;
float xf = 0;
float stop = 0;
bool firstview = false ;
bool solidview = false ;
bool circletrack = false ;
int   wheel_color = 11,car_color = 3,ding_color = 1,track_color = 12;


GLint sky;
GLint liang;
GLint wall;
GLint hanhan;
GLint car;
GLint car2;
GLint grass;
GLint paizi;
GLint front;




GLint w,h,total_bytes;
GLbyte *pixels = 0;
GLint last_texture_ID;
GLuint texture_ID = 0;


void myDisplay();
void myReshape(int , int);
void color_menu(int );
void main_menu(int );
void myinit();


GLint load_texture( const char *file_name)
{
    FILE* pFile = fopen(file_name, "rb" );
    printf( "ok");
    if ( pFile == 0 ) { printf("ok1" );; return 0;}
    fseek(pFile, 0x0012, SEEK_SET);
    fread(&w, 4, 1, pFile);
    fread(&h, 4, 1, pFile);
    fseek(pFile, BMP_Header_Length, SEEK_SET);
    GLuint line_bytes = w * 3;
    while ( line_bytes % 4 != 0 ) {++line_bytes;}
    total_bytes = line_bytes * h;
    pixels = (GLbyte*)malloc(total_bytes);
    if ( pixels == 0 )
    {
        fclose(pFile); printf( "ok2"); return 0;
    }
    if ( fread(pixels, total_bytes, 1, pFile) <= 0 ) { free(pixels); fclose(pFile);printf( "ok3"); return 0; }
    glGenTextures(1, &texture_ID);
    if ( texture_ID == 0 ) { free(pixels); fclose(pFile); printf( "ok4"); return 0; }
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture_ID);
    glBindTexture(GL_TEXTURE_2D, texture_ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
    glBindTexture(GL_TEXTURE_2D, last_texture_ID);
    free(pixels);
    return texture_ID;
}


void background1()


{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, hanhan);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);glVertex3f(-9.9,0,-489);
    glTexCoord2f(0.0f, 1.0f);glVertex3f(-9.9,12,-489);
    glTexCoord2f(1.0f, 1.0f);glVertex3f(9.9,12,-489);
    glTexCoord2f(1.0f, 0.0f);glVertex3f(9.9,0,-489);
    glEnd(); //bottom
    
    
    glBindTexture(GL_TEXTURE_2D, car);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);glVertex3f(-9.8,-5,-100);
    glTexCoord2f(0.0f, 1.0f);glVertex3f(-9.8,15,-100);
    glTexCoord2f(1.0f, 1.0f);glVertex3f(-9.8,15,-115);
    glTexCoord2f(1.0f, 0.0f);glVertex3f(-9.8,-5,-115);
    glEnd(); //bottom
    
    
    glBindTexture(GL_TEXTURE_2D, car2);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);glVertex3f(9.8,-5,-300);
    glTexCoord2f(0.0f, 1.0f);glVertex3f(9.8,15,-300);
    glTexCoord2f(1.0f, 1.0f);glVertex3f(9.8,15,-315);
    glTexCoord2f(1.0f, 0.0f);glVertex3f(9.8,-5,-315);
    glEnd(); //bottom
    
    
    
    
    glBindTexture(GL_TEXTURE_2D, liang);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);glVertex3f(-2.5,7,0);
    glTexCoord2f(0.0f, 1.0f);glVertex3f(-2.5,12,0);
    glTexCoord2f(1.0f, 1.0f);glVertex3f(2.5,12,0);
    glTexCoord2f(1.0f, 0.0f);glVertex3f(2.5,7,0);
    glEnd(); //bottom
    
    
    for (int i=-10;i<=30;i++){
        
        
        
        glBindTexture(GL_TEXTURE_2D, wall);
        glBegin(GL_POLYGON);
        glTexCoord2f(0.0f, 0.0f);glVertex3f(9.9,-5,-(i+1)*20);
        glTexCoord2f(0.0f, 1.0f);glVertex3f(9.9,15,-(i+1)*20);
        glTexCoord2f(1.0f, 1.0f);glVertex3f(9.9,15,-i*20);
        glTexCoord2f(1.0f, 0.0f);glVertex3f(9.9,-5,-i*20);
        glEnd(); //bottom
        
        
        glBegin(GL_POLYGON);
        glTexCoord2f(0.0f, 0.0f);glVertex3f(-9.9,-5,-(i+1)*20);
        glTexCoord2f(0.0f, 1.0f);glVertex3f(-9.9,15,-(i+1)*20);
        glTexCoord2f(1.0f, 1.0f);glVertex3f(-9.9,15,-i*20);
        glTexCoord2f(1.0f, 0.0f);glVertex3f(-9.9,-5,-i*20);
        glEnd(); //bottom
        
        
        glBindTexture(GL_TEXTURE_2D, sky);
        glBegin(GL_POLYGON);
        glTexCoord2f(0.0f, 0.0f);glVertex3f(-10,12.5,-(i+1)*20);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-10,12.5,-i*20);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(10,12.5,-i*20);
        glTexCoord2f(1.0f, 1.0f);glVertex3f(10,12.5,-(i+1)*20);
        glEnd(); //bottom
        
        
    }
    
    
    glDisable(GL_TEXTURE_2D);
}




void background2()


{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, sky);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);glVertex3f(-300,12.5,-300);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-300,12.5,300);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(300,12.5,300);
    glTexCoord2f(1.0f, 1.0f);glVertex3f(300,12.5,-300);
    glEnd(); //bottom
    
    
    glBindTexture(GL_TEXTURE_2D, grass);
    for(int i=1;i<=70;i++){
        for(int j=0;j<=30;j++){
            glBegin(GL_POLYGON);
            glTexCoord2f(0.0f, 0.0f);glVertex3f(-300+10*j,-1,-300+10*i);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-300+10*(j+1),-1,-300+10*i);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(-300+10*(j+1),-1,-300+10*(i+1));
            glTexCoord2f(1.0f, 1.0f);glVertex3f(-300+10*j,-1,-300+10*(i+1));
            glEnd(); //bottom
        }
    }
    glDisable(GL_TEXTURE_2D);
}




void myReshape(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w/(GLfloat)h,1.0,1000.0);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(xr,yr,zr,xc,zr,zc,0.0,1.0,0.0);
}


void myinit()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    GLfloat sun_light1_position[] = {100.0f, 150.0f, 0.0f, 1.0f};
    GLfloat sun_light_ambient[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat sun_light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat sun_spot1_direction[] = {-2.0f,-3.0f,-6.0f};
    GLfloat lmodel_ambient[] = {0.2f,0.2f,0.2f,1.0f};
    GLfloat sun_light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 60.0);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.0);
    glLightfv(GL_LIGHT0, GL_POSITION, sun_light1_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, sun_spot1_direction);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    
    
    
    
    wall = load_texture( "wall.bmp" );
    sky = load_texture( "sky.bmp" );
    hanhan = load_texture( "hanhan.bmp" );
    car = load_texture( "car.bmp" );
    car2 = load_texture( "car2.bmp" );
    paizi = load_texture( "pai.bmp" );
    grass = load_texture( "grass.bmp" );
    liang = load_texture( "liang.bmp" );
    front = load_texture( "front.bmp" );
}


void color1_menu(int index)
{
    car_color = index;
    glutPostRedisplay();
}


void color3_menu(int index)
{
    ding_color = index;
    glutPostRedisplay();
}


void track_menu(int index)
{
    if(index == 0){
        circletrack = true ;
        xc = -5.0;
        glutPostRedisplay();
    }
    else{
        circletrack = false ;
        xc = 0.0;
        glutPostRedisplay();
    }
}


void look_menu(int index)
{
    if(index == 2)
    {
        firstview = true ;
        solidview = false;
        
        
        glutPostRedisplay();
    }
    else if (index == 5)
    {
        firstview = false ;
        solidview = false;
        glutPostRedisplay();
    }
    else if (index == 7)
    {
        solidview = true ;
        glutPostRedisplay();
    }
}


void speed_menu(int index)
{
    speed = index;
}


void color2_menu(int index)
{
    wheel_color = index;
    glutPostRedisplay();
}


void main_menu(int index)
{
    switch(index)
    {
        case (6):
        {    xc = 0.0;
            yc = 0.0;
            zc = 0.0;
            firstview = false;
            solidview = false;
            if (circletrack){
                xc = xc - 5.0;
            }
            xr = 0.0;
            yr = 5.0;
            zr = 20.0;
            distan = 0.0;
            far = 1.0;
            speed = 1.0;
            turnangle = 0.0;
            zf = 0;
            xf = 0;
            yf = 5.0;
            stop = 0;
            glutPostRedisplay();
            break ;
        }
        case (3):
        {   exit(0);
        }
    }
}


void   DrawCarBody(void )  {
    glColor4fv(colors[car_color]);
    GLfloat body_mat_shininess =100.0f;
    glMaterialfv(GL_FRONT, GL_AMBIENT, colors[car_color]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[car_color]);
    glMaterialf(GL_FRONT, GL_SHININESS, body_mat_shininess);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0.0,0.9,0.0);
    glScalef(2.2,1.0,2.2);  //模型变换
    glRotatef(90, 0, 1, 0);
    glutSolidCube(2.0);
    glPopMatrix(); //绘制实心立方体
    glColor4fv(colors[ding_color]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, colors[ding_color]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[ding_color]);
    glMaterialf(GL_FRONT, GL_SHININESS, body_mat_shininess);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0.0,2.2,0.0);
    glScalef(2.4,0.6,2.4);  //模型变换
    glRotatef(90, 0, 1, 0);
    glutSolidCube(1.0); //绘制实心立方体和线框立方体
    glPopMatrix();
    float deep = -0.6;
    glColor4fv(colors[0]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, colors[0]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[0]);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
    
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, paizi);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f);glVertex3f(-1,1,3);
    glTexCoord2f(0.0f, 1.0f);glVertex3f(-1,2,3);
    glTexCoord2f(1.0f, 1.0f);glVertex3f(1,2,3);
    glTexCoord2f(1.0f, 0.0f);glVertex3f(1,1,3);
    glEnd(); //bottom
    
    
    if(firstview&&(!solidview)){
        glBindTexture(GL_TEXTURE_2D, front);
        glBegin(GL_POLYGON);
        glTexCoord2f(0.0f, 0.0f);glVertex3f(-7,0,-8);
        glTexCoord2f(0.0f, 1.0f);glVertex3f(-7,4,-8);
        glTexCoord2f(1.0f, 1.0f);glVertex3f(7,4,-8);
        glTexCoord2f(1.0f, 0.0f);glVertex3f(7,0,-8);
        glEnd();
    } //bottom
    glDisable(GL_TEXTURE_2D);
    
    
    glBegin(GL_POLYGON);    glVertex3f(-2.4, deep,1.0);
    glVertex3f(-2.4, deep,10.0);
    glVertex3f(2.4, deep,10.0);
    glVertex3f(2.4, deep,1.0);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(-3.0, deep,1.0);
    glVertex3f(-3.0, deep,6.0);
    glVertex3f(3.0, deep,6.0);
    glVertex3f(3.0, deep,1.0);
    glEnd();
}
void   DrawCarWheel(void )  {
    GLUquadricObj  *quadratic1,*quadratic2,*quadratic3,*quadratic4;
    GLUquadricObj  *quadraticw1,*quadraticw2,*quadraticw3,*quadraticw4;
    quadraticw1=gluNewQuadric(); // 创建圆片二次几何体
    quadratic1=gluNewQuadric(); // 创建车轮二次几何体
    quadraticw2=gluNewQuadric(); // 创建圆片二次几何体
    quadratic2=gluNewQuadric(); // 创建车轮二次几何体quadraticw1=gluNewQuadric(); // 创建圆片二次几何体
    quadraticw3=gluNewQuadric(); // 创建车轮二次几何体quadraticw1=gluNewQuadric(); // 创建圆片二次几何体
    quadratic3=gluNewQuadric(); // 创建车轮二次几何体
    quadraticw4=gluNewQuadric(); // 创建圆片二次几何体
    quadratic4=gluNewQuadric(); // 创建车轮二次几何体
    glColor4fv(colors[wheel_color]);
    GLfloat wheel_mat__shininess = 30.0f;
    glMaterialfv(GL_FRONT, GL_AMBIENT, colors[wheel_color]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[wheel_color]);
    glMaterialf (GL_FRONT, GL_SHININESS, wheel_mat__shininess);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(-2.9, 0.0, -2.5);
    glRotatef(90, 0, 1, 0);
    glPushMatrix();
    glTranslatef(0, 0, 1.5);
    gluDisk(quadraticw1, 0.0, RADIX, 32, 32); //画圆盘
    glPopMatrix();
    gluCylinder(quadratic1,RADIX,RADIX,1.5f,32,32); //画圆柱
    gluDisk(quadraticw1, 0.0, RADIX, 32, 32); //画圆盘
    glPopMatrix();
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(1.4, 0.0, -2.5);
    glRotatef(90, 0, 1, 0);
    glPushMatrix();
    glTranslatef(0, 0, 1.5);
    gluDisk(quadraticw1, 0.0, RADIX, 32, 32); //画圆盘
    glPopMatrix();
    gluCylinder(quadratic2,RADIX,RADIX,1.5f,32,32); //画圆柱
    gluDisk(quadraticw2, 0.0, RADIX, 32, 32); //画圆盘
    glPopMatrix();
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(-2.9, 0.0, 2.5);
    glRotatef(90, 0, 1, 0);
    glPushMatrix();
    glTranslatef(0, 0, 1.5);
    gluDisk(quadraticw1, 0.0, RADIX, 32, 32); //画圆盘
    glPopMatrix();
    gluCylinder(quadratic3,RADIX,RADIX,1.5f,32,32); //画圆柱
    gluDisk(quadraticw3, 0.0, RADIX, 32, 32); //画圆盘
    glPopMatrix();
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(1.4, 0.0, 2.5);
    glRotatef(90, 0, 1, 0);
    glPushMatrix();
    glTranslatef(0, 0, 1.5);
    gluDisk(quadraticw1, 0.0, RADIX, 32, 32); //画圆盘
    glPopMatrix();
    gluCylinder(quadratic4,RADIX,RADIX,1.5f,32,32); //画圆柱
    gluDisk(quadraticw4, 0.0, RADIX, 32, 32); //画圆盘
    glPopMatrix();
}


void myIdle(void ){
    xc += -distan*(sin(turnangle*pai))/10 -(-distan*(sin(turnangle*pai))/10)*stop;
    zc += -distan*(cos(turnangle*pai))/10-(-distan*(cos(turnangle*pai))/10)*stop;
    if(!circletrack&&(xc<=-10||xc>=10))stop = 1;
    if(circletrack&&(((xc+105)*(xc+105) + zc*zc)<=RADIX*110*RADIX*110||((xc+105)*(xc+105) + zc*zc)>=RADIX*140*RADIX*140))stop = 1;
    zr = zc + 30.0*cos(turnangle*pai);
    xr = xc + 30.0*sin(turnangle*pai);
    zf = zc - 30.0*cos(turnangle*pai);
    xf = xc - 30.0*sin(turnangle*pai);
    myDisplay();
}
void circle(){
    GLUquadricObj  *sky = gluNewQuadric(); // 创建车轮二次几何体
    GLfloat wheel_mat__shininess = 30.0f;
    background2();
    float deep = -0.65;
    for( int cirangleth=1;cirangleth <= 180;cirangleth++){
        if (cirangleth%2 == 1){
            glMaterialfv(GL_FRONT, GL_AMBIENT, colors[6]);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[6]);
            glMaterialf (GL_FRONT, GL_SHININESS, wheel_mat__shininess);
            float cirangle1 = cirangleth*2*pai;
            float cirangle2 = (cirangleth+1)*2*pai;
            glPushMatrix();
            glTranslatef(-105, 0.0, 0);
            glBegin(GL_POLYGON);
            glVertex3f(RADIX*122*cos(cirangle1),deep,-RADIX*122*sin(cirangle1));
            glVertex3f(RADIX*128*cos(cirangle1),deep,-RADIX*128*sin(cirangle1));
            glVertex3f(RADIX*128*cos(cirangle2),deep,-RADIX*128*sin(cirangle2));
            glVertex3f(RADIX*122*cos(cirangle2),deep,-RADIX*122*sin(cirangle2));
            glEnd();
            glPopMatrix();
        }
    }
    GLUquadricObj  *quadraticw;
    quadraticw=gluNewQuadric(); // 创建圆片二次几何体
    glMaterialfv(GL_FRONT, GL_AMBIENT, colors[track_color]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[track_color]);
    glMaterialf (GL_FRONT, GL_SHININESS, wheel_mat__shininess);
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslatef(0, -0.7, -105);
    glRotatef(90, 1, 0, 0);
    gluDisk(quadraticw, RADIX*110, RADIX*140, 256, 256); //画圆盘
    glPopMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, colors[6]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[6]);
    glMaterialf (GL_FRONT, GL_SHININESS, wheel_mat__shininess);
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslatef(0, -0.69, -105);
    glRotatef(90, 1, 0, 0);
    gluDisk(quadraticw, RADIX*110, RADIX*115, 256, 256); //画圆盘
    glPopMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, colors[6]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[6]);
    glMaterialf (GL_FRONT, GL_SHININESS, wheel_mat__shininess);
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslatef(0, -0.69, -105);
    glRotatef(90, 1, 0, 0);
    gluDisk(quadraticw, RADIX*135, RADIX*140, 256, 256); //画圆盘
    glPopMatrix();
    /*glMaterialfv(GL_FRONT, GL_AMBIENT, colors[10]);
     glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[10]);
     glMaterialf (GL_FRONT, GL_SHININESS, wheel_mat__shininess);
     glPushMatrix();
     glRotatef(90, 0, 1, 0);
     glTranslatef(0, -0.7, -105);
     glRotatef(90, 1, 0, 0);
     gluDisk(quadraticw, 0, RADIX*110, 256, 256); //画圆盘
     glPopMatrix();*/
    GLfloat track_mat__shininess = 30.0f;
    glMaterialfv(GL_FRONT, GL_AMBIENT, colors[9]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[9]);
    glMaterialf (GL_FRONT, GL_SHININESS, track_mat__shininess);
    glPushMatrix();
    glTranslatef(-106.0, -0.7, 0.0);
    glRotatef(90.0, -1.0, 0.0, 0.0);
    gluCylinder(sky,RADIX*140,RADIX*140,30.0f,1024,1024); //画圆柱
    glPopMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, colors[8]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[8]);
    glMaterialf (GL_FRONT, GL_SHININESS, track_mat__shininess);
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslatef(0, 28.6, -105);
    glRotatef(90, 1, 0, 0);
    gluDisk(sky, 0, RADIX*140, 256, 256); //画圆盘
    glPopMatrix();
    //画出起始点的四个黑白相间的立柱
    glMaterialfv(GL_FRONT, GL_AMBIENT, colors[7]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[7]);
    glMaterialf (GL_FRONT, GL_SHININESS, track_mat__shininess);
    glPushMatrix();
    glTranslatef(-9.0, 0.0, 15.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    gluDisk(quadraticw, 0, RADIX, 32, 32); //画圆盘
    gluCylinder(quadraticw,RADIX,RADIX,1.5f,32,32); //画圆柱
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.0, 0.0, 15.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    gluDisk(quadraticw, 0, RADIX, 32, 32); //画圆盘
    gluCylinder(quadraticw,RADIX,RADIX,1.5f,32,32); //画圆柱
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-4.0, 0.0, 15.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    gluDisk(quadraticw, 0, RADIX, 32, 32); //画圆盘
    gluCylinder(quadraticw,RADIX,RADIX,1.5f,32,32); //画圆柱
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-14.0, 0.0, 15.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    gluDisk(quadraticw, 0, RADIX, 32, 32); //画圆盘
    gluCylinder(quadraticw,RADIX,RADIX,1.5f,32,32); //画圆柱
    glPopMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, colors[0]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[0]);
    glMaterialf (GL_FRONT, GL_SHININESS, track_mat__shininess);
    glPushMatrix();
    glTranslatef(-9.0, 0.8, 15.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    gluDisk(quadraticw, 0, RADIX, 32, 32); //画圆盘
    gluCylinder(quadraticw,RADIX,RADIX,0.8f,32,32); //画圆柱
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.0, 0.8, 15.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    gluDisk(quadraticw, 0, RADIX, 32, 32); //画圆盘
    gluCylinder(quadraticw,RADIX,RADIX,0.8f,32,32); //画圆柱
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-4.0, 0.8, 15.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    gluDisk(quadraticw, 0, RADIX, 32, 32); //画圆盘
    gluCylinder(quadraticw,RADIX,RADIX,0.8f,32,32); //画圆柱
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-14.0, 0.8, 15.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    gluDisk(quadraticw, 0, RADIX, 32, 32); //画圆盘
    gluCylinder(quadraticw,RADIX,RADIX,0.8f,32,32); //画圆柱
    glPopMatrix();
}


void straight(){
    float deep = -0.65;
    GLfloat wheel_mat__shininess = 30.0f;
    background1();
    for( int i=1;i<=100;i++){
        glBegin(GL_POLYGON);
        if (i%2==1)
        {   glMaterialfv(GL_FRONT, GL_AMBIENT, colors[6]);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[6]);
            glMaterialf (GL_FRONT, GL_SHININESS, wheel_mat__shininess);
            glVertex3f(-2,deep,-i*5);
            glVertex3f(-2,deep,-(i-1)*5);
            glVertex3f(2,deep,-(i-1)*5);
            glVertex3f(2,deep,-i*5);
            glEnd();
        }
    }
    deep = -0.7;
    glBegin(GL_POLYGON);
    glMaterialfv(GL_FRONT, GL_AMBIENT, colors[track_color]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[track_color]);
    glMaterialf (GL_FRONT, GL_SHININESS, wheel_mat__shininess);
    glVertex3f(-10,deep,-500);
    glVertex3f(-10,deep,0);
    glVertex3f(10,deep,0);
    glVertex3f(10,deep,-500);
    glEnd();
    glBegin(GL_POLYGON);
    glMaterialfv(GL_FRONT, GL_AMBIENT, colors[4]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[4]);
    glMaterialf (GL_FRONT, GL_SHININESS, wheel_mat__shininess);
    glVertex3f(-10,13,-500);
    glVertex3f(-10,13,50);
    glVertex3f(10,13,50);
    glVertex3f(10,13,-500);
    glEnd();
    glMaterialfv(GL_FRONT, GL_AMBIENT, colors[0]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[0]);
    glMaterialf (GL_FRONT, GL_SHININESS, wheel_mat__shininess);
    glBegin(GL_POLYGON);
    glVertex3f(-10,deep,5);
    glVertex3f(-10,deep,0);
    glVertex3f(10,deep,0);
    glVertex3f(10,deep,5);
    glEnd();
    glMaterialfv(GL_FRONT, GL_AMBIENT, colors[7]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[7]);
    glMaterialf (GL_FRONT, GL_SHININESS, wheel_mat__shininess);
    glBegin(GL_POLYGON);
    glVertex3f(-10,deep,5);
    glVertex3f(-10,deep,10);
    glVertex3f(10,deep,10);
    glVertex3f(10,deep,5);
    glEnd();
    glMaterialfv(GL_FRONT, GL_AMBIENT, colors[0]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[0]);
    glMaterialf (GL_FRONT, GL_SHININESS, wheel_mat__shininess);
    glBegin(GL_POLYGON);
    glVertex3f(-10,deep,10);
    glVertex3f(-10,deep,15);
    glVertex3f(10,deep,15);
    glVertex3f(10,deep,10);
    glEnd();
    glMaterialfv(GL_FRONT, GL_AMBIENT, colors[7]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[7]);
    glMaterialf (GL_FRONT, GL_SHININESS, wheel_mat__shininess);
    glBegin(GL_POLYGON);
    glVertex3f(-10,deep,15);
    glVertex3f(-10,deep,20);
    glVertex3f(10,deep,20);
    glVertex3f(10,deep,15);
    glEnd();
    glMaterialfv(GL_FRONT, GL_AMBIENT, colors[0]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[0]);
    glMaterialf (GL_FRONT, GL_SHININESS, wheel_mat__shininess);
    glBegin(GL_POLYGON);
    glVertex3f(-10,deep,20);
    glVertex3f(-10,deep,30);
    glVertex3f(10,deep,30);
    glVertex3f(10,deep,20);
    glEnd();
    glMaterialfv(GL_FRONT, GL_AMBIENT, colors[6]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[6]);
    glMaterialf (GL_FRONT, GL_SHININESS, wheel_mat__shininess);
    glPushMatrix();
    glTranslatef(0.0, 0.0, -215);
    glScalef(20, 30, 550);
    glutSolidCube(1.0);
    glPopMatrix();
    glutPostRedisplay();
    //画路灯
    GLUquadricObj  *quadraticw;
    quadraticw=gluNewQuadric(); // 创建圆片二次几何体
    for( int i=0;i<10;i++){
        glMaterialfv(GL_FRONT, GL_AMBIENT, colors[14]);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[14]);
        glMaterialf (GL_FRONT, GL_SHININESS, wheel_mat__shininess);
        glPushMatrix();
        glTranslatef(-8, 0, -i*50);
        glRotatef(90,-1 , 0 , 0);
        gluCylinder(quadraticw,RADIX/8,RADIX/8,8.0f,32,32); //画圆柱
        glPopMatrix();
        glPushMatrix();
        glTranslatef(8, 0, -i*50);
        glRotatef(90,-1 , 0 , 0);
        gluCylinder(quadraticw,RADIX/8,RADIX/8,8.0f,32,32); //画圆柱
        glPopMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT, colors[5]);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[5]);
        glMaterialf (GL_FRONT, GL_SHININESS, wheel_mat__shininess);
        glPushMatrix();
        glTranslatef(8, 8, -i*50);
        glutSolidSphere(1.0, 32, 32);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(-8, 8, -i*50);
        glutSolidSphere(1.0, 32, 32);
        glPopMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT, colors[4]);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[4]);
        glMaterialf (GL_FRONT, GL_SHININESS, wheel_mat__shininess);
        glPushMatrix();
        glTranslatef(-8, 9, -i*50);
        glutSolidCube(0.5);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(8, 9, -i*50);
        glutSolidCube(0.5);
        glPopMatrix();
    }
    glutPostRedisplay();
}
void myDisplay()
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    if(!firstview&&!solidview){
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(xr,yr,zr,xc,yc,zc,0.0,1.0,0.0);
    }
    else if(firstview&&!solidview){
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(xc,5.0,zc,xf,yf,zf,0.0,1.0,0.0);
    }
    else if (solidview){
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0,5,0,xc,yc,zc,0.0,1.0,0.0);
    }
    if(!circletrack)
        straight();
    if(circletrack)
        circle();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(xc, yc, zc);
    if(turnangle != 0.0){glRotatef(turnangle,0,1,0);}
    DrawCarBody();
    DrawCarWheel();
    glPopMatrix();
    
    glutSwapBuffers();
}


void myKeyboard(unsigned char key, int x, int y){
    switch(key) {
        case 'q' :
            zr -= far/3*4;
            yr -= far;
            glutPostRedisplay();
            break ;
        case 'e' :
            zr += far/3*4;
            yr += far;
            glutPostRedisplay();
            break ;
        case 'w' :
            stop = 0;
            rush = true ;
            //speed *=2;
            distan = speed;
            glutPostRedisplay();
            break ;
        case 'u' :
            stop = 0;
            speed *=2;
            if (rush){distan = speed;}
            else {distan = -speed;}
            glutPostRedisplay();
            break ;
        case 'j' :
            stop = 0;
            speed /=2;
            if (rush){distan = speed;}
            else {distan = -speed;}
            glutPostRedisplay();
            break ;
        case 's' :
            stop = 0;
            rush = false ;
            //speed /=2;
            distan = -speed;
            glutPostRedisplay();
            break ;
        case 'x' :
            stop = 1;
            glutPostRedisplay();
            break ;
        case 'a' :
            turnangle += 5;
            glutPostRedisplay();
            break ;
        case 't' :
            if (temp%2 == 1)firstview = true ,solidview = false ;
            else if (temp%2 == 0)firstview = false,solidview = false;
            temp++;
            glutPostRedisplay();
            break ;
        case 'd' :
            turnangle -= 5;
            glutPostRedisplay();
            break ;
    }
}


int main(int argc, char** argv)
{
    int c_menu, w_menu,s_menu,v_menu,t_menu,l_menu;
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowPosition(130,130);
    glutInitWindowSize(1200, 800);
    glutCreateWindow( "Let's start the game of speed and passion!——亮闪1993" );
    myinit ();
    glutDisplayFunc(myDisplay);
    glutReshapeFunc (myReshape);
    glutKeyboardFunc(myKeyboard);
    glutIdleFunc(myIdle);
    c_menu = glutCreateMenu(color1_menu);
    glutAddMenuEntry( "黑色" ,0);
    glutAddMenuEntry( "红色" ,1);
    glutAddMenuEntry( "绿色" ,2);
    glutAddMenuEntry( "蓝色" ,3);
    glutAddMenuEntry( "青色" ,4);
    glutAddMenuEntry( "洋红" ,5);
    glutAddMenuEntry( "黄色" ,6);
    glutAddMenuEntry( "白色" ,7);
    v_menu = glutCreateMenu(color3_menu);
    glutAddMenuEntry( "黑色" ,0);
    glutAddMenuEntry( "红色" ,1);
    glutAddMenuEntry( "绿色" ,2);
    glutAddMenuEntry( "蓝色" ,3);
    glutAddMenuEntry( "青色" ,4);
    glutAddMenuEntry( "洋红" ,5);
    glutAddMenuEntry( "黄色" ,6);
    glutAddMenuEntry( "白色" ,7);
    w_menu = glutCreateMenu(color2_menu);
    glutAddMenuEntry( "黑色" ,0);
    glutAddMenuEntry( "红色" ,1);
    glutAddMenuEntry( "绿色" ,2);
    glutAddMenuEntry( "蓝色" ,3);
    glutAddMenuEntry( "青色" ,4);
    glutAddMenuEntry( "洋红" ,5);
    glutAddMenuEntry( "黄色" ,6);
    glutAddMenuEntry( "白色" ,7);
    s_menu = glutCreateMenu(speed_menu);
    glutAddMenuEntry( "飙车速度" ,5);
    glutAddMenuEntry( "中等速度" ,2);
    glutAddMenuEntry( "爬坡速度" ,1);
    glutAddMenuEntry( "加速—U,减速—J" ,7);
    t_menu = glutCreateMenu(track_menu);
    glutAddMenuEntry( "更换一条圆形封闭跑道" , 0);
    glutAddMenuEntry( "更换一条直线跑道" , 1);
    l_menu = glutCreateMenu(look_menu);
    glutAddMenuEntry( "第一视角——切换键T" , 2);
    glutAddMenuEntry( "上帝视角(默认)——切换键T" , 5);
    glutAddMenuEntry( "固定视角——切换键T" , 7);
    glutAddMenuEntry( "微调摄像机——Q-下移 ,E—上移" , 4);
    glutCreateMenu(main_menu);
    glutAddSubMenu( "赛车整体喷漆" , c_menu);
    glutAddSubMenu( "赛车更换顶棚" , v_menu);
    glutAddSubMenu( "赛车更换轮胎" , w_menu);
    glutAddSubMenu( "给赛车换挡" , s_menu);
    glutAddSubMenu( "更换跑道" , t_menu);
    glutAddSubMenu( "切换视角" , l_menu);
    glutAddMenuEntry( "回到起点-重新游戏" , 6);
    glutAddMenuEntry( "退出游戏" ,3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();
}
