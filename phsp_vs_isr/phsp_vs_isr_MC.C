#include "TFile.h"
#include <Riostream.h>
#include "TCanvas.h"
#include "TH1D.h"
#include "TTree.h"
#include "TH2F.h"
#include "TLegend.h"
#include "TStyle.h"

void gamma_phsp_vs_isr()
{
    
    gStyle->SetOptStat(0);
    string in_1 = "../../root_file/isr/isr_list_gamma_MC.root";
    string in_2 = "../../root_file/nbar_recoil/phsp_list_gamma_MC.root";
    
    ifstream in_f1(in_1);
    ifstream in_f2(in_2);
    
    if(!in_f1 | !in_f2)
    {
        cout<<"Selected root file doesn't exist. Please, generate it. \n";
        return;
    }
    in_f1.close();
    in_f2.close();
    
    TFile myf_1("../../root_file/isr/isr_list_gamma_MC.root");
    TFile myf_2("../../root_file/nbar_recoil/phsp_list_gamma_MC.root");
    
    TTree *tree_1 = (TTree*)myf_1.Get("tree");
    TTree *tree_2 = (TTree*)myf_2.Get("tree");
    
    TCanvas *c1 = new TCanvas("c1", "c1",800,600);
    
    tree_1->Draw("theta>>histo1(50,0,3.2)","mcISR == 1","goff");
    tree_2->Draw("theta >> histo2(50,0,3.2)","genMotherPDG == 300553","goff");
    
    delete c1;
    
    TH1 *histo1 = (TH1D*)gDirectory->Get("histo1");
    TH1 *histo2 = (TH1D*)gDirectory->Get("histo2");
    
    
    histo1->Scale(1.0 / histo1->Integral());
    histo2->Scale(1.0 / histo2->Integral());
    
    histo1->SetLineColor(kBlue);
    histo2->SetLineColor(kRed);
    
    histo1->GetXaxis()->SetTitle("#theta [rad]");
    histo1->GetYaxis()->SetTitle("counts []");
    histo1->SetTitle("#gamma list from MC");
    
    cout<<"NEntries_1 = "<<histo1->GetEntries()<<endl;
    cout<<"NEntries_2 = "<<histo2->GetEntries()<<endl;
    
    TLegend *leg = new TLegend(0.6,0.6,0.78,0.78);
    leg->AddEntry(histo1," ISR ","l");
    leg->AddEntry(histo2," PHSP ","l");
    
    TCanvas *tela = new TCanvas("tela", "tela");
    
    histo1->DrawCopy("HIST");
    histo2->DrawCopy("HIST SAME");
    leg->Draw("SAME");
    
    tela->Update();
    tela->SaveAs("images/phsp_vs_isr_gammaList_MC.pdf");
    
    
}

void nbar_phsp_vs_isr_MC()
{
    
    gStyle->SetOptStat(0);
    string in_1 = "../../root_file/isr/isr_list_n_MC.root";
    string in_2 = "../../root_file/nbar_recoil/phsp_list_n_MC.root";
    
    ifstream in_f1(in_1);
    ifstream in_f2(in_2);
    
    if(!in_f1 | !in_f2)
    {
        cout<<"Selected root file doesn't exist. Please, generate it. \n";
        return;
    }
    in_f1.close();
    in_f2.close();
    
    TFile myf_1("../../root_file/isr/isr_list_n_MC.root");
    TFile myf_2("../../root_file/nbar_recoil/phsp_list_n_MC.root");
    
    TTree *tree_1 = (TTree*)myf_1.Get("tree");
    TTree *tree_2 = (TTree*)myf_2.Get("tree");
    
    TCanvas *c1 = new TCanvas("c1", "c1",800,600);
    
    tree_1->Draw("theta>>histo1(50,0,3.2)","mcPDG == -2112","goff");
    tree_2->Draw("theta >> histo2(50,0,3.2)","genMotherPDG == 300553","goff");
    
    delete c1;
    
    TH1 *histo1 = (TH1D*)gDirectory->Get("histo1");
    TH1 *histo2 = (TH1D*)gDirectory->Get("histo2");
    
    
    histo1->Scale(1.0 / histo1->Integral());
    histo2->Scale(1.0 / histo2->Integral());
    
    histo1->SetLineColor(kBlue);
    histo2->SetLineColor(kRed);
    
    histo1->GetXaxis()->SetTitle("#theta [rad]");
    histo1->GetYaxis()->SetTitle("counts []");
    histo1->SetTitle("#bar{n} list from MC");
    
    cout<<"NEntries_1 = "<<histo1->GetEntries()<<endl;
    cout<<"NEntries_2 = "<<histo2->GetEntries()<<endl;
    
    TLegend *leg = new TLegend(0.6,0.6,0.78,0.78);
    leg->AddEntry(histo1," ISR ","l");
    leg->AddEntry(histo2," PHSP ","l");
    
    TCanvas *tela = new TCanvas("tela", "tela");
    
    histo1->DrawCopy("HIST");
    histo2->DrawCopy("HIST SAME");
    leg->Draw("SAME");
    
    tela->Update();
    tela->SaveAs("images/phsp_vs_isr_nList_MC.pdf");
    
    
}

