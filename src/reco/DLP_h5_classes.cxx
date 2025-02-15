
//  WARNING:
//    This file was autogenerated by h5_to_cpp.py.
//    Do not edit by hand!

#include "DLP_h5_classes.h"
#include "H5Cpp.h"

namespace cafmaker::types::dlp
{

  
  void Event::SyncVectors()
  {
  
  }
  
  
  void Particle::SyncVectors()
  {
    fragment_ids.reset(&fragment_ids_handle);
    index.reset(&index_handle);
    match.reset(&match_handle);
    match_counts.reset(&match_counts_handle);
  }
  
  
  void Interaction::SyncVectors()
  {
    match.reset(&match_handle);
    match_counts.reset(&match_counts_handle);
    particle_ids.reset(&particle_ids_handle);
  }
  
  
  void TrueInteraction::SyncVectors()
  {
    match.reset(&match_handle);
    match_counts.reset(&match_counts_handle);
    particle_ids.reset(&particle_ids_handle);
  }
  
  
  void TrueParticle::SyncVectors()
  {
    fragment_ids.reset(&fragment_ids_handle);
    index.reset(&index_handle);
    match.reset(&match_handle);
    match_counts.reset(&match_counts_handle);
    truth_index.reset(&truth_index_handle);
  }
  
  
  template <>
  H5::CompType BuildCompType<Event>()
  {
    H5::CompType ctype(sizeof(Event));
  
    ctype.insertMember("meta", HOFFSET(Event, meta), H5::PredType::STD_REF_DSETREG);
    ctype.insertMember("index", HOFFSET(Event, index), H5::PredType::STD_REF_DSETREG);
    ctype.insertMember("truth_interactions", HOFFSET(Event, truth_interactions), H5::PredType::STD_REF_DSETREG);
    ctype.insertMember("truth_particles", HOFFSET(Event, truth_particles), H5::PredType::STD_REF_DSETREG);
    ctype.insertMember("particles", HOFFSET(Event, particles), H5::PredType::STD_REF_DSETREG);
    ctype.insertMember("interactions", HOFFSET(Event, interactions), H5::PredType::STD_REF_DSETREG);
  
    return ctype;
  }
  
  
  template <>
  H5::CompType BuildCompType<Particle>()
  {
    H5::CompType ctype(sizeof(Particle));
  
    ctype.insertMember("depositions_sum", HOFFSET(Particle, depositions_sum), H5::PredType::IEEE_F64LE);
    ctype.insertMember("end_dir", HOFFSET(Particle, end_dir), H5::ArrayType(H5::PredType::IEEE_F32LE, 1, &std::array<hsize_t, 1>{3}[0]));
    ctype.insertMember("end_point", HOFFSET(Particle, end_point), H5::ArrayType(H5::PredType::IEEE_F64LE, 1, &std::array<hsize_t, 1>{3}[0]));
    ctype.insertMember("fragment_ids", HOFFSET(Particle, fragment_ids_handle), H5::VarLenType(H5::PredType::STD_I64LE));
    ctype.insertMember("id", HOFFSET(Particle, id), H5::PredType::STD_I64LE);
    ctype.insertMember("image_id", HOFFSET(Particle, image_id), H5::PredType::STD_I64LE);
    ctype.insertMember("index", HOFFSET(Particle, index_handle), H5::VarLenType(H5::PredType::STD_I64LE));
    ctype.insertMember("interaction_id", HOFFSET(Particle, interaction_id), H5::PredType::STD_I64LE);
    ctype.insertMember("is_primary", HOFFSET(Particle, is_primary), H5::PredType::STD_I64LE);
    ctype.insertMember("match", HOFFSET(Particle, match_handle), H5::VarLenType(H5::PredType::STD_I64LE));
    ctype.insertMember("match_counts", HOFFSET(Particle, match_counts_handle), H5::VarLenType(H5::PredType::IEEE_F32LE));
    ctype.insertMember("momentum_mcs", HOFFSET(Particle, momentum_mcs), H5::PredType::IEEE_F64LE);
    ctype.insertMember("momentum_range", HOFFSET(Particle, momentum_range), H5::PredType::IEEE_F64LE);
    ctype.insertMember("nu_id", HOFFSET(Particle, nu_id), H5::PredType::STD_I64LE);
    ctype.insertMember("num_fragments", HOFFSET(Particle, num_fragments), H5::PredType::STD_I64LE);
    
    H5::EnumType pid_enumtype(H5::PredType::STD_I64LE);
    int64_t pid_enum_val;
      pid_enum_val = 1; pid_enumtype.insert("Electron", &pid_enum_val);
      pid_enum_val = 2; pid_enumtype.insert("Muon", &pid_enum_val);
      pid_enum_val = 0; pid_enumtype.insert("Photon", &pid_enum_val);
      pid_enum_val = 3; pid_enumtype.insert("Pion", &pid_enum_val);
      pid_enum_val = 4; pid_enumtype.insert("Proton", &pid_enum_val);
    ctype.insertMember("pid", HOFFSET(Particle, pid), pid_enumtype);
    
    ctype.insertMember("pid_scores", HOFFSET(Particle, pid_scores), H5::ArrayType(H5::PredType::IEEE_F32LE, 1, &std::array<hsize_t, 1>{5}[0]));
    ctype.insertMember("primary_scores", HOFFSET(Particle, primary_scores), H5::ArrayType(H5::PredType::IEEE_F32LE, 1, &std::array<hsize_t, 1>{2}[0]));
    
    H5::EnumType semantic_type_enumtype(H5::PredType::STD_I64LE);
    int64_t semantic_type_enum_val;
      semantic_type_enum_val = 3; semantic_type_enumtype.insert("Delta", &semantic_type_enum_val);
      semantic_type_enum_val = 5; semantic_type_enumtype.insert("Ghost", &semantic_type_enum_val);
      semantic_type_enum_val = 4; semantic_type_enumtype.insert("Low Energy", &semantic_type_enum_val);
      semantic_type_enum_val = 2; semantic_type_enumtype.insert("Michel", &semantic_type_enum_val);
      semantic_type_enum_val = 0; semantic_type_enumtype.insert("Shower", &semantic_type_enum_val);
      semantic_type_enum_val = 1; semantic_type_enumtype.insert("Track", &semantic_type_enum_val);
      semantic_type_enum_val = 6; semantic_type_enumtype.insert("Unknown", &semantic_type_enum_val);
    ctype.insertMember("semantic_type", HOFFSET(Particle, semantic_type), semantic_type_enumtype);
    
    ctype.insertMember("size", HOFFSET(Particle, size), H5::PredType::STD_I64LE);
    ctype.insertMember("start_dir", HOFFSET(Particle, start_dir), H5::ArrayType(H5::PredType::IEEE_F32LE, 1, &std::array<hsize_t, 1>{3}[0]));
    ctype.insertMember("start_point", HOFFSET(Particle, start_point), H5::ArrayType(H5::PredType::IEEE_F64LE, 1, &std::array<hsize_t, 1>{3}[0]));
    ctype.insertMember("volume_id", HOFFSET(Particle, volume_id), H5::PredType::STD_I64LE);
  
    return ctype;
  }
  
  
  template <>
  H5::CompType BuildCompType<Interaction>()
  {
    H5::CompType ctype(sizeof(Interaction));
  
    ctype.insertMember("flash_hypothesis", HOFFSET(Interaction, flash_hypothesis), H5::PredType::STD_I64LE);
    ctype.insertMember("flash_id", HOFFSET(Interaction, flash_id), H5::PredType::STD_I64LE);
    ctype.insertMember("flash_time", HOFFSET(Interaction, flash_time), H5::PredType::IEEE_F64LE);
    ctype.insertMember("flash_total_pE", HOFFSET(Interaction, flash_total_pE), H5::PredType::STD_I64LE);
    ctype.insertMember("fmatched", HOFFSET(Interaction, fmatched), H5::PredType::STD_U8LE);
    ctype.insertMember("id", HOFFSET(Interaction, id), H5::PredType::STD_I64LE);
    ctype.insertMember("image_id", HOFFSET(Interaction, image_id), H5::PredType::STD_I64LE);
    ctype.insertMember("is_neutrino", HOFFSET(Interaction, is_neutrino), H5::PredType::STD_U8LE);
    ctype.insertMember("match", HOFFSET(Interaction, match_handle), H5::VarLenType(H5::PredType::STD_I64LE));
    ctype.insertMember("match_counts", HOFFSET(Interaction, match_counts_handle), H5::VarLenType(H5::PredType::IEEE_F32LE));
    ctype.insertMember("nu_id", HOFFSET(Interaction, nu_id), H5::PredType::STD_I64LE);
    ctype.insertMember("num_particles", HOFFSET(Interaction, num_particles), H5::PredType::STD_I64LE);
    ctype.insertMember("num_primaries", HOFFSET(Interaction, num_primaries), H5::PredType::STD_I64LE);
    ctype.insertMember("particle_counts", HOFFSET(Interaction, particle_counts), H5::ArrayType(H5::PredType::STD_I64LE, 1, &std::array<hsize_t, 1>{6}[0]));
    ctype.insertMember("particle_ids", HOFFSET(Interaction, particle_ids_handle), H5::VarLenType(H5::PredType::STD_I64LE));
    ctype.insertMember("primary_counts", HOFFSET(Interaction, primary_counts), H5::ArrayType(H5::PredType::STD_I64LE, 1, &std::array<hsize_t, 1>{6}[0]));
    ctype.insertMember("size", HOFFSET(Interaction, size), H5::PredType::STD_I64LE);
    ctype.insertMember("vertex", HOFFSET(Interaction, vertex), H5::ArrayType(H5::PredType::IEEE_F64LE, 1, &std::array<hsize_t, 1>{3}[0]));
    ctype.insertMember("volume_id", HOFFSET(Interaction, volume_id), H5::PredType::STD_I64LE);
  
    return ctype;
  }
  
  
  template <>
  H5::CompType BuildCompType<TrueInteraction>()
  {
    H5::CompType ctype(sizeof(TrueInteraction));
  
    ctype.insertMember("flash_hypothesis", HOFFSET(TrueInteraction, flash_hypothesis), H5::PredType::STD_I64LE);
    ctype.insertMember("flash_id", HOFFSET(TrueInteraction, flash_id), H5::PredType::STD_I64LE);
    ctype.insertMember("flash_time", HOFFSET(TrueInteraction, flash_time), H5::PredType::IEEE_F64LE);
    ctype.insertMember("flash_total_pE", HOFFSET(TrueInteraction, flash_total_pE), H5::PredType::STD_I64LE);
    ctype.insertMember("fmatched", HOFFSET(TrueInteraction, fmatched), H5::PredType::STD_U8LE);
    ctype.insertMember("id", HOFFSET(TrueInteraction, id), H5::PredType::STD_I64LE);
    ctype.insertMember("image_id", HOFFSET(TrueInteraction, image_id), H5::PredType::STD_I64LE);
    ctype.insertMember("is_neutrino", HOFFSET(TrueInteraction, is_neutrino), H5::PredType::STD_U8LE);
    ctype.insertMember("match", HOFFSET(TrueInteraction, match_handle), H5::VarLenType(H5::PredType::STD_I64LE));
    ctype.insertMember("match_counts", HOFFSET(TrueInteraction, match_counts_handle), H5::VarLenType(H5::PredType::IEEE_F32LE));
    ctype.insertMember("nu_current_type", HOFFSET(TrueInteraction, nu_current_type), H5::PredType::STD_I64LE);
    ctype.insertMember("nu_energy_init", HOFFSET(TrueInteraction, nu_energy_init), H5::PredType::IEEE_F64LE);
    ctype.insertMember("nu_id", HOFFSET(TrueInteraction, nu_id), H5::PredType::STD_I64LE);
    ctype.insertMember("nu_interaction_mode", HOFFSET(TrueInteraction, nu_interaction_mode), H5::PredType::STD_I64LE);
    ctype.insertMember("nu_interaction_type", HOFFSET(TrueInteraction, nu_interaction_type), H5::PredType::STD_I64LE);
    ctype.insertMember("num_particles", HOFFSET(TrueInteraction, num_particles), H5::PredType::STD_I64LE);
    ctype.insertMember("num_primaries", HOFFSET(TrueInteraction, num_primaries), H5::PredType::STD_I64LE);
    ctype.insertMember("particle_counts", HOFFSET(TrueInteraction, particle_counts), H5::ArrayType(H5::PredType::STD_I64LE, 1, &std::array<hsize_t, 1>{6}[0]));
    ctype.insertMember("particle_ids", HOFFSET(TrueInteraction, particle_ids_handle), H5::VarLenType(H5::PredType::STD_I64LE));
    ctype.insertMember("primary_counts", HOFFSET(TrueInteraction, primary_counts), H5::ArrayType(H5::PredType::STD_I64LE, 1, &std::array<hsize_t, 1>{6}[0]));
    ctype.insertMember("size", HOFFSET(TrueInteraction, size), H5::PredType::STD_I64LE);
    ctype.insertMember("vertex", HOFFSET(TrueInteraction, vertex), H5::ArrayType(H5::PredType::IEEE_F64LE, 1, &std::array<hsize_t, 1>{3}[0]));
    ctype.insertMember("volume_id", HOFFSET(TrueInteraction, volume_id), H5::PredType::STD_I64LE);
  
    return ctype;
  }
  
  
  template <>
  H5::CompType BuildCompType<TrueParticle>()
  {
    H5::CompType ctype(sizeof(TrueParticle));
  
    ctype.insertMember("depositions_sum", HOFFSET(TrueParticle, depositions_sum), H5::PredType::IEEE_F64LE);
    ctype.insertMember("end_dir", HOFFSET(TrueParticle, end_dir), H5::ArrayType(H5::PredType::IEEE_F32LE, 1, &std::array<hsize_t, 1>{3}[0]));
    ctype.insertMember("end_point", HOFFSET(TrueParticle, end_point), H5::ArrayType(H5::PredType::IEEE_F32LE, 1, &std::array<hsize_t, 1>{3}[0]));
    ctype.insertMember("end_position", HOFFSET(TrueParticle, end_position), H5::ArrayType(H5::PredType::IEEE_F32LE, 1, &std::array<hsize_t, 1>{4}[0]));
    ctype.insertMember("fragment_ids", HOFFSET(TrueParticle, fragment_ids_handle), H5::VarLenType(H5::PredType::STD_I64LE));
    ctype.insertMember("id", HOFFSET(TrueParticle, id), H5::PredType::STD_I64LE);
    ctype.insertMember("image_id", HOFFSET(TrueParticle, image_id), H5::PredType::STD_I64LE);
    ctype.insertMember("index", HOFFSET(TrueParticle, index_handle), H5::VarLenType(H5::PredType::STD_I64LE));
    ctype.insertMember("interaction_id", HOFFSET(TrueParticle, interaction_id), H5::PredType::STD_I64LE);
    ctype.insertMember("is_primary", HOFFSET(TrueParticle, is_primary), H5::PredType::STD_U8LE);
    ctype.insertMember("match", HOFFSET(TrueParticle, match_handle), H5::VarLenType(H5::PredType::STD_I64LE));
    ctype.insertMember("match_counts", HOFFSET(TrueParticle, match_counts_handle), H5::VarLenType(H5::PredType::IEEE_F32LE));
    ctype.insertMember("momentum", HOFFSET(TrueParticle, momentum), H5::ArrayType(H5::PredType::IEEE_F32LE, 1, &std::array<hsize_t, 1>{3}[0]));
    ctype.insertMember("momentum_mcs", HOFFSET(TrueParticle, momentum_mcs), H5::PredType::IEEE_F64LE);
    ctype.insertMember("momentum_range", HOFFSET(TrueParticle, momentum_range), H5::PredType::IEEE_F64LE);
    ctype.insertMember("nu_id", HOFFSET(TrueParticle, nu_id), H5::PredType::STD_I64LE);
    ctype.insertMember("num_fragments", HOFFSET(TrueParticle, num_fragments), H5::PredType::STD_I64LE);
    
    H5::EnumType pid_enumtype(H5::PredType::STD_I64LE);
    int64_t pid_enum_val;
      pid_enum_val = 1; pid_enumtype.insert("Electron", &pid_enum_val);
      pid_enum_val = 2; pid_enumtype.insert("Muon", &pid_enum_val);
      pid_enum_val = 0; pid_enumtype.insert("Photon", &pid_enum_val);
      pid_enum_val = 3; pid_enumtype.insert("Pion", &pid_enum_val);
      pid_enum_val = 4; pid_enumtype.insert("Proton", &pid_enum_val);
    ctype.insertMember("pid", HOFFSET(TrueParticle, pid), pid_enumtype);
    
    ctype.insertMember("pid_scores", HOFFSET(TrueParticle, pid_scores), H5::ArrayType(H5::PredType::IEEE_F32LE, 1, &std::array<hsize_t, 1>{5}[0]));
    ctype.insertMember("primary_scores", HOFFSET(TrueParticle, primary_scores), H5::ArrayType(H5::PredType::IEEE_F32LE, 1, &std::array<hsize_t, 1>{2}[0]));
    
    H5::EnumType semantic_type_enumtype(H5::PredType::STD_I64LE);
    int64_t semantic_type_enum_val;
      semantic_type_enum_val = 3; semantic_type_enumtype.insert("Delta", &semantic_type_enum_val);
      semantic_type_enum_val = 5; semantic_type_enumtype.insert("Ghost", &semantic_type_enum_val);
      semantic_type_enum_val = 4; semantic_type_enumtype.insert("Low Energy", &semantic_type_enum_val);
      semantic_type_enum_val = 2; semantic_type_enumtype.insert("Michel", &semantic_type_enum_val);
      semantic_type_enum_val = 0; semantic_type_enumtype.insert("Shower", &semantic_type_enum_val);
      semantic_type_enum_val = 1; semantic_type_enumtype.insert("Track", &semantic_type_enum_val);
      semantic_type_enum_val = 6; semantic_type_enumtype.insert("Unknown", &semantic_type_enum_val);
    ctype.insertMember("semantic_type", HOFFSET(TrueParticle, semantic_type), semantic_type_enumtype);
    
    ctype.insertMember("size", HOFFSET(TrueParticle, size), H5::PredType::STD_I64LE);
    ctype.insertMember("start_dir", HOFFSET(TrueParticle, start_dir), H5::ArrayType(H5::PredType::IEEE_F32LE, 1, &std::array<hsize_t, 1>{3}[0]));
    ctype.insertMember("start_point", HOFFSET(TrueParticle, start_point), H5::ArrayType(H5::PredType::IEEE_F32LE, 1, &std::array<hsize_t, 1>{3}[0]));
    ctype.insertMember("start_position", HOFFSET(TrueParticle, start_position), H5::ArrayType(H5::PredType::IEEE_F32LE, 1, &std::array<hsize_t, 1>{4}[0]));
    ctype.insertMember("truth_index", HOFFSET(TrueParticle, truth_index_handle), H5::VarLenType(H5::PredType::STD_I64LE));
    ctype.insertMember("truth_size", HOFFSET(TrueParticle, truth_size), H5::PredType::STD_I64LE);
    ctype.insertMember("volume_id", HOFFSET(TrueParticle, volume_id), H5::PredType::STD_I64LE);
  
    return ctype;
  }
  

}
