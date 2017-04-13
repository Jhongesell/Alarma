// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Direcci¢n: Amsterdam 312 col. Hipodromo Condesa
// Tel‚fono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisi¢n  1.1-A


#ifndef __EVAEXPC_HPP__
#define __EVAEXPC_HPP__


#include "\libreria\ana_exp.hpp"

class Evalua_expresion_cadena
{
   private:
   
      char                  *exp_not_pol;

   public:

                             // Puntero al analizador sintactico
      Analizador_sintactico *Ev;
                             // Indica si hay error en la evaluacion de la expresion de cadena
      int                    Error;

                     // Evalua una expresion EXP regresando el valor numerico de esta y la cadena con dicho valor en RES
      long double    Evalua_expresion(const char *exp, char *res);
};

#endif
