/***************************************************************
 * Name:      DecKDXApp.cpp
 * Purpose:   Code for Application Class
 * Author:    David Stancu (davidstancu@gmail.com)
 * Created:   2012-07-09
 * Copyright: David Stancu (http://davidstancu.me)
 * License:
 **************************************************************/

#include "DecKDXApp.h"

//(*AppHeaders
#include "DecKDXMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(DecKDXApp);

bool DecKDXApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	DecKDXDialog Dlg(0);
    	SetTopWindow(&Dlg);
    	Dlg.ShowModal();
    	wxsOK = false;
    }
    //*)
    return wxsOK;

}
