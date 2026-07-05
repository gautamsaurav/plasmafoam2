float maxValue=0.0;
int nIterations_=0;
do{
		EPotential.storePrevIter();
		//=================== semi implicit poisson solver ================================
		if (emSolver=="semiImplicit"){
			netCharge=0*netCharge;
			impSource= 0*impSource;
			forAll(speciesList, ii){
				int isElectron = 0;
				if (ii==0){isElectron =0;}
							netCharge = netCharge + eCharge * chargeNumber[ii] * nDensity[ii] + 
									eCharge * chargeNumber[ii] * runTime.deltaT() * fvc::laplacian(diffusion[ii], nDensity[ii],"laplacian(difC,nDensity)") +
									isElectron * eCharge * chargeNumber[ii] * runTime.deltaT() * fvc::laplacian(nDensity[0] * mobility[0] * kBoltz / eCharge, eTemp);
							impSource = impSource +  eCharge * chargeNumber[ii] * nDensity[ii] * sign(chargeNumber[ii]) * mobility[ii] * runTime.deltaT() / epsilon;
			}
			impSource=impSource+epsilon / epsilon;

			fvScalarMatrix poissonPlasmaEquation
									(
											fvm::laplacian(impSource,EPotential) + netCharge / epsilon
									);
			poissonPlasmaEquation.relax();
			poissonPlasmaEquation.solve();
			EField = -fvc::grad(EPotential);
		}//--------------------------------------------------------------------------------

		// =================== Explicit poisson solver ====================================
		else if (emSolver == "explicit"){
			netCharge = dimensionedScalar("zero", netCharge.dimensions(), 0.0);
			forAll(speciesList, ii){
					netCharge = netCharge + eCharge * chargeNumber[ii] * nDensity[ii];
			}
			fvScalarMatrix poissonPlasmaEquation
							(
								fvm::laplacian(EPotential) == -netCharge / epsilon
							);
			poissonPlasmaEquation.relax();
			poissonPlasmaEquation.solve();
			EField=-fvc::grad(EPotential);
			Info << "solvedPoisson" << endl;
		}//--------------------------------------------------------------------------------
		else if (emSolver=="linearized"){
				netCharge=0 * netCharge;
				forAll(speciesList, ii){
						netCharge = netCharge + eCharge * chargeNumber[ii] * nDensity[ii] - eCharge * fvc::div((fvc::interpolate(velocity[ii]) & mesh.Sf()),nDensity[ii],"div(vel,nDensity)") * runTime.deltaT() ;
				}
				fvScalarMatrix poissonPlasmaEquation
								(
									fvm::laplacian(EPotential) == -netCharge / epsilon
								);
				poissonPlasmaEquation.relax();
				poissonPlasmaEquation.solve();
				EField=-fvc::grad(EPotential);
				Info << "solvedPoisson" << endl;
		}


		//********************************************************************************************************************
		// Solving the poisson equation for all dielectric region ************************************************************
		//====================================================================================================================
		forAll (dielectricList,ii){
			EPotentialD[ii].storePrevIter();
			fvScalarMatrix poissonDielectricEquation
				(
					fvm::laplacian(EPotentialD[ii], "laplacian(EPotential)")
				);
				poissonDielectricEquation.relax();
				poissonDielectricEquation.solve();
				EFieldD[ii]=-fvc::grad(EPotentialD[ii]);
				//EFieldD[ii].correctBoundaryConditions();
				//Info << "Dielectric lai solve gardai cha" << endl;
				maxValue=gMax(mag(EPotential.internalField()-EPotential.prevIter().internalField()));
				float maxValue1 = gMax(mag(EPotentialD[ii].internalField()-EPotentialD[ii].prevIter().internalField()));
				if (maxValue1>maxValue)
					maxValue=maxValue1;	
		}
		nIterations_++;
}
while (maxValue>0.025 && nIterations_ <10);
Info << "Solved Poisson ======================================== iterations"<< nIterations_ <<endl;