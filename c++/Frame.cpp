#include "Frame.h"

Frame::Frame(const wxString& title, const wxPoint& pos, const wxSize&size)
        : wxFrame(NULL, wxID_ANY, title, pos, size) {
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(wxID_EXIT);

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);
    CreateStatusBar();

    //drawing canvas
    drawPane = new DrawPane((wxFrame*) this, wxSize(400,400));

    //guess area
    guessText = new wxStaticText((wxFrame*) this, -1, "Guess: ", wxPoint(300, 0), wxSize(300, 200));
    textFont = new wxFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    guessText->SetFont(*textFont);

    //button to clear drawing
    clearButton = new wxButton((wxFrame*) this, -1, "Clear drawing");

    //grid layout of components
    grid = new wxGridSizer(2, 2, 0, 0);
    grid->Add(drawPane, 1, wxEXPAND);
    grid->Add(guessText, 1);
    grid->Add(clearButton, 1);
    sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(grid, 1, wxEXPAND);
    this->SetSizer(grid);
    this->Show(true);
}

//mapping ids to frame events
BEGIN_EVENT_TABLE(Frame, wxFrame)
    EVT_MENU(wxID_EXIT, Frame::OnExit)
    EVT_MENU(wxID_ABOUT, Frame::OnAbout)
END_EVENT_TABLE()

void Frame::OnExit(wxCommandEvent& event) {
    Close(true);
}

void Frame::OnAbout(wxCommandEvent& event) {
    wxMessageBox("This is a program to read and identify digits.", "About", wxOK | wxICON_INFORMATION);
}