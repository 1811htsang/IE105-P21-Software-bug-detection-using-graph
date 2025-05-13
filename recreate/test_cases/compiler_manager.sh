# This file is used for compile each test case
# If there is any or no error, it will be printed to the output file in each test case
# The output file will be named as test_case_name.out
# The output file will be saved in the same directory as the test case

#! /bin/bash

# Thư mục gốc chứa các thư mục test_case_x_folder
BASE_DIR="/home/shanghuang/Documents/Code related/SoftwareBugDetectionUsingCallGraphReferences/recreate/test_cases"

# Duyệt qua từng thư mục test_case_x_folder
for folder in "$BASE_DIR"/test_case_*_folder; 
do
    # Kiểm tra xem thư mục có tồn tại không
    if [ -d "$folder" ]; then
        echo "----------------------"
        echo "Đang xử lý thư mục: $folder \n"

        # Xóa tất cả các file .out đã được compiled trước đó
        find "$folder" -type f -name "*.out" -exec rm -f {} \;

        # Tìm file .cpp trong thư mục
        cpp_file=$(find "$folder" -type f -name "*.cpp")

        # Kiểm tra nếu file .cpp tồn tại
        if [ -n "$cpp_file" ]; then
            # Tên file .out sẽ được lưu
            output_file="$folder/$(basename "$folder").out"

            # Compile file .cpp và lưu kết quả vào file .out
            g++ "$cpp_file" -o "$folder/a.out" &> "$output_file"

            # Kiểm tra nếu compile thành công
            # Nếu compile thành công, trong file .out sẽ không có gì
            # Nếu compile không thành công, trong file .out sẽ chứa thông tin lỗi báo từ compiler
            if [ $? -eq 0 ]; then
                echo "$cpp_file pass \n"
            else
                echo "$cpp_file fail \n"
            fi

            echo "-----------------------"
        else
            echo "Không tìm thấy file .cpp trong thư mục: $folder \n"
        fi
    fi
done
