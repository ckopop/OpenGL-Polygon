#include <GL/glut.h>
#include <math.h>

#define PI 3.14159265358979323846

float angleX = 0.0f;
float angleY = 0.0f;
int n = 6; // change this — 5=pentagon prism, 6=hexagon prism, 8=octagon prism

void drawNSidedPrism(int sides, float radius, float height) {
    float halfH = height / 2.0f;

    // Draw top face
    glBegin(GL_POLYGON);
    glColor3f(0.2f, 0.6f, 1.0f);
    for (int i = 0; i < sides; i++) {
        float theta = 2.0f * PI * i / sides;
        glVertex3f(radius * cos(theta), halfH, radius * sin(theta));
    }
    glEnd();

    // Draw bottom face
    glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.4f, 0.8f);
    for (int i = 0; i < sides; i++) {
        float theta = 2.0f * PI * i / sides;
        glVertex3f(radius * cos(theta), -halfH, radius * sin(theta));
    }
    glEnd();

    // Draw side faces
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= sides; i++) {
        float theta = 2.0f * PI * i / sides;
        float r = (float)i / sides;
        glColor3f(r, 0.5f, 1.0f - r);
        glVertex3f(radius * cos(theta), halfH, radius * sin(theta));
        glVertex3f(radius * cos(theta), -halfH, radius * sin(theta));
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Camera position
    gluLookAt(0, 1.5, 3,   // eye
        0, 0, 0,   // look at
        0, 1, 0);  // up

    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);

    drawNSidedPrism(n, 0.6f, 1.2f);

    glutSwapBuffers();
}

void update(int value) {
    angleY += 1.0f;
    if (angleY > 360) angleY -= 360;
    angleX += 0.3f;
    if (angleX > 360) angleX -= 360;
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void init() {
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("3D N-Sided Prism");

    init();
    glutDisplayFunc(display);
    glutTimerFunc(16, update, 0);
    glutMainLoop();

    return 0;
}