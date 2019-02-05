installdir = $(pkglibdir)/python/Plugins/Extensions

SUBDIRS = TuxboxPlugins CutListEditor DVDPlayer PicturePlayer MediaScanner MediaPlayer GraphMultiEPG SocketMMI

if ENABLE_TF7700
SUBDIRS += TopfieldVFD
endif

if IS_CUBEREVO
SUBDIRS += CuberevoVFD
endif

if ENABLE_FORTIS_HDBOX
SUBDIRS += fs9000VFD
endif

if ENABLE_OCTAGON1008
SUBDIRS += hs9510VFD
endif

if ENABLE_ATEVIO7500
SUBDIRS += hs8200VFD
endif

if ENABLE_HS7110
SUBDIRS += hs7110VFD
endif

if ENABLE_HS7420
SUBDIRS += hs742xVFD
endif

if ENABLE_HS7810A
SUBDIRS += hs7810aVFD
endif

if ENABLE_HS7119
SUBDIRS += hs7810aVFD
endif

if ENABLE_HS7429
SUBDIRS += hs742xVFD
endif

if ENABLE_HS7819
SUBDIRS += hs7810aVFD
endif

install_PYTHON =	\
	__init__.py
