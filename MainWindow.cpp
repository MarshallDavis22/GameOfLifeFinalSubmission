#include "MainWindow.h"
#include <wx/msgdlg.h>
#include <wx/filedlg.h>



enum
{
    wxID_SIZE_10 = 1001,
    wxID_SIZE_20,
    wxID_SIZE_30
};

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_MENU(wxID_EXIT, MainWindow::OnExit)
EVT_MENU(wxID_ABOUT, MainWindow::OnAbout)
EVT_MENU(wxID_SIZE_10, MainWindow::OnSizeSelect)
EVT_MENU(wxID_SIZE_20, MainWindow::OnSizeSelect)
EVT_MENU(wxID_SIZE_30, MainWindow::OnSizeSelect)
EVT_MENU(wxID_ANY, MainWindow::OnNext)
EVT_MENU(wxID_CLEAR, MainWindow::OnClear)
EVT_MENU(wxID_ANY, MainWindow::OnRandomize)
EVT_MENU(wxID_ANY, MainWindow::OnRandomizeWithSeed)
wxEND_EVENT_TABLE()



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


MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game of Life", wxDefaultPosition, wxSize(800, 600))
{
    gridSize = 10;
    cellSize = 40;
    generationCount = 0;
    livingCellCount = 0;

    menuBar = new wxMenuBar();

    drawingPanel = new DrawingPanel(this);

    statusBar = new wxStatusBar(this);
    
    CreateStatusBar();

    CreateMenu();

    SetMenuBar(menuBar);

    UpdateStatusText();

    wxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(drawingPanel, 1, wxEXPAND);
    SetSizerAndFit(sizer);

    ClearBoard();
}

void MainWindow::CreateMenu()
{
    wxMenu* fileMenu = new wxMenu();

    fileMenu->Append(wxID_NEW, "New");

    fileMenu->Append(wxID_OPEN, "Open", "Open a file");
    Bind(wxEVT_MENU, &MainWindow::OnOpen, this, wxID_OPEN);

    fileMenu->Append(wxID_SAVE, "Save", "Save the current file");
    Bind(wxEVT_MENU, &MainWindow::OnSave, this, wxID_SAVE);

    fileMenu->Append(wxID_SAVEAS, "Save As", "Save the file with a new name");
    Bind(wxEVT_MENU, &MainWindow::OnSaveAs, this, wxID_SAVEAS);

    fileMenu->Append(wxID_SAVEAS, "Save As", "Save the file with a new name");
    Bind(wxEVT_MENU, &MainWindow::OnSaveAs, this, wxID_SAVEAS);

    menuBar->Append(fileMenu, "File");
}

void MainWindow::OnOpen(wxCommandEvent& event)
{
    wxFileDialog openFileDialog(this, "Open File", "", "", "Cells files (*.cells)|*.cells",
        wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    wxString filePath = openFileDialog.GetPath();

}

void MainWindow::OnSave(wxCommandEvent& event)
{
    if (!currentFileName.IsEmpty())
    {
    }
    else
    {
        OnSaveAs(event);
    }
}

void MainWindow::OnSaveAs(wxCommandEvent& event)
{
    wxFileDialog saveFileDialog(this, "Save File", "", "", "Cells files (*.cells)|*.cells",
        wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;

    wxString filePath = saveFileDialog.GetPath();


}

void MainWindow::OnExit(wxCommandEvent& event)
{
    Close();
}

void MainWindow::CreateStatusBar()
{
    statusBar->SetFieldsCount(2);
    int widths[2] = { 150, -1 };
    statusBar->SetStatusWidths(2, widths);
}

void MainWindow::UpdateStatusText()
{
    wxString generationText = wxString::Format("Generation: %d", generationCount);
    wxString livingCellText = wxString::Format("Living Cells: %d", livingCellCount);

    statusBar->SetStatusText(generationText, 0);
    statusBar->SetStatusText(livingCellText, 1);
}

void MainWindow::ClearBoard()
{
    gameBoard.clear();

    for (int row = 0; row < gridSize; row++)
    {
        std::vector<bool> newRow;
        for (int col = 0; col < gridSize; col++)
        {
            newRow.push_back(false);
        }
        gameBoard.push_back(newRow);
    }

    generationCount = 0;
    livingCellCount = 0;

    UpdateStatusText();
    drawingPanel->SetGameBoard(gameBoard);
}

void MainWindow::RandomizeGrid(unsigned int seed)
{
    srand(seed);

    for (int row = 0; row < gridSize; row++)
    {
        for (int col = 0; col < gridSize; col++)
        {
            double random = static_cast<double>(rand()) / RAND_MAX;
            gameBoard[row][col] = (random < 0.5);

            if (gameBoard[row][col])
                livingCellCount++;
        }
    }

    generationCount = 0;

    UpdateStatusText();
    drawingPanel->SetGameBoard(gameBoard);
}

int MainWindow::CountLiveNeighbors(int row, int col)
{
    int count = 0;

    for (int i = row - 1; i <= row + 1; i++)
    {
        for (int j = col - 1; j <= col + 1; j++)
        {
            if (i == row && j == col)
                continue;

            if (i >= 0 && i < gameBoard.size() && j >= 0 && j < gameBoard[i].size())
            {
                if (gameBoard[i][j])
                    count++;
            }
        }
    }

    return count;
}

void MainWindow::OnSizeSelect(wxCommandEvent& event)
{
    int id = event.GetId();

    if (id == wxID_SIZE_10)
        gridSize = 10;
    else if (id == wxID_SIZE_20)
        gridSize = 20;
    else if (id == wxID_SIZE_30)
        gridSize = 30;

    ClearBoard();
}

void MainWindow::OnClear(wxCommandEvent& event)
{
    ClearBoard();
}

void MainWindow::OnRandomize(wxCommandEvent& event)
{
    RandomizeGrid(time(NULL));
}

void MainWindow::OnRandomizeWithSeed(wxCommandEvent& event)
{
    wxTextEntryDialog dialog(this, "Enter seed value", "Randomize with Seed");
    if (dialog.ShowModal() == wxID_OK)
    {
        long seed;
        if (dialog.GetValue().ToLong(&seed))
            RandomizeGrid(static_cast<unsigned int>(seed));
        else
            wxMessageBox("Invalid seed value!", "Error", wxOK | wxICON_ERROR);
    }
}

void MainWindow::OnNext(wxCommandEvent& event)
{
    std::vector<std::vector<bool>> nextGeneration = gameBoard;

    for (int row = 0; row < gameBoard.size(); row++)
    {
        for (int col = 0; col < gameBoard[row].size(); col++)
        {
            int liveNeighbors = CountLiveNeighbors(row, col);

            if (gameBoard[row][col])
            {
                if (liveNeighbors < 2 || liveNeighbors > 3)
                {
                    nextGeneration[row][col] = false;
                    livingCellCount--;
                }
            }
            else
            {
                if (liveNeighbors == 3)
                {
                    nextGeneration[row][col] = true;
                    livingCellCount++;
                }
            }
        }
    }

    gameBoard = nextGeneration;
    generationCount++;

    UpdateStatusText();
    drawingPanel->SetGameBoard(gameBoard);
}

void MainWindow::OnAbout(wxCommandEvent& event)
{
    wxString aboutMessage = "Conway's Game of Life\n\n"
        "The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician "
        "John Horton Conway in 1970. The game is a zero-player game, meaning that its evolution is determined by its "
        "initial state, requiring no further input. One interacts with the Game of Life by creating an initial "
        "configuration and observing how it evolves.\n\n"
        "For more information, visit: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life";

    wxMessageBox(aboutMessage, "About Game of Life", wxOK | wxICON_INFORMATION);
}
