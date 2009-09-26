
if DOC

all:
	@DOXYGEN@ Doxyfile

else

all:

endif

EXTRA_DIST = manual.xml
dist_doc_DATA = index.html manual.html style.css
docdir = ${datadir}/doc/${PACKAGE}

install-data-local :
	$(MKDIR_P) $(DESTDIR)$(docdir)
	cp -R html $(DESTDIR)$(docdir)

uninstall-local :
	chmod -R +w $(DESTDIR)$(docdir)
	rm -rf $(DESTDIR)$(docdir)

dist-hook :
	$(MKDIR_P) $(distdir)
	cp -R html $(distdir)

clean-local:
	$(RM) -rf html

