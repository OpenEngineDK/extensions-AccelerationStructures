// Strategies for finding a dividing face for BSP trees.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _BSP_FIND_DIVIDER_STRATEGY_H_
#define _BSP_FIND_DIVIDER_STRATEGY_H_

namespace OpenEngine {
namespace Scene {

/**
 * Short description.
 *
 * @class BSPFindDividerStrategy BSPFindDividerStrategy.h Scene/BSPFindDividerStrategy.h
 */
class BSPFindDividerStrategy {
public:
    virtual ~BSPFindDividerStrategy() { }
    /**
     * Find a dividing face to partition the BSP tree by.
     *
     * Must always return a face even in the case of a convex face
     * set.
     * It may be assumed that the supplied face set is non-empty.
     *
     * @pre faces is non-empty.
     * @param faces Face set in which to search for divider.
     * @param epsilon Epsilon value.
     * @return Dividing face.
     */
    virtual FacePtr FindDivider(FaceSet& faces, float epsilon = EPS) = 0;
};


/**
 * Find the best dividing face in the set.
 *
 * This algorithm is based on the choose-dividing-polygon listing
 * found at http://www.devmaster.net/articles/bsp-trees/
 */
class BSPDefaultFindDivider : public BSPFindDividerStrategy {
public:
    virtual FacePtr FindDivider(FaceSet& faces, float epsilon = EPS) {
        // adjustable constants
        float relation_minimum = 0.0; // initial minimum balance relation
        float relation_scale   = 0.5; // scale to lower the relation with
        // other declarations
        FaceList::iterator best_face = faces.end();
        int min_split = faces.Size();
        float best_rel = 0.0;
        float cur_rel = 0.0;
        int no_front, no_back, no_span;
        FaceList::iterator ftest, fcomp;
        Vector<3,int> pos;
        // if the set is empty return
        if (min_split == 0)
            throw Exception("Invalid call to find divider with an empty face set.");
        // if only one element is in the set it as best
        if (min_split == 1) best_face = faces.begin();
        // find the best face in the set
        while (best_face == faces.end()) {
            for (ftest = faces.begin(); ftest != faces.end(); ftest++) {
                no_front = no_back = no_span = 0;
                for (fcomp = faces.begin(); fcomp != faces.end(); fcomp++) {
                    // ignore the face we are testing
                    if (*fcomp == *ftest) continue;
                    // count the face positions
                    pos = (*ftest)->ComparePosition(*fcomp, epsilon);
                    switch (pos.Sum()) {
                    case -3:
                    case -2:
                        ++no_back; break;
                    case 3:
                    case 2:
                        ++no_front; break;
                    case -1:
                        if (pos[0] * pos[1] * pos[2] == 0) ++no_back;
                        else ++no_span;
                        break;
                    case 1:
                        if (pos[0] * pos[1] * pos[2] == 0) ++no_front;
                        else ++no_span;
                        break;
                    case 0:
                        if (pos[0] || pos[1] || pos[2]) ++no_span;
                        // else it is in the same plane and we don't care
                        break;
                    }
                    // compute the division relation
                    if (no_front * no_back == 0)
                        cur_rel = 0;
                    else if (no_front < no_back)
                        cur_rel = (float)no_front / (float)no_back;
                    else if (no_back < no_front)
                        cur_rel = (float)no_back / (float)no_front;
                    else
                        cur_rel = 1;
                    // if the face we are testing is the best seen save it
                    if (cur_rel >= relation_minimum &&
                        (no_span  < min_split ||
                         no_span == min_split && cur_rel > best_rel)) {
                        best_face = ftest;
                        min_split = no_span;
                        best_rel  = cur_rel;
                    }
                }
            }
            // lower the scale factor
            relation_minimum *= relation_scale - .01;
        }
        return *best_face;
    }
};
    
} // NS Scene
} // NS OpenEngine

#endif // _BSP_FIND_DIVIDER_STRATEGY_H_
