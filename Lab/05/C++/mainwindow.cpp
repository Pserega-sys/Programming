#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QColor>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::loadImage);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::saveImage);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::encodeMsg);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::decodeText);
    connect(ui->plainTextEdit, &QPlainTextEdit::textChanged, this, &MainWindow::msgChanged);

}

void setBit(QImage &image, int index, bool val)
{
    int pixelIndex = index / 3;

    int x = pixelIndex % image.width();
    int y = pixelIndex / image.width();

    switch (index % 3) {
        case 0:
            image.setPixel(x, y, (image.pixel(x, y) & ~0x010000) | (val << 16));
        case 1:
            image.setPixel(x, y, (image.pixel(x, y) & ~0x000100) | (val << 8));
        default:
            image.setPixel(x, y, (image.pixel(x, y) & ~0x000001) | val);
    }
}

bool getBit(const QImage &image, int index)
{
    int pixelIndex = index / 3;

    int x = pixelIndex % image.width();
    int y = pixelIndex / image.width();

    switch (index % 3) {
    case 0:
        return (image.pixel(x, y) >> 16) & 1;
    case 1:
        return (image.pixel(x, y) >> 8) & 1;
    default:
        return image.pixel(x, y) & 1;
    }
}

QByteArray readBytes(const QImage& img, size_t begin, size_t length)
{
    QByteArray byteArray;
    char buf = 0;

    size_t end = (begin + length) * 8;
    for (size_t i = begin * 8; i < end; ++i) {
        buf = (buf << 1) | getBit(img, i);

        if (i % 8 == 7) {
            byteArray.push_back(buf);
            buf = 0;
        }
    }

    return byteArray;
}

void writeBytes(QImage& image, size_t begin, QByteArray& byteArray)
{
    size_t end = (begin + byteArray.size()) * 8;
    for (size_t i = begin * 8; i < end; ++i) {
            setBit(image, i, (byteArray[i / 8] >> (7 - i % 8)) & 1);
        }
    }
void MainWindow::loadImage()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            ("Open Image"), "", ("Допустимые форматы (*.png)"));
    image.convertTo(QImage::Format_ARGB32);
    if (!image.load(fileName, "PNG")){
        ui->label->setText("Изображение не загружено");
    }
    else {
        ui->label->setText("Изображение успешно загружено");
    }
}

void MainWindow::saveImage()
{
    QString fileName = QFileDialog::getSaveFileName(this,
            ("Save Image"), "", ("Допустимые форматы (*.png)"));
    if (image.save(fileName, "PNG")) {
       ui->label->setText("Изображение успешно сохранено");
    }
    else {
       ui->label->setText("Изображение не сохранено");
    }
}

void MainWindow::encodeMsg()
{
    usedBytes = ui->plainTextEdit->toPlainText().toUtf8().size();
    imageCapacity = (image.width() * image.height() * 3) / 8 - marker.size() - messageInfoLength;
    if (imageCapacity < usedBytes) {
        ui->label->setText("Ошибка. Не достаточно места!");
        return;
        }

QByteArray byteArray;
    byteArray.push_back(marker);
    for (int i = messageInfoLength - 1; i >= 0; --i) {
        byteArray.push_back((usedBytes >> i*8) & 0xff);
    }
    byteArray.push_back(ui->plainTextEdit->toPlainText().toUtf8());

    writeBytes(image, 0, byteArray);

 //  QColor getColor = QImage::pixelColor(int x, int y) const ;
 //   QColor QImage::setPixelColor(int x, int y, const QColor &color);
    ui->label->setText("Сообщение добавлено в картинку!");

}

void MainWindow::decodeText()
{
    int headerSize = marker.size() + messageInfoLength;
        QByteArray byteArray;

        byteArray = readBytes(image, 0, headerSize);

        for (size_t i = 0; i < marker.size(); ++i) {
            if (marker[i] != byteArray[i]) {
                ui->label->setText("Сообщение не обнаружено");
                return;
            }
        }
        size_t messageSize = 0;
            for (size_t i = marker.size(); i < marker.size() + messageInfoLength; ++i) {
                messageSize = (messageSize << 8) + static_cast<unsigned char>(byteArray[i]);
            }

            byteArray = readBytes(image, headerSize, messageSize);

            QString text = QString::fromUtf8(byteArray);

            ui->plainTextEdit->setPlainText(text);

            ui->label->setText(QString("Присутствует сообщение длиной %1 байт").arg(messageSize));

}

void MainWindow::msgChanged()
{
    usedBytes = ui->plainTextEdit->toPlainText().toUtf8().size();

        if (imageCapacity < usedBytes) {
             ui->label->setText(QString("Размер сообщения повышен на: %1 байт").arg(usedBytes - imageCapacity));
        } else {
             ui->label->setText(QString("Ещё можно ввести: %1 байт").arg(imageCapacity - usedBytes));
        }
    }

MainWindow::~MainWindow()
{
    delete ui;
}

