#!/bin/bash
#SBATCH --mail-user=sgautam3@ucmerced.edu  
#SBATCH --mail-type=ALL  
#SBATCH --nodes=2
#SBATCH --ntasks=108
#SBATCH --ntasks-per-node=54
#SBATCH --partition=long     # Use the "long" partition
#SBATCH --time=3-00:00:00    # Job time limit
#SBATCH --output=/dev/null
#SBATCH --job-name=pressureVariation_all


#module load mpich/3.4.2-gcc-8.4.1
source /home/sgautam3/foam/foam-extend-4.1/etc/bashrc
module load mpich/3.4.2-gcc-8.4.1
cd /data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us
mpirun -np 108 ./a.out
