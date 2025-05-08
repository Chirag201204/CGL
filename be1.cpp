#include <GL/glut.h>

float ctrlPoints[4][2];
int pointCount = 0;

void bezierCurve() {
    glColor3f(1, 1, 1);
    glBegin(GL_LINE_STRIP);
    for (float t = 0; t <= 1.0; t += 0.01) {
        float x = (1 - t)*(1 - t)*(1 - t)*ctrlPoints[0][0]
                + 3*t*(1 - t)*(1 - t)*ctrlPoints[1][0]
                + 3*t*t*(1 - t)*ctrlPoints[2][0]
                + t*t*t*ctrlPoints[3][0];
        float y = (1 - t)*(1 - t)*(1 - t)*ctrlPoints[0][1]
                + 3*t*(1 - t)*(1 - t)*ctrlPoints[1][1]
                + 3*t*t*(1 - t)*ctrlPoints[2][1]
                + t*t*t*ctrlPoints[3][1];
        glVertex2f(x, y);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(5);
    glBegin(GL_POINTS);
    for (int i = 0; i < pointCount; i++)
        glVertex2f(ctrlPoints[i][0], ctrlPoints[i][1]);
    glEnd();

    if (pointCount == 4) {
        glColor3f(0, 1, 0);
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i < 4; i++)
            glVertex2f(ctrlPoints[i][0], ctrlPoints[i][1]);
        glEnd();
        bezierCurve();
    }
    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && pointCount < 4) {
        ctrlPoints[pointCount][0] = (x / 300.0f) - 1.0f;
        ctrlPoints[pointCount][1] = 1.0f - (y / 300.0f);
        pointCount++;
        glutPostRedisplay();
    }
}

void init() {
    glClearColor(0, 0, 0, 1);
    gluOrtho2D(-1, 1, -1, 1);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Bezier Curve");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}