#include "TFile.h"
#include <Riostream.h>
#include "TCanvas.h"
#include "TH1D.h"
#include "TTree.h"
#include "TH2F.h"

void phsp_vs_isr()
{

    string in_1 = "../root_file/isr/isr_list.root";
    string in_2 = "../root_file/nbar_recoil/phsp_gamma_out.root";
    
    ifstream in_f1(in_1);
    ifstream in_f2(in_2);
    
    if(!in_f1 | !in_f2)
    {
        cout<<"Selected root file doesn't exist. Please, generate it. \n";
        return;
    }
    in_f1.close();
    in_f2.close();
    
    TFile myf_1("../root_file/isr/isr_list.root");
    TFile myf_2("../root_file/nbar_recoil/phsp_gamma_out.root");
    
    TTree *tree_1 = (TTree*)myf_1.Get("tree");
    TTree *tree_2 = (TTree*)myf_2.Get("tree");
    
    TCanvas *tela = new TCanvas();
    tela->cd();
    
    tree_1->Draw("theta"," mcISR == 1");
    TH2F *htemp = (TH2F*)gPad->GetPrimitive("htemp");
    htemp->GetXaxis()->SetTitle("#theta [rad]");
    htemp->GetYaxis()->SetTitle("counts []");
    htemp->SetTitle("");
    
}

