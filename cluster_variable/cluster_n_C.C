#include "TFile.h"
#include <Riostream.h>
#include "TCanvas.h"
#include "TH1D.h"
#include "TTree.h"
#include "TH2F.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TString.h"

void super ()
{
    gStyle->SetOptStat(1);
    string in_1, in_2;
    TFile *myf_1 = nullptr;
    TFile *myf_2 = nullptr;
    
    
    in_1 = "../../../vpho_std_isr_n_REC_merge100k_kin.root";
    in_2 = "../../../vpho_std_isr_g_REC_merge100k_kin.root";
    
    ifstream in_f1(in_1);
    ifstream in_f2(in_2);
    
    if(!in_f1 || !in_f2)
    {
        cout<<"Selected root file doesn't exist. Please, generate it. \n";
        return;
    }
    in_f1.close();
    
    myf_1 = new TFile("../../../vpho_std_isr_n_REC_merge100k_kin.root");
    myf_2 = new TFile("../../../vpho_std_isr_g_REC_merge100k_kin.root");
    
    TTree *tree_1 = (TTree*)myf_1->Get("tree");
    TTree *tree_2 = (TTree*)myf_2->Get("tree");
    
    TCanvas *c1 = new TCanvas("c1", "c1",800,600);
    TString var = "nbar_clusterAbsZernikeMoment51";
    TString drawExpr1 = var + ">>histo1(128,0,1.2)";
    TString drawExpr2 = var + ">>histo2(128,0,1.2)";
    tree_1->Draw(drawExpr1, "nbar_clusterNHits>1", "goff");
    tree_2->Draw(drawExpr2, "nbar_clusterNHits>1", "goff");
    
    
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
    
    histo1->Scale(1.0 / histo1->Integral());
    histo2->Scale(1.0 / histo2->Integral());
    
    
    double max1 = histo1->GetBinContent(histo1->GetMaximumBin());
    cout<<"max1 = "<<max1<<endl;
    double max2 = histo2->GetBinContent(histo2->GetMaximumBin());
    cout<<"max2 = "<<max2<<endl;
    double max = (max1 > max2) ? max1 : max2;
    //double max = max1;
    cout<<"max = "<<max<<endl;
    
    histo1->SetMaximum(max + 0.1*max);
    histo2->SetMaximum(max + 0.1*max);
    
    histo1->SetLineColor(kBlue);
    histo2->SetLineColor(kRed);
    //TString title_x = var + "[rad]";
    TString title_x = "|Z_{51}|[]";
    histo1->GetXaxis()->SetTitle(title_x);
    histo1->GetYaxis()->SetTitle("counts []");
    
    TString title = var + " comparison in n vs g list";
    histo1->SetTitle(title);
    
    
    cout<<"NEntries_1 = "<<histo1->GetEntries()<<endl;
    cout<<"NEntries_2 = "<<histo2->GetEntries()<<endl;
    
    TLegend *leg = new TLegend(0.6,0.6,0.78,0.78);
    leg->AddEntry(histo1,"n list (histo1_copy)","l");
    leg->AddEntry(histo2,"g list (histo2_copy)","l");
    
    TCanvas *tela = new TCanvas("tela", "tela");
    
    histo1->DrawCopy("HIST");
    histo2->DrawCopy("HIST SAMES");
    leg->Draw("SAME");
    
    TString title_out = "images/isr_" + var + "_NHitsSEL.pdf";
    tela->SaveAs(title_out);
    
    
}

