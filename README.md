# tqDistpy
Python wrapper for the tqDist package

To start, clone this repo to your machine. The `tqDist` folder contains all the C++ source code to compute triplet and quartet distances of two trees. 
We will use CPython and setuptools to create a Python wrapper. The product is a Python module named `tqdist` that has two functions: `quartet_distance` and `triplet_distance`. 

## setup.py
Take a look at `setup.py`, which uses `setuptools` to build and install the package. Look at the `setup` function and notice the `ext_module` field. This is the component that instruct the installer to compile and include your C++ source. You will need to give it the sources and compile flags, as in our example.

## tqDist/tqdistmodule.cpp
Now open file `tqDist/tqdistmodule.cpp`. This file uses CPython to create the interface to communicate with `setup.py`. We use `PyModuleDef` (line 117) to define the module `tqdist` and `PyMethodDef` (line 110) to define the two functions `triplet_distance` and `quartet_distance`. Then we use `PyMODINIT_FUNC` (line 126) to create the module. The two functions `method_TripletDistance` and `method_QuartetDistance` are the wrappers that call the C++ functions to compute triplet/quartet distance, convert to a Python Object and return it. 
