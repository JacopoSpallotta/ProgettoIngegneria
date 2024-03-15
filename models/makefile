
ENVIDIR = environment/src
INSLPMPIDIR = insulin_pump/src
PATIDIR = patient/src
MONITORDIR = monitors/src
CON2REDISDIR = ../con2redis/src
CON2DBDIR = ../con2db
TIMEDIR = time/src
SCREENDIR = ../InsulinPumpDisplay

SUBDIRS = $(CON2REDISDIR) $(CON2DBDIR) $(TIMEDIR) $(ENVIDIR) $(INSLPMPIDIR) $(PATIDIR) $(MONITORDIR) $(SCREENDIR)

all:
	@echo ""
	@echo "######################################";
	@echo "######## BUILDING ALL TARGETS ########";
	@echo "######################################";
	@echo ""
	for i in $(SUBDIRS) ; \
	  do (cd $$i ; $(MAKE) ) ; \
	done

con2redis:
	@cd $(CON2REDISDIR) ; $(MAKE)

con2db:
	@cd $(CON2DBDIR) ; $(MAKE)

time:
	@cd $(TIMEDIR) ; $(MAKE)

env:
	@cd $(ENVDIR) ; $(MAKE)

insl:
	@cd $(INSLPMPDIR) ; $(MAKE)

pat:
	@cd $(PATDIR) ; $(MAKE)

monitor:
	@cd $(MONITORDIR) ; $(MAKE)

screen:
	@cd $(SCREENDIR) ; $(MAKE)

.PHONY: clean

clean:
	for i in $(SUBDIRS) ; \
	  do ( cd $$i ; $(MAKE) clean ) ; \
	done

clear:
	for i in $(SUBDIRS) ; \
	  do ( cd $$i ; $(MAKE) clean ) ; \
	done