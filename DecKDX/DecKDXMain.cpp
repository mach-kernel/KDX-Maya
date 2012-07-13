/***************************************************************
 * Name:      DecKDXMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    David Stancu (davidstancu@gmail.com)
 * Created:   2012-07-09
 * Copyright: David Stancu (http://davidstancu.me)
 * License:
 **************************************************************/

#include "DecKDXMain.h"
#include <wx/msgdlg.h>

// algorithm

#include "kdxalgo.h"
#include <stdio.h>
#include <cstring>
#include <iostream>
#include <iterator>
#include <sstream>

//(*InternalHeaders(DecKDXDialog)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat
{
    short_f, long_f
};

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(DecKDXDialog)
const long DecKDXDialog::ID_STATICTEXT1 = wxNewId();
const long DecKDXDialog::ID_STATICTEXT3 = wxNewId();
const long DecKDXDialog::ID_STATICTEXT2 = wxNewId();
const long DecKDXDialog::ID_TEXTCTRL2 = wxNewId();
const long DecKDXDialog::ID_TEXTCTRL1 = wxNewId();
const long DecKDXDialog::ID_BUTTON1 = wxNewId();
const long DecKDXDialog::ID_CHECKBOX1 = wxNewId();
const long DecKDXDialog::ID_STATICTEXT4 = wxNewId();
//*)

BEGIN_EVENT_TABLE(DecKDXDialog,wxDialog)
    //(*EventTable(DecKDXDialog)
    //*)
END_EVENT_TABLE()

DecKDXDialog::DecKDXDialog(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(DecKDXDialog)
    Create(parent, wxID_ANY, _("DecKDX v.7132012"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(492,360));
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("DecKDX v.7132012"), wxPoint(144,16), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    wxFont StaticText1Font(16,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    StaticText1->SetFont(StaticText1Font);
    StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Encrypted Packet (Hex):"), wxPoint(24,64), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Decrypted Packet (ASCII):"), wxPoint(24,176), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    encBox = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxPoint(24,88), wxSize(440,72), wxTE_MULTILINE, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    decBox = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxPoint(24,200), wxSize(440,72), wxTE_MULTILINE, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    decBTN = new wxButton(this, ID_BUTTON1, _("Decrypt!"), wxPoint(208,304), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    dumpChk = new wxCheckBox(this, ID_CHECKBOX1, _("Also export to \'dump.txt\' in same dir as program\?"), wxPoint(24,280), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    dumpChk->SetValue(false);
    StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Algorithm (C) Luigi Auriemma 2007. Program (C) David Stancu 2012."), wxPoint(88,336), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    Center();

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DecKDXDialog::OndecBTNClick);
    //*)
}

DecKDXDialog::~DecKDXDialog()
{
    //(*Destroy(DecKDXDialog)
    //*)
}

void DecKDXDialog::OnQuit(wxCommandEvent& event)
{
    Close();
}

void DecKDXDialog::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

std::istream & ReadIntoString (std::istream & istr, std::string & str)
{
    std::istreambuf_iterator<char> it(istr), end;
    std::copy(it, end, std::inserter(str, str.begin()));
    return istr;
}

void DecKDXDialog::OndecBTNClick(wxCommandEvent& event)
{
    wxString encString = encBox->GetValue();

    // Convert to iss parseable format
    if (encString.Contains(_(":")))
    {
        encString.Replace(_(":"), _(" 0x"));
        encString.Prepend(_(" 0x"));
        encBox->SetValue(encString);
    }

    // Go to std::string since wxString is annoying as shit
    std::string stencString = std::string(encString.mb_str());
    // Going to hold our uchar array, except in string format
    std::string buffer;
    std::istringstream in( stencString );
    in >> std::hex;
    std::copy( std::istream_iterator<int>( in ), std::istream_iterator<int>(), std::back_inserter( buffer ) );
    // Length is needed for writing file and some part of decryption (see kdxalgo.h)
    int length = int(buffer.length());
    unsigned char *buff = new unsigned char[length + 1];
    // Convert to uchar[]
    memcpy(buff, buffer.c_str(), length + 1);

    // Decryption is done below
    int key;
    key = ntohl(*(int *)buff);
    key = kdx_crypt(key, buff + 4, length - 4);

    // Output to textbox
    // TODO: Stops when hits whitespace, must fix for great internet justice.
    std::string outStr;
    // I'm an asshole buffer overflow risk etc :(
    sprintf((char*)outStr.c_str(), "%s", buff);
    decBox->SetValue(wxString(outStr.c_str(), wxConvUTF8));

    // Write file if checked
    if(dumpChk->IsChecked() == true)
    {
        FILE* f1 = fopen("dump.txt", "w");
        fwrite(buff, 1, length, f1);  // mother always said, output your shit, son.
        fclose(f1);
    }
}

