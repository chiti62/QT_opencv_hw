#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFileDialog>
#include <QDebug>
#include <QVector>
#include <QImage>
#include <QRgb>
#include <QPixmap>
#include <opencv.hpp>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionLoad_triggered();

    void on_horizontalSlider_valueChanged(int value);

    void on_red_horizontalSlider_valueChanged(int value);

    void on_green_horizontalSlider_valueChanged(int value);

    void on_blue_horizontalSlider_valueChanged(int value);

    void on_grayscale_pushButton_clicked();

    void on_blur_pushButton_clicked();

    void on_actionSave_triggered();

    void on_negative_clicked();


    void on_contrast_horizontalSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;

    cv::Mat sml;

    cv::Mat cur;//可能經過負片或模糊處理

    cv::Mat img;//原圖

    cv::Mat rslt;//輸出的圖(目前顯示在螢幕上的)

    int sldr[5];

    void changeColor(const cv::Mat &src , cv::Mat &dst, QVector<int> value);

    QImage Mat2QImage(const cv::Mat src);

    void showImage(const cv::Mat &src);
};

#endif // MAINWINDOW_H
