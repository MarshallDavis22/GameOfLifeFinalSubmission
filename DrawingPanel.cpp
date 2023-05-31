#include "DrawingPanel.h"
#include <wx/dcclient.h>

wxBEGIN_EVENT_TABLE(DrawingPanel, wxPanel)
EVT_PAINT(DrawingPanel::OnPaint)
wxEND_EVENT_TABLE()

DrawingPanel::DrawingPanel(wxWindow* parent) : wxPanel(parent)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);
}

void DrawingPanel::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);
    wxSize size = GetSize();

    int width = size.GetWidth();
    int height = size.GetHeight();

    int cellWidth = width / gameBoard[0].size();
    int cellHeight = height / gameBoard.size();

    for (int row = 0; row < gameBoard.size(); row++)
    {
        for (int col = 0; col < gameBoard[row].size(); col++)
        {
            if (gameBoard[row][col])
                dc.SetBrush(*wxBLACK_BRUSH);
            else
                dc.SetBrush(*wxWHITE_BRUSH);

            dc.DrawRectangle(col * cellWidth, row * cellHeight, cellWidth, cellHeight);
        }
    }
}

void DrawingPanel::SetGameBoard(const std::vector<std::vector<bool>>& board)
{
    gameBoard = board;
    Refresh();
}
