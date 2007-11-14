// BSP partitioning strategy.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _BSP_PARTITION_STRATEGY_H_
#define _BSP_PARTITION_STRATEGY_H_

namespace OpenEngine {
namespace Scene {

/**
 * Short description.
 *
 * @class BSPPartitionStrategy BSPPartitionStrategy.h Scene/BSPPartitionStrategy.h
 */
class BSPPartitionStrategy {
public:
    virtual ~BSPPartitionStrategy() {}
    /**
     * Partitioning algorithm for BSP tree construction.
     *
     * @pre faces is non-empty.
     * @param[in] divider Face to partition by.
     * @param[in] faces Face set to partition.
     * @param[out] front Front set after partitioning.
     * @param[out] front Spanning set after partitioning.
     * @param[out] front Back set after partitioning.
     * @param epsilon Optional epsilon.
     */
    virtual void Partition(FacePtr divider, FaceSet& faces,
                           FaceSet& front, FaceSet& span, FaceSet& back,
                           float epsilon = EPS) = 0;
};

class BSPSplitStrategy : public BSPPartitionStrategy {
public:
    virtual void Partition(FacePtr divider, FaceSet& faces,
                           FaceSet& front, FaceSet& span, FaceSet& back,
                           float epsilon = EPS) {
        faces.Split(divider, front, span, back, epsilon);
    }
};

class BSPDivideStrategy : public BSPPartitionStrategy {
public:
    virtual void Partition(FacePtr divider, FaceSet& faces,
                           FaceSet& front, FaceSet& span, FaceSet& back,
                           float epsilon = EPS) {
        FaceSet split;
        faces.Divide(divider, front, span, back, split, epsilon);
        front.Add(&split);
        back.Add(&split);
    }
};

} // NS Scene
} // NS OpenEngine

#endif // _BSP_PARTITION_STRATEGY_H_
