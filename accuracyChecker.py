import os
import subprocess

def get_percentage_difference(val1, val2):
    try:
        return 100 * abs(val1 - val2) / ((val1 + val2) / 2)
    except ZeroDivisionError:
        return 0

def main(folder_path):
    total_percentage_diff = 0
    num_cases = 0

    for filename in os.listdir(folder_path):
        if filename.endswith(".svp"):
            svp_path = os.path.join(folder_path, filename)
            svs_path = os.path.join(folder_path, filename.replace(".svp", ".svs"))
            print(f"Percentage difference for {filename}", end=" ")
            if os.path.exists(svs_path):
                # Read .svp file and prepare arguments
                with open(svp_path, 'r') as file:
                    svp_args = file.read().strip().split()

                # Run the C program with arguments from .svp file
                subprocess.run(["./runme"] + svp_args, stdout=open('output.txt', 'w'))

                # Read output from C program
                with open('output.txt', 'r') as file:
                    output_val = float(file.read().strip())

                # Read corresponding .svs file
                with open(svs_path, 'r') as file:
                    svs_val = float(file.read().strip())

                # Calculate the percentage difference
                percentage_diff = get_percentage_difference(output_val, svs_val)
                print(f"{percentage_diff:.2f}%")

                # Accumulate total percentage difference
                total_percentage_diff += percentage_diff
                num_cases += 1

    if num_cases > 0:
        # Calculate and print the total average percentage difference
        average_percentage_diff = total_percentage_diff / num_cases
        print(f"\nTotal average percentage difference: {average_percentage_diff:.2f}%")
    else:
        print("No valid cases found.")

if __name__ == "__main__":
    folder_path = '/Users/jezza/Downloads/gen'  # Replace with the path to your folder
    main(folder_path)