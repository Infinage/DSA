import glob
import os
import subprocess

files = glob.glob("./**/*.ipynb", recursive=True)
print (f"Total of {len(files)} files detected.\n")

def get_output_path(input_path: str) -> list[str]:
    fp_split = input_path.split(os.path.sep)
    dir_ = "./views/" + "/".join(fp_split[1:-1])
    fname = fp_split[-1] + ".md"
    return dir_, os.path.join(dir_, fname)

for inp_path in files:
    print(f"Input path: {inp_path}")
    op_dir, op_path = get_output_path(inp_path)
    print(f"Output Directory: {op_dir}, Output File Path: {op_path}")
    os.makedirs(op_dir, exist_ok=True)
    command = f"pandoc {inp_path} -s -t gfm -o {op_path}"
    print (f"Command: {command}")
    p = subprocess.Popen(command.split(), stdout=subprocess.PIPE)
    print(f"Command Output: {p.stdout.read().decode('utf-8')}\n")
