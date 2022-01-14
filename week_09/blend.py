from math import ceil, floor
import os
import glob
import scipy.ndimage
import imageio
import numpy as np
import random

image_1_path_in = "rick_bruh.png"
image_2_path_in = "rock.png"
image_path_out = "out.png"

ALPHA = 0.5

def gen_random(lower, upper):
    area_accepted = (upper - lower) / 2
    # coin_toss = random.randint(0, 1)
    coin_toss = 0
    if coin_toss == 0:
        return random.randint(lower, floor(lower + area_accepted))
    else:
        return random.randint(ceil(upper - area_accepted), upper)


def mix_images(image_1, image_2):
    # plan: out = (A + x + B - x) / 2
    # calculate upper and lower bounds
    image_a = image_1.astype(np.int16)
    image_b = image_2.astype(np.int16)
    upper_bound_a = 255 - image_a
    lower_bound_a = -image_a
    upper_bound_b = image_b
    lower_bound_b = image_b - 255
    upper_bound = np.empty_like(image_a)
    lower_bound = np.empty_like(image_a)
    for channel in range(3):
        for y in range(upper_bound.shape[0]):
            for x in range(upper_bound.shape[1]):
                upper_bound[y, x, channel] = min(upper_bound_a[y, x, channel], upper_bound_b[y, x, channel])
                lower_bound[y, x, channel] = max(lower_bound_a[y, x, channel], lower_bound_b[y, x, channel])
                
    # get random x in the bounds
    image_x = np.empty_like(image_a)
    for channel in range(3):
        for y in range(image_x.shape[0]):
            for x in range(image_x.shape[1]):
                image_x[y, x, channel] = gen_random(lower_bound[y, x, channel], upper_bound[y, x, channel])

    return (image_1 + image_x).astype(np.uint8), (image_2 - image_x).astype(np.uint8)

def mix_images_2(image_1, image_2):
    image_coin_toss = np.empty_like(image_1)
    for channel in range(4):
        for y in range(image_coin_toss.shape[0]):
            for x in range(image_coin_toss.shape[1]):
                image_coin_toss[y, x, channel] = random.randint(0, 1)
    mix_1 = (1 - image_coin_toss) * image_1 + image_coin_toss * image_2
    mix_2 = (1 - image_coin_toss) * image_2 + image_coin_toss * image_1
    return mix_1.astype(np.uint8), mix_2.astype(np.uint8)


def main():
    # read image and normalize
    image_1 = imageio.imread(image_1_path_in, as_gray=False).astype(np.uint8)
    image_2 = imageio.imread(image_2_path_in, as_gray=False).astype(np.uint8)
    # bruh transform
    mixed_1, mixed_2 = mix_images_2(image_1, image_2)
    mixed = ((1 - ALPHA) * mixed_1 + ALPHA * mixed_2).astype(np.uint8)
    # write out
    imageio.imsave("dwayne_the_rick_johnson.png", mixed_1)
    imageio.imsave("rock_astley.png", mixed_2)
    imageio.imsave("mixed.png", mixed)


if __name__ == "__main__":
    main()
