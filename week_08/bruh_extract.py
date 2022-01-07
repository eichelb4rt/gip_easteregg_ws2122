import os
import glob
import scipy.ndimage
import imageio
import numpy as np

image_1_path = "pepe.png"
image_2_path = "pepe_bruh.png"


def main():
    image_1 = imageio.imread(image_1_path, as_gray=False).astype(np.uint8)
    image_2 = imageio.imread(image_2_path, as_gray=False).astype(np.uint8)
    difference = image_1 ^ image_2
    # only red channel
    difference = difference[:, :, 0]
    difference_text = ""
    for y in range(difference.shape[0]):
        line = ""
        for x in range(difference.shape[1]):
            pixel = difference[y][x]
            if pixel <= 20:
                continue
            line += chr(pixel)
        if line:
            difference_text += line + "\n"
    print(difference_text)

if __name__ == "__main__":
    main()
