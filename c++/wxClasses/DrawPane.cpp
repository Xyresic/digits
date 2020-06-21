#include "DrawPane.h"

DrawPane::DrawPane(wxFrame* parent, const wxPoint& pos, const wxSize &size): wxPanel(parent, wxID_ANY, pos, size), drawDC(this) {
    dragging = false;
    this->SetBackgroundColour(wxColour(240, 240, 240));
}

void DrawPane::mouseDown(wxMouseEvent& event) {
    dragging = true;
    paintNow();
}

void DrawPane::mouseReleased(wxMouseEvent& event) {
    dragging = false;
}

void DrawPane::mouseMove(wxMouseEvent& event) {
    if (dragging) {
        paintNow();
    }
}

void DrawPane::paintEvent(wxPaintEvent& event) {
    wxPaintDC dc(this);
}

void DrawPane::paintNow() {
    render(drawDC);
}

void DrawPane::render(wxDC& dc) {
    wxPoint pt = wxGetMousePosition();
    int mouseX = pt.x - this->GetScreenPosition().x;
    int mouseY = pt.y - this->GetScreenPosition().y;

    dc.SetPen(wxPen(wxColor(0,0,0), 5));
    dc.DrawLine(mouseX, mouseY, mouseX, mouseY);
}

void DrawPane::clearPaint() {
    drawDC.Clear();
}

BEGIN_EVENT_TABLE(DrawPane, wxPanel)
    EVT_LEFT_DOWN(DrawPane::mouseDown)
    EVT_LEFT_UP(DrawPane::mouseReleased)
    EVT_MOTION(DrawPane::mouseMove)
    EVT_PAINT(DrawPane::paintEvent)
END_EVENT_TABLE()