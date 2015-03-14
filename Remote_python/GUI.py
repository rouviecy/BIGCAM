# -*- coding: utf-8 -*-
# @(#)		GUI.py
# @version	1.1
# @autor	C. Rouvière

'''
Provide GUI to listen keyboard and joystick
Adapted from NAO_TOOLS project :
https://github.com/rouviecy/NAO_TOOLS
'''

import pygame
import math			as m
from pygame.locals	import *
from Configuration	import Configuration as c
from threading		import Thread

class GUI(Thread):

	def __init__(self, serveur):
		Thread.__init__(self)
		self.joystick_WE = 0
		self.joystick_NS = 0
		self.joystick_ROT = 0
		self.current_v = 0
		self.clock = pygame.time.Clock()
		self.serveur = serveur
		self.initialisation()
		self.rafraishissement()

	def initialisation(self):
		pygame.init()
		fenetre = pygame.display.set_mode((100, 100))
		nb = pygame.joystick.get_count()
		print str(nb) + " joystick(s) détectés"
		if(nb > 0):
			print "Activation du 1er joystick"
			mon_joystick = pygame.joystick.Joystick(0)
			mon_joystick.init()
			return True
		return False

	def rafraishissement(self):
		pygame.display.flip()

	def action_clavier(self, downing, key):
		if		key == c.K_QUIT:					return False
		elif	key == c.K_UP:						self.serveur.go_up(downing)
		elif	key == c.K_DOWN:					self.serveur.go_down(downing)
		elif	key == c.K_LEFT:					self.serveur.go_left(downing)
		elif	key == c.K_RIGHT:					self.serveur.go_right(downing)
		elif	key == c.K_VITMORE:					self.serveur.go_more(downing)
		elif	key == c.K_VITLESS:					self.serveur.go_less(downing)
		elif	key == c.K_REMOTEON:
			if downing:								self.serveur.remote_enable(True)
		elif	key == c.K_REMOTEOFF:
			if downing:								self.serveur.remote_enable(False)
		return True

	def action_joystick_bouton(self, bouton):
		if		bouton == c.J_BUTTON_A:			self.serveur.remote_enable(True)
		elif	bouton == c.J_BUTTON_B:			self.serveur.remote_enable(False)
		return True

	def action_joystick_axe(self, axe, valeur):
		if		axe == c.J_AXIS_SCROLL:	self.action_scroll(valeur)
		if		axe == c.J_AXIS_NS:		self.action_NS(valeur)
		if		axe == c.J_AXIS_WE:		self.action_WE(valeur)
#		if		axe == c.J_AXIS_ROT:	self.action_ROT(valeur)
		return True

	def action_hat(self, hat, valeur):
		if hat != c.J_HAT_HEAD: return True
		elif	valeur == c.J_HAT_W :	self.serveur.deriv_right(True)
		elif	valeur == c.J_HAT_E :	self.serveur.deriv_left(True)
		elif	valeur == c.J_HAT_NW :	self.serveur.deriv_right(True)
		elif	valeur == c.J_HAT_SW :	self.serveur.deriv_right(True)
		elif	valeur == c.J_HAT_NE :	self.serveur.deriv_left(True)
		elif	valeur == c.J_HAT_SE :	self.serveur.deriv_left(True)
		elif	valeur == c.J_HAT_N :	self.serveur.deriv_left(False)
		elif	valeur == c.J_HAT_S :	self.serveur.deriv_left(False)
		elif	valeur == c.J_HAT_0 :	self.serveur.deriv_left(False)
		return True

	def action_scroll(self, valeur):
		val_min = c.J_INTERVAL_SCROLL[0]
		val_max = c.J_INTERVAL_SCROLL[1]
		nb_steps = c.J_STEP_SCROLL
		valeur_corrigee = -valeur
		if valeur_corrigee > +0.95 : valeur_corrigee = +1.0
		if valeur_corrigee < -0.95 : valeur_corrigee = -1.0
		power = int(m.floor(valeur_corrigee * (nb_steps - 1) / (val_max - val_min)) + 5)
		if power < 1:	power = 0
		if power > 8:	power = 9
		self.serveur.set_velocity(power)
		return True

	def action_NS(self, valeur):
		val_min = c.J_INTERVAL_NS[0]
		val_max = c.J_INTERVAL_NS[1]
		nb_steps = c.J_STEP_NS
		valeur_corrigee = -valeur
		if valeur_corrigee > +0.95 : valeur_corrigee = +1.0
		if valeur_corrigee < -0.95 : valeur_corrigee = -1.0
		power = int(m.floor(valeur_corrigee * (nb_steps - 1) / (val_max - val_min)) + 5)
		if power < 1:	power = 0
		if power > 8:	power = 9
		self.serveur.set_back(power)
		return True

	def action_WE(self, valeur):
		val_min = c.J_INTERVAL_WE[0]
		val_max = c.J_INTERVAL_WE[1]
		nb_steps = c.J_STEP_WE
		valeur_corrigee = +valeur
		if valeur_corrigee > +0.95 : valeur_corrigee = +1.0
		if valeur_corrigee < -0.95 : valeur_corrigee = -1.0
		power = int(m.floor(valeur_corrigee * (nb_steps - 1) / (val_max - val_min)) + 5)
		if power < 1:	power = 0
		if power > 8:	power = 9
		self.serveur.set_turn(power)
		return True

	def action_ROT(self, valeur):
		val_min = c.J_INTERVAL_ROT[0]
		val_max = c.J_INTERVAL_ROT[1]
		nb_steps = c.J_STEP_ROT
		valeur_corrigee = -valeur
		if valeur_corrigee > +0.95 : valeur_corrigee = +1.0
		if valeur_corrigee < -0.95 : valeur_corrigee = -1.0
		power = int(m.floor(valeur_corrigee * (nb_steps - 1) / (val_max - val_min)) + 5)
		if power < 1:	power = 0
		if power > 8:	power = 9
		self.serveur.set_deriv(power)
		return True

	def run(self):
		continuer = True
		while continuer:
			for event in pygame.event.get():
				if		event.type == QUIT:				continuer = False
				elif	event.type == KEYDOWN:			continuer = self.action_clavier(True, event.key)
				elif	event.type == KEYUP:			continuer = self.action_clavier(False, event.key)
				elif	event.type == JOYBUTTONDOWN:	continuer = self.action_joystick_bouton(event.button)
				elif	event.type == JOYAXISMOTION:	continuer = self.action_joystick_axe(event.axis, event.value)
				elif	event.type == JOYHATMOTION:		continuer = self.action_hat(event.hat, event.value)
			self.clock.tick(20)
		self.stop()

	def stop(self):
		self.serveur.quitter()
