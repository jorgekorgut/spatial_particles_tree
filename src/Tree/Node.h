#pragma once

#include <iostream>

class Node
{
public:
    Node(int numberOfFarms, int numberOfLeaves, int farm)
    {
        /*
        std::cout << "Node Created on farm [";
        std::cout << farm;
        std::cout << "]" << std::endl;
        */
        numberNodeParticlesByFarm = new int[numberOfFarms]();
        numberNodeParticlesByFarm[farm] += 1;

        children = new Node *[numberOfLeaves](); // Initializing 1d matrix of childrens with nullptr
    }

    Node(int numberOfFarms, int numberOfLeaves)
    {
        numberNodeParticlesByFarm = new int[numberOfFarms]();
        children = new Node *[numberOfLeaves](); // Initializing 1d matrix of childrens with nullptr
    }

    Node *updateNode(int index, int numberOfFarms, int numberOfLeaves, int farm)
    {
        if (children[index] == nullptr)
        {
            children[index] = new Node(numberOfFarms, numberOfLeaves);
        }
        children[index]->addFarm(farm);

        return children[index];
    }

    void addFarm(int farm)
    {
        numberNodeParticlesByFarm[farm] += 1;
        /*
                std::cout << "addFarm : ";
                std::cout << "\n n=";
                std::cout << numberNodeParticlesByFarm[farm] << std::endl;
        */
    }

    int *getNumberOfParticlesByFarm()
    {
        return numberNodeParticlesByFarm;
    }

    Node *getNode(int index)
    {
        return children[index];
    }

    Node **getChildren()
    {
        return children;
    }

    ~Node()
    {
        delete children;
        delete numberNodeParticlesByFarm;
    }

private:
    Node **children;
    int *numberNodeParticlesByFarm;
};
