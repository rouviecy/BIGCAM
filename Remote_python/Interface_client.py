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
		port = 4243
		self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		self.s.connect((host, port))

	def run(self):
		while True:
			msg_in = self.s.recv(1024)
			print msg_in[0], msg_in[1]
			if msg_in[0] == 'b' and msg_in[1] == 'y' and msg_in[2] == 'e':
				break
		self.stop()

	def stop(self):
		self.s.close()
