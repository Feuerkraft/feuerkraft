pkgdatadir = $(datadir)/games/@PACKAGE@

EXTRA_DIST = feuerkraft.scr images/*.png

pkgdata_DATA = $(EXTRA_DIST)

install-data-local: $(my_pkg_data)
	$(mkinstalldirs) $(DESTDIR)$(pkgdatadir)/images/

## EOF ##
