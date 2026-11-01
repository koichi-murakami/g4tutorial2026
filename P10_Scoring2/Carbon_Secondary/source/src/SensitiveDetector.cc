#include "SensitiveDetector.hh"
#include "G4Step.hh"
#include "G4TouchableHistory.hh"

SensitiveDetector::SensitiveDetector(const G4String& name, DataStore* ds)
    : G4VSensitiveDetector(name), dataStore(ds) {}

SensitiveDetector::~SensitiveDetector() {}

void SensitiveDetector::Initialize(G4HCofThisEvent* hce) {}

G4bool SensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory* history) {
    G4int copyNo = step->GetPreStepPoint()->GetTouchable()->GetCopyNumber();
    G4String particleName = step->GetTrack()->GetDefinition()->GetParticleName();
    G4double edep = step->GetTotalEnergyDeposit();

    if (edep > 0) {
      dataStore->AddEnergy(copyNo, particleName, edep);
//      dataStore->AddEnergy(copyNo, edep);
    }

// 一次粒子のカウント（既存）
    if (step->GetTrack()->GetParentID() == 0 && step->IsFirstStepInVolume()) {
        dataStore->AddPrimary(copyNo);
    }
    // 二次粒子のカウント（既存）
    else if (step->GetTrack()->GetParentID() > 0 && step->IsFirstStepInVolume()) {
            G4String particleName = step->GetTrack()->GetDefinition()->GetParticleName();

        dataStore->AddSecondary(copyNo, particleName);
    }


    return true;
}
void SensitiveDetector::EndOfEvent(G4HCofThisEvent* hce) {
    // No specific actions needed in EndOfEvent for this example
}
