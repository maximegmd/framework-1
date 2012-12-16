CXX           = /usr/lib/gcc-snapshot/bin/g++
#CXX           = g++
#CXX           = clang++
CXX_COMPILE   = $(CXX) -c $(CXX_CFLAGS)
CXX_LINK	  = $(CXX) $(CXX_LDFLAGS)
#CXX_CFLAGS	  = -std=c++11 -stdlib=libc++ -pedantic -Wall -Wextra -Werror -I./
#CXX_LDFLAGS   = -std=c++11 -stdlib=libc++ -lUnitTest++
CXX_CFLAGS	  = -std=c++11 -pedantic -Wall -Wextra -Werror -I./
CXX_LDFLAGS   = -std=c++11 -lUnitTest++

UNAME := $(shell uname -o)

EXECUTABLE = test
EXECUTABLE_LITTLE = test_little
EXECUTABLE_BIG = test_big

SOURCES = tests/test.cpp \
          tests/serializable/base_types.cpp \
          tests/serializable/containers/value.cpp \
          tests/serializable/containers/optional_field.cpp \
          tests/serializable/mutators/fixed_container.cpp \
          tests/serializable/mutators/variable_container.cpp \
          tests/serializable/mutators/terminated.cpp \
          tests/serializable/mutators/tuple_container.cpp \
          tests/serializable/mutators/stl.cpp \
          tests/serializable/interfaces/comparable.cpp

SOURCES_LITTLE = tests/test.cpp \
                 tests/serializable/mutators/little_endian_1.cpp \
                 tests/serializable/mutators/big_endian_2.cpp

SOURCES_BIG = tests/test.cpp \
              tests/serializable/mutators/little_endian_2.cpp \
              tests/serializable/mutators/big_endian_1.cpp

OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS_LITTLE = $(SOURCES_LITTLE:.cpp=.o)
OBJECTS_BIG = $(SOURCES_BIG:.cpp=.o)

GCNO = $(SOURCES:.cpp=.gcno)
GCNO_LITTLE = $(SOURCES_LITTLE:.cpp=.gcno)
GCNO_BIG = $(SOURCES_BIG:.cpp=.gcno)

GCDA = $(SOURCES:.cpp=.gcda)
GCDA_LITTLE = $(SOURCES_LITTLE:.cpp=.gcda)
GCDA_BIG = $(SOURCES_BIG:.cpp=.gcda)

all: normal little big

normal: CXX_CFLAGS += -O2
normal: CXX_LDFLAGS += -O2
normal: $(SOURCES) $(EXECUTABLE)

little: CXX_CFLAGS += -O2 -DFRAMEWORK_HOST_ENDIANESS=FRAMEWORK_LITTLE_ENDIAN
little: CXX_LDFLAGS += -O2
little: $(SOURCES_LITTLE) $(EXECUTABLE_LITTLE)

big: CXX_CFLAGS += -O2 -DFRAMEWORK_HOST_ENDIANESS=FRAMEWORK_BIG_ENDIAN
big: CXX_LDFLAGS += -O2
big: $(SOURCES_BIG) $(EXECUTABLE_BIG)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) $(CXX_LDFLAGS) -o $@
	@echo "Running unit tests..."
	@./$@

$(EXECUTABLE_LITTLE): $(OBJECTS_LITTLE)
	$(CXX) $(OBJECTS_LITTLE) $(CXX_LDFLAGS) -o $@
	@echo "Running little endian unit tests..."
	@./$@

$(EXECUTABLE_BIG): $(OBJECTS_BIG)
	$(CXX) $(OBJECTS_BIG) $(CXX_LDFLAGS) -o $@
	@echo "Running big endian unit tests..."
	@./$@

.cpp.o:
	$(CXX) $(CXX_CFLAGS) -c $< -o $@

clean: 
	rm -f src/test.o \
 $(EXECUTABLE) $(EXECUTABLE_LITTLE) $(EXECUTABLE_BIG) \
 $(OBJECTS) $(OBJECTS_LITTLE) $(OBJECTS_BIG) \
 $(GCNO) $(GCNO_LITTLE) $(GCNO_BIG) \
 $(GCDA) $(GCDA_LITTLE) $(GCDA_BIG)
