#include "Frame.h"
#include <string>

Frame::Frame(const wxString& title, const wxPoint& pos, const wxSize&size) : wxFrame(NULL, wxID_ANY, title, pos, size) {
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
    clearButton = new wxButton((wxFrame*) this, CLEAR_ID, "Clear drawing");

    //number button grid
    numberGrid = new wxGridSizer(4, 3, 2, 2);
    for (int i = 3; i >= 1; i--) {
        for (int j = (3 * i - 2); j <= 3 * i; j++) {
            wxButton *button = new wxButton((wxFrame*) this, wxID_HIGHEST + j + 100, std::to_string(j));
            numberGrid->Add(button, 1);
        }
    }

    wxButton *zeroButton = new wxButton((wxFrame*) this, wxID_HIGHEST + 100, "0");
    wxPanel *panel = new wxPanel((wxFrame*) this, -1);
    numberGrid->Add(panel, 1);
    numberGrid->Add(zeroButton, 1);

    //grid layout of components
    grid = new wxGridSizer(2, 2, 5, 5);
    grid->Add(drawPane, 1, wxEXPAND);
    grid->Add(guessText, 1, wxEXPAND);
    grid->Add(clearButton, 1);
    grid->Add(numberGrid, 1);
    this->SetSizer(grid);
    this->SetBackgroundColour(wxColour(255, 255, 255));
    this->Show(true);
}

void Frame::onExit(wxCommandEvent& event) {
    Close(true);
}

void Frame::onAbout(wxCommandEvent& event) {
    wxMessageBox("This is a program to read and identify digits.", "About", wxOK | wxICON_INFORMATION);
}

void Frame::onClear(wxCommandEvent& event) {
    drawPane->clearPaint();
}

//mapping ids to frame events
BEGIN_EVENT_TABLE(Frame, wxFrame)
    EVT_MENU(wxID_EXIT, Frame::onExit)
    EVT_MENU(wxID_ABOUT, Frame::onAbout)
    EVT_BUTTON(CLEAR_ID, Frame::onClear)
END_EVENT_TABLE()
