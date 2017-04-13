// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Direcci¢n: Amsterdam 312 col. Hipodromo Condesa
// Tel‚fono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisi¢n  1.1-A



#ifndef __V_PIXEL_HPP__
#define __V_PIXEL_HPP__

#include "definic.hpp"


// Definición del pixel
struct Definicion_pixel {
   bool pixel;
};


// Clase que manipila y controla un array de pixeles
class Arreglo_pixeles
{
   private:

      bool               Activo;        // Indica si esta activo el objeto
      unsigned int       i1,i2;         // Variables temporales
      unsigned int       Num_Y;         // Longitud de la matriz en Y
      unsigned int       Num_X;         // Longitud de la matrix en X
      Definicion_pixel **Arreglo;       // Puntero al arreglo de pixeles

      C2D                Escala;        // Escala usada dentro de la ventana de pixeles
      Dimencion_Ventana  Dimenciones;   // Dimenciones de la ventana de trabajo
      unsigned int       px, py;        // Valores temporales
 
      
   public:
                     // Constructor de la clase
                     Arreglo_pixeles(void)
                     { Activo = false; }
                     // Destructor de la clase
                    ~Arreglo_pixeles(void)
                     {Destruye();}
               void  Calcula_punto(const long double x, const long double y, unsigned int &px, unsigned int &py)
                     {
                        if ((y >= Dimenciones.Yi && y <= Dimenciones.Yf) && (y >= Dimenciones.Yi && y <= Dimenciones.Yf)) {
                           py = Num_Y - ((y - Dimenciones.Yi) * Escala.Y) -1;
                           px = ((x - Dimenciones.Xi) * Escala.X);
                        }
                     }
                     // Inicializa la clase
               void  Inicializa(const unsigned int pix_x, const unsigned int pix_y, const bool val, const Dimencion_Ventana v_dim);
                     // Asigna a un pixel del arreglo el valor indicado
               void  Asigna_valor(const unsigned int pix_x, const unsigned int pix_y, const bool val);
                     // Asigna a un pixel del arreglo el valor indicado
               void  Asigna_valor(const long double x, const long double y, const bool val)
                     {
                        Calcula_punto(x, y, px, py);   
                        Asigna_valor(px, py, val);
                     }
                     // Destruye el contenido del arreglo
               void  Destruye(void);
                     // Retorna el valor del pixel indicado dentro del arreglo
               bool  Retorna_valor(const unsigned int pix_x, const unsigned int pix_y) const;
                     // Asigna a todo el array el valor especificado
               void  Asigna_todo_array(const bool val);
               void  Asigna_linea(const unsigned int xi, const unsigned int yi, const unsigned int xf, const unsigned int yf);
               void  Asigna_linea(const long double xi, const long double yi, const long double xf, const long double yf);               
};


// Notas:
//   (1) El array empieza en cero para los pixeles Y y X
//   (2) El numero maximo de elemetos depende de la memoria de la maquina

#endif



