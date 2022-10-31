#include <iostream>
#include <vector>
using namespace std;

struct Point2D
{
    // float distance;
    int w;
    int h;
};

struct Point3D
{
    int d;
    int w;
    int h;
};



void topology_error_3D(const int * img, const unsigned char * label, int * distancemap, int depth, 
    int height, int width);    


