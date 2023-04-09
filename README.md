# Paillier CPP Workaround

This was created for a utility in a research project. 
**Note: This is not safe for production.**

## Usage

This requires [GNU Multiple Precision Arithmetic Library](https://gmplib.org/) to run.
You can run test.cpp to get started.

Clone this repository and then follow these steps:
Instructions for Ubuntu:
```sh
sudo apt-get update -y
sudo apt-get install -y libgmp-dev
cd paillier-cpp-workaround/
g++ test.cpp paillier.cpp -lgmp -o ./test.out 
```

## Issues
There are some issues with the generation of random states, which can cause the program to abort or throw a segmentation fault. 
If you intend to use this, please investigate before using.