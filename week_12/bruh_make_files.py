import os
import imageio
import numpy as np
from pathlib import Path


IMAGE_PATH = "rick_gray.png"
OUT_DIR = "./out"


def make_files(image):
    max_x = image.shape[1] - 1
    x_number_length = len(str(max_x))
    max_y = image.shape[0] - 1
    y_number_length = len(str(max_y))
    
    for y in range(image.shape[0]):
        for x in range(image.shape[1]):
            # directory name is the y index padded with 0 to the left
            directory_path = os.path.join(OUT_DIR, str(y).rjust(y_number_length, '0'))
            # make the directory
            Path(directory_path).mkdir(parents=True, exist_ok=True)
            # write the intensity of the image at these coordinates to the file with the x index
            intensity_file_path = os.path.join(directory_path, str(x).rjust(x_number_length, '0'))
            with open(intensity_file_path, 'w') as f:
                f.write("BRUH\n" * image[y, x])


def main():
    image = imageio.imread(IMAGE_PATH, as_gray=False).astype(np.uint8)
    make_files(image)

if __name__ == "__main__":
    main()
