#include <iostream>
#include "matplotlibcpp.h"
#include "routegenerator.hpp"
namespace plt = matplotlibcpp;

std::vector<double> x,y,l,v;

int main(int, char**) {
    RouteGenerator gen;
    gen.AddPoint(0,0,0);
    gen.AddPoint(6,5,3);
    gen.AddPoint(14,2,8);
    gen.AddPoint(16,9,2);
    gen.AddPoint(25,0,0);
    gen.Generate(0.001);
    int n = 4;
    Point<double> tmp;
    for(double t = 0;t < n;t += 0.01){
        tmp = gen.getXY(t);
        x.push_back(tmp.x);
        y.push_back(tmp.y);
    }
    for(double t = 0;t < n;t += 0.01){
        tmp = gen.getLV(t);
        l.push_back(tmp.x);
        v.push_back(tmp.y);
    }
    int k = 0;
    plt::plot(x,y);
    plt::plot(l,v);
    plt::scatter(gen.getx(),gen.gety(),30);
    plt::scatter(gen.getl(),gen.getv(),30);
    
    plt::show();
}