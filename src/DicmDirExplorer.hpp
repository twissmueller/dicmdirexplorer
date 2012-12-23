#ifndef DicmDirExplorer_HPP
#define DicmDirExplorer_HPP

#include "wx/wx.h" 

class DicmDirExplorer: public wxApp
{
    virtual bool OnInit();
};

IMPLEMENT_APP(DicmDirExplorer)

#endif // DicmDirExplorer_HPP