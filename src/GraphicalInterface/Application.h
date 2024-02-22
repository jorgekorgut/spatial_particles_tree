#pragma once

#include <wx/wx.h>
#include "TreeInterface.h"
#include "ParticleMatrixInterface.h"

class ParticleMatrixInterface;

class Application : public wxApp
{
public:
    bool OnInit() override;
};

class MyFrame : public wxFrame
{
public:
    MyFrame();
    void onFarmUpdate();
    
private:
    void OnHello(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);

    void OnGetParticlesInAreaButtonClicked(wxCommandEvent &event);
    void OnSearchWithoutDrawingButtonClicked(wxCommandEvent &event);

    ParticleMatrixInterface *particleMatrixInterface;
    TreeInterface *treeInterface;

    wxTextCtrl *xInput;
    wxTextCtrl *yInput;
    wxTextCtrl *widthInput;
    wxTextCtrl *heightInput;
    wxTextCtrl *resolutionInput;

    wxTextCtrl *loadDataTimeElapsedInput;
    wxTextCtrl *searchTimeElapsedInput;

    wxTextCtrl *logInput;
};

enum
{
    ID_Hello = 1
};