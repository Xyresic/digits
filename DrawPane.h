#ifndef DIGITS_DRAWPANE_H
#define DIGITS_DRAWPANE_H

#include <wx/wx.h>

class DrawPane: public wxPanel {
public:
    DrawPane(wxFrame* parent);

    void paintEvent(wxPaintEvent & evt);
    void paintNow();

    void render(wxDC& dc);

    void mouseDown(wxMouseEvent& event);
    void mouseReleased(wxMouseEvent& event);

    DECLARE_EVENT_TABLE()

private:
    bool pressedDown;
};


#endif //DIGITS_DRAWPANE_H
