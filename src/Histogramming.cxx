/******************************************************************************
HGC analysis code
Samuel Webb
Imperial College
***************************************************************************/

// Time-stamp: <2018-10-31 13:11:03 (snwebb)>

#include "HGCPlotting.h"

void HGCPlotting::MakeAllHistograms(){

  std::cout << "Creating All Histograms" << std::endl;


  
  
  _cloned_hists[ "Default" ] [ "tc_n" ] = new TH1D ( "default_tc_n", "", 100,0,1000 );  

  _cloned_hists[ "Default" ] [ "ex_sum" ] = new TH1D ( "default_ex_sum", "", 150,-150,150);
  _cloned_hists[ "Default" ] [ "ey_sum" ] = new TH1D ( "default_ey_sum", "", 150,-150,150);
  _cloned_hists[ "Default" ] [ "er_sum" ] = new TH1D ( "default_er_sum", "", 150,0,150);
  _cloned_hists[ "Default" ] [ "ephi_sum" ] = new TH1D ( "default_ephi_sum", "", 150,-M_PI,M_PI);
  





}


void HGCPlotting::CalculateVariables(  ){

  //Ex and Ey sums

  double exsum = 0;
  double eysum = 0;
  for (unsigned int i = 0; i < tc_pt->size(); i++){

    exsum += tc_pt->at(i)*std::cos(tc_phi->at(i));
    eysum += tc_pt->at(i)*std::sin(tc_phi->at(i));

  }

  double ersum = std::sqrt( exsum*exsum + eysum*eysum );
  double ephisum = std::atan2( eysum, exsum );

  _event_variables[  "ex_sum"  ] = exsum;
  _event_variables[  "ey_sum"  ] = eysum;
  _event_variables[  "er_sum"  ] = ersum;
  _event_variables[  "ephi_sum"  ] = ephisum;



}



void HGCPlotting::FillAllHists( std::string name ){

  CalculateVariables();
  
  _cloned_hists[ name ] [ "tc_n" ] ->Fill ( tc_n );
  _cloned_hists[ name ] [ "ex_sum" ] ->Fill (  _event_variables[  "ex_sum"  ] );
  _cloned_hists[ name ] [ "ey_sum" ] ->Fill (  _event_variables[  "ey_sum"  ] );
  _cloned_hists[ name ] [ "er_sum" ] ->Fill (  _event_variables[  "er_sum"  ] );
  _cloned_hists[ name ] [ "ephi_sum" ] ->Fill (  _event_variables[  "ephi_sum"  ] );


}
