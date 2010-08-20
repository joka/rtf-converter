# Microsoft Developer Studio Generated NMAKE File, Based on rtf.dsp
!IF "$(CFG)" == ""
CFG=rtf - Win32 Debug
!MESSAGE No configuration specified. Defaulting to rtf - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "rtf - Win32 Release" && "$(CFG)" != "rtf - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "rtf.mak" CFG="rtf - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "rtf - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "rtf - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "rtf - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\rtf.exe"


CLEAN :
	-@erase "$(INTDIR)\BodyDestination.obj"
	-@erase "$(INTDIR)\charoutput.obj"
	-@erase "$(INTDIR)\charsource.obj"
	-@erase "$(INTDIR)\Destination.obj"
	-@erase "$(INTDIR)\FileCharSource.obj"
	-@erase "$(INTDIR)\GraphicState.obj"
	-@erase "$(INTDIR)\IgnoreDestination.obj"
	-@erase "$(INTDIR)\InfoDestination.obj"
	-@erase "$(INTDIR)\rtfparser.obj"
	-@erase "$(INTDIR)\rtftohtml.obj"
	-@erase "$(INTDIR)\stylemap.obj"
	-@erase "$(INTDIR)\StyleSheetDestination.obj"
	-@erase "$(INTDIR)\Tag.obj"
	-@erase "$(INTDIR)\Token.obj"
	-@erase "$(INTDIR)\Tokeniser.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\rtf.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\rtf.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\rtf.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\rtf.pdb" /machine:I386 /out:"$(OUTDIR)\rtf.exe" 
LINK32_OBJS= \
	"$(INTDIR)\charoutput.obj" \
	"$(INTDIR)\charsource.obj" \
	"$(INTDIR)\Destination.obj" \
	"$(INTDIR)\FileCharSource.obj" \
	"$(INTDIR)\GraphicState.obj" \
	"$(INTDIR)\IgnoreDestination.obj" \
	"$(INTDIR)\InfoDestination.obj" \
	"$(INTDIR)\rtfparser.obj" \
	"$(INTDIR)\rtftohtml.obj" \
	"$(INTDIR)\stylemap.obj" \
	"$(INTDIR)\StyleSheetDestination.obj" \
	"$(INTDIR)\Tag.obj" \
	"$(INTDIR)\Token.obj" \
	"$(INTDIR)\Tokeniser.obj" \
	"$(INTDIR)\BodyDestination.obj"

"$(OUTDIR)\rtf.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "rtf - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\rtf.exe" "$(OUTDIR)\rtf.bsc"


CLEAN :
	-@erase "$(INTDIR)\BodyDestination.obj"
	-@erase "$(INTDIR)\BodyDestination.sbr"
	-@erase "$(INTDIR)\charoutput.obj"
	-@erase "$(INTDIR)\charoutput.sbr"
	-@erase "$(INTDIR)\charsource.obj"
	-@erase "$(INTDIR)\charsource.sbr"
	-@erase "$(INTDIR)\Destination.obj"
	-@erase "$(INTDIR)\Destination.sbr"
	-@erase "$(INTDIR)\FileCharSource.obj"
	-@erase "$(INTDIR)\FileCharSource.sbr"
	-@erase "$(INTDIR)\GraphicState.obj"
	-@erase "$(INTDIR)\GraphicState.sbr"
	-@erase "$(INTDIR)\IgnoreDestination.obj"
	-@erase "$(INTDIR)\IgnoreDestination.sbr"
	-@erase "$(INTDIR)\InfoDestination.obj"
	-@erase "$(INTDIR)\InfoDestination.sbr"
	-@erase "$(INTDIR)\rtfparser.obj"
	-@erase "$(INTDIR)\rtfparser.sbr"
	-@erase "$(INTDIR)\rtftohtml.obj"
	-@erase "$(INTDIR)\rtftohtml.sbr"
	-@erase "$(INTDIR)\stylemap.obj"
	-@erase "$(INTDIR)\stylemap.sbr"
	-@erase "$(INTDIR)\StyleSheetDestination.obj"
	-@erase "$(INTDIR)\StyleSheetDestination.sbr"
	-@erase "$(INTDIR)\Tag.obj"
	-@erase "$(INTDIR)\Tag.sbr"
	-@erase "$(INTDIR)\Token.obj"
	-@erase "$(INTDIR)\Token.sbr"
	-@erase "$(INTDIR)\Tokeniser.obj"
	-@erase "$(INTDIR)\Tokeniser.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\rtf.bsc"
	-@erase "$(OUTDIR)\rtf.exe"
	-@erase "$(OUTDIR)\rtf.ilk"
	-@erase "$(OUTDIR)\rtf.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\rtf.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\rtf.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\charoutput.sbr" \
	"$(INTDIR)\charsource.sbr" \
	"$(INTDIR)\Destination.sbr" \
	"$(INTDIR)\FileCharSource.sbr" \
	"$(INTDIR)\GraphicState.sbr" \
	"$(INTDIR)\IgnoreDestination.sbr" \
	"$(INTDIR)\InfoDestination.sbr" \
	"$(INTDIR)\rtfparser.sbr" \
	"$(INTDIR)\rtftohtml.sbr" \
	"$(INTDIR)\stylemap.sbr" \
	"$(INTDIR)\StyleSheetDestination.sbr" \
	"$(INTDIR)\Tag.sbr" \
	"$(INTDIR)\Token.sbr" \
	"$(INTDIR)\Tokeniser.sbr" \
	"$(INTDIR)\BodyDestination.sbr"

"$(OUTDIR)\rtf.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\rtf.pdb" /debug /machine:I386 /out:"$(OUTDIR)\rtf.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\charoutput.obj" \
	"$(INTDIR)\charsource.obj" \
	"$(INTDIR)\Destination.obj" \
	"$(INTDIR)\FileCharSource.obj" \
	"$(INTDIR)\GraphicState.obj" \
	"$(INTDIR)\IgnoreDestination.obj" \
	"$(INTDIR)\InfoDestination.obj" \
	"$(INTDIR)\rtfparser.obj" \
	"$(INTDIR)\rtftohtml.obj" \
	"$(INTDIR)\stylemap.obj" \
	"$(INTDIR)\StyleSheetDestination.obj" \
	"$(INTDIR)\Tag.obj" \
	"$(INTDIR)\Token.obj" \
	"$(INTDIR)\Tokeniser.obj" \
	"$(INTDIR)\BodyDestination.obj"

"$(OUTDIR)\rtf.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("rtf.dep")
!INCLUDE "rtf.dep"
!ELSE 
!MESSAGE Warning: cannot find "rtf.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "rtf - Win32 Release" || "$(CFG)" == "rtf - Win32 Debug"
SOURCE=.\bodydestination.cpp

!IF  "$(CFG)" == "rtf - Win32 Release"


"$(INTDIR)\BodyDestination.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "rtf - Win32 Debug"


"$(INTDIR)\BodyDestination.obj"	"$(INTDIR)\BodyDestination.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\charoutput.cpp

!IF  "$(CFG)" == "rtf - Win32 Release"


"$(INTDIR)\charoutput.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "rtf - Win32 Debug"


"$(INTDIR)\charoutput.obj"	"$(INTDIR)\charoutput.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\charsource.cpp

!IF  "$(CFG)" == "rtf - Win32 Release"


"$(INTDIR)\charsource.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "rtf - Win32 Debug"


"$(INTDIR)\charsource.obj"	"$(INTDIR)\charsource.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\destination.cpp

!IF  "$(CFG)" == "rtf - Win32 Release"


"$(INTDIR)\Destination.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "rtf - Win32 Debug"


"$(INTDIR)\Destination.obj"	"$(INTDIR)\Destination.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\filecharsource.cpp

!IF  "$(CFG)" == "rtf - Win32 Release"


"$(INTDIR)\FileCharSource.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "rtf - Win32 Debug"


"$(INTDIR)\FileCharSource.obj"	"$(INTDIR)\FileCharSource.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\graphicstate.cpp

!IF  "$(CFG)" == "rtf - Win32 Release"


"$(INTDIR)\GraphicState.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "rtf - Win32 Debug"


"$(INTDIR)\GraphicState.obj"	"$(INTDIR)\GraphicState.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\ignoredestination.cpp

!IF  "$(CFG)" == "rtf - Win32 Release"


"$(INTDIR)\IgnoreDestination.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "rtf - Win32 Debug"


"$(INTDIR)\IgnoreDestination.obj"	"$(INTDIR)\IgnoreDestination.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\infodestination.cpp

!IF  "$(CFG)" == "rtf - Win32 Release"


"$(INTDIR)\InfoDestination.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "rtf - Win32 Debug"


"$(INTDIR)\InfoDestination.obj"	"$(INTDIR)\InfoDestination.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\rtfparser.cpp

!IF  "$(CFG)" == "rtf - Win32 Release"


"$(INTDIR)\rtfparser.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "rtf - Win32 Debug"


"$(INTDIR)\rtfparser.obj"	"$(INTDIR)\rtfparser.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\rtftohtml.cpp

!IF  "$(CFG)" == "rtf - Win32 Release"


"$(INTDIR)\rtftohtml.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "rtf - Win32 Debug"


"$(INTDIR)\rtftohtml.obj"	"$(INTDIR)\rtftohtml.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\stylemap.cpp

!IF  "$(CFG)" == "rtf - Win32 Release"


"$(INTDIR)\stylemap.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "rtf - Win32 Debug"


"$(INTDIR)\stylemap.obj"	"$(INTDIR)\stylemap.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\stylesheetdestination.cpp

!IF  "$(CFG)" == "rtf - Win32 Release"


"$(INTDIR)\StyleSheetDestination.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "rtf - Win32 Debug"


"$(INTDIR)\StyleSheetDestination.obj"	"$(INTDIR)\StyleSheetDestination.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\tag.cpp

!IF  "$(CFG)" == "rtf - Win32 Release"


"$(INTDIR)\Tag.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "rtf - Win32 Debug"


"$(INTDIR)\Tag.obj"	"$(INTDIR)\Tag.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\token.cpp

!IF  "$(CFG)" == "rtf - Win32 Release"


"$(INTDIR)\Token.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "rtf - Win32 Debug"


"$(INTDIR)\Token.obj"	"$(INTDIR)\Token.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\tokeniser.cpp

!IF  "$(CFG)" == "rtf - Win32 Release"


"$(INTDIR)\Tokeniser.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "rtf - Win32 Debug"


"$(INTDIR)\Tokeniser.obj"	"$(INTDIR)\Tokeniser.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 


!ENDIF 

