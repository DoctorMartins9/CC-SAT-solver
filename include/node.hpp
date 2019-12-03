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

namespace hp{

    /**
    *   @brief      Node useful for complex data structures like heap.
    *   @tparam T   supports multiple type of numeric data.
    * 
     */    
    template<typename T>
    class Node{
    
    private:
        T value;

        /**
         * @brief               set the value that the node contains.
         * @param[in] input     value to set.
         */    
        void setValue(T input);

    public:

        /**
         * @brief   default constructor.
         */
        Node();

        /**
         * @brief           constructor given a value to contain.       
         * @param[in] i     value that the node will contain.
         */        
        Node(T i);

        /**
         * @brief           override of the = operator for assignments.
         * @param[in] n     node to assign.
         * @return          Node with value given in node input.
         */
        Node operator= (Node n);

        /**
         * @brief           get the value contained into the node.
         * @return          return the value of the node.
         */
        T getValue();

    };
}   // namespace 'hp'

#include "impl/node.i.hpp"
