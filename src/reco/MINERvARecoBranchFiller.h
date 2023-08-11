/// Fill MINERvA reco branches from MINERvA reco output.
///
/// \author  N.Roy <noeroy@yorku.ca>
/// \date    Nov. 2022

#ifndef ND_CAFMAKER_MINERvARecoBranchFiller_H
#define ND_CAFMAKER_MINERvARecoBranchFiller_H

#include <iostream>

// The virtual base class
#include "IRecoBranchFiller.h"

// File handlers from ROOT
#include "TFile.h"
#include "TTree.h"

// The duneanaobj includes
#include "duneanaobj/StandardRecord/StandardRecord.h"
//#include "duneanaobj/StandardRecord/SRTrack.h"

namespace cafmaker
{
  class MINERvARecoBranchFiller : public cafmaker::IRecoBranchFiller
  {
    public:
      MINERvARecoBranchFiller(const std::string & minervaRecoFilename);
      ~MINERvARecoBranchFiller() {
        delete MnvRecoTree;
        fMnvRecoFile->Close();
        delete fMnvRecoFile;
        MnvRecoTree = NULL;
        fMnvRecoFile = NULL;
      }

    private:
      void _FillRecoBranches(std::size_t evtIdx,
                             caf::StandardRecord &sr,
                             const cafmaker::Params &par) const override;

      std::map<int, std::vector<caf::SRShower>> fill_track(int & max_slice) const;

      std::map<int, std::vector<caf::SRShower>> fill_shower(int & max_slice) const;

      void find_truth_shower(caf::SRShower & sh, int shower_id) const;

      void find_truth_track(caf::SRTrack & t, int track_id) const;

      TFile *fMnvRecoFile;
      TTree *MnvRecoTree;

      //Tracks variables
      Int_t           n_tracks;
      Int_t           trk_index[100];   //[n_tracks]
      Int_t           trk_type[100];   //[n_tracks]
      Int_t           trk_patrec[100];   //[n_tracks]
      Int_t           trk_time_slice[100];   //[n_tracks]
      Double_t        trk_vis_energy[100];   //[n_tracks]
      Double_t        trk_theta[100];   //[n_tracks]
      Double_t        trk_phi[100];   //[n_tracks]
      Int_t           trk_hits[100];   //[n_tracks]
      Int_t           trk_dof[100];   //[n_tracks]
      Double_t        trk_chi2perDof[100];   //[n_tracks]
      Double_t        trk_fitMass[100];   //[n_tracks]
      Int_t           trk_nodes[100];   //[n_tracks]
      Double_t        trk_node_X[100][300];   //[n_tracks]
      Double_t        trk_node_Y[100][300];   //[n_tracks]
      Double_t        trk_node_Z[100][300];   //[n_tracks]
      Double_t        trk_node_aX[100][300];   //[n_tracks]
      Double_t        trk_node_aY[100][300];   //[n_tracks]
      Double_t        trk_node_qOverP[100][300];   //[n_tracks]
      Double_t        trk_node_chi2[100][300];   //[n_tracks]

      //Showers variables
      Int_t           n_blobs_id;
      Int_t           blob_id_idx[20];   //[n_blobs_id]
      Int_t           blob_id_subdet[20];   //[n_blobs_id]
      Int_t           blob_id_history[20];   //[n_blobs_id]
      Int_t           blob_id_size[20];   //[n_blobs_id]
      Int_t           blob_id_patrec[20];   //[n_blobs_id]
      Double_t        blob_id_e[20];   //[n_blobs_id]
      Double_t        blob_id_time[20];   //[n_blobs_id]
      Int_t           blob_id_time_slice[20];   //[n_blobs_id]
      Double_t        blob_id_startpoint_x[20];   //[n_blobs_id]
      Double_t        blob_id_startpoint_y[20];   //[n_blobs_id]
      Double_t        blob_id_startpoint_z[20];   //[n_blobs_id]
      Double_t        blob_id_centroid_x[20];   //[n_blobs_id]
      Double_t        blob_id_centroid_y[20];   //[n_blobs_id]
      Double_t        blob_id_centroid_z[20];   //[n_blobs_id]
      Int_t           blob_id_clus_idx[20][1500];   //[n_blobs_id]

      //Trajectories (Truth variables)
      Int_t           mc_traj_trkid[180];   //[n_mc_trajectories]
      Int_t           mc_traj_parentid[180];   //[n_mc_trajectories]
      Int_t           mc_traj_pdg[180];   //[n_mc_trajectories]
      Double_t        mc_traj_hit_e[180];   //[n_mc_trajectories]
      Int_t           mc_traj_npoints[180];   //[n_mc_trajectories]
      Double_t        mc_traj_point_x[180][5];   //[n_mc_trajectories]
      Double_t        mc_traj_point_y[180][5];   //[n_mc_trajectories]
      Double_t        mc_traj_point_z[180][5];   //[n_mc_trajectories]
      Double_t        mc_traj_point_t[180][5];   //[n_mc_trajectories]
      Double_t        mc_traj_point_px[180][5];   //[n_mc_trajectories]
      Double_t        mc_traj_point_py[180][5];   //[n_mc_trajectories]
      Double_t        mc_traj_point_pz[180][5];   //[n_mc_trajectories]
      Double_t        mc_traj_point_E[180][5];   //[n_mc_trajectories]

      //Cluster list & hit list for Trajectory matching
      Int_t           clus_id_size[2916];   //[n_clusters_id]
      Int_t           clus_id_hits_idx[2916][60];   //[n_clusters_id]
      Int_t           mc_id_mchit_trkid[3809][2];   //[n_mc_id_digits]
      Double_t        mc_id_mchit_dE[3809][2];   //[n_mc_id_digits]


  };

}
#endif //ND_CAFMAKER_MINERvARecoBranchFiller_H
