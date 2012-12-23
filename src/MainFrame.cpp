#include "MainFrame.hpp"

#include "DirWxTreeCtrl.hpp"
#include "DcmObjectWxListCtrl.hpp"
#include "DcmtkBuilder.hpp"
#include "DicomLibException.hpp"

#include <wx/splitter.h>

#include <sstream>

enum
{
	ID_File_Open = 1,
    ID_File_Quit = 2,
    ID_Help_About = 3,
};

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_MENU(ID_File_Open, MainFrame::OnFileOpen)
    EVT_MENU(ID_File_Quit, MainFrame::OnFileQuit)
    EVT_MENU(ID_Help_About, MainFrame::OnHelpAbout)
END_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame((wxFrame *)NULL, -1, title, pos, size)
{	
	// Create the menus
    wxMenu *menuFile = new wxMenu;
	wxMenu *menuHelp = new wxMenu;

    menuFile->Append( ID_File_Open, "&Open..." );
    menuFile->AppendSeparator();
    menuFile->Append( ID_File_Quit, "E&xit" );

	menuHelp -> Append( ID_Help_About, "&About...");

	// Create the menubar
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, "&File" );
	menuBar->Append( menuHelp, "&Help" );

    SetMenuBar( menuBar );

	// Create the statusbar
    CreateStatusBar();
    SetStatusText( "Welcome to DicmDirExplorer!" );

	// Create the window that splits the main views
	wxSplitterWindow* splitter = new wxSplitterWindow(this);

	// Create the main views
	treeView = new DirWxTreeCtrl(splitter, DirTree_Ctrl,
								 wxDefaultPosition, wxDefaultSize, wxTR_HAS_BUTTONS);
	dumpView = new DcmObjectWxListCtrl(splitter);

	// Tell the splitter how to split
	splitter->SplitVertically(treeView, dumpView, 270);

	treeView -> setDumpView(dumpView);
}

void MainFrame::OnFileOpen(wxCommandEvent& WXUNUSED(event))
{
	wxFileDialog* openDlg = new wxFileDialog(this, "Open a DICOM file", "", "", "",
											 wxOPEN, wxDefaultPosition);

	if (openDlg->ShowModal() == wxID_OK)
	{
		try
		{
			DcmtkBuilder dbuilder;
			dbuilder.setFilename(openDlg->GetPath().c_str());
			treeView -> setData(dbuilder.getDicomDirPtr());
			SetStatusText( "Please wait!" );
			treeView -> createView();
			SetStatusText( "Finished!" );
		}
		catch (DicomLibException& e)
		{
			std::stringstream tmp;
			tmp << e.what() << std::endl << "File: " << e.file() << std::endl << "Line: " << e.line();
			wxMessageBox(tmp.str().c_str() , "Exception error!", wxOK | wxICON_INFORMATION, this);
		}
		catch (...)
		{
			throw;
		}
	}

	openDlg -> Destroy();
}

void MainFrame::OnFileQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(TRUE);
}

void MainFrame::OnHelpAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox("DicmDirExplorer by Tobias Wissmueller",
        "About DicmDirExplorer", wxOK | wxICON_INFORMATION, this);
}

