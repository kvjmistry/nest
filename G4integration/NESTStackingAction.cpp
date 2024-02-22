#include "NESTStackingAction.hh"
#include "NESTS1Photon.hh"
#include <iostream>

NESTStackingAction::NESTStackingAction() {}
NESTStackingAction::~NESTStackingAction() {}

NESTStackingAction* NESTStackingAction::theStackingAction = 0;
G4StackManager* NESTStackingAction::savedManager = 0;

G4ClassificationOfNewTrack NESTStackingAction::ClassifyNewTrack(
    const G4Track* track) {
  savedManager = stackManager;
  if (track->GetDefinition() == NESTS1Photon::OpticalPhotonDefinition()) {
    return fWaiting;
  }
  return fUrgent;
}

bool NESTStackingAction::isUrgentEmpty() {
  if (!savedManager) {
    std::cerr
        << "savedManager not set by NESTStackingAction::ClassifyNewTrack(). "
           "Did you set up NESTStackingAction as your stacking action? Did you "
           "override ClassifyNewTrack and forget to set savedManager?"
        << std::endl;
  }
  return savedManager->GetNUrgentTrack() == 0;
}
void NESTStackingAction::NewStage() {}