/*---------------------------------------------------------------------------*\
Copyright (C) 2018 by the LUEUR authors
(This code was written by Abhishek Kumar Verma a former PhD student at UC Merced)
License
This project is licensed under The 3-Clause BSD License. For further information
look for license file include with distribution.

\*---------------------------------------------------------------------------*/

#include "surfaceCharge.H"
#include "addToRunTimeSelectionTable.H"
#include "fvPatchFieldMapper.H"
#include "mathematicalConstants.H"
#include "foamTime.H"
#include "volFields.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //
Foam::surfaceCharge::
surfaceCharge
(
    const fvPatch& p,
    const DimensionedField<scalar, volMesh>& iF
)
:
    fixedValueFvPatchScalarField(p, iF)//,
    //amplitude_(p.size(), 0.0),
    //modelName_("directCurrent"),
    //frequency_(0.0),
    //bias_(0.0)
{}


Foam::surfaceCharge::
surfaceCharge
(
    const fvPatch& p,
    const DimensionedField<scalar, volMesh>& iF,
    const dictionary& dict
)
:
    fixedValueFvPatchScalarField(p, iF)//,
    //amplitude_("amplitude", dict, p.size()),
    //modelName_(dict.lookupOrDefault<word>("model", "directCurrent")),
    //frequency_(dict.lookupOrDefault<scalar>("frequency", 0.0)),
    //bias_(dict.lookupOrDefault<scalar>("bias", 0.0))
{
    if (dict.found("value"))
    {
        fvPatchField<scalar>::operator=
        (
            scalarField("value", dict, p.size())
        );
    }
    else
    {
        fvPatchField<scalar>::operator=(patchInternalField());
    }
}

Foam::surfaceCharge::
surfaceCharge
(
    const surfaceCharge& ptf,
    const fvPatch& p,
    const DimensionedField<scalar, volMesh>& iF,
    const fvPatchFieldMapper& mapper
)
:
    fixedValueFvPatchScalarField(ptf, p, iF, mapper)//,
    //amplitude_(ptf.amplitude_, mapper),
    //modelName_(ptf.modelName_),
    //frequency_(ptf.frequency_),
    //bias_(ptf.bias_)
{}


Foam::surfaceCharge::
surfaceCharge
(
    const surfaceCharge& tppsf
)
:
    fixedValueFvPatchScalarField(tppsf)//,
    //amplitude_(tppsf.amplitude_),
    //modelName_(tppsf.modelName_),
    //frequency_(tppsf.frequency_),
    //bias_(tppsf.bias_)
{}


Foam::surfaceCharge::
surfaceCharge
(
    const surfaceCharge& tppsf,
    const DimensionedField<scalar, volMesh>& iF
)
:
    fixedValueFvPatchScalarField(tppsf, iF)//,
    //amplitude_(tppsf.amplitude_),
    //modelName_(tppsf.modelName_),
    //frequency_(tppsf.frequency_),
    //bias_(tppsf.bias_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::surfaceCharge::autoMap
(
    const fvPatchFieldMapper& m
)
{
    fixedValueFvPatchScalarField::autoMap(m);
    //amplitude_.autoMap(m);
}


void Foam::surfaceCharge::rmap
(
    const fvPatchScalarField& ptf,
    const labelList& addr
)
{
    fixedValueFvPatchScalarField::rmap(ptf, addr);

    const surfaceCharge& tiptf =
    refCast<const surfaceCharge>(ptf);

    //amplitude_.rmap(tiptf.amplitude_, addr);
}
void Foam::surfaceCharge::updateCoeffs()
{
    if (updated())
    {
        return;
    }

    vectorField n = patch().nf(); // Normal vector
    label patchi = this->patch().index();


    const volVectorField& toteFlux_ =
        db().lookupObject<volVectorField>("totalElectronFlux");
    const volVectorField& totiFlux_ =
        db().lookupObject<volVectorField>("totalIonFlux"); //fix this for negative species later

    volScalarField& surfC =
        const_cast<volScalarField&>(db().lookupObject<volScalarField>("surfC"));
    fvPatchField<scalar>& oldSurfaceCharge =
        surfC.boundaryField()[patchi];
    scalar dt = db().time().deltaT().value();
    scalarField newSurfaceCharge = oldSurfaceCharge;

    forAll(newSurfaceCharge, facei)
    {
        label faceCelli = patch().faceCells()[facei];
        newSurfaceCharge[facei] += dt * ( max(totiFlux_[faceCelli] & n[facei], scalar(0)) +  max(-toteFlux_[faceCelli] & n[facei], scalar(0)));
    }
    operator==(newSurfaceCharge);
    fixedValueFvPatchScalarField::updateCoeffs();
}


void Foam::surfaceCharge::
write(Ostream& os) const
{
    fvPatchScalarField::write(os);
    //os.writeKeyword("model")
    //    << modelName_ << token::END_STATEMENT << nl;
    //amplitude_.writeEntry("amplitude", os);
    //os.writeKeyword("frequency")
    //    << frequency_ << token::END_STATEMENT << nl;
    //os.writeKeyword("bias")
    //    << bias_ << token::END_STATEMENT << nl;
    writeEntry("value", os);
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
namespace Foam
{
    makePatchTypeField(fvPatchScalarField, surfaceCharge);
}
// ************************************************************************* //
