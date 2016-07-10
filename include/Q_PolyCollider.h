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

#ifndef Q_POLY_COLLIDER_H
#define Q_POLY_COLLIDER_H

#include "Q_Collider2D.h"
#include "Q_PolyColliderDef.h"

namespace Quantum2D {
    class PolyCollider : public Collider2D {
    public:
        PolyCollider(const BodyList &bodylist,
                     body2d_id body,
                     void *parent,
                     const std::function<void(void *other)> &onCollision,
                     const PolyColliderDef *colDef);
        
        /**
         Get the coordinates of this polygon's vertices
         in the parent rigidbody's local space.
        */
        const PointList &points() const { return m_colDef->points(); }
        
        /**
         Get the current coordinates of this polygon's vertices
         in world space.
        */
        const PointList &worldPoints() const { return m_worldPoints; }
        
        void update(tQ_delta delta) override;
        
    private:
        const PolyColliderDef *m_colDef;
        PointList m_worldPoints;
    };
}

#endif // Q_POLY_COLLIDER_H