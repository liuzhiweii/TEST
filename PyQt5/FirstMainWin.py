import sys
from PyQt5.QtWidgets import QMainWindow, QApplication
from PyQt5.QtGui import QIcon

class FirstMainWin(QMainWindow):
    def __init__(self):
        super(FirstMainWin,self).__init__()
        #设置主窗口的标题
        self.setWindowTitle('第一个主串口应用')
        #设置窗口的尺寸
        self.resize(400,300)
        self.status = self.statusBar() #通过这个方法获得状态栏
        self.status.showMessage('只存在5秒的消息',5000)

if __name__ == '__main__':
    app = QApplication(sys.argv)
    app.setWindowIcon(QIcon('./images/001.png'))  #设置应用程序的图标
    main = FirstMainWin()
    main.show()
    sys.exit(app.exec_())







