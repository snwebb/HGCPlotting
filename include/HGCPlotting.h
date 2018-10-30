/********************************************************************************
HCG plotting code
Samuel Webb
Imperial College
********************************************************************************/

#ifndef _HGCPlotting_h_
#define _HGCPlotting_h_
#define XXX std::cout << "I am here: " << __LINE__ << std::endl << std::endl;

#include "BuildTreeBase.h"
#include "tdrstyle.h"
#include "CmdLine.h"
#include <cstring>
#include <time.h>
#include <TLorentzVector.h>
#include <TMultiGraph.h>
#include <TMatrixD.h>
#include <TH1.h>
#include <TH2.h>
#include <TF1.h>
#include <TFitResult.h>
#include <TRandom3.h>
#include <THStack.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TEllipse.h>
#include <TProfile.h>
#include <TGraphErrors.h>
#include <TLine.h>
#include <TKey.h>
#include <TLatex.h>
#include <sys/stat.h>
#include <iomanip>

class HGCPlotting : public BuildTreeBase {
 private :
  
  /***** General *****/
  CmdLine * _cmd ;
  std::string _in_directory;
  std::string _out_directory;
  TDirectory * _origDir ;
  


  TChain * _chain    ;  


 public :
  HGCPlotting( CmdLine * cmd );
  ~HGCPlotting();
  
  void DoNothing();

  void SetupFillHistograms();

  void Loop();

  void Fill();

  bool FileExists( std::string file );

  void Save();


  
};


#endif
