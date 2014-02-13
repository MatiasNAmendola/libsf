##
## Auto Generated makefile, please do not edit
##
ProjectName:=Debi

## Debug
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/rick/.codelite/Debi"
ProjectPath            := "/home/rick/.codelite/Debi/Debi"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=rick
Date                   :=02/01/2010
CodeLitePath           :="/home/rick/.codelite"
LinkerName             :=g++
ArchiveTool            :=ar rcus
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
CompilerName           :=g++
C_CompilerName         :=g++
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=
CmpOptions             := -g $(Preprocessors)
LinkOptions            :=  
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)." 
RcIncludePath          :=
Libs                   :=
LibPath                := "$(LibraryPathSwitch)." 


Objects=$(IntermediateDirectory)/main$(ObjectSuffix) $(IntermediateDirectory)/disasm$(ObjectSuffix) 

##
## Main Build Targets 
##
all: $(OutputFile)

$(OutputFile): makeDirStep $(Objects)
	@mkdir -p $(@D)
	$(LinkerName) $(OutputSwitch)$(OutputFile) $(Objects) $(LibPath) $(Libs) $(LinkOptions)

makeDirStep:
	@test -d ./Debug || mkdir -p ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main$(DependSuffix)
	@test -d ./Debug || mkdir -p ./Debug
	$(CompilerName) $(SourceSwitch) "/home/rick/.codelite/Debi/Debi/main.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main$(DependSuffix): main.cpp
	@test -d ./Debug || mkdir -p ./Debug
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/main$(ObjectSuffix) -MF$(IntermediateDirectory)/main$(DependSuffix) -MM "/home/rick/.codelite/Debi/Debi/main.cpp"

$(IntermediateDirectory)/disasm$(ObjectSuffix): disasm.cpp $(IntermediateDirectory)/disasm$(DependSuffix)
	@test -d ./Debug || mkdir -p ./Debug
	$(CompilerName) $(SourceSwitch) "/home/rick/.codelite/Debi/Debi/disasm.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/disasm$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/disasm$(DependSuffix): disasm.cpp
	@test -d ./Debug || mkdir -p ./Debug
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/disasm$(ObjectSuffix) -MF$(IntermediateDirectory)/disasm$(DependSuffix) -MM "/home/rick/.codelite/Debi/Debi/disasm.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/disasm$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/disasm$(DependSuffix)
	$(RM) $(IntermediateDirectory)/disasm$(PreprocessSuffix)
	$(RM) $(OutputFile)


