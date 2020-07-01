#include <string>
#include <iostream>

#include "Frame.h"
#include "../Neural_Network/Network.h"

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
    int width = drawPane->GetSize().GetWidth() / 10;
    int height = drawPane->GetSize().GetHeight() / 10;
    double pixelArray[width * height];
    wxColour *colorPtr = new wxColour;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double sum = 0;
            for (int x = j * 10; x < j * 10 + 10; x++) {
                for (int y = i * 10; y < i * 10 + 10; y++) {
                    drawPane->drawDC.GetPixel(x, y, colorPtr);
                    sum += colorPtr->GetRGB();
                }
            }
            sum = (15790320 - (sum / 100)) / 15790320;
            pixelArray[i * width + j] = sum;
        }
    }
    delete colorPtr;
    run_network(pixelArray);
}

void Frame::onZero(wxCommandEvent &event) {

}

void Frame::onOne(wxCommandEvent &event) {

}

void Frame::onTwo(wxCommandEvent &event) {

}

void Frame::onThree(wxCommandEvent &event) {

}

void Frame::onFour(wxCommandEvent &event) {

}

void Frame::onFive(wxCommandEvent &event) {

}

void Frame::onSix(wxCommandEvent &event) {

}

void Frame::onSeven(wxCommandEvent &event) {

}

void Frame::onEight(wxCommandEvent &event) {

}

void Frame::onNine(wxCommandEvent &event) {

}


//mapping ids to frame events
BEGIN_EVENT_TABLE(Frame, wxFrame)
    EVT_MENU(wxID_EXIT, Frame::onExit)
    EVT_MENU(wxID_ABOUT, Frame::onAbout)
    EVT_BUTTON(CLEAR_ID, Frame::onClear)
    EVT_BUTTON(GUESS_ID, Frame::onGuess)
    EVT_BUTTON(wxID_HIGHEST + 100, Frame::onZero)
    EVT_BUTTON(wxID_HIGHEST + 101, Frame::onOne)
    EVT_BUTTON(wxID_HIGHEST + 102, Frame::onTwo)
    EVT_BUTTON(wxID_HIGHEST + 103, Frame::onThree)
    EVT_BUTTON(wxID_HIGHEST + 104, Frame::onFour)
    EVT_BUTTON(wxID_HIGHEST + 105, Frame::onFive)
    EVT_BUTTON(wxID_HIGHEST + 106, Frame::onSix)
    EVT_BUTTON(wxID_HIGHEST + 107, Frame::onSeven)
    EVT_BUTTON(wxID_HIGHEST + 108, Frame::onEight)
    EVT_BUTTON(wxID_HIGHEST + 109, Frame::onNine)
END_EVENT_TABLE()
