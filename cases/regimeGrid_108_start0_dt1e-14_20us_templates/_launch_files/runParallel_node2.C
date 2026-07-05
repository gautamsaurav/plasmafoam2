#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
    const char *cases[54] = {
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/2mm_10GHz/DD/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/2mm_10GHz/IM/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/2mm_10GHz/FM/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/2mm_1GHz/DD/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/2mm_1GHz/IM/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/2mm_1GHz/FM/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/2mm_2GHz/DD/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/2mm_2GHz/IM/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/2mm_2GHz/FM/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/2mm_4GHz/DD/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/2mm_4GHz/IM/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/2mm_4GHz/FM/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/2mm_6GHz/DD/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/2mm_6GHz/IM/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/2mm_6GHz/FM/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/2mm_8GHz/DD/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/2mm_8GHz/IM/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/2mm_8GHz/FM/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/500um_10GHz/DD/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/500um_10GHz/IM/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/500um_10GHz/FM/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/500um_1GHz/DD/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/500um_1GHz/IM/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/500um_1GHz/FM/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/500um_2GHz/DD/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/500um_2GHz/IM/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/500um_2GHz/FM/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/500um_4GHz/DD/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/500um_4GHz/IM/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/500um_4GHz/FM/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/500um_6GHz/DD/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/500um_6GHz/IM/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/500um_6GHz/FM/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/500um_8GHz/DD/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/500um_8GHz/IM/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/500um_8GHz/FM/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/5mm_10GHz/DD/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/5mm_10GHz/IM/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/5mm_10GHz/FM/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/5mm_1GHz/DD/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/5mm_1GHz/IM/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/5mm_1GHz/FM/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/5mm_2GHz/DD/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/5mm_2GHz/IM/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/5mm_2GHz/FM/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/5mm_4GHz/DD/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/5mm_4GHz/IM/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/5mm_4GHz/FM/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/5mm_6GHz/DD/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/5mm_6GHz/IM/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/5mm_6GHz/FM/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/5mm_8GHz/DD/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/5mm_8GHz/IM/",
        "/data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us/regimeGrid/5mm_8GHz/FM/",
    };

    MPI_Init(&argc, &argv);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    cout << "Process " << world_rank << " out of " << world_size << " started." << endl;

    const int nCases = 54;
    if (world_rank < nCases) {
        const char* case_dir = cases[world_rank];
        cout << "Process " << world_rank << " running case in directory: " << case_dir << endl;

        if (chdir(case_dir) == 0) {
            system("plasmaFoam2 2> log &");
        } else {
            cerr << "Process " << world_rank << " could not change to directory: " << case_dir << endl;
        }
    } else {
        cout << "Process " << world_rank << " has no case assigned." << endl;
    }

    MPI_Finalize();
    return 0;
}
