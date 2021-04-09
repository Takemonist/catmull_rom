/*
    catmullrom曲線
    使い方
    catmullrom ctmr(true); trueだと始点と終点を滑らかにつなぐことができる
    ctmr.addpoint(vec);
    or
    ctmr.addpoint(x,y); 点の追加(後ろにどんどん)
    ctmr.getx(),ctmr.gety(); 点の座標の配列(std::vector<double>)
    ctmr.getresult(time); その時間の座標をx,yの組で返す
    ctmr.calc() 仮装

    いつかやること
    演算子いじってもう少し式を見やすくする
*/

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

    vec<double> operator*(double scaler, vec<double> v){
        return v*scaler;
    }

class catmullrom{
private:
    std::vector< vec<double> > v;
    std::vector< vec<double> > p;
    std::vector<double> p_x;
    std::vector<double> p_y;
    bool closed = false;
    int size = 0;
    
    void calcv(){
        vec<double> temp;
        if(closed){
            temp = (p[1]-p[size-1])/2;
            v.at(0) = temp;
            for(int i = 1;i < size-1;i++){
                temp = (p[i+1]-p[i-1])/2;
                v.at(i) = temp;
            }
            temp = (p[0]-p[size-2])/2;
            v.at(size-1) = temp;
            temp = (p[1]-p[size-1])/2;
            v.at(size) = temp;
        }
        else{
            temp = (p[1]-p[0])*2-(p[2]-p[0])/2;
            v.push_back(temp);
            for(int i = 1;i < size-1;i++){
                temp = (p[i+1]-p[i-1])/2;
                v.push_back(temp);
            }
            temp = (p[size-1]-p[size-2])*2-(p[size-1]-p[size-2])/2;
            v.push_back(temp);
        }
    }
public:
    catmullrom(bool closed){this->closed = closed;};
    void addpoint(vec<double> p){
        this->p.push_back(p);
        p_x.push_back(p.x);
        p_y.push_back(p.y);
        size++;
        v.resize(size);
        calcv();
    };
    void addpoint(double x,double y){
        vec<double> p(x,y);
        this->p.push_back(p);
        p_x.push_back(x);
        p_y.push_back(y);
        size++;
        v.resize(size);
        calcv();
    };
    vec<double> getresult(double time){
        int n = size-1;
        int i = (int)time;
        double t = time - i;
        vec<double> ret;
        if(i == n){
            ret = (p[i]*2-p[0]*2+v[i]+v[0])*t*t*t
                + (p[0]*3-p[i]*3-v[i]*2-v[0])*t
                + v[i]*t
                + p[i];
        }
        else{
            ret = (p[i]*2-p[i+1]*2+v[i]+v[i+1])*t*t*t
                + (p[i+1]*3-p[i]*3-v[i]*2-v[i+1])*t*t
                + v[i]*t
                + p[i];
        }
        return ret;
    }
    std::vector<double> getx(){
        return p_x;
    }
    std::vector<double> gety(){
        return p_y;
    }
    std::vector< vec<double> > getvelocity(){
        return v;
    }
};

#endif /* IG_CATMULLROM_H_ */

/*
if(closed){
            ret = (p[i]*2-p[i+1]*2+v[i]+v[1])*t*t*t
                + (p[i+1]*3-p[i]*3-v[i]*2-v[i+1])*t*t
                + v[i]*t
                + p[i];
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
        */