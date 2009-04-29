#include "rose.h"
#include "RoseSrc_CallGraphAnalysis.h"

#include "CallGraphAnalysis.h"

using namespace std;

void
SB_CallGraph::createCallGraph(SgProject* project) {


  const char* callFileNameGML = "callgraph.gml";
  const char* callFileNameDOT = "callgraph.dot";
  bool mergedEdges = false;

  RoseBin_Def::RoseAssemblyLanguage = RoseBin_Def::x86;
  SgBinaryFile* binaryFile = isSgBinaryFile(project->get_fileList()[0]);
  SgAsmFile* file = binaryFile != NULL ? binaryFile->get_binaryFile() : NULL;
  if (file) {
    // binary analysis
    const SgAsmInterpretationPtrList& interps = file->get_interpretations();
    ROSE_ASSERT (interps.size() == 1);
    SgAsmInterpretation* interp = interps[0];
    SgAsmBlock* global_block = interp->get_global_block();
    ROSE_ASSERT (global_block != NULL);
    VirtualBinCFG::AuxiliaryInformation* info= new VirtualBinCFG::AuxiliaryInformation(project);
    RoseBin_DotGraph* dotGraph = new RoseBin_DotGraph(info);
    RoseBin_GMLGraph* gmlGraph = new RoseBin_GMLGraph(info);
    cout << " creating call graph ... " << endl;
    bin_callanalysis = new RoseBin_CallGraphAnalysis(global_block, new RoseObj(), info);
    // Building a GML file for the call graph
    bin_callanalysis->run(gmlGraph, callFileNameGML, !mergedEdges);
    // Building a DOT file for the call graph
    bin_callanalysis->run(dotGraph, callFileNameDOT, !mergedEdges);

  } else {
    // source code
    //VirtualCFG::AuxiliaryInformation* info= new VirtualCFG::AuxiliaryInformation(project);
#if 0
    RoseBin_DotGraph* dotGraph = new RoseBin_DotGraph(info);
    RoseBin_GMLGraph* gmlGraph = new RoseBin_GMLGraph(info);
    cout << " creating call graph ... " << endl;
    RoseBin_CallGraphAnalysis* callanalysis = new RoseBin_CallGraphAnalysis(global_block, new RoseObj(), info);
    // Building a GML file for the call graph
    callanalysis->run(gmlGraph, callFileNameGML, !mergedEdges);
    // Building a DOT file for the call graph
    callanalysis->run(dotGraph, callFileNameDOT);


#endif
  }

}
