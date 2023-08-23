// Start of wxWidgets "Hello World" Program
#include "Application.h"

bool Application::OnInit()
{
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}

MyFrame::MyFrame()
    : wxFrame(nullptr, wxID_ANY, "Application", wxDefaultPosition, wxSize(1700, 500))
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);

    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");

    Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);

    // FIXME : Pass tree on argument
    //ParticlesTree *particlesTree = new ParticlesTree(700, 400, 100, 4, 2, 2);
    ParticlesTree *particlesTree = new ParticlesTree(700, 400, 25, 4, 4, 2);
    /*
    particlesTree->addNode(Vector4(0, 0, 0, 1));
    particlesTree->addNode(Vector4(0, 300, 0, 1));
    particlesTree->addNode(Vector4(262.5, 300, 0, 1));
    particlesTree->addNode(Vector4(600, 350, 0, 1));
    particlesTree->addNode(Vector4(700, 400, 0, 1));
    */
    particleMatrixInterface = new ParticleMatrixInterface(this);
    particleMatrixInterface->SetBackgroundColour(wxColor(100, 50, 50));

    treeInterface = new TreeInterface(this, particlesTree);
    treeInterface->SetBackgroundColour(wxColor(50, 50, 100));

    wxBoxSizer *formWrapper = new wxBoxSizer(wxVERTICAL);

    wxGridSizer *form = new wxGridSizer(5, 2, wxSize(0, 0));
    wxStaticText *xLabel = new wxStaticText(this, wxID_ANY, "x:");
    xInput = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(FromDIP(300), wxDefaultSize.GetHeight()));
    wxStaticText *yLabel = new wxStaticText(this, wxID_ANY, "y:");
    yInput = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(FromDIP(300), wxDefaultSize.GetHeight()));
    wxStaticText *widthLabel = new wxStaticText(this, wxID_ANY, "width:");
    widthInput = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(FromDIP(300), wxDefaultSize.GetHeight()));
    wxStaticText *heightLabel = new wxStaticText(this, wxID_ANY, "height:");
    heightInput = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(FromDIP(300), wxDefaultSize.GetHeight()));
    wxStaticText *resolutionLabel = new wxStaticText(this, wxID_ANY, "resolution:");
    resolutionInput = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(FromDIP(300), wxDefaultSize.GetHeight()));

    form->Add(xLabel, 1, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 10);
    form->Add(xInput, 1, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 10);

    form->Add(yLabel, 1, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 10);
    form->Add(yInput, 1, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 10);

    form->Add(widthLabel, 1, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 10);
    form->Add(widthInput, 1, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 10);

    form->Add(heightLabel, 1, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 10);
    form->Add(heightInput, 1, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 10);

    form->Add(resolutionLabel, 1, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 10);
    form->Add(resolutionInput, 1, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 10);

    formWrapper->Add(form, 3, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 10);

    wxButton *getParticlesInAreaButton = new wxButton(this, -1, "Search for particles inside the area : ");
    formWrapper->Add(getParticlesInAreaButton, 1, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 10);
    getParticlesInAreaButton->Bind(wxEVT_BUTTON, &MyFrame::OnGetParticlesInAreaButtonClicked, this);

    logInput = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(FromDIP(300), wxDefaultSize.GetHeight()), wxTE_MULTILINE);
    logInput->Disable();
    formWrapper->Add(logInput, 3, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 10);

    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(treeInterface, 2, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 10);
    sizer->Add(particleMatrixInterface, 2, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 10);
    sizer->Add(formWrapper, 1, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 10);

    this->SetSizer(sizer);
    this->Show();
}

void MyFrame::onFarmUpdate()
{
    int numberOfFarms = treeInterface->GetTree()->getNumberOfFarms();
    int *selectedTileFarms = particleMatrixInterface->getSelectedTile();
    if (selectedTileFarms != nullptr)
    {
        logInput->Clear();
        std::string result = "Particles by farm : \n";
        for (int n = 0; n < numberOfFarms; n++)
        {
            result += "[";
            result += std::to_string(n);
            result += "]    ";
            result += std::to_string(selectedTileFarms[n]);
            result += "\n";
        }
        (*logInput) << wxString(result);
    }
}

void MyFrame::OnGetParticlesInAreaButtonClicked(wxCommandEvent &event)
{
    try
    {
        double x;
        bool valid = xInput->GetLineText(0).ToDouble(&x);
        double y;
        valid = valid && yInput->GetLineText(0).ToDouble(&y);
        double width;
        valid = valid && widthInput->GetLineText(0).ToDouble(&width);
        double height;
        valid = valid && heightInput->GetLineText(0).ToDouble(&height);
        double wantedResolution;
        valid = valid && resolutionInput->GetLineText(0).ToDouble(&wantedResolution);

        if (!valid)
        {
            throw(1);
        }

        ReturnParticleCountByFarm *data = treeInterface->GetTree()->getParticlesCountByFarm(x, y, width, height, wantedResolution);
        treeInterface->SetSelectedData(data);
        particleMatrixInterface->updateParticleMatrix(data);
    }
    catch (int errorCode)
    {
        std::cerr << "Conversion error" << std::endl;
    }
}

void MyFrame::OnExit(wxCommandEvent &event)
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent &event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
                 "About Hello World", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnHello(wxCommandEvent &event)
{
    wxLogMessage("Hello world from wxWidgets!");
}
