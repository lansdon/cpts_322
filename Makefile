################################################################################
TARGET      = tm_app
LDFLAGS     = #-L/usr/local/mysql/lib -lmysqlclient -L/sw/lib -ldl -lz -lstdc++ -lc 
CFLAGS      = #-O2 -I/sw/include -I/usr/local/mysql/include
CPPFLAGS    =
COMPILER    = g++

################################################################################
rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))
CPPSOURCES  = $(call rwildcard,,*.cpp)
CSOURCES    = $(call rwildcard,,*.c)
CPPOBJECTS  = $(CPPSOURCES:%.cpp=tmp/%.o) 
COBJECTS    = $(CSOURCES:%.c=tmp/%.o)
CPPDEPENDS  = $(CPPSOURCES:%.cpp=tmp/%.d) 
CDEPENDS    = $(CSOURCES:%.c=tmp/%.d)

################################################################################
tmp/%.o: %.cpp Makefile
	$(COMPILER) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

tmp/%.o: %.c Makefile
	$(COMPILER) -c $(CFLAGS) $< -o $@

################################################################################
.PHONY: clean dist

$(TARGET): Makefile $(CPPOBJECTS) $(COBJECTS)
	$(COMPILER) -o $@ $(CPPOBJECTS) $(COBJECTS) $(LDFLAGS) 

clean:
	@rm -f $(TARGET)
	@rm -rf tmp/
	@rm -f $(TARGET).tgz

dist:
	@$(MAKE) clean
	@tar czf $(TARGET).tgz `find . -type f`

################################################################################
tmp/%.d: %.cpp
	@echo "Updating dependencies for $< ..."
	@mkdir -p $(dir $@)
	@echo 'tmp/$*.o $@ \c' > $@
	@$(COMPILER) -c $(CFLAGS) $(CPPFLAGS) $< -M >> $@

tmp/%.d: %.c
	@echo "Updating dependencies for $< ..."
	@mkdir -p $(dir $@)
	@echo 'tmp/$*.o $@ \c' > $@
	@$(COMPILER) -c $(CFLAGS) $< -M >> $@

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),dist)
sinclude $(CPPDEPENDS)
sinclude $(CDEPENDS)
endif
endif
