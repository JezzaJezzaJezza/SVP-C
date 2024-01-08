import pandas as pd
import seaborn as sns
import re
import matplotlib.pyplot as plt

df =pd.read_csv("./output.csv")

def extract_dim_bit(svp_file):
    pattern = r'(r|u)_(\d{1,2})d_(\d{1,2})b'
    match = re.search(pattern, svp_file)
    print(match)
    if match:
        return match.group(1), match.group(2), match.group(3)
    else:
        return None, None, None

df['type'], df['dimension'], df['bits'] = zip(*df['test case'].apply(extract_dim_bit))

df[['dimension', 'bits']] = df[['dimension', 'bits']].astype(float)
sns.set_theme()
a =sns.lineplot(x="dimension", y="median", hue="bits", palette="bright", data=df)
a.set(ylabel="Time (ms)", xlabel="Dimension", yscale="log")
a.set_xticks(range(50))
plt.show()