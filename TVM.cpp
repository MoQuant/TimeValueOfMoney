#include <stdio.h>
#include <math.h>
#include <iostream>

void Problem48(){
    /*
        Topper plans to make semi-annual savings contributions of 
        $3,700.  His first semi-annual savings contribution is 
        expected later today.  Topper expects to earn 7.30 percent 
        per year.  How many semi-annual savings contributions of 
        $3,700 does Topper need to make in order to have $410,000?

        Answer: 44.34

    */
    
    double cf = 3700;
    double r = 0.0730;
    double fv = 410000;

    r /= 2.0;

    /*
        fv = (cf/r)*((1 + r)^t - 1)*(1 + r)
        ((fv*r)/cf)/(1+r) = (1 + r)^t - 1
        U + 1 = (1 + r)^t
        ln(U + 1) = t*ln(1 + r)
        ln(U + 1)/ln(1 + r) = t
    */

    double t = log(((fv*r)/cf)/(1+r) + 1)/log(1 + r);

    std::cout << "Answer: " << t << std::endl;

}

void Problem37(){
    /*
        Dat is planning to save $47.11 every month for 4 years.  
        He plans to make his first savings contribution in 1 month 
        from today.  If he currently has $920 saved and expects to 
        have $3,975.17 in 4 years from today, then what is the EAR 
        that he expects to earn?

        Answer: 8.86%
 
    */

    double cf = 47.11;
    double t = 4;
    t *= 12;
    double pv = 920;
    double fv = 3975.17;

    /*
        fv = (cf/r)*((1 + r)^t - 1) + pv(1 + r)^t
        AB' + BA' + dt[pv*(1 + r)^t]
        A = (cf/r)
        B = (1 + r)^t - 1
        A' = cf*r^-1 -> -1cfr^-2 -> -cf/r^2
        B' = t(1 + r)^t-1

        dF = (cf/r)*t*(1 + r)^t-1 + [(1 + r)^t - 1]-cf/r^2 + t*pv(1 + r)^t-1
    */

    auto futureValue = [](double cf, double r, int t, double pv)
    {
        return (cf/r)*(pow(1 + r, t) - 1) + pv*pow(1 + r, t);
    };

    auto deltaValue = [](double cf, double r, double t, double pv)
    {
        double A = cf/r;
        double A1 = -cf/pow(r, 2);
        double B = pow(1 + r, t) - 1;
        double B1 = t*pow(1 + r, t-1);
        return A*B1 + B*A1 + t*pv*pow(1 + r, t - 1);
    };

    double ri = 0.01, rj = 0.45;
    while(true){
        rj = ri - (futureValue(cf, ri, t, pv) - fv)/deltaValue(cf, ri, t, pv);
        if(abs(rj - ri) < 0.00001){
            break;
        }
        ri = rj;
    }
        
    double ear = pow(1 + rj, 12) - 1;

    std::cout << "Answer: " << ear << std::endl;

}

void Problem29(){
    /*
        Nadia wants to establish a charitable foundation 
        that will make annual scholarship payments of $50,700 
        per year forever.  Nadia wants the foundation to make 
        the first annual $50,700 scholarship payment in 10 
        years from today and she wants annual scholarship 
        payments of $50,700 to continue forever.  
        To fund the foundation, Nadia plans to make equal 
        annual donations to the foundation for 9 years.  
        How much does Nadia need to donate to the foundation 
        each year for 9 years to have exactly enough in the 
        foundation if she makes her first donation to the 
        foundation in one year from today, all donations to 
        the foundation are equal, and funds held by the 
        foundation are expected to earn 12.60 percent?

        Answer: 26,549
    */

    double cash = 50700;
    double rate = 12.60/100;
    double t = 9;

    double fv = cash/rate;

    /*
        fv = (cf/r)*((1 + r)^t - 1)
        fv*r = cf*((1 + r)^t - 1)
        (fv*r)/((1 + r)^t - 1) = cf
    */
    
    double cf = (fv*rate)/(pow(1 + rate, t) - 1);

    std::cout << "Answer: " << cf << std::endl;

}

void Problem19(){
    /*
        Tim wants to have $164,000 in 7 years from 
        today.  He expects to earn a return of 5.0 
        percent per year.  Tim plans to make regular
        savings contributions of X per year for 7 
        years, with the first of these regular 
        savings contributions made later today.  
        In addition, Tim expects to make a special 
        savings contribution of $42,000 in 2 years 
        from today.  What is X, the amount of Tim’s 
        regular savings contribution?

        Answer: 12,913
    */

    double fv = 164000;
    double t = 7;
    double r = 0.05;
    double special = 42000;
    double ts = 2;

    fv = fv - special*pow(1 + r, t - ts);
    
    /*
        fv = (cf/r)*((1 + r)^t - 1)*(1 + r)
        (fv*r)/(1 + r) = cf[(1 + r)^t - 1]
        [(fv*r)/(1 + r)]/[(1 + r)^t - 1] = cf

    */

    double cf = ((fv*r)/(1+r))/(pow(1 + r, t) - 1);

    std::cout << "Answer: " << cf << std::endl;

}

void Problem13(){
    /*
        Kory plans to save $75,000 per year for 5 
        years.  His first savings contribution is 
        expected later today.  He then plans to 
        make withdrawals for 8 years.  How much 
        can Kory expect to withdraw each year if 
        he expects to earn 13.30 percent per year, 
        he makes equal annual withdrawals, and 
        his first withdrawal is in 6 years?

        Answer: 116,624
    */

    double cf = 75000;
    double t = 5;
    double wt = 8;
    double r = 0.1330;

    double fv = (cf/r)*(pow(1 + r, t) - 1)*(1 + r);
    double withdraw = (fv*r)/(1 - pow(1 + r, -wt));

    std::cout << "Answer: " << withdraw << std::endl;

}

void Problem7(){
    /*
        Mathias plans to save $22,000 per year for 
        5 years.  His first savings contribution is 
        expected later today.  He then plans to 
        withdraw $37,000 per year for as long as he 
        can.  Mathias expects to earn 7.5 percent 
        per year.  How many payments of $37,000 
        can Mathias expect to receive if his first 
        annual payment of $37,000 is received in 
        5 years? 

        Answer: 4.15

    */

    double savings = 22000;
    double ts = 5;
    double withdraw = 37000;
    double r = 0.075;

    double fv = (savings/r)*(pow(1 + r, ts) - 1)*(1 + r);
    
    /*
        pv = cf + (cf/r)*(1 - (1 + r)^-t)
        (pv - cf)*r/cf = 1 - (1 + r)^-t
        1 - (pv - cf)*r/cf = (1 + r)^-t
        ln(U) = -tln(1 + r)
        -ln(U)/ln(1 + r) = t
    */

    double t = -log(1 - (fv - withdraw)*r/withdraw)/log(1 + r);

    std::cout << "Answer: " << t << std::endl;

}


int main()
{
    Problem7();
    return 0;
}