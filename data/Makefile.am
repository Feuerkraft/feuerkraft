SUBDIRS = missions images

pkgdatadir = $(datadir)/games/@PACKAGE@

pkgdata_DATA = feuerkraft.xml tiles.scm tiles.xml feuerkraft.scm $(wildchar sounds/*.wav)
EXTRA_DIST   = $(pkgdata_DATA) tiles.scm tiles.xml gentiledesc.scm gentilesscr.scm 

tiles.scm: images/tiles gentiledesc.scm
	./gentiledesc.scm > tiles.scm

tiles.xml: images/tiles gentilesscr.scm
	./gentilesscr.scm > tiles.xml

## EOF ##
