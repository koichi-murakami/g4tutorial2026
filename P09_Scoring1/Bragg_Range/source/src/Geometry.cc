#include "Geometry.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "SensitiveDetector.hh"
#include "DataStore.hh"

Geometry::Geometry() : G4VUserDetectorConstruction(), dataStore(nullptr) {}

Geometry::~Geometry() {}

void Geometry::SetDataStore(DataStore* ds) {
    dataStore = ds;
}

G4VPhysicalVolume* Geometry::Construct() {
    // Get materials
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* air = nist->FindOrBuildMaterial("G4_AIR");
    G4Material* water = nist->FindOrBuildMaterial("G4_WATER");

    // World
    G4double world_size = 1.0 * m;
    auto solidWorld = new G4Box("World", world_size / 2, world_size / 2, world_size / 2);
    auto logicWorld = new G4LogicalVolume(solidWorld, air, "World");
    auto physWorld = new G4PVPlacement(nullptr, G4ThreeVector(), logicWorld, "World", nullptr, false, 0, true);

    // Water phantom
    G4double phantom_size = 30.0 * cm;
    auto solidPhantom = new G4Box("Phantom", phantom_size / 2, phantom_size / 2, phantom_size / 2);
    auto logicPhantom = new G4LogicalVolume(solidPhantom, water, "Phantom");
    new G4PVPlacement(nullptr, G4ThreeVector(), logicPhantom, "Phantom", logicWorld, false, 0, true);



   // Container in the Water phantom
    G4double container_size = 1.0 * cm;
    auto solidContainer = new G4Box("Container", container_size / 2, container_size / 2, phantom_size / 2);
    auto logicContainer = new G4LogicalVolume(solidContainer, water, "Container");
    new G4PVPlacement(nullptr, G4ThreeVector(), logicContainer, "Container", logicPhantom, false, 0, true);



    // Slices
    G4double slice_thickness = 1.0 * mm;
    auto solidSlice = new G4Box("Slice", container_size / 2, container_size / 2, slice_thickness / 2);
    auto logicSlice = new G4LogicalVolume(solidSlice, water, "Slice");
    new G4PVReplica("containerSlice", logicSlice, logicContainer, kZAxis, 300, slice_thickness);
    return physWorld;
}
void Geometry::ConstructSDandField(){

    // Sensitive detector
    auto sd = new SensitiveDetector("Watercontainer", dataStore);
    G4SDManager::GetSDMpointer()->AddNewDetector(sd);
    SetSensitiveDetector("Slice", sd);

}
