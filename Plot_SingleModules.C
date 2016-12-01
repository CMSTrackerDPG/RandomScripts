#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <TROOT.h>
#include <TStyle.h>
#include "TFile.h"
#include "THStack.h"
#include "TH1D.h"
#include "TDirectoryFile.h"
#include "TDirectory.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TKey.h"
#include "TObject.h"
#include "TLegend.h"
#include "TRint.h"
#include "TFileIter.h"


void Plot_SingleModules(string filename, string modulelist,string dirlist, int runnumber){

  //int Plot(string filename, string modulelist) {

  gROOT->SetStyle("Plain");

  std::vector<string> dirs;

  //fill the vector with the correct dir
  std::ifstream dirstr;
  string tmp;

  TCanvas c1("c1","c1",1600,900);
  
  //c1.SetBatch(kTRUE);
  //c1.SetLogy(1);
  c1.SetGridy(1);

  dirstr.open(dirlist);
  //dirstr.open("/afs/cern.ch/user/f/fiori/public/SiStripSubdirs_SingleModulePlots.txt");
  
  while(1){

    dirstr >> tmp ;

    string address= "DQMData/Run " + to_string(runnumber) + "/SiStrip/Run summary/" + tmp;
    dirs.push_back(address);

    if (!dirstr.good()) break;
    
  }

  TFile* fin;
  fin=TFile::Open(filename.c_str());

  string detid;

  std::ifstream inmodules(modulelist.c_str());

  while(1){

    //cout << "while" << endl;

    inmodules >> detid;
    if (!inmodules.good()) break;

    bool found=false;
    int index=0;

    for (int i=0; i< dirs.size(); i++){

      TDirectory* tmpdir;
      tmpdir=(TDirectory*)fin->Get(dirs[i].c_str());
      if (!tmpdir){ cout << "cannot open dir " << dirs[i] << endl; return;} 
      //else cout << "dir found " << dirs[i] << endl;

      TKey *key;
      TIter next(tmpdir->GetListOfKeys());

      if (found) break;

      while ((key = (TKey *) next())) {

	string dname= string(key->GetName());
	if (dname.find(detid)!=std::string::npos) {
	  //cout << dname << endl;
	  found=true;
	  index=i;
	  break;
	} 
      }
    }
    

    string hn="NumberOfDigisPerStrip__det__" + detid;

    string complete=dirs[index] + "/module_" + detid +"/"+hn;

    c1.SetLogy();

    TH1D* histo;

    //cout << "AAAAAA " << complete << endl;
    histo=(TH1D*) fin->Get(complete.c_str());

    if (!histo) {cout << "Cannot find histo " << complete << endl; return;}

    histo->Draw();
    double max=histo->GetMaximum()*1.2;

    histo->GetYaxis()->SetRangeUser(.5,max);

    TLine l;
     
    l.SetLineColor(4);
    l.SetLineStyle(2);
    l.SetLineWidth(3);
    
    l.DrawLine(128,0,128,max);
    l.DrawLine(256,0,256,max);
    l.DrawLine(384,0,384,max);
    l.DrawLine(384,0,384,max);
    l.DrawLine(512,0,512,max);
    l.DrawLine(640,0,640,max);

    hn=hn+".png";
    c1.SaveAs(hn.c_str());
  }
}

