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
from Interface_client	import Interface_client_in
from Interface_client	import Interface_client_out
import sys, time

if __name__ == '__main__':
	cli_out = Interface_client_out(sys.argv[1])
	cli_in = Interface_client_in(sys.argv[1])
	gui = GUI(cli_out)
	gui.start()
	time.sleep(2)
	cli_in.start()
	gui.join()
	cli_in.join()
