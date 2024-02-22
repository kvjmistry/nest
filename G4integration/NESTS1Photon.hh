// ----------------------------------------------------------------------------
// nexus | S2Photon.hh
//
// Definition of the S1 Photon
// ----------------------------------------------------------------------------

#ifndef S1_PHOTON_H
#define S1_PHOTON_H
#include "globals.hh"
#include "G4ios.hh"
#include "G4ParticleDefinition.hh"
#include <G4ParticleDefinition.hh>



  class NESTS1Photon: public G4ParticleDefinition
  {
  public:
    /// Returns a pointer to the only instance
    static NESTS1Photon* Definition();

    static NESTS1Photon* OpticalPhotonDefinition();
    static NESTS1Photon* OpticalPhoton();

    /// Destructor
    ~NESTS1Photon(){};

  private:
    /// Default constructor is hidden.
    /// No instance of this class can be created.
    NESTS1Photon(){};

  private:
      static NESTS1Photon* theInstance;
  };

#endif
