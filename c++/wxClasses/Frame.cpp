#include "Frame.h"
#include <windows.h>
#include <string>

Frame::Frame(const wxString& title, const wxPoint& pos, const wxSize& size): wxFrame(NULL, wxID_ANY, title, pos, size) {
    //standard menu components
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
    drawPane = new DrawPane((wxFrame*) this, wxDefaultPosition, wxSize(300,300));

    //guess area
    guessText = new wxStaticText((wxFrame*) this, -1, "Guess: ", wxPoint(300, 0), wxSize(300, 200));
    textFont = new wxFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    guessText->SetFont(*textFont);

    //button to clear drawing
    clearButton = new wxButton((wxFrame*) this, CLEAR_ID, "Clear drawing");

    //button to guess the number
    wxButton *guessButton = new wxButton((wxFrame*) this, GUESS_ID, "Guess");

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

    //master layout of all components
    wxBoxSizer *controlSizer = new wxBoxSizer(wxHORIZONTAL);
    controlSizer->Add(clearButton);
    controlSizer->Add(guessButton);

    wxFlexGridSizer *leftColumn = new wxFlexGridSizer(2, 1, 0, 0);
    leftColumn->Add(drawPane, 1);
    leftColumn->Add(controlSizer, 1, wxEXPAND);

    wxFlexGridSizer *rightColumn = new wxFlexGridSizer(2, 1, 0, 0);
    rightColumn->Add(guessText, 1);
    rightColumn->Add(numberGrid, 1);

    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(leftColumn, 1);
    sizer->Add(rightColumn, 1);

    this->SetSizer(sizer);
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

void Frame::onGuess(wxCommandEvent& event) {
    HWND window = ::FindWindowA(NULL, "digits");
    HDC dc = ::GetDC(window);
    HDC compDC = ::CreateCompatibleDC(dc);
    HBITMAP bitmap = ::CreateCompatibleBitmap(dc, drawPane->GetSize().GetWidth(), drawPane->GetSize().GetHeight());
    ::SelectObject(compDC, bitmap);
    ::BitBlt(compDC, 0, 0, drawPane->GetSize().GetWidth(), drawPane->GetSize().GetHeight(), dc, 0, 0, SRCCOPY);
    COLORREF *pixelPtrArray[drawPane->GetSize().GetWidth() * drawPane->GetSize().GetHeight()];
    for (int x = 0; x < drawPane->GetSize().GetWidth(); x++) {
        for (int y = 0; y < drawPane->GetSize().GetHeight(); y++) {
            COLORREF pixel = ::GetPixel(compDC, x, y);
            COLORREF *ptr = &pixel;
            pixelPtrArray[x * 300 + y] = ptr;
        }
    }

    ::DeleteDC(compDC);
    ::DeleteObject(bitmap);
}

//mapping ids to frame events
BEGIN_EVENT_TABLE(Frame, wxFrame)
    EVT_MENU(wxID_EXIT, Frame::onExit)
    EVT_MENU(wxID_ABOUT, Frame::onAbout)
    EVT_BUTTON(CLEAR_ID, Frame::onClear)
    EVT_BUTTON(GUESS_ID, Frame::onGuess)
END_EVENT_TABLE()
