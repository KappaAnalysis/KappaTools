# Kappa Tools

[![Build Status](https://travis-ci.org/KappaAnalysis/KappaTools.svg)](https://travis-ci.org/KappaAnalysis/KappaTools)

ĸappa tools are tools that can be used to run an analysis
using ĸappa based data formats and root files. This library
contains several tools which are helpful for particle physics
analyses. They can be used independently and each folder
compiles on its own. Cross-dependencies should be avoided.

- **Example**: Examples how to build a simple analysis reading
  ĸappa files.
- **PlotTools**: A library to create root histograms and plots
  in C++ code. The Artus tree approach differs from that but
  analyses with huge numbers of events might (partially) come back to
  histograms at some point.
- **Plots**: Plots of specific muon and jet quantities.
  This code was used by Manuel Zeise for Z analyses.
- **PythonTools**: A C++ interface class to a python generated config.
- **RootTools**: This is a library of tools depending on 
  [ROOT](https://root.cern.ch/drupal/). It contains the file
  interface to ĸappa files, jet correction and jet ID tools, etc.
  Some of these are used by 
  [Artus](https://github.com/artus-analysis/Artus).
- **Toolbox**: A library with various tools to make C++ coding easier. 
  For example string operations like in python, coloured std output, progress
  monitors, vector, timing and memory tools. This is partially used
  in [Artus](https://github.com/artus-analysis/Artus).
- **Tools**: Standalone tools like a duplicate event checker,
  prescale handling, etc.
