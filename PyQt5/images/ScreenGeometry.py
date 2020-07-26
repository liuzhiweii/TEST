import sys
from PyQt5.QtWidgets import QHBoxLayout, QMainWindow, QApplication, QWidget, QPushButton
def onClick_Button():
    print("1")
    print("widget.x() = %d" % widget.x())
    print("widget.y() = %d" % widget.y())
    print("widget.width() = %d" % widget.width())
    print("widget.height() = %d" % widget.height())


app = QApplication(sys.argv)

widget = QWidget()
btn = QPushButton(widget)
btn.setText("按钮")
btn.clicked.connect(onClick_Button)

btn.move(24,52)
widget.resize(300,240) #设置窗口尺寸
widget.move(250,200)#移动窗口
widget.setWindowTitle("屏幕坐标系")
widget.show()
sys.exit(app.exec_()) #是程序正常退出






