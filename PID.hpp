#ifndef IG_PID_HPP_
#define IG_PID_HPP_

class PID{
public:
    PID(double KP,double KI,double KD,double DT):Kp(KP),Ki(KI),Kd(KD),dt(DT){

    }
    void Update(double e){
        PROP = e;
        INT += (curr_e + prev_e)*dt/2.0;
        DIFF = (curr_e - prev_e)/dt;
        mv = Kp*PROP + Ki*INT + Kd*DIFF;
    }
    double getmv(){
        return mv;
    }
private:
    double Kp,Ki,Kd; /* Pゲイン Iゲイン Dゲイン */
    double dt; /* 微小時間 */
    double prev_e,curr_e; /* 前回の誤差 現在の誤差 */
    double PROP,INT,DIFF; /* 比例　積分　微分 */
    double mv; /* manipulating variable */
};

#endif /* IG_PID_HPP_ */