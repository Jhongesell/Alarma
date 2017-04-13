// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Direcci¢n: Amsterdam 312 col. Hipodromo Condesa
// Tel‚fono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisi¢n  1.1-A


#ifndef __DEFINIC_HPP__
#define __DEFINIC_HPP__

struct Dimencion_Ventana {
    long double Xi;
    long double Yi;
    long double Xf;
    long double Yf;
};

struct Definicion_Ventana {
    int Xi;
    int Yi;
    int Xf;
    int Yf;
};


struct C2D {
    long double X;
    long double Y;
};

struct C3D {
    long double X;
    long double Y;
    long double Z;


};

#endif
