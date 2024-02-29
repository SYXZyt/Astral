import os
import time
import shutil

src_folder = "src"
dest_folder = "generated/include/Astral"

if os.path.exists(dest_folder):
	shutil.rmtree(dest_folder)

if not os.path.exists(dest_folder):
	os.makedirs(dest_folder)

count_found = count_skipped = 0
for root, dirs, files in os.walk(src_folder):
	for file in files:
		if file.endswith(".h"):
			count_found += 1

			relative_path = os.path.relpath(root, src_folder)
			src_file_path = os.path.join(root, file)

			dest_file_path = os.path.join(dest_folder, relative_path, file)

			os.makedirs(os.path.dirname(dest_file_path), exist_ok=True)

			print(f"Generated '{dest_file_path}'")

			shutil.copy2(src_file_path, dest_file_path)
		else:
			count_skipped += 1

print(f"Found {count_found} files\nSkipped {count_skipped} files")