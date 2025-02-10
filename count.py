import os

def count_lines_of_code(directory):
    total_lines = 0

    for root, dirs, files in os.walk(directory):
        for file in files:
            file_path = os.path.join(root, file)
            with open(file_path, "r") as f:
                lines = f.readlines()
                total_lines += len(lines)

    return total_lines

# Example usage
directory = "./lib"  # Replace with the directory you want to count lines of code in
lines_of_code = count_lines_of_code(directory)
print(f"Total lines of code in {directory}: {lines_of_code}")