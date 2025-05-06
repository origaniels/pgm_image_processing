#!/usr/bin/python3

import sys
import subprocess
import matplotlib.pyplot as plt

def bench_single(n: int, image: str)->float:
    total_time: float = 0
    for _ in range(n):
        out: str = subprocess.check_output(
            ["./bin/edge_detect", image, "out"],
            )
        total_time += float(out)
    return total_time/n

def compile(size: int):
    subprocess.run(["gcc",
                    "-Isrc",
                    "-O0",
                    "-pg",
                    "-g3",
                    "-fsanitize=signed-integer-overflow",
                    "-lm",
                    "src/edge_detect.c",
                    "bin/convolution.c.o",
                    "bin/new.c.o",
                    "bin/matrix.c.o",
                    "bin/pgm.o",
                    "-o",
                    "bin/edge_detect",
                    f"-DBLOCK_SIZE={size}"])

def bench_multiple(min_size, max_size, image)->None:
    sizes = [i for i in range(min_size, max_size+1, 8)]
    benches = []
    for i in sizes:
        print("Testing size=", i)
        compile(i)
        benches.append(bench_single(5, image))

    plt.plot(sizes, benches)
    plt.xlabel("Block size")
    plt.ylabel("Execution Time")
    plt.show()

def main():
    if len(sys.argv) > 2:
      print("Please provide input image.")
    image = sys.argv[1]
    bench_multiple(8, 500, image)


if __name__=="__main__":
    main()