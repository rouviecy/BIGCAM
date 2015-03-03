import socket
import time

class Interface_client(object):

	def __init__(self, host):
		port = 4242
		self.ouvert = True
		self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		self.s.connect((host, port))

	def go_left(self, activer):		self.envoyer("Q")
	def go_right(self, activer):	self.envoyer("S")
	def go_north(self, activer):	self.envoyer("R")
	def go_south(self, activer):	self.envoyer("T")
	def go_west(self, activer):		pass
	def go_est(self, activer):		pass
	def stiffness(self, activer):	pass
	def save_joints(self, save):	pass
	def last_pose(self):			pass
	def record(self):				pass
	def assis(self):				pass
	def debout(self):				pass
	def vitesse_tete(self, vx, vy):	pass
	def quitter(self):
		self.envoyer("f")
		time.sleep(1)
		self.s.close()

	def envoyer(self, message):
		self.s.send(message.encode())
