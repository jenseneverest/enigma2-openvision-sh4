# -*- coding: utf-8 -*-
from __future__ import print_function
from config import config, ConfigSubsection, ConfigSlider, ConfigYesNo, ConfigNothing
from enigma import eDBoxLCD
from Components.SystemInfo import SystemInfo
from Screens.InfoBar import InfoBar
from Screens.Screen import Screen

class dummyScreen(Screen):
	skin = """<screen position="0,0" size="0,0" transparent="1">
	<widget source="session.VideoPicture" render="Pig" position="0,0" size="0,0" backgroundColor="transparent" zPosition="1"/>
	</screen>"""
	def __init__(self, session, args=None):
		Screen.__init__(self, session)
		self.close()

class LCD:
	def __init__(self):
		pass

	def setBright(self, value):
		value *= 255
		value /= 10
		if value > 255:
			value = 255
		eDBoxLCD.getInstance().setLCDBrightness(value)

	def setContrast(self, value):
		value *= 63
		value /= 20
		if value > 63:
			value = 63
		eDBoxLCD.getInstance().setLCDContrast(value)

	def setInverted(self, value):
		if value:
			value = 255
		eDBoxLCD.getInstance().setInverted(value)

	def setFlipped(self, value):
		eDBoxLCD.getInstance().setFlipped(value)

	def isOled(self):
		return eDBoxLCD.getInstance().isOled()

<<<<<<< HEAD
=======
	def setMode(self, value):
		if fileExists("/proc/stb/lcd/show_symbols"):
			print('[Lcd] setLCDMode',value)
			open("/proc/stb/lcd/show_symbols", "w").write(value)
		if config.lcd.mode.value == "0":
			SystemInfo["SeekStatePlay"] = False
			SystemInfo["StatePlayPause"] = False
			if fileExists("/proc/stb/lcd/symbol_hdd"):
				open("/proc/stb/lcd/symbol_hdd", "w").write("0")
			if fileExists("/proc/stb/lcd/symbol_hddprogress"):
				open("/proc/stb/lcd/symbol_hddprogress", "w").write("0")
			if fileExists("/proc/stb/lcd/symbol_network"):
				open("/proc/stb/lcd/symbol_network", "w").write("0")
			if fileExists("/proc/stb/lcd/symbol_signal"):
				open("/proc/stb/lcd/symbol_signal", "w").write("0")
			if fileExists("/proc/stb/lcd/symbol_timeshift"):
				open("/proc/stb/lcd/symbol_timeshift", "w").write("0")
			if fileExists("/proc/stb/lcd/symbol_tv"):
				open("/proc/stb/lcd/symbol_tv", "w").write("0")
			if fileExists("/proc/stb/lcd/symbol_usb"):
				open("/proc/stb/lcd/symbol_usb", "w").write("0")

	def setPower(self, value):
		if fileExists("/proc/stb/power/vfd"):
			print('[Lcd] setLCDPower',value)
			open("/proc/stb/power/vfd", "w").write(value)
		elif fileExists("/proc/stb/lcd/vfd"):
			print('[Lcd] setLCDPower',value)
			open("/proc/stb/lcd/vfd", "w").write(value)

	def setShowoutputresolution(self, value):
		if fileExists("/proc/stb/lcd/show_outputresolution"):
			print('[Lcd] setLCDShowoutputresolution',value)
			open("/proc/stb/lcd/show_outputresolution", "w").write(value)

	def setfblcddisplay(self, value):
		if fileExists("/proc/stb/fb/sd_detach"):
			print('[Lcd] setfblcddisplay',value)
			open("/proc/stb/fb/sd_detach", "w").write(value)

	def setRepeat(self, value):
		if fileExists("/proc/stb/lcd/scroll_repeats"):
			print('[Lcd] setLCDRepeat',value)
			open("/proc/stb/lcd/scroll_repeats", "w").write(value)

	def setScrollspeed(self, value):
		if fileExists("/proc/stb/lcd/scroll_delay"):
			print('[Lcd] setLCDScrollspeed',value)
			open("/proc/stb/lcd/scroll_delay", "w").write(value)

	def setLEDNormalState(self, value):
		eDBoxLCD.getInstance().setLED(value, 0)

	def setLEDDeepStandbyState(self, value):
		eDBoxLCD.getInstance().setLED(value, 1)

	def setLEDBlinkingTime(self, value):
		eDBoxLCD.getInstance().setLED(value, 2)

	def setLCDMiniTVMode(self, value):
		if fileExists("/proc/stb/lcd/mode"):
			print('[Lcd] setLCDMiniTVMode',value)
			open("/proc/stb/lcd/mode", "w").write(value)

	def setLCDMiniTVPIPMode(self, value):
		print('[Lcd] setLCDMiniTVPIPMode',value)

	def setLCDMiniTVFPS(self, value):
		if fileExists("/proc/stb/lcd/fps"):
			print('[Lcd] setLCDMiniTVFPS',value)
			open("/proc/stb/lcd/fps", "w").write(value)

>>>>>>> ea39993a3... Use print() method Python 3, stage 1
def leaveStandby():
	config.lcd.bright.apply()

def standbyCounterChanged(dummy):
	from Screens.Standby import inStandby
	inStandby.onClose.append(leaveStandby)
	config.lcd.standby.apply()

def InitLcd():
	detected = eDBoxLCD.getInstance() and eDBoxLCD.getInstance().detected()
	config.lcd = ConfigSubsection();
	if detected:
<<<<<<< HEAD
=======
		ilcd = LCD()
		if can_lcdmodechecking:
			def setLCDModeMinitTV(configElement):
				try:
					print('[Lcd] setLCDModeMinitTV',configElement.value)
					open("/proc/stb/lcd/mode", "w").write(configElement.value)
				except:
					pass
			def setMiniTVFPS(configElement):
				try:
					print('[Lcd] setMiniTVFPS',configElement.value)
					open("/proc/stb/lcd/fps", "w").write(configElement.value)
				except:
					pass
			def setLCDModePiP(configElement):
				pass
			def setLCDScreenshot(configElement):
				ilcd.setScreenShot(configElement.value)

			config.lcd.modepip = ConfigSelection(choices={
					"0": _("off"),
					"5": _("PIP"),
					"7": _("PIP with OSD")},
					default = "0")
			if SystemInfo["GigaBlueQuad"]:
				config.lcd.modepip.addNotifier(setLCDModePiP)
			else:
				config.lcd.modepip = ConfigNothing()
			config.lcd.screenshot = ConfigYesNo(default=False)
			config.lcd.screenshot.addNotifier(setLCDScreenshot)

			config.lcd.modeminitv = ConfigSelection(choices={
					"0": _("normal"),
					"1": _("MiniTV"),
					"2": _("OSD"),
					"3": _("MiniTV with OSD")},
					default = "0")
			config.lcd.fpsminitv = ConfigSlider(default=30, limits=(0, 30))
			config.lcd.modeminitv.addNotifier(setLCDModeMinitTV)
			config.lcd.fpsminitv.addNotifier(setMiniTVFPS)
		else:
			config.lcd.modeminitv = ConfigNothing()
			config.lcd.screenshot = ConfigNothing()
			config.lcd.fpsminitv = ConfigNothing()

		config.lcd.scroll_speed = ConfigSelection(default = "300", choices = [
			("500", _("slow")),
			("300", _("normal")),
			("100", _("fast"))])
		config.lcd.scroll_delay = ConfigSelection(default = "10000", choices = [
			("10000", "10 " + _("seconds")),
			("20000", "20 " + _("seconds")),
			("30000", "30 " + _("seconds")),
			("60000", "1 " + _("minute")),
			("300000", "5 " + _("minutes")),
			("noscrolling", _("off"))])

>>>>>>> ea39993a3... Use print() method Python 3, stage 1
		def setLCDbright(configElement):
			ilcd.setBright(configElement.value);

		def setLCDcontrast(configElement):
			ilcd.setContrast(configElement.value);

		def setLCDinverted(configElement):
			ilcd.setInverted(configElement.value);

		def setLCDflipped(configElement):
			ilcd.setFlipped(configElement.value);

		standby_default = 0

		ilcd = LCD()

		if not ilcd.isOled():
			config.lcd.contrast = ConfigSlider(default=5, limits=(0, 20))
			config.lcd.contrast.addNotifier(setLCDcontrast);
		else:
			config.lcd.contrast = ConfigNothing()
			standby_default = 1

		config.lcd.standby = ConfigSlider(default=standby_default, limits=(0, 10))
		config.lcd.standby.addNotifier(setLCDbright);
		config.lcd.standby.apply = lambda : setLCDbright(config.lcd.standby)

		config.lcd.bright = ConfigSlider(default=5, limits=(0, 10))
		config.lcd.bright.addNotifier(setLCDbright);
		config.lcd.bright.apply = lambda : setLCDbright(config.lcd.bright)
		config.lcd.bright.callNotifiersOnSaveAndCancel = True

		config.lcd.invert = ConfigYesNo(default=False)
		config.lcd.invert.addNotifier(setLCDinverted);

		config.lcd.flip = ConfigYesNo(default=False)
		config.lcd.flip.addNotifier(setLCDflipped);

		if SystemInfo["LcdLiveTV"]:
			def lcdLiveTvChanged(configElement):
				setLCDLiveTv(configElement.value)
				configElement.save()
			config.lcd.showTv = ConfigYesNo(default = False)
			config.lcd.showTv.addNotifier(lcdLiveTvChanged)

			if "live_enable" in SystemInfo["LcdLiveTV"]:
				config.misc.standbyCounter.addNotifier(standbyCounterChangedLCDLiveTV, initial_call = False)
	else:
		def doNothing():
			pass
		config.lcd.contrast = ConfigNothing()
		config.lcd.bright = ConfigNothing()
		config.lcd.standby = ConfigNothing()
		config.lcd.bright.apply = lambda : doNothing()
		config.lcd.standby.apply = lambda : doNothing()

	config.misc.standbyCounter.addNotifier(standbyCounterChanged, initial_call = False)

def setLCDLiveTv(value):
	if "live_enable" in SystemInfo["LcdLiveTV"]:
		open(SystemInfo["LcdLiveTV"], "w").write(value and "enable" or "disable")
	else:
		open(SystemInfo["LcdLiveTV"], "w").write(value and "0" or "1")
	if not value:
		try:
			InfoBarInstance = InfoBar.instance
			InfoBarInstance and InfoBarInstance.session.open(dummyScreen)
		except:
			pass

def leaveStandbyLCDLiveTV():
	if config.lcd.showTv.value:
		setLCDLiveTv(True)

def standbyCounterChangedLCDLiveTV(dummy):
	if config.lcd.showTv.value:
		from Screens.Standby import inStandby
		if leaveStandbyLCDLiveTV not in inStandby.onClose:
			inStandby.onClose.append(leaveStandbyLCDLiveTV)
		setLCDLiveTv(False)
