import os
import re
from collections import defaultdict

def clean_folder(folder_path, max_cases_per_dimension=10):
    files_by_dimension = defaultdict(lambda: defaultdict(list))

    # Step 1: Categorize files by dimension and index, excluding 'intrel' files
    for filename in os.listdir(folder_path):
        if '64' in filename:
            os.remove(os.path.join(folder_path, filename))
            print(f"Removed: {filename}")
            continue

        match = re.match(r'(\d+)-(\d+)_(\d+)_(uniform)\.(svp|svs)', filename)
        if match:
            dimension, index, bit_size, _, ext = match.groups()
            files_by_dimension[dimension][index].append(filename)

    # Step 2: Keep only the first 100 unique indices for each dimension
    for dimension, indices in files_by_dimension.items():
        sorted_indices = sorted(indices.keys())

        for index in sorted_indices[max_cases_per_dimension:]:
            for filename in indices[index]:
                os.remove(os.path.join(folder_path, filename))
                print(f"Removed: {filename}")

if __name__ == "__main__":
    folder_path = '/Users/jezza/Downloads/gen'  # Replace with the path to your folder
    clean_folder(folder_path)
