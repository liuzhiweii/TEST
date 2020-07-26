import sys
from PyQt5.QtWidgets import QMainWindow, QApplication
from PyQt5.QtGui import QIcon

class IconForm(QMainWindow):
    def __init__(self):
        super(IconForm,self).__init__()
        #设置主窗口的标题
        self.setWindowTitle('设置窗口图标')
        #设置窗口的尺寸
        self.resize(400,300)


if __name__ == '__main__':
    app = QApplication(sys.argv)
    app.setWindowIcon(QIcon('./images/001.png'))  #设置应用程序的图标
    main = FirstMainWin()
    main.show()
    sys.exit(app.exec_())
