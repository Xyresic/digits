#ifndef DIGITS_FRAME_H
#define DIGITS_FRAME_H


#include <wx/wx.h>
#include "DrawPane.h"

//main window
class Frame: public wxFrame {
public:
    Frame(const wxString &title, const wxPoint &pos, const wxSize &size);

private:
    void onExit(wxCommandEvent &event);
    void onAbout(wxCommandEvent &event);

    wxGridSizer *numberGrid;
    DrawPane *drawPane;
    wxStaticText *guessText;
    wxButton *clearButton;
    wxFont *textFont;

    //for drawing
    void onClear(wxCommandEvent &event);
    void onGuess(wxCommandEvent &event);

    enum {CLEAR_ID = wxID_HIGHEST + 98};
    enum {GUESS_ID = wxID_HIGHEST + 99};

    //for training the neural network
    void onZero(wxCommandEvent &event);
    void onOne(wxCommandEvent &event);
    void onTwo(wxCommandEvent &event);
    void onThree(wxCommandEvent &event);
    void onFour(wxCommandEvent &event);
    void onFive(wxCommandEvent &event);
    void onSix(wxCommandEvent &event);
    void onSeven(wxCommandEvent &event);
    void onEight(wxCommandEvent &event);
    void onNine(wxCommandEvent &event);

DECLARE_EVENT_TABLE();
};

#endif //DIGITS_FRAME_H
