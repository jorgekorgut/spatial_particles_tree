#pragma once

#include <wx/wx.h>
#include "Application.h"
#include "../Tree/ParticlesTree.h"

class MyFrame;

enum class ParticleTileType
{
    EMPTY,
    CONTAINS,
    SELECTED
};
class ParticleMatrixInterface : public wxPanel
{

public:
    ParticleMatrixInterface(MyFrame *parentFrame);
    void updateParticleMatrix(ReturnParticleCountByFarm *particlesData);
    int *getSelectedTile() { return selectedFarm; }

protected:
    void OnPaint(wxPaintEvent &event);
    void OnLeftUp(wxMouseEvent &event);

private:
    void DrawSquare(wxPaintDC &dc, int x, int y, double width, double height, ParticleTileType type);

    MyFrame * parent;
    ReturnParticleCountByFarm *data;
    int *selectedFarm = nullptr;
    int clickScreenX = -1;
    int clickScreenY = -1;
};