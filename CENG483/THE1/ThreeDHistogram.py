import math
import numpy as np


def calculate_kl_divergence(array1, array2):
    # We assume that both of these histograms have the same bin size
    divided = np.divide(array1, array2, out = np.zeros_like(array1), where = array2!=0)
    logged = np.log10(divided, out = np.zeros_like(divided), where = divided!=0)
    multiplied = array1 * logged
    return np.sum(multiplied)


class ThreeDHistogram:
    def __init__(self, interval_count: int):
        bin_size = 256 // interval_count
        self.bin_size = bin_size
        self.interval_count = interval_count
        itr_count = math.ceil(256 / bin_size)
        self.bins = np.array([0] * (itr_count ** 3))
        self.interval_count_square = interval_count ** 2
        self.normalized = False

    def __increment_histogram_entry(self, cell):
        self.bins[(cell[0] - 1) * self.interval_count_square + (cell[1] - 1) * self.interval_count + (cell[2] - 1)] += 1

    def fill_histogram_with_data(self, data, size_x, size_y):
        bins = [interval_index * self.bin_size for interval_index in range(self.interval_count)]
        bins_np_array = np.array(bins)
        reshaped = data.reshape((-1, 3))
        # print(reshaped)
        # print(f"provided data: {data}")
        digitized = np.digitize(reshaped, bins_np_array)
        # print(f"digitized data: {digitized}")
        # print(digitized)
        # reshaped = digitized.reshape(size_x * size_y, 3)
        # print(reshaped)
        np.apply_along_axis(self.__increment_histogram_entry, 1, digitized)

        # bins = np.array([])

        # binned = data // self.bin_size
        # func = np.vectorize(self.__increment_histogram_entry)
        # func(data)
        # for row in binned:
        #     for cell in row:
        #         self.__increment_histogram_entry(cell)

    def l1_normalize(self):
        if self.normalized:
            return
        l1_norm = self.bins.sum()
        self.bins = np.divide(self.bins, l1_norm)
        self.normalized = True

    def calculate_js_divergence(self, secondHistogram):
        # print(self.bin_size, secondHistogram.bin_size)
        if self.bin_size != secondHistogram.bin_size:
            raise Exception("Bin sizes of the given histograms do not match")

        self.l1_normalize()
        secondHistogram.l1_normalize()

        summed_bins = self.bins + secondHistogram.bins
        processed_bins = summed_bins / 2
        l1_norm = np.sum(processed_bins)
        processed_bins = processed_bins / l1_norm

        kl_divergence_1 = calculate_kl_divergence(self.bins, processed_bins)
        kl_divergence_2 = calculate_kl_divergence(secondHistogram.bins, processed_bins)
        return (kl_divergence_1 + kl_divergence_2) / 2
