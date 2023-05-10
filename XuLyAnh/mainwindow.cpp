#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QPixmap"
#include "QLabel"
#include "QMessageBox"
#include "QtMath"

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

//Nút CHỌN
void MainWindow::on_filename_bt_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open File","D:",
                                                    "*.* All Files;;*.bmp;;*.jpeg;;*.ppm;;*.png;;*.jpg;;.jfif");
    if (filename.isEmpty())
        return;
    ui->filename_ln->setText(filename);

    QPixmap pixmap(filename);
    QLabel *label = new QLabel();
    label->setPixmap(pixmap);
    label->setWindowTitle(QFileInfo(filename).fileName());
    label->show();
}

void MainWindow::DisplayImage(QImage &img, QString title)
{
    QLabel *label = new QLabel();
    label->setPixmap(QPixmap::fromImage(img));
    label->setWindowTitle(title);
    label->show();
}

//xử lí mức sáng - mode: ảnh xám
void MainWindow::on_mucsang_btGray_clicked()
{
    QString filename = ui->filename_ln->text();
    QImage image_in(filename); //đọc ảnh từ file
    QImage image_out(image_in.width(), image_in.height(), QImage::Format_ARGB32);
    int c = ui->mucsang_ln->text().toInt();

    for(int x=0; x<image_in.width(); x++)
        for(int y=0; y<image_in.height(); y++)
        {
            QRgb color = image_in.pixel(x, y);
            int gray_in = qGray(color); //đổi giá trị màu thành xám
            int gray_out = gray_in + c; //thay đổi giá trị sáng tối
            if(gray_out>255)
                gray_out=255;
            else if (gray_out<0)
                gray_out=0;
            QRgb color_out = qRgb(gray_out, gray_out, gray_out); //giá trị điểm ảnh x, y: Ảnh xám
            image_out.setPixel(x, y, color_out);
        }
//    DisplayImage(image_in, QFileInfo(filename).fileName());
    DisplayImage(image_out, QFileInfo(filename).fileName()+"-đã xử lí độ sáng");
}

//Xử lí mức sáng - mode: ảnh màu
void MainWindow::on_mucsang_btColor_clicked()
{
    QString filename = ui->filename_ln->text();
    QImage image_in(filename);
    QImage image_out(image_in.width(), image_in.height(), QImage::Format_ARGB32);

    int c = ui->mucsang_ln->text().toInt();
    for(int x=0; x<image_in.width(); x++)
        for(int y=0; y<image_in.height(); y++)
        {
            QRgb rgb = image_in.pixel(x, y);
            QColor color_in(rgb);
            int h, s, v;
            color_in.getHsv(&h, &s, &v);
            int v_out = v+c;
            if(v_out>255)
                v_out = 255;
            else if(v_out <0)
                v_out = 0;
            QColor color_out = QColor::fromHsv(h, s, v_out);
            image_out.setPixel(x, y, color_out.rgb());
        }
//    DisplayImage(image_in, QFileInfo(filename).fileName());
    DisplayImage(image_out, QFileInfo(filename).fileName()+"-đã xử lí");
}

//Xử lí ảnh âm bản - mode: ảnh xám
void MainWindow::on_amban_btGray_clicked()
{
    QString filename = ui->filename_ln->text();
    QImage image_in(filename);
    QImage image_out(image_in.width(), image_in.height(), QImage::Format_ARGB32);

    for(int x=0; x<image_in.width(); x++)
        for(int y=0; y<image_in.height(); y++)
        {
            QRgb color = image_in.pixel(x, y);
            int gray_in = qGray(color); //đổi giá trị màu thành xám
            int gray_out = 255-gray_in; //đảo ngược màu
            if(gray_out>255)
                gray_out=0;
            else if(gray_out<0)
                gray_out=255;
            QRgb color_out = qRgb(gray_out, gray_out, gray_out); //giá trị điểm ảnh x, y: Ảnh xám
            image_out.setPixel(x, y, color_out);
        }
//    DisplayImage(image_in, QFileInfo(filename).fileName());
    DisplayImage(image_out, QFileInfo(filename).fileName()+"-đã xử lí âm bản");
}

//Xử lí ảnh âm bản - mode: ảnh màu
void MainWindow::on_amban_btColor_clicked()
{
    QString filename = "E:/Qt/XuLyAnh/image/azey.png";
//    QString filename = ui->filename_ln->text();
    QImage image_in(filename);
    QImage image_out(image_in.width(), image_in.height(), QImage::Format_ARGB32);

    for(int x=0; x<image_in.width(); x++)
        for(int y=0; y<image_in.height(); y++)
        {
            QRgb rgb = image_in.pixel(x, y);
            QColor color_in(rgb);
            int r, g, b;
            color_in.getRgb(&r, &g, &b);
            //Xử lí kênh R
            int r_out = 255 - r;
            if(r_out>255)
                r_out = 0;
            else if(r_out<0)
                r_out = 255;
            //Xử lí kênh G
            int g_out = 255-g;
            if(g_out>255)
                g_out = 0;
            else if(g_out<0)
                g_out = 255;
            //Xử lí kênh B
            int b_out = 255-b;
            if(b_out>255)
                b_out = 0;
            else if(b_out<0)
                b_out = 255;

            QColor color_out = QColor::fromRgb(r_out, g_out, b_out);
            image_out.setPixel(x, y, color_out.rgb());
        }
//    DisplayImage(image_in, QFileInfo(filename).fileName());
    DisplayImage(image_out, QFileInfo(filename).fileName()+"-đã xử lí");
}


//Xử lí phân ngưỡng - ảnh xám
void MainWindow::on_pnguong_btGray_clicked()
{
    QString filename = ui->filename_ln->text();
    QImage image_in(filename);
    QImage image_out(image_in.width(), image_in.height(), QImage::Format_ARGB32);
    int c = ui->pnguong_ln->text().toInt();
    for(int x=0; x<image_in.width(); x++)
        for(int y=0; y<image_in.height(); y++)
        {
            QRgb color = image_in.pixel(x, y);
            int gray_in = qGray(color), gray_out; //đổi giá trị màu thành xám
            if(gray_in >= c)
                gray_out=255;
            else
                gray_out=0;
            QRgb color_out = qRgb(gray_out, gray_out, gray_out); //giá trị điểm ảnh x, y: Ảnh xám
            image_out.setPixel(x, y, color_out);
        }
//    DisplayImage(image_in, QFileInfo(filename).fileName());
    DisplayImage(image_out, QFileInfo(filename).fileName()+"-đã xử lí âm bản");
}

void MainWindow::on_anhxam_clicked()
{
    QString filename = ui->filename_ln->text();
    QImage image_in(filename);
    QImage image_out(image_in.width(), image_in.height(), QImage::Format_ARGB32);

    for(int x=0; x<image_in.width(); x++)
        for(int y=0; y<image_in.height(); y++)
        {
            QRgb color = image_in.pixel(x, y);
            int gray = qGray(color); //đổi giá trị màu thành xám
            QRgb color_out = qRgb(gray, gray, gray); //giá trị điểm ảnh x, y: Ảnh xám
            image_out.setPixel(x, y, color_out);
        }
//    DisplayImage(image_in, QFileInfo(filename).fileName());
    DisplayImage(image_out, QFileInfo(filename).fileName()+"-đã xử lí âm bản");
}

//Buoi 2

void MainWindow::Histogram_GrayImage(const QImage &img, const int &his_height){
    int h[256];
    for (int i = 0; i<256;i++)
        h[i] = 0;
    QImage image_in(img);
    for (int x=0; x<img.width();x++)
        for(int y = 0; y<img.height(); y++){
            QRgb color = img.pixel(x,y);
            int gray = qGray(color);
            QRgb color_in = qRgb(gray,gray,gray);
            image_in.setPixel(x,y,color_in);
            h[gray]++;
        }
    int max = 0;
    for (int i = 0; i<256; i++){
        if(h[i]>max)
            max=h[i];
    }
    QImage img_his = QImage(256,his_height,QImage::Format_RGB888);
    img_his.fill(Qt::white);
    int lineHeight;
    for (int i=0;i<256;i++){
        lineHeight = his_height * h[i]/max;
    for(int j=his_height-1; j>=his_height -1 - lineHeight; j--)
        img_his.setPixel(i,j,qRgb(0,0,0));
    }
    QLabel* label_in = new QLabel();
    label_in->setPixmap(QPixmap::fromImage(image_in));
    label_in->show();

    QLabel* label_out = new QLabel();
    label_out->setPixmap(QPixmap::fromImage(img_his));
    label_out->show();
}

void MainWindow::on_bt_histogramxam_clicked()
{
    QImage img(ui->filename_ln->text());
    Histogram_GrayImage(img,200);
}

void MainWindow::Histogram_ColorImage(const QImage &img, const int &his_height){
    int hr[256];
    int hg[256];
    int hb[256];
    for (int i = 0; i<256;i++){
        hr[i] = 0;
        hg[i] = 0;
        hb[i] = 0;
    }
    QImage image_in(img);
    for (int x=0; x<img.width();x++)
        for (int y = 0; y<img.height();y++){
            QRgb color = img.pixel(x,y);
            int green = qGreen(color);
            int red = qRed(color);
            int blue = qBlue(color);
            hr[red]++;
            hg[green]++;
            hb[blue]++;
        }
    int maxr = 0,maxg = 0,maxb = 0;
    for (int i = 0; i<256; i++){
        if (hr[i]>maxr) maxr = hr[i];
        if (hg[i]>maxg) maxg = hg[i];
        if (hb[i]>maxb) maxb = hb[i];
    }
    QImage img_hisr = QImage(256,his_height,QImage::Format_RGB888);
    img_hisr.fill(Qt::white);
    QImage img_hisg = QImage(256,his_height,QImage::Format_RGB888);
    img_hisg.fill(Qt::white);
    QImage img_hisb = QImage(256,his_height,QImage::Format_RGB888);
    img_hisb.fill(Qt::white);

    int liner, lineg, lineb;
    for (int i = 0; i<256; i++){
        liner = his_height *hr[i]/maxr;
        lineg = his_height *hg[i]/maxg;
        lineb = his_height *hb[i]/maxb;

        for(int j=his_height-1; j>=his_height -1 - liner; j--)
            img_hisr.setPixel(i,j,qRgb(255,0,0));
        for(int j=his_height-1; j>=his_height -1 - lineg; j--)
            img_hisg.setPixel(i,j,qRgb(0,255,0));
        for(int j=his_height-1; j>=his_height -1 - lineb; j--)
            img_hisb.setPixel(i,j,qRgb(0,0,255));
    }
    QLabel* label_in = new QLabel();
    label_in->setPixmap(QPixmap::fromImage(image_in));
    label_in->show();

    QLabel* label_out1 = new QLabel();
    label_out1->setPixmap(QPixmap::fromImage(img_hisr));
    label_out1->show();

    QLabel* label_out2 = new QLabel();
    label_out2->setPixmap(QPixmap::fromImage(img_hisg));
    label_out2->show();

    QLabel* label_out3 = new QLabel();
    label_out3->setPixmap(QPixmap::fromImage(img_hisb));
    label_out3->show();
}

void MainWindow::on_bt_histogrammau_clicked()
{
    QImage img(ui->filename_ln->text());
    Histogram_ColorImage(img,200);
}

//Buoi 3

void MainWindow::on_bt_loctrungbinh_clicked()
{
    QImage image_in(ui->filename_ln->text());
    int size = ui->ln_matna->text().toInt();
    int margin = (size -1)/2;
    int cells = size * size;

    QImage image_out(image_in.width()-margin, image_in.height()-margin,QImage::Format_ARGB32);
    int sumR, sumG, sumB;
    QColor color;
    for (int x = margin; x<image_in.width();x++)
        for (int y = margin; y<image_in.height(); y++){
            sumR = sumG = sumB = 0;
            for (int i=-margin;i<=margin;i++)
                for(int j=-margin; j<=margin;j++){
                    color = image_in.pixel(x+i,y+j);
                    sumR += color.red();
                    sumG += color.green();
                    sumB += color.blue();
                }
            image_out.setPixel(x,y,qRgb(sumR/cells,sumG/cells,sumB/cells));
        }
    QLabel* label_in = new QLabel();
    label_in->setPixmap(QPixmap::fromImage(image_in.scaled(1024,768)));
    label_in->setToolTip("Hinh Goc");
    label_in->show();

    QLabel* label = new QLabel();
    label->setPixmap(QPixmap::fromImage(image_out.scaled(1024,768)));
    label->setToolTip("Hinh da xu ly");
    label->show();

//    QString fname = QFileDialog::getSaveFileName();
//    image_out.save(fname);
}



void MainWindow::on_bt_loctrungvi_clicked()
{
    QImage image_in(ui->filename_ln->text());

    int size = ui->ln_matna->text().toInt();
    int margin = (size -1)/2;
    int cells = size* size;

    QImage image_out(image_in.width()-margin,image_in.height()-margin,QImage::Format_RGB32);
    for (int x= margin; x<image_in.width()-margin;x++)
        for(int y = margin; y<image_in.height()-margin;y++){
            int h[cells];
            int k = 0;
            for (int i = -margin; i<= margin; i++)
                for (int j =-margin; j<= margin; j++){
                    QRgb color = image_in.pixel(x+i,y+j);
                    int gray = qGray(color);
                    h[k] = gray;
                    k++;
                }
            qSort(h,h+cells);
            int meanV = h[(cells-1)/2];
            image_out.setPixel(x,y,qRgb(meanV,meanV,meanV));
        }
    QLabel* label_in = new QLabel();
    label_in->setPixmap(QPixmap::fromImage(image_in.scaled(1024,768)));
    label_in->setToolTip("Hinh Goc");
    label_in->show();

    QLabel* label = new QLabel();
    label->setPixmap(QPixmap::fromImage(image_out.scaled(1024,768)));
    label->setToolTip("Hinh da xu ly");
    label->show();

//    QString fname = QFileDialog::getSaveFileName();
//    image_out.save(fname);
}
int MainWindow::Random(int n){
    return rand()%n;
}
QImage MainWindow::imNoise_Gray(QImage &image_in, float lavel){
    QImage image_out = image_in;
    int noisePoint = image_in.width() * image_in.height() * lavel;

    for (int i = 0; i < noisePoint;i++){
        int x = Random(image_in.width());
        int y = Random(image_in.height());
        int a = Random(2);
        if(a==0)
            image_out.setPixel(x,y,qRgb(0,0,0));
        else
            image_out.setPixel(x,y,qRgb(255,255,255));
    }
    return image_out;
}


void MainWindow::on_bt_themnhieu_clicked()
{
    QImage image_in(ui->filename_ln->text());
    QImage image_inGray(image_in.width(),image_in.height(),QImage::Format_ARGB32);

    for(int i = 0; i < image_in.width(); i++)
        for (int j =0; j< image_in.height(); j++){
            QRgb rgb = image_in.pixel(i,j);
            int gray = qGray(rgb);
            QRgb color_in = qRgb(gray,gray,gray);
            image_inGray.setPixel(i,j,color_in);
        }
    float percentage = (ui->ln_tylenhieu->text().toInt())/100;
    QImage image_out = imNoise_Gray(image_inGray,percentage);

    QLabel* label_in = new QLabel();
    label_in->setPixmap(QPixmap::fromImage(image_in.scaled(1024,768)));
    label_in->setToolTip("Hinh Goc");
    label_in->show();

    QLabel* label = new QLabel();
    label->setPixmap(QPixmap::fromImage(image_out.scaled(1024,768)));
    label->setToolTip("Hinh da xu ly");
    label->show();
    //    QString fname = QFileDialog::getSaveFileName();
    //    image_out.save(fname);
}

// Buoi 4

//Loc Gradient Anh Xam

void MainWindow::on_bt_Gradient_clicked()
{
    QImage image_in(ui->filename_ln->text());
    QImage image_out_Gx(image_in.width()-1,image_in.height(),QImage::Format_ARGB32);
    QImage image_out_Gy(image_in.width(),image_in.height()-1,QImage::Format_ARGB32);

    for (int i = 0; i< image_in.width()-1;i++)
        for (int j = 0; j< image_in.height(); j++){
            QRgb color1 = image_in.pixel(i,j);
            int gray1 = qGray(color1);

            QRgb color_in = qRgb(gray1,gray1,gray1);
            image_in.setPixel(i,j,color_in);

            QRgb color2 = image_in.pixel(i+1,j);
            int gray2 = qGray(color2);
            int newgray = abs (gray2 - gray1);
            image_out_Gx.setPixel(i,j,qRgb(newgray,newgray,newgray));
        }
    for(int i = 0; i< image_in.width(); i++)
        for(int j = 0; j <image_in.height()-1; j++){
            QRgb color1 = image_in.pixel(i,j);
            int gray1 = qGray(color1);

            QRgb color_in = qRgb(gray1,gray1,gray1);
            image_in.setPixel(i,j,color_in);

            QRgb color2 = image_in.pixel(i,j+1);
            int gray2 = qGray(color2);
            int newgray = abs (gray2 - gray1);
            image_out_Gy.setPixel(i,j,qRgb(newgray,newgray,newgray));
        }

    QLabel* label_in = new QLabel();
    label_in->setPixmap(QPixmap::fromImage(image_in.scaled(1024,768)));
    label_in->show();

    QLabel* label_Gx = new QLabel();
    label_Gx->setPixmap(QPixmap::fromImage(image_out_Gx.scaled(1024,768)));
    label_Gx->show();

    QLabel* label_Gy = new QLabel();
    label_Gy->setPixmap(QPixmap::fromImage(image_out_Gy.scaled(1024,768)));
    label_Gy->show();

}

// Loc Gradient Anh mau

void MainWindow::on_bt_Gradientmau_clicked()
{
    QString filename = ui->filename_ln->text();
        QImage image_in(filename);
        QImage image_out_Gx(image_in.width()-1, image_in.height(), QImage::Format_ARGB32);
        QImage image_out_Gy(image_in.width(), image_in.height()-1, QImage::Format_ARGB32);


        for(int i=0; i<image_in.width()-1; i++)
        {
            for(int j=0; j<image_in.height();j++)
            {
                QRgb rgb = image_in.pixel(i, j);
                QColor color1(rgb);
                int red, green, blue;
                color1.getRgb(&red, &green, &blue);


                QRgb color_in = qRgb(red, green, blue);
                image_in.setPixel(i, j, color_in);


                QRgb color2 = image_in.pixel(i+1,j);
                int red2 = qRed(color2);
                int newRed = abs(red2-red);
                int green2 = qGreen(color2);
                int newGreen = abs(green2-green);
                int blue2 = qBlue((color2));
                int newBlue = abs(blue2-blue);


                image_out_Gx.setPixel(i, j, qRgb(newRed, newGreen, newBlue));
            }
        }
        for(int i=0; i<image_in.width(); i++)
        {
            for(int j=0; j<image_in.height()-1;j++)
            {
                QRgb rgb = image_in.pixel(i, j);
                QColor color1(rgb);
                int red, green, blue;
                color1.getRgb(&red, &green, &blue);


                QRgb color_in = qRgb(red, green, blue);
                image_in.setPixel(i, j, color_in);


                QRgb color2 = image_in.pixel(i,j+1);
                int red2 = qRed(color2);
                int newRed = abs(red2-red);
                int green2 = qGreen(color2);
                int newGreen = abs(green2-green);
                int blue2 = qBlue((color2));
                int newBlue = abs(blue2-blue);


                image_out_Gy.setPixel(i, j, qRgb(newRed, newGreen, newBlue));
            }
        }

        QLabel* label_in = new QLabel();
        label_in->setPixmap(QPixmap::fromImage(image_in));
        label_in->setWindowTitle(filename + "--Anh goc");
        label_in->show();

        QLabel* label_Gx = new QLabel();
        label_Gx->setPixmap(QPixmap::fromImage(image_out_Gx));
        label_Gx->setWindowTitle(filename + "--Gx");
        label_Gx->show();


        QLabel* label_Gy = new QLabel();
        label_Gy->setPixmap(QPixmap::fromImage(image_out_Gy));
        label_Gy->setWindowTitle(filename + "--Gy");
        label_Gy->show();
}


// Robert Anh Xam

void MainWindow::on_bt_Robert_clicked()
{
    QImage image_in(ui->filename_ln->text());
    QImage image_out_Gx(image_in.width()-1,image_in.height(),QImage::Format_ARGB32);
    QImage image_out_Gy(image_in.width(),image_in.height()-1,QImage::Format_ARGB32);

    for (int i = 0; i< image_in.width()-1;i++)
        for (int j = 0; j< image_in.height(); j++){

            QRgb color1 = image_in.pixel(i,j);
            int gray1 = qGray(color1);

            QRgb color2 = image_in.pixel(i+1,j);
            int gray2 = qGray(color2);

            QRgb color3 = image_in.pixel(i,j+1);
            int gray3 = qGray(color3);

            QRgb color4 = image_in.pixel(i+1,j+1);
            int gray4 = qGray(color4);

            int newgray_Gx = abs (gray1 - gray4);

            int newgray_Gy = abs (gray2 - gray3);

            image_out_Gx.setPixel(i,j,qRgb(newgray_Gx,newgray_Gx,newgray_Gx));

            image_out_Gy.setPixel(i,j,qRgb(newgray_Gy,newgray_Gy,newgray_Gy));
        }
    QLabel* label_in = new QLabel();
    label_in->setPixmap(QPixmap::fromImage(image_in.scaled(1024,768)));
    label_in->show();

    QLabel* label_Gx = new QLabel();
    label_Gx->setPixmap(QPixmap::fromImage(image_out_Gx.scaled(1024,768)));
    label_Gx->show();

    QLabel* label_Gy = new QLabel();
    label_Gy->setPixmap(QPixmap::fromImage(image_out_Gy.scaled(1024,768)));
    label_Gy->show();
}



void MainWindow::on_bt_Sobel_clicked()
{
    QImage image_in(ui->filename_ln->text());
    QImage image_out(image_in.width()-1,image_in.height(),QImage::Format_ARGB32);
    QImage image_out2(image_in.width(),image_in.height()-1,QImage::Format_ARGB32);

    int maskSize = 3;
    int margin = maskSize / 2;
    //int ce;;s = maskSize * maskSize;
    int mask[maskSize][maskSize];
    mask [0][0] = -1; mask [0][1] = 0; mask[0][2] = 1;
    mask [1][0] = -2; mask [1][1] = 0; mask[1][2] = 2;
    mask [2][0] = -1; mask [2][1] = 0; mask[2][2] = 1;

    int mask2[maskSize][maskSize];
    mask2[0][0] = -1; mask2[0][1] = -2; mask2[0][2] = -1;
    mask2[1][0] =  0; mask2[1][1] = 0; mask2[1][2] = 0;
    mask2[2][0] = 1; mask2[2][1] = 2; mask2[2][2] = 1;

    QRgb color;
    int sum1, sum2;
    for (int y = margin; y < image_in.height()-margin; y++)
        for (int x = margin; x < image_in.width() - margin; x++){
            sum1 = sum2 = 0;
            for (int j = -margin; j<= margin; j++)
                for (int i = -margin; i<= margin;i++){
                    color = image_in.pixel(x+i,y+j);
                    int gray = qGray(color);
                    sum1 += gray * mask[j+margin][i+margin];
                    sum2 += gray * mask2[j+margin][i+margin];
                }
            image_out.setPixel(x,y,qRgb(abs(sum1),abs(sum1),abs(sum1)));
            image_out2.setPixel(x,y,qRgb(abs(sum2),abs(sum2),abs(sum2)));
        }
    QLabel* label_in = new QLabel();
    label_in->setPixmap(QPixmap::fromImage(image_in.scaled(1024,768)));
    label_in->show();

    QLabel* label_Gx = new QLabel();
    label_Gx->setPixmap(QPixmap::fromImage(image_out.scaled(1024,768)));
    label_Gx->show();

    QLabel* label_Gy = new QLabel();
    label_Gy->setPixmap(QPixmap::fromImage(image_out2.scaled(1024,768)));
    label_Gy->show();
}


//Buoi5

//Tuan tu
void MainWindow::on_bt_tuantu_clicked()
{
    QImage image_in(ui->filename_ln->text());
    QImage image_out(image_in.width(),image_in.height(),QImage::Format_ARGB32);
    int c =127;
    int newc = c;
    do{
        int G1 = 0;
        int count1 = 0;
        int G2 = 0;
        int count2 = 0;
        c = newc;
        for (int i = 0; i < image_in.width();i++){
            for (int j = 0; j < image_in.height();j++){
                QRgb rgb = image_in.pixel(i,j);
                int gray = qGray(rgb);
                QRgb color_in = qRgb (gray,gray,gray);
                image_in.setPixel(i,j,color_in);
                if(gray > c){
                    G1 = G1 + gray;
                    count1++;
                }
                else if (gray <= c){
                    G2 = G2 + gray;
                    count2++;
                }
            }
        }
        int M1 = G1/count1;
        int M2 = G2/count2;
        newc = (M1+M2)/2;
    }while (abs(newc - c)!=0);

    for(int x=0; x<image_in.width(); x++)
        for(int y=0; y<image_in.height(); y++)
        {
            QRgb color = image_in.pixel(x, y);
            int gray_in = qGray(color), gray_out; //đổi giá trị màu thành xám
            if(gray_in >= c)
                gray_out=255;
            else
                gray_out=0;
            QRgb color_out = qRgb(gray_out, gray_out, gray_out); //giá trị điểm ảnh x, y: Ảnh xám
            image_out.setPixel(x, y, color_out);
        }
    QLabel* label_in = new QLabel();
    label_in->setPixmap(QPixmap::fromImage(image_in.scaled(1024,768)));
    label_in->show();

    QLabel* label_out = new QLabel();
    label_out->setPixmap(QPixmap::fromImage(image_out.scaled(1024,768)));
    label_out->show();
}



// An mon
void MainWindow::on_bt_anmon_clicked()
{
    int kernel [3][3] = {{0,1,0},{1,1,1},{0,1,0}};
    int margin = 1;
    int c_gray;
    QImage image_in(ui->filename_ln->text());
    QImage image_out(image_in.width(),image_in.height(),QImage::Format_ARGB32);
    image_out.fill(Qt::white);

    for (int x = margin; x<= image_in.width()-margin; x++)
        for (int y =margin; y<= image_in.height()-margin;y++){
            int ok = 1;
            for (int i = -margin; i<= margin; i++)
                for(int j = -margin; j<= margin; j++){
                    c_gray = qGray(image_out.pixel(x+i,y+j));
                    ok = ok && (kernel[i][j] == 0 || c_gray == 0);
                }
             if(ok) image_out.setPixel(x,y,qRgb(0,0,0));
        }

    for(int x=0; x<image_in.width(); x++)
        for(int y=0; y<image_in.height(); y++)
        {
            QRgb color = image_in.pixel(x, y);
            int gray_in = qGray(color), gray_out; //đổi giá trị màu thành xám
            if(gray_in >= c_gray)
                gray_out=255;
            else
                gray_out=0;
            QRgb color_out = qRgb(gray_out, gray_out, gray_out); //giá trị điểm ảnh x, y: Ảnh xám
            image_out.setPixel(x, y, color_out);
        }
    QLabel* label_in = new QLabel();
    label_in->setPixmap(QPixmap::fromImage(image_in.scaled(1024,768)));
    label_in->show();

    QLabel* label_out = new QLabel();
    label_out->setPixmap(QPixmap::fromImage(image_out.scaled(1024,768)));
    label_out->show();
}


//Gian no


void MainWindow::on_bt_gianno_clicked()
{
    int kernel [3][3] = {{0,1,0},{1,1,1},{0,1,0}};
    int margin = 1;
    int c_gray;
    QImage image_in(ui->filename_ln->text());
    QImage image_out(image_in.width(),image_in.height(),QImage::Format_ARGB32);
    image_out.fill(Qt::white);
    for (int x = margin; x<= image_in.width()-margin; x++)
        for (int y =margin; y<= image_in.height()-margin;y++){

            c_gray = qGray(image_out.pixel(x,y));
            if (c_gray == 0){
                for(int i = -margin; i<= margin; i++){
                    for (int j = -margin; j<= margin;j++){
                        if(kernel[i+margin][j+margin])
                            image_out.setPixel(x+i,y+j,qRgb(0,0,0));
                    }
                }
            }
        }
    for(int x=0; x<image_in.width(); x++)
        for(int y=0; y<image_in.height(); y++)
        {
            QRgb color = image_in.pixel(x, y);
            int gray_in = qGray(color), gray_out; //đổi giá trị màu thành xám
            if(gray_in >= c_gray)
                gray_out=255;
            else
                gray_out=0;
            QRgb color_out = qRgb(gray_out, gray_out, gray_out); //giá trị điểm ảnh x, y: Ảnh xám
            image_out.setPixel(x, y, color_out);
        }
    QLabel* label_in = new QLabel();
    label_in->setPixmap(QPixmap::fromImage(image_in.scaled(1024,768)));
    label_in->show();

    QLabel* label_out = new QLabel();
    label_out->setPixmap(QPixmap::fromImage(image_out.scaled(1024,768)));
    label_out->show();
}


void MainWindow::on_bt_hello_clicked()
{
    QMessageBox::information(this,"infomation","xin chao");
}

