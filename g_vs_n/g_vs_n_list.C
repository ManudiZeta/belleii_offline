#include "TFile.h"
#include <Riostream.h>
#include "TCanvas.h"
#include "TH1D.h"
#include "TTree.h"
#include "TH2F.h"
#include "TLegend.h"
#include "TStyle.h"

void g_vs_n(bool choice)
{
    gStyle->SetOptStat(1);
    string in_1, in_2;
    TFile *myf_1 = nullptr;
    TFile *myf_2 = nullptr;
    
    if (choice == 0)
    {
        in_1 = "../../../vpho_std_isr_n_REC.root";
        in_2 = "../../../vpho_std_isr_g_REC.root";
    }
    
    else
    {
        in_1 = "../../../vpho_std_isr_n_REC_kin.root";
        in_2 = "../../../vpho_std_isr_g_REC_kin.root";
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
        myf_1 = new TFile("../../../vpho_std_isr_n_REC.root");
        myf_2 = new TFile("../../../vpho_std_isr_g_REC.root");
    }
    
    else
    {
        myf_1 = new TFile("../../../vpho_std_isr_n_REC_kin.root");
        myf_2 = new TFile("../../../vpho_std_isr_g_REC_kin.root");
    }
    
    TTree *tree_1 = (TTree*)myf_1->Get("tree");
    TTree *tree_2 = (TTree*)myf_2->Get("tree");
    
    TCanvas *c1 = new TCanvas("c1", "c1",800,600);
    
    tree_1->Draw("vpho_r_pRecoil-nbar_mcP>>histo1(100,-1,1)","nbar_mcPDG == -2112","goff");
    tree_2->Draw("vpho_r_pRecoil-nbar_mcP>>histo2(100,-1,1)","nbar_mcPDG == -2112","goff");
    
    delete c1;
    
    TH1 *histo1 = (TH1D*)gDirectory->Get("histo1");
    TH1 *histo2 = (TH1D*)gDirectory->Get("histo2");
    
    double mean_1 = histo1->GetMean();
    double devstd_1 = histo1->GetStdDev();
    double entries_1 = histo1->GetEntries();
    
    double mean_2 = histo2->GetMean();
    double devstd_2 = histo2->GetStdDev();
    double entries_2 = histo2->GetEntries();
    
    
    cout<<"entries_1 = "<<entries_1<<"|mean_1 = "<<mean_1<<"|devstd_1 = "<<devstd_1<<endl;
    cout<<"entries_2 = "<<entries_2<<"|mean_2 = "<<mean_2<<"|devstd_2 = "<<devstd_2<<endl;
    //histo1->Scale(1.0 / histo1->Integral());
    //histo2->Scale(1.0 / histo2->Integral());
 
    
    double max1 = histo1->GetBinContent(histo1->GetMaximumBin());
    cout<<"max1 = "<<max1<<endl;
    double max2 = histo2->GetBinContent(histo2->GetMaximumBin());
    cout<<"max2 = "<<max2<<endl;
    double max = (max1 > max2) ? max1 : max2;
    cout<<"max = "<<max<<endl;
    
    histo1->SetMaximum(max + 0.1*max);
    histo2->SetMaximum(max + 0.1*max);
    
    histo1->SetLineColor(kBlue);
    histo2->SetLineColor(kRed);
    
    histo1->GetXaxis()->SetTitle("#DeltaP [GeV]");
    histo1->GetYaxis()->SetTitle("counts []");
    
    histo1->SetTitle("#DeltaP comparison in n e g hp");
    
    cout<<"NEntries_1 = "<<histo1->GetEntries()<<endl;
    cout<<"NEntries_2 = "<<histo2->GetEntries()<<endl;
    
    TLegend *leg = new TLegend(0.6,0.6,0.78,0.78);
    leg->AddEntry(histo1,"n list (histo1_copy)","l");
    leg->AddEntry(histo2,"#gamma list (histo2_copy)","l");
    
    TCanvas *tela = new TCanvas("tela", "tela");
    
    histo1->DrawCopy("HIST");
    histo2->DrawCopy("HIST SAMES");
    leg->Draw("SAME");
    
    tela->Update();
    if (choice == 0)
    {
        tela->SaveAs("images/isr_g_vs_n_deltaP.pdf");
    }
    
    else
    {
        tela->SaveAs("images/isr_g_vs_n_deltaP_kin.pdf");
    }
    
}

void nosel_vs_sel(bool choice)
{
    gStyle->SetOptStat(0);
    string in_1, in_2;
    TFile *myf_1 = nullptr;
    TFile *myf_2 = nullptr;
    
    if (choice == 0)
    {
        in_1 = "../../../vpho_std_isr_n_REC.root";
    }
    
    else
    {
        in_1 = "../../../vpho_std_isr_n_REC_kin.root";
    }
    
    ifstream in_f1(in_1);
    
    if(!in_f1)
    {
        cout<<"Selected root file doesn't exist. Please, generate it. \n";
        return;
    }
    in_f1.close();
    
    if (choice == 0)
    {
        myf_1 = new TFile("../../../vpho_std_isr_n_REC.root");
    }
    
    else
    {
        myf_1 = new TFile("../../../vpho_std_isr_n_REC_kin.root");
    }
    
    TTree *tree_1 = (TTree*)myf_1->Get("tree");
    
    TCanvas *c1 = new TCanvas("c1", "c1",800,600);
    
    tree_1->Draw("nbar_clusterNHits>>histo1(100,0,70)","","goff");
    tree_1->Draw("nbar_clusterNHits>>histo2(100,0,70)","nbar_mcPDG == -2112","goff");
    
    delete c1;
    
    TH1 *histo1 = (TH1D*)gDirectory->Get("histo1");
    TH1 *histo2 = (TH1D*)gDirectory->Get("histo2");
        
    histo1->Scale(1.0 / histo1->Integral());
    histo2->Scale(1.0 / histo2->Integral());
 
    
    double max1 = histo1->GetBinContent(histo1->GetMaximumBin());
    cout<<"max1 = "<<max1<<endl;
    double max2 = histo2->GetBinContent(histo2->GetMaximumBin());
    cout<<"max2 = "<<max2<<endl;
    double max = (max1 > max2) ? max1 : max2;
    cout<<"max = "<<max<<endl;
    
    histo1->SetMaximum(max + 0.1*max);
    histo2->SetMaximum(max + 0.1*max);
    
    histo1->SetLineColor(kBlue);
    histo2->SetLineColor(kRed);
    
    histo1->GetXaxis()->SetTitle("clusterNHits []");
    histo1->GetYaxis()->SetTitle("counts []");
    
    histo1->SetTitle("clusterNHits comparison in not_sel  e sel");
    
    cout<<"NEntries_1 = "<<histo1->GetEntries()<<endl;
    cout<<"NEntries_2 = "<<histo2->GetEntries()<<endl;
    
    TLegend *leg = new TLegend(0.6,0.6,0.78,0.78);
    leg->AddEntry(histo1,"nbar_mcPDG = all","l");
    leg->AddEntry(histo2,"nbar_mcPDG = -2112","l");
    
    TCanvas *tela = new TCanvas("tela", "tela");
    
    histo1->DrawCopy("HIST");
    histo2->DrawCopy("HIST SAME");
    leg->Draw("SAME");
    
    tela->Update();
    if (choice == 0)
    {
        tela->SaveAs("images/isr_nosel_vs_sel_clusterNHits.pdf");
    }
    
    else
    {
        tela->SaveAs("images/isr_nosel_vs_sel_clusterNHits_kin.pdf");
    }
    
}
