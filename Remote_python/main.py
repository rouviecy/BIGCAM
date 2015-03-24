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
import sys, time, serial

if __name__ == '__main__':
	ser = serial.Serial("/dev/serial/by-id/usb-FTDI_TTL232R-3V3_FTH0D7TW-if00-port0", 4800, timeout=1)
	cli_out = Interface_client_out(sys.argv[1], ser)
	cli_in = Interface_client_in(sys.argv[1], ser)
	gui = GUI(cli_out)
	gui.start()
	time.sleep(2)
	cli_in.start()
	gui.join()
	cli_in.join()
	ser.close()
