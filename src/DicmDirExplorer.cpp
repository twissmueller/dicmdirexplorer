#include "DicmDirExplorer.hpp"

#include "MainFrame.hpp"

bool DicmDirExplorer::OnInit()
{
    MainFrame *frame = new MainFrame( "DicmDirExplorer", wxPoint(50,50), wxSize(1000,600) );
    frame->Show(TRUE);
    SetTopWindow(frame);
    return TRUE;
} 

