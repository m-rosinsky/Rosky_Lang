# SlickEdit generated file.  Do not edit this file except in designated areas.

# Make command to use for dependencies
MAKE=make
RM=rm
MKDIR=mkdir

# -----Begin user-editable area-----

# -----End user-editable area-----

# If no configuration is specified, "Debug" will be used
ifndef CFG
CFG=Debug
endif

#
# Configuration: Debug
#
ifeq "$(CFG)" "Debug"
OUTDIR=Debug
OUTFILE=$(OUTDIR)/rosky.exe
CFG_INC=
CFG_LIB=
CFG_OBJ=
COMMON_OBJ=$(OUTDIR)/evaluator.o $(OUTDIR)/function_handler.o \
	$(OUTDIR)/lexer.o $(OUTDIR)/main.o $(OUTDIR)/native_functions.o \
	$(OUTDIR)/native_member_functions.o $(OUTDIR)/parse_expr.o \
	$(OUTDIR)/parse_for.o $(OUTDIR)/parse_func.o \
	$(OUTDIR)/parse_func_def.o $(OUTDIR)/parse_group.o \
	$(OUTDIR)/parse_if.o $(OUTDIR)/parse_while.o $(OUTDIR)/parser.o \
	$(OUTDIR)/parser_utils.o $(OUTDIR)/rosky_bool.o \
	$(OUTDIR)/rosky_float.o $(OUTDIR)/rosky_group.o \
	$(OUTDIR)/rosky_int.o $(OUTDIR)/rosky_null.o \
	$(OUTDIR)/rosky_pointer.o $(OUTDIR)/rosky_string.o \
	$(OUTDIR)/variable_handler.o
OBJ=$(COMMON_OBJ) $(CFG_OBJ)
ALL_OBJ=$(OUTDIR)/evaluator.o $(OUTDIR)/function_handler.o \
	$(OUTDIR)/lexer.o $(OUTDIR)/main.o $(OUTDIR)/native_functions.o \
	$(OUTDIR)/native_member_functions.o $(OUTDIR)/parse_expr.o \
	$(OUTDIR)/parse_for.o $(OUTDIR)/parse_func.o \
	$(OUTDIR)/parse_func_def.o $(OUTDIR)/parse_group.o \
	$(OUTDIR)/parse_if.o $(OUTDIR)/parse_while.o $(OUTDIR)/parser.o \
	$(OUTDIR)/parser_utils.o $(OUTDIR)/rosky_bool.o \
	$(OUTDIR)/rosky_float.o $(OUTDIR)/rosky_group.o \
	$(OUTDIR)/rosky_int.o $(OUTDIR)/rosky_null.o \
	$(OUTDIR)/rosky_pointer.o $(OUTDIR)/rosky_string.o \
	$(OUTDIR)/variable_handler.o

COMPILE=g++ -c -std=c++17   -g -o "$(OUTDIR)/$(*F).o" $(CFG_INC) "$<"
LINK=g++ -std=c++17 -g -o "$(OUTFILE)" $(OBJ) $(CFG_LIB)
COMPILE_ADA=gnat -g -c -o "$(OUTDIR)/$(*F).o" "$<"
COMPILE_ADB=gnat -g -c -o "$(OUTDIR)/$(*F).o" "$<"
COMPILE_F=gfortran -c -g -o "$(OUTDIR)/$(*F).o" "$<"
COMPILE_F90=gfortran -c -g -o "$(OUTDIR)/$(*F).o" "$<"
COMPILE_D=gdc -c -g -o "$(OUTDIR)/$(*F).o" "$<"

# Pattern rules
$(OUTDIR)/%.o : src/objects/%.cpp
	$(COMPILE)

$(OUTDIR)/%.o : %.cpp
	$(COMPILE)

$(OUTDIR)/%.o : src/%.cpp
	$(COMPILE)

$(OUTDIR)/%.o : src/functions/%.cpp
	$(COMPILE)

$(OUTDIR)/%.o : src/parser/%.cpp
	$(COMPILE)

$(OUTDIR)/%.o : src/utils/%.cpp
	$(COMPILE)

$(OUTDIR)/%.o : src/objects/%.ada
	$(COMPILE_ADA)

$(OUTDIR)/%.o : %.ada
	$(COMPILE_ADA)

$(OUTDIR)/%.o : src/%.ada
	$(COMPILE_ADA)

$(OUTDIR)/%.o : src/functions/%.ada
	$(COMPILE_ADA)

$(OUTDIR)/%.o : src/parser/%.ada
	$(COMPILE_ADA)

$(OUTDIR)/%.o : src/utils/%.ada
	$(COMPILE_ADA)

$(OUTDIR)/%.o : src/objects/%.d
	$(COMPILE_D)

$(OUTDIR)/%.o : %.d
	$(COMPILE_D)

$(OUTDIR)/%.o : src/%.d
	$(COMPILE_D)

$(OUTDIR)/%.o : src/functions/%.d
	$(COMPILE_D)

$(OUTDIR)/%.o : src/parser/%.d
	$(COMPILE_D)

$(OUTDIR)/%.o : src/utils/%.d
	$(COMPILE_D)

$(OUTDIR)/%.o : src/objects/%.adb
	$(COMPILE_ADB)

$(OUTDIR)/%.o : %.adb
	$(COMPILE_ADB)

$(OUTDIR)/%.o : src/%.adb
	$(COMPILE_ADB)

$(OUTDIR)/%.o : src/functions/%.adb
	$(COMPILE_ADB)

$(OUTDIR)/%.o : src/parser/%.adb
	$(COMPILE_ADB)

$(OUTDIR)/%.o : src/utils/%.adb
	$(COMPILE_ADB)

$(OUTDIR)/%.o : src/objects/%.f90
	$(COMPILE_F90)

$(OUTDIR)/%.o : %.f90
	$(COMPILE_F90)

$(OUTDIR)/%.o : src/%.f90
	$(COMPILE_F90)

$(OUTDIR)/%.o : src/functions/%.f90
	$(COMPILE_F90)

$(OUTDIR)/%.o : src/parser/%.f90
	$(COMPILE_F90)

$(OUTDIR)/%.o : src/utils/%.f90
	$(COMPILE_F90)

$(OUTDIR)/%.o : src/objects/%.f
	$(COMPILE_F)

$(OUTDIR)/%.o : %.f
	$(COMPILE_F)

$(OUTDIR)/%.o : src/%.f
	$(COMPILE_F)

$(OUTDIR)/%.o : src/functions/%.f
	$(COMPILE_F)

$(OUTDIR)/%.o : src/parser/%.f
	$(COMPILE_F)

$(OUTDIR)/%.o : src/utils/%.f
	$(COMPILE_F)

# Build rules
all: $(OUTFILE)

$(OUTFILE): $(OUTDIR)  $(OBJ)
	$(LINK)

$(OUTDIR):
	$(MKDIR) -p "$(OUTDIR)"

# Rebuild this project
rebuild: cleanall all

# Clean this project
clean:
	$(RM) -f $(OUTFILE)
	$(RM) -f $(OBJ)

# Clean this project and all dependencies
cleanall: clean
endif

#
# Configuration: Release
#
ifeq "$(CFG)" "Release"
OUTDIR=Release
OUTFILE=$(OUTDIR)/rosky.exe
CFG_INC=
CFG_LIB=
CFG_OBJ=
COMMON_OBJ=$(OUTDIR)/evaluator.o $(OUTDIR)/function_handler.o \
	$(OUTDIR)/lexer.o $(OUTDIR)/main.o $(OUTDIR)/native_functions.o \
	$(OUTDIR)/native_member_functions.o $(OUTDIR)/parse_expr.o \
	$(OUTDIR)/parse_for.o $(OUTDIR)/parse_func.o \
	$(OUTDIR)/parse_func_def.o $(OUTDIR)/parse_group.o \
	$(OUTDIR)/parse_if.o $(OUTDIR)/parse_while.o $(OUTDIR)/parser.o \
	$(OUTDIR)/parser_utils.o $(OUTDIR)/rosky_bool.o \
	$(OUTDIR)/rosky_float.o $(OUTDIR)/rosky_group.o \
	$(OUTDIR)/rosky_int.o $(OUTDIR)/rosky_null.o \
	$(OUTDIR)/rosky_pointer.o $(OUTDIR)/rosky_string.o 
OBJ=$(COMMON_OBJ) $(CFG_OBJ)
ALL_OBJ=$(OUTDIR)/evaluator.o $(OUTDIR)/function_handler.o \
	$(OUTDIR)/lexer.o $(OUTDIR)/main.o $(OUTDIR)/native_functions.o \
	$(OUTDIR)/native_member_functions.o $(OUTDIR)/parse_expr.o \
	$(OUTDIR)/parse_for.o $(OUTDIR)/parse_func.o \
	$(OUTDIR)/parse_func_def.o $(OUTDIR)/parse_group.o \
	$(OUTDIR)/parse_if.o $(OUTDIR)/parse_while.o $(OUTDIR)/parser.o \
	$(OUTDIR)/parser_utils.o $(OUTDIR)/rosky_bool.o \
	$(OUTDIR)/rosky_float.o $(OUTDIR)/rosky_group.o \
	$(OUTDIR)/rosky_int.o $(OUTDIR)/rosky_null.o \
	$(OUTDIR)/rosky_pointer.o $(OUTDIR)/rosky_string.o 

COMPILE=g++ -c -std=c++17  -o "$(OUTDIR)/$(*F).o" $(CFG_INC) "$<"
LINK=g++ -std=c++17 -o "$(OUTFILE)" $(OBJ) $(CFG_LIB)
COMPILE_ADA=gnat -O -c -o "$(OUTDIR)/$(*F).o" "$<"
COMPILE_ADB=gnat -O -c -o "$(OUTDIR)/$(*F).o" "$<"
COMPILE_F=gfortran -O -g -o "$(OUTDIR)/$(*F).o" "$<"
COMPILE_F90=gfortran -O -g -o "$(OUTDIR)/$(*F).o" "$<"
COMPILE_D=gdc -c -g -o "$(OUTDIR)/$(*F).o" "$<"

# Pattern rules
$(OUTDIR)/%.o : src/objects/%.cpp
	$(COMPILE)

$(OUTDIR)/%.o : %.cpp
	$(COMPILE)

$(OUTDIR)/%.o : src/%.cpp
	$(COMPILE)

$(OUTDIR)/%.o : src/functions/%.cpp
	$(COMPILE)

$(OUTDIR)/%.o : src/parser/%.cpp
	$(COMPILE)

$(OUTDIR)/%.o : src/utils/%.cpp
	$(COMPILE)

$(OUTDIR)/%.o : src/objects/%.ada
	$(COMPILE_ADA)

$(OUTDIR)/%.o : %.ada
	$(COMPILE_ADA)

$(OUTDIR)/%.o : src/%.ada
	$(COMPILE_ADA)

$(OUTDIR)/%.o : src/functions/%.ada
	$(COMPILE_ADA)

$(OUTDIR)/%.o : src/parser/%.ada
	$(COMPILE_ADA)

$(OUTDIR)/%.o : src/utils/%.ada
	$(COMPILE_ADA)

$(OUTDIR)/%.o : src/objects/%.d
	$(COMPILE_D)

$(OUTDIR)/%.o : %.d
	$(COMPILE_D)

$(OUTDIR)/%.o : src/%.d
	$(COMPILE_D)

$(OUTDIR)/%.o : src/functions/%.d
	$(COMPILE_D)

$(OUTDIR)/%.o : src/parser/%.d
	$(COMPILE_D)

$(OUTDIR)/%.o : src/utils/%.d
	$(COMPILE_D)

$(OUTDIR)/%.o : src/objects/%.adb
	$(COMPILE_ADB)

$(OUTDIR)/%.o : %.adb
	$(COMPILE_ADB)

$(OUTDIR)/%.o : src/%.adb
	$(COMPILE_ADB)

$(OUTDIR)/%.o : src/functions/%.adb
	$(COMPILE_ADB)

$(OUTDIR)/%.o : src/parser/%.adb
	$(COMPILE_ADB)

$(OUTDIR)/%.o : src/utils/%.adb
	$(COMPILE_ADB)

$(OUTDIR)/%.o : src/objects/%.f90
	$(COMPILE_F90)

$(OUTDIR)/%.o : %.f90
	$(COMPILE_F90)

$(OUTDIR)/%.o : src/%.f90
	$(COMPILE_F90)

$(OUTDIR)/%.o : src/functions/%.f90
	$(COMPILE_F90)

$(OUTDIR)/%.o : src/parser/%.f90
	$(COMPILE_F90)

$(OUTDIR)/%.o : src/utils/%.f90
	$(COMPILE_F90)

$(OUTDIR)/%.o : src/objects/%.f
	$(COMPILE_F)

$(OUTDIR)/%.o : %.f
	$(COMPILE_F)

$(OUTDIR)/%.o : src/%.f
	$(COMPILE_F)

$(OUTDIR)/%.o : src/functions/%.f
	$(COMPILE_F)

$(OUTDIR)/%.o : src/parser/%.f
	$(COMPILE_F)

$(OUTDIR)/%.o : src/utils/%.f
	$(COMPILE_F)

# Build rules
all: $(OUTFILE)

$(OUTFILE): $(OUTDIR)  $(OBJ)
	$(LINK)

$(OUTDIR):
	$(MKDIR) -p "$(OUTDIR)"

# Rebuild this project
rebuild: cleanall all

# Clean this project
clean:
	$(RM) -f $(OUTFILE)
	$(RM) -f $(OBJ)

# Clean this project and all dependencies
cleanall: clean
endif
