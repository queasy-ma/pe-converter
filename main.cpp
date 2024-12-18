#include <iostream>
#include <string>
#include <filesystem>
#include "libpeconv/include/peconv.h"

namespace fs = std::filesystem;

std::string get_output_path(const std::string& input_path) {
    fs::path path(input_path);
    fs::path dir = path.parent_path();
    std::string filename = path.stem().string();
    fs::path new_path = dir / (filename + "_memory.exe");
    return new_path.string();
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <input_exe> [output_pe]" << std::endl;
        return 1;
    }

    std::string input_path = argv[1];
    std::string output_path;

    // 如果提供了输出路径就使用它，否则生成默认路径
    if (argc >= 3) {
        output_path = argv[2];
    } else {
        output_path = get_output_path(input_path);
    }

    // 1. 加载PE文件
    size_t exe_size = 0;
    BYTE *pe_buffer = peconv::load_pe_module(input_path.c_str(), exe_size, false, false);
    if (!pe_buffer) {
        std::cout << "[-] Failed to load the input file: " << input_path << std::endl;
        return -1;
    }

    // 2. 获取基址
    ULONGLONG current_base = peconv::get_image_base(pe_buffer);

    // 3. 设置dump模式为内存布局对齐
    peconv::t_pe_dump_mode dump_mode = peconv::PE_DUMP_REALIGN;

    // 4. 导出为新的PE文件
    bool is_dumped = peconv::dump_pe(
            output_path.c_str(),     // 输出路径
            pe_buffer,               // PE缓冲区
            exe_size,                // PE大小
            current_base,            // 当前基址
            dump_mode,               // dump模式
            nullptr                  // 无需导出映射
    );

    // 5. 清理资源
    peconv::free_pe_buffer(pe_buffer);

    // 6. 检查结果
    if (is_dumped) {
        std::cout << "[+] Successfully saved as: " << output_path << std::endl;
        std::cout << "[+] The new PE file is in memory-mapped format" << std::endl;
        return 0;
    } else {
        std::cout << "[-] Failed to save the output file" << std::endl;
        return -1;
    }
}