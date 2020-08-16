// MIT License
//
// Copyright (c) 2020 NeilKleistGao
//
//        Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
//        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//        copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
//        copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// LAST MODIFY: 2020/8/14
// FILENAME: serialization_test.cc

//#define NGIND_SERIALIZATION_TEST
#ifdef NGIND_SERIALIZATION_TEST

#include "serialization.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

class foo : public ngind::Serializable {
public:
    int bar;
    foo(int b = 0) : bar(b) {

    }
    virtual void serialize(std::ostream& os) const {
        ngind::serialize(bar, os);
    };
    virtual void deserialize(std::istream& is) {
        ngind::deserialize(bar, is);
    }
};

int main() {
    std::ofstream stream("temp.txt", std::ios::binary);
    int i = 65;
    ngind::serialize(i, stream);

    float f = 114.514;
    ngind::serialize(f, stream);

    bool b = true;
    ngind::serialize(b, stream);

    std::string str = "wtf";
    ngind::serialize(str, stream);

    std::vector<int> v{1, 2, 3, 4};
    ngind::serialize(v, stream);

    foo u(5);
    ngind::serialize(u, stream);

    std::vector<foo> v2 {foo(2), foo(2)};
    ngind::serialize(v2, stream);

    stream.close();

    std::ifstream stream2("temp.txt");
    int ipp = 0;
    ngind::deserialize(ipp, stream2);

    float fpp = 0.0f;
    ngind::deserialize(fpp, stream2);

    bool bpp = false;
    ngind::deserialize(bpp, stream2);

    std::string strpp = "";
    ngind::deserialize(strpp, stream2);

    std::vector<int> vpp;
    ngind::deserialize(vpp, stream2);

    foo upp(0);
    ngind::deserialize(upp, stream2);

    std::vector<foo> v2pp;
    ngind::deserialize(v2pp, stream2);

    stream2.close();

    assert(i == ipp);
    assert(f == fpp);
    assert(b == bpp);
    assert(str == strpp);
    assert(u.bar == upp.bar);

    for (int j = 0; j < v.size(); ++j) {
        assert(v[j] == vpp[j]);
    }
    for (int j = 0; j < v2.size(); ++j) {
        assert(v2[j].bar == v2pp[j].bar);
    }

    return 0;
}

#endif // NGIND_SERIALIZATION_TEST



