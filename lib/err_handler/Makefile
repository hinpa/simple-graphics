CC=clang


# Dependencies flags for .h files (to make make recompile the project when .h was changed)
DEPFLAGS=-MP -MD
LFLAGS=-lstdc++ -lm -lglfw
EFLAGS=-Wall -Wextra -std=c++20
CFLAGS=-fPIC $(EFLAGS) $(DEPFLAGS) 
CODEDIRS=. $(LIBS) $(foreach D,$(LIBS), $(wildcard $(D)/*))
CFILES=$(foreach D,$(CODEDIRS),$(wildcard $(D)/*.cpp))
OBJECTS=$(patsubst %.cpp,%.o,$(CFILES))
DEPFILES=$(patsubst %.cpp,%.d,$(CFILES))
STATIC_OBJ=../../complib/liberrh.a

all:$(STATIC_OBJ)

$(STATIC_OBJ):$(OBJECTS)
	ar cr $(STATIC_OBJ) $(OBJECTS)

%.o:%.cpp Makefile
	$(CC) -c $(CFLAGS) $< -o $@

-include $(DEPFILES)

#%.o:%.cpp Makefile
#	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS) $(STATIC_OBJ) $(DEPFILES)

