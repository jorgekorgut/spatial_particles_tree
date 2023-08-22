#pragma once

#include <wx/wx.h>
#include "../Tree/ParticlesTree.h"


class ParticleMatrixInterface : public wxPanel
{

public:
    ParticleMatrixInterface(wxFrame *parent, ReturnParticleCountByFarm *particlesData);
    ParticleMatrixInterface(wxFrame *parent);

    void updateParticleMatrix(ReturnParticleCountByFarm *particlesData);

protected:
    void OnPaint(wxPaintEvent &event);
    
private:
    ReturnParticleCountByFarm *data;

    //void DrawData(wxPaintDC &dc, double x, double y, double width, double height, int leavesX, int leavesY);
    //void DrawSquare(wxPaintDC &dc, int x, int y, double width, double height, int quantity);
};