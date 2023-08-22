#include "ParticleMatrixInterface.h"
#include "../Tree/Node.h"
#include <vector>
#include <iostream>
#include <string>

ParticleMatrixInterface::ParticleMatrixInterface(wxFrame *parent, ReturnParticleCountByFarm *particlesData)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition,
              wxDefaultSize, wxBORDER_NONE)
{
    data = particlesData;

    Connect(wxEVT_PAINT, wxPaintEventHandler(ParticleMatrixInterface::OnPaint));
    // Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(Board::OnKeyDown));
}

ParticleMatrixInterface::ParticleMatrixInterface(wxFrame *parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition,
              wxDefaultSize, wxBORDER_NONE)
{
    data = nullptr;

    Connect(wxEVT_PAINT, wxPaintEventHandler(ParticleMatrixInterface::OnPaint));
    // Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(Board::OnKeyDown));
}

void ParticleMatrixInterface::updateParticleMatrix(ReturnParticleCountByFarm *particlesData)
{
    data = particlesData;
    this->Refresh();
}

void ParticleMatrixInterface::OnPaint(wxPaintEvent &event)
{
    if (data != nullptr)
    {
        wxPaintDC dc(this);

        std::vector<int *> *countParticlesMatrix = data->countParticlesMatrix;
        int sizeX = data->sizeX;
        int sizeY = data->sizeY;
        double resolutionX = data->resolutionX;
        double resolutionY = data->resolutionY;
        int numberOfFarms = data->numberOfFarms;

        for (int index = 0; index < countParticlesMatrix->size(); ++index)
        {

            int xIndex = index % sizeX;
            int yIndex = index / sizeX;
            int *farmValue = (*countParticlesMatrix)[index];

            std::cout << "index: ";
            std::cout << xIndex;
            std::cout << " | ";
            std::cout << yIndex;
            std::cout << std::endl;

            std::cout << "particleFarms: { ";
            for (int n = 0; n < numberOfFarms; n++)
            {
                std::cout << farmValue[n];
                std::cout << " ";
            }
            std::cout << "}";
            std::cout << std::endl;
        }
    }
}
/*
void TreeInterface::DrawSquare(wxPaintDC &dc, int x, int y, double width, double height, LeafType type)
{
    static wxColour green = wxColour(57, 159, 16);

    static wxColour black = wxColour(0, 0, 0);

    static wxColour red = wxColour(159, 16, 16);

    if (type == LeafType::HAS_CHILDREN)
    {
        int padding = 1;
        dc.SetPen(wxPen(green, 3));
        dc.SetBrush(*wxTRANSPARENT_BRUSH);
        dc.DrawRectangle(x + padding,
                         y + padding,
                         width - padding,
                         height - padding);
    }
    else if (type == LeafType::TERMINAL_CHILD)
    {
        int padding = 1;
        dc.SetPen(wxPen(green, 3));
        dc.SetBrush(wxBrush(red));
        dc.DrawRectangle(x,
                         y,
                         width,
                         height);
    }
    else if (type == LeafType::EMPTY)
    {
        int padding = 1;
        dc.SetPen(wxPen(black, 0));
        dc.SetBrush(*wxTRANSPARENT_BRUSH);
        dc.DrawRectangle(x + padding,
                         y + padding,
                         width - padding,
                         height - padding);
    }
}
*/
/*
    static wxColour dark[] = {wxColour(0, 0, 0), wxColour(128, 59, 59),
                              wxColour(59, 128, 59), wxColour(59, 59, 128),
                              wxColour(128, 128, 59), wxColour(128, 59, 128),
                              wxColour(59, 128, 128), wxColour(128, 98, 0)};

    wxPen pen(light[int(shape)]);
    pen.SetCap(wxCAP_PROJECTING);
    dc.SetPen(pen);

    dc.DrawLine(x, y + SquareHeight() - 1, x, y);
    dc.DrawLine(x, y, x + SquareWidth() - 1, y);

    wxPen darkpen(dark[int(shape)]);
    darkpen.SetCap(wxCAP_PROJECTING);
    dc.SetPen(darkpen);

    dc.DrawLine(x + 1, y + SquareHeight() - 1,
                x + SquareWidth() - 1, y + SquareHeight() - 1);
    dc.DrawLine(x + SquareWidth() - 1,
                y + SquareHeight() - 1, x + SquareWidth() - 1, y + 1);

    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.SetBrush(wxBrush(colors[int(shape)]));
    dc.DrawRectangle(x + 1, y + 1, SquareWidth() - 2,
                     SquareHeight() - 2);
    */

/*
while (nodesList.size() != 0)
    {
        // Get first queue node
        currentNode = nodesList.front();
        // std::cout << currentNode->getNumberOfParticlesByFarm()[1] << std::endl;

        std::cout << "nodeList : ";
        std::cout << nodesList.size() << std::endl;

        std::cout << "currentWidthDepth : ";
        std::cout << currentWidthDepth << std::endl;
        std::cout << "currentHeightDepth : ";
        std::cout << currentHeightDepth << std::endl;
        std::cout << "countChildrenInDepth : ";
        std::cout << countChildrenInDepth << std::endl;

        nodesList.pop();
        --countChildrenInDepth;
        if (countChildrenInDepth == 0)
        {
            currentWidthDepth = currentWidthDepth / leavesX;
            currentHeightDepth = currentHeightDepth / leavesY;

            countChildrenInDepth = countChildrenNextDepth;
            countChildrenNextDepth = 0;
        }

        // Update list with node children and draw
        for (int x = 0; x < leavesX; x++)
        {
            for (int y = 0; y < leavesY; y++)
            {
                int currentIndex = y + leavesY * x;

                Node **children = currentNode->getChildren();
                if (children[currentIndex] != nullptr)
                {
                    std::cout << "node added [";
                    std::cout << children[currentIndex]->getNumberOfParticlesByFarm()[1];
                    std::cout << "]" << std::endl;
                    DrawSquare(dc, x, y, currentWidthDepth, currentHeightDepth, LeafType::HAS_CHILDREN);

                    nodesList.push(children[currentIndex]);
                    ++countChildrenNextDepth;
                }
                else
                {
                    DrawSquare(dc, x, y, currentWidthDepth, currentHeightDepth, LeafType::EMPTY);
                }
            }
        }
    }


     int boardTop = size.GetHeight() - BoardHeight * SquareHeight();
        for (int i = 0; i < BoardHeight; ++i) {
            for (int j = 0; j < BoardWidth; ++j) {
                Tetrominoes shape = ShapeAt(j, BoardHeight - i - 1);
                if (shape != NoShape)
                    DrawSquare(dc, 0 + j * SquareWidth(),
                               boardTop + i * SquareHeight(), shape);
            }
        }

        if (curPiece.GetShape() != NoShape) {
            for (int i = 0; i < 4; ++i) {
                int x = curX + curPiece.x(i);
                int y = curY - curPiece.y(i);
                DrawSquare(dc, 0 + x * SquareWidth(),
                           boardTop + (BoardHeight - y - 1) * SquareHeight(),
                           curPiece.GetShape());
            }
        }
        */