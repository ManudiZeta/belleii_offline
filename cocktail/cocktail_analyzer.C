#include "TFile.h"
#include <Riostream.h>
#include "TCanvas.h"
#include "TH1D.h"
#include "TTree.h"
#include "TH2F.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TString.h"

void imgen()
{
    gStyle->SetOptStat(0);
    TFile myf  ="../../../15012026_nog.root" ;
    
    TTree *tree = (TTree*)myf.Get("tree");
    TCanvas *tela = new TCanvas();
    
    tree->Draw("vpho_r_mRecoil>>h1(200,0,2)","");
    tree->Draw("vpho_r_mRecoil>>h2(200,0,2)","nROE_Charged__bo__bc == 0 && alpha <0.35");
    tree->Draw("vpho_r_mRecoil>>h3(200,0,2)","nROE_Charged__bo__bc == 0 && alpha <0.35 && pi_pionID>0.9 && roeE__bo__bc < 1");
    
    
    TH1* h1 = (TH1*)gDirectory->Get("h1");
    TH1* h2 = (TH1*)gDirectory->Get("h2");
    TH1* h3 = (TH1*)gDirectory->Get("h3");
    
    h1->SetXTitle("m_{recoil} [#frac{GeV}{c^{2}}]");
    h1->SetYTitle("counts");
    h1->SetTitle("recoil mass of p+, #pi-");
    
    h1->SetLineColor(kBlue);
    h2->SetLineColor(kRed);
    h3->SetLineColor(kGreen);
    
    
    TLegend *leg = new TLegend();
    leg->AddEntry(h1, "No further cuts","l");
    leg->AddEntry(h2, "nROE_Charged = 0, #alpha <0.35","l");
    leg->AddEntry(h3, "nROE_Charged = 0, #alpha < 0.35, #pi_{ID} > 0.9, roeE < 1","l");
    
    h1->DrawCopy();
    h2->DrawCopy("same");
    h3->DrawCopy("same");
    leg->Draw("same");
    tela->SaveAs("images/mRecoil_cuts.pdf");
    
    myf.Close();
}

