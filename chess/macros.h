#pragma once

#define add_int_strings(x,y) std::to_string(x).append(std::to_string(y))
#define in_vector(e,vec) std::find(vec.begin(), vec.end(), e) != vec.end()
#define in_array(e,arr) std::find(std::begin(arr), std::end(arr), e) != std::end(arr)