import sys
from PyQt5.QtWidgets import QHBoxLayout,QMainWindow, QApplication,QToolTip,QPushButton,QWidget
from PyQt5.QtGui import QFont

class TooltipForm(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
    def initUI(self):
        QToolTip.setFont(QFont('SansSerif',12))
        self.setToolTip('今天是<b>星期五</b>')
        self.setGeometry(300,300,200,300)
        self.setWindowTitle('设置控件提示消息')
if __name__ == '__main__':
    app = QApplication(sys.argv)

    main = TooltipForm()
    main.show()
    sys.exit(app.exec_())
