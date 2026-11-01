#include "DataStore.hh"
#include <fstream>
#include <cmath>
#include <iomanip> // 出力を整えるため

DataStore::DataStore() {}

DataStore::~DataStore() {}

void DataStore::InitializeMap() {
    myMap.clear();
}


void DataStore::AddEnergy(G4int copyNo, G4String particleName, G4double edep) {
    myMap[copyNo].totalEnergy += edep;
    myMap[copyNo].energyByParticle[particleName] += edep;
}

void DataStore::AddPrimary(G4int copyNo) {
   myMap[copyNo].primaries += 1;
 }

void DataStore::AddSecondary(G4int copyNo, G4String particleName) {
    // 指定したスライスの、その粒子名のカウントを +1 する
    myMap[copyNo].secondaries[particleName] += 1;
}


void DataStore::WriteCSV(const std::string& fileName) const {
    std::ofstream outFile(fileName);
    outFile << "copyNo,total_energy,primaries,energy_details,secondary_counts\n";
    for (const auto& entry : myMap) {
        outFile << entry.first << "," 
                << entry.second.totalEnergy << ","
                << entry.second.primaries << ",";
        
        // 粒子名:エネルギー[MeV]; の形式で記録
        for (const auto& e : entry.second.energyByParticle) {
            outFile << e.first << ":" << e.second << ";";
        }
outFile << ","; // 次の列へ

        // ★ 個数の内訳を追加
        for (const auto& s : entry.second.secondaries) {
            outFile << s.first << ":" << s.second << ";";
        }

        outFile << "\n";
    }

    outFile.close();
}
