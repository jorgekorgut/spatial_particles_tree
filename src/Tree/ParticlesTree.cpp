#include "ParticlesTree.h"
#include <iostream>
#include <algorithm>
#include <cmath>

ParticlesTree::ParticlesTree(double maxWidth, double maxHeight, double minRes, int leavesNumberX, int leavesNumberY, int nFarms)
{
    width = maxWidth;
    height = maxHeight;
    minResolution = minRes;

    leavesX = leavesNumberX;
    leavesY = leavesNumberY;
    numberOfLeaves = leavesNumberX * leavesNumberY;

    numberOfFarms = nFarms;
    root = new Node(numberOfFarms, leavesX * leavesY);
}
/*
void ParticlesTree::generateTreeFromVector3(std::vector<Vector4> &spatialData)
{
    int numberOfLeaves = leavesX * leavesY;
    for (Vector4 &currentParticle : spatialData)
    {
        if (currentParticle.farm < numberOfFarms)
        {
            addNode(currentParticle, numberOfLeaves);
        }
        else
        {
            std::cerr << "[Farm index Error]" << std::endl;
        }
    }
}
*/
// TODO : Optmize tree construction
void ParticlesTree::addNode(const Vector4 &spatialData)
{
    // std::cout << "AddNode : \n";
    if (spatialData.x > width || spatialData.y > height)
    {
        // std::cout << "Out of range" << std::endl;
        return;
    }

    double currentWidth = width / leavesX;
    double currentHeight = height / leavesY;
    int currentWidthIndex = 0;
    int currentHeightIndex = 0;
    int currentSpatialDataX = spatialData.x;
    int currentSpatialDataY = spatialData.y;
    Node *currentNode = root;

    double testResolutionX = minResolution / leavesX;
    double testResolutionY = minResolution / leavesY;

    while (currentWidth > testResolutionX ||
           currentHeight > testResolutionY)
    {
        currentWidthIndex = std::max((int)std::ceil(currentSpatialDataX / (currentWidth)) - 1, 0); // Intervals are [0,1] ]1,2] ]2,3] ...
        currentHeightIndex = std::max((int)std::ceil(currentSpatialDataY / (currentHeight)) - 1, 0);
        /*
                // std::cout << "position : ";
                // std::cout << spatialData.x;
                // std::cout << "|";
                // std::cout << spatialData.y << std::endl;
                std::cout << "size : ";
                std::cout << currentWidth;
                std::cout << "|";
                std::cout << currentHeight << std::endl;

                std::cout << "currentSpatial : ";
                std::cout << currentSpatialDataX;
                std::cout << "|";
                std::cout << currentSpatialDataY << std::endl;

                std::cout << "index : ";
                std::cout << currentWidthIndex;
                std::cout << "|";
                std::cout << currentHeightIndex << std::endl;
        */
        currentSpatialDataX = currentSpatialDataX - currentWidth * currentWidthIndex;
        currentSpatialDataY = currentSpatialDataY - currentHeight * currentHeightIndex;

        currentNode = currentNode->updateNode(currentWidthIndex + leavesX * currentHeightIndex, numberOfFarms, numberOfLeaves, spatialData.farm);

        currentWidth = currentWidth / leavesX;
        currentHeight = currentHeight / leavesY;
    }
}

ReturnParticleCountByFarm *ParticlesTree::getParticlesCountByFarm(double x, double y, double wantedWidth, double wantedHeight, double wantedResolution)
{
    if (countMatrix != nullptr)
    {
        // TODO : Free countMatrix
    }
    countMatrix = new std::vector<int *>();

    double resolutionX = std::max(wantedResolution, minResolution);
    double resolutionY = std::max(wantedResolution, minResolution);

    double realResolutionX = width;
    double realResolutionY = height;

    while (realResolutionX > resolutionX ||
           realResolutionY > resolutionY)
    {
        realResolutionX /= leavesX;
        realResolutionY /= leavesY;
    }

    // Snap x and y to the top left corner of the minimal resolution.
    double realX = 0;
    double realY = 0;
    while (realX <= x)
    {
        realX += realResolutionX;
    }
    realX -= realResolutionX;
    realX = std::max(0.0, realX);
    realX = std::min(width, realX);

    while (realY <= y)
    {
        realY += realResolutionY;
    }
    realY -= realResolutionY;
    realY = std::max(0.0, realY);
    realY = std::min(height, realY);

    // Snap width and height to ceil of x, y and realResolution

    int realSizeX = 1;
    int realSizeY = 1;
    double realWidth = realResolutionX;
    double realHeight = realResolutionY;
    while (realWidth < (wantedWidth + x - realX))
    {
        realWidth += realResolutionX;
        realSizeX += 1;
    }

    realWidth = std::min(realWidth, width - realX);

    while (realHeight < wantedHeight + y - realY)
    {
        realHeight += realResolutionY;
        realSizeY += 1;
    }

    realHeight = std::min(realHeight, height - realY);

    for (int i = 0; i < realSizeX * realSizeY; i++)
    {
        int *particlesByFarm = new int[numberOfFarms];
        for (int n = 0; n < numberOfFarms; n++)
        {
            particlesByFarm[n] = 0;
        }
        countMatrix->push_back(particlesByFarm);
    }

    std::cout << "== size: ";
    std::cout << realSizeX;
    std::cout << " | ";
    std::cout << realSizeY;
    std::cout << std::endl;

    /*
        std::cout << "== real: ";
        std::cout << realX;
        std::cout << " | ";
        std::cout << realY;
        std::cout << std::endl;
        std::cout << "== width/height: ";
        std::cout << realWidth;
        std::cout << " | ";
        std::cout << realHeight;
        std::cout << std::endl;
        std::cout << "resolutionX/resolutionY: ";
        std::cout << realResolutionX;
        std::cout << " | ";
        std::cout << realResolutionY;
        std::cout << std::endl;
        std::cout << "leavesX/leavesY: ";
        std::cout << leavesX;
        std::cout << " | ";
        std::cout << leavesY;
        std::cout << std::endl;
    */
    if (realHeight == 0 || realWidth == 0)
    {
        return nullptr;
    }

    Node *currentNode = root;

    searchRecursivelyParticlesCount(currentNode,
                                    realX,
                                    realY,
                                    width,
                                    height,
                                    realX,
                                    realY,
                                    realWidth,
                                    realHeight,
                                    realResolutionX,
                                    realResolutionY,
                                    realSizeX,
                                    realSizeY);

    return new ReturnParticleCountByFarm(realSizeX, realSizeY, numberOfFarms, countMatrix, realResolutionX, realResolutionY);
}

void ParticlesTree::searchRecursivelyParticlesCount(Node *currentNode,
                                                    double currentX,
                                                    double currentY,
                                                    double currentWidth,
                                                    double currentHeight,
                                                    double realX,
                                                    double realY,
                                                    double realWidth,
                                                    double realHeight,
                                                    double realResolutionX,
                                                    double realResolutionY,
                                                    double realSizeX,
                                                    double realSizeY)
{
    Node **children = currentNode->getChildren();
    double childWidthDepth = currentWidth / leavesX;
    double childHeightDepth = currentHeight / leavesY;

    for (int yIndex = 0; yIndex < leavesY; yIndex++)
    {
        for (int xIndex = 0; xIndex < leavesX; xIndex++)
        {
            int currentIndex = xIndex + leavesX * yIndex;
            if (children[currentIndex] != nullptr)
            {
                /*
                std::cout << "iterator: ";
                std::cout << xIndex;
                std::cout << " | ";
                std::cout << yIndex;
                std::cout << std::endl;
                std::cout << "childrenWidth/childrenHeight: ";
                std::cout << childWidthDepth;
                std::cout << " | ";
                std::cout << childHeightDepth;
                std::cout << std::endl;
*/
                if (childWidthDepth > realResolutionX ||
                    childHeightDepth > realResolutionY)
                {
                    double childX = currentX + xIndex * childWidthDepth;
                    double childY = currentY + yIndex * childHeightDepth;
                    /*
                                        std::cout << "== child: ";
                                        std::cout << childX;
                                        std::cout << " | ";
                                        std::cout << childY;
                                        std::cout << std::endl;
                    */
                    if (childX >= realX &&
                        childY >= realY &&
                        childX + childWidthDepth < realX + realWidth &&
                        childY + childHeightDepth < realY + realHeight)
                    {
                        searchRecursivelyParticlesCount(children[currentIndex],
                                                        childX,
                                                        childY,
                                                        childWidthDepth,
                                                        childHeightDepth,
                                                        realX,
                                                        realY,
                                                        realWidth,
                                                        realHeight,
                                                        realResolutionX,
                                                        realResolutionY,
                                                        realSizeX,
                                                        realSizeY);
                    }
                }
                else
                {
                    double childX = currentX + xIndex * childWidthDepth;
                    double childY = currentY + yIndex * childHeightDepth;
                    if (childX >= realX &&
                        childY >= realY &&
                        childX < realX + realWidth &&
                        childY < realY + realHeight)
                    {
                        int currentWidthIndex = (int)std::floor(childX / (realResolutionX)); // Intervals are [0,1] ]1,2] ]2,3] ...
                        int currentHeightIndex = (int)std::floor(childY / (realResolutionY));

                        int *globalParticleByFarms = ((*countMatrix)[currentWidthIndex + realSizeX * currentHeightIndex]);
                        /*
                                                std::cout << "== SelectedIndex: ";
                                                std::cout << currentWidthIndex;
                                                std::cout << " | ";
                                                std::cout << currentHeightIndex;
                                                std::cout << std::endl;
                                                std::cout << "child x/y: ";
                                                std::cout << childX;
                                                std::cout << " | ";
                                                std::cout << childY;
                                                std::cout << std::endl;
                        */
                        int *currentParticleByFarms = children[currentIndex]->getNumberOfParticlesByFarm();
                        for (int i = 0; i < numberOfFarms; i++)
                        {
                            globalParticleByFarms[i] = currentParticleByFarms[i];
                        }
                    }
                    /*

*/
                    /*

                    int *currentParticleByFarms = children[currentIndex]->getNumberOfParticlesByFarm();
                    for (int i = 0; i < numberOfFarms; i++)
                    {
                        globalParticleByFarms[i] = currentParticleByFarms[i];
                    }
                    */
                }
            }
        }
    }
}

// TODO : Destructor
ParticlesTree::~ParticlesTree()
{
}