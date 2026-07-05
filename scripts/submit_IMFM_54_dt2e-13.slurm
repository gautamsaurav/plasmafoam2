#!/bin/bash
#SBATCH --mail-user=sgautam3@ucmerced.edu
#SBATCH --mail-type=ALL
#SBATCH --nodes=1
#SBATCH --ntasks=54
#SBATCH --ntasks-per-node=54
#SBATCH --partition=medium
#SBATCH --time=1-00:00:00
#SBATCH --output=/dev/null
#SBATCH --job-name=pressureVar_IMFM54_dt2e13_nC10

source /home/sgautam3/foam/foam-extend-4.1/etc/bashrc
module load mpich/3.4.2-gcc-8.4.1
cd /data/sgautam3/2025/pressureVariation/revision2_IMFM_54cases_dt2e-13_nCycles10_20us

WATCHDOG_LOG="$PWD/slurm_self_restart.log"
RESTART_AFTER_SECONDS=$((23 * 3600 + 30 * 60))
(
    sleep "$RESTART_AFTER_SECONDS"
    echo "$(date '+%F %T') job $SLURM_JOB_ID reached 23h30m; submitting replacement" >> "$WATCHDOG_LOG"
    sbatch --partition=medium --time=1-00:00:00 --exclude=node014 "$0" >> "$WATCHDOG_LOG" 2>&1
    echo "$(date '+%F %T') cancelling current job $SLURM_JOB_ID" >> "$WATCHDOG_LOG"
    scancel "$SLURM_JOB_ID"
) &
watchdog_pid=$!
echo "$(date '+%F %T') started self-restart watchdog pid=$watchdog_pid job=$SLURM_JOB_ID host=$(hostname)" >> "$WATCHDOG_LOG"

mpirun -np 54 ./a_IMFM_54_dt2e-13.out
