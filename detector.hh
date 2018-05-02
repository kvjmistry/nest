
 // Primary Scintillation (S1) parameters

double g1 = 0.0760; //phd per S1 phot at dtCntr (not phe). Divide out 2-PE effect
double sPEres = 0.58; //single phe resolution (Gaussian assumed)
double sPEthr = 0.35; //POD threshold in phe, usually used IN PLACE of sPEeff
double sPEeff = 1.00; //actual efficiency, can be used in lieu of POD threshold
double noise[2] = {0.0,0.0}; //baseline noise mean and width in PE (Gaussian)
double P_dphe = 0.2; //chance 1 photon makes 2 phe instead of 1 in Hamamatsu PMT

int coinLevel= 2; //how many PMTs have to fire for an S1 to count
int numPMTs = 89; //For coincidence calculation

//S1 PDE custom fit for function of z
//s1polA + s1polB*z[mm] + s1polC*z^2+... (QE included, for binom dist) e.g.
double FitS1 ( double xPos_mm, double yPos_mm, double zPos_mm ) {

  return 1.; // unitless, 1.000 at detector center

}

//Drift electric field as function of Z in mm
//For example, use a high-order poly spline
double FitEF ( double xPos_mm, double yPos_mm, double zPos_mm ) { // in V/cm

  return 730.;

}

 // Ionization and Secondary Scintillation (S2) parameters

double g1_gas = 0.06; //phd per S2 photon in gas, used to get SE size
double s2Fano = 3.61; //Fano-like fudge factor for SE width
double s2_thr = 300.; //the S2 threshold in phe or PE, *not* phd. Affects NR most
double S2botTotRatio = 0.4; //S2 bottom-to-total ratio, not really used anymore
double E_gas = 12.; //field in kV/cm between liquid/gas border and anode
double eLife_us = 2200.; //the drift electron mean lifetime in micro-seconds

//S2 PDE custom fit for function of r
//s2polA + s2polB*r[mm] + s2polC*r^2+... (QE included, for binom dist) e.g.
double FitS2 ( double xPos_mm, double yPos_mm ) {

  return 1.; // unitless, 1.000 at detector center

}

 // Thermodynamic Properties

double T_Kelvin = 177.; //for liquid drift speed calculation
double p_bar = 2.14; //gas pressure in units of bars, it controls S2 size

 // Data Analysis Parameters and Geometry

double dtCntr = 40.; //center of detector for S1 corrections, in usec.
double dt_min = 20.; //minimum. Top of detector fiducial volume
double dt_max = 60.; //maximum. Bottom of detector fiducial volume
double radius = 50.; //millimeters

 double TopDrift = 150.; //mm not cm or us (but, this *is* where dt=0)
//a z-axis value of 0 means the bottom of the detector (cathode OR bottom PMTs)
//In 2-phase, TopDrift=liquid/gas border. In gas detector it's GATE, not anode!
double anode = 152.5; //the level of the anode grid-wire plane in mm
//In a gas TPC, this is not TopDrift (top of drift region), but a few mm above it
 double gate = 147.5; //mm. This is where the E-field changes (higher)
 // in gas detectors, the gate is still the gate, but it's where S2 starts

 // 2-D (X & Y) Position Reconstruction

std::vector<double> xyResolution ( double xPos_mm, double yPos_mm, double A_top, 
				   NEST::NESTcalc &m, long seed ) {
  
  std::vector<double> xySmeared(2);
  m.SetRandomSeed(seed);
  
  double radius = sqrt(pow(xPos_mm,2.)+pow(yPos_mm,2.));
  double kappa=70.8364+exp(.015*radius); // arXiv:1710.02752
  double sigmaR = kappa / sqrt ( A_top ); // ibid.
  
  double phi = m.rand_uniform() * 2. * M_PI;
  sigmaR = m.rand_gauss(0.0,sigmaR);
  double sigmaX = ( radius + sigmaR ) * cos ( phi );
  double sigmaY = ( radius + sigmaR ) * sin ( phi );
  
  xySmeared[0] = xPos_mm + sigmaX;
  xySmeared[1] = yPos_mm + sigmaY;

  return xySmeared; //new X and Y position in mm with empirical smearing. LUX Run03 example

}
