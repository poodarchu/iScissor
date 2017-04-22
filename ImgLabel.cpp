#include "ImgLabel.h"

#include <QMessageBox>

using namespace std;

ImgLabel::ImgLabel(QWidget *parent):QLabel(parent) {

    this->setMouseTracking(true);

    paint_seed_flag=true;
    contour_detected=false;
    paint_cut_line=true;
    finish_flag=true;
    scale_changed=false;
    new_seed_on_new_scale=false;
    scale_factor=1;

    paintpen_seeds.setWidth(5);
    paintpen_seeds.setColor(Qt::red);

    paintpen_wire.setWidth(2);
    paintpen_wire.setColor(Qt::blue);

    paintpen_fixed_wire.setWidth(2);
    paintpen_fixed_wire.setColor(Qt::yellow);
}

ImgLabel::~ImgLabel(){
}

void ImgLabel::mouseMoveEvent(QMouseEvent *mouse_event)
{
    QPoint mouse_pos = mouse_event->pos();
    if(mouse_pos.x()<=this->size().width() && mouse_pos.y()<=this->size().height() && !finish_flag) {
        if(mouse_pos.x()>=0 && mouse_pos.y()>=0) {
            current_x = (int)mouse_pos.x()/scale_factor;
            current_y = (int)mouse_pos.y()/scale_factor;
            if(paint_cut_line)
                add_wire_points(current_x,current_y);
        }
        if(paint_seed_flag)
          paint_cut_line = true;
    }

    //Move the Image By dragging using right click
    if(mouse_event->buttons() & Qt::RightButton)
        this->move(mapToParent(mouse_event->pos() - offset));
}

void ImgLabel::mousePressEvent(QMouseEvent *mouse_event) {
    if(mouse_event->button() == Qt::LeftButton&&!finish_flag) {
        paint_seed_flag = false;
        QPoint seed_pos = mouse_event->pos();
        if(seed_pos.x()<=this->size().width() && seed_pos.y()<=this->size().height()) {
            if(seed_pos.x()>=0 && seed_pos.y()>=0) {
                seed_x = (int)(seed_pos.x()/scale_factor);
                seed_y = (int)(seed_pos.y()/scale_factor);

                if(!seed_points.isEmpty()){
                    QPoint p = seed_points.first();
                      if(abs(seed_x-p.x())<10 && abs(seed_y-p.y())<10) {
                          add_wire_points(p.x(),p.y());
                          fixed_wrie_points.append(wire_points);
                          finish_flag = true;
                          closed_contour_detect();
                          return;
                        }
                }
                QPoint temp_p;
                temp_p.setX(seed_x);
                temp_p.setY(seed_y);
                seed_points.append(temp_p);
                paint_seed_flag=true;

                if(paint_cut_line) {
                    fixed_wrie_points.append(wire_points);
                    wire_index.append(fixed_wrie_points.size());
                }
            }
        }

        int seed_index = seed_y * img_width + seed_x;

        this->recover_matrix();

        my_LiveWireDP.compute_paths(seed_index,node_graph,img_width,img_height);
    }

    if(mouse_event->button()==Qt::RightButton)
        offset = mouse_event->pos();
}

void ImgLabel::mouseDoubleClickEvent(QMouseEvent * mouse_event)
{
    if(mouse_event->button() == Qt::LeftButton&&!finish_flag) {

        QPoint p = seed_points.first();

        add_wire_points(p.x(),p.y());

        fixed_wrie_points.append(wire_points);

        finish_flag = true;

        closed_contour_detect();
    }
    if(mouse_event->button() == Qt::RightButton) {
        this->setPixmap(QPixmap::fromImage(this->compute_gradient_graph(original_img)));
        this->adjustSize();
    }
}

void ImgLabel::paintEvent(QPaintEvent *e)
{
    QLabel::paintEvent(e);
    if(paint_seed_flag || paint_cut_line)
    {

        QImage tmp = original_img;
        QPainter painter(&tmp);
        painter.setPen(paintpen_seeds);
        QPoint pt;
        foreach (pt,seed_points) {
            painter.drawPoint(pt);
        }
        painter.setPen(paintpen_wire);
        if(!finish_flag){
            foreach(pt, wire_points) {
                painter.drawPoint(pt);
            }
        }

        painter.setPen(paintpen_fixed_wire);
        int count = 0;
        foreach(pt,fixed_wrie_points) {
            if(contour_detected) {
                if(toggle) {
                    if(count%5 == 0)
                        painter.drawPoint(pt);
                } else {
                    if(count%5 == 1)
                        painter.drawPoint(pt);
                }
                count++;
            } else {
                painter.drawPoint(pt);
            }
        }
        if(contour_detected) {
            if(toggle)
                toggle=false;
            else
                toggle=true;
        }

        this->setPixmap(QPixmap::fromImage(tmp));
        paint_seed_flag = false;
    }
}

void ImgLabel::receive_scale(double scale) {
    scale_factor=scale;
    scale_changed=true;
}

void ImgLabel::add_wire_points(int a_current_x, int a_current_y) {
    wire_points.clear();
    wire_points = my_LiveWireDP.show_path(a_current_x,a_current_y,node_graph,img_width);
}

void ImgLabel::reset_seeds(int x, int y, int undo) {
    seed_x = x;
    seed_y = y;

    int seed_index = seed_y * img_width + seed_x;
    this->recover_matrix();
    if(undo == 0)
      my_LiveWireDP.compute_paths(seed_index, node_graph, img_width, img_height);
}

double* ImgLabel::compute_cost_link(QImage &img, int i, int j)
{
     double *costlink = new double[8];

     double RDlink[8];
     double GDlink[8];
     double BDlink[8];

     uint RawColor[8];

     if((i+1) < img_width)
        RawColor[0] = img.pixel(i+1, j);
     if((i+1) < img_width && (j-1) >= 0)
        RawColor[1] = img.pixel(i+1, j-1);
     if((j-1) >= 0)
        RawColor[2] = img.pixel(i, j-1);
     if((i-1) >= 0 && (j-1) >= 0)
        RawColor[3] = img.pixel(i-1, j-1);
     if((i-1) >= 0)
        RawColor[4] = img.pixel(i-1, j);
     if((i-1) >= 0 && (j+1) < img_height)
        RawColor[5] = img.pixel(i-1, j+1);
     if((j+1) < img_height)
        RawColor[6] = img.pixel(i, j+1);
     if((i+1) < img_width && (j+1) < img_height)
        RawColor[7] = img.pixel(i+1, j+1);

     for(int k=0; k < 8; k++) {
         if(k==0 && (i+1)<img_width) {
             RDlink[k]=abs((qRed(RawColor[2])+qRed(RawColor[1]))/2-(qRed(RawColor[6])+qRed(RawColor[7]))/2)/2;
             GDlink[k]=abs((qGreen(RawColor[2])+qGreen(RawColor[1]))/2-(qGreen(RawColor[6])+qGreen(RawColor[7]))/2)/2;
             BDlink[k]=abs((qBlue(RawColor[2])+qBlue(RawColor[1]))/2-(qBlue(RawColor[6])+qBlue(RawColor[7]))/2)/2;
         } else if(k==1&&(i+1)<img_width&&(j-1)>=0) {
             RDlink[k]=abs((qRed(RawColor[2])-qRed(RawColor[0])))/sqrt(2.0);
             GDlink[k]=abs((qGreen(RawColor[2])-qGreen(RawColor[0])))/sqrt(2.0);
             BDlink[k]=abs((qBlue(RawColor[2])-qBlue(RawColor[0])))/sqrt(2.0);

         } else if(k==2&&(j-1)>=0) {
             RDlink[k]=abs((qRed(RawColor[3])+qRed(RawColor[4]))/2-(qRed(RawColor[1])+qRed(RawColor[0]))/2)/2;
             GDlink[k]=abs((qGreen(RawColor[3])+qGreen(RawColor[4]))/2-(qGreen(RawColor[1])+qGreen(RawColor[0]))/2)/2;
             BDlink[k]=abs((qBlue(RawColor[3])+qBlue(RawColor[4]))/2-(qBlue(RawColor[1])+qBlue(RawColor[0]))/2)/2;

         } else if(k==3&&(j-1)>=0&&(i-1)>=0) {
             RDlink[k]=abs((qRed(RawColor[2])-qRed(RawColor[4])))/sqrt(2.0);
             GDlink[k]=abs((qGreen(RawColor[2])-qGreen(RawColor[4])))/sqrt(2.0);
             BDlink[k]=abs((qBlue(RawColor[2])-qBlue(RawColor[4])))/sqrt(2.0);
         } else if(k==4&&(i-1)>=0) {
             RDlink[k]=abs((qRed(RawColor[3])+qRed(RawColor[2]))/2-(qRed(RawColor[5])+qRed(RawColor[6]))/2)/2;
             GDlink[k]=abs((qGreen(RawColor[3])+qGreen(RawColor[2]))/2-(qGreen(RawColor[5])+qGreen(RawColor[6]))/2)/2;
             BDlink[k]=abs((qBlue(RawColor[3])+qBlue(RawColor[2]))/2-(qBlue(RawColor[5])+qBlue(RawColor[6]))/2)/2;

         } else if(k==5&&(i-1)>=0&&(j+1)<img_height) {
             RDlink[k]=abs((qRed(RawColor[6])-qRed(RawColor[4])))/sqrt(2.0);
             GDlink[k]=abs((qGreen(RawColor[6])-qGreen(RawColor[4])))/sqrt(2.0);
             BDlink[k]=abs((qBlue(RawColor[6])-qBlue(RawColor[4])))/sqrt(2.0);
         } else if(k==6&&(j+1)<img_height) {
             RDlink[k]=abs((qRed(RawColor[4])+qRed(RawColor[5]))/2-(qRed(RawColor[0])+qRed(RawColor[7]))/2)/2;
             GDlink[k]=abs((qGreen(RawColor[4])+qGreen(RawColor[5]))/2-(qGreen(RawColor[0])+qGreen(RawColor[7]))/2)/2;
             BDlink[k]=abs((qBlue(RawColor[4])+qBlue(RawColor[5]))/2-(qBlue(RawColor[0])+qBlue(RawColor[7]))/2)/2;

         } else if(k==7&&(i+1)<img_width&&(j+1)<img_height) {
             RDlink[k]=abs((qRed(RawColor[6])-qRed(RawColor[0])))/sqrt(2.0);
             GDlink[k]=abs((qGreen(RawColor[6])-qGreen(RawColor[0])))/sqrt(2.0);
             BDlink[k]=abs((qBlue(RawColor[6])-qBlue(RawColor[0])))/sqrt(2.0);
         } else {
             RDlink[k]=max_weight ;
             GDlink[k]=max_weight ;
             BDlink[k]=max_weight ;
         }
     }

     for(int k = 0; k < 8; k++) {
         costlink[k]=sqrt((255-RDlink[k])*(255-RDlink[k])+(255-GDlink[k])*(255-GDlink[k])+(255-BDlink[k])*(255-BDlink[k]))/3;
         int a=1;
         costlink[k]=255*(1/(1+exp(-a*costlink[k]+127.5*a)));
     }

     return costlink;
}

QImage ImgLabel::compute_gradient_graph(QImage &img) {
    int W=img_width*3;
    int H=img_height*3;

    QImage temp(W,H,QImage::Format_RGB32);
    temp.fill(Qt::GlobalColor::black);

    for(int i=0;i<img_width;i++)
        for(int j=0;j<img_height;j++) {
           int index=j*img_width+i; //the index of the node
           int new_i=i*3+1;
           int new_j=j*3+1;
           QPoint p(new_i,new_j);
           QPoint q(i,j);
           temp.setPixel(p,img.pixel(q));
           for(int k=0;k<8;k++) {
               int offsetx,offsety;
               node_graph[index]->neighbour(offsetx,offsety,k);//get the offset of each nodes
               int n_p=new_i+offsetx;//this nodes x-axis
               int n_q=new_j+offsety;//this nodes y-axis
               QPoint cost_graph(n_p,n_q);
               if(n_p>=0&&n_q>=0&&n_p<img_width&&n_q<img_height) {
                  double cost=node_graph[index]->link_cost[k];
                  //uint rgb=QColor(cost);  //problem here
                  temp.setPixel(cost_graph,cost);
               } else continue;
           }
        }
     return temp;
}

QImage ImgLabel::compute_node_pixel(QImage &img) {
    int W=img_width*3;
    int H=img_height*3;
    QImage temp(W,H,QImage::Format_RGB32);
    temp.fill(Qt::GlobalColor::black);

    for(int i=0;i<img_width;i++)
        for(int j=0;j<img_height;j++)
        {
           QPoint p(i*3+1,j*3+1);
           QPoint q(i,j);
           temp.setPixel(p,img.pixel(q));
        }
    return temp;
}

void ImgLabel::compute_adjacent_matrix(QImage &img) {
    node_graph=node_list(img_height*img_width);

    for(int i=0;i<img_width;i++)
    {
        for(int j=0;j<img_height;j++)
        {
            int index=j*img_width+i;
            double *temp_costLink=compute_cost_link(img,i,j);
            node_graph[index]=new Node();
            node_graph[index]->column=i;
            node_graph[index]->row=j;
            node_graph[index]->link_cost = temp_costLink;
        }
    }
}

void ImgLabel::recover_matrix() {
    for(int i=0;i<img_width;i++) {
        for(int j=0;j<img_height;j++) {
            int index=j*img_width+i;
            node_graph[index]->prev_node=NULL;
            node_graph[index]->total_cost=max_weight;
            node_graph[index]->state=0;
        }
    }
}

void ImgLabel::flood_fill(int start_x,int start_y) {
    QImage temp(original_img.width(),original_img.height(),QImage::Format_ARGB32);
    mask=temp;
    int size_array=original_img.width()*original_img.height();
    bool_array_boundary = (bool*)malloc(sizeof(bool)*size_array);
    bool_array_mask= (bool*)malloc(sizeof(bool)*size_array);

    for(int i=0;i<size_array;i++) {
        bool_array_boundary[i]=false;
        bool_array_mask[i]=false;
    }

    QPoint pt;
    int i;int j;
    foreach(pt,fixed_wrie_points) {
        i=pt.x();j=pt.y();
        bool_array_boundary[j*original_img.width()+i]=true;
    }

    mask.fill(qRgba(0,0,0,0));

    QPoint start_p(start_x,start_y);

    if(!inside_img(start_p))
        return;
    QVector<QPoint> pointQueue;
    pointQueue.append(start_p);
    while(!pointQueue.empty()) {
        QPoint p=pointQueue.last();
        pointQueue.removeLast();
        if (inside_img(p)) {
            int index=p.y()*original_img.width()+p.x();
            if (!(bool_array_boundary[index]) && !bool_array_mask[index]) {
                bool_array_mask[index]=true;
                pointQueue.append(QPoint(p.x()+1,p.y()));
                pointQueue.append(QPoint(p.x()-1,p.y()));
                pointQueue.append(QPoint(p.x(),p.y()+1));
                pointQueue.append(QPoint(p.x(),p.y()-1));
            }
        }
    }

    for(int i=0;i<size_array;i++) {
        if(!bool_array_mask[i]) {
            int x=i%original_img.width();
            int y=(int)(i/original_img.width());
            QPoint p(x,y);
            mask.setPixel(p,original_img.pixel(p));
        }
    }

    QString fileName = QFileDialog::getSaveFileName(this,"Save",QDir::currentPath(),"PNG-Files (*.png)");
    if (!fileName.isEmpty()) {
         if (mask.isNull()) {
             QMessageBox::information(this, tr("Error"), tr("Please Load an Image First!"));
             return;
         }

    mask.save(fileName);
  }
}

bool ImgLabel::inside_img(QPoint p) {
    return (p.x()>= 0) && (p.x() < mask.width()) && (p.y()>= 0) && (p.y() < mask.height());
}

void ImgLabel::closed_contour_detect() {
    int size_array=original_img.width()*original_img.height();
    closed_contour = (bool*)malloc(sizeof(bool)*size_array);
    for(int i=0;i<size_array;i++) {
        closed_contour[i]=false;
    }

    QPoint pt;
    int i;int j;
    foreach(pt,fixed_wrie_points) {
        i=pt.x();j=pt.y();
        int index=j*original_img.width()+i;
        if(closed_contour[index])
            contour_detected=true;
        closed_contour[index]=true;
    }
}

void ImgLabel::finish_clear() {
    finish_flag=true;
    fixed_wrie_points.clear();
    wire_points.clear();
    seed_points.clear();
    wire_index.clear();
    recover_matrix();
    contour_detected=false;
}
