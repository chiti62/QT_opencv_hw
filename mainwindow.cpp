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
    this->cur=this->img.clone();
    this->rslt=this->img.clone();

    ui->label->setPixmap(QPixmap::fromImage(this->Mat2QImage(sml)));
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    if(sldr[1]==1){
        ui->red_horizontalSlider->setEnabled(false);
        this->cur=this->rslt;
    }
    if(sldr[2]==1){
        ui->green_horizontalSlider->setEnabled(false);
        this->cur=this->rslt;
    }
    if(sldr[3]==1){
        ui->blue_horizontalSlider->setEnabled(false);
        this->cur=this->rslt;
    }
    if(sldr[4]==1){
        ui->contrast_horizontalSlider->setEnabled(false);
        this->cur=this->rslt;
    }
    sldr[0]=1;
    cv::Mat dst;
    dst = this->cur.clone();//this 指定mainwindow的變數
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
    this->rslt=dst;
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
    if(sldr[0]==1){
        ui->horizontalSlider->setEnabled(false);
        this->cur=this->rslt;
    }
    if(sldr[2]==1){
        ui->green_horizontalSlider->setEnabled(false);
        this->cur=this->rslt;
    }
    if(sldr[3]==1){
        ui->blue_horizontalSlider->setEnabled(false);
        this->cur=this->rslt;
    }
    if(sldr[4]==1){
        ui->contrast_horizontalSlider->setEnabled(false);
        this->cur=this->rslt;
    }
    sldr[1]=1;
    cv::Mat dst;
    dst = this->cur.clone();
    QVector<int> valueVec(3);
    valueVec[0] = ui->blue_horizontalSlider->value();
    valueVec[1] = ui->green_horizontalSlider->value();
    valueVec[2] = ui->red_horizontalSlider->value();
    this->changeColor(this->cur,dst,valueVec);
    this->showImage(dst);
    this->rslt=dst;
}

void MainWindow::on_green_horizontalSlider_valueChanged(int value)
{
    if(sldr[0]==1){
        ui->horizontalSlider->setEnabled(false);
        this->cur=this->rslt;
    }
    if(sldr[1]==1){
        ui->red_horizontalSlider->setEnabled(false);
        this->cur=this->rslt;
    }
    if(sldr[3]==1){
        ui->blue_horizontalSlider->setEnabled(false);
        this->cur=this->rslt;
    }
    if(sldr[4]==1){
        ui->contrast_horizontalSlider->setEnabled(false);
        this->cur=this->rslt;
    }
    sldr[2]=1;
    cv::Mat dst;
    dst = this->cur.clone();
    QVector<int> valueVec(3);
    valueVec[0] = ui->blue_horizontalSlider->value();
    valueVec[1] = ui->green_horizontalSlider->value();
    valueVec[2] = ui->red_horizontalSlider->value();
    this->changeColor(this->cur,dst,valueVec);
    this->showImage(dst);
    this->rslt=dst;
}

void MainWindow::on_blue_horizontalSlider_valueChanged(int value)
{
    if(sldr[0]==1){
        ui->horizontalSlider->setEnabled(false);
        this->cur=this->rslt;
    }
    if(sldr[1]==1){
        ui->red_horizontalSlider->setEnabled(false);
        this->cur=this->rslt;
    }
    if(sldr[2]==1){
        ui->green_horizontalSlider->setEnabled(false);
        this->cur=this->rslt;
    }
    if(sldr[4]==1){
        ui->contrast_horizontalSlider->setEnabled(false);
        this->cur=this->rslt;
    }
    sldr[3]=1;
    cv::Mat dst;
    dst = this->cur.clone();
    QVector<int> valueVec(3);
    valueVec[0] = ui->blue_horizontalSlider->value();
    valueVec[1] = ui->green_horizontalSlider->value();
    valueVec[2] = ui->red_horizontalSlider->value();
    this->changeColor(this->img,dst,valueVec);
    this->showImage(dst);
    this->rslt=dst;
}

void MainWindow::on_grayscale_pushButton_clicked()
{
    ui->horizontalSlider->setEnabled(false);
    ui->red_horizontalSlider->setEnabled(false);
    ui->green_horizontalSlider->setEnabled(false);
    ui->blue_horizontalSlider->setEnabled(false);
    ui->blur_pushButton->setEnabled(false);
    ui->contrast_horizontalSlider->setEnabled(false);
    cv::Mat src = this->rslt;
    cv::Mat dst;
    dst.create(cv::Size(src.cols,src.rows),CV_8UC1);
    for(int i = 0 ;i <this->img.rows ; i++){
        for(int j = 0 ;j <this->img.cols ; j++){
            dst.at<uchar>(i,j)=(src.at<cv::Vec3b>(i,j)[0]+src.at<cv::Vec3b>(i,j)[1]+src.at<cv::Vec3b>(i,j)[2])/3;
        }
    }
    this->showImage(dst);
    this->rslt=dst;
}

void MainWindow::on_blur_pushButton_clicked()
{
    if(sldr[0]==1)
        ui->horizontalSlider->setEnabled(false);
    if(sldr[1]==1)
        ui->red_horizontalSlider->setEnabled(false);
    if(sldr[2]==1)
        ui->green_horizontalSlider->setEnabled(false);
    if(sldr[3]==1)
        ui->blue_horizontalSlider->setEnabled(false);
    if(sldr[4]==1)
        ui->contrast_horizontalSlider->setEnabled(false);

    cv::Mat src = this->rslt.clone();
    cv::Mat dst = this->rslt.clone();

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
    this->rslt=dst.clone();
    this->cur=dst.clone();
}

void MainWindow::on_actionSave_triggered()
{
    cv::imwrite("Result.bmp",this->rslt);
}

void MainWindow::on_negative_clicked()
{
    if(sldr[0]==1)
        ui->horizontalSlider->setEnabled(false);
    if(sldr[1]==1)
        ui->red_horizontalSlider->setEnabled(false);
    if(sldr[2]==1)
        ui->green_horizontalSlider->setEnabled(false);
    if(sldr[3]==1)
        ui->blue_horizontalSlider->setEnabled(false);
    if(sldr[4]==1)
        ui->contrast_horizontalSlider->setEnabled(false);
    cv::Mat dst=this->rslt.clone();

    for(int i = 0 ;i <this->img.rows ; i++){
        for(int j = 0 ;j <this->img.cols ; j++){
            for(int k = 0 ;k <this->img.channels() ; k++){//channels:rgb
                (dst.at<cv::Vec3b>(i,j)[k])=255-(dst.at<cv::Vec3b>(i,j)[k]);
            }
        }
    }
    this->showImage(dst);
    this->rslt=dst;
    this->cur=dst.clone();
}


void MainWindow::on_contrast_horizontalSlider_valueChanged(int value)
{
    if(sldr[0]==1){
        ui->horizontalSlider->setEnabled(false);
        this->cur=this->rslt;
    }
    if(sldr[1]==1){
        ui->red_horizontalSlider->setEnabled(false);
        this->cur=this->rslt;
    }
    if(sldr[2]==1){
        ui->green_horizontalSlider->setEnabled(false);
        this->cur=this->rslt;
    }
    if(sldr[3]==1){
        ui->blue_horizontalSlider->setEnabled(false);
        this->cur=this->rslt;
    }
    sldr[4]=1;
    float newV = value/10.0;

        cv::Mat dst=this->cur.clone();
        for(int i = 0 ;i < this->img.rows ; i++)
        {
            for(int j = 0 ;j < this->img.cols ; j++)
            {
                for(int k = 0 ;k < this->img.channels() ; k++)
                {
                    if(this->img.at<cv::Vec3b>(i,j)[k]*newV > 255)
                    {
                        dst.at<cv::Vec3b>(i,j)[k] = 255;
                    }
                    else if(this->img.at<cv::Vec3b>(i,j)[k]*newV < 0)
                    {
                        dst.at<cv::Vec3b>(i,j)[k] = 0;
                    }
                    else
                    {
                        dst.at<cv::Vec3b>(i,j)[k] = this->img.at<cv::Vec3b>(i,j)[k]*newV;
                    }

                }
            }
        }

        this->showImage(dst);
        this->rslt=dst;
}
