#ifndef DIGITS_APP_H
#define DIGITS_APP_H


#include <wx/wx.h>
#include "DrawPane.h"

//main app class derived from wxApp
class App: public wxApp {
public:
    virtual bool OnInit(); //parameters upon implementing

    DrawPane * drawPane;
    wxTextCtrl * guessText;
};

#endif //DIGITS_APP_H
