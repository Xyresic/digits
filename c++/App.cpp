#include "App.h"
#include "Frame.h"

bool App::OnInit() {
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    Frame *frame = new Frame("digits", wxPoint(50,50), wxSize(600,600));

    //drawing canvas
    drawPane = new DrawPane((wxFrame*) frame, wxSize(400,400));

    guessText = new wxTextCtrl((wxFrame*) frame, -1, "Guess: ", wxPoint(450, 300), wxSize(300, 20));
    sizer->Add(drawPane, 1, wxEXPAND);
    sizer->Add(guessText, 1);

    frame->SetSizer(sizer);
    frame->SetAutoLayout(true);

    frame->Show(true);
    return true;
}