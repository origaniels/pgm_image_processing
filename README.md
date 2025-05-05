# About

This repository is a multi-purpose image processing project.

It was mainly written to use as a benchmarking test for OpenMP.

The supported image formats are currently only `pgm` (Portable Gray Map).

It mostly contains:
- A minimal matrix computation library in `matrix.c` 
- A `pgm` image file format decoder that can generate matrices of pixels
- A simple edge detection frontend using the two libraries above.

# Usage
## Building

*Currently only supports systems that can run* `make`.

After cloning this repository, go to it's root.

To compile the edge detection program run:
```sh
mkdir bin #if the bin folder doesn't already exist
make
```

## Using `edge_detect`

Given an input file at `path/to/input/file.pgm` and a desired output file `path/to/edges/file`, run:

```sh
./bin/edge_detect path/to/input/file.pgm path/to/edges/file
```

You can change the edge detection method by changing the value of the `filter` variable in `edge_detect.c`.
