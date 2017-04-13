// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Dirección: Amsterdam 312 col. Hipodromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#include <vcl.h>
#include <extctrls.hpp>
#include <filectrl.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "d:\Libreria\fechas.hpp"
#include "d:\Libreria\tiempo.hpp"
#pragma hdrstop

#include "D:\Libreria\Formas\Pendient.h"
#include "d:\Libreria\Formas\AcercaDe.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

#define APLICACION "OUTLINE"

__fastcall TOutlineForm::TOutlineForm(TComponent* Owner)
        : TForm(Owner)
{
   Arbol->SortType = stNone;
}


void __fastcall TOutlineForm::MSalirClick(TObject *Sender)
{
   Close();        
}

/*
void __fastcall TForm1::Button1Click(TObject *Sender)

{
	//Adds a root node
	TreeView1->Items->Add(TreeView1->Selected, "RootTreeNode1");

	//Sets MyTreeNode to first node in
	//tree view and adds a child node to it
	TTreeNode *MyTreeNode1 = TreeView1->Items->Item[0];
	TreeView1->Items->AddChild(MyTreeNode1,"ChildNode1");

	//Adds a root node
	TreeView1->Items->Add(TreeView1->Selected, "RootTreeNode2");

	//Sets MyTreeNode to third node in
	//tree view and adds a child node to it
	TTreeNode *MyTreeNode2 = TreeView1->Items->Item[2];

TreeView1->Items->AddChild(MyTreeNode2,"ChildNode2");

	//Sets MyTreeNode to fourth node in
	//tree view and adds a child node to it
	MyTreeNode2=TreeView1->Items->Item[3];
	TreeView1->Items->AddChild(MyTreeNode2,"ChildNode2a");

	//Sets MyTreeNode to fifth node in
	//tree view and adds a child node to it
	MyTreeNode2 = TreeView1->Items->Item[4];
	TreeView1->Items->Add(MyTreeNode2,"ChildNode2b");

	//add another root node
	TreeView1->Items->Add(TreeView1->Selected, "RootTreeNode3");

}

/// borrar
void __fastcall TForm1::TreeView1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)

{
  THitTests HT;

if (CheckBox1->Checked and Sender->ClassNameIs("TTreeView"))
{
  TTreeView *pTV = (TTreeView *)Sender;
  HT = pTV->GetHitTestInfoAt(X,Y);
  if (HT.Contains(htOnItem))
    pTV->Items->Delete(pTV->GetNodeAt(X,Y));
}


*/













/*
 // first add a directory list box to the form
  TDirectoryListBox *Dirs = new TDirectoryListBox(this);
  // align it on the left of the form
  Dirs->Parent = this;
  Dirs->Align = alLeft;

  // now add the splitter to divide the directory pane

  // from the file pane 

  TSplitter *Split = new TSplitter(this);

  Split->Parent = this;

  // make sure the splitter is to the right 
  // of the directory list box! 

  Split->Left = Dirs->Left + Dirs->Width + 1;

  Split->Align = Dirs->Align; // give it the same alignment as the directory 

  // each pane must be at least one quarter of the form’s width
  Split->MinSize = Form1->ClientWidth / 4;
  // Finally, create the last pane – a file list box 

  TFileListBox *Files = new TFileListBox(this);
  Files->Parent = this;
  Files->Align = alClient;
  Dirs->FileList = Files; // link the file list box to the directory list box
*/        

// Tipo de letra del arbol
void __fastcall TOutlineForm::Tipodeletra1Click(TObject *Sender)
{
   FontDialog->Font = Arbol->Font;
   if(FontDialog->Execute()) Arbol->Font = FontDialog->Font;
        
}

// Tipo de letra del editor
void __fastcall TOutlineForm::Tipodeletra2Click(TObject *Sender)
{
   FontDialog->Font = Editor->Font;
   if(FontDialog->Execute()) Editor->Font = FontDialog->Font;
}

// Sortea el contenido del arbol
void __fastcall TOutlineForm::Sortea1Click(TObject *Sender)
{
   Arbol->SortType = stBoth;
   Arbol->SortType = stNone;
}

// Deshacer
void __fastcall TOutlineForm::Deshacer1Click(TObject *Sender)
{
   SendMessage(Editor->Handle,WM_UNDO,0,0);        
        
}

// Pegar
void __fastcall TOutlineForm::Corta1Click(TObject *Sender)
{
   Editor->CutToClipboard();        
}

// Copiar
void __fastcall TOutlineForm::Copia1Click(TObject *Sender)
{
   Editor->CopyToClipboard();        
}

// Pegar
void __fastcall TOutlineForm::Pega1Click(TObject *Sender)
{
   Editor->PasteFromClipboard();               
}

// Selecciona todo
void __fastcall TOutlineForm::Seleccionatodo1Click(TObject *Sender)
{
   Editor->SelectAll();                
}

// Inserta fecha
void __fastcall TOutlineForm::InsertaFechaClick(TObject *Sender)
{
   char fecha[20], fec_esc[50];
   Fechas f;
   f.Fecha_hoy(fecha);
   f.f_fecha_escrita(fecha, fec_esc, 1, 1);
   Editor->SetSelTextBuf(fec_esc);
}

// Inserta hora
void __fastcall TOutlineForm::InsertaHora1Click(TObject *Sender)
{
   char tiempo[20];
   Tiempo t;
   t.Hora_actual(tiempo, 1, 1);
   t.Trim(tiempo);
   Editor->SetSelTextBuf(tiempo);
}

// Inserta fecha y hora
void __fastcall TOutlineForm::Insertafechayhora1Click(TObject *Sender)
{
   char fecha[20], tiempo[20], xcad[100], fec_esc[50];
   Tiempo t;
   Fechas f;

   f.Fecha_hoy(fecha);
   f.f_fecha_escrita(fecha, fec_esc, 1, 1);
   t.Hora_actual(tiempo, 1, 1);
   t.Trim(tiempo);

   sprintf(xcad,"%s %s",fec_esc,tiempo);
   Editor->SetSelTextBuf(xcad);
}


// Acerca de ...
void __fastcall TOutlineForm::Acercade1Click(TObject *Sender)
{
   TAcercaDeForm *AcercaDeForm = new TAcercaDeForm(this);
   AcercaDeForm->Muestra_ventana_AcercaDe(APLICACION);
   delete AcercaDeForm;
}

