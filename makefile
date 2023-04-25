


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
DISTDIR = dist
SRCDIR = src
LIBSDIR = libs
INCLUDESDIR = src

CXX = clang++ -v -std=c++11 -Wc++11-extensions $(OSFLAG)
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

$(DISTDIR):
	mkdir -p $(DISTDIR)


.PHONY: all
all: $(DISTDIR)/$(APP_NAME)
	@echo Build complete for $(OSFLAG)


.PHONY: clean
clean:
#	rm -f $(OBJS) $(TARGET)
	yes | rm -rf $(OBJDIR)/* $(DISTDIR)/$(APP_NAME)


$(OBJDIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<
	
$(DISTDIR)/$(APP_NAME): $(OBJS)
	mkdir -p $(dir $@)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

