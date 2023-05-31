#include <wx/wx.h>
#include "MainWindow.h"

class GameOfLifeApp : public wxApp
{
public:
    bool OnInit()
    {
        MainWindow* mainWindow = new MainWindow();
        mainWindow->Show();
        return true;
    }
};

wxIMPLEMENT_APP(GameOfLifeApp);
