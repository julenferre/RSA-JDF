#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=None-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/ControlRobot.o \
	${OBJECTDIR}/src/Ejemplo.o \
	${OBJECTDIR}/src/IRobotConnection.o \
	${OBJECTDIR}/src/IRobotInstructionSet.o \
	${OBJECTDIR}/src/Instruction.o \
	${OBJECTDIR}/src/Laberinto.o \
	${OBJECTDIR}/src/Principal.o \
	${OBJECTDIR}/src/Serial.o \
	${OBJECTDIR}/src/Sigue_linea.o \
	${OBJECTDIR}/src/tinyxml/tinystr.o \
	${OBJECTDIR}/src/tinyxml/tinyxml.o \
	${OBJECTDIR}/src/tinyxml/tinyxmlerror.o \
	${OBJECTDIR}/src/tinyxml/tinyxmlparser.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/practica5

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/practica5: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/practica5 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/ControlRobot.o: src/ControlRobot.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/ControlRobot.o src/ControlRobot.cpp

${OBJECTDIR}/src/Ejemplo.o: src/Ejemplo.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Ejemplo.o src/Ejemplo.cpp

${OBJECTDIR}/src/IRobotConnection.o: src/IRobotConnection.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/IRobotConnection.o src/IRobotConnection.cpp

${OBJECTDIR}/src/IRobotInstructionSet.o: src/IRobotInstructionSet.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/IRobotInstructionSet.o src/IRobotInstructionSet.cpp

${OBJECTDIR}/src/Instruction.o: src/Instruction.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Instruction.o src/Instruction.cpp

${OBJECTDIR}/src/Laberinto.o: src/Laberinto.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Laberinto.o src/Laberinto.cpp

${OBJECTDIR}/src/Principal.o: src/Principal.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Principal.o src/Principal.cpp

${OBJECTDIR}/src/Serial.o: src/Serial.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Serial.o src/Serial.cpp

${OBJECTDIR}/src/Sigue_linea.o: src/Sigue_linea.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Sigue_linea.o src/Sigue_linea.cpp

${OBJECTDIR}/src/tinyxml/tinystr.o: src/tinyxml/tinystr.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/tinyxml
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/tinyxml/tinystr.o src/tinyxml/tinystr.cpp

${OBJECTDIR}/src/tinyxml/tinyxml.o: src/tinyxml/tinyxml.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/tinyxml
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/tinyxml/tinyxml.o src/tinyxml/tinyxml.cpp

${OBJECTDIR}/src/tinyxml/tinyxmlerror.o: src/tinyxml/tinyxmlerror.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/tinyxml
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/tinyxml/tinyxmlerror.o src/tinyxml/tinyxmlerror.cpp

${OBJECTDIR}/src/tinyxml/tinyxmlparser.o: src/tinyxml/tinyxmlparser.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/tinyxml
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/tinyxml/tinyxmlparser.o src/tinyxml/tinyxmlparser.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/practica5

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
