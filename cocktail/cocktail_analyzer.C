#include "TFile.h"
#include <Riostream.h>
#include "TCanvas.h"
#include "TH1D.h"
#include "TTree.h"
#include "TH2F.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TString.h"

void imgen(bool choice)
{
    
    TString name_file = (choice == 0) ? "../../../collection__output.root" : "../../../nog_out_05012026_2.root";
    
    if(name_file == "../../../collection__output.root")
    {
        cout<< "File: "<<name_file<<endl;
        gStyle->SetOptStat(1);
        ifstream in_file(name_file);
        
        if(!in_file)
        {
            cout<<"The root file doesn't exist. Generate it. \n";
            return;
        }
        in_file.close();
        TFile myf(name_file);
        
        TTree *tree = (TTree*)myf.Get("tree");
        TCanvas *tela = new TCanvas();
        
        tree->Draw("vpho_r_mRecoil>>h(100,0,2)","vpho_r_mRecoil>0 && vpho_r_mRecoil<2 && nROE_Charged__bo__bc == 0");
        TH1* h = (TH1*)gDirectory->Get("h");
        h->SetXTitle("m_{recoil} [GeV]");
        h->SetYTitle("counts []");
        h->SetTitle("Recoil mass of p+, #pi-, #gamma");
        tela->SaveAs("images/ranked_gamma/pdf/mRecoil_1.pdf");
        tela->SaveAs("images/ranked_gamma/root/mRecoil_1.root");
        
        myf.Close();
        delete tela;
    }
    
    
    
    
    else if(name_file == "../../../nog_out_05012026_2.root")
    {
        cout<< "File: "<<name_file<<endl;
        gStyle->SetOptStat(1);
        ifstream in_file(name_file);
        
        if(!in_file)
        {
            cout<<"The root file doesn't exist. Generate it. \n";
            return;
        }
        in_file.close();
        TFile myf(name_file);
        
        TTree *tree = (TTree*)myf.Get("tree");
        TCanvas *tela = new TCanvas();
        
        tree->Draw("vpho_r_mRecoil>>h(100,0,2)","vpho_r_mRecoil>0 && vpho_r_mRecoil<2 && nROE_Charged__bo__bc == 0 && alpha<0.35 && nbar_mcPDG == -2112");
        TH1* h = (TH1*)gDirectory->Get("h");
        h->SetXTitle("m_{recoil} [GeV]");
        h->SetYTitle("counts []");
        h->SetTitle("Recoil mass of p+, #pi-");
        tela->SaveAs("images/ranked_nogamma/pdf/mRecoil_3.pdf");
        tela->SaveAs("images/ranked_nogamma/root/mRecoil_3.root");
        
        myf.Close();
        delete tela;
        
    }
}

