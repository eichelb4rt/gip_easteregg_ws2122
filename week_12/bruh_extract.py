import glob
import imageio
import numpy as np
from pathlib import Path

ROOT_PATH = "./out"
IMAGE_PATH_OUT = "./extracted.png"


def get_shape(root_path):
    max_y = max([int(Path(dir_path).stem) for dir_path in glob.glob(f"{ROOT_PATH}/*")])
    max_x = max([int(Path(file_path).stem) for file_path in glob.glob(f"{ROOT_PATH}/*/*")])
    return (max_y + 1, max_x + 1)


def make_image(root_path, shape):
    image = np.empty(shape, dtype=np.uint8)
    for dir in glob.glob(f"{ROOT_PATH}/*"):
        y = int(Path(dir).stem)
        for intensity_file in glob.glob(f"{dir}/*"):
            x = int(Path(intensity_file).stem)
            with open(intensity_file, 'r') as f:
                # each BRUH is on a new line
                intensity = len(f.readlines())
                image[y, x] = intensity
    return image


def main():
    shape = get_shape(ROOT_PATH)
    image = make_image(ROOT_PATH, shape)
    imageio.imsave(IMAGE_PATH_OUT, image)


if __name__ == "__main__":
    main()
