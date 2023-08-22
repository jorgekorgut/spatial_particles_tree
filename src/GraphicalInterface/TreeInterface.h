#pragma once

#include <wx/wx.h>
#include "../Tree/ParticlesTree.h"

enum LeafType
{
    EMPTY,
    TERMINAL_CHILD,
    HAS_CHILDREN,
};

class TreeInterface : public wxPanel
{

public:
    TreeInterface(wxFrame *parent, ParticlesTree *tree);
    TreeInterface(wxFrame *parent);

protected:
    void OnPaint(wxPaintEvent &event);
    void OnLeftUp(wxMouseEvent &event);
    // void OnKeyDown(wxKeyEvent& event);
    // void OnTimer(wxCommandEvent& event);

private:
    ParticlesTree *tree;

    int SquareWidth() { return GetClientSize().GetWidth() / tree->getLeavesCountX(); }
    int SquareHeight() { return GetClientSize().GetHeight() / tree->getLeavesCountY(); }
    void ClearTree();
    void DrawRecursively(wxPaintDC &dc, double x, double y, double width, double height, Node *currentNode, int leavesX, int leavesY);
    void DrawSquare(wxPaintDC &dc, int x, int y, double width, double height, LeafType shape);
};