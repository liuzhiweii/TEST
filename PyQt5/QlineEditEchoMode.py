'''
QLineEdit控件与回显模式

基本功能：输入单行的文本
EchoMode回显模式
1、Normal
2、NoEcho 不回显
3、Password
4、PasswordEchoOnEdit  (显示回显，然后是密码)


'''

from PyQt5.QtWidgets import *
import sys


class QLineEditEchoMode(QWidget):
    def __init__(self):
        super(QLineEditEchoMode,self).__init__()
        self.initUI()

    def initUI(self):
        self.setWindowTitle('文本输入框的回显模式')

        formLayout = QFormLayout()

        normalLineEidt = QLineEdit()
        noEchoLineEdit = QLineEdit()
        passwordLineEdit = QLineEdit()
        passwordEchoOnEditLineEdit = QLineEdit()

        formLayout.addRow("Normal",normalLineEidt)
        formLayout.addRow("NoEcho",noEchoLineEdit)
        formLayout.addRow("Password",passwordLineEdit)
        formLayout.addRow("PasswordEchoOnEdit",passwordEchoOnEditLineEdit)

        normalLineEidt.setPlaceholderText("Normal")
        noEchoLineEdit.setPlaceholderText("NoEcho")
        passwordLineEdit.setPlaceholderText("Password")
        passwordEchoOnEditLineEdit.setPlaceholderText("PasswordEchoOnEdit")
        #设置模式
        normalLineEidt.setEchoMode(QLineEdit.Normal)
        noEchoLineEdit.setEchoMode(QLineEdit.NoEcho)
        passwordLineEdit.setEchoMode(QLineEdit.Password)
        passwordEchoOnEditLineEdit.setEchoMode(QLineEdit.PasswordEchoOnEdit)

        self.setLayout(formLayout)
if __name__ == '__main__':
    app = QApplication(sys.argv)

    main = QLineEditEchoMode()
    main.show()
    sys.exit(app.exec_())




