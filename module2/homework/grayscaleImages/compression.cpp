#include "compression.hpp"
#include <vector>
#include <array>
#include <algorithm>

compressed_vec compressGrayscale(bitmap_array const& bitmap)
{
    compressed_vec out_vec;
    uint8_t* registered_value = nullptr;

    std::for_each(bitmap.begin(), bitmap.end(),
            [&registered_value, &out_vec](auto row){
                registered_value = row.begin();
                while(true)
                {
                    auto iter = std::find_if(registered_value, row.end(),
                            [registered_value](uint8_t elem)
                            {
                                return elem != *registered_value;
                            }
                    );

                    out_vec.push_back(std::make_pair(*registered_value,
                            iter - registered_value));
                    registered_value = iter;
                    if(iter == row.end())
                    {
                        break;
                    }
                }
            }
    );

    return out_vec;
}

bitmap_array decompressGrayscale(const compressed_vec& comp_vec)
{
    int num_of_row = 0;
    std::vector<uint8_t> row = {};
    bitmap_array decompressed_data;
    std::for_each(comp_vec.begin(), comp_vec.end(),
                    [&decompressed_data, &row, &num_of_row](auto pair)
                    {
                        row.insert(row.end(), std::get<1>(pair), std::get<0>(pair));
                        if(row.size() == width)
                        {
                            std::copy(row.begin(), row.end(), (decompressed_data[num_of_row]).begin());
                            num_of_row++;
                            row.erase(row.begin(), row.end());
                            row.shrink_to_fit();
                        }
                    }
    );

    return decompressed_data;
}

void printMap(const bitmap_array& input_map)
{
    std::for_each(input_map.begin(), input_map.end(),
                    [](auto row)
                    {
                        std::for_each(row.begin(), row.end(),
                                        [](auto value)
                                        {
                                            std::cout << value;
                                        }
                        );
                        std::cout << '\n';
                    }
    );
}