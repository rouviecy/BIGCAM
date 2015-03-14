# -*- coding: utf-8 -*-
# @(#)		Interface_client.py
# @version	1.1
# @autor	C. Rouvière

'''
Python TCP Client
Adapted from NAO_TOOLS project :
https://github.com/rouviecy/NAO_TOOLS
'''

from threading import Thread
import socket
import time
import locale
import cv2
import numpy as np
import math as m

class Interface_client_out(object):

	def __init__(self, host):
		port = 4242
		self.s	= socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		self.s.connect((host, port))

	def go_left(self, activer):			self.envoyer("L" + ("1" if activer else "0"))
	def go_right(self, activer):		self.envoyer("R" + ("1" if activer else "0"))
	def go_up(self, activer):			self.envoyer("U" + ("1" if activer else "0"))
	def go_down(self, activer):			self.envoyer("D" + ("1" if activer else "0"))
	def deriv_left(self, activer):		self.envoyer("W" + ("1" if activer else "0"))
	def deriv_right(self, activer):		self.envoyer("X" + ("1" if activer else "0"))
	def go_more(self, activer):			self.envoyer("+")
	def go_less(self, activer):			self.envoyer("-")
	def set_velocity(self, val_0_to_9):
		if		val_0_to_9 == 0:		self.envoyer("M0")
		elif	val_0_to_9 == 1:		self.envoyer("M1")
		elif	val_0_to_9 == 2:		self.envoyer("M2")
		elif	val_0_to_9 == 3:		self.envoyer("M3")
		elif	val_0_to_9 == 4:		self.envoyer("M4")
		elif	val_0_to_9 == 5:		self.envoyer("M5")
		elif	val_0_to_9 == 6:		self.envoyer("M6")
		elif	val_0_to_9 == 7:		self.envoyer("M7")
		elif	val_0_to_9 == 8:		self.envoyer("M8")
		elif	val_0_to_9 == 9:		self.envoyer("M9")
	def set_back(self, val_0_to_9):
		if		val_0_to_9 == 0:		self.envoyer("B0")
		elif	val_0_to_9 == 1:		self.envoyer("B1")
		elif	val_0_to_9 == 2:		self.envoyer("B2")
		elif	val_0_to_9 == 3:		self.envoyer("B3")
		elif	val_0_to_9 == 4:		self.envoyer("B4")
		elif	val_0_to_9 == 5:		self.envoyer("B5")
		elif	val_0_to_9 == 6:		self.envoyer("B6")
		elif	val_0_to_9 == 7:		self.envoyer("B7")
		elif	val_0_to_9 == 8:		self.envoyer("B8")
		elif	val_0_to_9 == 9:		self.envoyer("B9")
	def set_turn(self, val_0_to_9):
		if		val_0_to_9 == 0:		self.envoyer("T0")
		elif	val_0_to_9 == 1:		self.envoyer("T1")
		elif	val_0_to_9 == 2:		self.envoyer("T2")
		elif	val_0_to_9 == 3:		self.envoyer("T3")
		elif	val_0_to_9 == 4:		self.envoyer("T4")
		elif	val_0_to_9 == 5:		self.envoyer("T5")
		elif	val_0_to_9 == 6:		self.envoyer("T6")
		elif	val_0_to_9 == 7:		self.envoyer("T7")
		elif	val_0_to_9 == 8:		self.envoyer("T8")
		elif	val_0_to_9 == 9:		self.envoyer("T9")
	def set_deriv(self, val_0_to_9):
		if		val_0_to_9 == 0:		self.envoyer("C0")
		elif	val_0_to_9 == 1:		self.envoyer("C1")
		elif	val_0_to_9 == 2:		self.envoyer("C2")
		elif	val_0_to_9 == 3:		self.envoyer("C3")
		elif	val_0_to_9 == 4:		self.envoyer("C4")
		elif	val_0_to_9 == 5:		self.envoyer("C5")
		elif	val_0_to_9 == 6:		self.envoyer("C6")
		elif	val_0_to_9 == 7:		self.envoyer("C7")
		elif	val_0_to_9 == 8:		self.envoyer("C8")
		elif	val_0_to_9 == 9:		self.envoyer("C9")
	def remote_enable(self, activer):	self.envoyer("A" if activer else "Z")
	def quitter(self):
		self.envoyer("Q")
		time.sleep(1)
		self.s.close()

	def envoyer(self, message):
		self.s.send(message.encode())

class Interface_client_in(Thread):

	def __init__(self, host):
		Thread.__init__(self)
		cv2.startWindowThread()
		port = 4243
		self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		self.s.connect((host, port))
		cv2.namedWindow('Monitor')
		self.MONITOR_SIZE = 700
		self.MONITOR_BORDER = 100
		self.available_size = float(self.MONITOR_SIZE - self.MONITOR_BORDER)
		self.min_coord = -1.
		self.max_coord = +1.
		self.path = []

	def run(self):
		while True:
			msg = self.s.recv(1024).split('\0')[0]
			if msg == "bye" : break
			state = []
			mini_buffer = ""
			for i in range(len(msg)):
				if msg[i] == '|':
					state.append(locale.atof(mini_buffer))
					mini_buffer = ""
				else:
					mini_buffer += msg[i]
			self.draw_monitor(state)
		self.stop()

	def draw_monitor(self, state):
		if(len(state) < 4):
			return
		x, y, z, thz = state
		img_monitor = np.zeros((self.MONITOR_SIZE, self.MONITOR_SIZE, 3), dtype=np.uint8)
		if x < self.min_coord : self.min_coord = x
		if x > self.max_coord : self.max_coord = x
		if y < self.min_coord : self.min_coord = y
		if y > self.max_coord : self.max_coord = y
		diff_minmax = self.max_coord - self.min_coord
		self.path.append([x, y])
		pt_draw_prev = (0, 0)
		first_point = True
		for point in self.path:
			draw_x = self.MONITOR_BORDER / 2 + int(self.available_size * (point[0] - self.min_coord) / diff_minmax)
			draw_y = self.MONITOR_BORDER / 2 + int(self.available_size * (point[1] - self.min_coord) / diff_minmax)
			pt_draw = (draw_x, draw_y)
			if not first_point:
				cv2.line(img_monitor, pt_draw_prev, pt_draw, (255, 0, 0))
			pt_draw_prev = pt_draw
			first_point = False
		cv2.circle(img_monitor, pt_draw_prev, 10, (0, 0, 255), 3)
		pt_arrow = (int(float(pt_draw[0]) + 40. * m.cos(thz)), int(float(pt_draw[1]) + 40. * m.sin(thz)))
		pt_arrow_l = (int(pt_arrow[0] + 10. * m.cos(thz + 2.5)), int(pt_arrow[1] + 10. * m.sin(thz + 2.5)))
		pt_arrow_r = (int(pt_arrow[0] + 10. * m.cos(thz - 2.5)), int(pt_arrow[1] + 10. * m.sin(thz - 2.5)))
		cv2.line(img_monitor, pt_draw_prev, pt_arrow, (0, 0, 255), 3)
		cv2.line(img_monitor, pt_arrow, pt_arrow_l, (0, 0, 255), 3)
		cv2.line(img_monitor, pt_arrow, pt_arrow_r, (0, 0, 255), 3)
		cv2.putText(img_monitor, "x = " + str(x), (10, 20), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255))
		cv2.putText(img_monitor, "y = " + str(y), (10, 40), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255))
		cv2.putText(img_monitor, "z = " + str(z), (10, 60), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255))
		cv2.imshow('Monitor', img_monitor)

	def stop(self):
		self.s.close()
		cv2.destroyAllWindows()
