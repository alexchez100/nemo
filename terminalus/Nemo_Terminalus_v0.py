import sys
from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5 import uic

class MyApp(QtWidgets):
    def __init__(self):
        super().__init__()
        uic.loadUi(Nemo_Terminalus_v0.ui)