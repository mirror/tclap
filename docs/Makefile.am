
if DOC

all:
	@DOXYGEN@ Doxyfile

else

all:

endif

EXTRA_DIST = manual.xml
dist_doc_DATA = index.html manual.html style.css

install-data-local :
	$(MKDIR_P) $(DESTDIR)$(docdir)/html
	cp -R html $(DESTDIR)$(docdir)/html

uninstall-local :
	chmod -R +w $(DESTDIR)$(docdir)/html
	rm -rf $(DESTDIR)$(docdir)/html

dist-hook :
	$(MKDIR_P) $(distdir)/html
	cp -R html $(distdir)

clean-local:
	$(RM) -rf html

