import os
import subprocess
import glob

def get_output_path(input_path: str) -> tuple[str, str, str]:
    fp_split = input_path.split(os.path.sep)
    dir_ = "./views/" + "/".join(fp_split[:-1])
    fname = fp_split[-1] + ".md"
    return os.path.join(dir_, fname), dir_, fname

def exec_command(commands: str) -> str:
    out = subprocess.check_output(commands, shell=True)
    return out.decode("utf-8")

# Only build the changed files
print(f"Using .git from the volume: {exec_command('git config --global --add safe.directory /data')}")

# Modify only the changed files
diff_output = exec_command("git diff --name-status origin/main~1 origin/main")
for line in diff_output.split("\n"):

    # Consider all diff lines with ipynb in them
    if ".ipynb" in line:
        print (f"\nDiff line: {line}")

        # Note that diff lines typically follow this format
        # MODE, OLD, NEW - based on the mode OLD might not exist
        mode, *file_changes = line.split()

        # Only consider first character
        mode = mode[0]

        for inp_path in file_changes:
            # Only consider ipynb inputs, it might happen to be non ipynb
            if inp_path.endswith(".ipynb"):
                op_path, op_dir, op_fname = get_output_path(inp_path)
                print (f"\nInput path: {inp_path}\nOutput Directory: {op_dir}\nOutput FP: {op_path}")

                # Rebuilding so delete the old view path
                if os.path.exists(op_path):
                    print (f"Deleting view: {op_path}")
                    os.remove(op_path)

                # The inp file might happen to OLD, say post a rename
                # We want to eliminate false positives by checking if 
                # the file actually exists
                if os.path.exists(inp_path):
                    os.makedirs(op_dir, exist_ok=True)
                    print (f"Creating view for: {inp_path}")
                    command = f"""
                        papermill {inp_path} {inp_path} &&
                        pandoc {inp_path} -s -t gfm -o {op_path}
                    """
                    print (f"Command: {command}")
                    output = exec_command(command)
                    print(f"Command Output: {output}")

# Build missing views somehow not in git history
files = glob.glob("**/*.ipynb", recursive=True)
views: set[str] = set()
for inp_path in files:
    op_path, op_dir, op_fname = get_output_path(inp_path)
    views.add(op_path) # Tracking all views that should actually exist

    # If not exists, let's build them
    if not os.path.exists(op_path):
        os.makedirs(op_dir, exist_ok=True)
        print (f"\nCreating view for missing file: {inp_path}")
        command = f"""
            papermill {inp_path} {inp_path} &&
            pandoc {inp_path} -s -t gfm -o {op_path}
        """
        print (f"Command: {command}")
        output = exec_command(command)
        print(f"Command Output: {output}")

# Print empty line for legibility
print()

# Prune missing files that somehow have a view
views_present = set(glob.glob("./views/**/*.ipynb.md", recursive=True))
views_to_prune = set.difference(views_present, views)
for op_path in views_to_prune:
    print (f"Pruning view not in VCS: {op_path}")
    os.remove(op_path)

# Prune empty directories
print("Pruning empty directories, output:", exec_command("find ./views -type d -empty -print -delete"))
