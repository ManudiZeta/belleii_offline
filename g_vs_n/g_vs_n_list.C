#include "TFile.h"
#include <Riostream.h>
#include "TCanvas.h"
#include "TH1D.h"
#include "TTree.h"
#include "TH2F.h"
#include "TLegend.h"
#include "TStyle.h"

void g_vs_n_theta(bool choice)
{
    gStyle->SetOptStat(0);
    string in_1, in_2;
    TFile *myf_1 = nullptr;
    TFile *myf_2 = nullptr;
    
    if (choice == 0)
    {
        in_1 = "../../root_file/nbar_recoil/vpho_p_pi_n.root";
        in_2 = "../../root_file/nbar_recoil/vpho_p_pi_nbg.root";
    }
    
    else
    {
        in_1 = "../../root_file/isr/vpho_isr_gamma_REC.root";
        in_2 = "../../root_file/isr/vpho_isr_nbg_gamma_REC.root";
    }
    
    ifstream in_f1(in_1);
    ifstream in_f2(in_2);
    
    if(!in_f1 | !in_f2)
    {
        cout<<"Selected root file doesn't exist. Please, generate it. \n";
        return;
    }
    in_f1.close();
    in_f2.close();
    
    if (choice == 0)
    {
        myf_1 = new TFile("../../root_file/nbar_recoil/vpho_p_pi_n.root");
        myf_2 = new TFile("../../root_file/nbar_recoil/vpho_p_pi_nbg.root");
    }
    
    else
    {
        myf_1 = new TFile("../../root_file/isr/vpho_isr_gamma_REC.root");
        myf_2 = new TFile("../../root_file/isr/vpho_isr_nbg_gamma_REC.root");
    }
    
    TTree *tree_1 = (TTree*)myf_1->Get("tree");
    TTree *tree_2 = (TTree*)myf_2->Get("tree");
    
    TCanvas *c1 = new TCanvas("c1", "c1",800,600);
    
    tree_1->Draw("nbar_theta>>histo1(50,0,3.2)","","goff");
    tree_2->Draw("nb_gamma_theta >> histo2(50,0,3.2)","","goff");
    
    delete c1;
    
    TH1 *histo1 = (TH1D*)gDirectory->Get("histo1");
    TH1 *histo2 = (TH1D*)gDirectory->Get("histo2");
    
    
    histo1->Scale(1.0 / histo1->Integral());
    histo2->Scale(1.0 / histo2->Integral());
    
    histo1->SetLineColor(kBlue);
    histo2->SetLineColor(kRed);
    
    histo1->GetXaxis()->SetTitle("#theta [rad]");
    histo1->GetYaxis()->SetTitle("counts []");
    
    if(choice == 0) {histo1->SetTitle("nbar list (PHSP #gamma)");}
    else {histo1->SetTitle("nbar list (ISR #gamma)");}
    
    cout<<"NEntries_1 = "<<histo1->GetEntries()<<endl;
    cout<<"NEntries_2 = "<<histo2->GetEntries()<<endl;
    
    TLegend *leg = new TLegend(0.6,0.6,0.78,0.78);
    leg->AddEntry(histo1,"n list","l");
    leg->AddEntry(histo2,"#gamma list","l");
    
    TCanvas *tela = new TCanvas("tela", "tela");
    
    histo1->DrawCopy("HIST");
    histo2->DrawCopy("HIST SAME");
    leg->Draw("SAME");
    
    tela->Update();
    if (choice == 0)
    {
        tela->SaveAs("images/phsp_g_vs_n_theta.pdf");
    }
    
    else
    {
        tela->SaveAs("images/isr_g_vs_n_theta.pdf");
    }
    
}

void g_vs_n_mRecoil(bool choice)
{
    gStyle->SetOptStat(0);
    string in_1, in_2;
    TFile *myf_1 = nullptr;
    TFile *myf_2 = nullptr;
    
    if (choice == 0)
    {
        in_1 = "../../root_file/nbar_recoil/vpho_p_pi_n.root";
        in_2 = "../../root_file/nbar_recoil/vpho_p_pi_nbg.root";
    }
    
    else
    {
        in_1 = "../../root_file/isr/vpho_isr_gamma_REC.root";
        in_2 = "../../root_file/isr/vpho_isr_nbg_gamma_REC.root";
    }
    
    ifstream in_f1(in_1);
    ifstream in_f2(in_2);
    
    if(!in_f1 | !in_f2)
    {
        cout<<"Selected root file doesn't exist. Please, generate it. \n";
        return;
    }
    in_f1.close();
    in_f2.close();
    
    if (choice == 0)
    {
        myf_1 = new TFile("../../root_file/nbar_recoil/vpho_p_pi_n.root");
        myf_2 = new TFile("../../root_file/nbar_recoil/vpho_p_pi_nbg.root");
    }
    
    else
    {
        myf_1 = new TFile("../../root_file/isr/vpho_isr_gamma_REC.root");
        myf_2 = new TFile("../../root_file/isr/vpho_isr_nbg_gamma_REC.root");
    }
    
    TTree *tree_1 = (TTree*)myf_1->Get("tree");
    TTree *tree_2 = (TTree*)myf_2->Get("tree");
    
    TCanvas *c1 = new TCanvas("c1", "c1",800,600);
    
    tree_1->Draw("vpho_mRecoil>>histo1(50,0,2.)","","goff");
    tree_2->Draw("vpho_mRecoil >> histo2(50,0,2.)","","goff");
    
    delete c1;
    
    TH1 *histo1 = (TH1D*)gDirectory->Get("histo1");
    TH1 *histo2 = (TH1D*)gDirectory->Get("histo2");
    
    
    histo1->Scale(1.0 / histo1->Integral());
    histo2->Scale(1.0 / histo2->Integral());
    
    histo1->SetLineColor(kBlue);
    histo2->SetLineColor(kRed);
    
    histo1->GetXaxis()->SetTitle("mRecoil [GeV]");
    histo1->GetYaxis()->SetTitle("counts []");
    
    if(choice == 0) {histo1->SetTitle("nbar list (PHSP #gamma)");}
    else {histo1->SetTitle("nbar list (ISR #gamma)");}
    
    cout<<"NEntries_1 = "<<histo1->GetEntries()<<endl;
    cout<<"NEntries_2 = "<<histo2->GetEntries()<<endl;
    
    TLegend *leg = new TLegend(0.6,0.6,0.78,0.78);
    leg->AddEntry(histo1,"n list","l");
    leg->AddEntry(histo2,"#gamma list","l");
    
    TCanvas *tela = new TCanvas("tela", "tela");
    
    histo1->DrawCopy("HIST");
    histo2->DrawCopy("HIST SAME");
    leg->Draw("SAME");
    
    tela->Update();
    if (choice == 0)
    {
        tela->SaveAs("images/phsp_g_vs_n_mRecoil.pdf");
    }
    
    else
    {
        tela->SaveAs("images/isr_g_vs_n_mRecoil.pdf");
    }
    
}

