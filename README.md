# HEPMC file for DRICH analysis (electrons only)

The code that creates the hepmc file is in `drich_hepmc_writer_sp.C`. This was provided by Chandradoy Chatterjee (INFN), modified by Deepak Samuel (CUK).

The filenames have the format `PID_MOMENTUM_ETABIN.hepmc`. Each file contains 2000 events.

- `PID` is 11 (electron). Hepmc files for K, p and pi can be found at https://github.com/deepaksamuel/hepmc-drich-eic/blob/main/README.md



- `MOMENTUM` can be one of:   
[ 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0, 6.5, 7.0, 7.5, 8.0, 8.5, 9.0, 9.5, 10.0, 10.5, 11.0, 11.5, 12.0, 12.5, 13.0, 13.5, 14.0, 14.5, 15.0, 15.5, 16.0, 16.5, 17.0, 17.5, 18.0, 18.5, 19.0, 19.5, 20.0, 20.5, 21.0, 21.5, 22.0, 22.5, 23.0, 23.5, 24.0, 24.5, 25.0, 25.5, 26.0, 26.5, 27.0, 27.5, 28.0, 28.5, 29.0, 29.5, 30.0, 30.5, 31.0, 32.0, 34.0, 36.0, 38.0, 40.0, 42.0, 44.0, 46.0, 48.0, 50.0, 55.0, 60.0]

indicating the momentum in GeV. It runs in:  

- 0.5 GeV steps from 0.5 GeV until 31 GeV,
- 1 GeV steps until 32 Gev,  
- 2 GeV steps until  50 GeV,
- 5 GeV steps until 60 GeV. 

In the code, internally momentum is smeared between +/- 0.1 GeV.


- `ETABIN` can be one of:  
 [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]

 with each number indicating a specific eta range as follows:

```
{1.499, 1.501}, //etaBin 0  
{1.599, 1.601}, //etaBin 1  
{1.699, 1.701}, //etaBin 2  
{1.799, 1.801}, //etaBin 3  
{1.899, 1.901}, //etaBin 4  
{1.999, 2.001}, //etaBin 5  
{2.099, 2.101}, //etaBin 6  
{2.199, 2.201}, //etaBin 7  
{2.299, 2.301}, //etaBin 8  
{2.399, 2.401}, //etaBin 9  
{2.499, 2.501}, //etaBin 10  
{2.599, 2.601}, //etaBin 11  
{2.699, 2.701}, //etaBin 12  
{2.799, 2.801}, //etaBin 13  
{2.899, 2.901}, //etaBin 14  
{2.999, 3.001}, //etaBin 15  
{3.099, 3.101}, //etaBin 16  
{3.199, 3.201}, //etaBin 17  
{3.299, 3.301}, //etaBin 18  
{3.399, 3.401}, //etaBin 19  
{3.499, 3.501}  //etaBin 20  
```

The code `generate_hepmc_parallel.py` generates the hepmc files using all the cores in the system. 

Run the code using: 

`nohup python generate_hepmc_parallel.py &`

inside the `eic-shell`.

It took about 1 minute to generate 1554 hepmc files, each with 2000 events.