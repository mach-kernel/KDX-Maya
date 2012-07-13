/***************************************************************
 * Name:      DecKDXMain.h
 * Purpose:   Defines Application Frame
 * Author:    David Stancu (davidstancu@gmail.com)
 * Created:   2012-07-09
 * Copyright: David Stancu (http://davidstancu.me)
 * License:
 **************************************************************/

#ifndef DECKDXMAIN_H
#define DECKDXMAIN_H

//(*Headers(DecKDXDialog)
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

class DecKDXDialog: public wxDialog
{
    public:

        DecKDXDialog(wxWindow* parent,wxWindowID id = -1);
        virtual ~DecKDXDialog();

    private:

        //(*Handlers(DecKDXDialog)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OndecBTNClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(DecKDXDialog)
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT3;
        static const long ID_STATICTEXT2;
        static const long ID_TEXTCTRL2;
        static const long ID_TEXTCTRL1;
        static const long ID_BUTTON1;
        static const long ID_CHECKBOX1;
        static const long ID_STATICTEXT4;
        //*)

        //(*Declarations(DecKDXDialog)
        wxStaticText* StaticText2;
        wxStaticText* StaticText1;
        wxStaticText* StaticText3;
        wxCheckBox* dumpChk;
        wxTextCtrl* encBox;
        wxTextCtrl* decBox;
        wxStaticText* StaticText4;
        wxButton* decBTN;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // DECKDXMAIN_H
