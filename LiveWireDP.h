#ifndef LiveWireDP_H
#define LiveWireDP_H

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <limits>
#include <queue>
#include <utility> // for pair
#include <algorithm>
#include <iterator>

#include <QObject>
#include <QWidget>

typedef unsigned int vertex_t;
typedef double weight_t;

const weight_t max_weight = std::numeric_limits<double>::infinity();

struct Node{
    double* link_cost;  // double link_cost[8]
    double total_cost;

    Node *prev_node;

    int state;//0-->init 1-->activite(in the queue) 2-->visited

    int column;
    int row;

    Node() {
      prev_node = NULL;
      total_cost = max_weight;
      state = 0;
    }

    void neighbour(int &offsetX, int &offsetY, int linkIndex)
    {

        if (linkIndex == 0)
        {
            offsetX = 1;
            offsetY = 0;
        }
        else if (linkIndex == 1)
        {
            offsetX = 1;
            offsetY = -1;
        }
        else if (linkIndex == 2)
        {
            offsetX = 0;
            offsetY = -1;
        }
        else if (linkIndex == 3)
        {
            offsetX = -1;
            offsetY = -1;
        }
        else if (linkIndex == 4)
        {
            offsetX = -1;
            offsetY = 0;
        }
        else if (linkIndex == 5)
        {
            offsetX = -1;
            offsetY = 1;
        }
        else if (linkIndex == 6)
        {
            offsetX = 0;
            offsetY = 1;
        }
        else if (linkIndex == 7)
        {
            offsetX = 1;
            offsetY = 1;
        }
    }

};
typedef std::vector<Node*> node_list;

typedef std::pair<weight_t, vertex_t> weight_vertex_pair_t;

class LiveWireDP {
public:
    LiveWireDP();

    void compute_paths(vertex_t source, node_list &node_graph, int width, int height);
    QVector<QPoint> show_path(int i, int j, node_list &node_graph, int width);
};

#endif // LiveWireDP_H
