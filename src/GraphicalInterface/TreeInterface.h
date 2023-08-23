#pragma once

#include <wx/wx.h>
#include "../Tree/ParticlesTree.h"

enum class LeafType
{
    EMPTY,
    TERMINAL_CHILD,
    HAS_CHILDREN,
    SELECTED,
};

class TreeInterface : public wxPanel
{

public:
    TreeInterface(wxFrame *parent, ParticlesTree *tree);
    TreeInterface(wxFrame *parent);

    ParticlesTree *GetTree() { return tree; }
    void SetSelectedData(ReturnParticleCountByFarm *data)
    {
        selectedData = data;
        this->Refresh();
    }

protected:
    void OnPaint(wxPaintEvent &event);
    void OnLeftUp(wxMouseEvent &event);

private:
    ParticlesTree *tree;
    ReturnParticleCountByFarm *selectedData = nullptr;

    void DrawRecursively(wxPaintDC &dc, double x, double y, double width, double height, Node *currentNode, int leavesX, int leavesY);
    void DrawSquare(wxPaintDC &dc, int x, int y, double width, double height, LeafType shape);
};