SUBDIRS = src data doc

binarydistdir = $(PACKAGE)-$(VERSION)-binary-i386

dist-binary: distdir
	cd src && $(MAKE) feuerkraft.static
	$(MAKE) install prefix=$(shell pwd)/$(binarydistdir)
	$(mkinstalldirs) $(binarydistdir)/share/guile/
	cp -R /usr/share/guile/1.6/ice-9/ $(binarydistdir)/share/guile/
	cp -R /usr/share/guile/1.6/oop/   $(binarydistdir)/share/guile/
	cp -R /usr/share/guile/1.6/srfi/  $(binarydistdir)/share/guile/
	cp src/feuerkraft.static   $(binarydistdir)/games/feuerkraft
	cp contrib/feuerkraft   $(binarydistdir)/feuerkraft
	$(AMTAR) chof - $(binarydistdir) | bzip2 -9 -c >  $(binarydistdir).tar.bz2
	rm -rf $(binarydistdir)

# EOF #