#ifndef DIGITS_DRAWPANE_H
#define DIGITS_DRAWPANE_H

#include <wx/wx.h>

class DrawPane: public wxPanel {
public:
    DrawPane(wxFrame* parent, const wxPoint& pos, const wxSize &size);

    void mouseDown(wxMouseEvent& event);
    void mouseReleased(wxMouseEvent& event);
    void mouseMove(wxMouseEvent& event);

    void paintEvent(wxPaintEvent& event);
    void paintNow();
    void render(wxDC& dc);
    void clearPaint();

private:
    bool dragging;
    wxClientDC drawDC;
    DECLARE_EVENT_TABLE()
};


#endif //DIGITS_DRAWPANE_H
