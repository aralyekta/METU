import math
import numpy as np
import sys
from PIL import Image
from numpy import asarray
import time


def calculate_kl_divergence(array1, array2):
    # We assume that both of these histograms have the same bin size
    divided = np.divide(array1, array2, out = np.zeros_like(array1), where = array2 != 0)
    logged = np.log10(divided, out = np.zeros_like(divided), where = divided != 0)
    multiplied = array1 * logged
    return np.sum(multiplied)


class PerChannelHistogram:
    def __init__(self, interval_count: int):
        bin_size = 256 // interval_count
        self.bin_size = bin_size
        self.interval_count = interval_count
        itr_count = math.ceil(256 / bin_size)
        self.r_bins = np.array([0] * itr_count)
        self.g_bins = np.array([0] * itr_count)
        self.b_bins = np.array([0] * itr_count)
        self.normalized = False

    def fill_histogram_with_data(self, data, size_x, size_y):
        bins = [interval_index * self.bin_size for interval_index in range(self.interval_count)]
        bins_np_array = np.array(bins)
        digitized = np.digitize(data, bins_np_array)
        reshaped = digitized.reshape(size_x * size_y, 3)
        np.apply_along_axis(self.__increment_histogram_entry, 1, reshaped)


    def __increment_histogram_entry(self, cell):
        self.r_bins[cell[0] - 1] += 1
        self.g_bins[cell[1] - 1] += 1
        self.b_bins[cell[2] - 1] += 1


    def l1_normalize(self):
        if self.normalized:
            return
        r_l1_norm = self.r_bins.sum()
        g_l1_norm = self.g_bins.sum()
        b_l1_norm = self.b_bins.sum()

        self.r_bins = np.divide(self.r_bins, r_l1_norm)
        self.g_bins = np.divide(self.g_bins, g_l1_norm)
        self.b_bins = np.divide(self.b_bins, b_l1_norm)
        self.normalized = True

    def calculate_js_divergence(self, secondHistogram):
        # print(self.bin_size, secondHistogram.bin_size)
        if self.bin_size != secondHistogram.bin_size:
            raise Exception("Bin sizes of the given histograms do not match")

        self.l1_normalize()
        secondHistogram.l1_normalize()

        r_summed_bins = self.r_bins + secondHistogram.r_bins
        g_summed_bins = self.g_bins + secondHistogram.g_bins
        b_summed_bins = self.b_bins + secondHistogram.b_bins

        r_processed_bins = r_summed_bins / 2
        g_processed_bins = g_summed_bins / 2
        b_processed_bins = b_summed_bins / 2

        r_l1_norm = np.sum(r_processed_bins)
        g_l1_norm = np.sum(g_processed_bins)
        b_l1_norm = np.sum(b_processed_bins)

        r_processed_bins /= r_l1_norm
        g_processed_bins /= g_l1_norm
        b_processed_bins /= b_l1_norm

        r_kl_divergence_1 = calculate_kl_divergence(self.r_bins, r_processed_bins)
        r_kl_divergence_2 = calculate_kl_divergence(secondHistogram.r_bins, r_processed_bins)
        r_divergence = (r_kl_divergence_1 + r_kl_divergence_2) / 2

        g_kl_divergence_1 = calculate_kl_divergence(self.g_bins, g_processed_bins)
        g_kl_divergence_2 = calculate_kl_divergence(secondHistogram.g_bins, g_processed_bins)
        g_divergence = (g_kl_divergence_1 + g_kl_divergence_2) / 2

        b_kl_divergence_1 = calculate_kl_divergence(self.b_bins, b_processed_bins)
        b_kl_divergence_2 = calculate_kl_divergence(secondHistogram.b_bins, b_processed_bins)
        b_divergence = (b_kl_divergence_1 + b_kl_divergence_2) / 2

        return (r_divergence + g_divergence + b_divergence) / 3
