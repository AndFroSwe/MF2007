function runtlccmd
% RUNTLCCMD - run tlc command (regenerate C code from .rtw file) for model motor_io_position_GABRIEL
% This function will run the tlc command stored in the variable 
% "tlccmd" in tlccmd.mat, whose contents is as follows:
% 
% 	tlc
% 	-r
% 	C:\Users\adamlang\Documents\MF2007\WorkshopA\dSpace+Matlab\motor_io_position_GABRIEL_rti1104\motor_io_position_GABRIEL.rtw
% 	C:\Program Files (x86)\dSPACE RCPHIL 2014-B\MATLAB\RTI\RTI1104\TLC\rti1104.tlc
% 	-OC:\Users\adamlang\Documents\MF2007\WorkshopA\dSpace+Matlab\motor_io_position_GABRIEL_rti1104
% 	-IC:\Program Files (x86)\dSPACE RCPHIL 2014-B\MATLAB\RTI\RTI1104\TLC
% 	-IC:\Program Files (x86)\dSPACE RCPHIL 2014-B\MATLAB\RTI\RTI\TLC
% 	-IC:\Users\adamlang\Documents\MF2007\WorkshopA\dSpace+Matlab\motor_io_position_GABRIEL_rti1104\tlc
% 	-IC:\Program Files (x86)\MATLAB\R2014b\rtw\c\tlc\mw
% 	-IC:\Program Files (x86)\MATLAB\R2014b\rtw\c\tlc\lib
% 	-IC:\Program Files (x86)\MATLAB\R2014b\rtw\c\tlc\blocks
% 	-IC:\Program Files (x86)\MATLAB\R2014b\rtw\c\tlc\fixpt
% 	-IC:\Program Files (x86)\MATLAB\R2014b\stateflow\c\tlc
% 	-aFoldNonRolledExpr=1
% 	-aInlineInvariantSignals=0
% 	-aInlineParameters=2
% 	-aLocalBlockOutputs=0
% 	-aRollThreshold=5
% 	-aForceBlockIOInitOptimize=0
% 	-aGenerateReport=0
% 	-aGenCodeOnly=0
% 	-aRTWVerbose=1
% 	-aIncludeHyperlinkInReport=0
% 	-aLaunchReport=0
% 	-aGenerateTraceInfo=0
% 	-aForceParamTrailComments=0
% 	-aGenerateComments=1
% 	-aIgnoreCustomStorageClasses=1
% 	-aIncHierarchyInIds=0
% 	-aMaxRTWIdLen=31
% 	-aShowEliminatedStatements=0
% 	-aIncDataTypeInIds=0
% 	-aInsertBlockDesc=0
% 	-aIgnoreTestpoints=0
% 	-aSimulinkBlockComments=1
% 	-aInlinedPrmAccess="Literals"
% 	-aTargetFcnLib="ansi_tfl_tmw.mat"
% 	-aLogVarNameModifier="rt_"
% 	-aGenerateFullHeader=1
% 	-aExtMode=0
% 	-aExtModeStaticAlloc=0
% 	-aExtModeTesting=0
% 	-aExtModeStaticAllocSize=1000000
% 	-aExtModeTransport=0
% 	-aRTWCAPISignals=0
% 	-aRTWCAPIParams=0
% 	-aGenerateASAP2=0
% 	-aMatFileLogging=0
% 	-aInitialSimState="RUN"
% 	-aExecutionMode="real-time"
% 	-aExecutionModeNonUI="RTSIM"
% 	-aTimeScaleFactor="1.0"
% 	-aTimeScaleFactorNonUI="OPTION_DISABLED"
% 	-aAssertionMode="OFF"
% 	-aCCompilerCommonOpts=""
% 	-aCCompilerOptimizationOptsPopup_="Default"
% 	-aCCompilerOptimizationOpts=""
% 	-aCCompilerOptimizationOptsNonUI="USE_DEFAULT"
% 	-aAllowReservedHostServiceNums=0
% 	-aRTICfgSetVer=450
% 	-aLoadAfterBuild=0
% 	-aLoadToFlash=0
% 	-aLoadApplNonUI="OFF"
% 	-aBoardName="ds1104"
% 	-aBoardNameNonUI="ds1104"
% 	-aNetworkClientNonUI="OPTION_DISABLED"
% 	-aTRCOnlyGlobals=0
% 	-aTRCGenerateLabels=1
% 	-aTRCGenerateVirtualBlocks=1
% 	-aTRCGenerateStates=0
% 	-aTRCGenerateDerivatives=0
% 	-aTRCGenerateParamValues=0
% 	-aTRCIsOmitVdOn=0
% 	-aGenerateTraceInfo=0
% 	-aIgnoreTestpoints=0
% 	-aProtectedModelReferenceTarget=0
% 	-p10000

   disp('This function will be obsoleted in a future release.') 
   mdl = 'motor_io_position_GABRIEL';

   sysopen = ~isempty(strmatch(mdl, find_system('type', 'block_diagram'), 'exact'));

   if ~sysopen

      disp([mfilename ': Error: model ' mdl ' is not open. Please open model ' mdl ' and then run ' mfilename ' again.']);

   else

      rtwprivate('rtwattic', 'setBuildDir', 'C:\Users\adamlang\Documents\MF2007\WorkshopA\dSpace+Matlab\motor_io_position_GABRIEL_rti1104');
      rtwprivate('ec_set_replacement_flag', 'motor_io_position_GABRIEL');
      set_param('motor_io_position_GABRIEL', 'RTWGenSharedUtilitiesWithoutAssert', 0);
      load tlccmd.mat;
      savedpwd = pwd;
      cd ..;
      coder.internal.ModelCodegenMgr.setInstance(modelCodegenMgr);
      tlccmd{end+1} = '-aSLCGUseRTWContext=0';
      feval(tlccmd{:});
      coder.internal.ModelCodegenMgr.setInstance([]);
      
      rtwprivate rtwattic clean;
      set_param('motor_io_position_GABRIEL', 'RTWGenSharedUtilitiesWithoutAssert', -1);
      cd(savedpwd);

   end
