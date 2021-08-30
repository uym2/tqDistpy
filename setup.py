#from setuptools import setup, Extension
from distutils.core import setup, Extension


extra_compile_args= ["-Wno-long-long", "-m64", "-O3", "-DquartetsToo"]

sources =  ["tqDist/tqdistmodule.cpp",
           "tqDist/HDT.cpp",
           "tqDist/HDTCountingCCToC.cpp",
           "tqDist/HDTCountingCTransform.cpp",
           "tqDist/HDTCountingG.cpp",
           "tqDist/HDTCountingIGToC.cpp",
           "tqDist/HDTCountingLeaf.cpp",
           "tqDist/HDTFactory.cpp",
           "tqDist/HDTListUtils.cpp",
           "tqDist/NewickParser.cpp",
           "tqDist/RootedTree.cpp",
           "tqDist/RootedTreeFactory.cpp",
           "tqDist/AbstractDistanceCalculator.cpp",
           "tqDist/TripletDistanceCalculator.cpp",
           "tqDist/QuartetDistanceCalculator.cpp",
           "tqDist/int_stuff.cpp"]

def main():
    setup(name="tqdistpy",
          version="1.2",
          description="Python interface for the tqdist C library",
          long_description="Python interface for the tqdist C library, extended from https://users-cs.au.dk/cstorm/software/tqdist/",
          author="uym2",
          author_email="ceciliamaitouyen@gmail.com",
          scripts = ["nw_triplets","nw_quartets"],
          ext_modules=[Extension("tqdist",sources=sources,
                              extra_compile_args=extra_compile_args)])

if __name__ == "__main__":
    main()
