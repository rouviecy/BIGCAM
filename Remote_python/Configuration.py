# -*- coding: utf-8 -*-
# @(#)		Configuration.py
# @version	1.1
# @autor	C. Rouvière

'''
Configuration to listen keyboard and joystick
Adapted from NAO_TOOLS project :
https://github.com/rouviecy/NAO_TOOLS
'''

class Configuration(object):

	K_UP =				273 # arrow up
	K_DOWN =			274 # arrow down
	K_LEFT =			276 # arrow left
	K_RIGHT =			275 # arrow right
	K_VITMORE =			270 # +
	K_VITLESS =			269 # -
	K_REMOTEON =		97	# a
	K_REMOTEOFF =		122 # z
	K_QUIT =			113 # q

	J_INDEX =			0
	J_BUTTON_A =		0	# activate remote control
	J_BUTTON_B =		1	# desactivate remote control
	J_AXIS_WE =			0
	J_AXIS_NS =			1
	J_AXIS_ROT =		2
	J_AXIS_SCROLL =		3
	J_INTERVAL_W =		[-2.0, -0.5]
	J_INTERVAL_E =		[+0.5, +2.0]
	J_INTERVAL_0WE =	[-0.3, +0.3]
	J_INTERVAL_N =		[-2.0, -0.5]
	J_INTERVAL_S =		[+0.5, +2.0]
	J_INTERVAL_0NS =	[-0.3, +0.3]
	J_INTERVAL_L =		[-2.0, -0.9]
	J_INTERVAL_R =		[+0.9, +2.0]
	J_INTERVAL_0ROT =	[-0.7, +0.7]
	J_INTERVAL_SCROLL =	[-0.9, +0.9]
	J_STEP_SCROLL =		10
	J_HAT_HEAD =		0
	J_HAT_0 =			(+0, +0)
	J_HAT_N =			(+0, +1)
	J_HAT_S =			(+0, -1)
	J_HAT_W =			(-1, +0)
	J_HAT_E =			(+1, +0)
	J_HAT_NE =			(+1, +1)
	J_HAT_SE =			(+1, -1)
	J_HAT_SW =			(-1, -1)
	J_HAT_NW =			(-1, +1)
