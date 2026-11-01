#include "DataStore.hh"
#include <fstream>
#include <cmath>

DataStore::DataStore() {}

DataStore::~DataStore() {}

void DataStore::InitializeMap() {
    myMap.clear();
}


void DataStore::AddEnergy(G4int copyNo, G4double energy) {
    myMap[copyNo].energy += energy;
}

void DataStore::AddPrimary(G4int copyNo) {
   myMap[copyNo].primaries += 1;
 }
void DataStore::WriteCSV(const std::string& fileName)const {
    std::ofstream outFile(fileName);
    outFile << "copyNo, energy, primaries\n";
    for (const auto& entry : myMap) {
        outFile << entry.first << ", "
                << entry.second.energy << ", "
                <<entry.second.primaries << "\n";
    }
    outFile.close();

}
