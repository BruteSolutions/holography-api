# GNU Make project makefile autogenerated by Premake
ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifndef CC
  CC = gcc
endif

ifndef CXX
  CXX = g++
endif

ifndef AR
  AR = ar
endif
# ifndef LIBXMLCFLAGS
# LIBXMLCFLAGS = $(shell pkg-config libxml++-2.6 --cflags)
# endif
#ifndef LIBXMLLIBS
# LIBXMLLIBS = $(shell pkg-config libxml++-2.6 --libs)
#endif
# put in CFLAGS $(LIBXMLCFLAGS) 
# put in LIBS $(LIBXMLLIBS) -lGL 
ifeq ($(config),debug)
  OBJDIR     = obj/Debug
  TARGETDIR  = .
  TARGET     = $(TARGETDIR)/test-demo
  DEFINES   += -D_CRT_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_DEPRECATE -D_SCL_SECURE_NO_WARNINGS -DTIXML_USE_STL -DFREEGLUT_STATIC -DLOAD_X11 -D_LIB -DFREEGLUT_LIB_PRAGMAS=0 -DDEBUG -D_DEBUG
  INCLUDES  += -I../framework -I../glsdk/glload/include -I../glsdk/glimg/include -I../glsdk/glm -I../glsdk/glutil/include -I../glsdk/glmesh/include -I../glsdk/freeglut/include -Iinclude
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES) -std=c++0x
  CFLAGS    += $(CPPFLAGS) $(ARCH) $(LIBXMLCFLAGS) -g
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -L../glsdk/glload/lib -L../glsdk/glimg/lib -L../glsdk/glutil/lib -L../glsdk/glmesh/lib -L../glsdk/freeglut/lib -L../framework/lib
  LIBS      += -lframeworkD -lglloadD -lglimgD -lglutilD -lglmeshD -lfreeglutD -lGLU $(LIBXMLLIBS)
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += ../framework/lib/libframeworkD.a
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(ARCH) $(LIBS)
  SRCPATH		 = src
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

OBJECTS := \
	$(OBJDIR)/test-demo.o $(OBJDIR)/Projector.o $(OBJDIR)/GraphicalObject.o $(OBJDIR)/ColorTranslator.o $(OBJDIR)/Scene.o $(OBJDIR)/ThreeDSpace.o $(OBJDIR)/Display.o $(OBJDIR)/Shader.o $(OBJDIR)/Monitor.o $(OBJDIR)/Configuration.o $(OBJDIR)/UniversalConfiguration.o $(OBJDIR)/TestFramework.o $(OBJDIR)/TestShader.o $(OBJDIR)/TestColorTranslator.o $(OBJDIR)/TestConfiguration.o\

# $(OBJDIR)/FileLoader.o $(OBJDIR)/X3DLoader.o 

RESOURCES := \

SHELLTYPE := msdos
ifeq (,$(ComSpec)$(COMSPEC))
  SHELLTYPE := posix
endif
ifeq (/bin,$(findstring /bin,$(SHELL)))
  SHELLTYPE := posix
endif

.PHONY: clean prebuild prelink

all: $(TARGETDIR) $(OBJDIR) prebuild prelink $(TARGET)
	@:

$(TARGET): $(GCH) $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking test-demo
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)

$(TARGETDIR):
	@echo Creating $(TARGETDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(TARGETDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(TARGETDIR))
endif

$(OBJDIR):
	@echo Creating $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(OBJDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(OBJDIR))
endif

clean:
	@echo Cleaning test-demo
ifeq (posix,$(SHELLTYPE))
	$(SILENT) rm -f  $(TARGET)
	$(SILENT) rm -rf $(OBJDIR)
else
	$(SILENT) if exist $(subst /,\\,$(TARGET)) del $(subst /,\\,$(TARGET))
	$(SILENT) if exist $(subst /,\\,$(OBJDIR)) rmdir /s /q $(subst /,\\,$(OBJDIR))
endif

prebuild:
	$(PREBUILDCMDS)

prelink:
	$(PRELINKCMDS)

ifneq (,$(PCH))
$(GCH): $(PCH)
	@echo $(notdir $<)
	-$(SILENT) cp $< $(OBJDIR)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
endif

$(OBJDIR)/test-demo.o: $(SRCPATH)/test-demo.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Projector.o: $(SRCPATH)/Projector.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/GraphicalObject.o: $(SRCPATH)/GraphicalObject.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ColorTranslator.o: $(SRCPATH)/ColorTranslator.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Scene.o: $(SRCPATH)/Scene.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) $ -o "$@" -c "$<"

$(OBJDIR)/ThreeDSpace.o: $(SRCPATH)/ThreeDSpace.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Shader.o: $(SRCPATH)/Shader.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Configuration.o: $(SRCPATH)/Configuration.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/UniversalConfiguration.o: $(SRCPATH)/UniversalConfiguration.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"


$(OBJDIR)/mytextreader.o: $(SRCPATH)/mytextreader.h
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) $(LIBXMLPP) -o "$@" -c "$<"

$(OBJDIR)/Monitor.o: $(SRCPATH)/Monitor.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Display.o: $(SRCPATH)/Display.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
	 

$(OBJDIR)/X3DLoader.o: $(SRCPATH)/X3DLoader.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS)-o "$@" -c "$<"

$(OBJDIR)/FileLoader.o: $(SRCPATH)/FileLoader.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"


$(OBJDIR)/TestFramework.o: $(SRCPATH)/TestFramework.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/TestShader.o: $(SRCPATH)/TestShader.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/TestColorTranslator.o: $(SRCPATH)/TestColorTranslator.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/TestConfiguration.o: $(SRCPATH)/TestConfiguration.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
