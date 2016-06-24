#pragma once

#define add_int_strings(x,y) std::to_string(x).append(std::to_string(y))
#define in_vector(e,vec) std::find(vec.begin(), vec.end(), e) != vec.end()
#define in_array(e,arr) std::find(std::begin(arr), std::end(arr), e) != std::end(arr)
#define empty(a) a == '.'
#define foe(a) in_array(a,foe)
#define empty_or_foe(a) a == '.' || in_array(a,foe)
#define dub(x) in_array(x, dub)

#define inf 1000000

#define in_tt(x,h) x.find(h) != x.end()
#define not_in_tt(x,h) x.find(h) == x.end()