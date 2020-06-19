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
    void onExit(wxCommandEvent &event);
    void onAbout(wxCommandEvent &event);
    void onClear(wxCommandEvent &event);

    wxGridSizer *grid;
    wxGridSizer *numberGrid;
    DrawPane *drawPane;
    wxStaticText *guessText;
    wxButton *clearButton;
    wxFont *textFont;

    enum {CLEAR_ID = wxID_HIGHEST + 98};
    enum {GUESS_ID = wxID_HIGHEST + 99};

DECLARE_EVENT_TABLE();
};

#endif //DIGITS_FRAME_H
