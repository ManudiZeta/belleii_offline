import ROOT
    
# stile ROOT
ROOT.gStyle.SetOptStat(0)
# apri il file ROOT
myf = ROOT.TFile.Open("../../../15012026_nog.root")
# prendi l'albero
tree = myf.Get("tree")
# canvas per disegno
tela = ROOT.TCanvas("tela", "Canvas", 800, 600)
# disegno istogrammi
tree.Draw("vpho_r_mRecoil>>h1(200,0,2)")
tree.Draw("vpho_r_mRecoil>>h2(200,0,2)", "nROE_Charged__bo__bc == 0 && alpha < 0.35")
tree.Draw("vpho_r_mRecoil>>h3(200,0,2)", "nROE_Charged__bo__bc == 0 && alpha < 0.35 && pi_pionID>0.9 && roeE__bo__bc < 1")
# prendi gli istogrammi
h1 = ROOT.gDirectory.Get("h1")
h2 = ROOT.gDirectory.Get("h2")
h3 = ROOT.gDirectory.Get("h3")
# etichette e titolo
h1.SetXTitle("m_{recoil} [{GeV}/{c^{2}}]")
h1.SetYTitle("counts")
h1.SetTitle("recoil mass of p+, #pi-")

h1.SetLineColor(ROOT.kBlue)
h2.SetLineColor(ROOT.kRed)
h3.SetLineColor(ROOT.kGreen)

leg = ROOT.TLegend()
leg.AddEntry(h1,"","l")
leg.AddEntry(h2, "nROE_Charged = 0, #alpha < 0.35","l")
leg.AddEntry(h3, "nROE_Charged = 0, #alpha < 0.35, #pi_{ID} > 0.9, roeE < 1","l")

tela.cd()
h1.Draw()
h2.Draw("same")
h3.Draw("same")
leg.Draw("same")
tela.Update()

input("Press Enter to close the plot and exit...")

