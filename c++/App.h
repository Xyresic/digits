#ifndef DIGITS_APP_H
#define DIGITS_APP_H


#include <wx/wx.h>
#include "DrawPane.h"

//main app class derived from wxApp
class App: public wxApp {
public:
    virtual bool OnInit(); //parameters upon implementing

    wxBoxSizer * sizer;
    wxGridSizer * grid;
    DrawPane * drawPane;
    wxStaticText * guessText;
    wxFont * textFont;
};

#endif //DIGITS_APP_H
