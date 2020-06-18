#include "App.h"
#include "Frame.h"

bool App::OnInit() {
    Frame *frame = new Frame("digits", wxPoint(50,50), wxSize(600,600));
    return true;
}