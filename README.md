#RandomScripts

this repository is meant to contain a collection of scripts that can be useful for DPG data analysis. Please add a description of your newly added script in this readme file.

#Plot_SingleModules.C
This is a root macro to plot single modules histograms taken from a DQM file. At the momnet the macro is designed to get digi occupancy plots, however can be easily extended to plot any other module level quantity stored in a DQM file.

Usage: open root and issue .x Plot_SingleModules(string filename, string modulelist,string dirlist, int runnumber)

filename is the name of the input file, modulelist is the name of a text file with a single column of detId you are interested in, dirlist is a file containing all possible directories in a DQM file where single module plots are booked, runnumber is obvious.