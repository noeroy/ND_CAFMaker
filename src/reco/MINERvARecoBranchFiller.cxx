#include "MINERvARecoBranchFiller.h"

namespace cafmaker
{
  MINERvARecoBranchFiller::MINERvARecoBranchFiller(const std::string &minervaRecoFilename)
  {
    fMnvRecoFile = new TFile(minervaRecoFilename.c_str(), "READ");
    if (!fMnvRecoFile->IsZombie()) {
      SetConfigured(true);
      // Save pointer to input tree
      MnvRecoTree = dynamic_cast<TTree*>(fMnvRecoFile->Get("minerva"));
      if (!MnvRecoTree) {
        std::cerr << "Did not find MINERvA reco tree in input file " << minervaRecoFilename << std::endl;
        std::cerr << "Are you sure it exists?" << std::endl;

        throw;
      }
      MnvRecoTree->SetBranchAddress("n_tracks", &n_tracks);
      MnvRecoTree->SetBranchAddress("trk_index", trk_index);
      MnvRecoTree->SetBranchAddress("trk_type", trk_type);
      MnvRecoTree->SetBranchAddress("trk_patrec", trk_patrec);
      MnvRecoTree->SetBranchAddress("trk_time_slice", trk_time_slice);
      MnvRecoTree->SetBranchAddress("trk_vis_energy", trk_vis_energy);
      MnvRecoTree->SetBranchAddress("trk_theta", trk_theta);
      MnvRecoTree->SetBranchAddress("trk_phi", trk_phi);
      MnvRecoTree->SetBranchAddress("trk_hits", trk_hits);
      MnvRecoTree->SetBranchAddress("trk_dof", trk_dof);
      MnvRecoTree->SetBranchAddress("trk_chi2perDof", trk_chi2perDof);
      MnvRecoTree->SetBranchAddress("trk_fitMass", trk_fitMass);
      MnvRecoTree->SetBranchAddress("trk_nodes", trk_nodes);
      MnvRecoTree->SetBranchAddress("trk_node_X", trk_node_X);
      MnvRecoTree->SetBranchAddress("trk_node_Y", trk_node_Y);
      MnvRecoTree->SetBranchAddress("trk_node_Z", trk_node_Z);
      MnvRecoTree->SetBranchAddress("trk_node_aX", trk_node_aX);
      MnvRecoTree->SetBranchAddress("trk_node_aY", trk_node_aY);
      MnvRecoTree->SetBranchAddress("trk_node_qOverP", trk_node_qOverP);
      MnvRecoTree->SetBranchAddress("trk_node_chi2", trk_node_chi2);
    } else {
      fMnvRecoFile = NULL;
      MnvRecoTree = NULL;
      std::cerr << "Did not find input MINERvA reco file you provided: " << minervaRecoFilename << std::endl;
      std::cerr << "Are you sure it exists?" << std::endl;
      throw;
    }
  }

  // ---------------------------------------------------------------------------

  // here we copy all the MINERvA reco into the SRMINERvA branch of the StandardRecord object.
  void MINERvARecoBranchFiller::_FillRecoBranches(std::size_t evtIdx,
                                              caf::StandardRecord &sr,
                                              const cafmaker::Params &par) const
  {
    // Get nth entry from tree
    MnvRecoTree->GetEntry(evtIdx);

    

    std::map<int,std::vector<caf::SRTrack>> track_map;

    std::cout<<"NOE "<<evtIdx<<std::endl;

    // Fill in the track info 
    for (int i = 0; i < n_tracks; ++i) {

      int my_slice = trk_time_slice[i];
      caf::SRTrack my_track;

      // Save first and last hit in track
      // MINERvA Reco info is saved in mm whereas CAFs use CM as default -> do conversion here
      my_track.start = caf::SRVector3D(trk_node_X[i][0]/10.,trk_node_Y[i][0]/10., trk_node_Z[i][0]/10.);
      my_track.end   = caf::SRVector3D(trk_node_X[i][n_tracks-1]/10.,trk_node_Y[i][n_tracks-1]/10., trk_node_Z[i][n_tracks-1]/10.);

      // Track info
      my_track.len_cm  = sqrt(pow(trk_node_X[i][n_tracks-1] - trk_node_X[i][0],2)+pow(trk_node_Y[i][n_tracks-1] - trk_node_Y[i][0],2)+pow(trk_node_Z[i][n_tracks-1] - trk_node_Z[i][0],2))/10.;
      my_track.qual      = trk_chi2perDof[i];
      my_track.E         = trk_vis_energy[i];

      // Get the directions
      my_track.dir     = caf::SRVector3D(sin(trk_theta[i])*cos(trk_phi[i]),sin(trk_theta[i])*sin(trk_phi[i]),cos(trk_theta[i]));
      my_track.enddir  = caf::SRVector3D(sin(trk_theta[i])*cos(trk_phi[i]),sin(trk_theta[i])*sin(trk_phi[i]),cos(trk_theta[i]));

      //Fill the track map
      track_map[my_slice].push_back(my_track);
    }

    for (auto & slice : track_map) {
      caf::SRMINERvAInt my_int;
      
      // First set number of tracks
      my_int.ntracks = slice.second.size();

      for (std::size_t i_track = 0; i_track<slice.second.size(); i_track++){
        my_int.tracks.push_back(std::move(slice.second[i_track]));
      }
      sr.nd.minerva.ixn.push_back(my_int);
      sr.nd.minerva.nixn +=1;
      
      
    }

  }
} // end namespace
