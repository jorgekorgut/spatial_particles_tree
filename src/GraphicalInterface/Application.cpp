// Start of wxWidgets "Hello World" Program
#include "Application.h"
#include "TreeInterface.h"
#include "ParticleMatrixInterface.h"

bool Application::OnInit()
{
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}

MyFrame::MyFrame()
    : wxFrame(nullptr, wxID_ANY, "Application", wxDefaultPosition, wxSize(1500, 500))
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
    ParticlesTree *particlesTree = new ParticlesTree(700, 400, 100, 4, 2, 2);
    particlesTree->addNode(Vector4(0, 0, 0, 1));
    particlesTree->addNode(Vector4(0, 300, 0, 1));
    particlesTree->addNode(Vector4(262.5, 300, 0, 1));
    particlesTree->addNode(Vector4(600, 350, 0, 1));
    particlesTree->addNode(Vector4(700, 400, 0, 1));

    ReturnParticleCountByFarm *particleCountResponse = particlesTree->getParticlesCountByFarm(87.5, 100, 175, 200, 200); // x0,y0,w350,h400,sx2,sy2
    // ReturnParticleCountByFarm * particleCountResponse = particlesTree->getParticlesCountByFarm(0, 0, 200, 200, 200); // x0,y0,w350,h200
    // ReturnParticleCountByFarm * particleCountResponse = particlesTree->getParticlesCountByFarm(175, 200, 175, 300, 200); // x175,y200,w175,h200

    // ReturnParticleCountByFarm * particleCountResponse = particlesTree->getParticlesCountByFarm(0, 400, 175, 300, 200); //nullptr

    /*
    std::cout << "Root: " ;
    std::cout << particlesTree->getRoot()->getNumberOfParticlesByFarm()[1] <<std::endl;
    */
    wxPanel *panelLeft = new TreeInterface(this, particlesTree);
    panelLeft->SetBackgroundColour(wxColor(50, 50, 100));
    wxPanel *panelRight = new ParticleMatrixInterface(this);
    panelRight->SetBackgroundColour(wxColor(100, 50, 50));

    //
    // TreeInterface *treeInterface =
    // ParticleMatrixInterface *particleMatrixInterface =

    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(panelLeft, 1, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 10);
    sizer->Add(panelRight, 1, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 10);

    this->SetSizer(sizer);
    this->Show();
    //
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
