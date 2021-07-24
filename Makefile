
prfx ?= 
cxx    := $(prfx)g++
ar     := $(prfx)ar
ranlib := $(prfx)ranlib
strip  := $(prfx)strip

# only three macros
name := rtcThread
srcs := $(wildcard rtc_base/*.cc)
objs := $(patsubst %.cc,%.o,$(filter %.cc, $(srcs)))
deps := $(patsubst %.o,%.d,$(objs))
libs := -lpthread
cflags  := -I. -DNDEBUG -DWEBRTC_POSIX # -DWEBRTC_WIN
ldflags := 

lib$(name).so : $(objs)
	@$(cxx) -shared -Wl,--gc-sections -Wl,--as-needed -Wl,--export-dynamic $(ldflags) $^ -o $@ $(libs)
	@$(strip) --strip-all $@
	$(info $(cxx) -shared $(notdir $^) -o $(notdir $@))

lib$(name).a : $(objs)
	@$(ar) -crD $@ $^
	@$(ranlib) -D $@
	@$(strip) --strip-unneeded $@
	$(info $(ar) -crD $(notdir $@) $(notdir $^))

%.o : %.cc
	@$(cxx) -Os -Wall -Wextra -fPIC -std=c++11 -fpermissive $(cflags) -c $< -o $@ -MMD -MF $*.d -MP
	$(info $(cxx) -c $(notdir $<) -o $(notdir $@))

-include $(deps)
