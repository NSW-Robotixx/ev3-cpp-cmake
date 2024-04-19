import glob
import os

# Define the root directory
root_dir = '/home/niklas/ev3-cpp-new'

# Define the folders to search in
folders = ['lib', 'src']

# Search for .cpp files recursively in the specified folders
cpp_files = []
for folder in folders:
  search_path = f'{root_dir}/{folder}/**/*.cpp'
  cpp_files.extend(glob.glob(search_path, recursive=True))

# Print the list of .cpp files
for file in cpp_files:
  testName = file.split('/')[-1].split('.')[0]
  testName += '.test.cpp'
  print(f'  - {testName}')

  # Create a file with the name in testName if it does not yet exist
  if not os.path.exists(testName):
    with open("tests/" + testName, 'w') as file:
      pass