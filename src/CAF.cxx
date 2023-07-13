#include "CAF.h"

// fixme: once DIRT-II is done with its work, this will be re-enabled
//#include "nusystematics/artless/response_helper.hh"

CAF::CAF( const std::string& filename, const std::string& rw_fhicl_filename )
  : rh(rw_fhicl_filename)
{
  cafFile = new TFile( filename.c_str(), "RECREATE" );
  cafSR = new TTree("cafTree", "cafTree");
  cafSRGlobal = new TTree("globalTree", "globalTree");
  cafMVA = new TTree("mvaTree", "mvaTree");
  cafPOT = new TTree( "meta", "meta" );
  genie = new TTree( "genieEvt", "genieEvt" );

  // initialize standard record bits
  cafSR->Branch("rec", "caf::StandardRecord", &sr);

  // initialize geometric efficiency throw results
  geoEffThrowResults = new std::vector< std::vector < std::vector < uint64_t > > >();
  cafMVA->Branch("geoEffThrowResults", &geoEffThrowResults);

  // initialize the GENIE record
  mcrec = nullptr;
  genie->Branch( "genie_record", &mcrec );

  cafPOT->Branch( "pot", &pot, "pot/D" );
  cafPOT->Branch( "run", &meta_run, "run/I" );
  cafPOT->Branch( "subrun", &meta_subrun, "subrun/I" );
  cafPOT->Branch( "version", &version, "version/I" );

  // fixme: the following is disabled until DIRT-II finishes on model + uncertainty decisions
//  // Get list of variations, and make CAF branch for each one
//  std::vector<unsigned int> parIds = rh.GetParameters();
//  for( unsigned int i = 0; i < parIds.size(); ++i ) {
//    systtools::SystParamHeader head = rh.GetHeader(parIds[i]);
//    printf( "Adding reweight branch %u for %s with %lu shifts\n", parIds[i], head.prettyName.c_str(), head.paramVariations.size() );
//
//    caf::SRSystParamHeader hdr;
//    hdr.nshifts = head.paramVariations.size();
//    hdr.name = head.prettyName;
//    hdr.id = head.systParamId; // TODO is this necessary?
//    srglobal.wgts.params.push_back(hdr);
//  }
  TBranch* br = cafSRGlobal->Branch("global", &srglobal);
  if(!br) abort();
  cafSRGlobal->Fill();
}

void CAF::fill()
{
  cafSR->Fill();
  cafMVA->Fill();
  genie->Fill();
}

void CAF::Print()
{
  // printf( "Event %d:\n", sr.event );
  // printf( "   Truth: Ev = %3.3f Elep = %3.3f Q2 = %3.3f W = %3.3f x = %3.3f y = %3.3f lepton %d mode %d\n", sr.Ev, sr.LepE, sr.Q2, sr.W, sr.X, sr.Y, sr.LepPDG, sr.mode );
  // printf( "    Reco: Ev = %3.3f Elep = %3.3f q %d mu/e/nc %d%d%d cont/trk/ecal/exit %d%d%d%d had veto %2.1f\n\n", sr.Ev_reco, sr.Elep_reco, sr.reco_q, sr.reco_numu, sr.reco_nue, sr.reco_nc, sr.muon_contained, sr.muon_tracker, sr.muon_ecal, sr.muon_exit, sr.Ehad_veto );
}

void CAF::fillPOT()
{
  printf( "Filling metadata\n" );
  cafPOT->Fill();
}

void CAF::write()
{
  cafFile->cd();
  cafSR->Write();
  cafSRGlobal->Write();
  cafMVA->Write();
  cafPOT->Write();
  genie->Write();
  cafFile->Close();
}


void CAF::setToBS()
{
  // use default constructors to reset
  sr = caf::StandardRecord();
  srglobal = caf::SRGlobal();
}
