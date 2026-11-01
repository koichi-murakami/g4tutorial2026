#include "SensitiveDetector.hh"
#include "G4Step.hh"
#include "G4TouchableHistory.hh"

SensitiveDetector::SensitiveDetector(const G4String& name, DataStore* ds)
    : G4VSensitiveDetector(name), dataStore(ds) {}

SensitiveDetector::~SensitiveDetector() {}

void SensitiveDetector::Initialize(G4HCofThisEvent* hce) {}

G4bool SensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory* history) {
    G4int copyNo = step->GetPreStepPoint()->GetTouchable()->GetCopyNumber();

    G4double edep = step->GetTotalEnergyDeposit();

    if (edep > 0) {
      dataStore->AddEnergy(copyNo, edep);
    }
// 一次粒子のみカウント（実験的飛程測定）
   if ( step->GetTrack()->GetParentID() == 0) { 
// そのスライスに初めて入った瞬間だけ
   if (step->IsFirstStepInVolume()) {
      dataStore->AddPrimary(copyNo); 
    }
  }


    return true;
}
void SensitiveDetector::EndOfEvent(G4HCofThisEvent* hce) {
    // No specific actions needed in EndOfEvent for this example
}
