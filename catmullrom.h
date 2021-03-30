#ifndef IG_CATMULLROM_H_
#define IG_CATMULLROM_H_

#include <vector>
#include <iostream>

template<class T>
class vec{
private:
public:
    vec(T x,T y):x(x),y(y){};
    vec(){};
    T x;
    T y;
    vec operator+(vec v){
        vec ret;

        ret.x = this->x + v.x;
        ret.y = this->y + v.y;

        return ret;
    }
    vec operator-(vec v){
        vec ret;

        ret.x = this->x - v.x;
        ret.y = this->y - v.y;

        return ret;
    }
    vec operator+(T scalar){
        vec ret;

        ret.x = this->x + scalar;
        ret.y = this->y + scalar;

        return ret;
    }
    vec operator-(T scalar){
        vec ret;

        ret.x = this->x - scalar;
        ret.y = this->y - scalar;

        return ret;
    }
    vec operator*(T scalar){
        vec ret;

        ret.x = this->x * scalar;
        ret.y = this->y * scalar;

        return ret;
    }
    vec operator/(T scalar){
        vec ret;

        ret.x = this->x / scalar;
        ret.y = this->y / scalar;

        return ret;
    }
    template<class X, class Y>
    vec operator()(const X& x, const Y& y){ 
        this->x = x;
        this->y = y;
        return *this;
    }
};

class catmullrom{
private:
    std::vector< vec<double> > v;
    std::vector< vec<double> > p;
    std::vector<double> p_x;
    std::vector<double> p_y;
    bool closed = false;
    int size = 0;
public:
    catmullrom(bool closed){this->closed = closed;};
    void addpoint(vec<double> p){
        this->p.push_back(p);
        p_x.push_back(p.x);
        p_y.push_back(p.y);
        size++;
    };
    void addpoint(double x,double y){
        vec<double> p(x,y);
        this->p.push_back(p);
        p_x.push_back(x);
        p_y.push_back(y);
        size++;
    };
    void calc(){
        vec<double> temp;
        for(int i = 1;i < p.size()-1;i++){
            temp = (p[i+1]-p[i-1])/2;
            v.at(i) = temp;
        }
    }
    vec<double> getresult(double time){
        int n = size-2;
        int i = (int)time;
        double t = time - i;
        vec<double> ret;
        if(closed){
            if(i == 0){
                ret = ((p[i]*3-p[i+1]*3+p[i+2]-p[n+1])*t*t*t
                    + (p[n+1]*2-p[i]*5+p[i+1]*4-p[i+2])*t*t
                    + (p[i+1]-p[n+1])*t ) / 2 + p[i];
            }
            else if(i == n+1){
                ret = ((p[i]*3-p[0]*3+p[1]-p[i-1])*t*t*t
                    + (p[i-1]*2-p[i]*5+p[0]*4-p[1])*t*t
                    + (p[0]-p[i-1])*t ) / 2 + p[i];
            }
            else{
                ret = ((p[i]*3-p[i+1]*3+p[i+2]-p[i-1])*t*t*t
                    + (p[i-1]*2-p[i]*5+p[i+1]*4-p[i+2])*t*t
                    + (p[i+1]-p[i-1])*t ) / 2 + p[i];
            }
        }
        else{
        if(i == 0){
            ret = ( (p[i]-p[i+1]*2+p[i+2])*t*t 
            + (p[i+1]*4-p[i+2]-p[i]*3)*t + p[i]*2) / 2;
        }
        else if(i == n){
            ret = ( (p[n-1]-p[n]*2+p[n+1])*t*t + (p[n+1]-p[n-1])*t + p[n]*2 )/2;
        }
        else{
            ret = ((p[i]*3-p[i+1]*3+p[i+2]-p[i-1])*t*t*t
                 + (p[i-1]*2-p[i]*5+p[i+1]*4-p[i+2])*t*t
                 + (p[i+1]-p[i-1])*t ) / 2 + p[i];
        }
        }
        return ret;
    }
    std::vector<double> getx(){
        return p_x;
    }
    std::vector<double> gety(){
        return p_y;
    }
};

#endif /* IG_CATMULLROM_H_ */