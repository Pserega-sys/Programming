#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

public slots:

    void loadImage();
    void saveImage();
    void encodeMsg();
    void decodeText();
    void msgChanged();
public:

    ~MainWindow();
    QImage image;
private:
    Ui::MainWindow *ui;
    size_t imageCapacity;
    size_t usedBytes;

    const std::array<char, 3> marker {
        static_cast<char>(0b11100010),
        static_cast<char>(0b10011101),
        static_cast<char>(0b10100100)
        };
    const size_t messageInfoLength = 4;
};
#endif // MAINWINDOW_H
