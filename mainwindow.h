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

private:
    Ui::MainWindow *ui;

    cv::Mat img;

    cv::Mat sml;

    cv::Mat rst;

    void changeColor(const cv::Mat &src , cv::Mat &dst, QVector<int> value);

    QImage Mat2QImage(const cv::Mat src);

    void showImage(const cv::Mat &src);
};

#endif // MAINWINDOW_H
