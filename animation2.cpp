#include <GL/glut.h>
#include <math.h>

int frameNumber = 0;

void drawWindmill() {
    int i;

    // Draw windmill pole
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(-0.05f, 0.0f);
    glVertex2f(-0.05f, 3.0f);
    glVertex2f(0.05f, 3.0f);
    glVertex2f(0.05f, 0.0f);
    glEnd();

    // Move origin to the top of the pole
    glTranslatef(0.0f, 3.0f, 0.0f);

    // Rotate blades
    glColor3f(0.0, 0.0, 1.0);
    glRotatef(frameNumber * (180.0 / 45), 0, 0, 1);

    // Draw 4 blades
    for (i = 0; i < 4; i++) {
        glRotatef(90, 0, 0, 1);
        glBegin(GL_POLYGON);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(1.0f, 0.2f);
        glVertex2f(1.0f, -0.2f);
        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glTranslatef(3.7f, 0.8f, 0.0f);
    glScalef(0.7f, 0.7f, 1.0f);
    drawWindmill();
    glPopMatrix();
    glutSwapBuffers();
}

void doFrame(int v) {
    frameNumber++;
    glutPostRedisplay();
    glutTimerFunc(10, doFrame, 0);
}

void init() {
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 7, 0, 4, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Animation Assignment");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(10, doFrame, 0);
    glutMainLoop();
    return 0;
}
