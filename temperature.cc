//
// Created by u211-05 on 27.04.2017.
//
#include <iostream>
#include "temperature.h"

using namespace std;

istream& operator >> (istream& in, Temperature& t)
{
    in >> t.value;
    if (!in) {
        cout<<"\nValue error";
        in.setstate(ios_base::failbit);
        return in;
    }
    char symbol;
    in >> symbol;
    /*if ((symbol != 'K') && (symbol != 'C') && (symbol != 'F')) {

      in.setstate(ios_base::failbit);
      return in;
    }
    */
    switch (symbol) {
    case 'K' :
        t.scale = Kelvin;
        break;
    case 'C' :
        t.scale = Celsiy;
        break;
    case 'F' :
        t.scale = Farenheit;
        break;
    default:
    {
        cout<<"\nScale error";
        in.setstate(ios_base::failbit);
        return in;}
    }
    Temperature P_1 = t; P_1 = convert (P_1, Kelvin);
    if (P_1.value < 0){
        cout<<"\nValue error(<0)";
        in.setstate(ios_base::failbit);
        return in;
    }
    return in;
}


Temperature convert (const Temperature& t, Scale scale) {
    double k;
    switch (t.scale) {
    case Kelvin :
        k = t.value;
        break;
    case Celsiy :
        k = t.value + 273;
        break;
    case Farenheit :
        k = (t.value - 32) / 1.8;
        break;
    };
    Temperature result;
    result.scale = scale;
    switch (scale) {
    case Kelvin :
        result.value = k;
        break;
    case Celsiy :
        result.value = k + 273;
        break;
    case Farenheit :
        result.value = 1.8 * k + 32;
        break;
    }
    return result;
}

bool operator < (Temperature t1, Temperature t2) //истина t1<t2, ложь t1>=t2
{
    t1 = convert(t2,t1.scale);
    return t1.value < t2.value;
}

bool operator > (Temperature t1, Temperature t2) //истина t1>t2, ложь t1<=t2
{
    t1 = convert(t2,t1.scale);
    return t1.value > t2.value;
}