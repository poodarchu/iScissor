#ifndef ImgLabel_H
#define ImgLabel_H

#include <QLabel>
#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QFileDialog>
#include <QEvent>
#include <QDebug>
#include <iostream>
#include "LiveWireDP.h"
#include <math.h>

class ImgLabel :public QLabel
{
    Q_OBJECT

public:

    ImgLabel(QWidget *parent =0);
    ~ImgLabel();

    QImage original_img;
    QPoint offset;
    QImage mask;
    QImage boundary_mask;

    QVector<QPoint> fixed_wrie_points;
    QVector<QPoint> wire_points;
    QVector<QPoint> seed_points;
    QVector<int> wire_index;

    QPen paintpen_seeds;
    QPen paintpen_wire;
    QPen paintpen_fixed_wire;

    LiveWireDP my_LiveWireDP;
    int img_width,img_height;

    void add_wire_points(int a_current_x,int a_current_y);

    double* compute_cost_link(QImage &img, int i, int j);
    void compute_adjacent_matrix(QImage &img);
    QImage compute_gradient_graph(QImage &img);
    QImage compute_node_pixel(QImage &img);

    void recover_matrix();
    void reset_seeds(int x,int y,int undo);

    bool finish_flag;
    bool *bool_array_boundary;
    bool *bool_array_mask;
    bool *closed_contour;
    bool contour_detected;
    bool toggle;

    void flood_fill(int start_x,int start_y);
    void closed_contour_detect();

    bool inside_img(QPoint p);
    void finish_clear();

private:

    int seed_x, seed_y;

    double scale_factor;
    int current_x, current_y;
    bool paint_seed_flag;
    bool paint_cut_line;

    bool scale_changed;
    bool new_seed_on_new_scale;
    node_list node_graph;
    QImage img_live_wire;

protected:
    void mouseMoveEvent(QMouseEvent *mouse_event);
    void mousePressEvent(QMouseEvent *mouse_event);
    void mouseDoubleClickEvent(QMouseEvent *mouse_event );
    void paintEvent(QPaintEvent *e);

signals:
    void sendMousePosition(QPoint&);
    void sendSeedPosition(QPoint&);

public slots:
    void receive_scale(double);
};

#endif // ImgLabel_H
