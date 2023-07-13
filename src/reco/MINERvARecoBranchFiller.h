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

      TFile *fMnvRecoFile;
      TTree *MnvRecoTree;
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
  };

}
#endif //ND_CAFMAKER_MINERvARecoBranchFiller_H
