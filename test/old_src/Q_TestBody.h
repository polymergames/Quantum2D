/*
    Copyright 2016 Ahnaf Siddiqui

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef Q_TEST_BODY_H
#define Q_TEST_BODY_H

#include <functional>
#include "Q_Collider2D.h"
#include "gtest/gtest.h"

namespace QTest {
    template <class COL>
    class TestBody {
    public:
        template <typename... Args>
        TestBody(Quantum2D::BodyList &bodylist, const std::string &name, int rbody, Args&&... args)
            : name(name), blist(bodylist), body(rbody), mCol(nullptr), other(nullptr) {
            std::function<void(void*)> callback = std::bind(&TestBody::onCollision, this, std::placeholders::_1);
            mCol = new COL(bodylist, rbody, this, callback, std::forward<Args>(args)...);
        }

        ~TestBody() {
            delete mCol;
        }

        Quantum2D::Rigidbody2D &getBody() {
            return blist[body];
        }

        void onCollision(void *other) {
            this->other = static_cast<TestBody*>(other);
        }

        void checkInit(const std::string &exp_name) {
            ASSERT_NE(mCol, nullptr);
            ASSERT_EQ(other, nullptr);
            ASSERT_EQ(name, exp_name);
        }

        std::string name;
        Quantum2D::BodyList &blist;
        body2d_id body;
        COL *mCol;
        TestBody *other;
    };
}

#endif // Q_TEST_BODY_H
