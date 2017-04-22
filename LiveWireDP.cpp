#include "LiveWireDP.h"

using namespace std;

LiveWireDP::LiveWireDP() {
}

struct compare{
  bool operator() ( Node* a, Node* b ){
    return a->total_cost > b->total_cost;
  }
};

QVector<QPoint> LiveWireDP::show_path(int i, int j, node_list &node_graph, int width) {

      QVector<QPoint> path_vector;
      int dest = j*width + i;

      QPoint temp;
      temp.setX(i);
      temp.setY(j);
      path_vector.append(temp);

      while(node_graph[dest]->prev_node != nullptr) {
             Node *next = node_graph[dest]->prev_node;
             int p = next->column;
             int q = next->row;

             temp.setX(p);
             temp.setY(q);
             path_vector.append(temp);

             dest = q*width + p;
      }

      return path_vector;
}

void LiveWireDP::compute_paths(vertex_t source, node_list &node_graph, int width, int height) {

         node_graph[source]->total_cost = 0;

         priority_queue<Node*, vector<Node*>, compare> prior_queue;
         prior_queue.push(node_graph[source]);

         // BFS
         while(!prior_queue.empty()) {

                 Node *temp = prior_queue.top();
                 prior_queue.pop();

                 temp->state = 2;//mark the state to be visited

                 int p = temp->column;//x_axis
                 int q = temp->row;//y_axis

                 int index = q*width + p;

                 for(int i = 0; i < 8; i++) {
                     int offsetx, offsety, new_index;

                     temp->neighbour(offsetx, offsety, i);//get the offset of each nodes
                     int n_p = p + offsetx;//this nodes axis
                     int n_q = q + offsety;//this nodes axis

                     if(n_p >= 0 && n_q >= 0 && n_p < width && n_q < height) {
                       new_index = n_q*width + n_p;
                     } //inside the range

                     int new_state = node_graph[new_index]->state;

                     if(new_state != 2) { //not visited now
                           if(new_state == 0) {  //still initial (not visit)
                              node_graph[new_index]->prev_node = node_graph[index];
                              node_graph[new_index]->total_cost = node_graph[index]->total_cost + node_graph[index]->link_cost[i];
                              node_graph[new_index]->state = 1;//active

                              prior_queue.push(node_graph[new_index]);
                            } else if(new_state == 1) {
                               if(node_graph[index]->total_cost + node_graph[index]->link_cost[i] < node_graph[new_index]->total_cost)
                               node_graph[new_index]->prev_node = node_graph[index];
                               node_graph[new_index]->total_cost = node_graph[index]->total_cost + node_graph[index]->link_cost[i];
                           }
                     }
                 }
             }
}
