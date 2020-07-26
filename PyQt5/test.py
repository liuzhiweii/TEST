
from PyQt5.Qt import *
import sys
class Window(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("刘志伟")
        self.resize(500, 500)
        label = QLabel(self)
        label.setText("liuzhiwie ")

app = QApplication(sys.argv)

window = Window()

window.move(400, 200)


window.show()
sys.exit(app.exec_())

