#!/bin/bash
#SBATCH --mail-user=sgautam3@ucmerced.edu
#SBATCH --mail-type=ALL
#SBATCH --nodes=1
#SBATCH --ntasks=54
#SBATCH --ntasks-per-node=54
#SBATCH --partition=long
#SBATCH --time=3-00:00:00
#SBATCH --output=/dev/null
#SBATCH --job-name=pressureVar_dt1e14_node2

source /home/sgautam3/foam/foam-extend-4.1/etc/bashrc
module load mpich/3.4.2-gcc-8.4.1
cd /data/sgautam3/2025/pressureVariation/revision2_start0_dt1e-14_20us
mpirun -np 54 ./a_node2.out
