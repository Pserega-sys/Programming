# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'mainwindowPtEQKH.ui'
##
## Created by: Qt User Interface Compiler version 6.0.1
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import *
from PySide6.QtGui import *
from PySide6.QtWidgets import *

def to_pixel(value) -> int:
    return value * 8

def set_pixel(image: QImage, index, value) -> None:
    pixel = index // 3

    x = pixel % image.width()
    y = pixel // image.width()

    px = index % 3

    if px == 0:
        image.setPixel(x, y, (image.pixel(x, y) & ~0x010000) | (value << 16))
    elif px == 1:
        image.setPixel(x, y, (image.pixel(x, y) & ~0x000100) | (value << 8))
    elif px == 2:
        image.setPixel(x, y, (image.pixel(x, y) & ~0x000001) | value)

def get_pixel(image: QImage, index) -> bool:
    pixel = index // 3

    x = pixel % image.width()
    y = pixel // image.width()

    px = index % 3

    if px == 0:
        return (image.pixel(x, y) >> 16) & 1
    elif px == 1:
        return (image.pixel(x, y) >> 8) & 1
    elif px == 2:
        return image.pixel(x, y) & 1
    else:
        raise Exception()

def read_pixel(image: QImage, start, length) -> QByteArray:
    array = QByteArray()
    buffer = 0

    for i in range(to_pixel(start), to_pixel(start + length)):
        buffer = (buffer << 1) | get_pixel(image, i)

        if i % 8 == 7:
            array.push_back(bytes((buffer,)))
            buffer = 0

    return array

def write_pixel(image: QImage, array: QByteArray, start) -> None:
    for i in range(to_pixel(start), to_pixel(start + array.size())):
        set_pixel(image, i, (int.from_bytes(array[i // 8], "big") >> (7 - i % 8)) & 1)


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        if not MainWindow.objectName():
            MainWindow.setObjectName(u"MainWindow")
        MainWindow.resize(544, 296)
        MainWindow.setWindowTitle(u"\u0421\u0442\u0435\u043d\u043e\u0433\u0440\u0430\u0444")
        MainWindow.setStyleSheet(u"QPushButton:hover{color: blue; font: bold 10pt;}")
        self.centralwidget = QWidget(MainWindow)
        self.centralwidget.setObjectName(u"centralwidget")
        self.gridLayout = QGridLayout(self.centralwidget)
        self.gridLayout.setObjectName(u"gridLayout")
        self.pushButton = QPushButton(self.centralwidget)
        self.pushButton.setObjectName(u"pushButton")

        self.gridLayout.addWidget(self.pushButton, 0, 0, 1, 1)

        self.pushButton_2 = QPushButton(self.centralwidget)
        self.pushButton_2.setObjectName(u"pushButton_2")

        self.gridLayout.addWidget(self.pushButton_2, 1, 0, 1, 1)

        self.label = QLabel(self.centralwidget)
        self.label.setObjectName(u"label")

        self.gridLayout.addWidget(self.label, 2, 0, 1, 1)

        self.plainTextEdit = QPlainTextEdit(self.centralwidget)
        self.plainTextEdit.setObjectName(u"plainTextEdit")

        self.gridLayout.addWidget(self.plainTextEdit, 3, 0, 1, 1)

        self.pushButton_3 = QPushButton(self.centralwidget)
        self.pushButton_3.setObjectName(u"pushButton_3")

        self.gridLayout.addWidget(self.pushButton_3, 4, 0, 1, 1)

        self.pushButton_4 = QPushButton(self.centralwidget)
        self.pushButton_4.setObjectName(u"pushButton_4")

        self.gridLayout.addWidget(self.pushButton_4, 5, 0, 1, 1)

        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)

        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"MainWindow", None))
        self.pushButton.setText(QCoreApplication.translate("MainWindow", u"\u0417\u0430\u0433\u0440\u0443\u0437\u0438\u0442\u044c \u043a\u0430\u0440\u0442\u0438\u043d\u043a\u0443", None))
        self.pushButton_2.setText(QCoreApplication.translate("MainWindow", u"\u0421\u043e\u0445\u0440\u0430\u043d\u0438\u0442\u044c \u043a\u0430\u0440\u0442\u0438\u043d\u043a\u0443", None))
        self.label.setText(QCoreApplication.translate("MainWindow", u"<span style=\"font-size:10pt; color:#ff0000;\"><b>\u041f\u0440\u0438\u0432\u0435\u0442:</b></span>", None))
        self.plainTextEdit.setPlaceholderText(QCoreApplication.translate("MainWindow", u"\u0412\u0432\u0435\u0434\u0438\u0442\u0435 \u0442\u0435\u043a\u0441\u0442:", None))
        self.pushButton_3.setText(QCoreApplication.translate("MainWindow", u"\u0417\u0430\u043a\u043e\u0434\u0438\u0440\u043e\u0432\u0430\u0442\u044c \u0442\u0435\u043a\u0441\u0442", None))
        self.pushButton_4.setText(QCoreApplication.translate("MainWindow", u"\u0414\u0435\u043a\u043e\u0434\u0438\u0440\u043e\u0432\u0430\u0442\u044c \u0442\u0435\u043a\u0441\u0442", None))
    # retranslateUi


class MainWindow(QMainWindow):
    marker = bytes((0b11100010, 0b10011101, 0b10100100))
    Length = 4

    def __init__(self):
        super(MainWindow, self).__init__(None)

        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

        self.image = None
        self.data = sizeData()

        self.ui.plainTextEdit.textChanged.connect(self.msgChanged)
        self.ui.pushButton.clicked.connect(self.loadImage)
        self.ui.pushButton_2.clicked.connect(self.saveImage)

        self.ui.pushButton_3.clicked.connect(self.encodeMsg)
        self.ui.pushButton_4.clicked.connect(self.decodeMsg)

    def get_input(self):
        return self.ui.plainTextEdit.toPlainText()

    @Slot()
    def loadImage(self):
        fileName, _ = QFileDialog.getOpenFileName(self, "Open Image", "", "Допустимые форматы (*.png)")

        if not QFile.exists(fileName):
            self.ui.label.setText(f"Изображение не найдено")
            return

        self.image = QImage()
        
        if not self.image.load(fileName):
            self.ui.label.setText(f"Изображение не загружено")
            self.clear_image()
            return

        self.image.convertTo(QImage.Format_ARGB32)

        self.data.capacity = (self.image.width() * self.image.height() * 3) // 8 - len(
            MainWindow.marker) - MainWindow.Length
        self.ui.label.setText("Изображение успешна загружено")
        
    @Slot()
    def saveImage(self):
        if self.image is None:
            self.ui.label.setText("Изображение не загружено")
            return

        fileName, _ = QFileDialog.getSaveFileName(self, "Сохранить картинку", "", "Допустимые форматы (*.png)")

        if self.image.save(fileName, "PNG"):
            self.ui.label.setText(f"Картинка успешна сохранена в {fileName}")
            return

        self.ui.label.setText("Изображение не сохранено")

    @Slot()
    def encodeMsg(self):
        if self.image is None:
            self.ui.label.setText("Изображение не загружено в программу")
            return

        array = QByteArray()
        array.push_back(self.get_input().encode())

        self.data.current = len(array)

        if self.data.overload():
            self.ui.label.setText("Недостаточно места для кодирования")
            return

        for i in range(MainWindow.Length):
            array.push_front(bytes(((self.data.current >> to_pixel(i)) & 0xff,)))

        for i in range(len(MainWindow.marker) - 1, -1, -1):
            array.push_front(bytes((MainWindow.marker[i],)))

        write_pixel(self.image, array, 0)

        self.ui.label.setText("Сообщение добавлено в изображение")

    @Slot()
    def decodeMsg(self):
        if self.image is None:
            self.ui.label.setText("Изображение не загружено в программу")
            return

        header = len(MainWindow.marker) + MainWindow.Length

        array = read_pixel(self.image, 0, header)

        for i in range(0, len(MainWindow.marker)):
            if bytes((MainWindow.marker[i],)) != array[i]:
                self.ui.label.setText("Сообщение отсутствует!")
                return

        size = 0

        for i in range(len(MainWindow.marker), len(MainWindow.marker) + MainWindow.Length):
            size = (size << 8) + int.from_bytes(array[i], "big")

        if size > self.data.capacity:
            self.ui.label.setText("Ошибка декодирования! Размер заголовка превышает размер сообщения.")
            return

        array.clear()
        array = read_pixel(self.image, header, size)

        text = bytes(array).decode("utf-8")

        self.ui.plainTextEdit.setPlainText(text)
        self.ui.label.setText(f"Присутствует сообщение длиной {size} байт.")

    @Slot()
    def msgChanged(self):
        array = QByteArray()
        array.push_back(self.get_input().encode())
        self.data.current = len(array)

        if self.data.less():
            mesto = self.data.diff()
            self.ui.label.setText(f"Ещё можно ввести: {mesto} байт.")
            return

        if self.data.max():
            self.ui.label.setText("Размер сообщения достиг максимума.")
            return

        mesto = self.data.rdiff()
        self.ui.label.setText(f"Размер сообщения превышен на: {mesto} байт.")

class sizeData:
    def __init__(self):
        self.current = 0
        self.capacity = 0

    def less(self):
        return self.current < self.capacity

    def max(self):
        return self.current == self.capacity

    def overload(self):
        return self.current > self.capacity

    def diff(self):
        return self.capacity - self.current

    def rdiff(self):
        return self.current - self.capacity

if __name__ == "__main__":
    import sys
    app = QApplication(sys.argv)

    window = MainWindow()
    window.show()

    sys.exit(app.exec_())
