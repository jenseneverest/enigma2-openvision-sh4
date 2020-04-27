#!/usr/bin/python
# -*- coding: utf-8 -*-
import os
from enigma import getBoxType
from Tools.Directories import SCOPE_SKIN, resolveFilename

class RcModel:
	RcModels = {}

	def __init__(self):
		self.model = getBoxType()
		# cfg files has modelname rcname entries.
		# modelname is boxname optionally followed by .rctype
		for line in open((resolveFilename(SCOPE_SKIN, 'rc_models/rc_models.cfg')), 'r'):
			if line.startswith(self.model):
				m, r = line.strip().split()
				self.RcModels[m] = r

	def getRcFile(self, ext):
		if self.model in self.RcModels.keys():
			remote = self.RcModels[self.model]
		else:
			remote = "spark"
		f = resolveFilename(SCOPE_SKIN, 'rc_models/' + remote + '.' + ext)
		if not os.path.exists(f):
			f = resolveFilename(SCOPE_SKIN, 'rc_models/spark.' + ext)
		return f

	def getRcImg(self):
		return self.getRcFile('png')

	def getRcPositions(self):
		return self.getRcFile('xml')

rc_model = RcModel()
