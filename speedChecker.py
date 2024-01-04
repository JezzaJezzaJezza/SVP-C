import os
import subprocess
import csv

def run_hyperfine_and_export(tests_folder_path, svp_file):
    svp_path = os.path.join(tests_folder_path, svp_file)
    
    # Read .svp file to get arguments
    with open(svp_path, 'r') as file:
        svp_args = file.read().strip().split()

    # Construct the hyperfine command as a single string
    command_string = f'"./runme {" ".join(svp_args)}"'
    hyperfine_command = f'hyperfine --warmup 5 -N {command_string} --export-csv ./tmp.csv'
    
    subprocess.run(hyperfine_command, shell=True)

def append_tmp_to_output(filename):
    tmp_path = "./tmp.csv"
    output_path = "./output.csv"

    with open(tmp_path, 'r') as tmp_file, open(output_path, 'a', newline='') as output_file:
        tmp_reader = csv.reader(tmp_file)
        output_writer = csv.writer(output_file)

        for i, row in enumerate(tmp_reader):
            if i == 0 and os.path.getsize(output_path) > 0:  # Skip the header line if output.csv is not empty
                continue
            if i > 0:  # Replace 'Benchmark' value with the filename
                row[0] = filename
            output_writer.writerow(row)

def main(tests_folder_path):
    # Create or clear the output.csv file
    with open("./output.csv", 'w', newline='') as file:
        writer = csv.writer(file)
        # Adjust these headers based on the actual output format of hyperfine
        writer.writerow(['Benchmark', 'Mean [ms]', 'Min [ms]', 'Max [ms]', 'Relative', 'Measurements'])  

    for filename in os.listdir(tests_folder_path):
        if filename.endswith(".svp"):
            print(f"Processing {filename}...")
            run_hyperfine_and_export(tests_folder_path, filename)
            append_tmp_to_output(filename)

    print("All hyperfine tests completed and results appended to output.csv.")

if __name__ == "__main__":
    tests_folder_path = '/Users/jezza/Downloads/tests-2'  # Replace with the path to your tests folder
    main(tests_folder_path)
