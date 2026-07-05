/*---------------------------------------------------------------------------*\
Copyright (C) 2018 by the LUEUR authors

License
This project is licensed under The 3-Clause BSD License. For further information
look for license file include with distribution.


Class
Foam::electronVelocity
Based on Thermal boundary conditions

SourceFiles
electronVelocity.C

\*---------------------------------------------------------------------------*/

#ifndef electronVelocity_H
#define electronVelocity_H

#include "fvPatchFields.H"
#include "fixedValueFvPatchFields.H"


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

class electronVelocity
:
public fixedValueFvPatchVectorField
{
	// Private data
	scalar scalar1Data_;
	word fieldName_;
	public:

	//- Runtime type information
	TypeName("electronVelocity");


	// Constructors

	//- Construct from patch and internal field
	electronVelocity
	(
	 const fvPatch&,
	 const DimensionedField<vector, volMesh>&
	 );

	//- Construct from patch, internal field and dictionary
	electronVelocity
	(
	 const fvPatch&,
	 const DimensionedField<vector, volMesh>&,
	 const dictionary&
	 );

	//- Construct by mapping given
	//  electronVelocity onto a new patch
	electronVelocity
	(
		const electronVelocity&,
		const fvPatch&,
		const DimensionedField<vector, volMesh>&,
		const fvPatchFieldMapper&
	);

	//- Construct as copy
	electronVelocity
	(
		const electronVelocity&
	);

	//- Construct and return a clone
	virtual tmp<fvPatchVectorField> clone() const
	{
	  return tmp<fvPatchVectorField>
	(
	 new electronVelocity(*this)
	 );
	}

	//- Construct as copy setting internal field reference
	electronVelocity
	(
	 const electronVelocity&,
	 const DimensionedField<vector, volMesh>&
	 );

	//- Construct and return a clone setting internal field reference
	virtual tmp<fvPatchVectorField> clone
	(
	 const DimensionedField<vector, volMesh>& iF
	) const
	{
		return tmp<fvPatchVectorField>
		(
			new electronVelocity(*this, iF)
		);
	}

	//- Map (and resize as needed) from self given a mapping object
	virtual void autoMap
	(
		const fvPatchFieldMapper&
	);

	//- Reverse map the given fvPatchField onto this fvPatchField
	virtual void rmap
	(
		const fvPatchVectorField&,
		const labelList&
	);
	// Member functions

	//- Update the coefficients associated with the patch field
	virtual void updateCoeffs();

	//- Write
	virtual void write(Ostream&) const;
  };


  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //