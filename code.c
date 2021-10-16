// Nidheesh Jain - 2019A7PS0024P
// IS-F311 Computer Graphics - Assignment #2


/*

------------CONTROLS-------------------------
S or s -> Start spinning fan blades
T or t -> Stop spinning fan blades
H or h -> Start/stop rotating fan sideways
---------------------------------------------
*****The camera always points at origin.*****
Up/Down/Right/Left Arrow Keys -> To move camera in +/-X, +/-Y respectively.
8/2 -> To move camera in Z-axis

U or u -> To move fan up on the wall
D or d -> To move fan down on the wall
R or r -> To move fan right on the wall
L or l -> To move fan left on the wall

Q or q -> Quit the Program
---------------------------------------------

*/




#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include <math.h>

GLfloat T = 0;
GLfloat cameraPose[3] = {0.45f, 0.05f, 1};
bool isBladeSpinning = false;
bool isLateralRotating = false;
GLfloat beige[4] = {0,1,0,1};
GLfloat grey[4] = {0.2f,0.2f,0.3f,1};
GLfloat fanBaseColor[4] = {0.0f,0.0f,0.0f,1};
GLfloat fanBodyColor[4] = {0.4f,0.4f,0.5f,1};
GLfloat fanBasePose[3] = {-0.9599f,0.5f,0};

GLfloat fanBladeColor[4] = {0.5294f,0.8078f,0.9215f,1};
GLfloat lateralRotAngle = 0;

bool LtoR = true;
int windowID;

GLfloat bladeAngle = 0;


float toB (int value) // Maps 0-255 to 0-1
{
    return ((value%255) / 255.00);
}


float degToRad(float deg)
{
    return (fmod(deg, 360)*0.01745329252);
}


void windowResizeHandler(int windowWidth, int windowHeight)
{
    const int aspectRatio = 1;
    glViewport(0, 0, windowHeight*aspectRatio, windowHeight);
}

void MyInit ()
{
    windowID = glutCreateWindow("Nidheesh Jain || 2019A7PS0024P || Assign#2 || OpenGL");
    glClearColor(toB(245), toB(245), toB(220), 1);
    glColor3f(toB(230), toB(230), toB(200));
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 1, 10);
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
}

void Spin()
{
    if (isLateralRotating)
    {
        GLfloat incrementor = fabs((lateralRotAngle*lateralRotAngle - 3000)/800);
        if (LtoR)
        {
            lateralRotAngle += incrementor;
            if (lateralRotAngle >= 45)
            {
                LtoR = false;
            }
        }
        else
        {
            lateralRotAngle -= incrementor;
            if (lateralRotAngle <= -45)
            {
                LtoR = true;
            }
        }
    }

    if (isBladeSpinning)
    {
        GLfloat fanSpeed = 30.0;
        bladeAngle += fanSpeed;
    }
    glutPostRedisplay();
}

void Face(
    GLfloat A[],
    GLfloat B[],
    GLfloat C[],
    GLfloat D[]
)
{
    glBegin(GL_POLYGON);
        glVertex3fv(A);
        glVertex3fv(B);
        glVertex3fv(C);
        glVertex3fv(D);
    glEnd();
}

void Triangle(
    GLfloat A[],
    GLfloat B[],
    GLfloat C[],
    GLfloat D[],
    GLfloat E[],
    GLfloat F[]
)
{
    glBegin(GL_POLYGON);
        glVertex3fv(A);
        glVertex3fv(B);
        glVertex3fv(C);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex3fv(A);
        glVertex3fv(D);
        glVertex3fv(E);
        glVertex3fv(B);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex3fv(A);
        glVertex3fv(D);
        glVertex3fv(F);
        glVertex3fv(C);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex3fv(B);
        glVertex3fv(E);
        glVertex3fv(F);
        glVertex3fv(C);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex3fv(F);
        glVertex3fv(E);
        glVertex3fv(D);
    glEnd();
}

void Cube(
    GLfloat V0[],
    GLfloat V1[],
    GLfloat V2[],
    GLfloat V3[],
    GLfloat V4[],
    GLfloat V5[],
    GLfloat V6[],
    GLfloat V7[]
)
{
    // glNormal3f(0, 0, -1.0);
    // Face(V0, V1, V2, V3); // Front

    glNormal3f(0, 0, 1.0);
    Face(V4, V5, V6, V7); // Back

    glNormal3f(0, -1.0, 0.0);
    Face(V0, V4, V5, V1); // Top

    glNormal3f(0, 1.0, 0.0);
    Face(V2, V6, V7, V3); // Bottom

    glNormal3f(1.0, 0.0, 0.0);
    Face(V0, V4, V7, V3); // Left

    glNormal3f(-1.0, 0.0, 0.0);
    Face(V2, V6, V5, V1); // Right
}

void Draw()
{
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    GLfloat lightPose[] = {0,0.0,1,1};
    GLfloat lightColorDiffuse[] = {0.8,0.8,0.8,1};
    GLfloat lightColorAmbient[] = {0.4,0.4,0.4,1};
    GLfloat lightColorSpecular[] = {0.8,0.8,0.8,1};


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glLightfv(GL_LIGHT0, GL_POSITION, lightPose);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColorDiffuse);

    glLightfv(GL_LIGHT1, GL_POSITION, lightPose);
    glLightfv(GL_LIGHT1, GL_AMBIENT, lightColorAmbient);

    glLightfv(GL_LIGHT2, GL_POSITION, lightPose);
    glLightfv(GL_LIGHT2, GL_SPECULAR, lightColorSpecular);
    GLfloat Vert[8][3] =
    {
        {-1.0, 1.0, 2.0},
        { 1.0, 1.0, 2.0},
        { 1.0,-1.0, 2.0},
        {-1.0,-1.0, 2.0},
        {-1.0, 1.0,-2.0},
        { 1.0, 1.0,-2.0},
        { 1.0,-1.0,-2.0},
        {-1.0,-1.0,-2.0}
    };
    glLoadIdentity();

    gluLookAt(cameraPose[0],cameraPose[1],cameraPose[2],0,0,0,0,1,0);
    glRotatef(T, 0, 1, 0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, beige);
    Cube
    (
        Vert[0],
        Vert[1],
        Vert[2],
        Vert[3],
        Vert[4],
        Vert[5],
        Vert[6],
        Vert[7]
    );


    glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, grey);
        glTranslatef(0.1,-0.925,-1.5);
        glutSolidTeapot(0.1);
    glPopMatrix();

    glPushMatrix();
        // Fan Base
        glTranslatef(fanBasePose[0], fanBasePose[1], fanBasePose[2]);
        glPushMatrix();
            glPushMatrix();
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, fanBaseColor);
                glScalef(0.4, 1.5, 0.5);
                glutSolidCube(0.2);
            glPopMatrix();
            glTranslatef(0.04, 0.11, 0);

            // Cylinder 1 - Joined to Base
            glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, fanBodyColor);

            gluCylinder(quadratic,0.036f,0.025f,0.1f,32,32);


            // Cylinder 2 - Joined to Lateral Rotator
            glTranslatef(0.0f, 0.0f, 0.07f);
            glRotatef(-65.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(quadratic,0.016f,0.02f,0.05f,32,32);


            // Lateral Rotator
            glTranslatef(0.0f, 0.005f, 0.08f);
            glRotatef(lateralRotAngle, 0.0f, 0.0f, 1.0f);
            glPushMatrix();
                glScalef(1.0f, 1.6f, 1.0f);
                glutSolidCube(0.08);
            glPopMatrix();

            glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(quadratic,0.008f,0.008f, 0.15f,32,32);
            glTranslatef(0.0f, 0.0f, 0.15f);

            // Rings around fan
            glutSolidTorus(0.007, 0.24, 232, 232);
            glPushMatrix();
                glRotatef(-90.0f , 0.0f, 1.0f, 0.0f );
                glScalef(0.2f, 1.0f, 1.0f);
                for (int i=0; i < 12; i++)
                {
                    glPushMatrix();
                        glRotatef(i*30.0f , 1.0f, 0.0f, 0.0f );
                        glutSolidTorus(0.007, 0.24, 232, 232);
                    glPopMatrix();
                }
            glPopMatrix();

            // Fan blades
            GLfloat triangleVert[6][3] =
            {
                { 0.0, 0.0, 0.01 },
                { 0.2, 0.0, 0.01 },
                { 0.14142135623, 0.14142135623, 0.01 },
                { 0.0, 0.0,-0.01 },
                { 0.2, 0.0,-0.01 },
                { 0.14142135623, 0.14142135623,-0.01 }
            };

            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, fanBladeColor);
            for (int i=0; i < 4; i++)
            {
                glPushMatrix();
                glRotatef( bladeAngle + (i*90.0f), 0.0f, 0.0f, 1.0f );
                Triangle(
                    triangleVert[0],
                    triangleVert[1],
                    triangleVert[2],
                    triangleVert[3],
                    triangleVert[4],
                    triangleVert[5]
                );
                glPopMatrix();
            }

        glPopMatrix();

    glPopMatrix();

    glutSwapBuffers();
}

void keyboardHandler(
    unsigned char ch,
    int x,
    int y)
{
    switch(ch)
    {
    case 's':
    case 'S':
        isBladeSpinning = true;
        break;
    case 't':
    case 'T':
        isBladeSpinning = false;
        break;
    case 'h':
    case 'H':
        isLateralRotating = !isLateralRotating;
        break;

    case 'd':
    case 'D':
        if (fanBasePose[1] > -0.845)
        {
            fanBasePose[1] -= 0.01;
        }
        else{
            printf("You have touched a boundary\n");
        }
        break;
    case 'u':
    case 'U':
        if (fanBasePose[1] < 0.619)
        {
            fanBasePose[1] += 0.01;
        }
        else{
            printf("You have touched a boundary\n");
        }
        break;
    case 'l':
    case 'L':
        if (fanBasePose[2] < 1.692)
        {
            fanBasePose[2] += 0.01;
        }
        else{
            printf("You have touched a boundary\n");
        }
        break;
    case 'r':
    case 'R':
        if (fanBasePose[2] > -1.692)
        {
            fanBasePose[2] -= 0.01;
        }
        else{
            printf("You have touched a boundary\n");
        }
        break;
    case 'q':
    case 'Q':
        glutDestroyWindow(windowID);
        exit(1);
        break;
    case '2':
        cameraPose[2] += 0.008;
        break;
    case '8':
        cameraPose[2] -= 0.008;
        break;
    }
    glutPostRedisplay();
}


void specialKeyboardHandler(
    int ch,
    int x,
    int y)
{
    switch(ch)
    {
    case GLUT_KEY_DOWN:
        cameraPose[1] -= 0.008;
        break;
    case GLUT_KEY_UP:
        cameraPose[1] += 0.008;
        break;
    case GLUT_KEY_LEFT:
        cameraPose[0] -= 0.008;
        break;
    case GLUT_KEY_RIGHT:
        cameraPose[0] += 0.008;
        break;
    }
    glutPostRedisplay();
}


int main(int C, char *V[])
{
    beige[0] = toB(230);
    beige[1] = toB(230);
    beige[2] = toB(200);
    beige[3] = 1;

    glutInit(&C, V);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    MyInit ();

    glutDisplayFunc(Draw);
    glutKeyboardFunc(keyboardHandler);
    glutSpecialFunc(specialKeyboardHandler);
    glutReshapeFunc(windowResizeHandler);
    glutIdleFunc(Spin);
    glutMainLoop();
    return 0;
}
