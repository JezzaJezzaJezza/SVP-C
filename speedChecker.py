import os
import re
import subprocess
import pandas as pd

def run_hyperforme_on_cases(folder_path):
    speeds = {"Dimension": [], "Speed": []}
    counter = 0

    for filename in os.listdir(folder_path):
        counter += 1
        print(filename, end=" ")
        print(counter)
        if filename.endswith(".svp"):
            match = re.match(r'(\d+)-\d+_\d+_(uniform)\.svp', filename)
            if match:
                dimension = match.group(1)

                # Read .svp file and prepare arguments
                with open(os.path.join(folder_path, filename), 'r') as file:
                    svp_args = file.read().strip().split()

                # Run hyperfine
                cmd = ["hyperfine", "--warmup", "2", "-N", f"./runme {' '.join(svp_args)}"]
                result = subprocess.run(cmd, capture_output=True, text=True)
                
                # Extract speed from hyperfine output
                speed_match = re.search(r"Time \(mean ± σ\): +([\d.]+) ms", result.stdout)
                if speed_match:
                    speed = float(speed_match.group(1))
                    speeds["Dimension"].append(int(dimension))
                    speeds["Speed"].append(speed)

    # Save the data to a CSV file
    df = pd.DataFrame(speeds)
    df.to_csv('speeds.csv', index=False)

    return df

if __name__ == "__main__":
    folder_path = '/Users/jezza/Downloads/gen'  # Replace with the path to your folder
    df = run_hyperforme_on_cases(folder_path)
    print("Speed data saved to speeds.csv")
