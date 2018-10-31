/******************************************************************************
HGC analysis code
Samuel Webb
Imperial College
***************************************************************************/

// Time-stamp: <2018-10-31 11:09:36 (snwebb)>

#include "HGCPlotting.h"

void HGCPlotting::MakeAllHistograms(){

  std::cout << "Creating All Histograms" << std::endl;


  
  
  _cloned_hists[ "Default" ] [ "tc_n" ] = new TH1D ( "default_tc_n", "", 100,0,1000 );  

  _cloned_hists[ "Default" ] [ "ex_sum" ] = new TH1D ( "default_ex_sum", "", 100,-0.02,0.02);
  _cloned_hists[ "Default" ] [ "ey_sum" ] = new TH1D ( "default_ey_sum", "", 100,-0.02,0.02);
  





}


void HGCPlotting::CalculateVariables(  ){

  //Ex and Ey sums

  double exsum = 0;
  double eysum = 0;
  for (unsigned int i = 0; i < tc_pt->size(); i++){

    exsum += tc_pt->at(i)*std::cos(tc_phi->at(i));
    eysum += tc_pt->at(i)*std::sin(tc_phi->at(i));

  }
  //  std::cout << exsum << std::endl;
  exsum/=double(tc_pt->size());
  eysum/=double(tc_pt->size());
  _event_variables[  "ex_sum"  ] = exsum;
  _event_variables[  "ey_sum"  ] = eysum;



}



void HGCPlotting::FillAllHists( std::string name ){

  CalculateVariables();
  
  _cloned_hists[ name ] [ "tc_n" ] ->Fill ( tc_n );
  _cloned_hists[ name ] [ "ex_sum" ] ->Fill (  _event_variables[  "ex_sum"  ] );
  _cloned_hists[ name ] [ "ey_sum" ] ->Fill (  _event_variables[  "ey_sum"  ] );


}
