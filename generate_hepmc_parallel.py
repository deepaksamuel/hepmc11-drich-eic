# Code to parallely generate hepmc files
# run with nohup python generate_hepmc_parallel.py &

import multiprocessing
import numpy as np
import subprocess

nevents=10000
#bin_id_range =[0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20]
bin_id_range = np.arange(0,21,1)
mom_range = np.concatenate((np.arange(0.5, 31.5, 0.5), np.arange(32, 50.5, 2), np.arange(55, 60.5, 5)))
pid_range=[11]

print("Bin IDs: {}, {} bins".format(bin_id_range,len(bin_id_range)))
print("Momentum range: {}, {} bins".format(mom_range, len(mom_range)))
print("PID range: {}".format(pid_range))
print("Total files to be generated: {}, each with {} events".format(len(bin_id_range)*len(mom_range)*len(pid_range),nevents))

def execute_statement(statement):
  subprocess.run(statement, shell=True)

def generate_and_execute_statements():
   print("generating")
    # ... your existing code ... 
   with multiprocessing.Pool() as pool:
         statements = [
             f"root -l 'drich_hepmc_writer_sp.C({nevents},{bin},{mom},{pid})'"
             for bin in bin_id_range
             for mom in mom_range
             for pid in pid_range
         ]
         pool.map(execute_statement, statements)

if __name__ == "__main__":
    generate_and_execute_statements()
