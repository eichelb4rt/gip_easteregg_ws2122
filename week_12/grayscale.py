import imageio
import numpy as np

IMAGE_PATH_IN = "rick_smiling.png"
IMAGE_PATH_OUT = "rick_gray.png"


def grayscale(image):
    gray_scaled = np.zeros(image.shape[:2]).astype(np.uint8)
    gray_scaled[:,:] = image[:,:,0] / 3 + image[:,:,1] / 3 + image[:,:,2] / 3
    return gray_scaled


def main():
    # read image and normalize
    image = imageio.imread(IMAGE_PATH_IN, as_gray=False).astype(np.uint8)
    # bruh transform
    new_image = grayscale(image)
    # write out
    imageio.imsave(IMAGE_PATH_OUT, new_image.astype(np.uint8))


if __name__ == "__main__":
    main()
