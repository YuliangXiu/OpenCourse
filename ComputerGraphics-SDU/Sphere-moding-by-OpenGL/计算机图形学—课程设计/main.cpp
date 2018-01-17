//
//  main.cpp
//  计算机图形学—课程设计
//
//  Created by 修宇亮 on 13-10-14.
//  Copyright (c) 2013年 修宇亮. All rights reserved.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <math.h>
using namespace std;

#define RED 1
#define GREEN 2
#define BLUE 3
#define WHITE 4
#define PINK 5
#define YELLOW 6
#define BLACK 7



float PI = 3.14159265357;
float c = PI/180;
float time1,time2,time3;
float foot = 20;
float r = 2;
//int menu, submenu1, submenu2;//定义三个菜单的索引

void myDisplay3(void){
   
    float phi;
    float thea;
    float m,n,p ;
    r = 1;
    glClear(GL_COLOR_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glColor3f(1.0,0.0,0.0);
    int distance = 0;
    foot = 20;
    
    
    for(int i=0;i<2;i+=1){
       
        //printf("123");
    for(phi = -90 ; phi <= 90 ; phi+=foot){
         glBegin(GL_TRIANGLES);
        for(thea = -180 ; thea <= 180 ; thea+=foot){
            float phir = phi*c;
            float theatar = c*thea;
            float phir20 = c*(phi + foot);
            float theatar20 = c*(thea + foot);
            
            
            m = sin(theatar)*cos(phir)*r+distance;
            n = cos(theatar)*cos(phir)*r;
            p = sin(phir)*r;
            glVertex3d(m, n, p );
            m = sin(theatar)*cos(phir20)*r+distance;
            n = cos(theatar)*cos(phir20)*r;
            p = sin(phir20)*r;
            glVertex3d(m, n, p );
            m = sin(theatar20)*cos(phir)*r+distance;
            n = cos(theatar20)*cos(phir)*r;
            p = sin(phir)*r;
            glVertex3d(m, n, p );
            
            
        }
        glEnd();
        glFlush();
        
    }
        
        
                    distance+=3;    }
}

void myDisplay4(void){
    float phi;
    float thea;
    float m,n,p ;
    r = 0.6;
    foot = 20;
    glClear(GL_COLOR_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glColor3f(0.0,1.0,0.0);
    int distance = -4;
    for(int i=0;i<4;i+=1){
        
        
        for(phi = -90 ; phi <= 90 ; phi+=foot){
            glBegin(GL_TRIANGLES);
            for(thea = -180 ; thea <= 180 ; thea+=foot){
                float phir = phi*c;
                float theatar = c*thea;
                float phir20 = c*(phi + foot);
                float theatar20 = c*(thea + foot);
                
                
                m = sin(theatar)*cos(phir)*r+distance;
                n = cos(theatar)*cos(phir)*r;
                p = sin(phir)*r;
                glVertex3d(m, n, p );
                m = sin(theatar)*cos(phir20)*r+distance;
                n = cos(theatar)*cos(phir20)*r;
                p = sin(phir20)*r;
                glVertex3d(m, n, p );
                m = sin(theatar20)*cos(phir)*r+distance;
                n = cos(theatar20)*cos(phir)*r;
                p = sin(phir)*r;
                glVertex3d(m, n, p );
                
                
            }
            glEnd();
            glFlush();
            
        }
        
        
    distance+=2;}
}



 void myDisplay2(void){
    float phi;
    float thea;
    float m,n,p ;
    foot = 20;
    r = 2;
    glClear(GL_COLOR_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glColor3f(1.0,1.0,1.0);
    
    for(phi = -90 ; phi <= 90 ; phi+=foot){
        
        glBegin(GL_TRIANGLES);
        for(thea = -180 ; thea <= 180 ; thea+=foot){
            float phir = phi*c;
            float theatar = c*thea;
            float phir20 = c*(phi + foot);
            float theatar20 = c*(thea + foot);
            
            
            m = sin(theatar)*cos(phir)*r;
            n = cos(theatar)*cos(phir)*r;
            p = sin(phir)*r;
            glVertex3d(m, n, p );
            m = sin(theatar)*cos(phir20)*r;
            n = cos(theatar)*cos(phir20)*r;
            p = sin(phir20)*r;
            glVertex3d(m, n, p );
            m = sin(theatar20)*cos(phir)*r;
            n = cos(theatar20)*cos(phir)*r;
            p = sin(phir)*r;
            glVertex3d(m, n, p );
            
            
        }
        glEnd();
        glFlush();
        
        
        
    }
}

void myDisplay7(void){
    
    foot = 20;
    r = 2;
    float x,y,z;
    glutGet(GLUT_ELAPSED_TIME);
    glClear(GL_COLOR_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glColor3f(1.0,1.0,1.0);
    
    for(float phi = -80 ; phi <= 80 ; phi+=foot){
        float phir = phi*c;
        float phir20 = c*(phi + foot);
        glBegin(GL_TRIANGLE_STRIP);
        for(float thea = -180 ; thea <= 180 ; thea+=foot){
            
            float theatar = c*thea;
            x = sin(theatar)*cos(phir)*r;
            y = cos(theatar)*cos(phir)*r;
            z = sin(phir)*r;
            glVertex3d(x, y, z );
            x = sin(theatar)*cos(phir20)*r;
            y = cos(theatar)*cos(phir20)*r;
            z = sin(phir20)*r;
            glVertex3d(x, y, z );
        }
        glEnd();
        
        
        
    }   glVertex3d(0.0, 0.0, 1.0);
    float c80 = c*80;
    
    
    z = sin(c80)*r;
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_TRIANGLE_FAN);
    for(float thea = -180 ; thea <= 180 ; thea+=foot){
        
        float theatar = c*thea;
        x = sin(theatar)*cos(c80)*r;
        y = cos(theatar)*cos(c80)*r;
        glVertex3d(x, y, z );
        
    }   glEnd();
    
    
    glVertex3d(0.0, 0.0, -1.0);
    z = sin(-c80)*r;
    glColor3f(0.0,0.0,1.0);
    
    glBegin(GL_TRIANGLE_FAN);
    for(float thea = -180 ; thea <= 180 ; thea+=foot){
        
        float theatar = c*thea;
        x = sin(theatar)*cos(c80)*r;
        y = cos(theatar)*cos(c80)*r;
        glVertex3d(x, y, z );
        
    }
    
    glEnd();
    
    glFlush();
    
    
    }


void myDisplay6(void){
    float phi;
    float thea;
    float m,n,p ;
    foot = 5;
    glClear(GL_COLOR_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glColor3f(1.0,1.0,1.0);
    
    for(phi = -90 ; phi <= 90 ; phi+=foot){
        
        glBegin(GL_TRIANGLES);
        for(thea = -180 ; thea <= 180 ; thea+=foot){
            float phir = phi*c;
            float theatar = c*thea;
            float phir20 = c*(phi + foot);
            float theatar20 = c*(thea + foot);
            
            
            m = sin(theatar)*cos(phir)*r;
            n = cos(theatar)*cos(phir)*r;
            p = sin(phir)*r;
            glVertex3d(m, n, p );
            m = sin(theatar)*cos(phir20)*r;
            n = cos(theatar)*cos(phir20)*r;
            p = sin(phir20)*r;
            glVertex3d(m, n, p );
            m = sin(theatar20)*cos(phir)*r;
            n = cos(theatar20)*cos(phir)*r;
            p = sin(phir)*r;
            glVertex3d(m, n, p );
            
            
        }
        glEnd();
        glFlush();
        
        
        
    }
}

void myDisplay5(void){
    float phi;
    float thea;
    float m,n,p ;
    r = 0.6;
    glClear(GL_COLOR_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glColor3f(1.0,1.0,1.0);
    
    for(phi = -90 ; phi <= 90 ; phi+=foot){
        
        glBegin(GL_TRIANGLES);
        for(thea = -180 ; thea <= 180 ; thea+=foot){
            float phir = phi*c;
            float theatar = c*thea;
            float phir20 = c*(phi + foot);
            float theatar20 = c*(thea + foot);
            
            
            m = sin(theatar)*cos(phir)*r;
            n = cos(theatar)*cos(phir)*r;
            p = sin(phir)*r;
            glVertex3d(m, n, p );
            m = sin(theatar)*cos(phir20)*r;
            n = cos(theatar)*cos(phir20)*r;
            p = sin(phir20)*r;
            glVertex3d(m, n, p );
            m = sin(theatar20)*cos(phir)*r;
            n = cos(theatar20)*cos(phir)*r;
            p = sin(phir)*r;
            glVertex3d(m, n, p );
            
            
        }
        glEnd();
        glFlush();
        
        
        
    }
}


 void myDisplay(void)
{
     foot = 20;
     r = 2;
    float x,y,z;
    glutGet(GLUT_ELAPSED_TIME);
    glClear(GL_COLOR_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glColor3f(1.0,1.0,1.0);

    for(float phi = -80 ; phi <= 80 ; phi+=foot){
        float phir = phi*c;
        float phir20 = c*(phi + foot);
        glBegin(GL_TRIANGLE_STRIP);
    for(float thea = -180 ; thea <= 180 ; thea+=foot){
            
            float theatar = c*thea;
             x = sin(theatar)*cos(phir)*r;
             y = cos(theatar)*cos(phir)*r;
             z = sin(phir)*r;
             glVertex3d(x, y, z );
             x = sin(theatar)*cos(phir20)*r;
             y = cos(theatar)*cos(phir20)*r;
             z = sin(phir20)*r;
            glVertex3d(x, y, z );
                     }
       glEnd();

        
       
    }   glVertex3d(0.0, 0.0, 1.0);
        float c80 = c*80;
    
    
        z = sin(c80)*r;
        glColor3f(1.0,0.0,0.0);
        glBegin(GL_TRIANGLE_FAN);
        for(float thea = -180 ; thea <= 180 ; thea+=foot){
            
            float theatar = c*thea;
            x = sin(theatar)*cos(c80)*r;
            y = cos(theatar)*cos(c80)*r;
            glVertex3d(x, y, z );
            
    }   glEnd();
       
    
        glVertex3d(0.0, 0.0, -1.0);
        z = sin(-c80)*r;
        glColor3f(0.0,0.0,1.0);

        glBegin(GL_TRIANGLE_FAN);
        for(float thea = -180 ; thea <= 180 ; thea+=foot){
            
            float theatar = c*thea;
            x = sin(theatar)*cos(c80)*r;
            y = cos(theatar)*cos(c80)*r;
            glVertex3d(x, y, z );
            
        }
       
        glEnd();
    
        glFlush();
        time3 = glutGet(GLUT_ELAPSED_TIME);
        cout<<time3;
}
void processMenuEvents(int option) {
    
       //void myDisplay(void);
    //void myDisplay2(void);
    //option，就是传递过来的value的值。
    switch (option) {
        case 1 :
            
        glClear(GL_COLOR_BUFFER_BIT);
        myDisplay();
        break;
        case 3 :
        glClear(GL_COLOR_BUFFER_BIT);
        myDisplay2();
        break;
        case 2 :
            glClear(GL_COLOR_BUFFER_BIT);
            myDisplay3();
            break;
        case 4 :
            glClear(GL_COLOR_BUFFER_BIT);
            myDisplay4();
            break;
        case 5 :
            glClear(GL_COLOR_BUFFER_BIT);
            myDisplay5();
            break;
            
        case 6 :
            glClear(GL_COLOR_BUFFER_BIT);
            myDisplay6();
            break;
        case 7 :
            glClear(GL_COLOR_BUFFER_BIT);
            myDisplay7();
            break;

 
    }
}

void createGLUTMenus()
{
    void processMenuEvents(int) ;
    int menu;          // 创建菜单并告诉GLUT，processMenuEvents处理菜单事件。
    menu = glutCreateMenu(processMenuEvents);                  //给菜单增加条目
    glutAddMenuEntry("一个球（四边形带+三角形扇）",RED);
    glutAddMenuEntry("一个球（三角形）",BLUE);
    glutAddMenuEntry("小球",PINK);
    glutAddMenuEntry("步长减小（球面细腻）",YELLOW);
    glutAddMenuEntry("两个球",GREEN);
    glutAddMenuEntry("填充的球",BLACK);
    glutAddMenuEntry("四个球",WHITE);// 把菜单和鼠标右键关联起来。
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    
}



void myInit(){
    
	
	glClearColor(0.0,0.0,0.0,0.0);
    
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5.0,5.0,-5.0,5.0,-5.0,5.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    
    glRotated(45,1,0,0);
	
	   
}


int main(int argc, char ** argv)
{
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("circle");
    myInit();
    createGLUTMenus();
    glutDisplayFunc(myDisplay);
    glutMainLoop();
    
   
    return 0;
    
}
 
    

