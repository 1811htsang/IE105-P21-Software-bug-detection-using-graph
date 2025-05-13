import json
import os
import random

# Đường dẫn đến file JSONL
jsonl_file_path = "/home/shanghuang/Documents/Code related/SoftwareBugDetectionUsingCallGraphReferences/recreate/cpp_dataset.jsonl"

# Đường dẫn thư mục gốc để lưu các thư mục test_case
output_base_dir = "/home/shanghuang/Documents/Code related/SoftwareBugDetectionUsingCallGraphReferences/recreate/test_cases"

# Tạo thư mục gốc nếu chưa tồn tại
os.makedirs(output_base_dir, exist_ok=True)

# Đọc toàn bộ file JSONL và lưu các dòng vào danh sách
with open(jsonl_file_path, "r", encoding="utf-8") as jsonl_file:
    lines = [line.strip() for line in jsonl_file if line.strip()]

# Chọn ngẫu nhiên 30 dòng từ file JSONL
random_lines = random.sample(lines, min(30, len(lines)))

# Xử lý từng dòng JSON
for idx, line in enumerate(random_lines, start=1):
    try:
        # Parse dòng JSON
        data = json.loads(line)

        # Kiểm tra key "pass"
        if "pass" in data:
            # Tạo thư mục riêng cho từng test case
            folder_name = f"test_case_{idx}_folder"
            folder_path = os.path.join(output_base_dir, folder_name)
            os.makedirs(folder_path, exist_ok=True)

            # Tạo file C++ trong thư mục
            cpp_file_path = os.path.join(folder_path, f"test_case_{idx}.cpp")
            with open(cpp_file_path, "w", encoding="utf-8") as cpp_file:
                cpp_file.write(data["pass"])

            print(f"Source code đã được lưu vào: {cpp_file_path}")

    except json.JSONDecodeError:
        print(f"Lỗi khi parse JSON ở dòng {idx}: {line}")