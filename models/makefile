
ENVIDIR = environment/src
INSLPMPIDIR = insulin_pump/src
PATIDIR = patient/src
MONITORDIR = monitors/src

SUBDIRS = $(ENVIDIR) $(INSLPMPIDIR) $(PATIDIR) $(MONITORDIR)

all:
	@echo ""
	@echo "######################################";
	@echo "######## BUILDING ALL TARGETS ########";
	@echo "######################################";
	@echo ""
	for i in $(SUBDIRS) ; \
	  do (cd $$i ; $(MAKE) ) ; \
	done

env:
	@cd $(ENVDIR) ; $(MAKE)

insl:
	@cd $(INSLPMPDIR) ; $(MAKE)

pat:
	@cd $(PATDIR) ; $(MAKE)

monitor:
	@cd $(MONITORDIR) ; $(MAKE)

.PHONY: clean

clean:
	for i in $(SUBDIRS) ; \
	  do ( cd $$i ; $(MAKE) clean ) ; \
	done

clear:
	for i in $(SUBDIRS) ; \
	  do ( cd $$i ; $(MAKE) clean ) ; \
	done