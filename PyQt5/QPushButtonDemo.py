'''
按钮控件（QPushButton）

QAbstractButton
QPushButton
ATollButton
QRadioButton  单选按钮
QCheckBox 复选框，多选


'''
import sys
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
class QPushButtonDemo(QDialog):
    def __init__(self):
        super(QPushButtonDemo,self).__init__()
        self.initUI()

    def initUI(self):
        self.setWindowTitle('QPushButton Demo')

        layout = QVBoxLayout()
        self.button1 = QPushButton('第一个按钮')
        self.button1.setText('First Button1')
        self.button1.setCheckable(True) #设置成可复选的
        self.button1.toggle()
        self.button1.clicked.connect(lambda:self.whichButton(self.button1))#用lambda表达式直接调用
        self.button1.clicked.connect(self.buttonState)
        layout.addWidget(self.button1)


        #在文本前面显示图像

        self.button2 = QPushButton('图像按钮')
        self.button2.setIcon(QIcon(QPixmap('./images/001.png')))
        self.button2.clicked.connect(lambda: self.whichButton(self.button2))  # 用lambda表达式直接调用
        layout.addWidget(self.button2)


        self.button3 = QPushButton('不可用的按钮')
        self.button3.setEnabled(False)
        layout.addWidget(self.button3)


        self.button4 = QPushButton('&MyButton')
        self.button4.setDefault(True)
        self.button4.clicked.connect(lambda: self.whichButton(self.button4))  # 用lambda表达式直接调用
        layout.addWidget(self.button4)


        self.setLayout(layout)
    def whichButton(self,btn):
        print('被单击的按钮是<'+btn.text()+'>')


    def buttonState(self):
        if self.button1.isChecked():
            print('按钮1 已经被选中')
        else:
            print('按钮1未被选中')


if __name__ == '__main__':
            app = QApplication(sys.argv)

            main = QPushButtonDemo()
            main.show()
            sys.exit(app.exec_())








