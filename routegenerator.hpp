#ifndef IG_ROUTEGENERATOR_HPP_
#define IG_ROUTEGENERATOR_HPP_

#include "catmullrom.hpp"

using cmr = catmullrom;
class RouteGenerator{
private:
    cmr xy;
    cmr lv;
    std::vector<double> x;
    std::vector<double> y;
    std::vector<double> v;
    std::vector<double> l;
    int points = 0;
public:
    RouteGenerator() : xy(false),lv(false){
        
    };
    void AddPoint(double x,double y,double v){
        xy.addpoint(x,y);
        this->x.resize(++points);
        this->y.resize(points);
        this->v.resize(points);
        this->l.resize(points);
        this->x[points-1] = x;
        this->y[points-1] = y;
        this->v[points-1] = v;
    }
    void Generate(double delta){
        l[0] = 0;
        double l = 0;
        for(int i = 0;i < points;i++){
            for(double t = 0;t < 1.0;t += delta){
                Point<double> temp;
                double dl;
                temp = xy.getdfdt(i+t);
                dl = sqrt( (temp.x)*(temp.x) + (temp.y)*(temp.y) );
                l += dl*delta;
                //printf("%lf\n",t);
            }
            this->l[i+1] = l;
            lv.addpoint(this->l[i],this->v[i]);
            printf("x:%lf,y:%lf,l:%lf,v:%lf\n",x[i],y[i],this->l[i],v[i]);
        }
    }
    Point<double> getLV(double t){
        Point<double> ret;
        ret = lv.getft(t);
        return ret;
    }
    Point<double> getXY(double t){
        Point<double> ret;
        ret = xy.getft(t);
        return ret;
    }
    std::vector<double> getx(){return x;}
    std::vector<double> gety(){return y;}
    std::vector<double> getl(){return l;}
    std::vector<double> getv(){return v;}
};

#endif /* IG_ROUTEGENERATOR_HPP_ */