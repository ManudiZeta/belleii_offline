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

void genMother(TString var, TString x1, TString x2)
{
    gStyle->SetOptStat(0);
    TFile *myf_1 = new TFile("../../../vpho_nog_n_REC_merge100k_09012026.root");
    
    TTree *tree_1 = (TTree*)myf_1->Get("tree");
    TTree *tree_2 = (TTree*)myf_1->Get("tree");
    TTree *tree_3 = (TTree*)myf_1->Get("tree");
    
    TCanvas *c1 = new TCanvas("c1", "c1",800,600);
    
    
    
    tree_1->Draw(var + ">>histo1(100," + x1 + "," + x2 + ")", "", "goff");
    tree_2->Draw(var + ">>histo2(100," + x1 + "," + x2 + ")","!TMath::IsNaN(nbar_mcPDG)", "goff");
    tree_3->Draw(var + ">>histo3(100," + x1 + "," + x2 + ")","!TMath::IsNaN(nbar_mcPDG) && nbar_genMotherPDG != -2112","goff");

        
    delete c1;
    TH1 *histo1 = (TH1D*)gDirectory->Get("histo1");
    TH1 *histo2 = (TH1D*)gDirectory->Get("histo2");
    TH1 *histo3 = (TH1D*)gDirectory->Get("histo3");

    
    histo1->SetLineColor(kBlue);
    histo2->SetLineColor(kRed);
    histo3->SetLineColor(kGreen);
    
    
    histo1->GetXaxis()->SetTitle(var);
    histo1->GetYaxis()->SetTitle("counts");
    
    
    TString title = "";
    histo1->SetTitle(title);
    
    
    cout<<"NEntries_1 = "<<histo1->GetEntries()<<endl;
    cout<<"NEntries_2 = "<<histo2->GetEntries()<<endl;
    cout<<"NEntries_3 = "<<histo3->GetEntries()<<endl;
    
    TLegend *leg = new TLegend(0.6,0.6,0.78,0.78);
    leg->AddEntry(histo1,"No cuts","l");
    leg->AddEntry(histo2,"nbar_mcPDG = IsNaN","l");
    leg->AddEntry(histo3,"nbar_mcPDG = IsNaN + nbar_genMotherPDG != -2112","l");
    
    TCanvas *tela = new TCanvas("tela", "tela");
    
    histo1->DrawCopy("HIST");
    histo2->DrawCopy("HIST SAMES");
    histo3->DrawCopy("HIST SAMES");
    leg->Draw("SAME");
    
    TString title_out = var + ".gif";
    tela->SaveAs(title_out);
    
}


void clusterE()
{
    gStyle->SetOptStat(0);
    TFile *myf_1 = new TFile("../../../vpho_nog_n_REC_merge100k_09012026.root");
    
    TTree *tree_1 = (TTree*)myf_1->Get("tree");
    TTree *tree_2 = (TTree*)myf_1->Get("tree");
    TTree *tree_3 = (TTree*)myf_1->Get("tree");
    
    TCanvas *c1 = new TCanvas("c1", "c1",800,600);
    
    tree_1->Draw("nbar_clusterE >> histo1(100,0,5)", "", "goff");
    tree_2->Draw("nbar_clusterE >> histo2(100,0,5)","!TMath::IsNaN(nbar_mcPDG)", "goff");
    tree_3->Draw("nbar_clusterE >> histo3(100,0,5)","!TMath::IsNaN(nbar_mcPDG) && nbar_genMotherPDG != -2112","goff");

        
    delete c1;
    TH1 *histo1 = (TH1D*)gDirectory->Get("histo1");
    TH1 *histo2 = (TH1D*)gDirectory->Get("histo2");
    TH1 *histo3 = (TH1D*)gDirectory->Get("histo3");

    
    histo1->SetLineColor(kBlue);
    histo2->SetLineColor(kRed);
    histo3->SetLineColor(kGreen);
    
    histo1->SetFillColor(kBlue);
    histo2->SetFillColor(kRed);
    histo3->SetFillColor(kGreen);
    
    TString title_x = "clusterE [GeV]";
    histo1->GetXaxis()->SetTitle(title_x);
    histo1->GetYaxis()->SetTitle("counts");
    
    
    TString title = "";
    histo1->SetTitle(title);
    
    
    cout<<"NEntries_1 = "<<histo1->GetEntries()<<endl;
    cout<<"NEntries_2 = "<<histo2->GetEntries()<<endl;
    cout<<"NEntries_3 = "<<histo3->GetEntries()<<endl;
    
    TLegend *leg = new TLegend(0.6,0.6,0.78,0.78);
    leg->AddEntry(histo1,"No additional cuts","l");
    leg->AddEntry(histo2,"nbar_mcPDG = IsNaN","l");
    leg->AddEntry(histo3,"nbar_mcPDG = IsNaN + nbar_genMotherPDG != -2112","l");
    
    TCanvas *tela = new TCanvas("tela", "tela");
    
    histo1->DrawCopy("HIST");
    histo2->DrawCopy("HIST SAMES");
    histo3->DrawCopy("HIST SAMES");
    leg->Draw("SAME");
    
    TString title_out = "clusterE.gif";
    tela->SaveAs(title_out);
    
}


