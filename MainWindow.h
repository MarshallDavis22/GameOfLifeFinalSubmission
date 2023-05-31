#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <wx/wx.h>

class DrawingPanel : public wxPanel
{
public:
    DrawingPanel(wxWindow* parent);

    void SetGameBoard(const std::vector<std::vector<bool>>& board);

    void OnPaint(wxPaintEvent& event);

public:
    std::vector<std::vector<bool>> gameBoard;

};

class MainWindow : public wxFrame
{
public:
    MainWindow();
    
public:
    wxMenuBar* menuBar;
    wxStatusBar* statusBar;

    DrawingPanel* drawingPanel;

    std::vector<std::vector<bool>> gameBoard;
    int gridSize;
    int cellSize;
    int generationCount;
    int livingCellCount;
    wxString currentFileName;

    void CreateMenu();
    void OnOpen(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnSaveAs(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnSizeSelect(wxCommandEvent& event);
    void OnNext(wxCommandEvent& event);
    void OnClear(wxCommandEvent& event);
    void OnRandomize(wxCommandEvent& event);
    void OnRandomizeWithSeed(wxCommandEvent& event);

    void CreateStatusBar();
    void UpdateStatusText();
    void ClearBoard();
    void RandomizeGrid(unsigned int seed);
    int CountLiveNeighbors(int row, int col);

    wxDECLARE_EVENT_TABLE();
};

#endif
