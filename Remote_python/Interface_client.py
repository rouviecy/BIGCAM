# -*- coding: utf-8 -*-
# @(#)		Interface_client.py
# @version	1.1
# @autor	C. Rouvière

'''
Python TCP Client
Adapted from NAO_TOOLS project :
https://github.com/rouviecy/NAO_TOOLS
'''

import socket
import time

class Interface_client(object):

	def __init__(self, host):
		port = 4242
		self.ouvert = True
		self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
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
