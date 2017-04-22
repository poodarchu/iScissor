#include "dijkstra.h"
using namespace std;

Dijkstra::Dijkstra()
{

}
struct cmp{
    bool operator() ( Node* a, Node* b ){
        return a->totalCost> b->totalCost; }
};
QVector<QPoint> Dijkstra::show_path(int i,int j,node_list &node_graph,int width)
{
      QVector<QPoint> path_vector;
      int dest=j*width+i;

      QPoint temp;
      temp.setX((int)i);
      temp.setY((int)j);
      path_vector.append(temp);
      while(node_graph[dest]->prevNode!=NULL)
      {
             Node *next=node_graph[dest]->prevNode;
             int p=next->column;
             int q=next->row;
             temp.setX((int)p);
             temp.setY((int)q);
             path_vector.append(temp);
             dest=q*width+p;
      }

      return path_vector;
}

void Dijkstra::compute_paths(vertex_t source, node_list &node_graph,int width,int height)
{
         //cout<<"size:"<<node_graph.size()<<endl;
         node_graph[source]->totalCost=0;
         priority_queue<Node*, vector<Node*>, cmp > qq;
         qq.push(node_graph[source]);

         while(!qq.empty())
         {
                 Node *temp=qq.top();
                 qq.pop();
                 //cout<<"cost:"<<temp->totalCost<<endl;
                 //int x=temp->state;
                 //if(x==1)continue;//alright inside the list
                 temp->state=2;//mark the state to be visited
                 int p=temp->column;//x_axis
                 int q=temp->row;//y_axis
                 int index=q*width+p;
                 //cout<<"x sequence:"<<p<<" y sequence:"<<q<<endl;
                 //cout<<"index sequence:"<<index<<endl;

                 for(int i=0;i<8;i++)
                 {
                     int offsetx,offsety,new_index;
                     temp->neighbour(offsetx,offsety,i);//get the offset of each nodes
                     int n_p=p+offsetx;//this nodes axis
                     int n_q=q+offsety;//this nodes axis
                     //cout<<"x sequence:"<<n_p<<" y sequence:"<<n_q<<endl;
                     if(n_p>=0&&n_q>=0&&n_p<width&&n_q<height) {new_index=n_q*width+n_p;} //inside the range
                     else continue;
                     int new_state=node_graph[new_index]->state;
                     /*
                     for(int i=0;i<8;i++)
                     {
                         cout<<node_graph[new_index]->linkCost[i]<<endl;
                     }*/
                     if(new_state!=2)//not visited now
                     {
                           if(new_state==0)  //still initial (not visit)
                           {
                              node_graph[new_index]->prevNode=node_graph[index];//set predecessor
                              node_graph[new_index]->totalCost=node_graph[index]->totalCost+node_graph[index]->linkCost[i];
                              node_graph[new_index]->state=1;//active
                              qq.push(node_graph[new_index]);

                           }
                           else if(new_state==1)
                           {
                               if(node_graph[index]->totalCost+node_graph[index]->linkCost[i]<node_graph[new_index]->totalCost)
                               node_graph[new_index]->prevNode=node_graph[index];
                               node_graph[new_index]->totalCost=node_graph[index]->totalCost+node_graph[index]->linkCost[i];
                           }
                     }

                 }

             }
}



