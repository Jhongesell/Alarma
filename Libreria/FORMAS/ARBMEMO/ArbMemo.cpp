// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Dirección: Amsterdam 312 col. Hipodromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#include <vcl.h>
#include <Clipbrd.hpp>
#include <extctrls.hpp>
#include <filectrl.hpp>
#include <fstream.h>
#include <stdlib.h>
#include <stdio.h>
#include <dir.h>
#include <io.h>
#include "d:\Libreria\fechora.hpp"
#include "d:\libreria\man_arch.hpp"
#include "D:\Libreria\Formas\ArbMemo\ArbMemo.h"
#include "d:\Libreria\Formas\AcercaDe.h"
#include "d:\libreria\formas\FCap1.h"
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

#define APLICACION "Arbol de Edición"



__fastcall TArbolMemoForm::TArbolMemoForm(TComponent* Owner): TForm(Owner)
{
}

// Al crear la forma
void __fastcall TArbolMemoForm::FormCreate(TObject *Sender)
{
   char arch[MAXPATH];
   Manipulador_archivos ma;
   
   ma.Construye_trayectoria(TRAYECTORIA_ARCHIVOS,"ARBOLMEM.CFG", arch);
   cla.Inicializa_lista_archivos(arch);
   Actualiza_lista();

   Arbol->SortType = stNone;
   Modificado = false;
   Actual = NULL;
   Datos = new TStringList;
   Pegar_activo = false;
   Genera_nuevo_nodo = false;
   OpenDialog->FileName = "";
   SaveDialog->FileName = "";
   strcpy(Encriptado,"N");
   strcpy(Password,"ESTE ES UN PASWORD MUY LARGO");
} 

// Al cerrar la forma
void __fastcall TArbolMemoForm::FormCloseQuery(TObject *Sender,  bool &CanClose)
{
   CanClose = false;
   if (Modificado) {
      if (MessageBox(Handle,"¿Desea terminar la actual edición?",APLICACION,MB_YESNO + MB_ICONQUESTION)  == IDYES) {
            if (MessageBox(Handle,"El archivo actual ha sido cambiado, ¿se graba?",APLICACION,MB_YESNO + MB_ICONQUESTION) == IDYES) Grabar1Click(Sender);
      } else return;
   }
   Destruye();
   delete Datos;
   Application->OnHint = NULL;
   Application->OnIdle = NULL;
   NCO.Activa_Borrado(PtrArbolEdicion);   
   CanClose = true;
}


// Al activar la forma
void __fastcall TArbolMemoForm::FormActivate(TObject *Sender)
{
   Application->OnHint = OnHint;
   Application->OnIdle = OnIdle;
}

// Al desactivar la forma
void __fastcall TArbolMemoForm::FormDeactivate(TObject *Sender)
{
   Application->OnHint = NULL;
   Application->OnIdle = NULL;
}

// OnHint
void  __fastcall TArbolMemoForm::OnHint(TObject *Sender)
{
   BarraDeEstados->SimpleText = Application->Hint;
}

// OnIdle
void  __fastcall TArbolMemoForm::OnIdle(TObject *Sender, bool &Done)
{
   if (Editor->Modified) Modificado = true;
   bool st;
   st = Editor->SelLength > 0;
   // Activa o desactiva la opcion de Cortar
   Corta->Enabled = st;
   Corta1->Enabled = st;
   // Activa o desactiva la opcion de Copiar
   Copia->Enabled = st; 
   Copia1->Enabled = st;
   Copia2->Enabled = st;
   // Activa o desactiva la opcion de Pegar 
   st = Clipboard()->HasFormat(CF_TEXT);
   Pegar->Enabled = st;
   Pegar1->Enabled = st;
   Pegar2->Enabled = st;
      
   // Activa o desactiva la opcion de Deshacer
   st = Editor->Modified;
   Deshacer->Enabled = st;
   Deshacer1->Enabled = st;
   Deshacer2->Enabled = st;
   // Activa o desactiva la opcion de Grabar y Grabar como ...
   BGrabar->Enabled = Modificado;
   Grabar1->Enabled = Modificado;
   Grabarcomo1->Enabled = Modificado;
   Imprimir1->Enabled = st;
   // Activa o desactiva la opcion de Seleccionar todo
   st = Editor->Lines->Count > 0;
   Selecciona1->Enabled = st;
   Selecciona2->Enabled = st;
   // Activa o desactiva la opción de imprimir
   BImprimir->Enabled = st;
   Imprimir1->Enabled = st;
   // Activa o desactiva la opcion de cambiar titulo
   st = Arbol->Items->Count > 0;
   BEditaTitulo->Enabled = st;
   // Activa o desactiva la opcion de borrar nodo
   BBorraNodo->Enabled = st;
   // Activa o desactiva la opcion de expande todo el árbol
   BExpandeTodo->Enabled = st;
   // Activa o desactiva la opcion de colapsa todo el árbol
   BColapsaTodo->Enabled = st;
   // No permite editar texto a menos que exista un nodo
   if (Editor->Lines->Count > 0 && Arbol->Items->Count == 0) Genera_nuevo_nodo = true;
}


// Al destruirse la forma
void TArbolMemoForm::Destruye(void)
{
   int i;
   for (i = 0; i < Arbol->Items->Count; i++) {
       TStrings *ed = (TStrings *) Arbol->Items->Item[i]->Data;
       delete ed;
       Arbol->Items->Item[i]->Data = NULL;
   }
   Arbol->Items->Clear();
   Editor->Clear();
   OpenDialog->FileName = "";
   SaveDialog->FileName = "";
   Modificado = false;
   Pegar_activo = false;
   Actual = NULL;
}


// Abrir el archivo indicado
void TArbolMemoForm::Abrir(const char *arch, const int ptr)
{
   PtrArbolEdicion = ptr;
   SaveDialog->FileName = arch;
   if (arch[0]) LeerArbolMemo(arch);
   Show();
}


// Actualiza el contenido del editor
void TArbolMemoForm::Actualiza(void)
{
   TStrings *ed;
   if (Actual) {
      ed = (TStrings *) Actual->Data;
      ed->Text = Editor->Lines->Text;
      Editor->Modified = false;
   }
}

// Nuevo archivo
void __fastcall TArbolMemoForm::Nuevo1Click(TObject *Sender)
{
   if (MessageBox(Handle,"¿Desea iniciar un nuevo archivo?",APLICACION,MB_YESNOCANCEL + MB_ICONQUESTION) == IDYES) {
      if (Modificado) {
         int res = MessageBox(Handle,"El archivo actual ha sido cambiado, ¿se graba?",APLICACION,MB_YESNOCANCEL + MB_ICONQUESTION);
         if (res == IDYES) Grabar1Click(Sender);
         if (res == IDCANCEL) return;
      }
      Destruye();
//      Titulo();
   }
}

// Abre el archivo de arbol de edición indicado
void __fastcall TArbolMemoForm::Abrir1Click(TObject *Sender)
{
   Actualiza();

   // Graba si el archivo fue modificado
   if (Modificado) {
      int res = MessageBox(Handle,"El archivo actual ha sido cambiado, ¿se graba?",APLICACION,MB_YESNOCANCEL + MB_ICONQUESTION);
      if (res == IDYES) Grabar1Click(Sender);
      if (res == IDCANCEL) return;
   }
   OpenDialog->FileName = "";
   if (OpenDialog->Execute()) {
      // Revisa que el archivo exista y pueda ser leido
      if (access(OpenDialog->FileName.c_str(),04) == 0) {
         // Lee el archivo
         LeerArbolMemo(OpenDialog->FileName.c_str());
      }
      SaveDialog->FileName = OpenDialog->FileName;
   }
//   Titulo();
}

// Lee un archivo al arbol de edición
void TArbolMemoForm::LeerArbolMemo(const char *arch)
{
   // Graba en la bitacora el archivo abierto
   NCO.Bitacora("Abrir archivo árbol edición",arch,"");

   cla.Inserta_nombre(arch);
   Actualiza_lista();


   TStrings *ed;
   char *xcad, xarch[MAXPATH], archbak[MAXPATH];
   int i, lg, num_elem;
   Manipulador_archivos ma;

   // Lee la configuracion de la ventana
   ma.Cambia_ext_path(arch,"CFG",xarch);
   if (!Configuracion_ventana(xarch,true)) return;
   // Lee el archivo del arbol
   Editor->Clear();
   ma.Cambia_ext_path(arch,"DAT",xarch);
   if (access(xarch,0) == 0) Arbol->LoadFromFile(xarch);
   for(i = 0; i < Arbol->Items->Count ; i++) {
       TStrings *xed =  new TStringList;
       Arbol->Items->Item[i]->Data = xed;
   }
   // Genera archivo de respaldo del DAT
   ma.Cambia_ext_path(xarch,"BAD", archbak);
   ma.Copia_archivo(xarch,archbak);
   if (!Arbol->Items->Count) return;

   // Lee el archivo memo 
   ma.Cambia_ext_path(arch,"MEM",xarch);
   ifstream lee(xarch,ios::binary);
   if(lee) {
      lee.read((char *) &num_elem, sizeof(num_elem));
      for(i = 0; i < num_elem; i++) {
          lee.read((char *) &lg, sizeof(lg));
          xcad = new char[lg];
          lee.read(xcad,lg);
          ed = (TStrings *) Arbol->Items->Item[i]->Data;
          ed->Text = xcad;
          delete []xcad;
      }
      lee.close();
   }
   // Genera archivo de respaldo MEM
   ma.Cambia_ext_path(xarch,"BAM", archbak);
   ma.Copia_archivo(xarch,archbak);

   Arbol->Selected = Arbol->Items->Item[0];
   Actual = Arbol->Selected;
   ed = (TStrings *) Actual->Data;
   Editor->Lines->Text = ed->Text;
   Modificado = false;
   Editor->Modified = false;
}


// Graba el archivo de arbol de edición indicado
void __fastcall TArbolMemoForm::Grabar1Click(TObject *Sender)
{
   Actualiza();
   
   if (SaveDialog->FileName != "") GrabaArbolMemo();
    else Grabarcomo1Click(Sender);
}

void __fastcall TArbolMemoForm::Grabarcomo1Click(TObject *Sender)
{
   Actualiza();

   SaveDialog->Title = "Graba como ...";
   if (SaveDialog->Execute()) {
      if (access(SaveDialog->FileName.c_str(),00) == 0) {
         if (access(SaveDialog->FileName.c_str(),02) == 0) {
             if (MessageBox(Handle,"¿Desea sobreescribir el archivo?",APLICACION,MB_YESNO + MB_ICONQUESTION) == IDYES) GrabaArbolMemo();
         } else MessageBox(Handle,"El archivo tiene permiso de solo lectura",APLICACION,MB_OK + MB_ICONINFORMATION);
      } else GrabaArbolMemo();
   }
   OpenDialog->FileName = SaveDialog->FileName;
//   Titulo();
}

// Graba el contenido del arbol de edicion
void TArbolMemoForm::GrabaArbolMemo(void)
{
   TStrings *ed;
   char *xcad, xarch[MAXPATH], arch[MAXPATH];
   int i, lg;
   Manipulador_archivos ma;
   strcpy(arch,SaveDialog->FileName.c_str());
   cla.Inserta_nombre(arch);
   Actualiza_lista();

   // Lee la configuracion de la ventana
   ma.Cambia_ext_path(arch,"CFG",xarch);
   Configuracion_ventana(xarch,false);
   // Graba el archivo del arbol
   ma.Cambia_ext_path(arch,"DAT",xarch);
   Arbol->SaveToFile(xarch);
   // Graba el archivo memo
   ma.Cambia_ext_path(arch,"MEM",xarch);
   ofstream grab(xarch,ios::binary);
   if (grab) {
      lg = Arbol->Items->Count;
      grab.write((char *)&lg,sizeof(lg));
      for (i = 0; i < Arbol->Items->Count; i++) {
          ed = (TStrings *) Arbol->Items->Item[i]->Data;
          lg = strlen(ed->Text.c_str())+1;
          xcad = new char[lg];
          strcpy(xcad,ed->Text.c_str());
          grab.write((char *)&lg, sizeof(lg));
          grab.write(xcad,lg);
          delete []xcad;
      }
      grab.close();
   }
   Editor->Modified = false;
   Modificado = false;
}


// Configura la impresora
void __fastcall TArbolMemoForm::Configurarimpresora1Click(TObject *Sender)
{
   PrintDialog->Execute();        
}


// Termina el programa
void __fastcall TArbolMemoForm::MSalirClick(TObject *Sender)
{
   Close();        
}


// Adiciona arriba del nodo actual
void __fastcall TArbolMemoForm::AdicionaArribaClick(TObject *Sender)
{
   Actualiza();
   TCaptura1Form *cn = new TCaptura1Form(this);
   cn->Abrir("Nuevo nodo","Nodo:", "","Escriba el nombre del nuevo nodo");
   if (cn->st) {
      // Revisa que no exista el grupo a adicionar en este mismo nivel
      if (Arbol->Selected) {
         bool st = false;
         TTreeNode *act = Arbol->Selected;
         while (act) {
            if (act->Text == cn->Edit1->Text) st = true;
            act = act->getNextSibling();
         }
         act = Arbol->Selected->getPrevSibling();
         while(act) {
            if (act->Text == cn->Edit1->Text) st = true;
            act = act->getPrevSibling();
         }
         if (st) {
            MessageBox(NULL,"El nombre del grupo ya existe","Agregar grupo",MB_OK + MB_ICONEXCLAMATION);
            return;
         }
      }   

      Editor->Clear();
      TStrings *ed = new TStringList;
      Arbol->Selected = Arbol->Items->InsertObject(Arbol->Selected, cn->Edit1->Text,ed);
      Actual = Arbol->Selected;
      Modificado = true;
   }
   delete cn;
}

// Adiciona abajo del nodo actual
void __fastcall TArbolMemoForm::AdicionaAbajoClick(TObject *Sender)
{
   Actualiza();
   TCaptura1Form *cn = new TCaptura1Form(this);
   cn->Abrir("Nuevo nodo","Nodo:", "","Escriba el nombre del nuevo nodo");
   if (cn->st) {
      // Revisa que no exista el grupo a adicionar en este mismo nivel
      if (Arbol->Selected) {
         bool st = false;
         TTreeNode *act = Arbol->Selected;
         while (act) {
            if (act->Text == cn->Edit1->Text) st = true;
            act = act->getNextSibling();
         }
         act = Arbol->Selected->getPrevSibling();
         while(act) {
            if (act->Text == cn->Edit1->Text) st = true;
            act = act->getPrevSibling();
         }
         if (st) {
            MessageBox(NULL,"El nombre del grupo ya existe","Agregar grupo",MB_OK + MB_ICONEXCLAMATION);
            return;
         }
      }   

      Editor->Clear();
      TTreeNode *ts = Arbol->Selected;
      TStrings *ed = new TStringList;
      if (ts && ts->getNextSibling()) Arbol->Selected = Arbol->Items->InsertObject(ts->getNextSibling(), cn->Edit1->Text,ed);
       else Arbol->Selected = Arbol->Items->AddObject(ts, cn->Edit1->Text,ed);
      Actual = Arbol->Selected;
      Modificado = true;
   }
   delete cn;
}

// Adiciona un hijo al nodo actual
void __fastcall TArbolMemoForm::AdicionaHijoClick(TObject *Sender)
{
   Actualiza();   
   TCaptura1Form *cn = new TCaptura1Form(this);
   cn->Abrir("Nuevo nodo","Nodo:", "","Escriba el nombre del nuevo nodo");
   if (cn->st) {
      // Revisa que no se pueda repetir el nombre de un subgrupo
      if (Arbol->Selected) {
         bool st = false;
         TTreeNode *act = Arbol->Selected->getFirstChild();
         while(act) {
            if (act->Text == cn->Edit1->Text) st = true;
            act = act->getNextSibling();
         }
         if (st) {
            MessageBox(NULL,"El nombre del subgrupo ya existe","Agregar subgrupo",MB_OK + MB_ICONEXCLAMATION);
            return;
         }
      }   
      Editor->Clear();
      TStrings *ed = new TStringList;
      Arbol->Selected = Arbol->Items->AddChildObject(Arbol->Selected, cn->Edit1->Text,ed);
      Actual = Arbol->Selected;
      Modificado = true;
   }
   delete cn;
}

// Indenta un nodo
void __fastcall TArbolMemoForm::Indenta1Click(TObject *Sender)
{
    Actualiza();
    TTreeNode *ts = Arbol->Selected;
    if (ts && ts->getPrevSibling()) {
       Arbol->Selected->MoveTo(ts->getPrevSibling(), naAddChildFirst);
       Modificado = true;
    }
}

// Desindenta un nodo
void __fastcall TArbolMemoForm::Desindenta1Click(TObject *Sender)
{
    Actualiza();
    TTreeNode *ts = Arbol->Selected;
    if (ts && ts->Parent) {
        Arbol->Selected->MoveTo(ts->Parent, naInsert);
        Modificado = true;
    }
}


// Colapsa todos los elementos
void __fastcall TArbolMemoForm::Colapsatodo1Click(TObject *Sender)
{
   Arbol->FullCollapse();        
}

// Expande todos los elementos
void __fastcall TArbolMemoForm::Expandetodo1Click(TObject *Sender)
{
   Arbol->FullExpand();
}

// Colapsa el elemento actual
void __fastcall TArbolMemoForm::Colapsa1Click(TObject *Sender)
{
   Arbol->Selected->Collapse(true);        
}

// Expande el elemento actual
void __fastcall TArbolMemoForm::Expande1Click(TObject *Sender)
{
   Arbol->Selected->Expand(true);
}

// Cambia el titulo de un nodo
void __fastcall TArbolMemoForm::Cambiatitulo1Click(TObject *Sender)
{
   Actualiza();
   if (Arbol->Selected) {
      TCaptura1Form *cn = new TCaptura1Form(this);
      cn->Abrir("Edita titulo","Elemento:", Arbol->Selected->Text.c_str(),"Escriba el nuevo nombre de este elemento");
      if (cn->st) Arbol->Selected->Text = cn->Edit1->Text;
      delete cn;
      Modificado = true;
   }
}



void __fastcall TArbolMemoForm::Cortaelemento1Click(TObject *Sender)
{
   Actualiza();
   if (Arbol->Selected) {
      if (MessageBox(Handle,"¿Desea cortar este elemento?",APLICACION,MB_YESNO + MB_ICONQUESTION)  == IDYES) {
          TStrings *ed;
          ed = (TStrings *) Arbol->Selected->Data;
          Datos->Text = ed->Text;
          strcpy(Titulo,Arbol->Selected->Text.c_str());
          delete ed;
          Arbol->Items->Delete(Arbol->Selected);
          Editor->Clear();
          Actual = Arbol->Selected;
          if (Actual) {
             ed = (TStrings *) Actual->Data;
             Editor->Lines->Text = ed->Text;
          }
          Pegar_activo = true;
          Modificado = true;
      }
   }
}

void __fastcall TArbolMemoForm::Copiaelemento1Click(TObject *Sender)
{
   Actualiza();
   if (Arbol->Selected) {
      TStrings *ed = (TStrings *) Arbol->Selected->Data;
      Datos->Text = ed->Text;
      strcpy(Titulo,Arbol->Selected->Text.c_str());
      Pegar_activo = true;
      Modificado = true;
   }
}

// Pega el elemento previamente copoado o cortado
void __fastcall TArbolMemoForm::Pegaelemento1Click(TObject *Sender)
{
   TStrings *ed;
   Actualiza();
   if (Pegar_activo) {
      ed =  new TStringList;
      ed->Text = Datos->Text ;
      Editor->Lines->Text = ed->Text;
      TTreeNode *ts = Arbol->Selected;
      if (ts && ts->getNextSibling()) Arbol->Selected = Arbol->Items->InsertObject(ts->getNextSibling(),Titulo,ed);
       else Arbol->Selected = Arbol->Items->AddObject(ts,Titulo,ed);
      Actual = Arbol->Selected;
      Modificado = true;
   }
}

void __fastcall TArbolMemoForm::Borrarelemento1Click(TObject *Sender)
{
   Actualiza();
   if (Arbol->Selected) {
//      if (Arbol->Selected->HasChildren) {
//          MessageBox(Handle,"¡No se puede borrar un nodo con hijos!",APLICACION,MB_OK + MB_ICONINFORMATION);
//          return;
//      }
      if (MessageBox(Handle,"¿Desea borrar este elemento?",APLICACION,MB_YESNO + MB_ICONQUESTION)  == IDYES) {
         TStrings *ed;
         ed = (TStrings *) Arbol->Selected->Data;
         // Solo borra si hay mas elementos en el arbol
         if (Arbol->Items->Count > 1) {
            BorraNodo(Arbol->Selected);
          } else {
             ed->Text = "";
             Arbol->Selected->Text = "Sin nombre";
         }
         Editor->Clear();
         Actual = Arbol->Selected;
         if (Actual) {
            ed = (TStrings *) Actual->Data;
            Editor->Lines->Text = ed->Text;
         }
         Modificado = true;
      }
   }
}



// Tipo de letra del arbol
void __fastcall TArbolMemoForm::Tipodeletra1Click(TObject *Sender)
{
   FontDialog->Font = Arbol->Font;
   if(FontDialog->Execute()) Arbol->Font = FontDialog->Font;
        
}


// Sortea el contenido del arbol
void __fastcall TArbolMemoForm::Sortea1Click(TObject *Sender)
{
   Actualiza();
   Arbol->SortType = stBoth;
   Arbol->SortType = stNone;
   Modificado = true;
}


// Deshacer
void __fastcall TArbolMemoForm::Deshacer1Click(TObject *Sender)
{
   SendMessage(Editor->Handle,WM_UNDO,0,0);        
}

// Pegar
void __fastcall TArbolMemoForm::Corta1Click(TObject *Sender)
{
   Editor->CutToClipboard();        
}

// Copiar
void __fastcall TArbolMemoForm::Copia1Click(TObject *Sender)
{
   Editor->CopyToClipboard();        
}

// Pegar
void __fastcall TArbolMemoForm::Pegar1Click(TObject *Sender)
{
   Editor->PasteFromClipboard();               
}

// Selecciona todo
void __fastcall TArbolMemoForm::Selecciona1Click(TObject *Sender)
{
   Editor->SelectAll();                
}

// Copia todo
void __fastcall TArbolMemoForm::Copiartodo1Click(TObject *Sender)
{
   Editor->SelectAll();                
   Editor->CopyToClipboard();        
}


// Inserta fecha
void __fastcall TArbolMemoForm::InsertaFechaClick(TObject *Sender)
{
   char fecha[20], fec_esc[50];
   Manipulador_archivos ma;
   Fechas_Horas fh;
   
   fh.Fecha_hoy(fecha);
   fh.Fecha_escrita(fecha, fec_esc, 1, 1);
   ma.Convierte_linea(fec_esc);
   Editor->SetSelTextBuf(fec_esc);
}

// Inserta hora
void __fastcall TArbolMemoForm::InsertaHora1Click(TObject *Sender)
{
   char tiempo[20];
   Manipulador_archivos ma;
   Fechas_Horas fh;
   
   fh.Hora_actual(tiempo, 1, 1);
   fh.Trim(tiempo);
   ma.Convierte_linea(tiempo);
   Editor->SetSelTextBuf(tiempo);
}

// Inserta fecha y hora
void __fastcall TArbolMemoForm::Insertafechayhora1Click(TObject *Sender)
{
   char xcad[100];
   Manipulador_archivos ma;
   Fechas_Horas fh;
   
   fh.Fecha_y_hora(xcad, 1, 1);
   ma.Convierte_linea(xcad);
   Editor->SetSelTextBuf(xcad);
   Spliter->Left = 200;
   Arbol->Width = 200;
   Editor->Left = 204;
}

// Tipo de letra del editor
void __fastcall TArbolMemoForm::Tipodeletra2Click(TObject *Sender)
{
   FontDialog->Font = Editor->Font;
   if(FontDialog->Execute()) Editor->Font = FontDialog->Font;
}



// Acerca de ...
void __fastcall TArbolMemoForm::Acercade1Click(TObject *Sender)
{
   TAcercaDeForm *AcercaDeForm = new TAcercaDeForm(this);
   AcercaDeForm->Muestra_ventana_AcercaDe(APLICACION);
   delete AcercaDeForm;
}


void __fastcall TArbolMemoForm::Longitudfija1Click(TObject *Sender)
{
   if (Editor->WordWrap) {
      // Longitud variable
      Editor->WordWrap = false;
      Editor->ScrollBars = ssBoth;
      Longitudfija1->Caption = "&Longitud de edición fija";
    } else {
      // Longitud fija
      Editor->WordWrap = true;     
      Editor->ScrollBars = ssVertical;
      Longitudfija1->Caption = "&Longitud de edición variable";
   }
}


// Lee un archivo y lo inserta en la actual posicion
void __fastcall TArbolMemoForm::LeeBloqueClick(TObject *Sender)
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
void __fastcall TArbolMemoForm::Convertiramayusculas1Click(TObject *Sender)
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
void __fastcall TArbolMemoForm::Convertiraminusculas1Click(TObject *Sender)
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

// Cuando el arbol es seleccionado por un click del mouse
void __fastcall TArbolMemoForm::ArbolClick(TObject *Sender)
{
   TStrings *ed;
   if (Actual) {
      ed = (TStrings *) Actual->Data;
      ed->Text = Editor->Lines->Text;
      if (Actual != Arbol->Selected) {
//         Editor->Clear();
         Actual = Arbol->Selected;
         ed = (TStrings *) Actual->Data;
         Editor->Lines->Text = ed->Text;
         Editor->Modified = false;
      }
   }
}

// Controla el movimiento dentro del arbol usando las flechas
void __fastcall TArbolMemoForm::ArbolKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
   // Solo flecha arriba y flecha abajo
   if ( Key == '&' || Key == '(') {
      Actualiza();
      TStrings *ed;
      if (Key == '&') {
         if (Arbol->Selected->GetPrevVisible()) { 
//            Editor->Clear();
            Actual = Arbol->Selected->GetPrevVisible();
            ed = (TStrings *) Actual->Data;
            Editor->Lines->Text = ed->Text;
            Editor->Modified = false;
         }
       } else {
         if (Arbol->Selected->GetNextVisible()) { 
//            Editor->Clear();
            Actual = Arbol->Selected->GetNextVisible();
            ed = (TStrings *) Actual->Data;
            Editor->Lines->Text = ed->Text;
            Editor->Modified = false;
         }
      }
   } else Key = 0;
}


// Graba o recupera la configuración de la ventana de trabajo
bool TArbolMemoForm::Configuracion_ventana(const char *arch, const bool st)
{
   int siz, st1 = 0, st2 = 0, st3 = 0, st4 = 0;
   int Asiz, Ast1 = 0, Ast2 = 0, Ast3 = 0, Ast4 = 0, Ast5 = 121;
   bool estatus = true;
   char fnt[100];
   char Afnt[100];
   char xarch[MAXPATH];
   TColor            Color_texto;
   TColor            AColor_texto;

   Manipulador_archivos ma;
   // Cambia la extención del archivo
   ma.Cambia_ext_path(arch,"CFG",xarch);
   
   if (st) {
      // Valores de configuracion por omision
      Color_texto = Editor->Font->Color;
      strcpy(fnt,Editor->Font->Name.c_str());
      siz = Editor->Font->Size;

      AColor_texto = Arbol->Font->Color;
      strcpy(Afnt,Arbol->Font->Name.c_str());
      Asiz = Arbol->Font->Size;

      // lee la configuracion de la ventana
      ifstream lee(xarch,ios::binary);
      if (lee) {
         // Editor
         lee.read((char *)&Color_texto,sizeof(TColor));
         lee.read((char *)&siz,sizeof(siz));
         lee.read((char *)fnt,100);
         lee.read((char *)&st1,sizeof(st1));
         lee.read((char *)&st2,sizeof(st2));
         lee.read((char *)&st3,sizeof(st3));
         lee.read((char *)&st4,sizeof(st4));
         // Arbol
         lee.read((char *)&AColor_texto,sizeof(TColor));
         lee.read((char *)&Asiz,sizeof(Asiz));
         lee.read((char *)Afnt,100);
         lee.read((char *)&Ast1,sizeof(Ast1));
         lee.read((char *)&Ast2,sizeof(Ast2));
         lee.read((char *)&Ast3,sizeof(Ast3));
         lee.read((char *)&Ast4,sizeof(Ast4));
         // Spliter
         lee.read((char *)&Ast5,sizeof(Ast5));
         // Clave de seguridad
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

      // Editor
      Editor->Font->Color = Color_texto;
      Editor->Font->Name = fnt;
      Editor->Font->Size = siz;
      TFontStyles st;
      if (st1) st << fsBold;
      if (st2) st << fsItalic;
      if (st3) st << fsUnderline;
      if (st4) st << fsStrikeOut;
      Editor->Font->Style = st;
      // Arbol
      Arbol->Font->Color = AColor_texto;
      Arbol->Font->Name = Afnt;
      Arbol->Font->Size = Asiz;
      TFontStyles Ast;
      if (Ast1) Ast << fsBold;
      if (Ast2) Ast << fsItalic;
      if (Ast3) Ast << fsUnderline;
      if (Ast4) Ast << fsStrikeOut;
      Arbol->Font->Style = Ast;
      // Spliter
      Spliter->Left = Ast5;
      Arbol->Width = Ast5;
      Editor->Left = Ast5+4;
    } else {
      // Graba la configuracion de la ventana
      ofstream grab(xarch,ios::binary);
      if (grab) {
         // Editor
         Color_texto = Editor->Font->Color;
         siz         = Editor->Font->Size;
         if (Editor->Font->Style.Contains(fsBold)) st1 = 1;
         if (Editor->Font->Style.Contains(fsItalic)) st2 = 1;
         if (Editor->Font->Style.Contains(fsUnderline)) st3 = 1;
         if (Editor->Font->Style.Contains(fsStrikeOut)) st4 = 1;
         // Arbol
         AColor_texto = Editor->Font->Color;
         Asiz         = Editor->Font->Size;
         if (Arbol->Font->Style.Contains(fsBold)) Ast1 = 1;
         if (Arbol->Font->Style.Contains(fsItalic)) Ast2 = 1;
         if (Arbol->Font->Style.Contains(fsUnderline)) Ast3 = 1;
         if (Arbol->Font->Style.Contains(fsStrikeOut)) Ast4 = 1;
         // Editor
         grab.write((char *)&Color_texto,sizeof(TColor));
         grab.write((char *)&siz,sizeof(siz));
         grab.write((char *)Editor->Font->Name.c_str(),100);
         grab.write((char *)&st1,sizeof(st1));
         grab.write((char *)&st2,sizeof(st2));
         grab.write((char *)&st3,sizeof(st3));
         grab.write((char *)&st4,sizeof(st4));
         // Arbol
         grab.write((char *)&AColor_texto,sizeof(TColor));
         grab.write((char *)&Asiz,sizeof(Asiz));
         grab.write((char *)Arbol->Font->Name.c_str(),100);
         grab.write((char *)&Ast1,sizeof(Ast1));
         grab.write((char *)&Ast2,sizeof(Ast2));
         grab.write((char *)&Ast3,sizeof(Ast3));
         grab.write((char *)&Ast4,sizeof(Ast4));
         // Spliter
         Ast5 = Spliter->Left;
         grab.write((char *)&Ast5,sizeof(Ast5));
         grab.write((char *)&Encriptado,sizeof(Encriptado));
         grab.write((char *)&Password,strlen(Password)+1);
         grab.close();
      }                                                        
   }
   return estatus;
}

 
// Auto graba cada 5 minutos
void __fastcall TArbolMemoForm::AutoGraba(TObject *Sender)
{
   if (SaveDialog->FileName != "") Grabar1Click(Sender);
}

// Dialogo de busqueda
void __fastcall TArbolMemoForm::BuscarClick(TObject *Sender)
{
    FindDialog->FindText = Editor->SelText;
    FindDialog->Execute();
}

// Busqueda de texto en el editor
void __fastcall TArbolMemoForm::FindDialogFind(TObject *Sender)
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



void __fastcall TArbolMemoForm::Buscayremplaza1Click(TObject *Sender)
{
    ReplaceDialog->FindText = Editor->SelText;
    ReplaceDialog->Execute();
}


void __fastcall TArbolMemoForm::ReplaceDialogReplace(TObject *Sender)
{
    if (Editor->SelLength == 0) FindDialogFind(Sender);
    else {
        Editor->SelText =  ReplaceDialog->ReplaceText;
        FindDialogFind(Sender);
    }
    if (ReplaceDialog->Options.Contains(frReplaceAll)) {
        while (Editor->SelLength !=0) {
           ReplaceDialogReplace(Sender);
        }
    }
}

// Imprime el contenido actual del editor
void __fastcall TArbolMemoForm::Imprimir1Click(TObject *Sender)
{
   Actualiza();
   Editor->Print(Actual->Text);
}



// Se activa cada segundo
void __fastcall TArbolMemoForm::Timer2Timer(TObject *Sender)
{
   // Revisa que actividades fueron solicitadas
   
   // Generar un nuevo nodo
   if (Genera_nuevo_nodo) {
       Genera_nuevo_nodo = false;
       Editor->Clear();
       AdicionaAbajoClick(Sender);
   }
}

// Configura el color de la ventana del arbol
void __fastcall TArbolMemoForm::Colordelaventanadelrbol1Click(TObject *Sender)
{
   ColorDialog->Color = Arbol->Color;
   if(ColorDialog->Execute()) Arbol->Color = ColorDialog->Color;
}


// Configura el color de la ventana del editor
void __fastcall TArbolMemoForm::Colordelaventandeleditor1Click(TObject *Sender)
{
   ColorDialog->Color = Editor->Color;
   if(ColorDialog->Execute()) Editor->Color = ColorDialog->Color;
}

void TArbolMemoForm::Actualiza_lista(void)
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

void __fastcall TArbolMemoForm::Arch1Click(TObject *Sender)
{
   Abrir_archivo_lista(NombresArchivos[0]);
}

void __fastcall TArbolMemoForm::Arch2Click(TObject *Sender)
{
   Abrir_archivo_lista(NombresArchivos[1]);   
}

void __fastcall TArbolMemoForm::Arch3Click(TObject *Sender)
{
   Abrir_archivo_lista(NombresArchivos[2]);
}

void __fastcall TArbolMemoForm::Arch4Click(TObject *Sender)
{
   Abrir_archivo_lista(NombresArchivos[3]);
}

void TArbolMemoForm::Abrir_archivo_lista(const char *arch)
{
   char xarch[MAXPATH];
   strcpy(xarch,arch);
   
   Actualiza();

   // Graba si el archivo fue modificado
   if (Modificado) {
      int res = MessageBox(Handle,"El archivo actual ha sido cambiado, ¿se graba?",APLICACION,MB_YESNOCANCEL + MB_ICONQUESTION);
      if (res == IDYES) Grabar1Click(this);
      if (res == IDCANCEL) return;
   }
   // Revisa que el archivo exista y pueda ser leido
   if (access(xarch,04) == 0) {
      // Lee el archivo
      LeerArbolMemo(xarch);
   }
   SaveDialog->FileName = xarch;
}

// Solicita la clave de seguridad para el documento actual
void __fastcall TArbolMemoForm::Clavedeseguridad1Click(TObject *Sender)
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
         } else MessageBox(Handle,"Error en la confirmación de la clave","Notas",MB_OK + MB_ICONEXCLAMATION);
      } 
      delete clvseg;
   } else delete clvseg;
}


// Borra el nodo indicado y todos los subnodos
void TArbolMemoForm::BorraNodo(TTreeNode* TreeNode)
{
   TStrings *ed;
   ed = (TStrings *) TreeNode->Data;
   delete ed;
   TreeNode->Data = NULL;
   for(int i = 0; i < TreeNode->Count; i++) BorraNodo(TreeNode->Item[i]);
   TreeNode->Delete();   
}

