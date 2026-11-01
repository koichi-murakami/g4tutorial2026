#ifndef RUNACTION_HH
#define RUNACTION_HH

#include "G4UserRunAction.hh"
#include "DataStore.hh"
#include "G4String.hh"

class G4GenericMessenger; // 前方宣言

class RunAction : public G4UserRunAction {
public:
    RunAction(DataStore* ds);
    virtual ~RunAction();
    virtual void BeginOfRunAction(const G4Run*) override;
    virtual void EndOfRunAction(const G4Run*) override;

private:
    DataStore* dataStore;
    G4String fFileName; // ファイル名を保存する変数
    G4GenericMessenger* fMessenger; // コマンドを定義するメッセンジャー
};

#endif