#ifndef CEPHES_H
#define CEPHES_H

class Cephes {
public:
    static double cephes_igamc(double a, double x);
    static double cephes_igam(double a, double x);
    static double cephes_lgam(double x);
    static double cephes_p1evl(double x, double *coef, int N);
    static double cephes_polevl(double x, double *coef, int N);
    static double cephes_erf(double x);
    static double cephes_erfc(double x);
    static double cephes_normal(double x);
};

#endif /*  _CEPHES_H_  */
