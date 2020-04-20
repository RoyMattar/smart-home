#include <map>
#include <string>

void test(int b, int f, int r, int e) {
    std::map<std::string, int> m;

    // room: 3 ,floor:1 event:smoke   --> 42
    // room: * ,floor:1 event:smoke   --> 44

    m["3:1:smoke"] = 42;
    m["*:1:smoke"] = 44;
    // room: * ,floor:* event:smoke   --> 46
    m["*:*:smoke"] = 46;
    m["*:*:*"] = 999;

    // we have event: et, r, f
    k1 = combine(r,f,et, ':');
    k2 = combine('*', f, et, ':');
    handlers = m[k1] + m[k2];

    keys_vector = gen(e, r, f, b, c)
    for each v in keys_vector: m[v] = 42
    // event: smoke, floor:1, room:2
    // x = m["2:1:smoke"];
    // y = m["*:1:smoke"];
    // z = m["*:*:smoke"];
    // w = m["*:*:*"];
    all = [sum for each v in keys_vector: m[v]
////////////////////////////////
    m["3:1:b1:smokke"] = 42;
    mAnyRoom["1:smoke"] = 44;
    mAnyFloor["smoke"] = 46;

    
}