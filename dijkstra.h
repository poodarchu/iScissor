#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <QObject>
#include <QWidget>

#include <limits> // for numeric_limits

#include <queue>
#include <utility> // for pair
#include <algorithm>
#include <iterator>

typedef int vertex_t;
typedef double weight_t;
const weight_t max_weight = std::numeric_limits<double>::infinity();

struct Node{
    double *linkCost;
    int state;//0-->init 1-->activite(in the queue) 2-->visited
    double totalCost;
    Node *prevNode;
    int column;
    int row;
    //Node(double cost[8],int s=0,double c=max_weight,Node *pre=NULL,int i=0,int j=0)
        //: linkCost(cost),state(s),totalCost(c),prevNode(pre),column(i),row(j){}
    Node () {prevNode=NULL;totalCost=max_weight;state=0;}
    void neighbour(int &offsetX, int &offsetY, int linkIndex)
    {

        if (linkIndex==0)
        {
            offsetX = 1;
            offsetY = 0;
        }
        else if (linkIndex==1)
        {
            offsetX = 1;
            offsetY = -1;
        }
        else if (linkIndex==2)
        {
            offsetX = 0;
            offsetY = -1;
        }
        else if (linkIndex==3)
        {
            offsetX = -1;
            offsetY = -1;
        }
        else if (linkIndex==4)
        {
            offsetX = -1;
            offsetY = 0;
        }
        else if (linkIndex==5)
        {
            offsetX = -1;
            offsetY = 1;
        }
        else if (linkIndex==6)
        {
            offsetX = 0;
            offsetY = 1;
        }
        else if (linkIndex==7)
        {
            offsetX = 1;
            offsetY = 1;
        }
    }

};
typedef std::vector<Node*> node_list;
//typedef std::vector<std::vector<neighbor> > adjacency_list_t;
typedef std::pair<weight_t, vertex_t> weight_vertex_pair_t;

class Dijkstra
{
public:
    Dijkstra();
    void compute_paths(vertex_t source,node_list &node_graph,int width,int height);
    QVector<QPoint> show_path(int i,int j,node_list &node_graph,int h);
};

#endif // DIJKSTRA_H
