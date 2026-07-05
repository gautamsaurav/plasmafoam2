//*****************************************************************************************************
//====================================== MOMENTUM SOLVER ==============================================
//*****************************************************************************************************
//ionFlux=0*ionFlux;
forAll (speciesList, ii){
	if (collisionType[ii] == "muBased" && chargeNumber[ii]!=0) //muBased done here. rrBased is default
		collFreqxN[ii] = nDensity[ii]*eCharge/(mobility[ii])/speciesMass[ii]/dimensionCorrectionMass;
	if (transportModel[ii] == "momentum"){
		if (ii==0){//electron
			pTemperature= 1*eTemp;}
		else //ion and other species
			{pTemperature= gasTemperature*dimensionCorrectionTemp;}


		// Include dimensionCorrectionMass where necessary to ensure consistency

		Foam::tmp<Foam::volVectorField> tmpNDensityVelocity = nDensity[ii] * velocity[ii];
		Foam::tmp<Foam::volVectorField> ddtTerm = fvc::ddt(tmpNDensityVelocity());
		Foam::tmp<Foam::volVectorField> divTerm = fvc::div(
			fvc::interpolate(nDensity[ii]) * (fvc::interpolate(velocity[ii]) & mesh.Sf()),
			velocity[ii],
			"div(velocity*nDensity,velocity)"
		);
		term1 = (ddtTerm() + divTerm()) ;
		term2 = (collFreqxN[ii] * velocity[ii]); 
		term3 = (chargeNumber[ii] / abs(chargeNumber[ii]) * eCharge * nDensity[ii] * EField) /
        	(speciesMass[ii] * dimensionCorrectionMass);

		// term4: Gradient term
		term4 = fvc::grad(kBoltz * pTemperature * nDensity[ii]) / speciesMass[ii]/dimensionCorrectionMass;


		Info << "Solving momentum equation" << endl;//--------------------
			fvVectorMatrix momEqn
			(
				fvm::ddt(nDensity[ii],velocity[ii])  
				+ fvm::div(fvc::interpolate(nDensity[ii])*
						(fvc::interpolate(velocity[ii]) & mesh.Sf()),velocity[ii],"div(velocity*nDensity,velocity)")  
				+ fvm::Sp(collFreqxN[ii],velocity[ii])
				== 
				chargeNumber[ii]/abs(chargeNumber[ii])*eCharge*nDensity[ii]*EField/speciesMass[ii]/dimensionCorrectionMass
				- fvc::grad(kBoltz*pTemperature*nDensity[ii])/speciesMass[ii]/dimensionCorrectionMass
			);
		momEqn.solve();
		limitVectorMagnitude(velocity[ii], 10000000);
		velocity[ii].correctBoundaryConditions();
	}
}//======================================================================================================
eCollisionFrequency = collFreqxN[0]/nDensity[0];
