from PIL import Image
from numpy import asarray
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

x_size = 96
y_size = 96


def __run_3d_without_grid(query_num, bin_number):
    correct_retrieval = 0
    total_images = 0
    for query_file_name in file_names:
        total_images += 1
        query_image = Image.open(base_query_folder + str(query_num) + "/" + query_file_name)
        query_image_data = asarray(query_image)
        query_histogram = ThreeDHistogram(bin_number)
        query_histogram.fill_histogram_with_data(query_image_data, x_size, y_size)
        min_divergence = sys.maxsize
        min_divergence_file = ""
        for support_file_name in file_names:
            if support_histograms_3d.get((support_file_name, bin_number)):
                support_histogram = support_histograms_3d[(support_file_name, bin_number)]
            else:
                support_image = Image.open(support_folder + "/" + support_file_name)
                support_image_data = asarray(support_image)
                support_histogram = ThreeDHistogram(bin_number)
                support_histogram.fill_histogram_with_data(support_image_data, x_size, y_size)
                support_histograms_3d[(support_file_name, bin_number)] = support_histogram
            js_divergence = query_histogram.calculate_js_divergence(support_histogram)
            if js_divergence < min_divergence:
                min_divergence = js_divergence
                min_divergence_file = support_file_name
        if query_file_name == min_divergence_file:
            correct_retrieval += 1

    return correct_retrieval / total_images


def run_all_3d_without_grid():
    f = open("dataset/InstanceNames.txt")
    for name in f:
        file_names.append(name.strip())
    query_numbers = [1,2,3]
    bin_numbers = [2,4,8,16]
    for query_num in query_numbers:
        for bin_num in bin_numbers:
            tic = time.perf_counter()
            accuracy = __run_3d_without_grid(query_num, bin_num)
            toc = time.perf_counter()
            print(f"Finished a batch in {toc - tic:0.4f} seconds")
            print(f"For query set {query_num} and {bin_num} many bins, accuracy is: {accuracy}\n")


def __run_per_channel_without_grid(query_num, bin_number):
    query_histograms = {}

    correct_retrieval = 0
    total_images = 0
    support_cache_misses = 0
    support_cache_hits = 0
    for query_file_name in file_names:
        total_images += 1
        query_image = Image.open(base_query_folder + str(query_num) + "/" + query_file_name)
        query_image_data = asarray(query_image)
        query_histogram = PerChannelHistogram(bin_number)
        query_histogram.fill_histogram_with_data(query_image_data, x_size, y_size)
        query_histograms[query_file_name] = query_histogram
        min_divergence = sys.maxsize
        min_divergence_file = ""
        for support_file_name in file_names:
            if support_histograms_3_color.get((support_file_name, bin_number)):
                support_histogram = support_histograms_3_color[(support_file_name, bin_number)]
                support_cache_hits += 1
            else:
                support_image = Image.open(support_folder + "/" + support_file_name)
                support_image_data = asarray(support_image)
                support_histogram = PerChannelHistogram(bin_number)
                support_histogram.fill_histogram_with_data(support_image_data, x_size, y_size)
                support_histograms_3_color[(support_file_name, bin_number)] = support_histogram
                support_cache_misses += 1
            js_divergence = query_histogram.calculate_js_divergence(support_histogram)
            if js_divergence < min_divergence:
                min_divergence = js_divergence
                min_divergence_file = support_file_name
        # print(f"Original file is: {query_file_name} while the matched file is: {min_divergence_file}")
        if query_file_name == min_divergence_file:
            correct_retrieval += 1

    return correct_retrieval / total_images


def run_all_per_channel_without_grid():
    f = open("dataset/InstanceNames.txt")
    for name in f:
        file_names.append(name.strip())
    query_numbers = [1,2,3]
    bin_numbers = [2,4,8,16,32]
    for query_num in query_numbers:
        for bin_num in bin_numbers:
            tic = time.perf_counter()
            accuracy = __run_per_channel_without_grid(query_num, bin_num)
            toc = time.perf_counter()
            print(f"Finished a batch in {toc - tic:0.4f} seconds")
            print(f"For query set {query_num} and {bin_num} many bins, accuracy is: {accuracy}\n")