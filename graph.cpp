#include "Graphs\graph.h"

Graph::Graph(){}

Graph::Graph(int noVertices, Point* vertices): noVertices(noVertices), vertices(vertices){}

Point* Graph::findClosestVertex(Point targetVertex){
    Point* closestVertex = nullptr;
    double* shortestDistance = nullptr;
    
    for (int i = 0; i < noVertices; i ++){
        double distance = targetVertex.distance(vertices[i]);
        if (shortestDistance == nullptr){
            *shortestDistance = distance;
            *closestVertex = vertices[i];
        }else{
            if (distance < *shortestDistance){
                *shortestDistance = distance;
                *closestVertex = vertices[i];
            }
        }
    }
    return closestVertex;
}

Point* Graph::fastestPathAllVs(Point startingVertex){
    bool done = false;
    for (int i = 0; i < noVertices; i ++){
        Point targetVertex = vertices[i];
    }
    
    while (!done){

    }
}