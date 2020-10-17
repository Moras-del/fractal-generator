#include <GL/glut.h>
#include <complex>
#include "climanager.hpp"
#include <iostream>

using namespace std;

const int WIDTH = 800;
const int HEIGHT = 800;
GLubyte* pixels = new GLubyte[WIDTH * HEIGHT * 3];

pair<float, float> getNumbers(int size, char** args);
float extractFloat(string arg);
void display();
void setPixel(int x, int y, int r, int g, int b, GLubyte* pixels);
int julia(float x, float y, float real, float imag);
inline int square(complex<float> value);
void resize(int width, int height);

pair<float, float> getNumbers(int size, char** args)
{
    pair<float, float> numbers;
    for(int i = 0; i < size; i++)
    {
        string arg = args[i];
        if(arg.rfind("-r", 0)==0 || arg.rfind("--real", 0) == 0)
        {
            numbers.first = extractFloat(arg);
        }
        if(arg.rfind("-i", 0)==0 || arg.rfind("--imaginary", 0)==0)
        {
            numbers.second = extractFloat(arg);
        }
    }
    return numbers;
}

float extractFloat(string arg)
{
    int index = arg.find("=")+1;
    string number = arg.substr(index, arg.size());
    return stof(number);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawPixels(WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    glutSwapBuffers(); 
}

void setPixel(int x, int y, int r, int g, int b, GLubyte* pixels)
{
    int position = (x + y * WIDTH) * 3;
    pixels[position] = r;
    pixels[position + 1] = g;
    pixels[position + 2] = b;
}

int julia(float x, float y, float real, float imag)
{
    complex<float> c(real, imag);
    complex<float> z(1.5*(x - WIDTH/2)/(0.40*WIDTH), 1.0*(y - HEIGHT/2)/(0.40*HEIGHT));
    unsigned short iters = 0;
    while (square(z) < 4 && iters < 34) {
           z = z * z + c;
           iters++;
    }
    return iters < 34 ? 255*iters/34 : 0;
}

inline int square(complex<float> value)
{
    return value.real()*value.real()+value.imag()*value.imag();
}

int main(int argc, char** argv)
{    
    CliManager manager(argc, argv);
    float real, imag;
    if(!manager.getFloat(real, "--real", "-r")){
        cout << "please specify --real (-r) number" << endl;
        return -1;
    }
    if(!manager.getFloat(imag, "--imaginary", "-i")){
        cout << "please specify --imaginary (-i) number" << endl;
        return -1;
    }
    for(int x = 0; x < WIDTH; x++)
    {
        for(int y = 0; y < HEIGHT; y++)
        {
            setPixel(x, y, 0, 0, julia(x, y, real, imag), pixels);
        }
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(100, 100); 
    glutCreateWindow("fractal-generator");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}