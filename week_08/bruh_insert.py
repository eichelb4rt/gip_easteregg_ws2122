import os
import glob
import scipy.ndimage
import imageio
import numpy as np
import random

image_path_in = "pepe.png"
image_path_out = "pepe_bruh.png"
# the insertions you want
bruh_insertions = [
    ("Bruh! Frohes neues Jahr!", (0, 0)),
    ("Bruh!", (1, 0)),
    ("Bruh! Du hast das Super-Easteregg gefunden, dafür bekommst du einen Preis: nichts!", (212, 42)),
]
# noise params
min_noise = 0
max_noise = 20


def bruh_all_channels(image):
    # construct XOR image
    bruh_image = np.zeros(image.shape[:2]).astype(np.uint8)
    for bruh_insertion in bruh_insertions:
        text, position = bruh_insertion
        y, start_x = position
        end_x = start_x + len(text)
        bruh_image[y][start_x:end_x] = [ord(char) for char in text]

    # add some noise to XOR image
    for y in range(bruh_image.shape[0]):
        for x in range(bruh_image.shape[1]):
            pixel = bruh_image[y][x]
            if pixel == 0:
                noise = random.randint(min_noise, max_noise)
                bruh_image[y][x] ^= noise

    # transform
    image_transformed = np.empty_like(image)
    # image.shape[2] = number of channels in a 2d image
    for channel in range(image.shape[2]):
        # skip alpha channel
        if channel == 3:
            image_transformed[:, :, channel] = image[:, :, channel]
            continue
        image_transformed[:, :, channel] = image[:, :, channel] ^ bruh_image
    return image_transformed


def main():
    # read image and normalize
    image = imageio.imread(image_path_in, as_gray=False)
    image = image.astype(np.uint8)
    # bruh transform
    new_image = bruh_all_channels(image)
    # write out
    imageio.imsave(image_path_out, new_image.astype(np.uint8))


if __name__ == "__main__":
    main()
