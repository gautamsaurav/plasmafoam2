//**************************************************
//this will convert int to string-------------------
//--------------------------------------------------
string convertIntToString(int numberr){
	 std::stringstream ss;
	 ss << numberr;
	 return ss.str();
}
//**************************************************
//this will convert string to integer --------------
//--------------------------------------------------
int convertStringToInt(string stringg){
 	 std::stringstream ss(stringg);
	 int x=0;
	 ss >> x;
	 return x;
}
//**************************************************
//this will convert string to float ----------------
//--------------------------------------------------
float convertStringToFloat(string stringg){
 	 std::stringstream ss(stringg);
	 float x=0;
	 ss >> x;
	 return x;
}
//******************************************************************************************************
//------ This function is used to count the number of rows in a text file (with 2 columns) -------------
//------------------------------------------------------------------------------------------------------
int countRows(string fileKoNaam){
	string pathOfFile="constant/"+fileKoNaam;
	std::ifstream iFile(pathOfFile.c_str());
	string hello;int ct=0;
	if (iFile.fail()){
        Info << "file " << pathOfFile << " does not exist"<< endl;//File does not exist code here
		exit(0);
    } else {
		while(! iFile.eof()){
			iFile >> hello;iFile >> hello;ct=ct+1;
		}
		return ct;
	}
}
////*******************************************************************************************************
//----A  function that compares all the values of a 1D array and return the largest value -----------------
//---------------------------------------------------------------------------------------------------------
int maxSize(int x[],int numSpecies){//there must already be some function to this in C++ or openfoam lib :)
	int largestValue=0;
	for (int c=0; c<numSpecies; c++){
		if (x[c]>largestValue)
			largestValue=x[c];
	}
	return largestValue;
}
//********************************************************************************************************************
// -------------- This code is used to perform the interpolation of a field ------------------------------------------
//--------------------------------------------------------------------------------------------------------------------
//this is not a good interpolation code. There will be a problem if the values are out of bound. 
//Also the maximum number of data rows is 1000. However it works for now with some workarounds. 
//I will update this part later when I fix other part of the code
void interpolation(volScalarField &efield_ref, volScalarField &mobility_ref, 
														float (*tableX)[1000][2],int speciesNum, int sizeOfDataTable ){
	int found=0; int countt=0;
	forAll (efield_ref.internalField(),ii){
		float temmpor=efield_ref[ii];
		if (temmpor> tableX[speciesNum][sizeOfDataTable-1][0])
			temmpor= tableX[speciesNum][sizeOfDataTable-1][0];
		found=0;countt=0;
		while (found ==0 && countt<sizeOfDataTable-1){
			if (temmpor>=tableX[speciesNum][countt][0] && temmpor<tableX[speciesNum][countt+1][0]){
				found=1;
				mobility_ref[ii]=tableX[speciesNum][countt][1]+
					(tableX[speciesNum][countt+1][1]-tableX[speciesNum][countt][1])/
					(tableX[speciesNum][countt+1][0]-tableX[speciesNum][countt][0])*
					(temmpor-tableX[speciesNum][countt][0]);
			}
			countt++;
		}
	}
}
//***********************************************************************************************************************



void limitVectorMagnitude(Foam::volVectorField& field, Foam::scalar maxMagnitude)
{
    forAll(field, i)
    {
        Foam::scalar vecMag = mag(field[i]); // Store the magnitude as a scalar value
        if (vecMag > maxMagnitude)
        {
            field[i] *= (maxMagnitude / vecMag); // Scale down the vector to limit its magnitude
        }
    }
    Info << "Limited vector field: " << field.name() << " to max magnitude: " << maxMagnitude << endl;
}



//limitVectorMagnitude(U, 50.0)
//U.correctBoundaryConditions();


void applyBounds(volScalarField& field, scalar minVal, scalar maxVal)
{
    forAll(field, i)
    {
        scalar& value = field[i]; // Reference to avoid repeated indexing operations.
        if (value < minVal)
        {
            value = minVal;
        }
        else if (value > maxVal)
        {
            value = maxVal;
        }
    }
    Info << "Applied bounds: [" << minVal << ", " << maxVal << "] to field: " << field.name() << endl;
}
//applyBounds(eTemp, 300, 150000)