#pragma once

class Node
{
public:
    Node();
    void addNode(int index, Node *node);

private:
    Node **children;
    int * numberNodeParticlesByFarm;
};
