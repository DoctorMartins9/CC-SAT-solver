/**
 * @copyright Copyright © 2019 Heap. All rights reserved.
 *
 * @license{<blockquote>
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * * Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 * </blockquote>}
 *
 * @author Enrico Martini                                                  <br>
 *         enrico.martini_02@studenti.univr.it
 * @date June, 2019
 * @version v1.0
 *
 * @file
 */

#pragma once
#include "heap.hpp"

namespace hp{ 

    /**
    *   @brief      Max heap class.
    *   @tparam T   supports multiple types of numeric data.
    * 
     */
    template<typename T>
    class MaxHeap : public Heap<T> {
    

    private:  

        /**
         * @brief           private recursive method for building the max-heap.
         * @param[in] heap  input vector reference to order.
         * @param[in] n     number of elements in vector.
         * @param[in] i     index of largest value.
         */
        void heapify(std::vector<Node<T>> &heap, uint64_t n, uint64_t i) override;


        /**
         * @brief   private method that calls heapify for building the max-heap.
         */
        void maxHeapify();

    public:

        using Heap<T>::heap;
        using Heap<T>::size;
        using Heap<T>::addElement;
        using Heap<T>::getVector;

        /**
         * @brief               constructor from unordered vector to heap.
         * @param[in] input     initial unordered vector.
         */
        MaxHeap(std::vector<T> &input);

        /**
         * @brief           static method for complete ordering a vector.
         * @param[in] vec   initial unoirdered vector.
         */
        static void heapSort(std::vector<T> &vec);
        

        /**
         * @brief           add an element to heap (not a node).
         * @param[in] n     value to insert into heap.
         */
        void addElement(T n);

        /**
         * @brief               erase the element at the given index.
         * @param[in] index     index of element to erase.
         */
        void erase(uint64_t index);

        /**
         * @brief               erase value (or values) equal to input value.
         * @param[in] value     value to erase.
         */
        void eraseByValue(T value);

        /**
         * @brief               add a vector to heap.
         * @param[in] vec       unordered vector to add to heap.
         */
        void addVector(std::vector<T> &vec);

        /**
         * @brief               override of the + operation.
         * @param[in] input     input heap to sum.
         * @return              return the resulting heap.
         */
        MaxHeap operator+(Heap<T> &input);

    };

}   // namespace 'heap'Node

#include <impl/max_heap.i.hpp>