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

	def go_left(self, activer):			self.envoyer("L")
	def go_right(self, activer):		self.envoyer("R")
	def go_up(self, activer):			self.envoyer("U")
	def go_down(self, activer):			self.envoyer("D")
	def go_more(self, activer):			self.envoyer("+")
	def go_less(self, activer):			self.envoyer("-")
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
			print state
			self.draw_monitor(state)
		self.stop()

	def draw_monitor(self, state):
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
