#include "ParticlesTree.h"
#include <iostream>
#include <algorithm>
#include <cmath>

ParticlesTree::ParticlesTree(double maxWidth, double maxHeight, double minResolution, int leavesNumberX, int leavesNumberY, int nFarms)
{
    width = maxWidth;
    height = maxHeight;
    // resolution = minResolution;

    resolution = minResolution;
    leavesX = leavesNumberX;
    leavesY = leavesNumberY;

    numberOfFarms = nFarms;
    root = new Node(numberOfFarms, leavesX * leavesY);
}

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

// TODO : Optmize tree construction
void ParticlesTree::addNode(const Vector4 &spatialData, int numberOfLeaves)
{
    if (spatialData.x > width || spatialData.y > height)
    {
        return;
    }

    double currentWidth = width;
    double currentHeight = height;
    int currentWidthIndex = 0;
    int currentHeightIndex = 0;
    Node *currentNode = root;

    while (currentWidth > resolution ||
           currentHeight > resolution)
    {
        currentWidthIndex = std::max((int)std::floor(spatialData.x / (currentWidth)) - 1, 0); // Intervals are [0,1] ]1,2] ]2,3] ...
        currentHeightIndex = std::max((int)std::floor(spatialData.y / (currentHeight)) - 1, 0);

        currentNode = currentNode->updateNode(currentWidthIndex + leavesX * currentHeightIndex, numberOfFarms, numberOfLeaves, spatialData.farm);

        if (currentWidth >= resolution)
        {
            currentWidth = currentWidth / leavesX;
        }
        if (currentHeight >= resolution)
        {
            currentHeight = currentHeight / leavesY;
        }
    }

    currentNode->updateNode(currentWidthIndex + leavesX * currentHeightIndex, numberOfFarms, numberOfLeaves, spatialData.farm);
}

// Question : Does it lose in performance ?
/*
int ParticlesTree::findTreeDepth(int maxDimension, int minResolution, int leavesNumber)
{
    return (int)(std::ceil(std::log2(maxDimension / (double)minResolution) / std::log2(leavesNumber)));
}
*/
int ParticlesTree::getTreeDepth()
{
    return treeDepth;
}

// TODO : Destructor
ParticlesTree::~ParticlesTree()
{
}