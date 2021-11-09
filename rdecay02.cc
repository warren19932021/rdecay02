//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file rdecay02.cc
/// \brief Main program of the radioactivedecay/rdecay02 example
//
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4Types.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "Randomize.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"
#include "SteppingVerbose.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "FTFP_BERT.hh"

#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv) {


  //detect interactive mode (if no arguments) and define UI session
  G4UIExecutive* ui = 0;
//  if (argc == 1) ui = new G4UIExecutive(argc,argv);
  ui = new G4UIExecutive(argc,argv);

  G4cout<<"ui: "<<(bool)ui<<G4endl;
  //choose the Random engine
  G4Random::setTheEngine(new CLHEP::RanecuEngine);


   std::cout << "Step 111********************* "<< std::endl;


  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  G4VSteppingVerbose::SetInstance(new SteppingVerbose);
   std::cout << "Step 222********************* "<< std::endl;
  G4RunManager* runManager = new G4RunManager;
   std::cout << "Step 2.52.52.5********************* "<< std::endl;

/*

#ifdef G4MULTITHREADED

  //choose the Random engine
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  if (argc==3) nThreads = G4UIcommand::ConvertToInt(argv[2]);
  runManager->SetNumberOfThreads(nThreads);
#else
  //my Verbose output class
  G4VSteppingVerbose::SetInstance(new SteppingVerbose);
  G4RunManager* runManager = new G4RunManager;
#endif

*/

  //set mandatory initialization classes
  DetectorConstruction* det= new DetectorConstruction;
  runManager->SetUserInitialization(det);

  //PhysicsList* phys = new PhysicsList;
  //runManager->SetUserInitialization( phys );
  G4VModularPhysicsList* physicsList = new FTFP_BERT;
  runManager->SetUserInitialization( physicsList );
   std::cout << "Step 2.55555555555555555******************** "<< std::endl;

  runManager->SetUserInitialization(new ActionInitialization(det));
   std::cout << "Step 2.66666666666666666******************** "<< std::endl;

  //initialize visualization
  G4VisManager* visManager = nullptr;
   std::cout << "Step 2.77777777777777777******************** "<< std::endl;
   visManager = new G4VisExecutive;
   std::cout << "Step 2.88888888888888888******************** "<< std::endl;
  // get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();
   std::cout << "Step 2.99999999999999999******************** "<< std::endl;
   visManager->Initialize();

  if (ui)  {
   //interactive mode
   //  visManager->Initialize();
   std::cout << "Step 333********************* "<< std::endl;

   UImanager->ApplyCommand("/control/execute vis.mac");
//   UImanager->ApplyCommand("/control/execute ne24.mac");
   ui->SessionStart();
   delete ui;
 
  }
  else  {
   //batch mode/
  //visManager->Initialize();

    std::cout << "Step 444********************* "<< std::endl;
   G4String command = "/control/execute ";
   G4String fileName = argv[1];
   std::cout << "command: " << command << " filename: " << fileName << std::endl;
   UImanager->ApplyCommand(command+fileName);
  }


//UImanager->ApplyCommand("/control/execute vis.mac");
//UImanager->ApplyCommand("/control/execute neutron.mac");
  //job termination
  delete visManager;
  delete runManager;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
