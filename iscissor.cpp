#include "iScissor.h"
#include "ui_iScissor.h"

#include<iostream>

iScissor::iScissor(QWidget *parent): QMainWindow(parent), ui(new Ui::iScissor)
{
    ui->setupUi(this);

    connect(this,SIGNAL(scale_changed(double)),ui->label,SLOT(receive_scale(double)));

    ui->label->setText("");
    ui->label->setBackgroundRole(QPalette::Base);
    ui->label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->label->setScaledContents(true);

    ui->scrollArea->setBackgroundRole(QPalette::Dark);

    image_loaded=false;
    scaleFactor = 1.0;
}

iScissor::~iScissor()
{
    delete ui;
}


void iScissor::on_actionOpen_triggered()
{
    //qDebug() << "open()";
    QString fileName = QFileDialog::getOpenFileName(this,
                                     tr("Open File"), QDir::currentPath());

    if (!fileName.isEmpty()) {
         QImage Original_Image(fileName);
         if (Original_Image.isNull()) {
             QMessageBox::information(this, tr("Image Viewer"), tr("Cannot load %1.").arg(fileName));
             return;
         }

         original_img=Original_Image.copy();
         img_height=original_img.height();
         img_width=original_img.width();
         ui->label->setPixmap(QPixmap::fromImage(original_img));
         ui->label->original_img=original_img;
         ui->label->img_width=original_img.width();
         ui->label->img_height=original_img.height();
         ui->label->compute_adjacent_matrix(original_img);//compute the graph
         image_loaded=true;
         ui->label->adjustSize();//Adjust Size according to the original image
         edge_img=original_img.copy();

         ui->label->finish_clear();
         ui->actionZoom_in->setEnabled(true);
         ui->actionZoom_Out->setEnabled(true);
         ui->actionScissorStart->setEnabled(true);
    }
}

void iScissor::scaleImage(double factor)
{
    scaleFactor *= factor;
    ui->label->resize(scaleFactor * (ui->label->pixmap()->size()));

    adjustScrollBar(ui->scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(ui->scrollArea->verticalScrollBar(), factor);

}

void iScissor::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
     scrollBar->setValue(int(factor * scrollBar->value()+ ((factor - 1) * scrollBar->pageStep()/2)));
}

void iScissor::on_actionZoom_in_triggered()
{
     scaleImage(1.25);
     emit scale_changed(scaleFactor);
}

void iScissor::on_actionZoom_Out_triggered()
{
    scaleImage(0.8);
     emit scale_changed(scaleFactor);
}

void iScissor::on_actionSaveContour_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Save",QDir::currentPath(),"JPGE files (*.jpg);;PNG-Files (*.png);;BMP-Files (*.bmp);;All Files (*)");
    if (!fileName.isEmpty()) {
    QImage tmp( ui->label->pixmap()->toImage());
         if (tmp.isNull()) {
             QMessageBox::information(this, tr("Error"),
                                      tr("Please Load an Image First!"));
             return;
         }
    tmp.save(fileName);
    }
}

void iScissor::on_actionSaveMask_triggered()
{
    ui->label->flood_fill(0,0);
}

void iScissor::on_actionScissorStart_triggered()
{
    ui->label->finish_flag=false;
    ui->actionScissorStop->setEnabled(true);
    ui->actionScissorUndoLast->setEnabled(true);
    ui->actionScissorStart->setDisabled(true);
}

void iScissor::on_actionScissorStop_triggered()
{
    ui->label->finish_clear();
    ui->actionScissorStop->setDisabled(true);
    ui->actionScissorUndoLast->setDisabled(true);
    ui->actionScissorStart->setEnabled(true);
}

void iScissor::on_actionScissorUndoLast_triggered()
{
    if(!ui->label->seed_points.isEmpty()&&!ui->label->finish_flag)
    {
        ui->label->seed_points.removeLast();
        QPoint pt;
        int undo_flag;
        if(!ui->label->seed_points.isEmpty())
           {pt=ui->label->seed_points.last();undo_flag=0;}
        else{undo_flag=1;}

        ui->label->reset_seeds(pt.x(),pt.y(),undo_flag);
        if(!ui->label->wire_index.isEmpty())
        {
            int indx_1=ui->label->wire_index.last();
            ui->label->wire_index.removeLast();
            int indx_2;
            if(ui->label->wire_index.isEmpty())
            {
                indx_2=0;
            }
            else
            {
                indx_2=ui->label->wire_index.last();
            }
            for(int i=indx_1;i>=indx_2;i--)
            {
                if(!ui->label->fixed_wrie_points.isEmpty())
                ui->label->fixed_wrie_points.removeLast();
            }
        }
    }
}
