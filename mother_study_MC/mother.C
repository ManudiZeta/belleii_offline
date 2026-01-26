#include "TFile.h"
#include <Riostream.h>
#include "TCanvas.h"
#include "TH1D.h"
#include "TTree.h"
#include "TH2F.h"
#include "TMath.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TLine.h"
#include "TString.h"

void ancestor()
{
    gStyle->SetOptStat(0);
    TFile *myf_1 = new TFile("../../../mother_stud.root");
    
    TTree *tree = (TTree*)myf_1->Get("tree");
    
    TCanvas *c1 = new TCanvas("c1", "c1",800,600);
    
    tree->Draw("vpho_r_pRecoil>>h1(100,0,7)","","goff");
    tree->Draw("nbar_mcP>>h2(100,0,7)","","goff");
    tree->Draw("nbar_mcP>>h3(100,0,7)","nbar_mcPDG == -2112","goff");
    tree->Draw("nbar_varForFirstMCAncestorOfType_anti_n0_p>>h4(100,0,7)","","goff");

    
    TH1 *h1 = (TH1*)gDirectory->Get("h1");
    TH1 *h2 = (TH1*)gDirectory->Get("h2");
    TH1 *h3 = (TH1*)gDirectory->Get("h3");
    TH1 *h4 = (TH1*)gDirectory->Get("h4");
    
    TH1 *hsum = (TH1*)h1->Clone("hSum");
    hsum->Reset();          // parte da zero
    hsum->Add(h3);          // hSum = h1
    hsum->Add(h4);          // hSum = h1 + h2

    delete c1;
    
    h1->SetLineColor(kBlue);
    h2->SetLineColor(kRed);
    h3->SetLineColor(kGreen);
    h4->SetLineColor(kYellow);
    hsum->SetLineColor(kBlack);
    
    
    h1->GetXaxis()->SetTitle("#frac{GeV}{c}");
    h1->GetYaxis()->SetTitle("counts");
    
    
    TString title = "";
    h1->SetTitle(title);
    
    TLegend *leg = new TLegend(0.6,0.6,0.78,0.78);
    leg->AddEntry(h1,"Recoil momentum","l");
    leg->AddEntry(h2,"#bar{n} MC_p","l");
    leg->AddEntry(h3,"#bar{n} MC_p with mcPDG == -2112","l");
    leg->AddEntry(h4,"Ancestor momentum","l");
    leg->AddEntry(hsum,"Green + Yellow","l");
    
    TCanvas *tela = new TCanvas("tela", "tela");
    
    h1->DrawCopy("HIST");
    h2->DrawCopy("HIST SAMES");
    h3->DrawCopy("HIST SAMES");
    h4->DrawCopy("HIST SAMES");
    hsum->DrawCopy("HIST SAMES");
    leg->Draw("SAME");
    
    TString title_out = "momentum_ancestors_comparison.pdf";
    tela->SaveAs(title_out);
    
}


void delta_ancestor()
{
    gStyle->SetOptStat(1);
    TFile *myf_1 = new TFile("../../../mother_stud.root");
    
    TTree *tree = (TTree*)myf_1->Get("tree");
    
    TCanvas *c1 = new TCanvas("c1", "c1",800,600);
    
    tree->Draw("(vpho_r_pRecoil - nbar_mcP)>>h1(100,-1,1)","nbar_mcPDG == -2112","goff");
    tree->Draw("(vpho_r_pRecoil - nbar_varForFirstMCAncestorOfType_anti_n0_p)>>h2(100,-1,1)","!TMath::IsNaN(nbar_mcPDG)","goff");
    
    TH1 *h1 = (TH1*)gDirectory->Get("h1");
    TH1 *h2 = (TH1*)gDirectory->Get("h2");
    
    delete c1;
    
    h1->SetLineColor(kBlue);
    h2->SetLineColor(kRed);
    
    
    h1->GetXaxis()->SetTitle("#Deltap[#frac{GeV}{c}]");
    h1->GetYaxis()->SetTitle("counts");
    
    TString title = "";
    h1->SetTitle(title);
    
    TLegend *leg = new TLegend(0.6,0.6,0.78,0.78);
    leg->AddEntry(h1,"pRecoil - #bar{n}p_{MC} (mcPDG == -2112)","l");
    leg->AddEntry(h2,"pRecoil - ancestorP_{MC} (mcPDG != NaN)","l");
    
    TCanvas *tela = new TCanvas("tela", "tela");
    
    h1->DrawCopy("HIST");
    h2->DrawCopy("HIST SAMES");
    leg->Draw("SAME");
    
    TString title_out = "deltaP_ancestors.pdf";
    tela->SaveAs(title_out);
    
}

void cluster_ancestor()
{
    gStyle->SetOptStat(0);
    TFile *myf_1 = new TFile("../../../mother_stud.root");
    TString var [5] = {"nbar_clusterE","nbar_clusterNHits","nbar_clusterLAT","nbar_clusterSecondMoment","nbar_clusterAbsZernikeMoment51"};
    TString rate [5] = {"(192,0,7)","(128,0,100)","(192,0,1)","(192,0,39)","(192,0,1.2)"};
    
    
    for (int i = 1; i<2; i++)
    {
    
        TTree *tree = (TTree*)myf_1->Get("tree");
        
        TCanvas *c1 = new TCanvas("c1", "c1",800,600);

        // riempio usando Draw su istogrammi ESISTENTI
        tree->Draw(var[i] + ">>h1" + rate[i],"nbar_mcPDG == -2112", "goff");
        tree->Draw(var[i] + ">>h2" + rate[i],"TMath::IsNaN(nbar_mcPDG)", "goff");
        tree->Draw(var[i] + ">>h3" + rate[i],"nbar_hasAncestor_2112_1 == 0", "goff");
        tree->Draw(var[i] + ">>h4" + rate[i],"nbar_hasAncestor_2112_1 == 1", "goff");
        tree->Draw(var[i] + ">>h5" + rate[i],"nbar_hasAncestor_2112_1 == 2", "goff");
        
        TH1D *h1 = (TH1D*)gDirectory->Get("h1");
        TH1D *h2 = (TH1D*)gDirectory->Get("h2");
        TH1D *h3 = (TH1D*)gDirectory->Get("h3");
        TH1D *h4 = (TH1D*)gDirectory->Get("h4");
        TH1D *h5 = (TH1D*)gDirectory->Get("h5");
        

        delete c1;
        
        h1->SetLineColor(kBlue);
        h2->SetLineColor(kRed);
        h3->SetLineColor(kGreen);
        h4->SetLineColor(kYellow -6);
        h5->SetLineColor(kBlack);

        
       
        h1->Scale(1.0 / h1->Integral());
        h2->Scale(1.0 / h2->Integral());
        h3->Scale(1.0 / h3->Integral());
        h4->Scale(1.0 / h4->Integral());
        h5->Scale(1.0 / h5->Integral());
        
        
        
        h2->GetXaxis()->SetTitle(var[i]);
        h2->GetYaxis()->SetTitle("counts");
        
        TString title = "";
        h1->SetTitle(title);
        
        TLegend *leg = new TLegend(0.6,0.6,0.78,0.78);
        leg->AddEntry(h1,"nbar_mcPDG = -2112","l");
        leg->AddEntry(h2,"nbar_mcPDG = NaN","l");
        leg->AddEntry(h3,"Ancestor = 0 (no #bar{n} relatives)","l");
        leg->AddEntry(h4,"Ancestor = 1 (#bar{n} as mum)","l");
        //leg->AddEntry(h5,"Ancestor = 2 (#bar{n} as grand-mum)","l");
        
        
        auto tela = std::make_unique<TCanvas>("c1", "c1", 800, 600);
        
        
        h2->Draw("HIST");
        h1->Draw("HIST SAMES");
        h3->Draw("HIST SAMES");
        h4->Draw("HIST SAMES");

        //h5->Draw("HIST SAMES");
        
        leg->Draw("SAME");
        
        TString title_out = "cluster" + var [i] + "_norm.pdf";
        tela->SaveAs(title_out);
        
        delete tree;
        delete h1;
        delete h2;
        delete h3;
        delete h4;
        delete h5;
        delete leg;
        
        
    }
    
}
