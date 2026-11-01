#ifndef DATASTORE_HH
#define DATASTORE_HH

#include <map>
#include "globals.hh"

#include "G4Types.hh"
#include "G4String.hh"
#include <string>

struct SliceData {
 G4double totalEnergy = 0.0; // deposited energy in this slice
 std::map<G4String, G4double> energyByParticle; // 粒子ごとのエネルギー [MeV]
 G4int primaries = 0;   // primary particles that reached this slice
 std::map<G4String, G4int> secondaries;
 };

class DataStore {
public:
    DataStore();
    ~DataStore();
// called by BeginRunAction, SensitiveDetector and EndRunAction
    void InitializeMap(); 
 //   void AddEnergy(G4int copyNo, G4double energy);
    void AddEnergy(G4int copyNo, G4String particleName, G4double edep); 
    void AddPrimary(G4int copyNo);
    void AddSecondary(G4int copyNo, G4String particleName);
    void WriteCSV(const std::string& fileName) const;
private:
    std::map<G4int, SliceData> myMap;
};

#endif
