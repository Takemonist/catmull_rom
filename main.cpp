#include "catmullrom.h"
#include <iostream>
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;
int main(int, char**) {
    catmullrom cmr(true);
    int n;
    std::cin >> n;
    for(int i = 0;i < n;i++){
        double X,Y;
        scanf("%lf",&X);
        scanf("%lf",&Y);
        cmr.addpoint(X,Y);
    }
    std::vector<double> x,y;
    int l = 0;
    vec<double> tmp;
    plt::scatter(cmr.getx(),cmr.gety(),30);
    for(double t = 0;t < n;t += 0.01){
        tmp = cmr.getresult(t);
        x.push_back(tmp.x);
        y.push_back(tmp.y);
    }
    plt::plot(x,y);
    plt::show();
}
