#ifndef DATASTORE_HH
#define DATASTORE_HH

#include <map>
#include "globals.hh"

struct SliceData {
 G4double energy = 0.0; // deposited energy in this slice
 G4int primaries = 0;   // primary particles that reached this slice
 };

class DataStore {
public:
    DataStore();
    ~DataStore();
// called by BeginRunAction, SensitiveDetector and EndRunAction
    void InitializeMap(); 
    void AddEnergy(G4int copyNo, G4double energy);
    void AddPrimary(G4int copyNo);
    void WriteCSV(const std::string& fileName) const;
private:
    std::map<G4int, SliceData> myMap;
};

#endif
