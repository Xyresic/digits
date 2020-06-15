#ifndef DIGITS_DRAWPANE_H
#define DIGITS_DRAWPANE_H

#include <wx/wx.h>

class DrawPane: public wxPanel {
public:
    DrawPane(wxFrame* parent, const wxSize &size);

    void mouseDown(wxMouseEvent& event);
    void mouseReleased(wxMouseEvent& event);
    void mouseMove(wxMouseEvent& event);

    void paintEvent(wxPaintEvent & evt);
    void paintNow();
    void render(wxDC& dc);

private:
    bool dragging;
    DECLARE_EVENT_TABLE()
};


#endif //DIGITS_DRAWPANE_H
