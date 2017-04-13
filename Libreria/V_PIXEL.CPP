// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Direcci¢n: Amsterdam 312 col. Hipodromo Condesa
// Tel‚fono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisi¢n  1.1-A

#include "\libreria\v_pixel.hpp"

// Inicializa el arreglo de pixeles con el valor VAL
void Arreglo_pixeles::Inicializa(const unsigned int pix_x, const unsigned int pix_y, const bool val, const Dimencion_Ventana v_dim)
{
   if (Activo) return;
   // Declara el arreglo para los renglones
   Arreglo = new Definicion_pixel *[pix_y];
   // Declara el arreglo para las columnas dentro de cada renglon
   for (i1 = 0; i1 < pix_y; i1++) Arreglo[i1] = new Definicion_pixel [pix_x];
   Num_X = pix_x, Num_Y = pix_y;
   Activo = true;
   Asigna_todo_array(val);
   // Dimenciones de la ventana de trabajo
   Dimenciones = v_dim;
   // Escala para trabajar en la ventana de pixeles
   Escala.X = (Num_X -1) / (Dimenciones.Xf - Dimenciones.Xi);
   Escala.Y = (Num_Y -1) / (Dimenciones.Yf - Dimenciones.Yi);
}


// Asigna el valor al pixel (X,Y) el valor VAL
void Arreglo_pixeles::Asigna_valor(const unsigned int pix_x, const unsigned int pix_y, const bool val)
{
   if (Activo && pix_x < Num_X && pix_y < Num_Y) Arreglo[pix_y][pix_x].pixel = val;
}


// Destruye el contenido del arreglo
void Arreglo_pixeles::Destruye(void)
{
   if (!Activo) return;
   // Destruye el arreglo 
   for (i1 = 0; i1 < Num_Y; i1++) delete []Arreglo[i1];
   delete []Arreglo;
   Activo = false;
}


// Asigna a todo el array el valor especificado
void Arreglo_pixeles::Asigna_todo_array(const bool val)
{
   if (!Activo) return;
   for (i1 = 0; i1 <  Num_Y; i1++) {
      for (i2 = 0; i2 <  Num_X; i2++) Arreglo[i1][i2].pixel = val;
   }
}

// Retorna el valor del pixel indicado dentro del arreglo
bool Arreglo_pixeles::Retorna_valor(const unsigned int pix_x, const unsigned int pix_y) const
{
   if (!Activo) return false;
   if (pix_x < Num_X && pix_y < Num_Y) return (Arreglo[pix_y][pix_x].pixel);
   return false;
}


void Arreglo_pixeles::Asigna_linea(const unsigned int xi, const unsigned int yi, const unsigned int xf, const unsigned int yf)
{
     int min_x, max_x, min_y, max_y, xxi,xyi,xxf,xyf,py;
     xxi = xi, xxf = xf, xyi = yi, xyf = yf;
     min_x = xxi < xxf ? xxi: xxf;
     max_x = xxf > xxi ? xxf: xxi;
     min_y = xyi < xyf ? xyi: xyf;
     max_y = xyf > xyi ? xyf: xyi;
     long double m;
     unsigned int i;
     // Linea vertical
     if (xxi == xxf) {
        for (i = min_y; i <= max_y; i++) Asigna_valor(xi, i, true);
     }
     // Linea horizontal
     if (xyi == xyf) {
        for (i = min_x; i <= max_x; i++) Asigna_valor(i, yi, true);
     }
     // Linea en general
     if (xxi != xxf && xyi != xyf) {
        m = (xyf - xyi) / (xxf - xxi);
        for (i = min_x; i <= max_x; i++) {
            py = m * (i - xxf) + xyf;
            Asigna_valor(i, py, true);
        }
     }
}


void Arreglo_pixeles::Asigna_linea(const long double xi, const long double yi, const long double xf, const long double yf)
{
   unsigned int p1,p2,p3,p4;
   Calcula_punto(xi, yi, p1, p2);
   Calcula_punto(xf, yf, p3, p4);
   Asigna_linea(p1, p2, p3, p4);
}


