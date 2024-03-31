from clang.cindex import Index, TranslationUnit
import os

def find_function_definitions(folder_path):
  """
  Finds all C++ function definitions recursively within a folder.

  Args:
    folder_path: The path to the folder containing C++ files.

  Returns:
    A list of tuples, where each tuple contains the file path and the function name.
  """
  function_definitions = []
  for root, _, files in os.walk(folder_path):
    for filename in files:
      if filename.endswith(".cpp") or filename.endswith(".h"):  # Adjust for file extensions
        filepath = os.path.join(root, filename)
        try:
          index = Index.create()
          tu = index.parse(filepath, ["-x", "c++"])
          if not tu:
            continue

          for cursor in tu.cursor.walk_preorder():
            if cursor.kind.is_function_definition():
              function_definitions.append((filepath, cursor.spelling))
        except Exception as e:
          print(f"Error parsing file: {filepath} ({e})")

  return function_definitions

# Example usage
folder_path = "./src"  # Replace with your actual folder path
definitions = find_function_definitions(folder_path)

if definitions:
  print("Found function definitions:")
  for filepath, function_name in definitions:
    print(f"{filepath}: {function_name}")
else:
  print("No function definitions found.")







# import os
# import re

# src_dir = "./src"
# test_dir = "./tests"

# print('src_dir (absolute) = ' + os.path.abspath(src_dir))

# src_file_content = ""
# test_file_content = ""

# # get content of all source files in src folder
# for root, subdirs, files in os.walk(src_dir):
#     list_file_path = os.path.join(root, 'my-directory-list.txt')

#     for filename in files:
#         file_path = os.path.join(root, filename)

#         if not filename.endswith(".txt") and not filename.endswith(".hpp"):
#             with open(file_path, 'rb') as f:
#                 f_content = f.read()
#                 src_file_content += str(f_content)


# # get content of all test files in tests directory
# for root, subdirs, files in os.walk(test_dir):
#     list_file_path = os.path.join(root, 'my-directory-list.txt')

#     for filename in files:
#         file_path = os.path.join(root, filename)


#         if not filename.endswith(".txt") and not filename.endswith(".hpp"):
#             with open(file_path, 'rb') as f:
#                 f_content = f.read()
#                 test_file_content += str(f_content)

# function_pattern = r"(?P<function_decl>^\s*(?:class\s+|\w+\s*::)?\w+\s*\([^)]*\)\s*;)"

# function_names = re.findall(function_pattern, src_file_content)

# print("Function names found:")
# for name in function_names:
#   print(name.split(" ")[1])  # Extract the actual function name

# # print(src_file_content)