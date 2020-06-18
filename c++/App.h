#ifndef DIGITS_APP_H
#define DIGITS_APP_H


#include <wx/wx.h>

//main app class derived from wxApp
class App: public wxApp {
public:
    virtual bool OnInit();
};

#endif //DIGITS_APP_H
