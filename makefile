
# Mac OS
# install_name_tool -add_rpath /Library/Frameworks ./dist/GemEngine 


#install_name_tool -change @rpath/SDL2.framework/Versions/A/SDL2 @executable_path/../Frameworks/SDL2.framework/Versions/A/SDL2 ./dist/GemEngine.app/Contents/MacOS/GemEngine

#install_name_tool -change @rpath/SDL2_image.framework/Versions/A/SDL2_image @executable_path/../Frameworks/SDL2_image.framework/Versions/A/SDL2_image ./dist/GemEngine.app/Contents/MacOS/GemEngine

#install_name_tool -change @rpath/SDL2_mixer.framework/Versions/A/SDL2_mixer @executable_path/../Frameworks/SDL2_mixer.framework/Versions/A/SDL2_mixer ./dist/GemEngine.app/Contents/MacOS/GemEngine

#install_name_tool -change @rpath/SDL2_ttf.framework/Versions/A/SDL2_ttf @executable_path/../Frameworks/SDL2_ttf.framework/Versions/A/SDL2_ttf ./dist/GemEngine.app/Contents/MacOS/GemEngine


#@rpath/SDL2.framework/Versions/A/SDL2
#@rpath/SDL2_image.framework/Versions/A/SDL2_image
#@rpath/SDL2_mixer.framework/Versions/A/SDL2_mixer
#@rpath/SDL2_ttf.framework/Versions/A/SDL2_ttf



OSFLAG 				:=
ifeq ($(OS),Windows_NT)
	OSFLAG += -D WIN32
	ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
		OSFLAG += -D AMD64
	endif
	ifeq ($(PROCESSOR_ARCHITECTURE),x86)
		OSFLAG += -D IA32
	endif
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		OSFLAG += -D LINUX
	endif
	ifeq ($(UNAME_S),Darwin)
		OSFLAG += -D OSX
		LIBS = -F/Library/Frameworks -framework SDL2 -framework SDL2_image -framework SDL2_mixer -framework SDL2_ttf
	endif
		UNAME_P := $(shell uname -p)
	ifeq ($(UNAME_P),x86_64)
		OSFLAG += -D AMD64
	endif
		ifneq ($(filter %86,$(UNAME_P)),)
			OSFLAG += -D IA32
		endif
	ifneq ($(filter arm%,$(UNAME_P)),)
		OSFLAG += -D ARM
	endif
endif




OBJDIR = obj
BINDIR = bin
DISTDIR = dist
SRCDIR = src
LIBSDIR = libs
INCLUDESDIR = src

CXX = clang++ -v -std=c++17 -Wc++17-extensions $(OSFLAG)
CXXFLAGS = -I$(INCLUDESDIR) -I/Library/Frameworks/SDL2.framework/Headers -I/Library/Frameworks/SDL2_image.framework/Headers -I/Library/Frameworks/SDL2_mixer.framework/Headers  -I/Library/Frameworks/SDL2_ttf.framework/Headers -F/Library/Frameworks

CC = clang++ -v
CFLAGS = $(CXXFLAGS)

APP_NAME = GemEngine

# Find all the C and C++ files we want to compile
# Note the single quotes around the * expressions. The shell will incorrectly expand these otherwise, but we want to send the * directly to the find command.
SOURCES := $(shell find $(SRCDIR) -name '*.cpp' -or -name '*.c')
#SOURCES += $(shell find $(LIBSDIR) -name '*.cpp' -or -name '*.c')


# Prepends BUILD_DIR and appends .o to every src file
# As an example, ./your_dir/hello.cpp turns into ./build/./your_dir/hello.cpp.o
OBJS := $(SOURCES:%=$(OBJDIR)/%.o)

#LIBS = -F/Library/Frameworks -framework SDL2 -framework SDL2_image -framework SDL2_mixer -framework SDL2_ttf

$(info $$SOURCES is [${SOURCES}])
$(info $$OBJS is [${OBJS}])

##---------------------------------------------------------------------
## BUILD RULES
##---------------------------------------------------------------------

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

$(DISTDIR):
	mkdir -p $(DISTDIR)


.PHONY: all
all: $(BINDIR)/$(APP_NAME)
# @install_name_tool -add_rpath /Library/Frameworks $(DISTDIR)/$(APP_NAME) 
	@install_name_tool -add_rpath /Library/Frameworks $(BINDIR)/$(APP_NAME)
	@echo Build complete for $(OSFLAG)

# Generate Application Bundle
.PHONY: package
package:
	rm -Rf $(DISTDIR)/$(APP_NAME).app
	mkdir $(DISTDIR)/$(APP_NAME).app
	mkdir $(DISTDIR)/$(APP_NAME).app/Contents
	mkdir $(DISTDIR)/$(APP_NAME).app/Contents/Frameworks
	mkdir $(DISTDIR)/$(APP_NAME).app/Contents/Frameworks/SDL2.framework
	mkdir $(DISTDIR)/$(APP_NAME).app/Contents/Frameworks/SDL2_ttf.framework
	mkdir $(DISTDIR)/$(APP_NAME).app/Contents/Frameworks/SDL2_image.framework
	mkdir $(DISTDIR)/$(APP_NAME).app/Contents/Frameworks/SDL2_mixer.framework
	mkdir $(DISTDIR)/$(APP_NAME).app/Contents/MacOS
	mkdir $(DISTDIR)/$(APP_NAME).app/Contents/Resources
	mkdir $(DISTDIR)/$(APP_NAME).app/Contents/Resources/lib
	mkdir $(DISTDIR)/$(APP_NAME).app/Contents/Resources/examples

	cp -R /Library/Frameworks/SDL2.framework/* $(DISTDIR)/$(APP_NAME).app/Contents/Frameworks/SDL2.framework/
	cp -R /Library/Frameworks/SDL2_ttf.framework/* $(DISTDIR)/$(APP_NAME).app/Contents/Frameworks/SDL2_ttf.framework/
	cp -R /Library/Frameworks/SDL2_image.framework/* $(DISTDIR)/$(APP_NAME).app/Contents/Frameworks/SDL2_image.framework/
	cp -R /Library/Frameworks/SDL2_mixer.framework/* $(DISTDIR)/$(APP_NAME).app/Contents/Frameworks/SDL2_mixer.framework/
	
	cp $(BINDIR)/$(APP_NAME) $(DISTDIR)/$(APP_NAME).app/Contents/MacOS/

	install_name_tool -change @rpath/SDL2.framework/Versions/A/SDL2 @executable_path/../Frameworks/SDL2.framework/Versions/A/SDL2 $(DISTDIR)/$(APP_NAME).app/Contents/MacOS/GemEngine
	install_name_tool -change @rpath/SDL2_image.framework/Versions/A/SDL2_image @executable_path/../Frameworks/SDL2_image.framework/Versions/A/SDL2_image $(DISTDIR)/$(APP_NAME).app/Contents/MacOS/GemEngine
	install_name_tool -change @rpath/SDL2_mixer.framework/Versions/A/SDL2_mixer @executable_path/../Frameworks/SDL2_mixer.framework/Versions/A/SDL2_mixer $(DISTDIR)/$(APP_NAME).app/Contents/MacOS/GemEngine
	install_name_tool -change @rpath/SDL2_ttf.framework/Versions/A/SDL2_ttf @executable_path/../Frameworks/SDL2_ttf.framework/Versions/A/SDL2_ttf $(DISTDIR)/$(APP_NAME).app/Contents/MacOS/GemEngine


.PHONY: clean
clean:
#	rm -f $(OBJS) $(TARGET)
	yes | rm -rf $(OBJDIR)/* $(BINDIR)/$(APP_NAME) $(DISTDIR)/$(APP_NAME).app


$(OBJDIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<
	
$(BINDIR)/$(APP_NAME): $(OBJS)
	mkdir -p $(dir $@)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

