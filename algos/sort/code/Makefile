TARGETS = C
CLEAN_TRGETS = $(TARGETS:%=%-clean)

${TARGETS} :
	${MAKE} -C $@

$(CLEAN_TRGETS) :
	${MAKE} -C $(@:%-clean=%) clean 

clean : $(CLEAN_TRGETS)