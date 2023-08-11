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
      //tracks branches 
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

      //Shower branches
      MnvRecoTree->SetBranchAddress("n_blobs_id", &n_blobs_id);
      MnvRecoTree->SetBranchAddress("blob_id_idx", blob_id_idx);
      MnvRecoTree->SetBranchAddress("blob_id_subdet", blob_id_subdet);
      MnvRecoTree->SetBranchAddress("blob_id_history", blob_id_history);
      MnvRecoTree->SetBranchAddress("blob_id_size", blob_id_size);
      MnvRecoTree->SetBranchAddress("blob_id_patrec", blob_id_patrec);
      MnvRecoTree->SetBranchAddress("blob_id_e", blob_id_e);
      MnvRecoTree->SetBranchAddress("blob_id_time", blob_id_time);
      MnvRecoTree->SetBranchAddress("blob_id_time_slice", blob_id_time_slice);
      MnvRecoTree->SetBranchAddress("blob_id_startpoint_x", blob_id_startpoint_x);
      MnvRecoTree->SetBranchAddress("blob_id_startpoint_y", blob_id_startpoint_y);
      MnvRecoTree->SetBranchAddress("blob_id_startpoint_z", blob_id_startpoint_z);
      MnvRecoTree->SetBranchAddress("blob_id_clus_idx", blob_id_clus_idx);


      //Truth branches
      MnvRecoTree->SetBranchAddress("mc_traj_trkid", mc_traj_trkid);
      MnvRecoTree->SetBranchAddress("mc_traj_parentid", mc_traj_parentid);
      MnvRecoTree->SetBranchAddress("mc_traj_pdg", mc_traj_pdg);
      MnvRecoTree->SetBranchAddress("mc_traj_hit_e", mc_traj_hit_e);
      MnvRecoTree->SetBranchAddress("mc_traj_npoints", mc_traj_npoints);
      MnvRecoTree->SetBranchAddress("mc_traj_point_x", mc_traj_point_x);
      MnvRecoTree->SetBranchAddress("mc_traj_point_y", mc_traj_point_y);
      MnvRecoTree->SetBranchAddress("mc_traj_point_z", mc_traj_point_z);
      MnvRecoTree->SetBranchAddress("mc_traj_point_t", mc_traj_point_t);
      MnvRecoTree->SetBranchAddress("mc_traj_point_px", mc_traj_point_px);
      MnvRecoTree->SetBranchAddress("mc_traj_point_py", mc_traj_point_py);
      MnvRecoTree->SetBranchAddress("mc_traj_point_pz", mc_traj_point_pz);
      MnvRecoTree->SetBranchAddress("mc_traj_point_E", mc_traj_point_E);

      //Truth Matching variables
      MnvRecoTree->SetBranchAddress("clus_id_size", clus_id_size);
      MnvRecoTree->SetBranchAddress("clus_id_hits_idx", clus_id_hits_idx);
      MnvRecoTree->SetBranchAddress("mc_id_mchit_trkid", mc_id_mchit_trkid);
      MnvRecoTree->SetBranchAddress("mc_id_mchit_dE", mc_id_mchit_dE);


    } else {
      fMnvRecoFile = NULL;
      MnvRecoTree = NULL;
      std::cerr << "Did not find input MINERvA reco file you provided: " << minervaRecoFilename << std::endl;
      std::cerr << "Are you sure it exists?" << std::endl;
      throw;
    }

    //TODO: This is hardcoded for now, need to find a way to pass it through via MINERvA file 
    offset_z = 654.8649999999999636; //Minerva ref point not centered on 0
    offset_y = - 43.0; //Minerva ref point not centered on 0
  }

  // ---------------------------------------------------------------------------

  // here we copy all the MINERvA reco into the SRMINERvA branch of the StandardRecord object.
  void MINERvARecoBranchFiller::_FillRecoBranches(std::size_t evtIdx,
                                              caf::StandardRecord &sr,
                                              const cafmaker::Params &par) const
  {
    // Get nth entry from tree
    MnvRecoTree->GetEntry(evtIdx);  

    int max_slice = 0;
    // Fill in the track info 
    std::map<int,std::vector<caf::SRTrack>> track_map = fill_track(max_slice);
    std::map<int,std::vector<caf::SRShower>> shower_map = fill_shower(max_slice);

    

    for (int i_slice = 0; i_slice < max_slice; i_slice++)
    {
      if (track_map[i_slice].size() == 0 && shower_map[i_slice].size() == 0) continue;
      caf::SRMINERvAInt my_int;

      my_int.ntracks = track_map[i_slice].size();
      my_int.nshowers = shower_map[i_slice].size();

      for (std::size_t i_track = 0; i_track < track_map[i_slice].size(); i_track ++) my_int.tracks.push_back(std::move(track_map[i_slice][i_track]));

      for (std::size_t i_shower = 0; i_shower < shower_map[i_slice].size(); i_shower ++) my_int.showers.push_back(std::move(shower_map[i_slice][i_shower]));
      
      sr.nd.minerva.ixn.push_back(my_int);
      sr.nd.minerva.nixn +=1;
    }

  }

  std::map<int, std::vector<caf::SRTrack>> MINERvARecoBranchFiller::fill_track(int & max_slice) const
  {
    std::map<int,std::vector<caf::SRTrack>> track_map;

    for (int i = 0; i < n_tracks; ++i) {

      int my_slice = trk_time_slice[i];
      caf::SRTrack my_track;

      // Save first and last hit in track
      // MINERvA Reco info is saved in mm whereas CAFs use CM as default -> do conversion here
      my_track.start = caf::SRVector3D(trk_node_X[i][0]/10.,trk_node_Y[i][0]/10. - offset_y, trk_node_Z[i][0]/10. + offset_z);
      my_track.end   = caf::SRVector3D(trk_node_X[i][n_tracks-1]/10.,trk_node_Y[i][n_tracks-1]/10. - offset_y, trk_node_Z[i][n_tracks-1]/10. + offset_z);

      // Track info
      my_track.len_cm  = sqrt(pow(trk_node_X[i][n_tracks-1] - trk_node_X[i][0],2)+pow(trk_node_Y[i][n_tracks-1] - trk_node_Y[i][0],2)+pow(trk_node_Z[i][n_tracks-1] - trk_node_Z[i][0],2))/10.;
      my_track.qual      = trk_chi2perDof[i];
      my_track.E         = trk_vis_energy[i];

      // Get the directions
      my_track.dir     = caf::SRVector3D(sin(trk_theta[i])*cos(trk_phi[i]),sin(trk_theta[i])*sin(trk_phi[i]),cos(trk_theta[i]));
      my_track.enddir  = caf::SRVector3D(sin(trk_theta[i])*cos(trk_phi[i]),sin(trk_theta[i])*sin(trk_phi[i]),cos(trk_theta[i]));

      //Fill the track map

      find_truth_track(my_track,i);
      track_map[my_slice].push_back(my_track);
      if (max_slice < my_slice) max_slice = my_slice;
    }
    return track_map;
  }

  std::map<int,std::vector<caf::SRShower>> MINERvARecoBranchFiller::fill_shower(int & max_slice) const
  {
    std::map<int,std::vector<caf::SRShower>> shower_map;

    for (int i = 0; i < n_blob_id; ++i) {

      int my_slice = blob_id_time_slice[i];
      caf::SRShower my_shower;

      // Save first and last hit in track
      // MINERvA Reco info is saved in mm whereas CAFs use CM as default -> do conversion here
      my_shower.start = caf::SRVector3D(blob_id_startpoint_x[i]/10.,blob_id_startpoint_y[i][0]/10. - offset_y, blob_id_startpoint_z[i][0]/10. + offset_z);
      
      double x_dir = (blob_id_centroid_x[i] - blob_id_startpoint_x[i]);
      double y_dir = (blob_id_centroid_y[i] - blob_id_startpoint_y[i]);
      double z_dir = (blob_id_centroid_z[i] - blob_id_startpoint_z[i]);
      double norm_dir = sqrt(x*x+y*y+z*z);
      x_dir /= norm_dir;
      y_dir /= norm_dir;
      z_dir /= norm_dir;

      my_shower.direction = caf::SRVector3D(x_dir, y_dir, z_dir);

      my_shower.Evis = blob_id_e[i];

      find_truth_shower(my_shower,i);
      //Fill the shower map
      shower_map[my_slice].push_back(my_shower);
      if (max_slice < my_slice) max_slice = my_slice;
    }

    return shower_map;
  }

  void MINERvARecoBranchFiller::find_truth_shower(caf::SRShower &sh, int shower_id) const
  {
    std::map<int, double> most_ids;
    for (int j = 0; j<blob_id_size[shower_id]; j++)
    {
        //Get the cluster associated to the node
        int id_cl = blob_id_clus_idx[shower_id][j];
        
        //Get the # of digits (hits) in the cluster
        int clus_size = clus_id_size[id_cl];

        for (int k = 0; k<clus_size; k++)
        {
            int id_hit = clus_id_hits_idx[id_cl][0];
            int traj_id = mc_id_mchit_trkid[id_hit][0]; // Get the true trajectory associated to the hit
            if (mc_id_mchit_dE[id_hit][0] > 0) 
            {
              most_trkid[traj_id] += mc_id_mchit_dE[id_hit][0]; // Looks for trajectory that contributed the most to the track 
            }
        }          
    }
   
    double max_trkid_stat = 0;
    int max_trkid = 0;

    for (auto & tkid : most_trkid) 
    {
        if (tkid.second > max_trkid_stat) {
            max_trkid_stat = tkid.second;
            max_trkid = tkid.first; 
        }
    }
    t.truth.pdg = mc_traj_pdg[max_trkid];
    t.truth.G4ID = max_trkid; 
    t.truth.time = mc_traj_point_t[max_trkid][0];
    t.truth.parent = mc_traj_parentid[max_trkid];
    SRVector3D start_pos = SRVector3D(mc_traj_point_x[max_trkid][0],mc_traj_point_y[max_trkid][0],mc_traj_point_z[max_trkid][0])
    SRVector3D end_pos = SRVector3D(mc_traj_point_x[max_trkid][1],mc_traj_point_y[max_trkid][1],mc_traj_point_z[max_trkid][1])

    t.truth.start_pos = start_pos;
    t.truth.end_pos = end_pos;
  }

  void MINERvARecoBranchFiller::find_truth_track(caf::SRTrack &t, int track_id) const
  {
    std::map<int, double> most_ids;
    for (int j = 0; j<trk_nodes[track_id]; j++)
    {
        //Get the cluster associated to the node
        int id_cl = trk_node_cluster_idx[track_id][j];
        
        //Get the # of digits (hits) in the cluster
        int clus_size = clus_id_size[id_cl];

        for (int k = 0; k<clus_size; k++)
        {
            int id_hit = clus_id_hits_idx[id_cl][0];
            int traj_id = mc_id_mchit_trkid[id_hit][0]; // Get the true trajectory associated to the hit
            if (mc_id_mchit_dE[id_hit][0] > 0) 
            {
              most_trkid[traj_id] += mc_id_mchit_dE[id_hit][0]; // Looks for trajectory that contributed the most to the track 
            }
        }          
    }
   
    double max_trkid_stat = 0;
    int max_trkid = 0;

    for (auto & tkid : most_trkid) 
    {
        if (tkid.second > max_trkid_stat) {
            max_trkid_stat = tkid.second;
            max_trkid = tkid.first; 
        }
    }
    t.truth.pdg = mc_traj_pdg[max_trkid];
    t.truth.G4ID = max_trkid; 
    t.truth.time = mc_traj_point_t[max_trkid][0];
    t.truth.parent = mc_traj_parentid[max_trkid];
    SRVector3D start_pos = SRVector3D(mc_traj_point_x[max_trkid][0],mc_traj_point_y[max_trkid][0],mc_traj_point_z[max_trkid][0])
    SRVector3D end_pos = SRVector3D(mc_traj_point_x[max_trkid][1],mc_traj_point_y[max_trkid][1],mc_traj_point_z[max_trkid][1])

    t.truth.start_pos = start_pos;
    t.truth.end_pos = end_pos;
  }


} // end namespace
