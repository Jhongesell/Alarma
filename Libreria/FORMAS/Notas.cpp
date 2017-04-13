// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Dirección: Amsterdam 312 col. Hipodromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A



#include <vcl.h>
#include <Clipbrd.hpp>
#include <fstream.h>
#include <stdio.h>
#include <dir.h>
#include <io.h>
#include "d:\Libreria\fechora.hpp"
#include "d:\libreria\man_arch.hpp"
#include "d:\Libreria\Formas\AcercaDe.h"
#include "d:\libreria\formas\Notas.h"
#include "d:\Libreria\ctrl_l_a.hpp"
#include "d:\libreria\nucleo.hpp"
#include "d:\libreria\formas\CClavSeg.h"
#include "d:\libreria\ClavSeg.hpp"
#pragma hdrstop


// Objeto global
extern Nucleo NCO;
extern char *TRAYECTORIA_ARCHIVOS;
static Ctrl_lista_archivos cla;


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

__fastcall TNotasForm::TNotasForm(TComponent* Owner) : TForm(Owner)
{
}

// Al crear la forma ...
void __fastcall TNotasForm::FormCreate(TObject *Sender)
{
   char arch[MAXPATH];
   Manipulador_archivos ma;
   
   ma.Construye_trayectoria(TRAYECTORIA_ARCHIVOS,"NOTAS.CFG", arch);
   cla.Inicializa_lista_archivos(arch);
   Actualiza_lista();

   SaveDialog->FileName = "";
   Editor->SelStart = 0;
   strcpy(Encriptado,"N");
   strcpy(Password,"ESTE ES UN PASWORD MUY LARGO");
}


// Al cerrar la forma ...
void __fastcall TNotasForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
   CanClose = false;   
   if (Editor->Modified) {
      if (MessageBox(Handle,"¿Desea terminar la actual edición?","Notas",MB_YESNO + MB_ICONQUESTION)  == IDYES) {
         if (MessageBox(Handle,"El archivo actual ha sido cambiado, ¿se graba?","Notas",MB_YESNO + MB_ICONQUESTION) == IDYES) Grabar1Click(Sender);
      } else return;
   }
   Application->OnIdle = NULL;
   NCO.Activa_Borrado(PtrNotas);   
   CanClose = true;
}


// Al activar la forma
void __fastcall TNotasForm::FormActivate(TObject *Sender)
{
   Application->OnIdle = OnIdle;
}

// Al desactivar la forma
void __fastcall TNotasForm::FormDeactivate(TObject *Sender)
{
   Application->OnIdle = NULL;
}

// OnIdle
void  __fastcall TNotasForm::OnIdle(TObject *Sender, bool &Done)
{
   bool st;
   st = Editor->SelLength > 0;
   // Activa o desactiva la opcion de Cortar
   Cortar1->Enabled = st;
   Cortar2->Enabled = st;
   // Activa o desactiva la opcion de Copiar
   Copiar1->Enabled = st; 
   Copiar2->Enabled = st;
   // Activa o desactiva la opcion de Pegar 
   st = Clipboard()->HasFormat(CF_TEXT);
   Pegar1->Enabled = st;
   Pegar2->Enabled = st;
      
   // Activa o desactiva la opcion de Deshacer
   st = Editor->Modified;
   Deshacer1->Enabled = st;
   Deshacer2->Enabled = st;
   // Activa o desactiva la opcion de Grabar y Grabar como ...
   Grabar1->Enabled = st;
   Grabarcomo1->Enabled = st;
   Imprimir2->Enabled = st;
   // Activa o desactiva la opcion de Seleccionar todo
   st = Editor->Lines->Count > 0;
   Seleccionar1->Enabled = st;
   Seleccionar2->Enabled = st;
}

// Nuevo archivo
void __fastcall TNotasForm::Nuevo1Click(TObject *Sender)
{
   if (MessageBox(Handle,"¿Desea iniciar un nuevo archivo?","Notas",MB_YESNO + MB_ICONQUESTION) == IDYES) {
      if (Editor->Modified) {
         int res = MessageBox(Handle,"El archivo actual ha sido cambiado, ¿se graba?","Notas",MB_YESNOCANCEL + MB_ICONQUESTION);
         if (res == IDYES) Grabar1Click(Sender);
         if (res == IDCANCEL) return;
      }
      if (Editor->Lines->Count > 0) Editor->Clear();
      SaveDialog->FileName = "";
   }
}

void __fastcall TNotasForm::Abrir1Click(TObject *Sender)
{
   if (Editor->Modified) {
      int res = MessageBox(Handle,"El archivo actual ha sido cambiado, ¿se graba?","Notas",MB_YESNOCANCEL + MB_ICONQUESTION);
      if (res == IDYES) Grabar1Click(Sender);
      if (res == IDCANCEL) return;
   }        
   OpenDialog->FileName = "";
   if (OpenDialog->Execute()) {
      // Lee la configuracion de la ventana
      if (!Configuracion_ventana(OpenDialog->FileName.c_str(),1)) return;
      // Limpia el contenido del editor
      if(Editor->Lines->Count > 0) Editor->Clear();
      // Revisa que el archivo exista y pueda ser leido
      if (access(OpenDialog->FileName.c_str(),04) == 0) {
         // Lee el archivo
         Editor->Lines->LoadFromFile(OpenDialog->FileName);
      }
      // Genera archivo de respaldo
      Manipulador_archivos ma;
      char arch[MAXPATH];
      ma.Cambia_ext_path(OpenDialog->FileName.c_str(),"BAK", arch);
      ma.Copia_archivo(OpenDialog->FileName.c_str(),arch);
      // Graba en la bitacora el archivo abierto
      NCO.Bitacora("Abrir archivo de notas",OpenDialog->FileName.c_str(),"");
      SaveDialog->FileName = OpenDialog->FileName;
      cla.Inserta_nombre(OpenDialog->FileName.c_str());
      Actualiza_lista();
   }
}


// Graba archivo del editor
void __fastcall TNotasForm::Grabar1Click(TObject *Sender)
{
   if (Editor->Modified) {
      if (SaveDialog->FileName != "") {
         Editor->Lines->SaveToFile(SaveDialog->FileName);
         Editor->Modified = false;
         // Graba la configuracion de la ventana
         Configuracion_ventana(SaveDialog->FileName.c_str(),0);
         OpenDialog->FileName = SaveDialog->FileName;
         cla.Inserta_nombre(OpenDialog->FileName.c_str());
         Actualiza_lista();
      } else Grabarcomo1Click(Sender);
   }
}


// Graba archivo como ... 
void __fastcall TNotasForm::Grabarcomo1Click(TObject *Sender)
{
   SaveDialog->Title = "Graba como ...";
   if (SaveDialog->Execute()) {
      if (access(SaveDialog->FileName.c_str(),00) == 0) {
         if (access(SaveDialog->FileName.c_str(),02) == 0) {
             if (MessageBox(Handle,"¿Desea sobreescribir el archivo?","Notas",MB_YESNO + MB_ICONQUESTION) == IDYES) {
                Editor->Lines->SaveToFile(SaveDialog->FileName);
                Editor->Modified = false;
                // Graba la configuracion de la ventana
                Configuracion_ventana(SaveDialog->FileName.c_str(),0);
                OpenDialog->FileName = SaveDialog->FileName;
                cla.Inserta_nombre(OpenDialog->FileName.c_str());
                Actualiza_lista();
             }
         } else MessageBox(Handle,"El archivo tiene permiso de solo lectura","Notas",MB_OK + MB_ICONEXCLAMATION);
       } else {
         Editor->Lines->SaveToFile(SaveDialog->FileName);
         Editor->Modified = false;
         // Graba la configuracion de la ventana
         Configuracion_ventana(SaveDialog->FileName.c_str(),0);
         OpenDialog->FileName = SaveDialog->FileName;
         cla.Inserta_nombre(OpenDialog->FileName.c_str());
         Actualiza_lista();
      }
   }
}



// Imprime el contenido del sistema
void __fastcall TNotasForm::Imprimir1Click(TObject *Sender)
{
   Editor->Print("NOTAS");
}

// Configura el tipo de impresora
void __fastcall TNotasForm::Configurarimpresora1Click(TObject *Sender)
{
   PrintDialog->Execute();        
}


// Salir del programa
void __fastcall TNotasForm::Salir1Click(TObject *Sender)
{
   Close();        
}


void __fastcall TNotasForm::Deshacer1Click(TObject *Sender)
{
   SendMessage(Editor->Handle,WM_UNDO,0,0);        
}

void __fastcall TNotasForm::Cortar1Click(TObject *Sender)
{
   Editor->CutToClipboard();        
}

void __fastcall TNotasForm::Copiar1Click(TObject *Sender)
{
   Editor->CopyToClipboard();
}

void __fastcall TNotasForm::Pegar1Click(TObject *Sender)
{
   Editor->PasteFromClipboard();       
}

// Selecciona todo el texto
void __fastcall TNotasForm::Seleccionar1Click(TObject *Sender)
{
   Editor->SelectAll();        
}

// Copia todo el contenido
void __fastcall TNotasForm::Copiartodo1Click(TObject *Sender)
{
   Editor->SelectAll();                
   Editor->CopyToClipboard();        
}


void __fastcall TNotasForm::Insertafecha1Click(TObject *Sender)
{
   char fecha[20], fec_esc[50];
   Manipulador_archivos ma;
   Fechas_Horas fh;

   fh.Fecha_hoy(fecha);
   fh.Fecha_escrita(fecha, fec_esc, 1, 1);
   ma.Convierte_linea(fec_esc);
   Editor->SetSelTextBuf(fec_esc);
}

void __fastcall TNotasForm::Insertahora1Click(TObject *Sender)
{
   char tiempo[20];
   Manipulador_archivos ma;
   Fechas_Horas fh;
   
   fh.Hora_actual(tiempo, 1, 1);
   fh.Trim(tiempo);
   ma.Convierte_linea(tiempo);
   Editor->SetSelTextBuf(tiempo);
}

void __fastcall TNotasForm::Insertafechayhora1Click(TObject *Sender)
{
   char xcad[100];
   Manipulador_archivos ma;
   Fechas_Horas fh;

   fh.Fecha_y_hora(xcad, 1, 1);
   ma.Convierte_linea(xcad);
   Editor->SetSelTextBuf(xcad);
}


// Leer bloque de un archivo
void __fastcall TNotasForm::Leerbloque1Click(TObject *Sender)
{
   OpenDialog1->FileName = "";
   if (OpenDialog1->Execute()) {
      char xcad[310];
      // Lee la configuracion del usuario
      Manipulador_archivos ma;
      ma.Parametros(OpenDialog1->FileName.c_str(),LEE_ARCHIVO,300);
      // Revisa que pueda abrir correctamente el archivo
      if (ma.Retorna_estado()) return;
      while(!ma.Retorna_estado()) {
         ma.Lee_linea(xcad);
         if (!ma.Retorna_estado()) {
            ma.Convierte_linea(xcad);
            Editor->SetSelTextBuf(xcad);
         }
      } 
   }
}

// Convierte el bloque en mayusculas
void __fastcall TNotasForm::Convierteamaysculas1Click(TObject *Sender)
{
   Cadenas c;
   int Size = Editor->SelLength; 
   Size++;                      
   char *Buffer = new char[Size];  
   Editor->GetSelTextBuf(Buffer,Size); 
   c.Convierte_mayusculas(Buffer);
   Editor->SetSelTextBuf(Buffer);        
   delete Buffer;
}

// Convierte el bloque en minusculas
void __fastcall TNotasForm::Convierteaminusculas1Click(TObject *Sender)
{
   Cadenas c;
   int Size = Editor->SelLength; 
   Size++;                      
   char *Buffer = new char[Size];  
   Editor->GetSelTextBuf(Buffer,Size); 
   c.Convierte_minusculas(Buffer);
   Editor->SetSelTextBuf(Buffer);        
   delete Buffer;
}

// Configura el color de las notas
void __fastcall TNotasForm::Configuracolor1Click(TObject *Sender)
{
   ColorDialog->Color = Editor->Color;
   if(ColorDialog->Execute()) Editor->Color = ColorDialog->Color;
}

// Configura el tipo de letra
void __fastcall TNotasForm::Configuratipodeletra1Click(TObject *Sender)
{
   if (MessageBox(Handle,"Afectaria el tipo de letra de todo el texto, ¿Desea cambiar el tipo de letra?","Notas",MB_YESNO + MB_ICONQUESTION)  == IDYES) {
      FontDialog->Font = Editor->Font;
      if(FontDialog->Execute()) Editor->Font = FontDialog->Font;
   }
}

// Longitud de edicion fija/variable
void __fastcall TNotasForm::Longituddeedicinfija1Click(TObject *Sender)
{
   if (Editor->WordWrap) {
      // Longitud variable
      Editor->WordWrap = false;
      Editor->ScrollBars = ssBoth;
      Longituddeedicinfija1->Caption = "&Longitud de edición fija";
    } else {
      // Longitud fija
      Editor->WordWrap = true;     
      Editor->ScrollBars = ssVertical;
      Longituddeedicinfija1->Caption = "&Longitud de edición variable";
   }
}

// Ventana no/siempre visible
void __fastcall TNotasForm::Ventanasiemprevisible1Click(TObject *Sender)
{
   if (FormStyle == fsStayOnTop) {
       Ventanasiemprevisible1->Caption = "&Ventana siempre visible";
       FormStyle = fsNormal;
    } else {
       Ventanasiemprevisible1->Caption = "&Ventana no siempre visible";
       FormStyle = fsStayOnTop;
   }
}


// Graba cada 5 minutos si el archivo de notas tiene nombre
void __fastcall TNotasForm::TimerTimer(TObject *Sender)
{
   if (SaveDialog->FileName != "") Grabar1Click(Sender);
}

// Acerca de ...
void __fastcall TNotasForm::Acercade1Click(TObject *Sender)
{
   TAcercaDeForm *AcercaDeForm = new TAcercaDeForm(this);
   AcercaDeForm->Muestra_ventana_AcercaDe("Notas");
   delete AcercaDeForm;
}


// Graba o recupera la configuración de la ventana de trabajo
bool TNotasForm::Configuracion_ventana(const char *arch, const bool st)
{
   int xIzq, xArr, xLar, xAnc, siz, st1 = 0, st2 = 0, st3 = 0, st4 = 0;
   bool estatus = true;
   char fnt[100];
   char xarch[MAXPATH];
   TColor            Color_fondo;
   TColor            Color_texto;

   Manipulador_archivos ma;
   // Cambia la extención del archivo
   ma.Cambia_ext_path(arch,"CFG",xarch);
   
   if (st) {
      // Valores de configuracion por omision
      xIzq = 10, xArr = 60, xLar = 270, xAnc = 200;
      Color_fondo = Editor->Color;
      Color_texto = Editor->Font->Color;
      strcpy(fnt,Editor->Font->Name.c_str());
      siz = Editor->Font->Size;
      // lee la configuracion de la ventana
      ifstream lee(xarch,ios::binary);
      if (lee) {
         lee.read((char *)&xIzq,sizeof(xIzq));
         lee.read((char *)&xArr,sizeof(xArr));
         lee.read((char *)&xLar,sizeof(xLar));
         lee.read((char *)&xAnc,sizeof(xAnc));
         lee.read((char *)&Color_fondo,sizeof(TColor));
         lee.read((char *)&Color_texto,sizeof(TColor));
         lee.read((char *)&siz,sizeof(siz));
         lee.read((char *)fnt,100);
         lee.read((char *)&st1,sizeof(st1));
         lee.read((char *)&st2,sizeof(st2));
         lee.read((char *)&st3,sizeof(st3));
         lee.read((char *)&st4,sizeof(st4));
         lee.read((char *)&Encriptado,sizeof(Encriptado));
         lee.read((char *)&Password,strlen(Password));
         lee.close();
      }
      // Revisa si el archivo tiene clave de seguridad para su lectura
      if (Encriptado[0] != 'N') {
         Clave_seguridad cs;

         TCapturaClaveSeguridadForm *clvseg = new TCapturaClaveSeguridadForm(this);
         clvseg->Caption = "Clave para leer el archivo";
         clvseg->ShowModal();
         char xpass[32];
         strcpy(xpass,clvseg->Edit1->Text.c_str());
         if (clvseg->Estado) {
            if (!cs.Compara(xpass,"ECVCYACL$$")) {
               if (!cs.Compara(cs.Desencripta(Password),xpass)) {
                  MessageBox(Handle,"Error en la clave de acceso, el archivo no fue cargado","Notas",MB_OK + MB_ICONSTOP);
                  estatus = false;
                  return estatus;
               }
            }
         } 
         delete clvseg;
      }
      // Modificar configuracion de ventana
      Editor->Color = Color_fondo;
      Editor->Font->Color = Color_texto;
      Editor->Font->Name = fnt;
      Editor->Font->Size = siz;
      TFontStyles st;
      if (st1) st << fsBold;
      if (st2) st << fsItalic;
      if (st3) st << fsUnderline;
      if (st4) st << fsStrikeOut;
      Editor->Font->Style = st;
      Left = xIzq;
      Top = xArr;
      Height = xLar;
      Width = xAnc;
    } else {
      // Graba la configuracion de la ventana
      ofstream grab(xarch,ios::binary);
      if (grab) {
         Color_fondo = Editor->Color;
         Color_texto = Editor->Font->Color;
         siz         = Editor->Font->Size;
         if (Editor->Font->Style.Contains(fsBold)) st1 = 1;
         if (Editor->Font->Style.Contains(fsItalic)) st2 = 1;
         if (Editor->Font->Style.Contains(fsUnderline)) st3 = 1;
         if (Editor->Font->Style.Contains(fsStrikeOut)) st4 = 1;
         grab.write((char *)&Left,sizeof(Left));
         grab.write((char *)&Top,sizeof(Top));
         grab.write((char *)&Height,sizeof(Height));
         grab.write((char *)&Width,sizeof(Width));
         grab.write((char *)&Color_fondo,sizeof(TColor));
         grab.write((char *)&Color_texto,sizeof(TColor));
         grab.write((char *)&siz,sizeof(siz));
         grab.write((char *)Editor->Font->Name.c_str(),100);
         grab.write((char *)&st1,sizeof(st1));
         grab.write((char *)&st2,sizeof(st2));
         grab.write((char *)&st3,sizeof(st3));
         grab.write((char *)&st4,sizeof(st4));
         grab.write((char *)&Encriptado,sizeof(Encriptado));
         grab.write((char *)&Password,strlen(Password)+1);
         grab.close();
      }                                                        
   }
   return estatus;
}


// Buscar cadena
void __fastcall TNotasForm::Buscar1Click(TObject *Sender)
{
    FindDialog->FindText = Editor->SelText;
    FindDialog->Execute();
}

// Buscar cadena dentro del texto
void __fastcall TNotasForm::FindDialogFind(TObject *Sender)
{
    Show();
    TSearchTypes st;
    TFindDialog *cd;
    int newpos;

    if ((cd = dynamic_cast<TFindDialog *> (Sender)) == 0) MessageBox(NULL, "Error en solicitud de memoria dinámica", "Buscar", MB_OK + MB_ICONSTOP);

    if (cd->Options.Contains(frMatchCase)) st << stMatchCase;
    if (cd->Options.Contains(frWholeWord)) st << stWholeWord;

    if (Editor->SelLength) Editor->SelStart += 1;

    newpos = Editor->FindText(cd->FindText, Editor->SelStart, Editor->Text.Length(), st);

    if (newpos != -1) {
        Editor->SelStart = newpos;
        Editor->SelLength = cd->FindText.Length();
     } else {
        MessageBox(NULL, "Fin del documento", "Buscar", MB_OK + MB_ICONINFORMATION);
        Editor->SelStart = 0;
    }
}

// Busca y Remplaza texto del editor
void __fastcall TNotasForm::ReplaceDialogFind(TObject *Sender)
{
    if (Editor->SelLength == 0) FindDialogFind(Sender);
    else {
        Editor->SelText =  ReplaceDialog->ReplaceText;
        FindDialogFind(Sender);
    }

    if (ReplaceDialog->Options.Contains(frReplaceAll)) {
        while (Editor->SelLength !=0) {
           ReplaceDialogFind(Sender);
        }
    }
}

// Dialogo de buscar y remplazar
void __fastcall TNotasForm::Buscaryremplazar1Click(TObject *Sender)
{
    ReplaceDialog->FindText = Editor->SelText;
    ReplaceDialog->Execute();
}


// Tipo de letra negrita
void __fastcall TNotasForm::Negrita1Click(TObject *Sender)
{
   if (Editor->SelAttributes->Style.Contains(fsBold)) Editor->SelAttributes->Style = Editor->SelAttributes->Style >> fsBold;
   else Editor->SelAttributes->Style = Editor->SelAttributes->Style << fsBold;
}

// Tipo de letra italica
void __fastcall TNotasForm::Italica1Click(TObject *Sender)
{
   if (Editor->SelAttributes->Style.Contains(fsItalic)) Editor->SelAttributes->Style = Editor->SelAttributes->Style >> fsItalic;
   else Editor->SelAttributes->Style = Editor->SelAttributes->Style << fsItalic;
}

// Tipo de letra subrayado
void __fastcall TNotasForm::Subrayado1Click(TObject *Sender)
{
   if (Editor->SelAttributes->Style.Contains(fsUnderline)) Editor->SelAttributes->Style = Editor->SelAttributes->Style >> fsUnderline;
   else Editor->SelAttributes->Style = Editor->SelAttributes->Style << fsUnderline;
}

// Tipo de letra tachada
void __fastcall TNotasForm::Tachado1Click(TObject *Sender)
{                                            
   if (Editor->SelAttributes->Style.Contains(fsStrikeOut)) Editor->SelAttributes->Style = Editor->SelAttributes->Style >> fsStrikeOut;
   else Editor->SelAttributes->Style = Editor->SelAttributes->Style << fsStrikeOut;
}


// Define el tipo de letra del parrafo
void __fastcall TNotasForm::Tipodeletra2Click(TObject *Sender)
{
   FontDialog->Font->Assign( Editor->SelAttributes );
   if (FontDialog->Execute()) Editor->SelAttributes->Assign(FontDialog->Font);
   Editor->SetFocus();
}

// Alineación a la izquierda
void __fastcall TNotasForm::AlineadoIzquierda1Click(TObject *Sender)
{
   Editor->Paragraph->Alignment = taLeftJustify;        
}

// Alineación a la derecha
void __fastcall TNotasForm::Alineadoderecha1Click(TObject *Sender)
{
   Editor->Paragraph->Alignment = taRightJustify;
}

// Alineación centrada
void __fastcall TNotasForm::Alineadocentrada1Click(TObject *Sender)
{
   Editor->Paragraph->Alignment =  taCenter;
}

// Viñetas
void __fastcall TNotasForm::Vietas1Click(TObject *Sender)
{
   if (Editor->Paragraph->Numbering == nsNone) Editor->Paragraph->Numbering = nsBullet;
    else Editor->Paragraph->Numbering = nsNone;      
}






/*
// Imprime el contenido del sistema
void __fastcall TNotasForm::Imprimir1Click(TObject *Sender)
{
   if (PrintDialog->Execute()) {
      Printer()->Title = "NOTAS";
      Printer()->Canvas->Font = Editor->Font;
      int LineaAlto = abs(MulDiv(Printer()->Canvas->Font->Size, GetDeviceCaps(Printer()->Handle,LOGPIXELSY), 72));
      LineaAlto *= 1.4;
      int LineasPorPagina = (Printer()->PageHeight/LineaAlto) -4;
      int Contador_lineas = 4;
      Printer()->BeginDoc();
      TRect rect;
      rect.Top = LineaAlto;
      rect.Left = 20;
      rect.Right = Printer()->PageWidth;
      rect.Bottom = LineaAlto * 2;
      DrawText(Printer()->Handle, "NOTAS", -1, (RECT*) & rect, DT_CENTER);
      for (int i=0;i < Editor->Lines->Count; i++) {
         if (Contador_lineas++ ==LineasPorPagina) {
            Pie_pagina_impresion(rect,LineaAlto);
            Contador_lineas = 4;
            Printer()->NewPage();
         }
         String s = Editor->Lines->Strings[i];
         Printer()->Canvas->TextOut(0, Contador_lineas * LineaAlto, s);
      }
      Pie_pagina_impresion(rect,LineaAlto);
      Printer()->EndDoc();
   }        
}


// Imprime el pie de pagina
void TNotasForm::Pie_pagina_impresion(TRect &rect,int LineaAlto)
{
   char buff[100];
   wsprintf(buff, "Pagina %d", Printer()->PageNumber);
   rect.Top = Printer()->PageHeight -(LineaAlto * 2);
   rect.Bottom = rect.Top + LineaAlto;
   DrawText(Printer()->Handle, buff, -1, (RECT*) &rect, DT_CENTER);
   Printer()->Canvas->MoveTo(0,rect.Top -2);
   Printer()->Canvas->LineTo(rect.Right,rect.Top -2);
}
*/


void TNotasForm::Actualiza_lista(void)
{
   char arch[MAXPATH];
   char xcad[100];
   bool st;
   
   Manipulador_archivos ma;
   
   cla.Retorna_nombre(0,arch, st);
   strcpy(NombresArchivos[0],arch);
   ma.AjustaNombreArchivo(arch,xcad);
   Arch1->Caption = xcad;   
   Arch1->Visible = st;

   cla.Retorna_nombre(1,arch, st);
   strcpy(NombresArchivos[1],arch);
   ma.AjustaNombreArchivo(arch,xcad);
   Arch2->Caption = xcad;   
   Arch2->Visible = st;

   cla.Retorna_nombre(2,arch, st);
   strcpy(NombresArchivos[2],arch);
   ma.AjustaNombreArchivo(arch,xcad);
   Arch3->Caption = xcad;   
   Arch3->Visible = st;
    
   cla.Retorna_nombre(3,arch, st);
   strcpy(NombresArchivos[3],arch);
   ma.AjustaNombreArchivo(arch,xcad);
   Arch4->Caption = xcad;   
   Arch4->Visible = st;

   Separador->Visible = cla.Existe_almenos_uno();
}


void __fastcall TNotasForm::Arch1Click(TObject *Sender)
{
   Abrir_archivo_lista(NombresArchivos[0]);
}

void __fastcall TNotasForm::Arch2Click(TObject *Sender)
{
   Abrir_archivo_lista(NombresArchivos[1]);
}

void __fastcall TNotasForm::Arch3Click(TObject *Sender)
{
   Abrir_archivo_lista(NombresArchivos[2]);
}

void __fastcall TNotasForm::Arch4Click(TObject *Sender)
{
   Abrir_archivo_lista(NombresArchivos[3]);
}

void TNotasForm::Abrir_archivo_lista(const char *xarch)
{
   if (Editor->Modified) {
      int res = MessageBox(Handle,"El archivo actual ha sido cambiado, ¿se graba?","Notas",MB_YESNOCANCEL + MB_ICONQUESTION);
      if (res == IDYES) Grabar1Click(this);
      if (res == IDCANCEL) return;
   }        
   OpenDialog->FileName = xarch;
   // Lee la configuracion de la ventana
   if (!Configuracion_ventana(xarch,1)) return;
   // Limpia el contenido del editor
   if(Editor->Lines->Count > 0) Editor->Clear();
   // Revisa que el archivo exista y pueda ser leido
   if (access(xarch,04) == 0) {
      // Lee el archivo
      Editor->Lines->LoadFromFile(xarch);
   }
   // Genera archivo de respaldo
   Manipulador_archivos ma;
   char arch[MAXPATH];
   ma.Cambia_ext_path(xarch,"BAK", arch);
   ma.Copia_archivo(xarch,arch);
   // Graba en la bitacora el archivo abierto
   NCO.Bitacora("Abrir archivo de notas",OpenDialog->FileName.c_str(),"");
   SaveDialog->FileName = xarch;
   cla.Inserta_nombre(xarch);
   Actualiza_lista();
}

// Solicita la clave de seguridad para el documento actual
void __fastcall TNotasForm::Clavedeseguridad1Click(TObject *Sender)
{
   Clave_seguridad cs;
   char xxpassword[32];
   char xpassword[32];

   TCapturaClaveSeguridadForm *clvseg = new TCapturaClaveSeguridadForm(this);
   clvseg->ShowModal();
   if (clvseg->Estado) {
      strcpy(xpassword,clvseg->Edit1->Text.c_str());
      delete clvseg;
      TCapturaClaveSeguridadForm *clvseg = new TCapturaClaveSeguridadForm(this);
      clvseg->Caption = "Confirmación de la clave";
      clvseg->ShowModal();
      if (clvseg->Estado) {
         strcpy(xxpassword,clvseg->Edit1->Text.c_str());
         if (cs.Compara(cs.Desencripta(cs.Encripta(xpassword)),xxpassword)) {
            strcpy(Password,cs.Encripta(xpassword));
            strcpy(Encriptado,"S");
         } else MessageBox(Handle,"Error en la confirmación de la clave","Notas",MB_OK + MB_ICONSTOP);
      } 
      delete clvseg;
   } else delete clvseg;
}

