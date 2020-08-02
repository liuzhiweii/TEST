'''
绘制不同类型的直线
2020年8月2号
'''
'''
用像素点绘制正弦曲线
-2PI   2PI
drWPoint(x,y)
2020年8月1号

'''
import sys, math
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import Qt


class DrawMultiLine(QWidget):
    def __init__(self):
        super(DrawMultiLine, self).__init__()
        self.resize(300, 300)
        self.setWindowTitle('设置pen的样式')

    def paintEvent(self, event):
        painter = QPainter()
        painter.begin(self)
        painter.setPen(Qt.blue)

        pen = QPen(Qt.red,2,Qt.SolidLine)
        painter.setPen(pen)
        painter.drawLine(20,40,250,40)


        pen.setStyle(Qt.DashLine)
        painter.setPen(pen)
        painter.drawLine(20, 80, 250, 80)

        pen.setStyle(Qt.DashDotDotLine)
        painter.setPen(pen)
        painter.drawLine(20, 120, 250, 120)



        pen.setStyle(Qt.DotLine)
        painter.setPen(pen)
        painter.drawLine(20, 160, 250, 160)

        pen.setStyle(Qt.DashDotDotLine)
        pen.setDashPattern([1,10,5,4])
        painter.setPen(pen)
        painter.drawLine(20, 200, 250, 200)



        size = self.size()



        painter.end()


if __name__ == '__main__':
    app = QApplication(sys.argv)
    main = DrawMultiLine()
    main.show()
    sys.exit(app.exec_())






