# HGCPlotting
Plotting scripts for HGCal

## Setting up
To compile: type `make`
To run `./FillHistograms --in_directory inputdirectory --out_directory outputdirectory --max_events 10000`

`inputdirectory` can be local or remote (searches for `ntuple_i.root`, where i is a number).
`--max_events` is an optional variable

## Creating your own histograms

The code works by defining 'Histogram sets' - i.e. a set of histograms for a given study.
The histogram sets you choose are currently chosen in the Constructor function at the top of `src/HGCPlotting.cxx`

Define a new histogram set in the `LoadHistoTemplates` function in `src/Histogramming.cxx`.
The histograms are filled in the `FillAllHists` function.
The histograms can be filled directly with variables from the input tree, or with custom variables defined in the function `CalculateTriggerCellVariables` and saved into the `_event_variables` map. 
More functions can be added for specific calculations.
