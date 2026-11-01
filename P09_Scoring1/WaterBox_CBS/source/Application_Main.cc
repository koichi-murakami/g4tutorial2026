//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Geant4 Application: Tutorial course for Hep/Medicine Users
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Geometry.hh"
#include "UserActionInitialization.hh"
#include "G4ScoringManager.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "FTFP_BERT.hh"
#include "G4String.hh" // 追加

//-------------------------------------------------------------------------------
  int main( int argc, char** argv )
//-------------------------------------------------------------------------------
{
// Construct the default run manager
   auto runManager = new G4RunManager;

// Activate UI-command base scorer
    G4ScoringManager * scManager = G4ScoringManager::GetScoringManager();
    scManager->SetVerboseLevel(1);

// Set up mandatory user initialization: Geometry
   runManager->SetUserInitialization( new Geometry );

// Set up mandatory user initialization: Physics-List
   runManager->SetUserInitialization( new FTFP_BERT );

// Set up user initialization: User Actions
   runManager->SetUserInitialization( new UserActionInitialization );

// Initialize G4 kernel
   runManager->Initialize();

// Get the pointer to the User Interface manager
   G4UImanager* uiManager = G4UImanager::GetUIpointer();

   if ( argc > 2 && G4String(argv[1]) == "-m" ) {
      // --------------------------------------------------
      // バッチモード: 指定されたマクロを実行して終了
      // --------------------------------------------------
      G4String macroFile = argv[2];
      G4String command = "/control/execute " + macroFile;
      uiManager->ApplyCommand( command );
   }
   else {
      // --------------------------------------------------
      // インタラクティブモード: GUI/ターミナルを起動
      // --------------------------------------------------
      auto visManager = new G4VisExecutive;
      visManager->Initialize();

      auto uiExec = new G4UIExecutive( argc, argv );
      uiManager->ApplyCommand( "/control/execute GlobalSetup.mac" );
      uiExec->SessionStart();

      delete uiExec;
      delete visManager;
   }

// Job termination
   delete runManager;

   return 0;
}
