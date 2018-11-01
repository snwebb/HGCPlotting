/******************************************************************************
HGC analysis code
Samuel Webb
Imperial College
***************************************************************************/

// Time-stamp: <2018-11-01 15:09:20 (snwebb)>

#include "HGCPlotting.h"

void HGCPlotting::MakeAllHistograms( std::vector<std::string> &HistoSets){

  std::cout << "Creating All Histograms" << std::endl;
  
  for (auto& names : HistoSets ){
    LoadHistoTemplates ( names );
  }
  
}

void HGCPlotting::LoadHistoTemplates( std::string name ){

  if ( name == "TriggerCells" ){

    _cloned_hists[ name ] [ "tc_eta" ] = new TH1D ( (name + "_tc_eta").c_str(), "", 100,-5,5 );  
    _cloned_hists[ name ] [ "tc_phi" ] = new TH1D ( (name + "_tc_phi").c_str(), "", 100,-M_PI,M_PI );  

  }

  if ( name == "PU0_General" ){

    _cloned_hists[ name ] [ "tc_n" ] = new TH1D ( (name + "_tc_n").c_str(), "", 100,0,1000 );  

  }

  if ( name == "PU200" ){

    _cloned_hists[ name ] [ "tc_n" ] = new TH1D ( "default_tc_n", "", 100,0,100000 );  
    _cloned_hists[ name ] [ "ex_sum" ] = new TH1D ( "default_ex_sum", "", 150,-150,150);
    _cloned_hists[ name ] [ "ey_sum" ] = new TH1D ( "default_ey_sum", "", 150,-150,150);
    _cloned_hists[ name ] [ "er_sum" ] = new TH1D ( "default_er_sum", "", 150,0,150);
    _cloned_hists[ name ] [ "ephi_sum" ] = new TH1D ( "default_ephi_sum", "", 150,-M_PI,M_PI);
  
  }

  if ( name == "PU0_forward" || name == "PU0_backward" ){

    _cloned_hists[ name ] [ "tc_n" ] = new TH1D ( (name + "_tc_n").c_str(), "", 100,0,1000 );  
    _cloned_hists[ name ] [ "ex_sum" ] = new TH1D ( (name + "_ex_sum").c_str(), "", 150,-50,50);
    _cloned_hists[ name ] [ "ey_sum" ] = new TH1D ( (name + "_ey_sum").c_str(), "", 150,-50,50);
    _cloned_hists[ name ] [ "er_sum" ] = new TH1D ( (name + "_er_sum").c_str(), "", 150,0,2);
    _cloned_hists[ name ] [ "ephi_sum" ] = new TH1D ( (name + "_ephi_sum").c_str(), "", 150,-M_PI,M_PI);
    _cloned_hists[ name ] [ "dphi_met" ] = new TH1D ( (name + "_dphi_met").c_str(), "", 150,-0.05,0.05);
  
  }




}


void HGCPlotting::CalculateTriggerCellVariables(  ){

  //Ex and Ey sums

  double exsum_forward = 0;
  double eysum_forward = 0;
  double exsum_backward = 0;
  double eysum_backward = 0;
  for (unsigned int i = 0; i < tc_pt->size(); i++){
    if  ( tc_eta->at(i)>0){
      exsum_forward += tc_pt->at(i)*std::cos(tc_phi->at(i));
      eysum_forward += tc_pt->at(i)*std::sin(tc_phi->at(i));
    }
    else{
      exsum_backward += tc_pt->at(i)*std::cos(tc_phi->at(i));
      eysum_backward += tc_pt->at(i)*std::sin(tc_phi->at(i));
    }
  }

  double ersum_forward = std::sqrt( exsum_forward*exsum_forward + eysum_forward*eysum_forward );

  double ersum_backward = std::sqrt( exsum_backward*exsum_backward + eysum_backward*eysum_backward );
  double ephisum_forward = std::atan2( eysum_forward, exsum_forward );
  double ephisum_backward = std::atan2( eysum_backward, exsum_backward );

  _event_variables[  "ex_sum_forward"  ] = exsum_forward;
  _event_variables[  "ey_sum_forward"  ] = eysum_forward;
  _event_variables[  "er_sum_forward"  ] = ersum_forward;
  _event_variables[  "ephi_sum_forward"  ] = ephisum_forward;

  _event_variables[  "ex_sum_backward"  ] = exsum_backward;
  _event_variables[  "ey_sum_backward"  ] = eysum_backward;
  _event_variables[  "er_sum_backward"  ] = ersum_backward;
  _event_variables[  "ephi_sum_backward"  ] = ephisum_backward;

  //Difference betwen photon truth phi and MET

  
  TVector2 met, truth;
  met.Set( exsum_forward, eysum_forward );
  truth.SetMagPhi( 1, gen_phi->at(0) );
  double dphi_met = met.DeltaPhi( truth );
  _event_variables[  "dphi_met_forward"  ] =  dphi_met;
  met.Set( exsum_backward, eysum_backward );
  truth.SetMagPhi( 1, gen_phi->at(1) );
  dphi_met = met.DeltaPhi( truth );
  _event_variables[  "dphi_met_backward"  ] =  dphi_met;

}



void HGCPlotting::FillAllHists( std::string name ){

  CalculateTriggerCellVariables();
  
  //  if ( name == "PU0" ||  name == "PU200" ){

  if ( name == "TriggerCells" ){

    for (unsigned int i = 0; i < tc_eta->size(); i++){
      _cloned_hists[ name ] [ "tc_eta" ] ->Fill ( tc_eta->at(i) );
      _cloned_hists[ name ] [ "tc_phi" ] ->Fill ( tc_phi->at(i) );
    }

  }


  if ( name == "PU0_General" ){

    _cloned_hists[ name ] [ "tc_n" ] ->Fill ( tc_n );

  }

  if ( name == "PU0_forward" ){



    _cloned_hists[ name ] [ "ex_sum" ] ->Fill (  _event_variables[  "ex_sum_forward"  ] );
    _cloned_hists[ name ] [ "ey_sum" ] ->Fill (  _event_variables[  "ey_sum_forward"  ] );
    _cloned_hists[ name ] [ "er_sum" ] ->Fill (  _event_variables[  "er_sum_forward"  ] );
    _cloned_hists[ name ] [ "ephi_sum" ] ->Fill (  _event_variables[  "ephi_sum_forward"  ] );        
    _cloned_hists[ name ] [ "dphi_met" ] ->Fill (  _event_variables[  "dphi_met_forward"  ] );    
           
  }

  if ( name == "PU0_backward" ){

    _cloned_hists[ name ] [ "tc_n" ] ->Fill ( tc_n );

    _cloned_hists[ name ] [ "ex_sum" ] ->Fill (  _event_variables[  "ex_sum_backward"  ] );
    _cloned_hists[ name ] [ "ey_sum" ] ->Fill (  _event_variables[  "ey_sum_backward"  ] );
    _cloned_hists[ name ] [ "er_sum" ] ->Fill (  _event_variables[  "er_sum_backward"  ] );
    _cloned_hists[ name ] [ "ephi_sum" ] ->Fill (  _event_variables[  "ephi_sum_backward"  ] );   
    _cloned_hists[ name ] [ "dphi_met" ] ->Fill (  _event_variables[  "dphi_met_backward"  ] );                
  }

}
