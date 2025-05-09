#!/usr/bin/python3

import sys
import subprocess
import matplotlib.pyplot as plt
import datetime

def bench_single(size: int, n: int, image: str)->float:
    total_time: float = 0
    for _ in range(n):
        out: str = subprocess.check_output(
            ["./bin/edge_detect", f"{size}", image, "out"],
            )
        total_time += float(out)
    return total_time/n

def bench_single_single_block(n: int, image: str)->float:
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
    sizes = [i for i in range(min_size, max_size+1, 5)]
    benches = []
    for i in sizes:
        print("Testing size =", i)
        benches.append(bench_single(i, 2, image))

    plt.plot(sizes, benches)
    plt.xlabel("Block size")
    plt.ylabel("Execution Time")
    plt.savefig(f"bench{min_size}_{max_size}_{datetime.datetime.now()}.png", dpi=500)
    plt.show()

def bench_multiple_images(images, sizes)->None:
    benches = []
    for image in images:
        benches.append(bench_single_single_block(2, image))

    plt.plot(sizes, benches)
    plt.xlabel("Image width")
    plt.ylabel("Execution Time")
    plt.savefig(f"control_{datetime.datetime.now()}.png", dpi=500)
    plt.show()

def bench_control():
  size = 32;
  images = []
  sizes = []
  for _ in range(200):
    image = f"rects/rect{size}x{size}"
    images.append(image)
    sizes.append(size**2)
    size += 32
  bench_multiple_images(images, sizes)
    

def main():
    if len(sys.argv) == 1:
      bench_control()
      return

    if len(sys.argv) > 2:
      print("Please provide input image.")
    image = sys.argv[1]
    bench_multiple(10, 250, image)


if __name__=="__main__":
    main()