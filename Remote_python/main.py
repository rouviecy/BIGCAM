# -*- coding: utf-8 -*-
# @(#)		main.py
# @version	1.1
# @autor	C. Rouvière

'''
Begin remote control with keyboard/joystick and TCP
Adapted from NAO_TOOLS project :
https://github.com/rouviecy/NAO_TOOLS
'''

from GUI				import GUI
from Interface_client	import Interface_client
import sys

if __name__ == '__main__':
	cli = Interface_client(sys.argv[1])
	gui = GUI(cli)
