from PIL import Image
import numpy as np
import time
import sys
from ThreeDHistogram import ThreeDHistogram
from PerChannelHistogram import PerChannelHistogram

file_names = []
dataset_folder = "dataset"
base_query_folder = "dataset/query_"
support_folder = "dataset/support_96"

support_histograms_3d = {}
support_histograms_3_color = {}

image_grids = {}
row_count = 96
col_count = 96

grid_cache_hit = 0
grid_cache_total = 0
support_histogram_cache_hit = 0
support_histogram_cache_total = 0

x_size = 96
y_size = 96


def __get_grids(query_num, image_name, grid_x, grid_y):
    global grid_cache_total
    global grid_cache_hit

    grid_cache_total += 1
    # This means the image is already separated into grids
    if image_grids.get((query_num, image_name, grid_x, grid_y)) is not None:
        grid_cache_hit += 1
        return image_grids[(query_num, image_name, grid_x, grid_y)]

    if query_num == 4: # If it is support
        query_image = Image.open(support_folder + "/" + image_name)
    else:
        query_image = Image.open(base_query_folder + str(query_num) + "/" + image_name)
    query_image_data = np.asarray(query_image)

    reshaped = query_image_data.reshape((grid_x * grid_y, -1, 3))
    image_grids[(query_num, image_name, grid_x, grid_y)] = reshaped
    return reshaped


def __run_3d_with_grid(query_num, bin_number, grid_x, grid_y):
    correct_retrieval = 0
    total_images = 0

    global support_histogram_cache_total
    global support_histogram_cache_hit

    for query_file_name in file_names:
        # tic = time.perf_counter()
        total_images += 1
        query_image_grids = __get_grids(query_num, query_file_name, grid_x, grid_y)

        query_image_grid_histograms = []
        for query_image_grid in query_image_grids:
            query_image_grid_histogram = ThreeDHistogram(bin_number)
            query_image_grid_histogram.fill_histogram_with_data(query_image_grid, x_size // grid_x, y_size // grid_y)
            query_image_grid_histograms.append(query_image_grid_histogram)

        min_divergence = sys.maxsize
        for support_file_name in file_names:
            total_js_divergence = 0
            support_image_grids = __get_grids(4, support_file_name, grid_x, grid_y)
            grid_num = 0
            for support_image_grid in support_image_grids:
                support_histogram_cache_total += 1
                query_image_grid_histogram = query_image_grid_histograms[grid_num]
                if support_histograms_3d.get((support_file_name, bin_number, grid_x, grid_y, grid_num)) is not None:
                    support_image_grid_histogram = support_histograms_3d[(support_file_name, bin_number, grid_x, grid_y, grid_num)]
                    support_histogram_cache_hit += 1
                else:
                    support_image_grid_histogram = ThreeDHistogram(bin_number)
                    support_image_grid_histogram.fill_histogram_with_data(support_image_grid, x_size // grid_x, y_size // grid_y)
                    support_histograms_3d[(support_file_name, bin_number, grid_x, grid_y, grid_num)] = support_image_grid_histogram
                # print(support_image_grid_histogram.bins)
                grid_js_divergence = query_image_grid_histogram.calculate_js_divergence(support_image_grid_histogram)
                # print(grid_js_divergence)
                total_js_divergence += grid_js_divergence
                # print(total_js_divergence, grid_js_divergence)
                grid_num += 1
            total_js_divergence /= grid_x * grid_y
            # print(f"Js divergence of file {support_file_name} is {total_js_divergence}")
            if total_js_divergence < min_divergence:
                min_divergence = total_js_divergence
                min_divergence_file = support_file_name
                # print(f"Set {support_file_name} as the min_divergence file for {query_file_name}")
        # toc = time.perf_counter()
        # print(f"Finished a batch in {toc - tic:0.4f} seconds")
        # print(query_file_name, min_divergence_file)
        # print(grid_cache_hit / grid_cache_total, grid_cache_total)
        # print(support_histogram_cache_hit / support_histogram_cache_total, support_histogram_cache_total)
        # print(total_images / 200)
        if query_file_name == min_divergence_file:
            correct_retrieval += 1

    return correct_retrieval / total_images


def run_all_3d_with_grid():
    global file_names

    f = open("dataset/InstanceNames.txt")
    for name in f:
        file_names.append(name.strip())

    # file_names = file_names[:10]

    query_numbers = [1,2,3]
    grid_options = [(2,2), (4,4), (6,6), (8,8)]
    bin_num = 16
    for query_num in query_numbers:
        for grid_option in grid_options:
            tic = time.perf_counter()
            accuracy = __run_3d_with_grid(query_num, bin_num, grid_option[0], grid_option[1])
            toc = time.perf_counter()
            print(f"Finished a batch in {toc - tic:0.4f} seconds")
            print(f"For query set {query_num} and {grid_option} grid, accuracy is: {accuracy}\n")


def __run_per_channel_with_grid(query_num, bin_number, grid_x, grid_y):
    correct_retrieval = 0
    total_images = 0

    global support_histogram_cache_total
    global support_histogram_cache_hit

    for query_file_name in file_names:
        total_images += 1
        query_image_grids = __get_grids(query_num, query_file_name, grid_x, grid_y)

        query_image_grid_histograms = []
        for query_image_grid in query_image_grids:
            query_image_grid_histogram = PerChannelHistogram(bin_number)
            query_image_grid_histogram.fill_histogram_with_data(query_image_grid, x_size // grid_x, y_size // grid_y)
            query_image_grid_histograms.append(query_image_grid_histogram)

        min_divergence = sys.maxsize

        # tic = time.perf_counter()
        for support_file_name in file_names:
            total_js_divergence = 0
            support_image_grids = __get_grids(4, support_file_name, grid_x, grid_y)
            grid_num = 0
            for support_image_grid in support_image_grids:
                support_histogram_cache_total += 1
                query_image_grid_histogram = query_image_grid_histograms[grid_num]
                if support_histograms_3_color.get((support_file_name, bin_number, grid_x, grid_y, grid_num)) is not None:
                    support_image_grid_histogram = support_histograms_3_color[(support_file_name, bin_number, grid_x, grid_y, grid_num)]
                    support_histogram_cache_hit += 1
                else:
                    support_image_grid_histogram = PerChannelHistogram(bin_number)
                    support_image_grid_histogram.fill_histogram_with_data(support_image_grid, x_size // grid_x, y_size // grid_y)
                    support_histograms_3_color[(support_file_name, bin_number, grid_x, grid_y, grid_num)] = support_image_grid_histogram
                grid_js_divergence = query_image_grid_histogram.calculate_js_divergence(support_image_grid_histogram)
                total_js_divergence += grid_js_divergence
                grid_num += 1

            total_js_divergence /= grid_x * grid_y
            if total_js_divergence < min_divergence:
                min_divergence = total_js_divergence
                min_divergence_file = support_file_name
        # toc = time.perf_counter()
        # print(f"Finished a batch in {toc - tic:0.4f} seconds")
        # print(query_file_name, min_divergence_file)
        # print(support_histogram_cache_hit / support_histogram_cache_total, support_histogram_cache_total)
        if query_file_name == min_divergence_file:
            correct_retrieval += 1

    return correct_retrieval / total_images

def run_all_per_channel_with_grid():
    f = open("dataset/InstanceNames.txt")
    for name in f:
        file_names.append(name.strip())

    query_numbers = [1, 2, 3]
    grid_options = [(2,2), (4,4), (6,6), (8,8)]
    bin_num = 32
    for query_num in query_numbers:
        for grid_option in grid_options:
            tic = time.perf_counter()
            accuracy = __run_per_channel_with_grid(query_num, bin_num, grid_option[0], grid_option[1])
            toc = time.perf_counter()
            print(f"Finished a batch in {toc - tic:0.4f} seconds")
            print(f"For query set {query_num} and {grid_option} grid, accuracy is: {accuracy}\n")