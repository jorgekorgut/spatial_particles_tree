#include "ParticleMatrixInterface.h"
#include "../Tree/Node.h"
#include <vector>
#include <iostream>
#include <string>

ParticleMatrixInterface::ParticleMatrixInterface(MyFrame *parentFrame)
    : wxPanel(parentFrame, wxID_ANY, wxDefaultPosition,
              wxDefaultSize, wxBORDER_NONE)
{

    data = nullptr;
    parent = parentFrame;

    Connect(wxEVT_PAINT, wxPaintEventHandler(ParticleMatrixInterface::OnPaint));
    Connect(wxEVT_LEFT_UP, wxMouseEventHandler(ParticleMatrixInterface::OnLeftUp));
}

void ParticleMatrixInterface::OnLeftUp(wxMouseEvent &event)
{
    wxPoint clickedPos = event.GetPosition();

    clickScreenX = clickedPos.x;
    clickScreenY = clickedPos.y;

    this->Refresh();
}

void ParticleMatrixInterface::updateParticleMatrix(ReturnParticleCountByFarm *particlesData)
{
    data = particlesData;
    this->Refresh();
}

void ParticleMatrixInterface::OnPaint(wxPaintEvent &event)
{
    wxPaintDC dc(this);

    if (data != nullptr)
    {
        selectedFarm = nullptr;
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

            int sum = 0;
            for (int n = 0; n < numberOfFarms; n++)
            {
                sum += farmValue[n];
            }

            if (sum == 0)
            {
                DrawSquare(dc, xIndex * resolutionX, yIndex * resolutionY, resolutionX, resolutionY, ParticleTileType::EMPTY);
            }
            else
            {
                DrawSquare(dc, xIndex * resolutionX, yIndex * resolutionY, resolutionX, resolutionY, ParticleTileType::CONTAINS);
            }

            if (clickScreenX >= xIndex * resolutionX &&
                clickScreenY >= yIndex * resolutionY &&
                clickScreenX < xIndex * resolutionX + resolutionX &&
                clickScreenY < yIndex * resolutionY + resolutionY)
            {
                selectedFarm = farmValue;
                parent->onFarmUpdate();
                DrawSquare(dc, xIndex * resolutionX, yIndex * resolutionY, resolutionX, resolutionY, ParticleTileType::SELECTED);
            }

            /*
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
            */
        }
    }
}
void ParticleMatrixInterface::DrawSquare(wxPaintDC &dc, int x, int y, double width, double height, ParticleTileType type)
{
    static wxColour green = wxColour(57, 159, 16);
    static wxColour black = wxColour(0, 0, 0);
    static wxColour red = wxColour(150, 16, 16);

    if (type == ParticleTileType::EMPTY)
    {
        int padding = 1;
        dc.SetPen(wxPen(black, 0));
        dc.SetBrush(*wxTRANSPARENT_BRUSH);
        dc.DrawRectangle(x + padding,
                         y + padding,
                         width - padding,
                         height - padding);
    }
    else if (type == ParticleTileType::CONTAINS)
    {
        int padding = 1;
        dc.SetPen(wxPen(red, 3));
        dc.SetBrush(*wxTRANSPARENT_BRUSH);
        dc.DrawRectangle(x,
                         y,
                         width,
                         height);
    }
    else if (type == ParticleTileType::SELECTED)
    {
        int padding = 1;
        dc.SetPen(*wxTRANSPARENT_PEN);
        dc.SetBrush(wxBrush(green));
        dc.DrawRectangle(x,
                         y,
                         width,
                         height);
    }
}
