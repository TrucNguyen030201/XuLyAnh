#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void DisplayImage(QImage &img, QString title);
    void Histogram_GrayImage(const QImage &img,const int &his_height);
    void Histogram_ColorImage(const QImage &img, const int &his_height);
    int Random(int n);
    QImage imNoise_Gray(QImage &image_in, float lavel);

private slots:
    void on_filename_bt_clicked();

    void on_mucsang_btGray_clicked();

    void on_mucsang_btColor_clicked();

    void on_amban_btGray_clicked();

    void on_amban_btColor_clicked();

    void on_pnguong_btGray_clicked();

    void on_anhxam_clicked();

    void on_bt_histogramxam_clicked();

    void on_bt_histogrammau_clicked();

    void on_bt_loctrungbinh_clicked();

    void on_bt_loctrungvi_clicked();

    void on_bt_themnhieu_clicked();

    void on_bt_Gradient_clicked();

    void on_bt_Robert_clicked();

    void on_bt_Sobel_clicked();

    void on_bt_Gradientmau_clicked();

    void on_bt_tuantu_clicked();

    void on_bt_anmon_clicked();

    void on_bt_gianno_clicked();

    void on_bt_hello_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
