#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionLoad_triggered()
{
    QString fileName = QFileDialog::getOpenFileName();
    cv::Mat src=cv::imread(fileName.toStdString());

    int width = src.cols;
    int height = src.rows;
    cv::resize(src,src,cv::Size(width/4,height/4));
    this->img = src.clone();
    this->showImage(this->img);
    //cv::Mat sml;

    ui->label->setPixmap(QPixmap::fromImage(this->Mat2QImage(sml)));
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    //cv::Mat dst;
    cv::Mat src = this->img;
    cv::Mat dst(src);
    //dst = this->img.clone();//this 指定mainwindow的變數
    for(int i = 0 ;i <this->img.rows ; i++){
        for(int j = 0 ;j <this->img.cols ; j++){
            for(int k = 0 ;k <this->img.channels() ; k++){//channels:rgb
                if(this->img.at<cv::Vec3b>(i,j)[k]+value > 255){
                    dst.at<cv::Vec3b>(i,j)[k]=255;
                }
                else if(this->img.at<cv::Vec3b>(i,j)[k]+value < 0){
                    dst.at<cv::Vec3b>(i,j)[k]=0;
                }
                else{
                    dst.at<cv::Vec3b>(i,j)[k]=dst.at<cv::Vec3b>(i,j)[k] + value;
                }
            }
        }
    }
    this->showImage(dst);
}

void MainWindow::changeColor(const cv::Mat &src, cv::Mat &dst, QVector<int> value)
{
    for(int i = 0 ;i <this->img.rows ; i++){
        for(int j = 0 ;j <this->img.cols ; j++){
            for(int k = 0 ;k <this->img.channels() ; k++){//channels:rgb
                if(this->img.at<cv::Vec3b>(i,j)[k]+value[k] > 255){
                    dst.at<cv::Vec3b>(i,j)[k]=255;
                }
                else if(this->img.at<cv::Vec3b>(i,j)[k]+value[k] < 0){
                    dst.at<cv::Vec3b>(i,j)[k]=0;
                }
                else{
                    dst.at<cv::Vec3b>(i,j)[k]=dst.at<cv::Vec3b>(i,j)[k] + value[k];
                }
            }
        }
    }
}

QImage MainWindow::Mat2QImage(const cv::Mat src)
{

    if(src.type()==CV_8UC1)
    {
        QVector<QRgb> colorTable;
        for (int i=0; i<256; i++)
            colorTable.push_back(qRgb(i,i,i));
        const uchar *qImageBuffer = (const uchar*)src.data;
        QImage img(qImageBuffer, src.cols, src.rows, src.step, QImage::Format_Indexed8);
        img.setColorTable(colorTable);
        return img;
    }

    if(src.type()==CV_8UC3)
    {
        const uchar *qImageBuffer = (const uchar*)src.data;
        QImage img(qImageBuffer, src.cols, src.rows, src.step, QImage::Format_RGB888);
        return img.rgbSwapped();
    }
    else
    {
        qDebug() << "Error! Can't convert image type.";
        return QImage();
    }
}

void MainWindow::showImage(const cv::Mat &src)
{

    cv::Mat dst;
    //cv::Mat dst(src);
    int width = ui->image_label->width();
    int height = ui->image_label->height();
    double ratio = (double)width / (double)height;
    double imgRatio = src.cols / src.rows;
    if (ratio>imgRatio)
    {
        cv::resize(src,dst,cv::Size(width,src.rows/(src.cols/width)));
    }
    else
    {
        cv::resize(src,dst,cv::Size(src.cols/(src.rows/height),height));
    }
    ui->image_label->setPixmap(QPixmap::fromImage(this->Mat2QImage(dst)));
    sml=dst.clone();
    cv::resize(sml,sml,cv::Size(width/4,height/4));

}
void MainWindow::on_red_horizontalSlider_valueChanged(int value)
{
    //cv::Mat dst;
    cv::Mat src = this->img;
    cv::Mat dst(src);
    QVector<int> valueVec(3);
    valueVec[0] = ui->blue_horizontalSlider->value();
    valueVec[1] = ui->green_horizontalSlider->value();
    valueVec[2] = ui->red_horizontalSlider->value();
    //dst = this->img.clone();
    this->changeColor(this->img,dst,valueVec);
    this->showImage(dst);
}

void MainWindow::on_green_horizontalSlider_valueChanged(int value)
{
    //cv::Mat dst;
    cv::Mat src = this->img;
    cv::Mat dst(src);
    QVector<int> valueVec(3);
    valueVec[0] = ui->blue_horizontalSlider->value();
    valueVec[1] = ui->green_horizontalSlider->value();
    valueVec[2] = ui->red_horizontalSlider->value();
    //dst = this->img.clone();
    this->changeColor(this->img,dst,valueVec);
    this->showImage(dst);
}

void MainWindow::on_blue_horizontalSlider_valueChanged(int value)
{
    //cv::Mat dst;
    cv::Mat src = this->img;
    cv::Mat dst(src);
    QVector<int> valueVec(3);
    valueVec[0] = ui->blue_horizontalSlider->value();
    valueVec[1] = ui->green_horizontalSlider->value();
    valueVec[2] = ui->red_horizontalSlider->value();
    //dst = this->img.clone();
    this->changeColor(this->img,dst,valueVec);
    this->showImage(dst);
}

void MainWindow::on_grayscale_pushButton_clicked()
{
    ui->horizontalSlider->setEnabled(false);
    ui->red_horizontalSlider->setEnabled(false);
    ui->green_horizontalSlider->setEnabled(false);
    ui->blue_horizontalSlider->setEnabled(false);
    ui->blur_pushButton->setEnabled(false);
    cv::Mat src = this->img;
    //cv::Mat dst;
    cv::Mat dst(src);
    dst.create(cv::Size(src.cols,src.rows),CV_8UC1);
    for(int i = 0 ;i <this->img.rows ; i++){
        for(int j = 0 ;j <this->img.cols ; j++){
            dst.at<uchar>(i,j)=(src.at<cv::Vec3b>(i,j)[0]+src.at<cv::Vec3b>(i,j)[1]+src.at<cv::Vec3b>(i,j)[2])/3;
        }
    }
    this->showImage(dst);
    this->img=dst;
}

void MainWindow::on_blur_pushButton_clicked()
{
    cv::Mat src = this->img;
    cv::Mat dst(src);//?????????????????



    for(int i = 1 ;i <src.rows-1 ; i++){
        for(int j = 1 ;j <src.cols-1 ; j++){
            for(int k = 0 ;k <src.channels() ; k++){//channels:rgb
                dst.at<cv::Vec3b>(i,j)[k]=
                        (src.at<cv::Vec3b>(i-1,j-1)[k]+
                         src.at<cv::Vec3b>(i-1,j)[k]+
                         src.at<cv::Vec3b>(i-1,j+1)[k]+
                         src.at<cv::Vec3b>(i,j-1)[k]+
                         src.at<cv::Vec3b>(i,j)[k]+
                         src.at<cv::Vec3b>(i,j+1)[k]+
                         src.at<cv::Vec3b>(i+1,j-1)[k]+
                         src.at<cv::Vec3b>(i+1,j)[k]+
                         src.at<cv::Vec3b>(i+1,j+1)[k])/9;
            }
        }
    }
    this->showImage(dst);
    this->rst=dst.clone();
}

void MainWindow::on_actionSave_triggered()
{
    cv::imwrite("Result.bmp",this->img);
}

void MainWindow::on_negative_clicked()
{
    cv::Mat src = this->img;
    cv::Mat dst(src);

    for(int i = 0 ;i <this->img.rows ; i++){
        for(int j = 0 ;j <this->img.cols ; j++){
            for(int k = 0 ;k <this->img.channels() ; k++){//channels:rgb
                (this->img.at<cv::Vec3b>(i,j)[k])=255-(this->img.at<cv::Vec3b>(i,j)[k]);
//                if(this->img.at<cv::Vec3b>(i,j)[k]+value > 255){
//                    dst.at<cv::Vec3b>(i,j)[k]=255;
//                }
//                else if(this->img.at<cv::Vec3b>(i,j)[k]+value < 0){
//                    dst.at<cv::Vec3b>(i,j)[k]=0;
//                }
//                else{
//                    dst.at<cv::Vec3b>(i,j)[k]=dst.at<cv::Vec3b>(i,j)[k] + value;
//                }
            }
        }
    }
    this->showImage(dst);
}
