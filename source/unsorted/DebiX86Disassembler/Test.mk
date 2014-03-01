##
## Auto Generated makefile, please do not edit
##
ProjectName:=Test

## Release
ConfigurationName      :=Release
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/rick/.codelite/Debi"
ProjectPath            := "/home/rick/.codelite/Debi"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=rick
Date                   :=01/24/2010
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
CmpOptions             :=  $(Preprocessors)
LinkOptions            :=  -O2
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)." 
RcIncludePath          :=
Libs                   :=
LibPath                := "$(LibraryPathSwitch)." 


Objects=$(IntermediateDirectory)/test_asm$(ObjectSuffix) 

##
## Main Build Targets 
##
all: $(OutputFile)

$(OutputFile): makeDirStep $(Objects)
	@mkdir -p $(@D)
	$(LinkerName) $(OutputSwitch)$(OutputFile) $(Objects) $(LibPath) $(Libs) $(LinkOptions)

makeDirStep:
	@test -d ./Release || mkdir -p ./Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/test_asm$(ObjectSuffix): test_asm.cpp $(IntermediateDirectory)/test_asm$(DependSuffix)
	@test -d ./Release || mkdir -p ./Release
	$(CompilerName) $(SourceSwitch) "/home/rick/.codelite/Debi/test_asm.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/test_asm$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/test_asm$(DependSuffix): test_asm.cpp
	@test -d ./Release || mkdir -p ./Release
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/test_asm$(ObjectSuffix) -MF$(IntermediateDirectory)/test_asm$(DependSuffix) -MM "/home/rick/.codelite/Debi/test_asm.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/test_asm$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/test_asm$(DependSuffix)
	$(RM) $(IntermediateDirectory)/test_asm$(PreprocessSuffix)
	$(RM) $(OutputFile)


