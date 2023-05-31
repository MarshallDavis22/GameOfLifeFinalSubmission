#ifndef DRAWINGPANEL_H
#define DRAWINGPANEL_H

#endif

#include <wx/wx.h>
#include <wx/dcbuffer.h>

class DrawingPanel : public wxPanel
{
public:
    DrawingPanel(wxWindow* parent);

    void SetGameBoard(const std::vector<std::vector<bool>>& board);

private:
    std::vector<std::vector<bool>> gameBoard;

    void OnPaint(wxPaintEvent& event);

    wxDECLARE_EVENT_TABLE();
};
