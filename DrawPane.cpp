#include "DrawPane.h"

BEGIN_EVENT_TABLE(DrawPane, wxPanel)
    EVT_LEFT_DOWN(DrawPane::mouseDown)
    EVT_LEFT_UP(DrawPane::mouseReleased)
    EVT_PAINT(DrawPane::paintEvent)
END_EVENT_TABLE()

void DrawPane::mouseDown(wxMouseEvent& event) {
    pressedDown = true;
    paintNow();
}

void DrawPane::mouseReleased(wxMouseEvent& event) {
    pressedDown = false;
}

DrawPane::DrawPane(wxFrame* parent): wxPanel(parent) {
    pressedDown = false;
}

void DrawPane::paintEvent(wxPaintEvent & evt) {
    wxPaintDC dc(this);
    render(dc);
}

void DrawPane::paintNow() {
    wxClientDC dc(this);
    render(dc);
}

void DrawPane::render(wxDC& dc) {
    while (pressedDown) {
        wxPoint pt = wxGetMousePosition();
        int mouseX = pt.x;
        int mouseY = pt.y;

        dc.SetPen(wxPen(wxColor(0,0,0), 5));
        dc.DrawLine(mouseX, mouseY, mouseX, mouseY);
    }
}
