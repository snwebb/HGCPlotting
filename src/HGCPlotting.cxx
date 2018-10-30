/******************************************************************************
HGC analysis code
Samuel Webb
Imperial College
***************************************************************************/

// Time-stamp: <2018-10-30 13:01:08 (snwebb)>

#include "HGCPlotting.h"

HGCPlotting::HGCPlotting( CmdLine * cmd ){

  _cmd = cmd;
  _origDir = gDirectory ;
  _in_directory = _cmd->string_val( "--in_directory" ) ;
  _out_directory = _cmd->string_val( "--out_directory" ) ;

}


HGCPlotting::~HGCPlotting() {

  gDirectory = _origDir ;

  // for(auto &it1 : _cloned_stacks) {
  //   for(auto &it2 : it1.second) {
  //     it2.second->Delete();
  //   }
  // }

}

void HGCPlotting::DoNothing(){

 
}


void HGCPlotting::SetupFillHistograms(){


  _chain   = new TChain ( "hgcalTriggerNtuplizer/HGCalTriggerNtuple"   );


  for ( int i = 1; i < 10; i++ ){
    if (FileExists( (_in_directory + "/ntuples/ntuple_" + std::to_string(i) + ".root"   ).c_str()  )  )   
      _chain  ->Add ( (_in_directory + "/ntuples/ntuple_" + std::to_string(i) + ".root"   ).c_str() );
  }
 
}


void HGCPlotting::Fill(){

  Init(  _chain );
  Loop( );

}


void HGCPlotting::Loop( ){

  //Loop over events

  std::cout << "Beginning Event Loop" << std::endl;

  if (fChain == 0) return;

  std::cout << "Getting Number of Entries" << std::endl;

  Long64_t nentries = fChain->GetEntries();
  Long64_t nbytes = 0, nb = 0;

  for (Long64_t jentry=0; jentry<nentries;jentry++) {

    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    if ( jentry % 10000 == 0 ) {
      std::cout << jentry << "/" << nentries  << "\n" ;
    }


    std::cout << event << std::endl;


  }


}

bool HGCPlotting::FileExists( std::string file ){

  struct stat buf;
  if (  stat (  ( file ).c_str(), &buf ) == 0)
    return true;
  else{
    return false;
  }
}

void HGCPlotting::Save(){

 
 
}


//////////


