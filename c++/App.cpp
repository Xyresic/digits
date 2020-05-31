#include "App.h"
#include "Frame.h"
#include "DrawPane.h"

bool App::OnInit() {
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    Frame *frame = new Frame("digits", wxPoint(50, 50), wxSize(400, 400));

    drawPane = new DrawPane((wxFrame*) frame);
    sizer->Add(drawPane, 1, wxEXPAND);

    frame->SetSizer(sizer);
    frame->SetAutoLayout(true);

    frame->Show(true);
    return true;
}