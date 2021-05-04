# -*- coding: utf-8 -*-

import sys

import os

  
from PySide6.QtWidgets import QApplication, QMainWindow

from PySide6.QtCore import QFile

from PySide6.QtUiTools import QUiLoader



if __name__ == "__main__":

    app = QApplication(sys.argv)

    

    path = os.path.join(os.path.dirname(__file__), "form.ui")

    ui_file = QFile(path)

    ui_file.open(QFile.ReadOnly)

    

    loader = QUiLoader()

    window = loader.load(ui_file)

    ui_file.close()

    

    window.show()

    sys.exit(app.exec_())



class MainWindow(QMainWindow):

    def __init__(self):
        
        super(MainWindow, self).__init__()

        pushButton.clicked.connect(self.loadImage)

__slots__ = 'loadImage',

def loadImage(self):

        fileName, _ = QFileDialog.getOpenFileName(self, self("Open Image"),
        "", self("Доступные форматы (*.png)"))
        
        self.image.convertTo(QImage.Format_ARGB32)
        
        label.setText("fds 23")
     

    










        
