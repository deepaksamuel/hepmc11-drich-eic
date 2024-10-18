
//
// root -l 'rich-hepmc-writer.cxx("out.hepmc", 100)'
//

#include "HepMC3/GenEvent.h"
#include "HepMC3/ReaderAscii.h"
#include "HepMC3/WriterAscii.h"
#include "HepMC3/Print.h"

#include <iostream>
#include <random>
#include <cmath>
#include <math.h>
#include <TMath.h>

using namespace HepMC3;

/** Generate single particle event with fixed three momentum **/
// n_events is number of events
// etaBinID defines etaBin We want to simulate
// mom is particle momentum
// pdg is particle PDG code


void drich_hepmc_writer_sp(int n_events, int etaBinID, double mom, int pdg)
{
  auto *DatabasePDG = new TDatabasePDG();
  
  auto *particle = DatabasePDG->GetParticle(pdg);
  //double mom = 50.;
  //double Eta[6] = {1.5,1.8,2.0,2.5,3.0,3.5}; 
  //double etaL=Eta[EtaBin], etaU=Eta[EtaBin]+0.01;   //   lower and upper limit of the eta bins
  double etaL=0, etaU=0;   //   lower and upper limit of the eta bins


//const char * out_fname = "out.hepmc";
 
  std::ostringstream oss;
  oss << pdg << "_" << mom << "_" << etaBinID<<".hepmc";
  std::string formattedString = oss.str();
  std::cout<<formattedString<<std::endl;   
  char* cStyleString = new char[formattedString.length() + 1]; // +1 for null terminator
  strcpy(cStyleString, formattedString.c_str());
  
  const char *out_fname = cStyleString;
  //double etaVals [6][2] ={{1.5,1.8},{1.8,2.0},{2.0,2.2},{2.2,2.5},{2.5,3.0},{3.0,3.5}};
  // double etaVals [3][2] ={{1.5,2.0},{2.0,2.5},{2.5,3.5}};
  // double etaVals [2][2] ={{1.5,2.5},{2.5,3.5}}; //CUK edited
      double etaVals[21][2] = {
        {1.499, 1.501}, //etaBin 0
        {1.599, 1.601}, //etaBin 1
        {1.699, 1.701}, //etaBin 2
        {1.799, 1.801}, //etaBin 3
        {1.899, 1.901}, //etaBin 4
        {1.999, 2.001}, //etaBin 5
        {2.099, 2.101}, //etaBin 6
        {2.199, 2.201}, //etaBin 7
        {2.299, 2.301}, //etaBin 8
        {2.399, 2.401}, //etaBin 9
        {2.499, 2.501}, //etaBin 10
        {2.599, 2.601}, //etaBin 11
        {2.699, 2.701}, //etaBin 12
        {2.799, 2.801}, //etaBin 13
        {2.899, 2.901}, //etaBin 14
        {2.999, 3.001}, //etaBin 15
        {3.099, 3.101}, //etaBin 16
        {3.199, 3.201}, //etaBin 17
        {3.299, 3.301}, //etaBin 18
        {3.399, 3.401}, //etaBin 19
        {3.499, 3.501}  //etaBin 20
    };

if (etaBinID >= 0 && etaBinID <= 20) {
    etaL = etaVals[etaBinID][0];
    etaU = etaVals[etaBinID][1];
} else {
    std::cerr << "Invalid etaBinID: " << etaBinID << std::endl;
}


  // if(etaBinID == 0){ etaL = etaVals[0][0] ; etaU = etaVals[0][1];} 
  // if(etaBinID == 1){ etaL = etaVals[1][0] ; etaU = etaVals[1][1];} 
//  if(etaBinID == 2){ etaL = etaVals[2][0] ; etaU = etaVals[2][1];} 
  
  printf("%d particles (PDG: %d) will be shot of mom %0.2lf at eta: %0.3lf-%0.3lf in %s file\n",n_events,pdg,mom,etaL,etaU,out_fname);

  WriterAscii hepmc_output(out_fname);
  int events_parsed = 0;
  

  //std::random_device rd;
  unsigned int seed = 0x12345678;//(unsigned int)abs(rd());
  std::cout << "init seed for random generator is " << seed << std::endl;
  // Random number generator
  TRandom *rdmn_gen = new TRandom(seed);
    for (events_parsed = 0; events_parsed < n_events; events_parsed++) { //event loop
    GenEvent evt(Units::GEV, Units::MM);
    // evt.set_event_number(events_parsed); 

    
      //FourVector(px,py,pz,e,pdgid,status)
      // type 4 is beam
      // pdgid 2212 - proton
      ////Mother particle; We really don't care
      // Type 4 means mother particle
      GenParticlePtr p1 =
        std::make_shared<GenParticle>(FourVector(0.0, 0.0, 12.0, 12.0), 11, 4);
      GenParticlePtr p2 = std::make_shared<GenParticle>(
        FourVector(0.0, 0.0, 100.0, 100.004), 2212, 4); 

      GenVertexPtr v1 = std::make_shared<GenVertex>();//FourVector(0,0,30,0));
      v1->add_particle_in(p1);
      v1->add_particle_in(p2);


      /// Daughter particles; We care for RICH analysis
      // type 1 is final state; 211: pion; FIXME: give a proper mass;

      for(int iq=0; iq<1; iq++){ // daughter particle loop  
        Double_t eta =0;
        eta = rdmn_gen->Uniform(etaL,etaU);
        Double_t th    = 2*std::atan(exp(-eta));
        Double_t p =0.0;
        p     = rdmn_gen->Uniform(mom-0.1, mom+0.1);
      
        //Double_t phi   = rdmn_gen->Uniform(i_sec*60, (i_sec*60)+0.5);
        //Double_t phi   = rdmn_gen->Uniform(Phi*(M_PI/180.),((Phi+0.5)*(M_PI/180.)));
        Double_t phi   = rdmn_gen->Uniform(0.0, 2*M_PI);
        Double_t px    = p * std::cos(phi) * std::sin(th);
        Double_t py    = p * std::sin(phi) * std::sin(th);
        Double_t pz    = p * std::cos(th);

        //cout<<"px,py,pz: "<<px<<" "<<py<<" "<<pz<<endl;
      
        GenParticlePtr pq = std::make_shared<GenParticle>(FourVector(
								   px, py, pz,
								   sqrt(p*p + pow(particle->Mass(), 2))),
							pdg, 1);
        v1->add_particle_out(pq);
      }//iq	
      evt.add_vertex(v1);

      if (events_parsed == 0) {
        std::cout << "First event: " << std::endl;
        Print::listing(evt);
      } 

      hepmc_output.write_event(evt);
      if (events_parsed % 10000 == 0) {
        std::cout << "Event: " << events_parsed << std::endl;
      }
      evt.clear();
    }
  
  hepmc_output.close();
  std::cout << "Events parsed and written: " << events_parsed << std::endl;
  exit(0);
}
