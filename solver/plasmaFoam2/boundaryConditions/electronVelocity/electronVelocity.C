/*---------------------------------------------------------------------------*\
Copyright (C) 2018 by the LUEUR authors

License
This project is licensed under The 3-Clause BSD License. For further information
look for license file include with distribution.

\*---------------------------------------------------------------------------*/

#include "electronVelocity.H"
#include "addToRunTimeSelectionTable.H"
#include "fvPatchFieldMapper.H"
#include "volFields.H"
#include "fvPatch.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::electronVelocity::
electronVelocity
(
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF
)
:
  fixedValueFvPatchVectorField(p, iF),
    fieldName_(iF.name()),
  scalar1Data_(0.0)
{}


Foam::electronVelocity::
electronVelocity
(
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF,
    const dictionary& dict
)
:
    fixedValueFvPatchVectorField(p, iF),
    fieldName_(iF.name()),
    scalar1Data_(readScalar(dict.lookup("sec")))
{
    if (dict.found("value"))
    {
        fvPatchField<vector>::operator=
        (
            vectorField("value", dict, p.size())
        );
    }
    else
    {
        fvPatchField<vector>::operator=(patchInternalField());
    }
}


Foam::electronVelocity::
electronVelocity
(
    const electronVelocity& ptf,
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF,
    const fvPatchFieldMapper& mapper
)
:
    fixedValueFvPatchVectorField(ptf, p, iF, mapper),
    fieldName_(ptf.fieldName_),
    scalar1Data_(ptf.scalar1Data_)
{}


Foam::electronVelocity::
electronVelocity
(
    const electronVelocity& ptf
)
:
    fixedValueFvPatchVectorField(ptf),
    fieldName_(ptf.fieldName_),
    scalar1Data_(ptf.scalar1Data_)
{}


Foam::electronVelocity::
electronVelocity
(
    const electronVelocity& ptf,
    const DimensionedField<vector, volMesh>& iF
)
:
    fixedValueFvPatchVectorField(ptf, iF),
    fieldName_(ptf.fieldName_),
    scalar1Data_(ptf.scalar1Data_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //
void Foam::electronVelocity::
autoMap
(
    const fvPatchFieldMapper& m
)
{
    fixedValueFvPatchVectorField::autoMap(m);
}


void Foam::electronVelocity::
rmap
(
    const fvPatchVectorField& ptf,
    const labelList& addr
)
{
    fixedValueFvPatchVectorField::rmap(ptf, addr);
}

void Foam::electronVelocity::updateCoeffs()
{
    if (this->updated())
    {
        return;
    }
       if (this->updated())
    {
        return;
    }
    vectorField n = patch().nf();
    label patchi = this->patch().index();
    

    const volScalarField& Tef =
        db().objectRegistry::lookupObject<volScalarField>("eTemp");
    const volScalarField& electrn =
        db().objectRegistry::lookupObject<volScalarField>("electron");
    const fvPatchField<scalar>& elec_bound=
        patch().lookupPatchField<volScalarField, scalar>("electron");

    
    scalarField pp(patch().size());
    forAll(pp, facei)
    {
    	label faceCelli = patch().faceCells()[facei];
        float vth = sqrt(8.0*1.38e-23*Tef[faceCelli]/9.1e-31/acos(-1.0)) ;
        pp[facei] = 0.5*vth*electrn[faceCelli]/(elec_bound[facei]+1e-30);
	}
    operator == (pp*n);
    fixedValueFvPatchVectorField::updateCoeffs();
}


void Foam::electronVelocity::write(Ostream& os) const
{
    fvPatchVectorField::write(os);
    os.writeKeyword("sec")
        << scalar1Data_ << token::END_STATEMENT << nl;
    writeEntry("value", os);
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
    makePatchTypeField
    (
        fvPatchVectorField,
        electronVelocity
    );
}


// ************************************************************************* //
