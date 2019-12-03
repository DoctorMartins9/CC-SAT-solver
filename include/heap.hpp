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
#include "node.hpp"

namespace hp{

    /**
    *   @brief      Abstract parent class for generic heap.
    *   @tparam T   supports multiple types of numeric data.
    * 
     */
    template<typename T>
    class Heap {

    protected:

        std::vector<Node<T>> heap;  // Vector of elements    

        /**
         * @brief               virtual recursive method for building the max-heap.
         * @param[in] heap      input vector reference to order.
         * @param[in] n         number of elements in vector.
         * @param[in] i         index of largest value.
         */
        virtual void heapify(std::vector<Node<T>> &heap, uint64_t n, uint64_t i) = 0;

    public:

        /**
         * @brief               constructor from unordered vector to unordered heap.          
         * @param[in] input     initial unordered vector.
         */
        Heap (std::vector<T>& input);

        /**
         * @brief               add an element to heap.
         * @param[in] n         element to add to heap.
         */
        void addElement(T n);

        /*
         * @brief               erase a value by its index.
         * @param[in] index     index of value to erase.
         */
        virtual void erase(uint64_t index) = 0;

        /**
         * @brief               erase value/values.
         * @param[in] value     value of the element/elements to erase.
         */
        virtual void eraseByValue(T value) = 0;

        /**
         * @brief               add an unordered vector to heap.
         * @param[in] vec       unordered vector to add to heap.       
         */
        virtual void addVector(std::vector<T> &vec) = 0;
            
        /**
         * @brief               number of the elements in heap.
         * @return              return the size of the heap.
         */
        uint64_t size();

        /**
         * @brief               ordered vector of data from heap.
         * @return              return the ordered vector.
         */
        std::vector<T> getVector();

        /**
         * @brief               override of the << operator, useful for std::cout.
         * @param[in] stream    output stream.
         * @param[in] hp        heap to print.
         * @return              return the output stream for std::cout.
         */
        template<typename U>
        friend std::ostream& operator<<(std::ostream& stream, Heap<U>& hp);
        
        /**
         * @brief               access to element by index
         * @param[in] n         index of element
         * @return              return the element at the input index.
         */
        T operator[](uint64_t n);

    };
} // namespace 'hp'

#include <impl/heap.i.hpp>
