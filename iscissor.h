#ifndef iScissor_H
#define iScissor_H

#include <QMainWindow>
#include <iostream>
#include <QLabel>
#include <QProcess>
#include <QString>
#include <QScrollBar>
#include <QFileDialog>
#include <QMessageBox>
#include <ImgLabel.h>
#include "LiveWireDP.h"

namespace Ui {
class iScissor;
}

class iScissor : public QMainWindow
{
    Q_OBJECT

public:
    QImage original_img;
    QImage edge_img;

    int img_height;
    int img_width;

    int mouse_curr_pos_x;
    int mouse_curr_pos_y;

    int seed_x;
    int seed_y;

    LiveWireDP my_LiveWireDP;

    std::vector<weight_t> min_distance;
    std::vector<vertex_t> prev_vertex;

    explicit iScissor(QWidget *parent = 0);

    ~iScissor();
public slots:

private slots:

    void on_actionOpen_triggered();

    void on_actionZoom_in_triggered();
    void on_actionZoom_Out_triggered();

    void on_actionScissorStart_triggered();
    void on_actionScissorStop_triggered();

    void on_actionScissorUndoLast_triggered();

    void on_actionExit_triggered();

    void on_actionSaveMask_triggered();
    void on_actionSaveContour_triggered();


private:
    Ui::iScissor *ui;
    bool image_loaded;
    bool seed_changed;
    //Scaling
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);
    //void adjustScrollBar(QScrollBar *scrollBar, double factor);
    double scaleFactor;
//    void paintEvent(QPaintEvent *e);
//    QLabel *label;
//    QScrollArea *scrollArea;
signals:
    void scale_changed(double);
};

#endif // iScissor_H
