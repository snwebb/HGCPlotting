#ifndef FillHistograms_cxx
#define FillHistograms_cxx

//bool debug = false;

#include "HGCPlotting.h"

int main ( int argc, char ** argv ) {

  CmdLine cmd( argc, argv ) ;

  HGCPlotting * hgcPlotting = new HGCPlotting ( &cmd );

  hgcPlotting->DoNothing();


  hgcPlotting->SetupFillHistograms();


  hgcPlotting->Fill();


  hgcPlotting->Save();

  delete hgcPlotting;



}

#endif
