'''
对话框：QDialog
QMessageBox  显示消息对话框
QColorDialog  显示颜色对话框
QFileDialog  显示文件保存或打开对话框
QFontDialog  显示字体的对话框
QInputDialog  用于获取用户输入信息的对话框
2020年7月27号
'''
import sys
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *

class QDialogDemo(QMainWindow):
    def __init__(self):
        super(QDialogDemo,self).__init__()
        self.initUI()

    def initUI(self):
        self.setWindowTitle('QDialog案列')
        self.resize(300,200)

        self.button = QPushButton(self)
        self.button.setText('弹出对话框')
        self.button.move(50,50)
        self.button.clicked.connect(self.showDialog)
    def showDialog(self):
        dialog = QDialog()
        button = QPushButton('确定',dialog)
        button.clicked.connect(dialog.close)
        button.move(50,50)
        dialog.setWindowTitle('对话框')
        dialog.setWindowModality(Qt.ApplicationModal)

        dialog.exec()
if __name__ == '__main__':
    app = QApplication(sys.argv)
    main = QDialogDemo()
    main.show()
    sys.exit(app.exec_())


















