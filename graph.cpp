#include "Graphs\graph.h"

Graph::Graph(){}

Graph::Graph(int noVertices, Point* vertices): noVertices(noVertices), vertices(vertices){}

Point* Graph::findClosestVertex(Point targetVertex){
    for (int i = 0; i < noVertices; i ++){

    }
}

Point* Graph::fastestPathAllVs(Point* startingVertex){
    bool done = false;
    for (int i = 0; i < noVertices; i ++){
        Point targetVertex = vertices[i];
    }
    Point* closestVertex = findClosestVertex(targetVertex);
    while (!done){

    }
}