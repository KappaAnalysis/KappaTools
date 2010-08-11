#include <TChain.h>
#include "RootTools/FileInterface.h"
#include "Toolbox/CmdLineSetup.h"
#include "Toolbox/ProgressMonitor.h"
#include "EventId.h"
#include <set>

using namespace std;

std::ostream& operator <<(std::ostream& output, const EventId& id){
    output<<"Run_id: "<<id.rid<<", Lumi_id: "<<id.lid<<", Event_Id: "<<id.nCmsEvent;
    return output;
}

set<EventId> _globalEventCheckerSet;

string progname;

void MyHelpFunction(string arg){
  cout<<"Duplicate Event Checker Help: "<<endl;
  cout<<progname<<" [list of filenames] "<<endl;
  exit(1);
}

int main(int argc, char* argv[])
{
  static CmdLineOptionCallback clVersion('h', "help", "Print help", MyHelpFunction);
  progname=argv[0];
  std::vector<std::string> filenames = CmdLineBase::ParseArgs(argc, argv);

  if (filenames.size()==0) {
    cerr<<"No input files given!"<<endl;
    MyHelpFunction("");
  }
  cout<<"Reading files: "<<endl;
  for (std::vector<std::string>::iterator it=filenames.begin(); it!=filenames.end();it++)
    cout<<*it<<", ";
  
  cout<<endl;
  
  cout<<"\nDuplicate Event Checker "<<endl;
  cout<<"-- currently only checking for duplicate run/lumisection/event numbers."<<endl;
  cout<<"Feel free to add physical event-checking for Generator etc. Yourself, as this needs to be adopted to the specific sample. (Check Muon/Jet Pt, etc.)\n"<<endl;
  
  FileInterface kpFi(filenames,false,2);
  TChain *theChain=&kpFi.eventdata;
  KEventMetadata *metadata;
  KGenEventMetadata *kGen;
  kpFi.AssignEventPtr(&metadata,&kGen);
  run_id rid(0);  lumi_id lid(0);
  event_id nCmsEvent(0);
  //now code the super-sophisticated event loop.
  const unsigned nEvents=theChain->GetEntries();
  _globalEventCheckerSet.clear();
  ProgressMonitor pm(nEvents);
  
  for (unsigned i=0;i<nEvents;++i){
    if (!pm.Update()) break;
    theChain->GetEntry(i);
    nCmsEvent=metadata->nEvent;
    rid=metadata->nRun;
    lid=metadata->nLumi;
    EventId tmpId(rid,lid,nCmsEvent);
    if (_globalEventCheckerSet.find(tmpId)!=_globalEventCheckerSet.end()){
      cerr<<"Duplicate Event found!!! "<<endl;
      cout<<tmpId<<endl;
      exit(1);
    }
    else _globalEventCheckerSet.insert(tmpId);
  }
  
  cout<<"RESULT: No duplicate events found."<<endl;
  return 0;
}

