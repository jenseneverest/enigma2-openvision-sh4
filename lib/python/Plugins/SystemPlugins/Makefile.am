installdir = $(pkglibdir)/python/Plugins/SystemPlugins

SUBDIRS = SoftwareManager PositionerSetup Satfinder \
	SkinSelector SatelliteEquipmentControl Videomode VideoTune Hotplug \
	DefaultServicesScanner DiseqcTester CommonInterfaceAssignment \
	CableScan FastScan OSDPositionSetup OSD3DSetup HdmiCEC VideoClippingSetup \
	VideoEnhancement WirelessLan NetworkWizard SH4OSDAdjustment

if ENABLE_CUBEREVO
SUBDIRS += VFD-Icons
endif

if ENABLE_CUBEREVO_250HD
SUBDIRS += VFD-Icons
endif

if ENABLE_CUBEREVO_2000HD
SUBDIRS += VFD-Icons
endif

if ENABLE_CUBEREVO_3000HD
SUBDIRS += VFD-Icons
endif

if ENABLE_CUBEREVO_9500HD
SUBDIRS += VFD-Icons
endif

if ENABLE_CUBEREVO_MINI
SUBDIRS += VFD-Icons
endif

if ENABLE_CUBEREVO_MINI2
SUBDIRS += VFD-Icons
endif

if ENABLE_SPARK
SUBDIRS += SH4BoosterControl SparkVFDControl
endif

if ENABLE_SPARK7162
SUBDIRS += SparkUnionTunerType SH4BoosterControl SparkVFDControl
endif

install_PYTHON =	\
	__init__.py
