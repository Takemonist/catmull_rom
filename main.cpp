#include <iostream>
#include "matplotlibcpp.h"
#include "routegenerator.hpp"
#include <stdlib.h>
#include <fstream>
#include <string>
#include <stdio.h>
namespace plt = matplotlibcpp;

std::vector<double> x,y,l,v;

int main(int argc, char *argv[]) {
    double delta = atof(argv[1]);
    RouteGenerator gen;
    gen.AddPoint(0,0,0);
    gen.AddPoint(5,3,2);
    gen.AddPoint(7,7,8);
    gen.AddPoint(13,2,3);
    gen.AddPoint(20,6,0);
    gen.Generate(delta);
    int n = 4;
    Point<double> tmp;
    FILE *dat;
    dat = fopen("route.dat","w");

    for(double t = 0;t < n;t += 0.01){
        tmp = gen.getXY(t);
        x.push_back(tmp.x);
        y.push_back(tmp.y);
        std::cout << "x:" << tmp.x << " " << "y:" << tmp.y << " ";
        fprintf(dat,"x:%.5lf y:%.5lf",tmp.x,tmp.y);
        tmp = gen.getLV(t);
        l.push_back(tmp.x);
        v.push_back(tmp.y);
        std::cout<< "l:" << tmp.x << " " << "v:" << tmp.y << std::endl;
        fprintf(dat,"v:%.5lf\n",tmp.y);
    }
    fclose(dat);
    int k = 0;
    plt::plot(x,y);
    plt::plot(l,v);
    plt::scatter(gen.getx(),gen.gety(),30);
    plt::scatter(gen.getl(),gen.getv(),30);
    
    plt::show();
}