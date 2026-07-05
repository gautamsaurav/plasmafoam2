# plasmaFoam2 Transfer Package

This package contains the plasmaFoam2 source tree and clean OpenFOAM/foam-extend case templates for transferring to another HPC system.

## Contents

- `solver/plasmaFoam2/`: plasmaFoam2 source copied from the UC Merced environment.
- `cases/baseline/`: baseline DD, IM, and FM cases.
- `cases/IMFM_54_dt1e-13_nCycles5/`: selected 54-case IM/FM template set.
- `cases/IMFM_54_dt2e-13_nCycles10/`: selected 54-case IM/FM template set.
- `scripts/`: example Slurm launchers and MPI rank launch sources.
- `docs/source_manifest.txt`: original source paths from the UC Merced filesystem.

The case directories are templates and should contain only `0`, `constant`, and `system`.

## Expected Environment

Install and source foam-extend 4.1 on the target cluster before building:

```bash
source /path/to/foam-extend-4.1/etc/bashrc
```

The original environment used:

- foam-extend 4.1
- OpenMPI from foam-extend ThirdParty
- `wmake` build system

## Build

From the target cluster:

```bash
cd solver/plasmaFoam2
source /path/to/foam-extend-4.1/etc/bashrc
wmake
```

The executable should be installed as:

```text
$FOAM_APPBIN/plasmaFoam2
```

If the target cluster uses a different compiler/MPI stack, rebuild foam-extend and this solver in the same environment.

## Run A Single Case

```bash
source /path/to/foam-extend-4.1/etc/bashrc
cd cases/IMFM_54_dt1e-13_nCycles5/regimeGrid/250um_10GHz/FM
plasmaFoam2 > run.log 2>&1
```

## Run Multiple Cases

The `scripts/` directory contains example Slurm and MPI launcher files. Update absolute paths and partition names for the target cluster before submitting.

The current examples assume one case per MPI rank and one node with 54 tasks.

## Notes

- Do not commit generated output time folders, logs, processor directories, or post-processing results.
- Keep this repository private unless the solver and cases are cleared for public release.
