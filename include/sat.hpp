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
#include "formula.hpp"
#include <vector>
#include <string>
#include <algorithm>
#include <thread>
#include <future>

namespace ccsat{

class Sat{
    private:
        // Variables
        Formula f;
        std::vector<Node> n_set;
        #ifdef F_LIST
        bool is_sat = true;
        #endif
        // Sorte
        std::vector<int> atoms;
        std::vector<int> arrays;
        std::vector<Clause> forbidden_list;
        // Methods
        bool is_legal();
        int transform_node(std::string n);
        void initialize_DAG(std::string input);
        // FIND i
        int FIND(int index);
        // UNION i1 i2
        void UNION(int i1, int i2);
        // CCPAR i
        std::vector<int> CCPAR(int index);
        // CONGRUENT i1 i2
        bool CONGRUENT(int i1, int i2);
        // MERGE i1 i2
        void MERGE(int i1, int i2);

    public:
        // Constructors
        Sat();
        Sat(Formula input );
        Sat(std::string input);

        // Methods
        std::vector<std::string> split_arguments(std::string s);
        static std::vector<std::string> split(std::string s);
        static bool well_formed(std::string s);
        void print_status();
        Formula get_formula();
        void set_formula(Formula input);
        std::vector<Node> get_nodes();
        bool classic_congruence_closure();
        bool list_congruence_closure();
        static bool solve(std::string s);
        static bool solve_parallel(std::string s);
        static void solve_th(std::string s,bool* result);
        static std::vector<std::string> detect_store(std::string input);
        static bool SOLVE(std::string input,std::string mode);
};

}   // namespace 'ccsat'

#include "impl/sat.i.hpp"
