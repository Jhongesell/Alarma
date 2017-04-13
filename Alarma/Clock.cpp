// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Dirección: Amsterdam 312 col. Hipodromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A

//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("Clock.res");
USEFORM("princip.cpp", AlarmaForm);
USEUNIT("..\libreria\Tiempo.cpp");
USEUNIT("..\libreria\Cadenas.cpp");
USEUNIT("..\libreria\Man_arch.cpp");
USEUNIT("..\libreria\FORMAS\Acercade.cpp");
USEUNIT("..\libreria\FORMAS\TASCII.cpp");
USEUNIT("..\libreria\FORMAS\Calend.cpp");
USEUNIT("..\libreria\Fechas.cpp");
USEUNIT("..\libreria\FORMAS\Calculad.cpp");
USEUNIT("..\libreria\Evaexpc.cpp");
USEUNIT("..\libreria\Calnpol.cpp");
USEUNIT("..\libreria\Ana_exp.cpp");
USEUNIT("..\libreria\Pila.cpp");
USEUNIT("..\libreria\formas\Cronomet.cpp");
USEUNIT("..\libreria\formas\Ayuda.cpp");
USEUNIT("..\Libreria\formas\Editor.cpp");
USEFORM("..\libreria\formas\Alarma\AlarmVis.cpp", AlarmaVis);
USEUNIT("..\libreria\formas\Alarma\AlarmCap.cpp");
USEUNIT("..\libreria\formas\Lmensaje.cpp");
USEUNIT("..\Libreria\formas\ALARMA\aviso.cpp");
USEUNIT("..\Libreria\formas\director\Director.cpp");
USEUNIT("..\Libreria\formas\director\Vdirect.cpp");
USEUNIT("..\Libreria\formas\Pendient\Vpendien.cpp");
USEUNIT("..\Libreria\formas\Pendient\Cpendien.cpp");
USEUNIT("..\libreria\formas\CPasword.cpp");
USEUNIT("..\Libreria\formas\CNPaswor.cpp");
USEUNIT("..\libreria\formas\ArbMemo\ArbMemo.cpp");
USEUNIT("..\libreria\formas\FCap1.cpp");
USEUNIT("..\libreria\Nucleo.cpp");
USEFORM("Config.cpp", ConfigurarForm);
USEUNIT("..\Libreria\formas\Notas.cpp");
USEUNIT("..\Libreria\ClavSeg.cpp");
USEUNIT("..\Libreria\formas\2D\Vgrafica.cpp");
USEUNIT("..\Libreria\formas\2D\Graf2d.cpp");
USEUNIT("..\Libreria\formas\2D\CDim2D.cpp");
USEUNIT("..\Libreria\fechora.cpp");
USEUNIT("..\Libreria\formas\agenda\Agenda.cpp");
USEUNIT("..\Libreria\formas\agenda\Cagenda.cpp");
USEUNIT("..\Libreria\formas\agenda\RepAgen.cpp");
USEUNIT("..\Libreria\formas\Pendient\RepPend.cpp");
USEUNIT("..\Libreria\ctrl_l_a.cpp");
USEUNIT("..\Libreria\formas\director\RepDir.cpp");
USEUNIT("..\Libreria\formas\Diario\VDiario.cpp");
USEUNIT("..\Libreria\Reconoc.cpp");
USEUNIT("..\Libreria\formas\cclavseg.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->Title = "Alarma 1.0a";
        Application->CreateForm(__classid(TAlarmaForm), &AlarmaForm);
                 Application->CreateForm(__classid(TAlarmaVis), &AlarmaVis);
                 Application->CreateForm(__classid(TConfigurarForm), &ConfigurarForm);
                 Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
