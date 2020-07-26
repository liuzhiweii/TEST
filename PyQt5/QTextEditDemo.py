'''
QTextEdit控件
2020/6/13

'''

from PyQt5.QtWidgets import  *
import sys

class QTexteDITDemo(QWidget):
    def __init__(self):
        super(QTexteDITDemo,self).__init__()
        self.initUI()

    def initUI(self):
        self.setWindowTitle('QTextEdit控件演示')
        self.resize(800,800)

        self.textEdit =QTextEdit()
        self.buttonText = QPushButton('显示文本')
        self.buttonHTML = QPushButton('显示HTML')
        self.buttontoText = QPushButton('获取文本')
        self.buttontoHTML = QPushButton('获取HTML')

        layout = QVBoxLayout()
        layout.addWidget(self.textEdit)
        layout.addWidget(self.buttonText)
        layout.addWidget(self.buttonHTML)
        layout.addWidget(self.buttontoText)
        layout.addWidget(self.buttontoHTML)

        self.setLayout(layout)

        self.buttonText.clicked.connect(self.onClick_ButtonText)
        self.buttonHTML.clicked.connect(self.onClick_ButtonHTML)

        self.buttontoText.clicked.connect(self.onClick_ButtontoText)
        self.buttontoHTML.clicked.connect(self.onClick_ButtontoHTML)
    def onClick_ButtonText(self):
        self.textEdit.setPlainText('Hello Word,世界你好吗')#设置纯文本的显示

    def onClick_ButtontoText(self):
        print(self.textEdit.toPlainText())


    def onClick_ButtonHTML(self):
        self.textEdit.setHtml('<font color="blue" size = "5"> Hello World</font>')
    def onClick_ButtontoHTML(self):
        print(self.textEdit.toHtml())

if __name__ == '__main__':
    app = QApplication(sys.argv)

    main = QTexteDITDemo()
    main.show()
    sys.exit(app.exec_())



