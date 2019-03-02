hw_info = None

class HardwareInfo:
	device_name = _("unavailable")
	device_model = None
	device_version = ""
	device_revision = ""
	device_hdmi = True

	def __init__(self):
		global hw_info
		if hw_info:
			return
		hw_info = self

		print "[HardwareInfo] Scanning hardware info"

		try:
			self.device_name = open("/proc/stb/info/model").read().strip()
		except:
			pass

		self.device_model = self.device_model or self.device_name

		self.machine_name = self.device_model

		if self.device_revision:
			self.device_string = "%s (%s-%s)" % (self.device_model, self.device_revision, self.device_version)
		elif self.device_version:
			self.device_string = "%s (%s)" % (self.device_model, self.device_version)
		else:
			self.device_string = self.device_model

		print "Detected: " + self.get_device_string()

	def get_device_name(self):
		return hw_info.device_name

	def get_device_model(self):
		return hw_info.device_model

	def get_device_version(self):
		return hw_info.device_version

	def get_device_revision(self):
		return hw_info.device_revision

	def get_device_string(self):
		return hw_info.device_string

	def get_machine_name(self):
		return hw_info.machine_name

	def has_hdmi(self):
		return hw_info.device_hdmi
