#ifndef DIGITS_FRAME_H
#define DIGITS_FRAME_H


#include <wx/wx.h>
#include "DrawPane.h"

//main window
class Frame: public wxFrame {
public:
    Frame(const wxString &title, const wxPoint &pos, const wxSize &size);

private:
    //event handlers
    void OnExit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);

    wxBoxSizer * sizer;
    wxGridSizer * grid;
    DrawPane * drawPane;
    wxStaticText * guessText;
    wxButton * clearButton;
    wxFont * textFont;

    DECLARE_EVENT_TABLE();
};

#endif //DIGITS_FRAME_H
