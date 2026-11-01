#include "RunAction.hh"
#include "G4Run.hh"
#include <fstream>
#include "G4GenericMessenger.hh"

RunAction::RunAction(DataStore* ds) : G4UserRunAction(), dataStore(ds) , fFileName("Bragg_Range.csv")
{
// メッセンジャーの作成。第一引数はコマンドのパス
    fMessenger = new G4GenericMessenger(this, "/run/output/", "Output control");

    // コマンドの定義: /run/output/fileName [文字列] で fFileName を書き換える
    fMessenger->DeclareProperty("fileName", fFileName, "Name of the output CSV file");
}


RunAction::~RunAction() {delete fMessenger; }

void RunAction::BeginOfRunAction(const G4Run*) {
    dataStore->InitializeMap();
}

void RunAction::EndOfRunAction(const G4Run*) {
    dataStore->WriteCSV(fFileName);
}
