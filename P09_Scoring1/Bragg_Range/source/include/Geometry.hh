#ifndef GEOMETRY_HH
#define GEOMETRY_HH

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4LogicalVolume.hh"

// forward declaration
class DataStore;

class Geometry : public G4VUserDetectorConstruction {
public:
    Geometry();
    virtual ~Geometry();
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField() override;
    void SetDataStore(DataStore* ds);

private:
//    G4LogicalVolume* logicSlice;
    DataStore* dataStore;
};

#endif
