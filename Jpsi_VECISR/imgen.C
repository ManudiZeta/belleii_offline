void imgen(int choice)
{
    if(choice == 0)
    {
        gStyle->SetOptStat(1);
        ifstream in_file("../../../vpho_Jpsi_isr_n_REC.root");
        
        if(!in_file)
        {
            cout<<"The root file doesn't exist. Generate it. \n";
            return;
        }
        in_file.close();
        TFile myf("../../../vpho_Jpsi_isr_n_REC.root");
        
        TTree *tree = (TTree*)myf.Get("tree");
        TCanvas *tela = new TCanvas();
        
        tree->Draw("vpho_r_mRecoil>>h(100,0,10)");
        TH1* h = (TH1*)gDirectory->Get("h");
        h->SetXTitle("m_{recoil} [GeV]");
        h->SetYTitle("counts []");
        h->SetTitle("Recoil mass of p+, #pi-, #gamma");
        tela->SaveAs("images/mRecoil_Jpsi.pdf");
        
        tree->Draw("gamma_mRecoil>>h(100,0,11)");
        h = (TH1*)gDirectory->Get("h");
        h->SetXTitle("m_{recoil} [GeV]");
        h->SetYTitle("counts []");
        h->SetTitle("Recoil mass of #gamma");
        tela->SaveAs("images/mRecoil_gamma_Jpsi.pdf");
        
        tree->Draw("vpho_r_pRecoil-nbar_mcP>>h(50,-0.5,0.5)","","colz");
        h = (TH1*)gDirectory->Get("h");
        h->SetXTitle("#DeltaP [rad]");
        h->SetYTitle("counts []");
        h->SetTitle("Momentum difference");
        tela->SaveAs("images/p_diff_Jpsi.pdf");
        
        tree->Draw("vpho_r_pRecoilTheta-nbar_theta>>h(40,-0.4,0.4)","","colz");
        h = (TH1*)gDirectory->Get("h");
        h->SetXTitle("#Delta#theta [rad]");
        h->SetYTitle("counts []");
        h->SetTitle("#theta difference");
        tela->SaveAs("images/theta_diff_Jpsi.pdf");
        
        gStyle->SetOptStat(0);
        
        tree->Draw("vpho_r_pRecoil:nbar_mcP","","colz");
        h = (TH2*)gDirectory->Get("h");
        h->SetXTitle("#bar{n} mcP [rad]");
        h->SetYTitle("pRecoil [GeV]");
        h->SetTitle("Momentum correlation");
        tela->SaveAs("images/p_corr_Jpsi.pdf");
        
        tree->Draw("vpho_r_pRecoilTheta:nbar_theta>>h(40,0,3.2,40,0,3.2)","","colz");
        h = (TH2*)gDirectory->Get("h");
        h->SetXTitle("#bar{n} #theta [rad]");
        h->SetYTitle("recoil #theta [rad]");
        h->SetTitle("#theta correlation");
        tela->SaveAs("images/theta_corr_Jpsi.pdf");
        
        tree->Draw("(vpho_r_pRecoil-nbar_mcP):vpho_r_pRecoil>>h(50,-3.,7.,50.,-3,7.)","","colz");
        h = (TH2*)gDirectory->Get("h");
        h->SetXTitle("#DeltaP [rad]");
        h->SetYTitle("pRecoil [GeV]");
        h->SetTitle("(pRecoil - nbar_mcPDG) vs pRecoil");
        tela->SaveAs("images/p_diff_corr_Jpsi.pdf");
                    
        tree->Draw("(vpho_r_pRecoil-nbar_mcP):vpho_r_pRecoil>>h(50,-3.,7.,50.,-3,7.)","nbar_mcPDG == -2112","colz");
        h = (TH2*)gDirectory->Get("h");
        h->SetXTitle("#DeltaP [rad]");
        h->SetYTitle("pRecoil [GeV]");
        h->SetTitle("(pRecoil - nbar_mcPDG) vs pRecoil");
        tela->SaveAs("images/p_diff_corr_Jpsi_nPDG.pdf");
        
        
        myf.Close();
        delete tela;
    }
    
    else if(choice == 1)
    {
        gStyle->SetOptStat(1);
        ifstream in_file("../../../vpho_Jpsi_isr_n_REC_kin.root");
        
        if(!in_file)
        {
            cout<<"The root file doesn't exist. Generate it. \n";
            return;
        }
        in_file.close();
        TFile myf("../../../vpho_Jpsi_isr_n_REC_kin.root");
        
        TTree *tree = (TTree*)myf.Get("tree");
        TCanvas *tela = new TCanvas();
        
        tree->Draw("vpho_r_mRecoil>>h(100,0.9395642,0.939566)");
        TH1* h = (TH1*)gDirectory->Get("h");
        h->SetXTitle("m_{recoil} [GeV]");
        h->SetYTitle("counts []");
        h->SetTitle("Recoil mass of p+, #pi-, #gamma kin");
        tela->SaveAs("images/mRecoil_Jpsi_kin.pdf");
        
        tree->Draw("gamma_mRecoil>>h(100,0,11)");
        h = (TH1*)gDirectory->Get("h");
        h->SetXTitle("m_{recoil} [GeV]");
        h->SetYTitle("counts []");
        h->SetTitle("Recoil mass of #gamma kin");
        tela->SaveAs("images/mRecoil_gamma_Jpsi_kin.pdf");
        
        tree->Draw("vpho_r_pRecoil-nbar_mcP>>h(50,-0.5,0.5)","","colz");
        h = (TH1*)gDirectory->Get("h");
        h->SetXTitle("#DeltaP [GeV]");
        h->SetYTitle("counts []");
        h->SetTitle("Momentum difference kin");
        tela->SaveAs("images/p_diff_Jpsi_kin.pdf");
        
        tree->Draw("vpho_r_pRecoilTheta-nbar_theta>>h(40,-0.4,0.4)","","colz");
        h = (TH1*)gDirectory->Get("h");
        h->SetXTitle("#Delta#theta [rad]");
        h->SetYTitle("counts []");
        h->SetTitle("#theta difference kin");
        tela->SaveAs("images/theta_diff_Jpsi_kin.pdf");
        
        gStyle->SetOptStat(0);
        
        tree->Draw("vpho_r_pRecoil:nbar_mcP","","colz");
        h = (TH2*)gDirectory->Get("h");
        h->SetXTitle("#bar{n} mcP [rad]");
        h->SetYTitle("pRecoil [GeV]");
        h->SetTitle("Momentum correlation kin");
        tela->SaveAs("images/p_corr_Jpsi_kin.pdf");
        
        tree->Draw("vpho_r_pRecoilTheta:nbar_theta>>h(40,0,3.2,40,0,3.2)","","colz");
        h = (TH2*)gDirectory->Get("h");
        h->SetXTitle("#bar{n} #theta [rad]");
        h->SetYTitle("recoil #theta [rad]");
        h->SetTitle("#theta correlation kin");
        tela->SaveAs("images/theta_corr_Jpsi_kin.pdf");
        
        tree->Draw("(vpho_r_pRecoil-nbar_mcP):vpho_r_pRecoil>>h(50,-3.,7.,50.,-3,7.)","","colz");
        h = (TH2*)gDirectory->Get("h");
        h->SetXTitle("#DeltaP [rad]");
        h->SetYTitle("pRecoil [GeV]");
        h->SetTitle("(pRecoil - nbar_mcPDG) vs pRecoil kin");
        tela->SaveAs("images/p_diff_corr_Jpsi_kin.pdf");
                    
        tree->Draw("(vpho_r_pRecoil-nbar_mcP):vpho_r_pRecoil>>h(50,-3.,7.,50.,-3,7.)","nbar_mcPDG == -2112","colz");
        h = (TH2*)gDirectory->Get("h");
        h->SetXTitle("#DeltaP [rad]");
        h->SetYTitle("pRecoil [GeV]");
        h->SetTitle("(pRecoil - nbar_mcPDG) vs pRecoil kin");
        tela->SaveAs("images/p_diff_corr_Jpsi_nPDG_kin.pdf");
        
        myf.Close();
        delete tela;
    }
    
    else if(choice == 2)
    {
        gStyle->SetOptStat(1);
        ifstream in_file("../../../isrVEC_list_gamma_MC.root");
        
        if(!in_file)
        {
            cout<<"The root file doesn't exist. Generate it. \n";
            return;
        }
        in_file.close();
        TFile myf("../../../isrVEC_list_gamma_MC.root");
        
        
        TTree *tree = (TTree*)myf.Get("tree");
        TCanvas *tela = new TCanvas();
        
        tree->Draw("p>>h(100,0,7)");
        TH1* h = (TH1*)gDirectory->Get("h");
        h->SetXTitle("p [GeV]");
        h->SetYTitle("counts []");
        h->SetTitle("ISR #gamma momentum from generator");
        tela->SaveAs("images/VECISR_p_MC.pdf");
        
        tree->Draw("theta>>h(100,0,3.2)");
        h = (TH1*)gDirectory->Get("h");
        h->SetXTitle("#theta [rad]");
        h->SetYTitle("counts []");
        h->SetTitle("ISR #gamma theta from generator");
        tela->SaveAs("images/VECISR_theta_MC.pdf");
        
        gStyle->SetOptStat(0);
        
        
        myf.Close();
        delete tela;
    }
}

