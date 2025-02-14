/**
 * @copyright Copyright © 2019 Enrico Martini. All rights reserved.
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
 * @date December, 2019
 * @version v1.0
 *
 * @file
 */
#pragma once
#include <string>

namespace ccsat{

class Node{
    private:
        std::string fn;              // Costant or symbol function name
        int id;                      // Node's unique identification number
        std::vector<int> args;       // If node is function here there are its arguments
        int find;                    // Representative of his congruent class
        std::vector<int> ccpar;      // Congruence closure parents list 

    public:

        // Constructor
        Node();
        Node(std::string fn_i, int id_i, std::vector<int> args_i, 
                               int find_i,std::vector<int> ccpar_i);

        // Methods
        std::string get_fn();
        int get_id();
        std::vector<int> get_args();
        std::vector<int> get_ccpar();
        int get_find();
        void set_find(int find_i);
        void set_ccpar(std::vector<int> ccpar_i);
        void add_ccpar(int ccpar_i);
        bool is_equal(Node input);
};

}   // namespace 'ccsat'

#include "impl/node.i.hpp"
