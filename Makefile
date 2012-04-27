
CHANGE_DIR = cd src


all:
	$(CHANGE_DIR); $(MAKE) $(MFLAGS)

clean:
	$(CHANGE_DIR); $(MAKE) clean

obj:
	$(CHANGE_DIR); $(MAKE) obj	

viewer:
	$(CHANGE_DIR); $(MAKE) viewer

simplify:
	$(CHANGE_DIR); $(MAKE) simplify
