#ifndef DIGITS_DRAWPANE_H
#define DIGITS_DRAWPANE_H

#include <wx/wx.h>

class DrawPane: public wxPanel {
    bool dragging;
public:
    DrawPane(wxFrame* parent, const wxSize &size);

    void mouseDown(wxMouseEvent& event);
    void mouseReleased(wxMouseEvent& event);
    void mouseMove(wxMouseEvent& event);

    void paintEvent(wxPaintEvent & evt);
    void paintNow();

    void render(wxDC& dc);

    DECLARE_EVENT_TABLE()
};


#endif //DIGITS_DRAWPANE_H
