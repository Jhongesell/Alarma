// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Dirección: Amsterdam 312 col. Hipodromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#ifndef VGraficaH
#define VGraficaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include "d:\libreria\definic.hpp"

//---------------------------------------------------------------------------
class TVVisualizacion : public TForm
{
__published:	// IDE-managed Components
        TStatusBar *StatusBar;
        TMainMenu *MainMenu1;
        TMenuItem *archivo1;
        TMenuItem *Imprimir1;
        TMenuItem *N1;
        TMenuItem *Salir1;
        TMenuItem *Grabar;
        TMenuItem *Leer;
        TPaintBox *Visualizacion;
        TMenuItem *Ventana1;
        TMenuItem *Limpiar1;
        TMenuItem *Ayuda1;
        TMenuItem *Acercade1;
        void __fastcall Salir1Click(TObject *Sender);
        void __fastcall VisualizacionMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall VisualizacionMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall VisualizacionMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall GrabarClick(TObject *Sender);
        void __fastcall LeerClick(TObject *Sender);
        void __fastcall Imprimir1Click(TObject *Sender);
        
        
        void __fastcall Limpiar1Click(TObject *Sender);
        void __fastcall Acercade1Click(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        
        void __fastcall FormPaint(TObject *Sender);
private:	// User declarations

                        // Variables necesarias para dibujar recuadro de selecccion de una area 
    Definicion_Ventana  Vt1, Vt2, xVt;
    Dimencion_Ventana   Vs;
    bool                Ventana_seleccionada;
    bool                Sw_Dibuja_rectangulo;
    bool                Sw_Dibuja_rectangulo_ant;
    bool                Sw_Recuadro_activo;
    char                xcad[300];


                        // Dimenciones de la ventana (dimenciones reales)
    Dimencion_Ventana   Vtn;
                        // Valor de la escala
    C3D                 Escala;
                        // Valores temporales
    int                 x,y;


    void Calcula_escala(void);
    
    
public:		// User declarations
                        // Variable que indica cuando es requerido revisualizar
    bool                Revisualizar;
                        // Color de la ventana
    TColor              Color_ventana;
    TColor              Color_grafico;

    
    __fastcall          TVVisualizacion(TComponent* Owner);

    
         // Configura la ventana de graficacion
    void Configura(const Dimencion_Ventana vtn);
         // Dibuja un punto sobre la ventana grafica
    void Dibuja_punto(C3D pto);
         // Limpia la ventana de graficacion
    void Limpiar_vantana(void);
         // Muestra un mensaje dentro de la barra de estado
    void Muestra_mensaje(const char *msg);
};
#endif
