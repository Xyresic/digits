#include "App.h"
#include "Frame.h"

bool App::OnInit() {
    sizer = new wxBoxSizer(wxVERTICAL);
    grid = new wxGridSizer(1, 2, 0, 0);
    Frame *frame = new Frame("digits", wxPoint(50,50), wxSize(600,600));

    //drawing canvas
    drawPane = new DrawPane((wxFrame*) frame, wxSize(400,400));
    guessText = new wxStaticText((wxFrame*) frame, -1, "Guess: ", wxPoint(300, 0), wxSize(300, 200));

    grid->Add(drawPane, 1, wxEXPAND);
    grid->Add(guessText, 1);

    sizer->Add(grid, 1, wxEXPAND);
    frame->SetSizer(grid);
    frame->Show(true);

    return true;
}