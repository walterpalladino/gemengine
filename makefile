

ECHO_MESSAGE = "Mac OS X"

OBJDIR = obj
DISTDIR = dist
SRCDIR = src
LIBSDIR = libs
INCLUDESDIR = src

CXX = clang++ -v -Wc++11-extensions
CXXFLAGS = -I$(INCLUDESDIR) -I/Library/Frameworks/SDL2.framework/Headers -I/Library/Frameworks/SDL2_image.framework/Headers -I/Library/Frameworks/SDL2_mixer.framework/Headers  -I/Library/Frameworks/SDL2_ttf.framework/Headers -I../glad/include -F/Library/Frameworks

CC = clang++ -v
CFLAGS = $(CXXFLAGS)

APP_NAME = GemEngine
#SOURCES = $(SRCDIR)/main.cpp $(SRCDIR)/core/App.cpp $(SRCDIR)/utils/Log.cpp $(SRCDIR)/utils/StringUtils.cpp $(LIBSDIR)/glad/src/glad.c

#SOURCES += $(SRCDIR)/math/Math3d.cpp $(SRCDIR)/math/MathCommons.cpp $(SRCDIR)/math/Matrix3d.cpp $(SRCDIR)/math/Matrix4x4.cpp
#SOURCES += $(SRCDIR)/math/Plane.cpp $(SRCDIR)/math/Plane3d.cpp $(SRCDIR)/math/Point2dList.cpp 
#SOURCES += $(SRCDIR)/math/Ray3d.cpp $(SRCDIR)/math/Vector3d.cpp $(SRCDIR)/math/Vector4d.cpp

# Find all the C and C++ files we want to compile
# Note the single quotes around the * expressions. The shell will incorrectly expand these otherwise, but we want to send the * directly to the find command.
SOURCES := $(shell find $(SRCDIR) -name '*.cpp' -or -name '*.c')

#OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))

#OBJS = $(OBJDIR)/main.o $(OBJDIR)/App.o $(OBJDIR)/Log.o $(OBJDIR)/StringUtils.o $(OBJDIR)/glad.o

#OBJS += $(OBJDIR)/Math3d.o $(OBJDIR)/MathCommons.o $(OBJDIR)/Matrix3d.o $(OBJDIR)/Matrix4x4.o
#OBJS += $(OBJDIR)/Plane.o $(OBJDIR)/Plane3d.o $(OBJDIR)/Point2dList.o 
#OBJS += $(OBJDIR)/Ray3d.o $(OBJDIR)/Vector3d.o $(OBJDIR)/Vector4d.o
# Prepends BUILD_DIR and appends .o to every src file
# As an example, ./your_dir/hello.cpp turns into ./build/./your_dir/hello.cpp.o
OBJS := $(SOURCES:%=$(OBJDIR)/%.o)

LIBS = -F/Library/Frameworks -framework SDL2 -framework SDL2_image -framework SDL2_mixer -framework SDL2_ttf

$(info $$SOURCES is [${SOURCES}])
$(info $$OBJS is [${OBJS}])

##---------------------------------------------------------------------
## BUILD RULES
##---------------------------------------------------------------------

$(OBJDIR):
	mkdir -p $(OBJDIR)

#%.o:%.cpp
#	$(CXX) $(CXXFLAGS) -c -o $@ $<

#%.o:$(LIBSDIR)/glad/src/%.c
#	$(CC) $(CFLAGS) -c -o $@ $<

$(DISTDIR):
	mkdir -p $(DISTDIR)

#$(DISTDIR)/$(TARGET) := make

.PHONY: all
all: $(DISTDIR)/$(APP_NAME)
	@echo Build complete for $(ECHO_MESSAGE)

#$(TARGET): $(OBJS)
#	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

.PHONY: clean
clean:
#	rm -f $(OBJS) $(TARGET)
	yes | rm -rf $(OBJDIR)/* $(DISTDIR)/$(APP_NAME)

#$(OBJDIR)/StringUtils.o: $(SRCDIR)/utils/StringUtils.cpp $(INCLUDESDIR)/utils/StringUtils.h
#	$(CXX) $(CXXFLAGS) -c -o $@ $<
#$(OBJDIR)/Log.o: $(SRCDIR)/utils/Log.cpp $(INCLUDESDIR)/utils/Log.h $(INCLUDESDIR)/utils/StringUtils.h
#	$(CXX) $(CXXFLAGS) -c -o $@ $<
#$(OBJDIR)/main.o: $(SRCDIR)/main.cpp $(INCLUDESDIR)/core/App.h
#	$(CXX) $(CXXFLAGS) -c -o $@ $<
#$(OBJDIR)/App.o: $(SRCDIR)/core/App.cpp $(INCLUDESDIR)/core/App.h $(INCLUDESDIR)/utils/Log.h
#	$(CXX) $(CXXFLAGS) -c -o $@ $<

#$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
#	$(CXX) $(CXXFLAGS) -c -o $@ $<
#$(OBJDIR)/%.o: $(SRCDIR)/core/%.cpp
#	$(CXX) $(CXXFLAGS) -c -o $@ $<
#$(OBJDIR)/%.o: $(SRCDIR)/utils/%.cpp
#	$(CXX) $(CXXFLAGS) -c -o $@ $<
#$(OBJDIR)/%.o: $(SRCDIR)/math/%.cpp
#	$(CXX) $(CXXFLAGS) -c -o $@ $<
$(OBJDIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)/glad.o: $(LIBSDIR)/glad/src/glad.c
	$(CC) $(CFLAGS) -c -o $@ $<
	
$(DISTDIR)/$(APP_NAME): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

